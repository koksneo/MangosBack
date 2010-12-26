/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Howling_Fjord
SD%Complete: ?
SDComment: Quest support: 11221, 11483
SDCategory: Howling Fjord
EndScriptData */

#include "precompiled.h"
#include "escort_ai.h"

/*#######################
## Deathstalker Razael ##
#######################*/

#define GOSSIP_ITEM_DEATHSTALKER_RAZAEL "High Executor Anselm requests your report."

enum
{
    QUEST_REPORTS_FROM_THE_FIELD       = 11221,
    SPELL_RAZAEL_KILL_CREDIT           = 42756,
    GOSSIP_TEXTID_DEATHSTALKER_RAZAEL1 = 11562,
    GOSSIP_TEXTID_DEATHSTALKER_RAZAEL2 = 11564
};

bool GossipHello_npc_deathstalker_razael(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_REPORTS_FROM_THE_FIELD) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEATHSTALKER_RAZAEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEATHSTALKER_RAZAEL1, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_deathstalker_razael(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEATHSTALKER_RAZAEL2, pCreature->GetGUID());
            pCreature->CastSpell(pPlayer, SPELL_RAZAEL_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*######
## npc_dark_ranger_lyana - TODO, can be moved to database
######*/

#define GOSSIP_ITEM_DARK_RANGER_LYANA "High Executor Anselm requests your report."

enum
{
    GOSSIP_TEXTID_DARK_RANGER_LYANA1    = 11586,
    GOSSIP_TEXTID_DARK_RANGER_LYANA2    = 11588,
    SPELL_DARK_RANGER_LYANA_KILL_CREDIT = 42799
};

bool GossipHello_npc_dark_ranger_lyana(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_REPORTS_FROM_THE_FIELD) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DARK_RANGER_LYANA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DARK_RANGER_LYANA1, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_dark_ranger_lyana(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DARK_RANGER_LYANA2, pCreature->GetGUID());
            pCreature->CastSpell(pPlayer, SPELL_DARK_RANGER_LYANA_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*######
## npc_greer_orehammer
######*/

enum
{
    GOSSIP_ITEM_TAXI                        = -3000106,
    GOSSIP_ITEM_GET_BOMBS                   = -3000107,
    GOSSIP_ITEM_FLIGHT                      = -3000108,

    QUEST_MISSION_PLAGUE_THIS               = 11332,
    ITEM_PRECISION_BOMBS                    = 33634,
    TAXI_PATH_PLAGUE_THIS                   = 745,
};

bool GossipHello_npc_greer_orehammer(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_MISSION_PLAGUE_THIS) == QUEST_STATUS_INCOMPLETE)
    {
        if (!pPlayer->HasItemCount(ITEM_PRECISION_BOMBS, 1, true))
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GET_BOMBS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    }

    if (pCreature->isTaxi())
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_TAXI, GOSSIP_ITEM_TAXI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_greer_orehammer(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            if (Item* pItem = pPlayer->StoreNewItemInInventorySlot(ITEM_PRECISION_BOMBS, 10))
                pPlayer->SendNewItem(pItem, 10, true, false);

            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->ActivateTaxiPathTo(TAXI_PATH_PLAGUE_THIS);
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->GetSession()->SendTaxiMenu(pCreature);
            break;
    }

    return true;
}

/*######
## npc_mcgoyver - TODO, can be moved to database
######*/

#define GOSSIP_ITEM_MCGOYVER1 "Walt sent me to pick up some dark iron ingots."
#define GOSSIP_ITEM_MCGOYVER2 "Yarp."

enum
{
    QUEST_WE_CAN_REBUILD_IT                = 11483,
    GOSSIP_TEXTID_MCGOYVER                 = 12193,
    ITEM_DARK_IRON_INGOTS                  = 34135,
    SPELL_MCGOYVER_TAXI_EXPLORERSLEAGUE    = 44280,
    SPELL_MCGOYVER_CREATE_DARK_IRON_INGOTS = 44512
};

