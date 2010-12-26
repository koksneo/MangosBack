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
SDName: Dragonblight
SD%Complete: 100
SDComment: Quest support: 12166, 12499/12500(end sequenze). Taxi paths Wyrmrest temple.
SDCategory: Dragonblight
EndScriptData */

/* ContentData
go_abbey_bell_rope
npc_abbot_to_escort
npc_abbot_landgren
npc_afrasastrasz
npc_alexstrasza_wr_gate
mob_maggot
npc_liquid_fire_of_elune
npc_tariolstrasz
npc_torastrasza
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## go_abbey_bell_rope
######*/

enum
{
    NPC_ONSLAUGHT_RAVEN_PRIEST          = 27202,
    SOUND_NORTHSHIRE_BELL               = 7256,

    SAY_AFTER_BELL_RANG                 = -1999850,
    SAY_HIGH_ABBOT_BEGINING             = -1999849,
    SAY_HIGH_ABBOT_CLIFF_1              = -1999848,
    SAY_HIGH_ABBOT_CLIFF_2              = -1999847,
    SAY_HIGH_ABBOT_CLIFF_3              = -1999846,
    SAY_HIGH_ABBOT_CLIFF_4              = -1999845,
    SAY_HIGH_ABBOT_CLIFF_5              = -1999844,

    SPELL_KILL_ABBOT_CREDIT             = 48771,
    SPELL_ABBOT_RIDE_VEHICLE            = 48773,
    SPELL_KISSED_RING                   = 48756,
    SPELL_SUMMON_ABBOT_FORCED_CAST      = 48759,
    SPELL_BELL_RANG                     = 48753,
    
    GOSSIP_TEXTID_1                     = 12848,
    GOSSIP_TEXTID_2                     = 12849,

    QUEST_A_FALL_FROM_GREACE            = 12274,

    NPC_ABBOT                           = 27439
};

bool GOHello_go_abbey_bell_rope(Player* pPlayer, GameObject* pGo)
{
    if (!pGo || !pPlayer)
        return false;

    pPlayer->CastSpell(pPlayer,SPELL_BELL_RANG,true);
    pGo->PlayDirectSound(SOUND_NORTHSHIRE_BELL);
    if (Creature* pPriest = GetClosestCreatureWithEntry(pGo,NPC_ONSLAUGHT_RAVEN_PRIEST,INTERACTION_DISTANCE*2))
    {
        pPriest->SetFacingToObject(pPlayer);
        DoScriptText(SAY_AFTER_BELL_RANG,pPriest);
    }
    return false;
}

/*######
## npc_abbot_to_escort
######*/

struct MANGOS_DLL_DECL npc_abbot_to_escortAI : public npc_escortAI
{
    npc_abbot_to_escortAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    uint32 PointStarted;
    uint8  subevent;
    uint32 m_uiEvent_Timer;
    bool bReady;

    void Reset()
    {
        bReady = true;
        PointStarted = 0;
        subevent = 0;
        m_uiEvent_Timer = 0;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!bReady || !pWho)
            return;

        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;

