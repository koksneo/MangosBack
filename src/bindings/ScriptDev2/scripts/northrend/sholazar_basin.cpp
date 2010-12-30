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
SDName: Sholazar_Basin
SD%Complete: 100
SDComment: Quest support: 12573
SDCategory: Sholazar Basin
EndScriptData */

/* ContentData
mob_rjr_target
npc_vekjik
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## mob_rjr_target
######*/

enum rjr_target
{
    NPC_WILHELM             = 28054,
    NPC_DROSTAN             = 28328,

    SPELL_HIT_APPLE         = 51331,
    SPELL_HIT_BIRD          = 51366,
    SPELL_HIT_WILHELM       = 51332,
    SPELL_BIRD_FALL         = 51369,
    SPELL_APPLE_FALL        = 51371
};

int DrostanText[] = {-1999835,-1999833,-1999831,-1999830};
int WilhelmText[] = {-1999836,-1999834,-1999832,-1999829};

struct MANGOS_DLL_DECL mob_rjr_targetAI : public ScriptedAI
{
    mob_rjr_targetAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bResponce;
    uint32 m_uiResponceTimer;

    void Reset() 
    {
        bResponce = false;
        m_uiResponceTimer = 2000;
    }

    void SpellHit(Unit* pCaster, const SpellEntry *pSpell)
    {
        if (!pCaster || pCaster->GetTypeId() != TYPEID_PLAYER || !pSpell || !m_creature->isAlive())
            return;

        switch (pSpell->Id)
        {
            case SPELL_HIT_APPLE:
                if (Unit* pWilhelm = GetClosestCreatureWithEntry(m_creature, NPC_WILHELM, 30.0f))
                    DoScriptText(WilhelmText[3], pWilhelm, pCaster);
                DoCastSpellIfCan(m_creature, SPELL_APPLE_FALL, CAST_TRIGGERED);
                ((Player*)pCaster)->KilledMonsterCredit(m_creature->GetEntry(), m_creature->GetGUID());
                m_creature->ForcedDespawn();
                break;
            case SPELL_HIT_BIRD:
                if (Unit* pDrostan = GetClosestCreatureWithEntry(m_creature, NPC_DROSTAN, 30.0f))
                    DoScriptText(DrostanText[3], pDrostan ,m_creature);
                DoCastSpellIfCan(m_creature, SPELL_BIRD_FALL, CAST_TRIGGERED);
                break;
            case SPELL_HIT_WILHELM:
                DoScriptText(WilhelmText[urand(0, 2)], m_creature);
                bResponce = true;
                break;
                
            default: break;
        }
    }

    void UpdateAI (uint32 const uiDiff)
    {
        if (bResponce)
            if (Unit* pDrostan = GetClosestCreatureWithEntry(m_creature, NPC_DROSTAN, 30.0f))
                if (m_uiResponceTimer <= uiDiff)
                {
                    DoScriptText(DrostanText[urand(0, 2)], pDrostan, m_creature);
                    m_uiResponceTimer = 2000;
                    bResponce = false;
                }
                else
                    m_uiResponceTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_rjr_target(Creature* pCreature)
{
    return new mob_rjr_targetAI(pCreature);
}

/*######
## npc_vekjik
######*/

#define GOSSIP_VEKJIK_ITEM1 "Shaman Vekjik, I have spoken with the big-tongues and they desire peace. I have brought this offering on their behalf."
#define GOSSIP_VEKJIK_ITEM2 "No no... I had no intentions of betraying your people. I was only defending myself. it was all a misunderstanding."

enum
{
    GOSSIP_TEXTID_VEKJIK1       = 13137,
    GOSSIP_TEXTID_VEKJIK2       = 13138,

    SAY_TEXTID_VEKJIK1          = -1000208,

    SPELL_FREANZYHEARTS_FURY    = 51469,

    QUEST_MAKING_PEACE          = 12573
};

bool GossipHello_npc_vekjik(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_MAKING_PEACE) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_vekjik(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            DoScriptText(SAY_TEXTID_VEKJIK1, pCreature, pPlayer);
            pPlayer->AreaExploredOrEventHappens(QUEST_MAKING_PEACE);
            pCreature->CastSpell(pPlayer, SPELL_FREANZYHEARTS_FURY, false);
            break;
    }

    return true;
}

/*######
## npc_injured_oracle
######*/

enum InjuredOracle
{
    SAY_ESCORT_READY                    = -1999795,
    SAY_ESCORT_START                    = -1999794,
    SAY_ESCORT_FINISHED                 = -1999793,
    SAY_AFTER_ESCORT                    = -1999792,