bool GossipHello_npc_mcgoyver(Player* pPlayer, Creature* pCreature)
{
    switch(pPlayer->GetQuestStatus(QUEST_WE_CAN_REBUILD_IT))
    {
        case QUEST_STATUS_INCOMPLETE:
            if (!pPlayer->HasItemCount(ITEM_DARK_IRON_INGOTS, 1, true))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            }
            else
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
            }
            break;
        case QUEST_STATUS_COMPLETE:
            if (!pPlayer->GetQuestRewardStatus(QUEST_WE_CAN_REBUILD_IT))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
                break;
            }
        default:
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }

    return true;
}

bool GossipSelect_npc_mcgoyver(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pCreature->CastSpell(pPlayer, SPELL_MCGOYVER_CREATE_DARK_IRON_INGOTS, true);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, SPELL_MCGOYVER_TAXI_EXPLORERSLEAGUE, true);
            break;
    }

    return true;
}

enum
{
    QUEST_CARVER_AND_A_CROAKER      = 11476,
    ITEM_SCALAWAG_FROG              = 35803
};

struct MANGOS_DLL_DECL mob_scalawag_frogAI : public ScriptedAI
{
    mob_scalawag_frogAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset() {}

    void DamageTaken(Unit* pAttacker, uint32& uiDamage)
    {
        if (!pAttacker || pAttacker->GetTypeId() != TYPEID_PLAYER || ((Player*)pAttacker)->GetQuestStatus(QUEST_CARVER_AND_A_CROAKER) != QUEST_STATUS_INCOMPLETE)
        {
            ScriptedAI::DamageTaken(pAttacker, uiDamage);
            return;
        }
        Player* pPlayer = ((Player*)pAttacker);
        ItemPosCountVec dest;
        uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SCALAWAG_FROG, 1, false);
        if (msg == EQUIP_ERR_OK)
        {
            uiDamage = 0;
            pPlayer->StoreNewItem(dest, ITEM_SCALAWAG_FROG, 1, true);
            m_creature->ForcedDespawn();
        }
    }
};

CreatureAI* GetAI_mob_scalawag_frog(Creature* pCreature)
{
    return new mob_scalawag_frogAI(pCreature);
}

enum Crowleg_Dan
{
    QUEST_CROWLEG_DAN       = 11479,
    SPELL_TRASH_KICK        = 50306
};

#define GOSSIP_ITEM_CROWLEG_DAN "Umm... the frog says you're a traitor."

struct MANGOS_DLL_DECL npc_crowleg_danAI : public ScriptedAI
{
    npc_crowleg_danAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool bTalked;
    uint32 m_uiDelayTimer;
    uint32 m_uiTrashKickTimer;
    uint64 PlayerGUID;

    void Reset() 
    {
        m_creature->setFaction(m_creature->GetCreatureInfo()->faction_A);
        bTalked = false;
        m_uiDelayTimer = 5000;
        m_uiTrashKickTimer = urand(1000,4000);
        PlayerGUID = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bTalked)
        {
            if (m_uiDelayTimer <= uiDiff)
            {
                // dunno exact text and emote
                // DoSciptText();
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(PlayerGUID))
                {
                    m_creature->setFaction(16);
                    m_creature->AI()->AttackStart(pTarget);
                    bTalked = false;
                }else Reset();
            }else m_uiDelayTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTrashKickTimer <= uiDiff)
        {
            DoCast(m_creature->getVictim(),SPELL_TRASH_KICK,false);
            m_uiTrashKickTimer = urand(3000,6000);
        }else m_uiTrashKickTimer -= uiDiff;
        
        DoMeleeAttackIfReady();
    }
};

