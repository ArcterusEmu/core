/*
* Copyright (C) 2009 - 2010 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/*
*Need correct timers
*Need add  Sindragossa fly in fly phase
*/

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "icecrown_citadel.h"

enum Yells
{
    SAY_AGGRO            = -1666071,
    SAY_UNCHAIND_MAGIC   = -1666072,
    SAY_BLISTERING_COLD  = -1666073,
    SAY_BREATH           = -1666074,
    SAY_AIR_PHASE        = -1666075,
    SAY_PHASE_3          = -1666076,
    SAY_KILL_1           = -1666077,
    SAY_KILL_2           = -1666078,
    SAY_BERSERK          = -1666079,
    SAY_DEATH            = -1666080
};

enum Spells
{
    SPELL_FROST_AURA          = 70084,
    SPELL_CLEAVE              = 19983,
    SPELL_TAIL_SMASH          = 71077,
    SPELL_FROST_BREATH        = 73061,
    SPELL_PERMEATING_CHILL    = 70107, //
    SPELL_PERMEATING_AURA     = 70106,
    SPELL_UNCHAINED_MAGIC     = 69762, // нужно узнать механику на офе
    SPELL_ICY_TRIP_PULL       = 70117,
    SPELL_BOMB_VISUAL_1       = 64624,
    SPELL_BOMB_VISUAL_2       = 69016,
    SPELL_BLISTERING_COLD     = 71047,
    SPELL_FROST_BOMB_TRIGGER  = 69846,
    SPELL_FROST_BEACON        = 70126,
    SPELL_ICE_TOMB            = 70157,
    SPELL_FROST_BOMB          = 69845,
    SPELL_MYSTIC_BUFFED       = 70128,
    SPELL_ASPHYXATION         = 71665,
    SPELL_FROST_AURA_ADD      = 71387,
    SPELL_FROST_BREATH_ADD    = 71386,
    SPELL_ICE_BLAST           = 71376,
    SPELL_BELLOWING_ROAR      = 36922,
    SPELL_CLEAVE_ADD          = 40505,
    SPELL_TAIL_SWEEP          = 71369
};

enum ePoints
{
    POINT_HOME                = 1
};

const Position SpawnLoc[]=
{
    {4523.889f, 2486.907f, 280.249f, 3.155f}, //fly pos
    {4407.439f, 2484.905f, 203.374f, 3.166f}, //land pos
    {4671.521f, 2481.815f, 343.365f, 3.166f} //spawn pos
};

class boss_sindragosa : public CreatureScript
{
    public:
        boss_sindragosa() : CreatureScript("boss_sindragosa") { }

        struct boss_sindragosaAI : public BossAI
        {
            boss_sindragosaAI(Creature* pCreature) : BossAI(pCreature, DATA_SINDRAGOSA)
            {
                pInstance = me->GetInstanceScript();
            }

            void Reset()
            {
                m_uiPhase = 1;

                m_uiBreathTimer = 15000;
                m_uiTailSmashTimer = 15000;
                m_uiBlisteringColdTimer = 30000;
                m_uiMarkTimer = 25000;
                m_uiPermatingChilTimer = 12000;
                m_uiBerserkTimer = 600000;
                m_uiChangePhaseTimer = 110000;
                m_uiUnchainedMagicTimer = 12000;
                m_uiBombTimer = 9000;
                m_uiCleaveTimer = 5000;

                me->SetFlying(true);
                me->SetSpeed(MOVE_WALK, 1.5f, true);
                me->SetSpeed(MOVE_RUN, 1.5f, true);
                me->SetSpeed(MOVE_FLIGHT, 2.5f, true);

                bSwitch = false;
                bMystic = false;

                if(!pInstance)
                    return;

                pInstance->SetData(DATA_SINDRAGOSA_EVENT, NOT_STARTED);
            }

            void EnterCombat(Unit* /*who*/)
            {
                if(pInstance)
                    pInstance->SetData(DATA_SINDRAGOSA_EVENT, IN_PROGRESS);

                DoCast(me, SPELL_FROST_AURA);
                DoScriptText(SAY_AGGRO, me);
            }