    SPELL_QUEST_READY                   = 53807,
    SPELL_ESCORT_START                  = 51341,

    QUEST_FORTUNATE_MISUNDERSTANDINGS   = 12570
};

#define GOSSIP_INJURED_ORACLE "I am ready to travel to your village now."

struct MANGOS_DLL_DECL npc_injured_oracleAI : public npc_escortAI
{
    npc_injured_oracleAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    void Reset(){}
    void WaypointReached(uint32 uiPointId) 
    {
        switch(uiPointId)
        {
            case 24:
                DoScriptText(SAY_ESCORT_FINISHED, m_creature);
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->AreaExploredOrEventHappens(QUEST_FORTUNATE_MISUNDERSTANDINGS);
                break;
            case 25:
                DoScriptText(SAY_AFTER_ESCORT, m_creature);
                break;
            default: break;
        }
    }
};

CreatureAI* GetAI_npc_injured_oracle(Creature* pCreature)
{
    return new npc_injured_oracleAI(pCreature);
}

bool GossipHello_npc_injured_oracle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTANDINGS) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_INJURED_ORACLE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_injured_oracle(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (npc_injured_oracleAI* pEscortAI = dynamic_cast<npc_injured_oracleAI*>(pCreature->AI()))
        {
            pCreature->RemoveAllAuras();
            pEscortAI->Start(false, pPlayer->GetGUID());
            pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_ACTIVE);
            DoScriptText(SAY_ESCORT_START, pCreature);
            // dunno exactly what should this spell do
            //pPlayer->CastSpell(pCreature, SPELL_ESCORT_START, true);
        }
    }
    return true;
}

bool QuestAccept_fortunate_misunderstandings(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FORTUNATE_MISUNDERSTANDINGS)
    {
        // dunno exactly what should this spell do
        // pCreature->CastSpell(pCreature, SPELL_QUEST_READY, true);
        
        DoScriptText(SAY_ESCORT_READY, pCreature);
    }
    return true;
}

enum TasteTest
{
    SPELL_OFFER_JUNGLE_PUNCH    = 51962,

    NPC_HEMET_NESINGWAY         = 27986,
    NPC_HADRIUS_HARLOWE         = 28047,
    NPC_TAMARA_WOBBLESPROCKET   = 28568
};

int32 HemetText[3] = {-1999791, -1999790, -1999789};
int32 HadriusText[3] = {-1999788, -1999787, -1999786};
int32 TamaraText[3] = {-1999785, -1999784, -1999783};

struct MANGOS_DLL_DECL mob_taste_testAI : public ScriptedAI
{
    mob_taste_testAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bTasteing;
    uint8 Phase;
    uint32 m_uiEventTimer;
    uint64 m_uiPlayersGUID;

    void Reset() 
    {
        bTasteing = false;
        Phase = 0;
        m_uiPlayersGUID = 0;
        m_uiEventTimer = 5000;
    }

    void UpdateAI (const uint32 uiDiff)
    {
        if (bTasteing)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_HEMET_NESINGWAY: DoScriptText(HemetText[Phase], m_creature); break;
                    case NPC_HADRIUS_HARLOWE: DoScriptText(HadriusText[Phase], m_creature); break;
                    case NPC_TAMARA_WOBBLESPROCKET: DoScriptText(TamaraText[Phase], m_creature); break;
                    default: break;
                }
                if (Phase == 2)
                {
                    if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayersGUID))
                        pPlayer->KilledMonsterCredit(m_creature->GetEntry(), m_creature->GetGUID());
                    Reset();
                    return;
                }
                ++Phase;
                m_uiEventTimer = 5000;
            } else m_uiEventTimer -= uiDiff;
        }
    }
};

bool EffectDummyCreature_mob_taste_test(Unit *pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature *pCreatureTarget)
{
    if (spellId == SPELL_OFFER_JUNGLE_PUNCH && effIndex == EFFECT_INDEX_1 && pCaster->GetTypeId() == TYPEID_PLAYER && pCreatureTarget)
    {
        if (pCreatureTarget->AI())
        {
            ((mob_taste_testAI*)pCreatureTarget->AI())->bTasteing = true;
            ((mob_taste_testAI*)pCreatureTarget->AI())->m_uiPlayersGUID = pCaster->GetGUID();
        }
    }
    return true;
}