bool GossipHello_npc_crowleg_dan(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_CROWLEG_DAN) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_CROWLEG_DAN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_crowleg_dan(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        // dunno exact text
        // DoScriptText();
        ((npc_crowleg_danAI*)pCreature->AI())->bTalked = true;
        ((npc_crowleg_danAI*)pCreature->AI())->PlayerGUID = pPlayer->GetGUID();
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_crowleg_dan(Creature* pCreature)
{
    return new npc_crowleg_danAI(pCreature);
}

enum Sivermoon_Harry
{
    QUEST_GAMBLING_DEBT             = 11464,
    SPELL_BLASTWAVE                 = 15091,
    SPELL_SCORCH                    = 50183,
    ITEM_SILVERMOON_HARRYS_DEBT     = 34115,
    SAY_SILVERMOON_HARRY_AGGRO      = -1999820,
    SAY_SILVERMOON_HARRY_SURRENDER  = -1999819
};

#define GOSSIP_ITEM_SILVERMOON_HARRY_1 "Taruk send me to collect what you owe."
#define GOSSIP_ITEM_SILVERMOON_HARRY_2 "Alright, here's your cut."

struct MANGOS_DLL_DECL npc_silvermoon_harryAI : public ScriptedAI
{
    npc_silvermoon_harryAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool bTriggeredByEvent;
    bool bEventDone;

    uint32 m_uiEventTimer;
    uint64 PlayerGUID;
    std::list<uint64> lPlayersEventDone;

    void Reset() 
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->setFaction(m_creature->GetCreatureInfo()->faction_A);
        bTriggeredByEvent = false;
        bEventDone = false;
        m_uiEventTimer = urand(3000,6000);
        PlayerGUID = 0;
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        ScriptedAI::AttackStart(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Silvermoon Harry is aggresive for players that not have complered prequests
        // or are not at quest, so in that case lets switch this part off
        if (bTriggeredByEvent)
        {
            if (m_creature->GetHealth() * 100 / m_creature->GetMaxHealth() <= 33)
            {
                ThreatList const& tList = m_creature->getThreatManager().getThreatList();
                for (ThreatList::const_iterator itr = tList.begin();itr != tList.end(); ++itr)
                {
                    if ((*itr))
                    {
                        if (Unit* pUnit = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
                        {
                            if (pUnit->GetTypeId() == TYPEID_PLAYER)
                                lPlayersEventDone.push_back((*itr)->getUnitGuid());
                        }
                    }
                }
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->setFaction(m_creature->GetCreatureInfo()->faction_A);
                m_creature->CombatStop();
                m_creature->DeleteThreatList();
                DoScriptText(SAY_SILVERMOON_HARRY_SURRENDER,m_creature);
                m_uiEventTimer = 30000;
                bEventDone = true;
            }
        }

        // reset creature after amount of time
        if (bEventDone)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                lPlayersEventDone.clear();
                m_creature->AI()->EnterEvadeMode();
            }else m_uiEventTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            DoCast(m_creature->getVictim(),(urand(0,1) == 0 ? SPELL_BLASTWAVE : SPELL_SCORCH),false);
            m_uiEventTimer = urand(3000,6000);
        }else m_uiEventTimer -= uiDiff;
        
        DoMeleeAttackIfReady();
    }

    // two functions managing players that have joined encounter and are supposed to 
    // get quest item at the end
    bool CheckoutPlayerEventDone(uint64 PlayerGUID)
    {
        if (lPlayersEventDone.empty())
            return false;

        for(std::list<uint64>::iterator itr = lPlayersEventDone.begin(); itr != lPlayersEventDone.end(); ++itr)
        {
            if ((*itr) && (*itr) == PlayerGUID)
                return true;
        }

        return false;
    }
};

bool GossipHello_npc_silvermoon_harry(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isVendor())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    if (pPlayer->GetQuestStatus(QUEST_GAMBLING_DEBT) == QUEST_STATUS_INCOMPLETE)
    {
        if (((npc_silvermoon_harryAI*)pCreature->AI())->CheckoutPlayerEventDone(pPlayer->GetGUID()))
        {
            if (pPlayer->GetItemCount(ITEM_SILVERMOON_HARRYS_DEBT,false) < 1)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SILVERMOON_HARRY_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        }
        else pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SILVERMOON_HARRY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_silvermoon_harry(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF+1: 
            ((npc_silvermoon_harryAI*)pCreature->AI())->AttackStart(pPlayer);
            ((npc_silvermoon_harryAI*)pCreature->AI())->bTriggeredByEvent = true;
            pCreature->setFaction(16);
            DoScriptText(SAY_SILVERMOON_HARRY_AGGRO,pCreature);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;

        case GOSSIP_ACTION_INFO_DEF+2:
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SILVERMOON_HARRYS_DEBT, 1, false);
            if (msg == EQUIP_ERR_OK)
                pPlayer->StoreNewItem(dest, ITEM_SILVERMOON_HARRYS_DEBT, 1, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;            
    }

    return true;
}

