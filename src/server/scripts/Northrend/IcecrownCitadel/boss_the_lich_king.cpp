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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "icecrown_citadel.h"

#define GOSSIP_MENU 10600
//#define GOSSIP_MENU "Long have I waited for this day, hero. Are you and your allies prepared to bring the Lich King to justice? We charge on your command!"
#define GOSSIP_START_EVENT "We are prepared, Highlord. Let us battle for the fate of Azeroth! For the light of dawn!"

enum Yells
{
    SAY_INTRO_1_KING         = -1810001,
    SAY_INTRO_2_TIRION       = -1810002,
    SAY_INTRO_3_KING         = -1810003,
    SAY_INTRO_4_TIRION       = -1810004,
    SAY_INTRO_5_KING         = -1810005,
    SAY_AGGRO                = -1810006,
    SAY_REMORSELESS_WINTER   = -1810007,
    SAY_RANDOM_1             = -1810008,
    SAY_RANDOM_2             = -1810009,
    SAY_KILL_1               = -1810010,
    SAY_KILL_2               = -1810011,
    SAY_BERSERK              = -1810012,
    SAY_ENDING_1_KING        = -1810013,
    SAY_ENDING_2_KING        = -1810014,
    SAY_ENDING_3_KING        = -1810015,
    SAY_ENDING_4_KING        = -1810016,
    SAY_ENDING_5_TIRION      = -1810017,
    SAY_ENDING_6_KING        = -1810018,
    SAY_ENDING_8_TIRION      = -1810020,
    SAY_ENDING_9_FATHER      = -1810021,
    SAY_ENDING_10_TIRION     = -1810022,
    SAY_ENDING_11_FATHER     = -1810023,
    SAY_ENDING_12_KING       = -1810024,
    SAY_DEATH_KING           = -1810025,
    SAY_ESCAPE_FROSTMOURNE   = -1810026,
    SAY_HARVEST_SOUL         = -1810027,
    SAY_DEVOURED_FROSTMOURNE = -1810028,
    SAY_SUMMON_VALKYR        = -1810029,
    SAY_BROKEN_ARENA         = -1810030,
    SAY_10_PROZENT           = -1810031,
    SAY_EMOTE_DEFILE         = -1810032,
};

enum Spells
{
    SPELL_SUMMON_SHAMBLING_HORROR    = 70372,
    SPELL_SUMMON_DRUDGE_GHOULS       = 70359,
    SPELL_SUMMON_ICE_SPEHERE         = 69104,
    SPELL_SUMMON_RAGING_SPIRIT       = 69200,
    SPELL_SUMMON_VALKYR              = 74361,
    SPELL_SUMMON_DEFILE              = 72762,
    SPELL_SUMMON_VILE_SPIRIT         = 70498,
    SPELL_SUMMON_BROKEN_FROSTMOURNE  = 72406,
    SPELL_SUMMON_SHADOW_TRAP         = 73539,
    SPELL_INFEST                     = 70541,
    SPELL_NECROTIC_PLAGUE            = 70337, //70337 - initial cast
    SPELL_NECROTIC_PLAGUE_IMMUNITY   = 72846,
    SPELL_PLAGUE_SIPHON              = 74074,
    SPELL_REMORSELES_WINTER          = 68981,
    SPELL_REMORSELES_WINTER_DAMAGE   = 68983,
    SPELL_PAIN_AND_SUFFERING         = 72133,
    SPELL_WINGS_OF_THE_DAMNED        = 74352,
    SPELL_SOUL_REAPER                = 69409,
    SPELL_SOUL_REAPER_HASTE_AURA     = 69410,
    SPELL_HARVEST_SOUL_TELEPORT      = 71372,
    SPELL_HARVEST_SOULS              = 74325,
    SPELL_QUAKE                      = 72262,
    SPELL_CHANNEL_KING               = 71769,
    SPELL_BROKEN_FROSTMOURNE         = 72398,
    SPELL_BOOM_VISUAL                = 72726,
    SPELL_ICEBLOCK_TRIGGER           = 71614,
    SPELL_TIRION_LIGHT               = 71797,
    SPELL_FROSTMOURNE_TRIGGER        = 72405,
    SPELL_DISENGAGE                  = 61508,
    SPELL_FURY_OF_FROSTMOURNE        = 70063,
    SPELL_REVIVE_VISUAL              = 37755,
    SPELL_REVIVE                     = 72429,
    SPELL_REVIVE_EFFECT              = 72423,
    SPELL_CLONE_PLAYER               = 57507,
    SPELL_DEFILE                     = 72743,
    SPELL_ICE_PULSE                  = 69091,
    SPELL_ICE_BURST                  = 69108,
    SPELL_LIFE_SIPHON                = 73783,
    SPELL_SOUL_SHRIEK                = 69242,
    SPELL_WHOCKVAWE                  = 72149,
    SPELL_ENRAGE                     = 72143,
    SPELL_BURST                      = 70503,
    SPELL_VILE_SPIRIT_DISTANCE_CHECK = 70502,
    SPELL_ICE_BURST_DISTANCE_CHECK   = 69109,
    SPELL_VILE_SPIRIT_ACTIVE         = 72130,
    SPELL_RAGING_VISUAL              = 69198

    //SPELL_70501 //Vile Spirit Move Target Search
};

