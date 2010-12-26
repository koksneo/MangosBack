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
SDComment: Quest support: 1640, 1447, 4185, 11223, 434 (DB support required for spell 42711)
SDCategory: Stormwind City
EndScriptData */

/* ContentData
npc_archmage_malin
npc_bartleby
npc_corbett_schneider
npc_rema_schneider
npc_dashel_stonefist
npc_lady_katrana_prestor
npc_lord_gregor_lescovar
npc_marzon_silent_blade
npc_tyrion_spybot
npc_tyrion
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
        pCreature->AI()->AttackStart(pPlayer);
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
                    if (Creature* pRema = m_creature->GetMap()->GetCreature(RemaGUID))
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
                    if (Creature* pHarlan = m_creature->GetMap()->GetCreature(HarlanGUID))
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
                    if (Creature* pElaine = m_creature->GetMap()->GetCreature(ElaineGUID))
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
                pEscortAI->Start(false, pPlayer->GetGUID());
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
        pCreature->AI()->AttackStart(pPlayer);
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

/*######
## npc_lord_gregor_lescovar
######*/

enum 
{
    SAY_LESCOVAR_2 = -1100008,
    SAY_GUARD_2    = -1100009,
    SAY_LESCOVAR_3 = -1100010,
    SAY_MARZON_1   = -1100011,
    SAY_LESCOVAR_4 = -1100012,
    SAY_TYRION_2   = -1100013,
    SAY_MARZON_2   = -1100014,

    NPC_STORMWIND_ROYAL = 1756,
    NPC_MARZON_BLADE    = 1755,
    NPC_TYRION          = 7766,
    NPC_LORD_GREGOR_LESCOVAR = 1754,
    QUEST_THE_ATTACK    = 434
};

struct MANGOS_DLL_DECL npc_lord_gregor_lescovarAI : public npc_escortAI
{
    npc_lord_gregor_lescovarAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }
    uint32 m_uiNormalFaction;

    uint32 uiTimer;
    uint32 uiPhase;

    uint64 MarzonGUID;

    void Reset()
    {
            uiTimer = 0;
            uiPhase = 0;

            MarzonGUID = 0;
            if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn(10);

        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature, NPC_MARZON_BLADE, 150.0f))
        {
            if (pMarzon->isAlive())
                pMarzon->ForcedDespawn(10);
        }
    }

    void EnterCombat(Unit* pWho)
    {
        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature, NPC_MARZON_BLADE, 150.0f))
        {
            if (pMarzon->isAlive() && !pMarzon->isInCombat())
               pMarzon->AI()->AttackStart(pWho); 
           
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 14:
                SetEscortPaused(true);
                DoScriptText(SAY_LESCOVAR_2, m_creature);
                uiTimer = 3000;
                uiPhase = 1;
                break;
            case 16:
                SetEscortPaused(true);
                if (Creature *pMarzon = m_creature->SummonCreature(NPC_MARZON_BLADE,-8411.360352f, 480.069733f, 123.760895f, 4.941504f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000))
                {
                    pMarzon->GetMotionMaster()->MovePoint(0,-8408.000977f, 468.611450f, 123.759903f);
                   
                }
                uiTimer = 2000;
                uiPhase = 4;
                break;
        }
    } 
        
    void DoGuardsDisappearAndDie()
    {
        std::list<Creature*> GuardList;
        GetCreatureListWithEntryInGrid(GuardList,m_creature,NPC_STORMWIND_ROYAL,8.0f);
        if (!GuardList.empty())
        {
            for (std::list<Creature*>::const_iterator itr = GuardList.begin(); itr != GuardList.end(); ++itr)
            {
                if (Creature* pGuard = *itr)
                    pGuard->ForcedDespawn(10);
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
        {
            if (uiPhase)
            {
                if (uiTimer <= uiDiff)
                {
                     switch(uiPhase)
                    {
                        case 1:
                            if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature,NPC_STORMWIND_ROYAL, 8.0f))
                                DoScriptText(SAY_GUARD_2, pGuard);
                            uiTimer = 3000;
                            uiPhase = 2;
                            break;
                        case 2:
                            DoGuardsDisappearAndDie();
                            uiTimer = 2000;
                            uiPhase = 3;
                            break;
                        case 3:
                            SetEscortPaused(false);
                            uiTimer = 0;
                            uiPhase = 0;
                            break;
                        case 4:
                            DoScriptText(SAY_LESCOVAR_3, m_creature);
                            uiTimer = 0;
                            uiPhase = 0;
                            break;
                        case 5:
                            if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature,NPC_MARZON_BLADE, 150.0f))
                                DoScriptText(SAY_MARZON_1, pMarzon);
                            uiTimer = 3000;
                            uiPhase = 6;
                            break;
                        case 6:
                            DoScriptText(SAY_LESCOVAR_4, m_creature);
                            if (Player* pPlayer = GetPlayerForEscort())
                                pPlayer->AreaExploredOrEventHappens(QUEST_THE_ATTACK);
                            uiTimer = 2000;
                            uiPhase = 7;
                            break; 
                        case 7:
                            if (Creature* pTyrion = GetClosestCreatureWithEntry(m_creature,NPC_TYRION, 20.0f))
                                DoScriptText(SAY_TYRION_2, pTyrion);
                            if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature,NPC_MARZON_BLADE, 150.0f))
                                pMarzon->setFaction(14);
                            m_creature->setFaction(14);
                            uiTimer = 0;
                            uiPhase = 0;
                            break;
                    }
                } else uiTimer -= uiDiff;
            }
    }

};
CreatureAI* GetAI_npc_lord_gregor_lescovarAI(Creature* pCreature)
{
    return new npc_lord_gregor_lescovarAI(pCreature);
}
          