CreatureAI* GetAI_npc_silvermoon_harry(Creature* pCreature)
{
    return new npc_silvermoon_harryAI(pCreature);
}

// Quest: Jack Likes His Drink
enum
{
    SAY_OLGA_0                  = -1999818, // whisper
    SAY_OLGA_1                  = -1999817,
    SAY_JACK_ADAMS_2            = -1999816,
    SAY_OLGA_3                  = -1999815,
    SAY_JACK_ADAMS_4            = -1999814,
    SAY_JACK_ADAMS_5            = -1999813, // faint
    SAY_JACK_ADAMS_6            = -1999812, // wakeup

    NPC_TEXT_OLGA_1             = 12180,
    NPC_JACK_ADAMS              = 24788,

    SPELL_VOMIT                 = 41995,
    ITEM_JACK_ADAMS_DEBT        = 34116,
    QUEST_JACK_LIKES_HIS_DRINK  = 11466,
};

float OlgaWaypoints[2][4] = 
{
    {0.0f, -91.81f, -3532.70f, 7.71f},  
    {1.0f, -87.23f, -3544.23f, 7.71f}
};

#define GOSSIP_ITEM_OLGA_1 "I'd like to buy Jack a drink. Perhaps something... extra strong."
#define GOSSIP_ITEM_OLGA_2 "Here's a gold, buy yourself something nice." 
#define GOSSIP_ITEM_OLGA_3 "Do you really want to bribe Olga?"
#define GOSSIP_ITEM_JACK_ADAMS_1 "<Discreetly search the pirate's pockets for Taruk's payment.>"

struct MANGOS_DLL_DECL npc_olgaAI : public ScriptedAI
{
    npc_olgaAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool bEventInProgress;
    bool bInRightPoint;

    uint8 subevent;
    uint32 m_uiEventTimer;
    uint32 m_uiResetJackTimer;
    uint64 JackAdamsGUID;

    void Reset()
    {
        bEventInProgress = false;
        bInRightPoint = true;
        subevent = 0;
        m_uiEventTimer = 5000;
        m_uiResetJackTimer = 30000;
        // restore DB flags (GOSSIP)
        m_creature->SetUInt32Value(UNIT_NPC_FLAGS, m_creature->GetCreatureInfo()->npcflag);
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == OlgaWaypoints[1][0] || uiPointId == OlgaWaypoints[0][0])
            bInRightPoint = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // if not event in progress and Jack is unconscous lets awake him after certain amount of time
        if (!bEventInProgress)
        {
            if (m_uiResetJackTimer <= uiDiff)
            {
                Creature* pJack = m_creature->GetMap()->GetCreature(JackAdamsGUID);
                if (pJack && pJack->isAlive() && pJack->GetByteValue(UNIT_FIELD_BYTES_1,0) == UNIT_STAND_STATE_DEAD)
                    pJack->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_STAND);
                m_uiResetJackTimer = 30000;
            }else m_uiResetJackTimer -= uiDiff;
        }

        if(bEventInProgress && bInRightPoint)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                // if there is no Jack around or he is dead there is no point to continue
                Creature* pJack = m_creature->GetMap()->GetCreature(JackAdamsGUID);
                if (!pJack || !pJack->isAlive())
                {
                    m_creature->AI()->EnterEvadeMode();
                    return;
                }

                switch(subevent)
                {
                    case 0:
                        DoScriptText(SAY_OLGA_1,m_creature);
                        m_creature->GetMotionMaster()->MovePoint(OlgaWaypoints[1][0],OlgaWaypoints[1][1],OlgaWaypoints[1][2],OlgaWaypoints[1][3]);
                        m_uiEventTimer = 3000;
                        break;
                    case 1:
                        DoScriptText(SAY_JACK_ADAMS_2,pJack,m_creature);
                        m_uiEventTimer = 1000;
                        bInRightPoint = false;
                        break;
                    case 2:
                        m_creature->SetFacingToObject(pJack);
                        m_uiEventTimer = 2000;
                        break;
                    case 3:
                        DoScriptText(SAY_OLGA_3,m_creature,pJack);
                        m_uiEventTimer = 7000;
                        break;
                    case 4:
                        pJack->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_KNEEL);
                        DoScriptText(SAY_JACK_ADAMS_4,pJack,m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 5:
                        pJack->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 3000;
                        break;
                    case 6:
                        pJack->CastSpell(pJack,SPELL_VOMIT,false);
                        m_uiEventTimer = 3000;
                        break;
                    case 7:
                        DoScriptText(SAY_JACK_ADAMS_5,pJack,m_creature);
                        pJack->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_DEAD);
                        pJack->SetUInt32Value(UNIT_NPC_FLAGS, m_creature->GetCreatureInfo()->npcflag);
                        m_uiEventTimer = 3000;
                    case 8:
                        m_creature->GetMotionMaster()->MovePoint(OlgaWaypoints[0][0],OlgaWaypoints[0][1],OlgaWaypoints[0][2],OlgaWaypoints[0][3]);
                        bInRightPoint = false;
                        break;
                    case 9:
                        m_creature->SetFacingToObject(pJack);
                        Reset();
                        return;
                    default: break;
                }
                ++ subevent;
            }else m_uiEventTimer -= uiDiff;
        }
    }
};


