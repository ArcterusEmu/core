/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "icecrown_citadel.h"
#include "Spell.h"

enum Spells
{
    SPELL_ON_ORGRIMS_HAMMER_DECK   = 70121, //maybe for gunship battle
    SPELL_DARKMARTYRDOM_FANATIC     = 71236,
    SPELL_DARKMARTYRDOM_ADHERENT    = 70903,
    SPELL_DARKTRANSFORMATION        = 70900,
    SPELL_NECROTICSTRIKE            = 70659,
    SPELL_SHADOWCLEAVE              = 70670,
    SPELL_VAMPIRICMIGHT             = 70674,
    SPELL_FANATIC_DETERMINATION     = 71235,
    SPELL_ADHERENT_DETERMINATION    = 71234,
    SPELL_EMPOWEREMENT              = 70901,
    SPELL_FROST_FEVER               = 67767,
    SPELL_DEATHCHILL_BLAST          = 70906,
    SPELL_DEATHCHILL_BOLT           = 70594,
    SPELL_CURSE_OF_TORPOR           = 71237,
    SPELL_SHORUD_OF_THE_OCCULT      = 70768,
    SPELL_DARK_TRANSFORMATION_T     = 70895,
    SPELL_DARK_EMPOWERMENT_T        = 70896,
    SPELL_STANDART_HORDE            = 69811
};

enum TeleportSpells
{
    HAMMER        = 70781,
    ORATORY       = 70856,
    RAMPART       = 70857,
    SAURFANG      = 70858,
    UPPER_SPIRE   = 70859,
    PLAGUEWORKS   = 9995,
    CRIMSONHALL   = 9996,
    FWHALLS       = 9997,
    QUEEN         = 70861,
    LICHKING      = 70860
};

class npc_cult_fanatic_and_adherent : public CreatureScript
{
    public:
        npc_cult_fanatic_and_adherent() : CreatureScript("npc_cult_fanatic_and_adherent") { }

        struct npc_cult_fanatic_and_adherentAI : public ScriptedAI
        {
            npc_cult_fanatic_and_adherentAI(Creature *pCreature) : ScriptedAI(pCreature) { }

            void Reset()
            {
                m_uiStrikeTimer = urand(8000, 11000);
                m_uiVampirTimer = urand(19000, 22000);
                m_uiCleaveTimer = urand(7000, 9000);
                m_uiMartyrdomTimer = urand(24000, 30000);
                m_uiFrostFeverTimer = urand(9000, 11000);
                m_uiDeathchillTimer = urand(10000, 12000);
                m_uiCurseTimer = urand(8000, 10000);
                m_uiOccultTimer = urand(25000, 29000);

                bEmpowerement = false;

                if(me->GetEntry() == CREATURE_REANIMATED_ADHERENT)
                    DoCast(me, SPELL_ADHERENT_DETERMINATION);
                if(me->GetEntry() == CREATURE_REANIMATED_FANATIC)
                    DoCast(me, SPELL_FANATIC_DETERMINATION);
            }

            void JustDied(Unit* /*who*/) { }

            void SpellHit(Unit* /*caster*/, const SpellEntry * spell)
            {
                if(me->GetEntry() == CREATURE_ADHERENT)
                {
                    if (spell->Id == SPELL_EMPOWEREMENT)
                        me->UpdateEntry(CREATURE_EMPOWERED_ADHERENT);
                    else if (spell->Id == SPELL_DARK_EMPOWERMENT_T)
                    {
                        DoCast(me, SPELL_EMPOWEREMENT);
                        bEmpowerement = true;
                    }
                }
                if(me->GetEntry() == CREATURE_FANATIC)
                {
                    if (spell->Id == SPELL_DARKTRANSFORMATION)
                        me->UpdateEntry(CREATURE_DEFORMED_FANATIC);
                    else if (spell->Id == SPELL_DARK_TRANSFORMATION_T)
                    {
                        DoCast(me, SPELL_DARKTRANSFORMATION);
                    }
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim() || me->hasUnitState(UNIT_STAT_CASTING))
                    return;

                if((me->GetEntry() == CREATURE_ADHERENT) || (me->GetEntry() == CREATURE_EMPOWERED_ADHERENT) || (me->GetEntry() == CREATURE_REANIMATED_ADHERENT))
                {
                    if (m_uiMartyrdomTimer <= uiDiff && !bEmpowerement)
                    {
                        DoCast(me, SPELL_DARKMARTYRDOM_ADHERENT);
                        m_uiMartyrdomTimer = urand(24000, 30000);
                    } else m_uiMartyrdomTimer -= uiDiff;

                    if (m_uiFrostFeverTimer <= uiDiff)
                    {
                        DoCast(me->getVictim(), SPELL_FROST_FEVER);
                        m_uiFrostFeverTimer = urand(9000, 11000);
                    } else m_uiFrostFeverTimer -= uiDiff;

                    if (m_uiDeathchillTimer <= uiDiff)
                    {
                        if (me->GetEntry() == CREATURE_EMPOWERED_ADHERENT)
                            DoCast(me->getVictim(), SPELL_DEATHCHILL_BLAST);
                        else
                            DoCast(me->getVictim(), SPELL_DEATHCHILL_BOLT);
                        m_uiDeathchillTimer = urand(10000, 12000);
                    } else m_uiDeathchillTimer -= uiDiff;

                    if (m_uiCurseTimer <= uiDiff)
                    {
                        if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                            DoCast(pTarget, SPELL_CURSE_OF_TORPOR);
                        m_uiCurseTimer = urand(8000, 10000);
                    } else m_uiCurseTimer -= uiDiff;

                    if (m_uiOccultTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_SHORUD_OF_THE_OCCULT);
                        m_uiOccultTimer = urand(25000, 29000);
                    } else m_uiOccultTimer -= uiDiff;
                }
                if((me->GetEntry() == CREATURE_FANATIC) || (me->GetEntry() == CREATURE_REANIMATED_FANATIC) || (me->GetEntry() == CREATURE_DEFORMED_FANATIC))
                {
                    if (m_uiMartyrdomTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_DARKMARTYRDOM_FANATIC);
                        m_uiMartyrdomTimer = urand(24000, 30000);
                    } else m_uiMartyrdomTimer -= uiDiff;

