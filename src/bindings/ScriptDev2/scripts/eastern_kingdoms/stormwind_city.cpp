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
SDName: Stormwind_City
SD%Complete: 100
SDComment: Quest support: 1640, 1447, 4185, 11223 (DB support required for spell 42711)
SDCategory: Stormwind City
EndScriptData */

/* ContentData
npc_archmage_malin
npc_bartleby
npc_corbett_schneider
npc_rema_schneider
npc_dashel_stonefist
npc_lady_katrana_prestor
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_archmage_malin
######*/

#define GOSSIP_ITEM_MALIN "Can you send me to Theramore? I have an urgent message for Lady Jaina from Highlord Bolvar."

bool GossipHello_npc_archmage_malin(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(11223) == QUEST_STATUS_COMPLETE && !pPlayer->GetQuestRewardStatus(11223))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MALIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_archmage_malin(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->CastSpell(pPlayer, 42711, true);
    }

    return true;
}

/*######
## npc_bartleby
######*/

enum
{
    FACTION_ENEMY       = 168,
    QUEST_BEAT          = 1640
};

struct MANGOS_DLL_DECL npc_bartlebyAI : public ScriptedAI
{
    npc_bartlebyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (m_creature->getVictim())
            return;

        if (m_creature->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() || ((m_creature->GetHealth() - uiDamage)*100 / m_creature->GetMaxHealth() < 15))
        {
            uiDamage = 0;

            if (pDoneBy->GetTypeId() == TYPEID_PLAYER)
                ((Player*)pDoneBy)->AreaExploredOrEventHappens(QUEST_BEAT);

            EnterEvadeMode();
        }
    }
};

bool QuestAccept_npc_bartleby(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_BEAT)
    {
        pCreature->setFaction(FACTION_ENEMY);
        ((npc_bartlebyAI*)pCreature->AI())->AttackStart(pPlayer);
    }
    return true;
}

CreatureAI* GetAI_npc_bartleby(Creature* pCreature)
{
    return new npc_bartlebyAI(pCreature);
}

/*######
## npc_corbett_schneider
######*/
enum
{
    QUEST_HARLAN_RESUPPLY = 333,

    TIME_SPEACH           = 5000,

    NPC_CORBETT           = 1433,
    NPC_REMA              = 1428,
    NPC_HARLAN            = 1427,
    NPC_ELAINE            = 483,

    SAY_REMA_0            = -1999889,
    SAY_REMA_1            = -1999888,

    CORBET_WP_0_0         = -1999887,
    CORBET_WP_0_1         = -1999886,
    CORBET_WP_13_0        = -1999885,
    CORBET_WP_13_1        = -1999884,
    CORBET_WP_14_0        = -1999883,
    CORBET_WP_14_1        = -1999882,
    HARLAN_0              = -1999881,
    HARLAN_1              = -1999880,
    CORBET_WP_14_2        = -1999879,
    CORBET_WP_14_3        = -1999878,
    CORBET_WP_17          = -1999877,
    CORBET_WP_20_0        = -1999876,
    CORBET_WP_20_1        = -1999875,
    ELAINE_0              = -1999874,
    ELAINE_1              = -1999873,
    CORBET_WP_20_2        = -1999872,
    CORBET_WP_20_3        = -1999871,
    CORBET_WP_22          = -1999870,
    CORBET_WP_32          = -1999869
};

float CorbettSpawn[4] = {-8774.32f, 716.87f, 99.53f, 3.99f};

struct MANGOS_DLL_DECL npc_corbett_schneiderAI : public npc_escortAI
{
    npc_corbett_schneiderAI(Creature* pCreature) : npc_escortAI(pCreature) 
    {
        Point = 0;
        subevent = 0;
        RemaGUID = 0;
        HarlanGUID = 0;
        ElaineGUID = 0;
        Reset();
    }

    uint8 Point;
    uint8 subevent;

    uint32 m_uiEvent_Timer;

    uint64 RemaGUID;
    uint64 HarlanGUID;
    uint64 ElaineGUID;