bool GossipHello_npc_olga(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_JACK_LIKES_HIS_DRINK) == QUEST_STATUS_INCOMPLETE && pPlayer->GetMoney() >= 10000)
    {
        Creature* pJack = GetClosestCreatureWithEntry(pCreature,NPC_JACK_ADAMS,20.0f);
        if (pJack && pJack->isAlive() && pJack->GetByteValue(UNIT_FIELD_BYTES_1,0) == UNIT_STAND_STATE_STAND)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_OLGA_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            ((npc_olgaAI*)pCreature->AI())->JackAdamsGUID = pJack->GetGUID();
        }
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_olga(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, GOSSIP_ITEM_OLGA_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2,GOSSIP_ITEM_OLGA_3, 10000,false);
            pPlayer->SEND_GOSSIP_MENU(NPC_TEXT_OLGA_1, pCreature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            DoScriptText(SAY_OLGA_0,pCreature,pPlayer);
            pCreature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
            pPlayer->ModifyMoney(-10000);
            ((npc_olgaAI*)pCreature->AI())->bEventInProgress = true;
            break;
    }
    return true;
}

bool GossipHello_npc_jack_adams(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_JACK_LIKES_HIS_DRINK) == QUEST_STATUS_INCOMPLETE && pPlayer->GetItemCount(ITEM_JACK_ADAMS_DEBT,false) < 1)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_JACK_ADAMS_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_jack_adams(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ItemPosCountVec dest;
        uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_JACK_ADAMS_DEBT, 1, false);
        if (msg == EQUIP_ERR_OK)
            pPlayer->StoreNewItem(dest, ITEM_JACK_ADAMS_DEBT, 1, true);
        pCreature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
        // 50% chance that jack standup immediately
        if (urand(0, 1) == 0)
        {
            pCreature->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_STAND);
            DoScriptText(SAY_JACK_ADAMS_6,pCreature,pPlayer);
        }
    }
    return true;
}

CreatureAI* GetAI_npc_olga(Creature* pCreature)
{
    return new npc_olgaAI(pCreature);
}

/*######
## npc_apothecary_hanes
######*/

enum Hanes
{
    QUEST_TRIAL_OF_FIRE     = 11241,
    SPELL_HEALING_POTION    = 17534,
    SPELL_FLAME_PATCH_VIS   = 46836,
    NPC_FIRE_TRIGGER        = 23968,

    SAY_ESCORT_STARTED      = -1999760,
    SAY_1ST_WAYPOINT        = -1999759,
    SAY_2ND_WAYPOINT        = -1999758,
    SAY_1ST_SET_BURNED      = -1999757,
    SAY_2ND_SET_BURNED      = -1999756,
    SAY_3RD_SET_BURNED      = -1999755,
    YELL_ALL_SETS_BURNED    = -1999754,
    SAY_ESCORT_COMPLETED    = -1999753
};

struct MANGOS_DLL_DECL npc_apothecary_hanesAI : public npc_escortAI
{
    npc_apothecary_hanesAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    uint32 m_uiPotionTimer;

    void Reset() 
    {
        m_uiPotionTimer = 0;
    }

