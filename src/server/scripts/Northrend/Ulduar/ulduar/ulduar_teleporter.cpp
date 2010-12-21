#include "ScriptPCH.h"
#include "ulduar.h"

enum Locations
{
    BASE_CAMP                                   = 200,
    GROUNDS                                     = 201,
    FORGE                                       = 202,
    SCRAPYARD                                   = 203,
    ANTECHAMBER                                 = 204,
    WALKWAY                                     = 205,
    CONSERVATORY                                = 206,
    SPARK_IMAGINATION                           = 207,
    DESCENT_MADNESS                             = 208
};

class ulduar_teleporter : public GameObjectScript
{
public:
    ulduar_teleporter() : GameObjectScript("ulduar_teleporter") { }

	bool OnGossipHello( Player *pPlayer, GameObject *pGO )
	{
//		InstanceScript *pInstance = pPlayer->GetInstanceScript();
		InstanceScript *pInstance = pGO->GetInstanceScript();
		if(!pInstance) 
			return false;

		pPlayer->ADD_GOSSIP_ITEM(0, "Expedition Base Camp", GOSSIP_SENDER_MAIN, BASE_CAMP);
		//pPlayer->ADD_GOSSIP_ITEM(0, "Formation Grounds", GOSSIP_SENDER_MAIN, GROUNDS);
		if (pInstance->GetBossState(BOSS_LEVIATHAN) == DONE || pPlayer->isGameMaster())
		{
			pPlayer->ADD_GOSSIP_ITEM(0, "Colossal Forge", GOSSIP_SENDER_MAIN, FORGE);
			if (pInstance->GetBossState(BOSS_XT002) == DONE || pPlayer->isGameMaster())
			{
				pPlayer->ADD_GOSSIP_ITEM(0, "Scrapyard", GOSSIP_SENDER_MAIN, SCRAPYARD);
				pPlayer->ADD_GOSSIP_ITEM(0, "Antechamber of Ulduar", GOSSIP_SENDER_MAIN, ANTECHAMBER);
				if (pInstance->GetBossState(BOSS_KOLOGARN) == DONE || pPlayer->isGameMaster())
				{
					pPlayer->ADD_GOSSIP_ITEM(0, "Shattered Walkway", GOSSIP_SENDER_MAIN, WALKWAY);
					if (pInstance->GetBossState(BOSS_AURIAYA) == DONE || pPlayer->isGameMaster())
					{
						pPlayer->ADD_GOSSIP_ITEM(0, "Conservatory of Life", GOSSIP_SENDER_MAIN, CONSERVATORY);
						if (pInstance->GetBossState(BOSS_MIMIRON) == FAIL || pInstance->GetBossState(BOSS_MIMIRON) == DONE || pPlayer->isGameMaster())
						{
							pPlayer->ADD_GOSSIP_ITEM(0, "Spark of Imagination", GOSSIP_SENDER_MAIN, SPARK_IMAGINATION);
							if (pInstance->GetBossState(BOSS_VEZAX) == DONE || pPlayer->isGameMaster())
								pPlayer->ADD_GOSSIP_ITEM(0, "Descent into Madness", GOSSIP_SENDER_MAIN, DESCENT_MADNESS);
						}
					}
				}
			}
		}
		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pGO->GetGUID());

		return true;
	}

	bool OnGossipSelect( Player *pPlayer, GameObject *pGO, uint32 sender, uint32 action )
	{
		if(sender != GOSSIP_SENDER_MAIN) return true;
		if(!pPlayer->getAttackers().empty()) return true;

		switch(action)
		{
		case BASE_CAMP:
			pPlayer->TeleportTo(603, -706.122f, -92.6024f, 429.876f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case GROUNDS:
			pPlayer->TeleportTo(603, 131.248f, -35.3802f, 409.804f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case FORGE:
			pPlayer->TeleportTo(603, 553.233f, -12.3247f, 409.679f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case SCRAPYARD:
			pPlayer->TeleportTo(603, 926.292f, -11.4635f, 418.595f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case ANTECHAMBER:
			pPlayer->TeleportTo(603, 1498.09f, -24.246f, 420.967f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case WALKWAY:
			pPlayer->TeleportTo(603, 1859.45f, -24.1f, 448.9f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case CONSERVATORY:
			pPlayer->TeleportTo(603, 2086.27f, -24.3134f, 421.239f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case SPARK_IMAGINATION:
			pPlayer->TeleportTo(603, 2518.16f, 2569.03f, 412.299f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		case DESCENT_MADNESS:
			pPlayer->TeleportTo(603, 1854.82f, -11.5608f, 334.175f, 0);
			pPlayer->CLOSE_GOSSIP_MENU(); break;
		}

		return true;
	}
};

void AddSC_ulduar_teleporter()
{
    new ulduar_teleporter();
}