enum ePoints
{
    POINT_PLATFORM_CENTRE            = 3659701,
    POINT_PLATFORM_END               = 3659702,
    POINT_VALKYR_END                 = 3659703,
    POINT_VALKYR_ZET                 = 3659704
};

struct Position MovePos[]=
{
    {461.792633f, -2125.855957f, 1040.860107f, 0.0f}, // move
    {503.156525f, -2124.516602f, 1040.860107f, 0.0f}, // move ending
    {490.110779f, -2124.989014f, 1040.860352f, 0.0f}, // move tirion frostmourne
    {478.333466f, -2124.618652f, 1040.859863f, 0.0f}, // move tirion attack
    {498.004486f, 2201.573486f, 1046.093872f, 0.0f}  // move valkyr
};

//TODO:
//Need fixed:
//raging spirit aura
//raging spirit cast 69198
//69200 - must be aura with duration: 5 seconds

/*struct Locations
{
    float x,y,z;
};

static Locations TeleportPoint[]=
{
    {959.996f, 212.576f, 193.843f},
    {932.537f, 231.813f, 193.838f},
    {958.675f, 254.767f, 193.822f},
    {946.955f, 201.316f, 192.535f},
    {944.294f, 149.676f, 197.551f},
    {930.548f, 284.888f, 193.367f},
    {965.997f, 278.398f, 195.777f},
};*/

Creature* pLichKing;
Creature* pTirion;
Creature* pFather;
Creature* pFrostmourne;

class boss_the_lich_king : public CreatureScript
{
    public:
        boss_the_lich_king() : CreatureScript("boss_the_lich_king") { }

        struct boss_the_lich_kingAI : public BossAI
        {
            boss_the_lich_kingAI(Creature* pCreature) : BossAI(pCreature, DATA_LICH_KING), summons(me)
            {
                pInstance = me->GetInstanceScript();
                pLichKing = me;
            }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                m_uiPhase = 1;
                m_uiRandomSpeechTimer = 33000;
                m_uiBerserkTimer = 900000;
                m_uiSummonShamblingHorrorTimer = 20000;
                m_uiSummonDrudgeGhoulsTimer = 30000;
                m_uiInfestTimer = 30000;
                m_uiNecroticPlagueTimer = !bCast ? 30000 : 30000000;
                m_uiTirionSpawnTimer = 5000;
                m_uiIcePulsSummonTimer = 10000;
                m_uiPainandSufferingTimer = 10000;
                m_uiSummonSpiritTimer = 25000;
                m_uiSummonValkyrTimer = 5000;
                m_uiSoulReaperTimer = 30000;
                m_uiDefileTimer = 25000;
                m_uiInfestTimer = 40000;
                m_uiSummonVileSpiritTimer = 30000;
                m_uiHarvestSoulTimer = 70000;
                m_uiSummonShadowTrap = 20000;
                m_uiEndingTimer = 1000;
                m_uiEndingPhase = 1;

                TriggerSpawned = false;
                bEnding = false;
                bCast = false;

                if(!pInstance)
                    return;

                pInstance->SetData(DATA_LICH_KING_EVENT, NOT_STARTED);
                pInstance->SetData(DATA_BEEN_WAITING, DONE);
                pInstance->SetData(DATA_NECK_DEEP, DONE);

                summons.DespawnAll();

                me->SetSpeed(MOVE_RUN, 1.8f);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED);

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                    me->GetMotionMaster()->MovementExpired();