    void Reset()
    {
        m_uiEvent_Timer = 0;
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 6: DoScriptText(urand(0, 1) ? CORBET_WP_13_0 : CORBET_WP_13_1,m_creature); break;
            case 17: DoScriptText(CORBET_WP_17,m_creature); break;
            case 23: DoScriptText(CORBET_WP_22,m_creature); break;
            case 32: DoScriptText(CORBET_WP_32,m_creature); break;
            default: break;
        }
        Point = uiPointId;
    }

    void WaypointReached(uint32 uiPointId){}

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (m_uiEvent_Timer <= uiDiff)
        {
            switch(Point)
            {
                case 0: 
                    if (Creature* pRema = (Creature*)Unit::GetUnit((*m_creature),RemaGUID))
                    {
                        switch(subevent)
                        {
                            case 0:
                                SetEscortPaused(true);
                                m_creature->SetFacingToObject(pRema);
                                pRema->SetFacingToObject(m_creature);
                                DoScriptText(urand(0, 1) ? SAY_REMA_0 : SAY_REMA_1,pRema,m_creature);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 1:
                                DoScriptText(urand(0, 1) ? CORBET_WP_0_0 : CORBET_WP_0_1,m_creature,pRema);
                                m_uiEvent_Timer = TIME_SPEACH;
                                subevent = 0;
                                SetEscortPaused(false);
                                break;
                        }
                    }else
                        {   
                            if (Creature* pRema = GetClosestCreatureWithEntry(m_creature, NPC_REMA, 2*INTERACTION_DISTANCE))
                                RemaGUID = pRema->GetGUID();
                        }
                    break;
                case 14:
                    if (Creature* pHarlan = (Creature*)Unit::GetUnit((*m_creature),HarlanGUID))
                    {
                        switch(subevent)
                        {
                            case 0:
                                SetEscortPaused(true);
                                m_creature->SetFacingToObject(pHarlan);
                                pHarlan->SetFacingToObject(m_creature);
                                DoScriptText(urand(0,1) ? CORBET_WP_14_0 : CORBET_WP_14_1,m_creature,pHarlan);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 1:
                                DoScriptText(urand(0,1) ? HARLAN_0 : HARLAN_1,pHarlan,m_creature);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 2:
                                DoScriptText(urand(0,1) ? CORBET_WP_14_2 : CORBET_WP_14_3,m_creature,pHarlan);
                                m_uiEvent_Timer = TIME_SPEACH;
                                subevent = 0;
                                SetEscortPaused(false);
                                break;
                        }
                    }else 
                    {
                        if (Creature* pHarlan = GetClosestCreatureWithEntry(m_creature, NPC_HARLAN, 2*INTERACTION_DISTANCE))
                            HarlanGUID = pHarlan->GetGUID();
                    }
                    break;
                case 20:
                    if (Creature* pElaine = (Creature*)Unit::GetUnit((*m_creature),ElaineGUID))
                    {
                        switch(subevent)
                        {
                            case 0:
                                SetEscortPaused(true);
                                m_creature->SetFacingToObject(pElaine);
                                pElaine->SetFacingToObject(m_creature);
                                DoScriptText(urand(0,1) ? CORBET_WP_20_0 : CORBET_WP_20_1,m_creature,pElaine);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 1:
                                DoScriptText(urand(0,1) ? ELAINE_0 : ELAINE_1,pElaine,m_creature);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 2:
                                DoScriptText(CORBET_WP_20_2,m_creature,pElaine);
                                m_uiEvent_Timer = TIME_SPEACH;
                                ++subevent;
                                break;
                            case 3:
                                DoScriptText(CORBET_WP_20_3,m_creature,pElaine);
                                m_uiEvent_Timer = TIME_SPEACH;
                                subevent = 0;
                                SetEscortPaused(false);
                                break;
                        }
                    }else
                    {
                        if (Creature* pElaine = GetClosestCreatureWithEntry(m_creature, NPC_ELAINE, 2*INTERACTION_DISTANCE))
                            ElaineGUID = pElaine->GetGUID();
                    }
                    break;
                default: break;
            }
        }else m_uiEvent_Timer -= uiDiff;
    }
};
/*######
## npc_rema_schneider
######*/
bool ChooseReward_npc_rema_schneider(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 slot)
{

    if (pPlayer && pQuest->GetQuestId() == QUEST_HARLAN_RESUPPLY)
    {
        if (Creature* pCorbett = pCreature->SummonCreature(NPC_CORBETT, CorbettSpawn[0], CorbettSpawn[1], CorbettSpawn[2], CorbettSpawn[3], TEMPSUMMON_CORPSE_DESPAWN, 0))
            if (npc_corbett_schneiderAI* pEscortAI = dynamic_cast<npc_corbett_schneiderAI*>(pCorbett->AI()))
                pEscortAI->Start(false, false, pPlayer->GetGUID());
    }
    return true;
}
CreatureAI* GetAI_npc_corbett_schneiderAI(Creature* pCreature)
{
    return new npc_corbett_schneiderAI(pCreature);
}
                