/*######
## npc_marzon_silent_blade
######*/

struct MANGOS_DLL_DECL npc_marzon_silent_bladeAI : public ScriptedAI
{
    npc_marzon_silent_bladeAI(Creature* pCreature) : ScriptedAI(pCreature)
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

        void EnterCombat(Unit* pWho)
        {
            DoScriptText(SAY_MARZON_2, m_creature);
        }

        void EnterEvadeMode()
        {
            m_creature->ForcedDespawn(10);
         }

        void MovementInform(uint32 uiType, uint32 )
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            
                if (Creature *pLescovar = GetClosestCreatureWithEntry(m_creature,NPC_LORD_GREGOR_LESCOVAR, 30.0f))
                {
                    ((npc_lord_gregor_lescovarAI*)pLescovar->AI())-> uiTimer = 2000;
                    ((npc_lord_gregor_lescovarAI*)pLescovar->AI())-> uiPhase = 5;
                  
                }
            
        }
        void UpdateAI(const uint32)
        {
            if (!m_creature->getVictim())
                return;

            DoMeleeAttackIfReady();
        }
};
CreatureAI* GetAI_npc_marzon_silent_bladeAI(Creature* pCreature)
{
    return new npc_marzon_silent_bladeAI(pCreature);
}

/*######
## npc_tyrion_spybot
######*/

enum 
{
    SAY_QUEST_ACCEPT_ATTACK  = -1100000,
    SAY_TYRION_1             = -1100001,
    SAY_SPYBOT_1             = -1100002,
    SAY_GUARD_1              = -1100003,
    SAY_SPYBOT_2             = -1100004,
    SAY_SPYBOT_3             = -1100005,
    SAY_LESCOVAR_1           = -1100006,
    SAY_SPYBOT_4             = -1100007,

    NPC_PRIESTESS_TYRIONA    = 7779
    
};

struct MANGOS_DLL_DECL npc_tyrion_spybotAI : public npc_escortAI
{
    npc_tyrion_spybotAI(Creature* pCreature) : npc_escortAI(pCreature) {Reset();}

    uint32 uiTimer;
        uint32 uiPhase;

        void Reset()
        {
            uiTimer = 0;
            uiPhase = 0;
        }