                if(SpellEntry* spellRevive = GET_SPELL(SPELL_SUMMON_DEFILE))
                {
                    spellRevive->DurationIndex = 3;
                }
                if(SpellEntry* lock = GET_SPELL(SPELL_ICEBLOCK_TRIGGER))
                {
                    lock->Targets = 6; //target chain damage
                }
                if(SpellEntry* reaper = GET_SPELL(SPELL_SOUL_REAPER_HASTE_AURA))
                {
                    reaper->Targets = 1;
                }
            }

            void EnterCombat(Unit* /*pWho*/)
            {
                DoScriptText(SAY_AGGRO, me);

                if(pInstance)
                    pInstance->SetData(DATA_LICH_KING_EVENT, IN_PROGRESS);
            }

            void JustDied(Unit* /*pKiller*/)
            {
                if(!pInstance)
                    return;

                DoScriptText(SAY_DEATH_KING, me);
                pInstance->SetData(DATA_LICH_KING_EVENT, DONE);
                if(pInstance->GetData(DATA_BEEN_WAITING) == DONE)
                    pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_BEEN_WAITING_A_LONG_TIME_FOR_THIS_10,ACHIEV_BEEN_WAITING_A_LONG_TIME_FOR_THIS_25));
                if(pInstance->GetData(DATA_NECK_DEEP) == FAIL)
                    pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_NECK_DEEP_IN_VILE_10,ACHIEV_NECK_DEEP_IN_VILE_25));

                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_INFEST);

                summons.DespawnAll();

                PlayerCinematic();
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if(type != POINT_MOTION_TYPE)
                    return;

                if(id == POINT_PLATFORM_CENTRE)
                {
                    DoScriptText(SAY_REMORSELESS_WINTER, me);
                    DoCast(me, SPELL_REMORSELES_WINTER);
                    me->GetMotionMaster()->MovementExpired();
                }
            }

            void PlayerCinematic()
            {
                Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

                if (PlList.isEmpty())
                    return;

                for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                {
                    if (Player* pPlayer = i->getSource())
                    {
                        pPlayer->SendMovieStart(16);
                    }
                }
            }

            void JustReachedHome()
            {
                if(!pInstance)
                    return;

                pInstance->SetData(DATA_LICH_KING_EVENT, FAIL);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_INFEST);

                summons.DespawnAll();
            }

            void KilledUnit(Unit* victim)
            {
                if(!bEnding)
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
            }

            void JustSummoned(Creature* summoned)
            {
                if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                    summoned->AI()->AttackStart(pTarget);

                summons.Summon(summoned);

                switch(summoned->GetEntry())
                {
                    case CREATURE_ICE_SPHERE:
                        summoned->CastSpell(summoned, SPELL_ICE_BURST_DISTANCE_CHECK, true);
                        summoned->CastSpell(summoned, SPELL_ICE_PULSE, true);
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                        {
                            summoned->AI()->AttackStart(pTarget);
                            summoned->GetMotionMaster()->MoveChase(pTarget);
                        }
                        break;
                    case CREATURE_DEFILE:
                        summoned->CastSpell(summoned, SPELL_DEFILE, true);
                        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        break;
                    case CREATURE_RAGING_SPIRIT:
                        summoned->CastSpell(summoned->getVictim(), SPELL_RAGING_VISUAL, true);
                        break;
                    case CREATURE_VILE_SPIRIT:
                        summoned->CastSpell(summoned, SPELL_VILE_SPIRIT_DISTANCE_CHECK, true);
                        break;
                    case CREATURE_TRIGGER:
                        summoned->AI()->AttackStart(me);
                        summoned->SetDisplayId(MODEL_INVISIBLE);
                        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        break;

                }
            }

            void Phasenswitch()
            {
                me->SetReactState(REACT_PASSIVE);
                me->AttackStop();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                SetCombatMovement(false);
                me->GetMotionMaster()->MovePoint(POINT_PLATFORM_CENTRE, MovePos[1]);
            }

            void NextPhase() //caled after cast winter
            {
                m_uiPhase = m_uiPhase == 2 ? 3 : 5;
                me->SetReactState(REACT_AGGRESSIVE);
                SetCombatMovement(true);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                switch(m_uiPhase)
                {
                case 1:
                    if(HealthAbovePct(71))
                        return;
                        m_uiPhase = 2;
                        Phasenswitch();
                    break;
                case 3:
                    if(HealthAbovePct(41))
                        return;
                        m_uiPhase = 4;
                        Phasenswitch();
                    break;
                case 4:
                    if(HealthAbovePct(11) || bEnding)
                        return;
                        bEnding = true;
                    break;
                }

                if(!HealthAbovePct(12) && !TriggerSpawned)
                {
                    me->SummonCreature(CREATURE_TRIGGER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 360000);
                    TriggerSpawned = true;
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!pInstance || pInstance->GetData(DATA_LICH_KING_EVENT) != IN_PROGRESS)
                    return;

                if(!bEnding)
                {
                    if (m_uiRandomSpeechTimer < uiDiff)
                    {
                        DoScriptText(RAND(SAY_RANDOM_1,SAY_RANDOM_2), me);
                        m_uiRandomSpeechTimer = 33000;
                    } else m_uiRandomSpeechTimer -= uiDiff;

                    if (m_uiBerserkTimer < uiDiff)
                    {
                        DoScriptText(SAY_BERSERK, me);
                        DoCast(me, SPELL_BERSERK);
                        m_uiBerserkTimer = 900000;
                    } else m_uiBerserkTimer -= uiDiff;
                }

                if(m_uiPhase == 1)
                {
                    if (IsHeroic())
                    {
                        if (m_uiSummonShadowTrap < uiDiff)
                        {
                            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                                DoCast(pTarget, SPELL_SUMMON_SHADOW_TRAP, true);
                            m_uiSummonShadowTrap = 30000;
                        } else m_uiSummonShadowTrap -= uiDiff;
                    }

                    if (m_uiInfestTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_INFEST);
                        m_uiInfestTimer = 30000;
                    } else m_uiInfestTimer -= uiDiff;

                    if (m_uiSummonDrudgeGhoulsTimer < uiDiff)
                    {
                        DoCast(SPELL_SUMMON_DRUDGE_GHOULS);
                        m_uiSummonDrudgeGhoulsTimer = 20000;
                    } else m_uiSummonDrudgeGhoulsTimer -= uiDiff;

                    if (m_uiSummonShamblingHorrorTimer < uiDiff)
                    {
                        DoCast(SPELL_SUMMON_SHAMBLING_HORROR);
                        m_uiSummonShamblingHorrorTimer = 30000;
                    } else m_uiSummonShamblingHorrorTimer -= uiDiff;

                    if (m_uiNecroticPlagueTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_NECROTIC_PLAGUE);
                        m_uiNecroticPlagueTimer = !bCast ? 30000 : 30000000;
                    } else m_uiNecroticPlagueTimer -= uiDiff;
                }

                if(m_uiPhase == 2) //transition phase 1
                {
                    if (m_uiSummonSpiritTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_SUMMON_RAGING_SPIRIT);
                        m_uiSummonSpiritTimer = 20000;
                    } else m_uiSummonSpiritTimer -= uiDiff;

                    if (m_uiIcePulsSummonTimer < uiDiff)
                    {
                        DoCast(SPELL_SUMMON_ICE_SPEHERE);
                        m_uiIcePulsSummonTimer = 15000;
                    } else m_uiIcePulsSummonTimer -= uiDiff;

                    if (m_uiPainandSufferingTimer < uiDiff)
                    {
                        DoCast(SPELL_PAIN_AND_SUFFERING);
                        m_uiPainandSufferingTimer = 2000;
                    } else m_uiPainandSufferingTimer -= uiDiff;
                }

                if(m_uiPhase == 3)
                {
                    if (m_uiDefileTimer < uiDiff)
                    {
                        DoScriptText(SAY_EMOTE_DEFILE, me);
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(pTarget, SPELL_SUMMON_DEFILE);
                        m_uiDefileTimer = 20000;
                    } else m_uiDefileTimer -= uiDiff;

                    if (m_uiSummonValkyrTimer < uiDiff)
                    {
                        DoScriptText(SAY_SUMMON_VALKYR, me);
                        DoCast(SPELL_SUMMON_VALKYR);
                        m_uiSummonValkyrTimer = 35000;
                        m_uiDefileTimer = 5000; //cast defile after cast valkyr summon
                    } else m_uiSummonValkyrTimer -= uiDiff;

                    if (m_uiSoulReaperTimer < uiDiff)
                    {
                        DoCastVictim(SPELL_SOUL_REAPER);
                        DoCast(SPELL_SOUL_REAPER_HASTE_AURA);
                        m_uiSoulReaperTimer = 30000;
                    } else m_uiSoulReaperTimer -= uiDiff;

                    if (m_uiInfestTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_INFEST);
                        m_uiInfestTimer = 30000;
                    } else m_uiInfestTimer -= uiDiff;
                }

                if(m_uiPhase == 4) //transition phase 2
                {
                    if (m_uiSummonSpiritTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_SUMMON_RAGING_SPIRIT);
                        m_uiSummonSpiritTimer = 25000;
                    } else m_uiSummonSpiritTimer -= uiDiff;

                    if (m_uiIcePulsSummonTimer < uiDiff)
                    {
                        DoCast(SPELL_SUMMON_ICE_SPEHERE);
                        m_uiIcePulsSummonTimer = 15000;
                    } else m_uiIcePulsSummonTimer -= uiDiff;

                    if (m_uiPainandSufferingTimer < uiDiff)
                    {
                        DoCast(SPELL_PAIN_AND_SUFFERING);
                        m_uiPainandSufferingTimer = 3000;
                    } else m_uiPainandSufferingTimer -= uiDiff;
                }

                if(m_uiPhase == 5)
                {
                    if (m_uiSummonVileSpiritTimer < uiDiff)
                    {
                        DoCast(SPELL_SUMMON_VILE_SPIRIT);
                        m_uiSummonVileSpiritTimer = 30000;
                    } else m_uiSummonVileSpiritTimer -= uiDiff;

                    if (m_uiHarvestSoulTimer < uiDiff)
                    {
                        DoScriptText(SAY_HARVEST_SOUL, me);
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                            DoCast(pTarget, SPELL_HARVEST_SOULS);
                        m_uiHarvestSoulTimer = 70000;
                    } else m_uiHarvestSoulTimer -= uiDiff;

                    if (m_uiSoulReaperTimer < uiDiff)
                    {
                        DoCastVictim(SPELL_SOUL_REAPER);
                        DoCast(me, SPELL_SOUL_REAPER_HASTE_AURA);
                        m_uiSoulReaperTimer = 30000;
                    } else m_uiSoulReaperTimer -= uiDiff;

                    if (m_uiDefileTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            DoCast(pTarget, SPELL_SUMMON_DEFILE);
                        m_uiDefileTimer = 20000;
                    } else m_uiDefileTimer -= uiDiff;
                }

                DoMeleeAttackIfReady();

                if(!bEnding)
                    return;

                if (m_uiEndingTimer <= uiDiff)
                {
                    switch(m_uiEndingPhase)
                    {
                        case 1:
                            me->GetMotionMaster()->MoveIdle();
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->CastStop();
                            DoResetThreat();
                            DoScriptText(SAY_10_PROZENT, me);
                            DoCast(SPELL_FURY_OF_FROSTMOURNE);
                            m_uiEndingTimer = 15000;
                            ++m_uiEndingPhase;
                            break;
                        case 2:
                            DoScriptText(SAY_ENDING_1_KING, me);
                            m_uiEndingTimer = 24000;
                            ++m_uiEndingPhase;
                            break;
                        case 3:
                            DoScriptText(SAY_ENDING_2_KING, me);
                            m_uiEndingTimer = 25000;
                            ++m_uiEndingPhase;
                            break;
                        case 4:
                            me->GetMotionMaster()->MovePoint(0, MovePos[1]);
                            m_uiEndingTimer = 4000;
                            ++m_uiEndingPhase;
                            break;
                        case 5:
                            DoCast(me, SPELL_CHANNEL_KING);
                            DoScriptText(SAY_ENDING_3_KING, me);
                            m_uiEndingTimer = 26000;
                            ++m_uiEndingPhase;
                            break;
                        case 6:
                            DoScriptText(SAY_ENDING_4_KING, me);
                            m_uiEndingTimer = 9000;
                            ++m_uiEndingPhase;
                            break;
                        case 7:
                            DoScriptText(SAY_ENDING_5_TIRION, pTirion);
                            m_uiEndingTimer = 9000;
                            ++m_uiEndingPhase;
                            break;
                        case 8:
                            DoCast(pTirion, SPELL_TIRION_LIGHT);
                            m_uiEndingTimer = 5000;
                            ++m_uiEndingPhase;
                            break;
                        case 9:
                            pTirion->RemoveAurasDueToSpell(SPELL_ICEBLOCK_TRIGGER);
                            m_uiEndingTimer = 2000;
                            ++m_uiEndingPhase;
                            break;
                        case 10:
                            pTirion->GetMotionMaster()->MovePoint(0, MovePos[2]);
                            m_uiEndingTimer = 1000;
                            ++m_uiEndingPhase;
                            break;
                        case 11:
                            pTirion->GetMotionMaster()->MoveJump(517.482910f, -2124.905762f, 1040.861328f, 10.0f, 15.0f); //pTirion->JumpTo(pFrostmourne, 15.0f);
                            pTirion->SetUInt32Value(UNIT_NPC_EMOTESTATE, 375);
                            m_uiEndingTimer = 1000;
                            ++m_uiEndingPhase;
                            break;
                        case 12:
                            me->RemoveAura(SPELL_CHANNEL_KING);
                            me->CastSpell(me, SPELL_BOOM_VISUAL, false);
                            m_uiEndingTimer = 300;
                            ++m_uiEndingPhase;
                            break;
                        case 13:
                            me->CastSpell(me, SPELL_SUMMON_BROKEN_FROSTMOURNE, false);
                            m_uiEndingTimer = 3000;
                            ++m_uiEndingPhase;
                            break;
                        case 14:
                            me->CastSpell(me, 73017, false);
                            m_uiEndingTimer = 1000;
                            ++m_uiEndingPhase;
                            break;
                        case 15:
                            DoScriptText(SAY_ENDING_6_KING, me);
                            m_uiEndingTimer = 3000;
                            ++m_uiEndingPhase;
                            break;
                        case 16:
                            pFrostmourne = me->SummonCreature(27880, me->GetPositionX()+2, me->GetPositionY()+2, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 99999999);
                            pFrostmourne->CastSpell(pFrostmourne, SPELL_BROKEN_FROSTMOURNE, false);
                            pFrostmourne->CastSpell(pFrostmourne, SPELL_FROSTMOURNE_TRIGGER, false);
                            pFrostmourne->GetMotionMaster()->MoveChase(me);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED);
                            //pTirion->CastSpell(pTirion, SPELL_DISENGAGE, false);
                            m_uiEndingTimer = 2000;
                            ++m_uiEndingPhase;
                            break;
                        case 17:
                            me->RemoveAllAuras();
                            me->RemoveAura(SPELL_SUMMON_BROKEN_FROSTMOURNE);
                            DoPlaySoundToSet(me, SOUND_ENDING_7_KING);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 473);
                            m_uiEndingTimer = 5000;
                            ++m_uiEndingPhase;
                            break;
                        case 18:
                            DoScriptText(SAY_ENDING_8_TIRION, pTirion);
                            m_uiEndingTimer = 6000;
                            ++m_uiEndingPhase;
                            break;
                        case 19:
                            pFather = me->SummonCreature(CREAUTRE_MENETHIL, me->GetPositionX()+5, me->GetPositionY()+5, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 9999999);
                            DoScriptText(SAY_ENDING_9_FATHER, pFather);
                            pFather->CastSpell(pFather, SPELL_REVIVE, true);
                            m_uiEndingTimer = 3000;
                            ++m_uiEndingPhase;
                            break;
                        case 20:
                            DoScriptText(SAY_ENDING_11_FATHER, pFather);
                            //pFather->CastSpell(pFather, SPELL_REVIVE_VISUAL, false);
                            m_uiEndingTimer = 6000;
                            ++m_uiEndingPhase;
                            break;
                        case 21:
                            DoScriptText(SAY_ENDING_10_TIRION, pTirion);
                            m_uiEndingTimer = 5000;
                            ++m_uiEndingPhase;
                            break;
                        case 22:
                            DoScriptText(SAY_ENDING_12_KING, me);
                            pTirion->SetReactState(REACT_AGGRESSIVE);
                            pTirion->AI()->AttackStart(me);
                            pFather->AI()->AttackStart(me);
                            m_uiEndingTimer = 5000;
                            ++m_uiEndingPhase;
                            break;
                    }
                } else m_uiEndingTimer -= uiDiff;
            }
        private:
            InstanceScript* pInstance;

            uint8 m_uiEndingPhase;
            uint8 m_uiPhase;

            uint32 m_uiEndingTimer;
            uint32 m_uiTirionSpawnTimer;
            uint32 m_uiSummonShamblingHorrorTimer;
            uint32 m_uiSummonDrudgeGhoulsTimer;
            uint32 m_uiSummonShadowTrap;
            uint32 m_uiInfestTimer;
            uint32 m_uiNecroticPlagueTimer;
            uint32 m_uiBerserkTimer;
            uint32 m_uiSummonValkyrTimer;
            uint32 m_uiSoulReaperTimer;
            uint32 m_uiDefileTimer;
            uint32 m_uiHarvestSoulTimer;
            uint32 m_uiSummonVileSpiritTimer;
            uint32 m_uiPainandSufferingTimer;
            uint32 m_uiIcePulsSummonTimer;
            uint32 m_uiSummonSpiritTimer;
            uint32 m_uiRandomSpeechTimer;

            bool TriggerSpawned;
            bool bEnding;
            bool bCast;

            SummonList summons;

        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_the_lich_kingAI(pCreature);
        }
};