CreatureAI* GetAI_mob_taste_test(Creature* pCreature)
{
    return new mob_taste_testAI(pCreature);
}

#define GOSSIP_TIPSY_MCMANUS "I am ready to start the event."
/*##################################
#Quest Still at it - Tipsy McManus #
###################################*/ 
enum
{
    QUEST_STILL_AT_IT = 12644,
    SAY_EVENT_STARTED = -1760000,
    SAY_ADD_BANNANAS  = -1760001,
    SAY_ADD_PAPAYA    = -1760002,
    SAY_GOOD_JOB_1    = -1760003,
    SAY_BRAZIER       = -1760004,
    SAY_GOOD_JOB_2    = -1760005,
    SAY_OPEN_VALVE    = -1760006,
    SAY_GOOD_JOB_3    = -1760007,
    SAY_GOOD_JOB_4    = -1760008,
    SAY_EVENT_END     = -1760009,
    SAY_ADD_ORANGE    = -1760010,
    SAY_FAIL        = -1760011,
    GO_JUNGLE_PUNCH   =  190643
};
int32 GoogJobText[4] = {SAY_GOOD_JOB_1,SAY_GOOD_JOB_2,SAY_GOOD_JOB_3,SAY_GOOD_JOB_4};
struct MANGOS_DLL_DECL npc_tipsy_mcmanusAI : public ScriptedAI
{
    npc_tipsy_mcmanusAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bEventCanBeStarted;
    bool bEventStarted;
    uint32 m_uiStepTimer;
    uint32 m_uiEventStartTimer;
    uint32 uiPhase;
    uint32 uiObjectToClick;
    uint32 uiCurrentClickedObject;
    uint32 uiPhaseCounter;
    /*
       banana         = 1
       orange         = 2
       papaya         = 3
       pressure valve = 4
       brazier        = 5

    */ 
    void Reset() 
    {
        bEventCanBeStarted      = false;
        bEventStarted           = false;
        m_uiStepTimer           = 10000;
        m_uiEventStartTimer     = 5000;
        uiPhase                 = 0;
        uiObjectToClick         = 0;
        uiCurrentClickedObject  = 0;
        uiPhaseCounter          = 0;
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    bool CheckClickedObject(uint32 uiObjectToClick)
    {
        if(uiObjectToClick == uiCurrentClickedObject)
            return true;
        
        else return false;

    }
    void SayEventText(uint32 uiTextIdentifier)
    {
        switch(uiTextIdentifier)
        {
            case 1: DoScriptText(SAY_ADD_BANNANAS, m_creature); break;
            case 2: DoScriptText(SAY_ADD_ORANGE, m_creature);   break;
            case 3: DoScriptText(SAY_ADD_PAPAYA, m_creature);   break;
            case 4: DoScriptText(SAY_OPEN_VALVE, m_creature);   break;
            case 5: DoScriptText(SAY_BRAZIER, m_creature);      break;
            default: break;
        }
    }

    void UpdateAI (uint32 const uiDiff)
    {
        if (bEventCanBeStarted)
        {
                if (m_uiEventStartTimer <= uiDiff && !bEventStarted)
                {
                    uiObjectToClick = urand(1,3);
                    SayEventText(uiObjectToClick);
                    m_uiEventStartTimer = 0;
                    bEventStarted = true;
                    uiPhase++;
                }
                else m_uiEventStartTimer -= uiDiff;

                if(bEventStarted)
                {
                    if (m_uiStepTimer <=uiDiff)
                    {
                        switch(uiPhase)
                        {
                            case 1:
                                if(CheckClickedObject(uiObjectToClick))
                                {
                                    DoScriptText(GoogJobText[urand(0,3)] , m_creature);
                                    uiObjectToClick = urand(1,3); 
                                    SayEventText(uiObjectToClick);
                                    
                                    uiPhaseCounter++;
                                    if(uiPhaseCounter == 3){ uiPhase++; uiPhaseCounter=0;}
                                }
                                else {Reset(); DoScriptText(SAY_FAIL, m_creature);}
                                break;
                               
                             case 2: 
                                if(CheckClickedObject(uiObjectToClick))
                                {
                                    DoScriptText(GoogJobText[urand(0,3)] , m_creature);
                                    uiObjectToClick = urand(4,5);
                                    SayEventText(uiObjectToClick);
                                    uiPhase++; 
                                }
                                else {Reset(); DoScriptText(SAY_FAIL, m_creature);}
                                break;
                             case 3: 
                                 if(CheckClickedObject(uiObjectToClick))
                                 {
                                    DoScriptText(GoogJobText[urand(0,3)] , m_creature);
                                    uiObjectToClick = urand(1,5);
                                    SayEventText(uiObjectToClick);
                                    uiPhaseCounter++;
                                    if(uiPhaseCounter == 6)uiPhase++;
                                 }
                                 else {Reset(); DoScriptText(SAY_FAIL, m_creature);}
                                 break;
                             case 4: 
                                 DoScriptText(SAY_EVENT_END , m_creature); 
                                 if(GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, GO_JUNGLE_PUNCH, 15.0f))
                                 {
                                     pGo->SetRespawnTime(3*MINUTE);        //despawn object in ? seconds
                                     pGo->Respawn();
                                  
                                     Reset();
                                 }
                                 break; 
                                
                             default: break;

                        }
                        m_uiStepTimer=5000;
                    }
                    else m_uiStepTimer -=uiDiff;

                }
        }
    }
};