            void JustDied(Unit* /*pKiller*/)
            {
                if (!pInstance)
                    return;

                DoScriptText(SAY_DEATH, me);

                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PERMEATING_CHILL);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_UNCHAINED_MAGIC);
                pInstance->SetData(DATA_SINDRAGOSA_EVENT, DONE);
                if(pInstance->GetData(DATA_ALL_YOU_CAN_EAT) == DONE)
                    pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_ALL_YOU_CAN_EAT_10,ACHIEV_ALL_YOU_CAN_EAT_25));
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                {
                    switch(rand()%1)
                    {
                        case 0: DoScriptText(SAY_KILL_1, me); break;
                        case 1: DoScriptText(SAY_KILL_2, me); break;
                    }
                }
            }

            void JustReachedHome()
            {
                if (!pInstance)
                    return;

                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PERMEATING_CHILL);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_UNCHAINED_MAGIC);
                pInstance->SetData(DATA_SINDRAGOSA_EVENT, FAIL);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiBerserkTimer <= uiDiff)
                {
                    DoScriptText(SAY_BERSERK, me);
                    DoCast(me, SPELL_BERSERK);
                    m_uiBerserkTimer = 600000;
                } else m_uiBerserkTimer -= uiDiff;

                if(m_uiPhase == 1)
                {
                    if(m_uiUnchainedMagicTimer <= uiDiff)
                    {
                        for (uint8 i = 1; i <= urand(2, 4); ++i)
                        {
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, -10.0f, true, -SPELL_UNCHAINED_MAGIC))
                                DoCast(pTarget, SPELL_UNCHAINED_MAGIC);
                        }
                        DoScriptText(SAY_UNCHAIND_MAGIC, me);
                        m_uiUnchainedMagicTimer = 12000;
                    } else m_uiUnchainedMagicTimer -= uiDiff;

                    if (m_uiPermatingChilTimer <= uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true, -SPELL_PERMEATING_CHILL))
                            DoCast(pTarget, SPELL_PERMEATING_CHILL);
                        m_uiPermatingChilTimer = 20000;
                    } else m_uiPermatingChilTimer -= uiDiff;

                    if (m_uiBreathTimer <= uiDiff)
                    {
                        DoScriptText(SAY_BREATH, me);
                        DoCastVictim(SPELL_FROST_BREATH);
                        m_uiBreathTimer = 15000;
                    } else m_uiBreathTimer -= uiDiff;

                    if (m_uiCleaveTimer <= uiDiff)
                    {
                        DoCastVictim(SPELL_CLEAVE);
                        m_uiCleaveTimer = 6000;
                    } else m_uiCleaveTimer -= uiDiff;

                    if (m_uiTailSmashTimer <= uiDiff)
                    {
                        DoCast(SPELL_TAIL_SMASH);
                        m_uiTailSmashTimer = 15000;
                    } else m_uiTailSmashTimer -= uiDiff;

                    if (m_uiBlisteringColdTimer <= uiDiff)
                    {
                        DoCast(SPELL_ICY_TRIP_PULL);
                        DoCast(SPELL_BLISTERING_COLD);
                        DoScriptText(SAY_BLISTERING_COLD, me);
                        m_uiBlisteringColdTimer = 30000;
                    } else m_uiBlisteringColdTimer -= uiDiff;
                }

                if(m_uiPhase == 2)
                {
                    if (m_uiMarkTimer < uiDiff)
                    {
                        for (uint8 i = 1; i <= RAID_MODE(2,5,2,5); ++i)
                        {
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true, -SPELL_FROST_BEACON))
                                DoCast(pTarget, SPELL_FROST_BEACON);
                        }
                        m_uiMarkTimer = 25000;
                    } else m_uiMarkTimer -= uiDiff;

                    if (m_uiBombTimer <= uiDiff)
                    {
                        if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                            DoCast(pTarget, SPELL_FROST_BOMB);
                        m_uiBombTimer = 10000;
                    } else m_uiBombTimer -= uiDiff;
                }

                if(m_uiPhase == 3)
                {
                    if (m_uiMarkTimer < uiDiff)
                    {
                        for (uint8 i = 1; i <= RAID_MODE(2,5,2,5); ++i)
                        {
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true, -SPELL_FROST_BEACON))
                                DoCast(pTarget, SPELL_FROST_BEACON);
                        }
                        m_uiMarkTimer = 25000;
                    } else m_uiMarkTimer -= uiDiff;

                    if (m_uiBreathTimer <= uiDiff)
                    {
                        DoScriptText(SAY_BREATH, me);
                        DoCast(SPELL_FROST_BREATH);
                        m_uiBreathTimer = 15000;
                    } else m_uiBreathTimer -= uiDiff;

                    if(!bMystic)
                    {
                       DoCast(me, SPELL_MYSTIC_BUFFED);
                       bMystic = true;
                    }
                }

                if((HealthBelowPct(36)) && !bSwitch)
                {
                    DoScriptText(SAY_PHASE_3, me);
                    m_uiPhase = 3;
                    bSwitch = true;
                }

                if (m_uiChangePhaseTimer < uiDiff)
                {
                    if(bSwitch)
                        return;

                        switch (m_uiPhase)
                        {
                            case 1:
                                DoScriptText(SAY_AIR_PHASE, me);
                                m_uiPhase = 2;
                                break;
                            case 2:
                                m_uiPhase = 1;
                                break;
                        }
                    m_uiChangePhaseTimer = 110000;
                } else m_uiChangePhaseTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* pInstance;

            uint8 m_uiPhase;
            uint32 m_uiBreathTimer;
            uint32 m_uiCleaveTimer;
            uint32 m_uiTailSmashTimer;
            uint32 m_uiBlisteringColdTimer;
            uint32 m_uiBerserkTimer;
            uint32 m_uiMarkTimer;
            uint32 m_uiPermatingChilTimer;
            uint32 m_uiChangePhaseTimer;
            uint32 m_uiUnchainedMagicTimer;
            uint32 m_uiBombTimer;

            bool bSwitch;
            bool bMystic;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_sindragosaAI(pCreature);
        }
};