class npc_tirion_icc : public CreatureScript
{
    public:
        npc_tirion_icc() : CreatureScript("npc_tirion_icc") { }

        struct npc_tirion_iccAI : public ScriptedAI
        {
            npc_tirion_iccAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                pTirion = me;
            }

            void Reset()
            {
                m_uiIntroTimer = 1000;
                m_uiIntroPhase = 1;

                bIntro = false;

                me->SetReactState(REACT_PASSIVE);
                me->SetSpeed(MOVE_RUN, 1.8f);
            }

            void StartEvent()
            {
                bIntro = true;
            }

            void UpdateAI(const uint32 diff)
            {
                if(!pInstance)
                    return;

                if(pInstance->GetData(DATA_LICH_KING_EVENT) != NOT_STARTED)
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                else
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                 if(!bIntro)
                     return;

                if(m_uiIntroTimer <= diff)
                {
                    switch(m_uiIntroPhase)
                    {
                    case 1:
                        {
                            pLichKing->SetStandState(UNIT_STAND_STATE_STAND);
                            pLichKing->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                            pLichKing->SetSpeed(MOVE_WALK, 1.2f);
                            pLichKing->GetMotionMaster()->MovePoint(0, MovePos[0]);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 375);
                            m_uiIntroTimer = 3000;
                            ++m_uiIntroPhase;
                        }
                    break;
                    case 2:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 1);
                        DoScriptText(SAY_INTRO_1_KING, pLichKing);
                        m_uiIntroTimer = 14000;
                        ++m_uiIntroPhase;
                        break;
                    case 3:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        DoScriptText(SAY_INTRO_2_TIRION, me);
                        m_uiIntroTimer = 9000;
                        ++m_uiIntroPhase;
                        break;
                    case 4:
                        DoScriptText(SAY_INTRO_3_KING, pLichKing);
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 392);
                        m_uiIntroTimer = 3000;
                        ++m_uiIntroPhase;
                        break;
                    case 5:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 397);
                        m_uiIntroTimer = 2000;
                        ++m_uiIntroPhase;
                        break;
                    case 6:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        m_uiIntroTimer = 18000;
                        ++m_uiIntroPhase;
                        break;
                    case 7:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 397);
                        DoScriptText(SAY_INTRO_4_TIRION, me);
                        m_uiIntroTimer = 1000;
                        ++m_uiIntroPhase;
                        break;
                    case 8:
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        me->GetMotionMaster()->MovePoint(0, MovePos[3]);
                        m_uiIntroTimer = 2000;
                        ++m_uiIntroPhase;
                        break;
                    case 9:
                        pLichKing->CastSpell(pTirion, SPELL_ICEBLOCK_TRIGGER, true);
                        m_uiIntroTimer = 2000;
                        ++m_uiIntroPhase;
                        break;
                    case 10:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 1);
                        DoScriptText(SAY_INTRO_5_KING, pLichKing);
                        m_uiIntroTimer = 12000;
                        ++m_uiIntroPhase;
                        break;
                    case 11:
                        pLichKing->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        pLichKing->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pLichKing->SetReactState(REACT_AGGRESSIVE);
                        if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                            me->AI()->AttackStart(pTarget);
                        m_uiIntroTimer = 6000;
                        ++m_uiIntroPhase;
                        break;
                    }
                } else m_uiIntroTimer -= diff;
            }
        private:
            InstanceScript* pInstance;

            uint32 m_uiIntroTimer;
            uint8 m_uiIntroPhase;

            bool bIntro;
        };

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT, GOSSIP_SENDER_MAIN, 999999);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            if (uiAction == 999999)
            {
                CAST_AI(npc_tirion_icc::npc_tirion_iccAI, pCreature->AI())->StartEvent();
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            return true;
        }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_tirion_iccAI(pCreature);
        }
};