        void WaypointReached(uint32 uiPointId)
        {
            switch(uiPointId)
            {
                case 1:
                    SetEscortPaused(true);
                    uiTimer = 2000;
                    uiPhase = 1;
                    break;
                case 5:
                    SetEscortPaused(true);
                    DoScriptText(SAY_SPYBOT_1, m_creature);
                    uiTimer = 2000;
                    uiPhase = 5;
                    break;
                case 17:
                    SetEscortPaused(true);
                    DoScriptText(SAY_SPYBOT_3, m_creature);
                    uiTimer = 3000;
                    uiPhase = 8;
                    break;
            }
        }
        void UpdateEscortAI(const uint32 uiDiff)
        {
            if (uiPhase)
            {
                if (uiTimer <= uiDiff)
                {
                     switch(uiPhase)
                    {
                        case 1:
                            DoScriptText(SAY_QUEST_ACCEPT_ATTACK, m_creature);
                            uiTimer = 3000;
                            uiPhase = 2;
                            break;
                        case 2:
                            if (Creature* pTyrion =GetClosestCreatureWithEntry(m_creature,NPC_TYRION, 30.0f))  
                                DoScriptText(SAY_TYRION_1, pTyrion);
                            uiTimer = 3000;
                            uiPhase = 3;
                            break;
                        case 3:
                            m_creature->UpdateEntry(NPC_PRIESTESS_TYRIONA, ALLIANCE);
                            uiTimer = 2000;
                            uiPhase = 4;
                            break;
                        case 4:
                           SetEscortPaused(false);
                           uiPhase = 0;
                           uiTimer = 0;
                           break;
                        case 5:
                            if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature,NPC_STORMWIND_ROYAL, 10.0f)) 
                                DoScriptText(SAY_GUARD_1, pGuard);
                            uiTimer = 3000;
                            uiPhase = 6;
                            break;
                        case 6:
                            DoScriptText(SAY_SPYBOT_2, m_creature);
                            uiTimer = 3000;
                            uiPhase = 7;
                            break;
                        case 7:
                            SetEscortPaused(false);
                            uiTimer = 0;
                            uiPhase = 0;
                            break;
                        case 8:
                            if (Creature* pLescovar = GetClosestCreatureWithEntry(m_creature,NPC_LORD_GREGOR_LESCOVAR, 10.0f))  
                                DoScriptText(SAY_LESCOVAR_1, pLescovar);
                            uiTimer = 3000;
                            uiPhase = 9;
                            break;
                        case 9:
                            DoScriptText(SAY_SPYBOT_4, m_creature);
                            uiTimer = 3000;
                            uiPhase = 10;
                            break;
                        case 10:
                            if (Creature* pLescovar = GetClosestCreatureWithEntry(m_creature,NPC_LORD_GREGOR_LESCOVAR, 10.0f))
                            {
                                if (Player* pPlayer = GetPlayerForEscort())
                               {
                                    if (npc_lord_gregor_lescovarAI* pEscortAI = dynamic_cast<npc_lord_gregor_lescovarAI*>(pLescovar->AI()))
                                        pEscortAI->Start(true, pPlayer->GetGUID());
                                    
                                }
                            }
                            m_creature->ForcedDespawn(10);
                            uiTimer = 0;
                            uiPhase = 0;
                            break;
                    }
                } else uiTimer -= uiDiff;
            }
        }

};

CreatureAI* GetAI_npc_tyrion_spybotAI(Creature* pCreature)
{
    return new npc_tyrion_spybotAI(pCreature);
}
/*######
## npc_tyrion
######*/

enum 
{
    NPC_TYRION_SPYBOT = 8856
};

bool QuestAccept_npc_tyrion(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_THE_ATTACK)
    {
        if(Creature* pTyrionSpybot = GetClosestCreatureWithEntry(pCreature,NPC_TYRION_SPYBOT, 10.0f))
        {
            if (npc_tyrion_spybotAI* pEscortAI = dynamic_cast<npc_tyrion_spybotAI*>(pTyrionSpybot->AI()))
             {                         
                pEscortAI->Start(true, pPlayer->GetGUID(), pQuest);
            }
            return true;
        }
    }
    return true;
};

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

    newscript = new Script;
    newscript->Name = "npc_lord_gregor_lescovar";
    newscript->GetAI = &GetAI_npc_lord_gregor_lescovarAI;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_marzon_silent_blade";
    newscript->GetAI = &GetAI_npc_marzon_silent_bladeAI;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tyrion_spybot";
    newscript->GetAI = &GetAI_npc_tyrion_spybotAI;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tyrion";
    newscript->pQuestAccept = &QuestAccept_npc_tyrion;
    newscript->RegisterSelf();
}