class npc_ice_tomb : public CreatureScript
{
    public:
        npc_ice_tomb() : CreatureScript("npc_ice_tomb") { }

        struct npc_ice_tombAI: public Scripted_NoMovementAI
        {
            npc_ice_tombAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                IceTombGUID = 0;
            }

            void SetGUID(const uint64& guid)
            {
                IceTombGUID = guid;
            }

            void Reset()
            {
                IceTombGUID = 0;
            }

            void JustDied(Unit* pKiller)
            {
                if (Player* IceTomb = ObjectAccessor::GetPlayer(*me, IceTombGUID))
                {
                    IceTomb->RemoveAurasDueToSpell(SPELL_ICE_TOMB);
                    IceTomb->RemoveAurasDueToSpell(SPELL_ASPHYXATION);
                }
            }

            void KilledUnit(Unit *pVictim)
            {
                me->Kill(me);
            }

            void UpdateAI(const uint32 /*uiDiff*/)
            {
                if(!IceTombGUID)
                    return;

                if (Player* IceTomb = ObjectAccessor::GetPlayer(*me, IceTombGUID))
                    if (!IceTomb->HasAura(SPELL_ICE_TOMB))
                        me->Kill(me);
            }

        private:
            uint64 IceTombGUID;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_ice_tombAI(pCreature);
        }
};

class npc_frost_bomb : public CreatureScript
{
    public:
        npc_frost_bomb() : CreatureScript("npc_frost_bomb") { }

        struct npc_frost_bombAI: public ScriptedAI
        {
            npc_frost_bombAI(Creature* pCreature) : ScriptedAI(pCreature) { }

            void Reset()
            {
                DoStartNoMovement(me->getVictim());

                m_uiVisualTimer = 6000;
                m_uiBoomTimer = 9000;

                end = false;

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            void EnterCombat(Unit* /*who*/) { }

            void UpdateAI(const uint32 uiDiff)
            {
                if (end == true)
                {
                    DoCast(me, SPELL_FROST_BOMB);
                    me->ForcedDespawn();
                    end = false;
                }

                if (m_uiVisualTimer <= uiDiff)
                {
                    DoCast(me, SPELL_BOMB_VISUAL_1);
                    m_uiVisualTimer = 99999;
                } else m_uiVisualTimer -= uiDiff;

                if (m_uiBoomTimer <= uiDiff)
                {
                    DoCast(me, SPELL_BOMB_VISUAL_2);
                    end = true;
                } else m_uiBoomTimer -= uiDiff;
            }

        private:
            uint32 m_uiBoomTimer;
            uint32 m_uiVisualTimer;
            bool end;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_frost_bombAI(pCreature);
        }
};

class npc_rimefang : public CreatureScript
{
    public:
        npc_rimefang() : CreatureScript("npc_rimefang") { }

        struct npc_rimefangAI: public ScriptedAI
        {
            npc_rimefangAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            void Reset()
            {
                m_uiFrostBreathTimer = 5000;
                m_uiIceBlastTimer = 7000;
                me->SetFlying(true);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoCast(me, SPELL_FROST_AURA_ADD);
            }

            void JustDied(Unit* /*killer*/)
            {
                if(!pInstance)
                    return;

                if(pInstance->GetData(DATA_SINDRAGOSA_EVENT) != DONE)
                {
                    pInstance->SetData(DATA_SPAWN, +1);
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiFrostBreathTimer <= uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_FROST_BREATH_ADD);
                    m_uiFrostBreathTimer = 6000;
                } else m_uiFrostBreathTimer -= uiDiff;

                if (m_uiIceBlastTimer <= uiDiff)
                {
                    DoCast(me, SPELL_ICE_BLAST);
                    m_uiIceBlastTimer = 8000;
                } else m_uiIceBlastTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* pInstance;

            uint32 m_uiFrostBreathTimer;
            uint32 m_uiIceBlastTimer;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_rimefangAI(pCreature);
        }
};

class npc_spinestalker : public CreatureScript
{
    public:
        npc_spinestalker() : CreatureScript("npc_spinestalker") { }

