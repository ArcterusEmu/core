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

#include "ScriptPCH.h"
#include "icecrown_citadel.h"

enum Yells
{
    SAY_STINKY                  = -1631078,
    SAY_AGGRO                   = -1631079,
    EMOTE_GAS_SPORE             = -1631081,
    EMOTE_WARN_GAS_SPORE        = -1631082,
    SAY_PUNGENT_BLIGHT          = -1631083,
    EMOTE_WARN_PUNGENT_BLIGHT   = -1631084,
    EMOTE_PUNGENT_BLIGHT        = -1631085,
    SAY_KILL_1                  = -1631086,
    SAY_KILL_2                  = -1631087,
    SAY_BERSERK                 = -1631088,
    SAY_DEATH                   = -1631089
};

enum Spells
{
    SPELL_PUNGENT_BLIGHT     = 69195,
    SPELL_INHALE_BLIGHT      = 69165,
    SPELL_VILE_GAS           = 69240,
    SPELL_GASTRIC_BLOAT      = 72219,
    SPELL_GAS_SPORES         = 69278,
    SPELL_UNOCULATED         = 69291,
    SPELL_GAS_FLOOD          = 71379,
    SPELL_MORTAL_WOUND       = 71127,
    SPELL_DECIMATE           = 71123,
    SPELL_PLAGUE_STENCH      = 71805,
    SPELL_GASTRIC_EXPLOSION  = 72227
};

static const uint32 gaseousBlight[3]        = {69157, 69162, 69164};
static const uint32 gaseousBlightVisual[3]  = {69126, 69152, 69154};

class boss_festergut : public CreatureScript
{
    public:
        boss_festergut() : CreatureScript("boss_festergut") { }

        struct boss_festergutAI : public BossAI
        {
            boss_festergutAI(Creature* pCreature) : BossAI(pCreature, DATA_FESTERGURT)
            {
                pInstance = me->GetInstanceScript();
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
            }

            void Reset()
            {
                m_uiInhaleBlightTimer = urand(23000,29000);
                m_uiVileGasTimer = 20000;
                m_uiGasSporesTimer = 20000;
                m_uiGastricBloatTimer = 12000;
                m_uiBerserkTimer = 300000;
                m_uiGaseousTimer = 1000;

                m_uiInhaleBlightCount = 0;

                if (Creature* gasDummy = GetClosestCreatureWithEntry(me, CREATURE_ORANGE_GAS_STALKER, 100.0f, true))
                {
                    m_uiGasDummyGUID = gasDummy->GetGUID();
                    for (uint8 i = 0; i < 3; ++i)
                    {
                        gasDummy->RemoveAurasDueToSpell(gaseousBlight[i]);
                        gasDummy->RemoveAurasDueToSpell(gaseousBlightVisual[i]);
                    }
                }

                if (pInstance && me->isAlive())
                    pInstance->SetData(DATA_FESTERGURT_EVENT, NOT_STARTED);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoScriptText(SAY_AGGRO, me);

                if (pInstance)
                    pInstance->SetData(DATA_FESTERGURT_EVENT, IN_PROGRESS);

                if (Creature* professor = Unit::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                {
                    professor->AI()->DoAction(ACTION_FESTERGUT_COMBAT);
                    professor->AI()->DoAction(ACTION_FESTERGUT_GAS);
                }

                if (Creature* gasDummy = GetClosestCreatureWithEntry(me, CREATURE_ORANGE_GAS_STALKER, 100.0f, true))
                {
                    m_uiGasDummyGUID = gasDummy->GetGUID();
                    for (uint8 i = 0; i < 3; ++i)
                    {
                        gasDummy->CastSpell(gasDummy,gaseousBlight[i], true);
                    }
                }
            }

            void JustDied(Unit* /*pKiller*/)
            {
                if (!pInstance)
                    return;

                DoScriptText(SAY_DEATH, me);

                pInstance->SetData(DATA_FESTERGURT_EVENT, DONE);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GASTRIC_BLOAT);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_VILE_GAS);
                me->RemoveAurasDueToSpell(SPELL_PUNGENT_BLIGHT);

                if (Creature* professor = Unit::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                    professor->AI()->DoAction(ACTION_FESTERGUT_DEATH);

                if (Creature* gasDummy = Unit::GetCreature(*me, m_uiGasDummyGUID))
                    gasDummy->RemoveAllAuras();
            }