class npc_valkyr_icc : public CreatureScript
{
    public:
        npc_valkyr_icc() : CreatureScript("npc_valkyr_icc") { }

        struct npc_valkyr_iccAI : public ScriptedAI
        {
            npc_valkyr_iccAI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(pCreature->GetVehicleKit())
            {
                assert(vehicle);
            }

            void Reset()
            {
                me->SetFlying(true);
                m_uiGrabTimer = 2000;
                me->GetVehicleKit();
                CanCast = false;
                inVehicle = false;
                DoCast(me, SPELL_WINGS_OF_THE_DAMNED);
                m_uiLifeSiphonTimer = 3000;

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                    me->GetMotionMaster()->MovementExpired();
            }

            void DamageTaken(Unit* /*done_by*/, uint32& /*damage*/)
            {
                if(!HealthAbovePct(50) && IsHeroic() && !CanCast)
                {
                    vehicle->RemoveAllPassengers();
                    me->GetMotionMaster()->MovePoint(POINT_VALKYR_ZET, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10);
                }
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if(type != POINT_MOTION_TYPE)
                    return;

                if(CanCast)
                    return;

                switch(id)
                {
                    case POINT_PLATFORM_END:
                        vehicle->RemoveAllPassengers();
                        float x,y,z;
                        me->GetNearPoint2D(x, y, 50, me->GetAngle(me));
                        me->GetMotionMaster()->MovePoint(POINT_VALKYR_END,x,y,z+15);
                        break;
                    case POINT_VALKYR_END:
                        me->ForcedDespawn();
                        break;
                    case POINT_VALKYR_ZET:
                        CanCast = true;
                        break;
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (!inVehicle && m_uiGrabTimer < uiDiff)
                {
                    if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                    {
                        pTarget->EnterVehicle(vehicle);
                        me->GetMotionMaster()->MovePoint(POINT_PLATFORM_END, MovePos[4]);
                        inVehicle = true;
                    }
                    m_uiGrabTimer = 20000;
                } else m_uiGrabTimer -= uiDiff;

                if (CanCast && m_uiLifeSiphonTimer < uiDiff)
                {
                    DoCastVictim(SPELL_LIFE_SIPHON);
                    m_uiLifeSiphonTimer = 3000;
                } else m_uiLifeSiphonTimer -= uiDiff;
            }
        private:
            uint32 m_uiGrabTimer;
            uint32 m_uiLifeSiphonTimer;
            bool CanCast;
            bool inVehicle;

            Vehicle* vehicle;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_valkyr_iccAI(pCreature);
        }
};

class npc_vile_spirit_icc : public CreatureScript
{
    public:
        npc_vile_spirit_icc() : CreatureScript("npc_vile_spirit_icc") { }