        struct npc_spinestalkerAI: public ScriptedAI
        {
            npc_spinestalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            void Reset()
            {
                m_uiRoarTimer = 14000;
                m_uiCleaveTimer = 6000;
                m_uiSweepTimer = 7000;
                me->SetFlying(true);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoCast(me, SPELL_FROST_AURA_ADD);
            }

            void JustDied(Unit* /*killer*/)
            {
                if(!pInstance)
                    return;

                if(pInstance->GetData(DATA_SINDRAGOSA_EVENT) != DONE)
                {
                    pInstance->SetData(DATA_SPAWN, +1);
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiRoarTimer <= uiDiff)
                {
                    DoCastAOE(SPELL_BELLOWING_ROAR);
                    m_uiRoarTimer = 15000;
                } else m_uiRoarTimer -= uiDiff;

                if (m_uiCleaveTimer <= uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_CLEAVE_ADD);
                    m_uiCleaveTimer = 5000;
                } else m_uiCleaveTimer -= uiDiff;

                if (m_uiSweepTimer <= uiDiff)
                {
                    DoCast(SPELL_TAIL_SWEEP);
                    m_uiSweepTimer = 7000;
                } else m_uiSweepTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        private:
            InstanceScript* pInstance;

            uint32 m_uiRoarTimer;
            uint32 m_uiCleaveTimer;
            uint32 m_uiSweepTimer;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_spinestalkerAI(pCreature);
        }
};

class spell_sindragosa_ice_tomb : public SpellScriptLoader
{
    public:
        spell_sindragosa_ice_tomb() : SpellScriptLoader("spell_sindragosa_ice_tomb") { } //70157


        class spell_sindragosa_ice_tomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_ice_tomb_AuraScript)

            void OnRemove(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                if(Unit* beacon = aurApp->GetBase()->GetCaster())
                {
                    if (InstanceScript* instance = aurApp->GetBase()->GetOwner()->GetInstanceScript())
                        if (Creature* sindragosa = Unit::GetCreature(*aurApp->GetBase()->GetOwner(), instance->GetData64(DATA_SINDRAGOSA)))
                            if(sindragosa->isAlive())
                                sindragosa->CastSpell(beacon, SPELL_ICE_TOMB, true);

                    beacon->CastSpell(beacon, SPELL_ASPHYXATION, true);
                    Creature* tomb = beacon->SummonCreature(CREATURE_ICE_TOMB, beacon->GetPositionX(), beacon->GetPositionY(), beacon->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                    if(tomb)
                        tomb->AI()->SetGUID(beacon->GetGUID());
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_sindragosa_ice_tomb_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_ice_tomb_AuraScript();
        }
};

class spell_sindragosa_mystic_buffet : public SpellScriptLoader
{
    public:
        spell_sindragosa_mystic_buffet() : SpellScriptLoader("spell_sindragosa_mystic_buffet") { } //70127


        class spell_sindragosa_mystic_buffet_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_mystic_buffet_AuraScript)

            void OnApply(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                if (InstanceScript* instance = aurApp->GetBase()->GetOwner()->GetInstanceScript())
                    if(aurApp->GetBase()->GetStackAmount() >= 5)
                        instance->SetData(DATA_ALL_YOU_CAN_EAT, FAIL);
                    else
                        instance->SetData(DATA_ALL_YOU_CAN_EAT, DONE);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sindragosa_mystic_buffet_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_mystic_buffet_AuraScript();
        }
};

class spell_sindragosa_unchained_magic : public SpellScriptLoader
{
    public:
        spell_sindragosa_unchained_magic() : SpellScriptLoader("spell_sindragosa_unchained_magic") { } //69766


        class spell_sindragosa_unchained_magic_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sindragosa_unchained_magic_AuraScript)

            void OnRemove(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                Unit* caster = GetCaster();
                if (!caster)
                    return;

                SpellEntry const* spell = sSpellStore.LookupEntry(71044);
                spell = sSpellMgr.GetSpellForDifficultyFromSpell(spell, caster);
                int32 damage = (aurApp->GetBase()->GetStackAmount() * 2000);
                aurApp->GetTarget()->CastCustomSpell(71044, SPELLVALUE_BASE_POINT0, damage, aurApp->GetTarget(), true, NULL, aurEff, GetCasterGUID());
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_sindragosa_unchained_magic_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sindragosa_unchained_magic_AuraScript();
        }
};

void AddSC_boss_sindragosa()
{
    new boss_sindragosa();
    new npc_spinestalker();
    new npc_rimefang();
    new npc_ice_tomb();
    new npc_frost_bomb();
    new spell_sindragosa_ice_tomb();
    new spell_sindragosa_mystic_buffet(); //for achievement
    new spell_sindragosa_unchained_magic();
}