CreatureAI* GetAI_npc_tipsy_mcmanus(Creature* pCreature)
{
    return new npc_tipsy_mcmanusAI(pCreature);
};

bool GossipHello_npc_tipsy_mcmanus(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_STILL_AT_IT) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TIPSY_MCMANUS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tipsy_mcmanus(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (npc_tipsy_mcmanusAI* pTipsyAI = dynamic_cast<npc_tipsy_mcmanusAI*>(pCreature->AI()))
        {
            pTipsyAI->bEventCanBeStarted=true;
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            DoScriptText(SAY_EVENT_STARTED, pCreature);
        }
    }
    return true;
}

/*################################
#Quest Still at it - gameobjects #
#################################*/ 
enum
{
    GO_BARREL_OF_ORANGES           =  190637,
    GO_BARREL_OF_PAPAYAS           =  190639,
    GO_BARREL_OF_BANANAS           =  190638,
    GO_PRESSURE_VALVE              =  190635,
    GO_BRAZIER                     =  190636,
    NPC_TIPSY_MCMANUS              =  28566,
};

bool GOHello_go_still_at_it_quest(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_STILL_AT_IT) == QUEST_STATUS_INCOMPLETE)
    {
        if(Creature* pTipsy = GetClosestCreatureWithEntry(pPlayer, NPC_TIPSY_MCMANUS, 30.0f))
        {
            if (npc_tipsy_mcmanusAI* pTipsyAI = dynamic_cast<npc_tipsy_mcmanusAI*>(pTipsy->AI()))
            {
                 switch (pGo->GetEntry())
                {
                    case GO_BARREL_OF_ORANGES: pTipsyAI->uiCurrentClickedObject = 2; break;
                    case GO_BARREL_OF_PAPAYAS: pTipsyAI->uiCurrentClickedObject = 3; break;
                    case GO_BARREL_OF_BANANAS: pTipsyAI->uiCurrentClickedObject = 1; break;
                    case GO_PRESSURE_VALVE:    pTipsyAI->uiCurrentClickedObject = 4; break;
                    case GO_BRAZIER:           pTipsyAI->uiCurrentClickedObject = 5; break;
                    
                        break;
                }
            }
        }
    }
    return false;
};

void AddSC_sholazar_basin()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mob_taste_test";
    newscript->GetAI = &GetAI_mob_taste_test;
    newscript->pEffectDummyCreature = &EffectDummyCreature_mob_taste_test;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_rjr_target";
    newscript->GetAI = &GetAI_mob_rjr_target;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_injured_oracle";
    newscript->GetAI = &GetAI_npc_injured_oracle;
    newscript->pQuestAccept = &QuestAccept_fortunate_misunderstandings;
    newscript->pGossipHello = &GossipHello_npc_injured_oracle;
    newscript->pGossipSelect = &GossipSelect_npc_injured_oracle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_vekjik";
    newscript->pGossipHello = &GossipHello_npc_vekjik;
    newscript->pGossipSelect = &GossipSelect_npc_vekjik;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_still_at_it_quest";
    newscript->pGOHello = &GOHello_go_still_at_it_quest;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tipsy_mcmanus";
    newscript->GetAI = &GetAI_npc_tipsy_mcmanus;
    newscript->pGossipHello = &GossipHello_npc_tipsy_mcmanus;
    newscript->pGossipSelect = &GossipSelect_npc_tipsy_mcmanus;
    newscript->RegisterSelf();
}