        struct npc_vile_spirit_iccAI : public ScriptedAI
        {
            npc_vile_spirit_iccAI(Creature* pCreature) : ScriptedAI(pCreature) { }

            void Reset()
            {
                m_uiMoveTimer = 15000;
                bStartMove = false;
                DoStartNoMovement(me->getVictim());
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!bStartMove && m_uiMoveTimer < uiDiff)
                {
                    DoStartMovement(me->getVictim());
                    DoCast(me, SPELL_VILE_SPIRIT_ACTIVE);
                    bStartMove = true;
                    if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true))
                        me->AddThreat(pTarget, 100000.0f);
                    m_uiMoveTimer = 15000;
                } else m_uiMoveTimer -= uiDiff;
            }
        private:
            bool bStartMove;
            uint32 m_uiMoveTimer;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_vile_spirit_iccAI(pCreature);
        }
};

class spell_lich_king_necrotic_plague : public SpellScriptLoader
{
    public:
        spell_lich_king_necrotic_plague() : SpellScriptLoader("spell_lich_king_necrotic_plague") { } //70338


        class spell_lich_king_necrotic_plague_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lich_king_necrotic_plague_AuraScript)

            void OnApply(AuraEffect const* aurEff, AuraApplication const* aurApp)
            {
                if (InstanceScript* instance = aurApp->GetBase()->GetCaster()->GetInstanceScript())
                {
                    aurApp->GetBase()->SetStackAmount(aurApp->GetBase()->GetStackAmount() + instance->GetData(DATA_NECROTIC_STACK));
                    instance->SetData(DATA_NECROTIC_STACK, instance->GetData(DATA_NECROTIC_STACK) + 1);
                    if(aurApp->GetBase()->GetStackAmount() >= 30)
                        instance->SetData(DATA_BEEN_WAITING, FAIL);
                }
            }
            void OnRemove(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                //70337 вешает обычную чуму.В базе делаем запись, что бы при спаде 70337 кастовалась 70338 и иммунитет
                //Для 70338 в базе также делаем каст при спадет.Кастовать будет тот-же 70338
                //В Скрипте остается сделать увеличение стака и реализацию ачивки
                CAST_AI(boss_the_lich_king::boss_the_lich_kingAI, CAST_CRE(aurApp->GetBase()->GetCaster())->AI())->DoCast(SPELL_PLAGUE_SIPHON);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_lich_king_necrotic_plague_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
                OnEffectApply += AuraEffectApplyFn(spell_lich_king_necrotic_plague_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lich_king_necrotic_plague_AuraScript();
        }
};