    void BurnSupplies()
    {
        std::list<Creature*> lFireTriggers;
        GetCreatureListWithEntryInGrid(lFireTriggers, m_creature, NPC_FIRE_TRIGGER, 20.0f);
        if (lFireTriggers.empty())
            return;

        for (std::list<Creature*>::iterator itr = lFireTriggers.begin(); itr != lFireTriggers.end(); ++itr)
        {
            if ((*itr)->isAlive())
                (*itr)->CastSpell(*itr, SPELL_FLAME_PATCH_VIS, true);
        }
    }
        

    void WaypointReached(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 0: DoScriptText(SAY_1ST_WAYPOINT, m_creature); break;
            case 1: DoScriptText(SAY_2ND_WAYPOINT, m_creature); break;
            case 7:
            case 11:
            case 17:
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USESTANDING_NOSHEATHE);
                break;
            case 18:
                DoScriptText(YELL_ALL_SETS_BURNED, m_creature);
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH_NOSHEATHE);
                break;
            case 32:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_creature->SetFacingToObject(pPlayer);
                    DoScriptText(SAY_ESCORT_COMPLETED, m_creature, pPlayer);
                    pPlayer->AreaExploredOrEventHappens(QUEST_TRIAL_OF_FIRE);
                }
                break;
        }
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 8:
                BurnSupplies();
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                DoScriptText(SAY_1ST_SET_BURNED, m_creature);
                break;
            case 12:
                BurnSupplies();
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                DoScriptText(SAY_2ND_SET_BURNED, m_creature);
                break;
            case 18:
                BurnSupplies();
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                DoScriptText(SAY_3RD_SET_BURNED, m_creature);
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->GetHealthPercent() < 75.0f)
        {
            if (m_uiPotionTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_HEALING_POTION);
                m_uiPotionTimer = 30000;
            }
            else
                m_uiPotionTimer -= uiDiff;
        }
        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_apothecary_hanes(Creature* pCreature)
{
    return new npc_apothecary_hanesAI(pCreature);
}

bool QuestAccept_npc_apothecary_hanes(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_TRIAL_OF_FIRE)
    {

        if (npc_apothecary_hanesAI* pEscortAI = dynamic_cast<npc_apothecary_hanesAI*>(pCreature->AI()))
        {
            pEscortAI->Start(true, pPlayer->GetGUID(), pQuest);
            pCreature->setFaction(FACTION_ESCORT_H_NEUTRAL_ACTIVE);
            DoScriptText(SAY_ESCORT_STARTED, pCreature);
        }
    }
    return true;
}

/*#####
## go_dragonflayer_cage
#####*/

enum
{
    QUEST_PRISONERS_OF_WYRMSKULL      = 11255,
    NPC_VALGARDE_PRISONER_PRIEST      = 24086,
    NPC_VALGARDE_PRISONER_MAGE        = 24088,
    NPC_VALGARDE_PRISONER_WARRIOR     = 24089,
    NPC_VALGARDE_PRISONER_PALADIN     = 24090,
    NPC_VALGARDE_PRIEST               = 24099,
    NPC_VALGARDE_MAGE                 = 24096,
    NPC_VALGARDE_WARRIOR              = 24097,
    NPC_VALGARDE_PALADIN              = 24103,

    SPELL_GBOM                        = 43940,
    SPELL_STAMINA                     = 39231,
    SPELL_SHOUT                       = 25101,
    SPELL_VALGARDE_PRISONER_CREDIT    = 43094,

    PRISONER_TEXT_ID_1                = -1700001,
    PRISONER_TEXT_ID_2                = -1700002,
    PRISONER_TEXT_ID_3                = -1700003
};