                    if (m_uiStrikeTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_NECROTICSTRIKE);
                        m_uiStrikeTimer = urand(8000, 11000);
                    } else m_uiStrikeTimer -= uiDiff;

                    if (m_uiCleaveTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_SHADOWCLEAVE);
                        m_uiCleaveTimer = urand(7000, 9000);
                    } else m_uiCleaveTimer -= uiDiff;

                    if (m_uiVampirTimer <= uiDiff)
                    {
                        DoCast(me, SPELL_VAMPIRICMIGHT);
                        m_uiVampirTimer = urand(19000, 22000);
                    } else m_uiVampirTimer -= uiDiff;
                }

                DoMeleeAttackIfReady();
            }

        private:
            uint32 m_uiStrikeTimer;
            uint32 m_uiCleaveTimer;
            uint32 m_uiVampirTimer;
            uint32 m_uiMartyrdomTimer;
            uint32 m_uiFrostFeverTimer;
            uint32 m_uiDeathchillTimer;
            uint32 m_uiCurseTimer;
            uint32 m_uiOccultTimer;

            bool bEmpowerement;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_cult_fanatic_and_adherentAI(pCreature);
        }
};

class go_icecrown_teleporter : public GameObjectScript
{
    public:
        go_icecrown_teleporter() : GameObjectScript("go_icecrown_teleporter") { }

        bool OnGossipHello(Player *pPlayer, GameObject *pGO)
        {
            InstanceScript* pInstance = pGO->GetInstanceScript();
            if(!pInstance)
                return false;

            if(pInstance->GetData(DATA_MARROWGAR_EVENT) == DONE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to Light's Hammer.", GOSSIP_SENDER_MAIN, HAMMER);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Oratory of the Damned.", GOSSIP_SENDER_MAIN, ORATORY);
            }
            if(pInstance->GetData(DATA_DEATHWHISPER_EVENT) == DONE)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Rampart of Skulls.", GOSSIP_SENDER_MAIN, RAMPART);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Deathbringer's Rise.", GOSSIP_SENDER_MAIN, SAURFANG);
            }
            if(pInstance->GetData(DATA_SAURFANG_EVENT) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Upper Spire.", GOSSIP_SENDER_MAIN, UPPER_SPIRE);
            if(pInstance->GetData(DATA_PROFESSOR_PUTRICIDE_EVENT) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Plagueworks", GOSSIP_SENDER_MAIN, PLAGUEWORKS);
            if(pInstance->GetData(DATA_BLOOD_QUEEN_LANATHEL_EVENT) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Crimson Halls", GOSSIP_SENDER_MAIN, CRIMSONHALL);
            if(pInstance->GetData(DATA_VALITHRIA_DREAMWALKER_EVENT) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Sindragosa's Lair", GOSSIP_SENDER_MAIN, QUEEN);
            if(pInstance->GetData(DATA_SINDRAGOSA_EVENT) == DONE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Frostwing Halls", GOSSIP_SENDER_MAIN, FWHALLS);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pGO->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, GameObject* /*pGO*/, uint32 uiSender, uint32 uiAction)
        {
            //pPlayer->PlayerTalkClass->ClearMenus();
            if(!pPlayer->getAttackers().empty())
                return false;

            switch(uiAction)
            {
                case HAMMER:
                    pPlayer->TeleportTo(631, -17.192f, 2211.440f, 30.1158f, 3.121f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case ORATORY:
                    pPlayer->TeleportTo(631, -503.620f, 2211.470f, 62.8235f, 3.139f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case RAMPART:
                    pPlayer->TeleportTo(631, -615.145f, 2211.470f, 199.972f, 6.268f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case SAURFANG:
                    pPlayer->TeleportTo(631, -549.131f, 2211.290f, 539.291f, 6.275f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case UPPER_SPIRE:
                    pPlayer->TeleportTo(631, 4199.407f, 2769.478f, 351.064f, 6.258f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case PLAGUEWORKS:
                    pPlayer->TeleportTo(631, 4356.988f, 2867.540f, 349.332f, 1.558f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case CRIMSONHALL:
                    pPlayer->TeleportTo(631, 4452.847f, 2769.345f, 349.348f, 6.234f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case QUEEN:
                    pPlayer->TeleportTo(631, 4357.002f, 2674.207f, 349.342f, 4.683f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
                case FWHALLS:
                    pPlayer->TeleportTo(631, 4356.580f, 2565.750f, 220.40f, 4.886f);
                    pPlayer->CLOSE_GOSSIP_MENU();
                    break;
            }

            SpellEntry const* spell = sSpellStore.LookupEntry(uiAction);
            if (!spell)
                return false;


            if (pPlayer->isInCombat())
            {
                Spell::SendCastResult(pPlayer, spell, 0, SPELL_FAILED_AFFECTING_COMBAT);
                return true;
            }

            if (uiSender == GOSSIP_SENDER_MAIN)
                pPlayer->CastSpell(pPlayer, spell, true);

            return true;
        }
};

void AddSC_icecrown_citadel()
{
    new npc_cult_fanatic_and_adherent();
    new go_icecrown_teleporter();
}