class spell_lich_king_infection : public SpellScriptLoader
{
    public:
        spell_lich_king_infection() : SpellScriptLoader("spell_lich_king_infection") { } //70541


        class spell_lich_king_infection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lich_king_infection_AuraScript)

            void OnPeriodic(AuraEffect const* aurEff, AuraApplication const* aurApp)
            {
                PreventDefaultAction();
                if(!aurApp->GetTarget()->isAlive() || aurApp->GetTarget()->GetHealthPct() < 90)
                    return;

                aurApp->GetTarget()->RemoveAurasDueToSpell(SPELL_INFEST);

                if(aurApp->GetBase()->GetCaster()->GetMapId() != 631) //Remove infection if player without ICC
                    aurApp->GetTarget()->RemoveAurasDueToSpell(SPELL_INFEST);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lich_king_infection_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lich_king_infection_AuraScript();
        }
};

class spell_lich_king_valkyr_summon : public SpellScriptLoader
{
    public:
        spell_lich_king_valkyr_summon() : SpellScriptLoader("spell_lich_king_valkyr_summon") { } //74361


        class spell_lich_king_valkyr_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lich_king_valkyr_summon_AuraScript);

            void OnApply(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = aurApp->GetBase()->GetCaster())
                {
                    uint8 spawnMod = caster->GetMap()->GetSpawnMode();
                    aurApp->GetBase()->SetDuration(spawnMod == 1 || spawnMod == 3 ? 3000 : 1000);
                }
            }

            void HandleTriggerSpell(AuraEffect const* aurEff, AuraApplication const* aurApp)
            {
                PreventDefaultAction();
                if (Unit* caster = aurApp->GetBase()->GetCaster())
                {
                    uint32 triggerSpellId = GetSpellProto()->EffectTriggerSpell[aurEff->GetEffIndex()];
                    float x, y, z;
                    caster->GetPosition(x, y, z);
                    caster->CastSpell(x, y, z + 6, triggerSpellId, true, NULL, NULL, GetCasterGUID(), caster);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lich_king_valkyr_summon_AuraScript::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
                OnEffectApply += AuraEffectApplyFn(spell_lich_king_valkyr_summon_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lich_king_valkyr_summon_AuraScript();
        }
};

class spell_lich_king_winter : public SpellScriptLoader
{
    public:
        spell_lich_king_winter() : SpellScriptLoader("spell_lich_king_winter") { } //68981


        class spell_lich_king_winter_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lich_king_winter_AuraScript)

            void OnPereodic(AuraEffect const* /*aurEff*/, AuraApplication const* aurApp)
            {
                PreventDefaultAction();
                if(!aurApp)
                    return;

                aurApp->GetBase()->GetCaster()->CastSpell(aurApp->GetBase()->GetCaster(), SPELL_REMORSELES_WINTER_DAMAGE, true);

                if (InstanceScript* instance = aurApp->GetTarget()->GetInstanceScript())
                    if (GameObject* floor = GameObject::GetGameObject(*aurApp->GetTarget(), instance->GetData64(DATA_PLATFORM)))
                        if(floor->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED))
                            floor->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED);
            }

            void OnRemove(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = aurApp->GetBase()->GetCaster())
                {
                    caster->CastSpell(caster, SPELL_QUAKE, true);
                    DoScriptText(SAY_BROKEN_ARENA, caster);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_lich_king_winter_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_lich_king_winter_AuraScript::OnPereodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lich_king_winter_AuraScript();
        }
};