        if ((pWho->GetGUID() == pPlayer->GetGUID()) && (m_creature->GetDistance(pPlayer)<= INTERACTION_DISTANCE))
        {
            // Don't know why crashing server : / so temp removed
            //m_creature->SetVisibility(VISIBILITY_ON);
            bReady = false;
        }
    }

    void WaypointReached(uint32 uiPointId) {}
    void WaypointStart(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 10:
                m_uiEvent_Timer = 0;
            case 0:
                subevent = 0;
                break;
            default: break;
        }
        PointStarted = uiPointId;
    }
    void UpdateEscortAI(const uint32 uiDiff)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer || bReady)
            return;

        if (m_uiEvent_Timer <= uiDiff)
        {
            switch (PointStarted)
            {
                case 0:
                    switch (subevent)
                    {
                        // Abbot speaks few secounds after emerging
                        case 0: SetEscortPaused(true); break;
                        case 1:
                            m_creature->SetFacingToObject(pPlayer);
                            DoScriptText(SAY_HIGH_ABBOT_BEGINING, m_creature);
                            break;
                        case 2: SetEscortPaused(false); break;
                        
                        default: break;
                    }
                    break;
                case 10:
                    switch (subevent)
                    {
                        case 0: SetEscortPaused(true); break;
                        case 1: m_creature->SetFacingToObject(pPlayer);
                            DoScriptText(SAY_HIGH_ABBOT_CLIFF_1, m_creature, pPlayer); break;
                        case 2: DoScriptText(SAY_HIGH_ABBOT_CLIFF_2, m_creature, pPlayer); break;
                        case 3: DoScriptText(SAY_HIGH_ABBOT_CLIFF_3 ,m_creature, pPlayer); break;
                        case 4: DoScriptText(SAY_HIGH_ABBOT_CLIFF_4, m_creature, pPlayer); break;
                        case 5: 
                            DoScriptText(SAY_HIGH_ABBOT_CLIFF_5, m_creature, pPlayer);
                            // pPlayer->CastSpell(pPlayer, SPELL_KILL_ABBOT_CREDIT, true);
                            // Hack - SPELL_KILL_ABBOT_CREDIT is not working
                            pPlayer->KilledMonsterCredit(27444, m_creature->GetGUID());
                            // DoCast(m_creature,SPELL_ABBOT_RIDE_VEHICLE,true);
                            // Hack - SPELL_ABBOT_RIDE_VEHICLE is not working
                            m_creature->KnockBackFrom(pPlayer, 12.0f, 12.0f);
                            break;
                        case 6: m_creature->ForcedDespawn();
                        default: break;
                    }
                    break;
                default: break;
            }
            ++subevent;
            m_uiEvent_Timer = 5000;
        }else m_uiEvent_Timer -= uiDiff;
    }
};

/*######
## npc_abbot_landgren
######*/

#define GOSSIP_ITEM_ABBOT_1     "Your eminence, may I have a word in private?"
#define GOSSIP_ITEM_ABBOT_2     "I am ready, your grace. <kiss the ring>"
float Abbot[] = {2827.27f, -447.32f, 119.62f, 1.68f};

bool GossipHello_npc_abbot_landgren(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_A_FALL_FROM_GREACE) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ABBOT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_abbot_landgren(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ABBOT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_1, pCreature->GetGUID());
        // SPELL_KISSED_RING does not work
        // pPlayer->CastSpell(pCreature,SPELL_KISSED_RING,true);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_2, pCreature->GetGUID());

        // DoCast(pCreature,SPELL_SUMMON_ABBOT_FORCED_CAST,true);
        // Hack - SPELL_SUMMON_ABBOT_FORCED_CAST is not supported
        if (Creature* pAbbot = pPlayer->SummonCreature(NPC_ABBOT, Abbot[0], Abbot[1], Abbot[2], Abbot[3], TEMPSUMMON_CORPSE_DESPAWN, 0))
        {
            if (npc_abbot_to_escortAI* pEscortAI = dynamic_cast<npc_abbot_to_escortAI*>(pAbbot->AI()))
            {
                pEscortAI->Start(false, pPlayer->GetGUID());
                pEscortAI->SetEscortPaused(true);
                // Don't know why crashing server : / so temp removed
                //pAbbot->SetVisibility(VISIBILITY_OFF);
            }
        }
    }
    return true;
}
CreatureAI* GetAI_npc_abbot_to_escort(Creature* pCreature)
{
    return new npc_abbot_to_escortAI(pCreature);
}
     
enum
{
    TAXI_PATH_ID_MIDDLE_DOWN            = 882,
    TAXI_PATH_ID_MIDDLE_TOP             = 881
};

#define GOSSIP_ITEM_TAXI_MIDDLE_DOWN    "I would like to take a flight to the ground, Lord Of Afrasastrasz."
#define GOSSIP_ITEM_TAXI_MIDDLE_TOP     "My Lord, I must go to the upper floor of the temple."

bool GossipHello_npc_afrasastrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_MIDDLE_DOWN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_MIDDLE_TOP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_afrasastrasz(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_MIDDLE_DOWN);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_MIDDLE_TOP);
    }
    return true;
}

/*######
## npc_alexstrasza_wr_gate
######*/

enum
{
    QUEST_RETURN_TO_AG_A    = 12499,
    QUEST_RETURN_TO_AG_H    = 12500,
    MOVIE_ID_GATES          = 14
};