/*######
## npc_dashel_stonefist
######*/

enum
{
    QUEST_MISSING_DIPLO_PT8     = 1447,
    FACTION_HOSTILE             = 168
};

struct MANGOS_DLL_DECL npc_dashel_stonefistAI : public ScriptedAI
{
    npc_dashel_stonefistAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (m_creature->getVictim())
            return;

        if (m_creature->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() || ((m_creature->GetHealth() - uiDamage)*100 / m_creature->GetMaxHealth() < 15))
        {
            uiDamage = 0;

            if (pDoneBy->GetTypeId() == TYPEID_PLAYER)
                ((Player*)pDoneBy)->AreaExploredOrEventHappens(QUEST_MISSING_DIPLO_PT8);

            EnterEvadeMode();
        }
    }
};

bool QuestAccept_npc_dashel_stonefist(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT8)
    {
        pCreature->setFaction(FACTION_HOSTILE);
        ((npc_dashel_stonefistAI*)pCreature->AI())->AttackStart(pPlayer);
    }
    return true;
}

CreatureAI* GetAI_npc_dashel_stonefist(Creature* pCreature)
{
    return new npc_dashel_stonefistAI(pCreature);
}

/*######
## npc_lady_katrana_prestor
######*/

#define GOSSIP_ITEM_KAT_1 "Pardon the intrusion, Lady Prestor, but Highlord Bolvar suggested that I seek your advice."
#define GOSSIP_ITEM_KAT_2 "My apologies, Lady Prestor."
#define GOSSIP_ITEM_KAT_3 "Begging your pardon, Lady Prestor. That was not my intent."
#define GOSSIP_ITEM_KAT_4 "Thank you for your time, Lady Prestor."

bool GossipHello_npc_lady_katrana_prestor(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(4185) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(2693, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lady_katrana_prestor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(2694, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(2695, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(2696, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(4185);
            break;
    }
    return true;
}

void AddSC_stormwind_city()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_archmage_malin";
    newscript->pGossipHello = &GossipHello_npc_archmage_malin;
    newscript->pGossipSelect = &GossipSelect_npc_archmage_malin;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_bartleby";
    newscript->GetAI = &GetAI_npc_bartleby;
    newscript->pQuestAccept = &QuestAccept_npc_bartleby;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_corbett_schneider";
    newscript->GetAI = &GetAI_npc_corbett_schneiderAI;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_rema_schneider";
    newscript->pChooseReward = &ChooseReward_npc_rema_schneider;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dashel_stonefist";
    newscript->GetAI = &GetAI_npc_dashel_stonefist;
    newscript->pQuestAccept = &QuestAccept_npc_dashel_stonefist;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lady_katrana_prestor";
    newscript->pGossipHello = &GossipHello_npc_lady_katrana_prestor;
    newscript->pGossipSelect = &GossipSelect_npc_lady_katrana_prestor;
    newscript->RegisterSelf();
}