class spell_lich_king_quake : public SpellScriptLoader
{
    public:
        spell_lich_king_quake() : SpellScriptLoader("spell_lich_king_quake") { } //72262


        class spell_lich_king_quake_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_lich_king_quake_AuraScript)

            void OnRemove(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes /*mode*/)
            {
                if(!aurApp->GetBase()->GetCaster() || !aurApp->GetBase()->GetOwner())
                    return;

                if (InstanceScript* instance = aurApp->GetTarget()->GetInstanceScript())
                {
                    if (GameObject* floor = GameObject::GetGameObject((*aurApp->GetBase()->GetOwner()), instance->GetData64(DATA_PLATFORM)))
                    {
                        floor->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_DAMAGED);
                        CAST_AI(boss_the_lich_king::boss_the_lich_kingAI, pLichKing->AI())->NextPhase();
                        //CAST_AI(boss_the_lich_king::boss_the_lich_kingAI, CAST_CRE(aurApp->GetBase()->GetCaster())->AI())->DoCast(SPELL_PLAGUE_SIPHON);
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_lich_king_quake_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_lich_king_quake_AuraScript();
        }
};

class spell_vile_spirit_distance_check : public SpellScriptLoader
{
    public:
        spell_vile_spirit_distance_check() : SpellScriptLoader("spell_vile_spirit_distance_check") { }


        class spell_vile_spirit_distance_check_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_vile_spirit_distance_check_SpellScript);


            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive()))
                    return;

                if(Unit* caster = GetCaster())
                {
                    caster->CastSpell(caster, SPELL_BURST, true);

                    if (InstanceScript* instance = caster->GetInstanceScript())
                        instance->SetData(DATA_NECK_DEEP, FAIL);
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_vile_spirit_distance_check_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_vile_spirit_distance_check_SpellScript();
        }
};

class spell_ice_burst_distance_check : public SpellScriptLoader
{
    public:
        spell_ice_burst_distance_check() : SpellScriptLoader("spell_ice_burst_distance_check") { }


        class spell_ice_burst_distance_check_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ice_burst_distance_check_SpellScript);


            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!(GetHitUnit() && GetHitUnit()->isAlive()))
                    return;

                if(Unit* caster = GetCaster())
                    caster->CastSpell(caster, SPELL_ICE_BURST, true);
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_ice_burst_distance_check_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ice_burst_distance_check_SpellScript();
        }
};

void AddSC_boss_lichking()
{
    new boss_the_lich_king();
    new npc_tirion_icc();
    new npc_valkyr_icc();
    new npc_vile_spirit_icc();
    new spell_lich_king_necrotic_plague();
    new spell_lich_king_infection();
    new spell_lich_king_valkyr_summon();
    new spell_lich_king_winter();
    new spell_vile_spirit_distance_check();
    new spell_ice_burst_distance_check();
    new spell_lich_king_quake();
}