#define GOSSIP_ITEM_WHAT_HAPPENED   "Alexstrasza, can you show me what happened here?"

bool GossipHello_npc_alexstrasza_wr_gate(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_A) || pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_H))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_alexstrasza_wr_gate(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->SendMovieStart(MOVIE_ID_GATES);
    }

    return true;
}

/*######
/*######
## mob_maggot
######*/
#define NPC_BLOODFEAST       27008

struct MANGOS_DLL_DECL mob_maggotAI : public ScriptedAI
{
    mob_maggotAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset() {}

    void DamageDeal(Unit* pDoneTo, uint32& uiDamage)
    {
        if (!pDoneTo || !uiDamage)
            return;

        if (Creature* pBloodfeast = GetClosestCreatureWithEntry(m_creature, NPC_BLOODFEAST, INTERACTION_DISTANCE*2))
            if (pBloodfeast->GetHealth() < pBloodfeast->GetMaxHealth())
                pBloodfeast->SetHealth(pBloodfeast->GetHealth()+ uiDamage);
    }
};
CreatureAI* GetAI_mob_maggot(Creature* pCreature)
{
    return new mob_maggotAI(pCreature);
}
/*#####
## npc_tariolstrasz
######*/

enum
{
    QUEST_INFORM_QUEEN_A                = 12123,            //need to check if quests are required before gossip available
    QUEST_INFORM_QUEEN_H                = 12124,
    TAXI_PATH_ID_BOTTOM_TOP             = 878,
    TAXI_PATH_ID_BOTTOM_MIDDLE          = 883
};

#define GOSSIP_ITEM_TAXI_BOTTOM_TOP     "My Lord, I must go to the upper floor of the temple."
#define GOSSIP_ITEM_TAXI_BOTTOM_MIDDLE  "Can you spare a drake to travel to Lord Of Afrasastrasz, in the middle of the temple?"

bool GossipHello_npc_tariolstrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_BOTTOM_TOP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_BOTTOM_MIDDLE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tariolstrasz(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_BOTTOM_TOP);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_BOTTOM_MIDDLE);
    }
    return true;
}

/*######
## npc_torastrasza
######*/

enum
{
    TAXI_PATH_ID_TOP_MIDDLE             = 880,
    TAXI_PATH_ID_TOP_BOTTOM             = 879
};

#define GOSSIP_ITEM_TAXI_TOP_MIDDLE     "I would like to see Lord Of Afrasastrasz, in the middle of the temple."
#define GOSSIP_ITEM_TAXI_TOP_BOTTOM     "Yes, Please. I would like to return to the ground floor of the temple."

bool GossipHello_npc_torastrasza(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_TOP_MIDDLE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAXI_TOP_BOTTOM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_torastrasza(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_TOP_MIDDLE);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->ActivateTaxiPathTo(TAXI_PATH_ID_TOP_BOTTOM);
    }
    return true;
}

void AddSC_dragonblight()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_abbey_bell_rope";
    newscript->pGOHello = &GOHello_go_abbey_bell_rope;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_abbot_landgren";
    newscript->pGossipHello = &GossipHello_npc_abbot_landgren;
    newscript->pGossipSelect = &GossipSelect_npc_abbot_landgren;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "npc_abbot_to_escort";
    newscript->GetAI = &GetAI_npc_abbot_to_escort;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_afrasastrasz";
    newscript->pGossipHello = &GossipHello_npc_afrasastrasz;
    newscript->pGossipSelect = &GossipSelect_npc_afrasastrasz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_alexstrasza_wr_gate";
    newscript->pGossipHello = &GossipHello_npc_alexstrasza_wr_gate;
    newscript->pGossipSelect = &GossipSelect_npc_alexstrasza_wr_gate;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_maggot";
    newscript->GetAI = &GetAI_mob_maggot;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tariolstrasz";
    newscript->pGossipHello = &GossipHello_npc_tariolstrasz;
    newscript->pGossipSelect = &GossipSelect_npc_tariolstrasz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_torastrasza";
    newscript->pGossipHello = &GossipHello_npc_torastrasza;
    newscript->pGossipSelect = &GossipSelect_npc_torastrasza;
    newscript->RegisterSelf();
}