bool GOHello_go_dragonflayer_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_PRISONERS_OF_WYRMSKULL) == QUEST_STATUS_INCOMPLETE)
    {
        Creature *pPrisoner = GetClosestCreatureWithEntry(pPlayer, NPC_VALGARDE_PRISONER_PRIEST, INTERACTION_DISTANCE);
        if(!pPrisoner)
            pPrisoner = GetClosestCreatureWithEntry(pPlayer, NPC_VALGARDE_PRISONER_MAGE, INTERACTION_DISTANCE);
        if(!pPrisoner)
            pPrisoner = GetClosestCreatureWithEntry(pPlayer, NPC_VALGARDE_PRISONER_WARRIOR, INTERACTION_DISTANCE);
        if(!pPrisoner)
            pPrisoner = GetClosestCreatureWithEntry(pPlayer, NPC_VALGARDE_PRISONER_PALADIN, INTERACTION_DISTANCE);
        if(pPrisoner)
        {
            pPrisoner->setFaction(pPlayer->getFaction());
            
            switch(urand(0,2))
            {
                case 0:DoScriptText(PRISONER_TEXT_ID_1,pPrisoner);break;
                case 1:DoScriptText(PRISONER_TEXT_ID_2,pPrisoner);break;
                case 2:DoScriptText(PRISONER_TEXT_ID_3,pPrisoner);break;

            }
            
            uint32 uiType = pPrisoner->GetEntry();
            pPlayer->CastSpell(pPlayer,SPELL_VALGARDE_PRISONER_CREDIT,false);
            switch(uiType)
            {
                case NPC_VALGARDE_PRISONER_WARRIOR:
                {
                    pPlayer->CastSpell(pPlayer, SPELL_SHOUT, true);
                    pPrisoner->UpdateEntry(NPC_VALGARDE_WARRIOR);
                    break;
                }
                case NPC_VALGARDE_PRISONER_PALADIN:
                {
                    pPlayer->CastSpell(pPlayer, SPELL_GBOM, true);
                    pPrisoner->UpdateEntry(NPC_VALGARDE_PALADIN);
                    break;
                }
                 case NPC_VALGARDE_PRISONER_MAGE:
                {
                    pPrisoner->UpdateEntry(NPC_VALGARDE_MAGE);
                    break;
                }
                case NPC_VALGARDE_PRISONER_PRIEST:
                {
                    pPlayer->CastSpell(pPlayer, SPELL_STAMINA, true);
                    pPrisoner->UpdateEntry(NPC_VALGARDE_PRIEST);
                    break;
                }
            }
            pPrisoner->SetStandState(UNIT_STAND_STATE_STAND);
            pPrisoner->ForcedDespawn(2*MINUTE*IN_MILLISECONDS); //despawn after 2 minutes
            pPrisoner->GetMotionMaster()->MoveFollow(pPlayer, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }
    }
    return false;
};

void AddSC_howling_fjord()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_deathstalker_razael";
    newscript->pGossipHello = &GossipHello_npc_deathstalker_razael;
    newscript->pGossipSelect = &GossipSelect_npc_deathstalker_razael;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dark_ranger_lyana";
    newscript->pGossipHello = &GossipHello_npc_dark_ranger_lyana;
    newscript->pGossipSelect = &GossipSelect_npc_dark_ranger_lyana;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_mcgoyver";
    newscript->pGossipHello = &GossipHello_npc_mcgoyver;
    newscript->pGossipSelect = &GossipSelect_npc_mcgoyver;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_scalawag_frog";
    newscript->GetAI = &GetAI_mob_scalawag_frog;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_crowleg_dan";
    newscript->GetAI = &GetAI_npc_crowleg_dan;
    newscript->pGossipHello = &GossipHello_npc_crowleg_dan;
    newscript->pGossipSelect = &GossipSelect_npc_crowleg_dan;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_silvermoon_harry";
    newscript->GetAI = &GetAI_npc_silvermoon_harry;
    newscript->pGossipHello = &GossipHello_npc_silvermoon_harry;
    newscript->pGossipSelect = &GossipSelect_npc_silvermoon_harry;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_olga";
    newscript->GetAI = &GetAI_npc_olga;
    newscript->pGossipHello = &GossipHello_npc_olga;
    newscript->pGossipSelect = &GossipSelect_npc_olga;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_jack_adams";
    newscript->pGossipHello = &GossipHello_npc_jack_adams;
    newscript->pGossipSelect = &GossipSelect_npc_jack_adams;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_apothecary_hanes";
    newscript->GetAI = &GetAI_npc_apothecary_hanes;
    newscript->pQuestAccept = &QuestAccept_npc_apothecary_hanes;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "go_dragonflayer_cage";
    newscript->pGOHello = &GOHello_go_dragonflayer_cage;
    newscript->RegisterSelf();
}