            void JustReachedHome()
            {
                if (!pInstance)
                    return;

                pInstance->SetData(DATA_FESTERGURT_EVENT, FAIL);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GASTRIC_BLOAT);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_VILE_GAS);
                me->RemoveAurasDueToSpell(SPELL_PUNGENT_BLIGHT);
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

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiGastricBloatTimer < uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_GASTRIC_BLOAT);
                    m_uiGastricBloatTimer = 13000;
                } else m_uiGastricBloatTimer -= uiDiff;

                if (m_uiInhaleBlightTimer < uiDiff)
                {
                    if (Creature* gasDummy = Unit::GetCreature(*me, m_uiGasDummyGUID))
                    {
                        if(m_uiInhaleBlightCount == 3)
                        {
                            DoScriptText(EMOTE_WARN_PUNGENT_BLIGHT, me);
                            DoCast(me, SPELL_PUNGENT_BLIGHT);
                            DoScriptText(SAY_PUNGENT_BLIGHT, me);
                            m_uiInhaleBlightCount = 0;

                            if (Creature* professor = Unit::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                                professor->AI()->DoAction(ACTION_FESTERGUT_GAS);
                        }
                        else
                        {
                            DoCast(me, SPELL_INHALE_BLIGHT);
                            gasDummy->RemoveAurasDueToSpell(gaseousBlight[m_uiInhaleBlightCount]);
                            gasDummy->RemoveAurasDueToSpell(gaseousBlightVisual[m_uiInhaleBlightCount]);
                            ++m_uiInhaleBlightCount;
                        }
                    }
                    m_uiInhaleBlightTimer = urand(23000, 29000);
                } else m_uiInhaleBlightTimer -= uiDiff;

                if (m_uiVileGasTimer < uiDiff)
                {
                    for (uint8 i = 1; i <= 3; i++)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                        {
                            DoCast(pTarget, SPELL_VILE_GAS, true);
                        }
                    }
                    m_uiVileGasTimer = 20000;
                } else m_uiVileGasTimer -= uiDiff;

                if (m_uiGasSporesTimer < uiDiff)
                {
                    uint32 count = RAID_MODE(2,3,2,3);
                    for (uint8 i = 1; i <= count; i++)
                    {
                        if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                        {
                            DoScriptText(EMOTE_WARN_GAS_SPORE, me);
                            pTarget->CastSpell(pTarget, SPELL_GAS_SPORES, true);
                            DoScriptText(EMOTE_GAS_SPORE, me);
                        }
                    }
                    m_uiGasSporesTimer = 20000;
                } else m_uiGasSporesTimer -= uiDiff;

                if(m_uiBerserkTimer < uiDiff)
                {
                    DoCast(me, SPELL_BERSERK);
                    DoScriptText(SAY_BERSERK, me);
                    m_uiBerserkTimer = 300000;
                } else m_uiBerserkTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        private:
            InstanceScript* pInstance;

            uint32 m_uiInhaleBlightTimer;
            uint32 m_uiGasSporesTimer;
            uint32 m_uiVileGasTimer;
            uint32 m_uiGastricBloatTimer;
            uint32 m_uiBerserkTimer;
            uint32 m_uiGaseousTimer;
            uint64 m_uiGasDummyGUID;
            uint8 m_uiInhaleBlightCount;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_festergutAI(pCreature);
        }
};

class npc_stinky_icc : public CreatureScript
{
    public:
        npc_stinky_icc() : CreatureScript("npc_stinky_icc") { }

        struct npc_stinky_iccAI : public ScriptedAI
        {
            npc_stinky_iccAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            void Reset()
            {
                m_uiDecimateTimer = 23000;
                m_uiMortalTimer = urand(8000, 10000);

                DoCast(me, SPELL_PLAGUE_STENCH);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if(m_uiDecimateTimer < uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_DECIMATE);
                    m_uiDecimateTimer = 23000;
                } else m_uiDecimateTimer -= uiDiff;

                if(m_uiMortalTimer < uiDiff)
                {
                    DoCast(me->getVictim(), SPELL_MORTAL_WOUND);
                    m_uiMortalTimer = urand(8000,10000);
                } else m_uiMortalTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                uint64 festergutGUID = pInstance ? pInstance->GetData64(DATA_FESTERGURT) : 0;
                if (Creature *festergut = me->GetCreature(*me, festergutGUID))
                    DoScriptText(SAY_STINKY, festergut);
            }
        private:
            InstanceScript* pInstance;
            uint32 m_uiDecimateTimer;
            uint32 m_uiMortalTimer;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_stinky_iccAI(pCreature);
        }
};

class spell_festergut_gastric_bloat : public SpellScriptLoader
{
    public:
        spell_festergut_gastric_bloat() : SpellScriptLoader("spell_festergut_gastric_bloat") { }


        class spell_festergut_gastric_bloat_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_festergut_gastric_bloat_SpellScript)
            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                Aura const* aura = GetHitUnit()->GetAura(GetSpellInfo()->Id);
                if (!(aura && aura->GetStackAmount() == 10))
                    return;

                SpellEntry const* spellInfo = sSpellStore.LookupEntry(SPELL_GASTRIC_EXPLOSION);
                if (!spellInfo)
                    return;

                spellInfo = sSpellMgr.GetSpellForDifficultyFromSpell(spellInfo, GetCaster());
                GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->Id);
                GetHitUnit()->CastSpell(GetHitUnit(), spellInfo, true);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_festergut_gastric_bloat_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_festergut_gastric_bloat_SpellScript();
        }
};

void AddSC_boss_festergut()
{
    new boss_festergut();
    new npc_stinky_icc();
    new spell_festergut_gastric_bloat();
}