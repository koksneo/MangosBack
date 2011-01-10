/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDComment: Quest support: 12573, 12570, 12580
SDCategory: Sholazar Basin
EndScriptData */

/* ContentData
npc_injured_rainspeaker
npc_mosswalker_victim
npc_vekjik - TODO, can be moved to database (already exist)
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_injured_rainspeaker
######*/

enum
{
    QUEST_FORTUNATE_MISUNDERSTAND       = 12570,

    GOSSIP_ITEM_READY                   = -3000103,

    SAY_ACCEPT                          = -1000605,
    SAY_START                           = -1000606,
    SAY_END_1                           = -1000607,
    SAY_END_2                           = -1000608,
    SAY_TRACKER                         = -1000609,

    NPC_FRENZYHEART_TRACKER             = 28077,

    SPELL_FEIGN_DEATH                   = 51329,
    SPELL_ORACLE_INTRO                  = 51448,
};

// TODO: add, if faction change is expected.
struct MANGOS_DLL_DECL npc_injured_rainspeakerAI : public npc_escortAI
{
    npc_injured_rainspeakerAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    void Reset() { }

    void JustStartedEscort()
    {
        if (Player* pPlayer = GetPlayerForEscort())
            DoScriptText(SAY_START, m_creature, pPlayer);
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 22:
            {
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    DoScriptText(SAY_END_1, m_creature, pPlayer);
                    // more likely m_creature->player, doesn't seem to work though.
                    pPlayer->CastSpell(pPlayer, SPELL_ORACLE_INTRO, true);
                }
                break;
            }
            case 23:
            {
                DoScriptText(SAY_END_2, m_creature);

                // location behind
                float fAngle = m_creature->GetOrientation();
                fAngle += M_PI_F;

                float fX, fY, fZ;
                m_creature->GetNearPoint(m_creature, fX, fY, fZ, 0.0f, 15.0f, fAngle);

                m_creature->SummonCreature(NPC_FRENZYHEART_TRACKER, fX, fY, fZ, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 30000);
                break;
            }
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        DoScriptText(SAY_TRACKER, pSummoned);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_injured_rainspeaker(Creature* pCreature)
{
    return new npc_injured_rainspeakerAI(pCreature);
}

bool QuestAccept_npc_injured_rainspeaker(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FORTUNATE_MISUNDERSTAND)
    {
        pCreature->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
        DoScriptText(SAY_ACCEPT, pCreature, pPlayer);

        // Workaround, GossipHello/GossipSelect doesn't work well when object already has gossip from database
        if (npc_injured_rainspeakerAI* pEscortAI = dynamic_cast<npc_injured_rainspeakerAI*>(pCreature->AI()))
            pEscortAI->Start(true, pPlayer->GetGUID(), pQuest);
    }

    return false;
}

/*
bool GossipHello_npc_injured_rainspeaker(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTAND) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_READY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    return false;
}

bool GossipSelect_npc_injured_rainspeaker(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_injured_rainspeakerAI* pEscortAI = dynamic_cast<npc_injured_rainspeakerAI*>(pCreature->AI()))
            pEscortAI->Start(true, pPlayer->GetGUID());
    }

    return false;
}
*/

/*######
## npc_mosswalker_victim
######*/

enum
{
    QUEST_MOSSWALKER_SAVIOR         = 12580,
    SPELL_DEAD_SOLDIER              = 45801,                // not clear what this does, but looks like all have it
    SPELL_MOSSWALKER_QUEST_CREDIT   = 52157,

    GOSSIP_ITEM_PULSE               = -3000104,
    TEXT_ID_INJURED                 = 13318,

    EMOTE_PAIN                      = -1000610,

    SAY_RESCUE_1                    = -1000611,
    SAY_RESCUE_2                    = -1000612,
    SAY_RESCUE_3                    = -1000613,
    SAY_RESCUE_4                    = -1000614,

    SAY_DIE_1                       = -1000615,
    SAY_DIE_2                       = -1000616,
    SAY_DIE_3                       = -1000617,
    SAY_DIE_4                       = -1000618,
    SAY_DIE_5                       = -1000619,
    SAY_DIE_6                       = -1000620,
};

bool GossipHello_npc_mosswalker_victim(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_MOSSWALKER_SAVIOR) == QUEST_STATUS_INCOMPLETE)
    {
        // doesn't appear they always emote
        if (urand(0,3) == 0)
            DoScriptText(EMOTE_PAIN, pCreature);

        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_PULSE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    }

    pPlayer->SEND_GOSSIP_MENU(TEXT_ID_INJURED, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_mosswalker_victim(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        // just to prevent double credit
        if (pCreature->GetLootRecipient())
            return true;
        else
            pCreature->SetLootRecipient(pPlayer);

        if (urand(0,2))                                     // die
        {
            switch(urand(0,5))
            {
                case 0: DoScriptText(SAY_DIE_1, pCreature, pPlayer); break;
                case 1: DoScriptText(SAY_DIE_2, pCreature, pPlayer); break;
                case 2: DoScriptText(SAY_DIE_3, pCreature, pPlayer); break;
                case 3: DoScriptText(SAY_DIE_4, pCreature, pPlayer); break;
                case 4: DoScriptText(SAY_DIE_5, pCreature, pPlayer); break;
                case 5: DoScriptText(SAY_DIE_6, pCreature, pPlayer); break;
            }
        }
        else                                                // survive
        {
            switch(urand(0,3))
            {
                case 0: DoScriptText(SAY_RESCUE_1, pCreature, pPlayer); break;
                case 1: DoScriptText(SAY_RESCUE_2, pCreature, pPlayer); break;
                case 2: DoScriptText(SAY_RESCUE_3, pCreature, pPlayer); break;
                case 3: DoScriptText(SAY_RESCUE_4, pCreature, pPlayer); break;
            }

            pCreature->CastSpell(pPlayer, SPELL_MOSSWALKER_QUEST_CREDIT, true);
        }

        // more details may apply, instead of just despawn
        pCreature->ForcedDespawn(5000);
    }
    return true;
}

/*######
## npc_vekjik - TODO, can be moved to database (already exist)
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

/*######################
# Quest The Taste Test #
######################*/ 

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

/*#######################
# npc_artruis_heartless #
#######################*/ 
enum
{
    SPELL_FROSTBOLT                 = 15530,
    SPELL_ICE_LANCE                 = 54261,
    SPELL_ICY_VEINS                 = 54792,
    SPELL_FROST_NOVA                = 11831,
    SPELL_BINDINGS_OF_SUBMISSION    = 52185,
    GO_ARTRUISS_PYLACTERY           = 190777,
    SAY_AGGRO                       = -1780000,
    EMOTE_SHIELDED                  = -1780001,
    NPC_ZEPIK                       = 28668,
    NPC_JALOOT                      = 28667,

};
struct MANGOS_DLL_DECL npc_artruisAI : public ScriptedAI
{
    npc_artruisAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiFrostboltTimer;
    uint32 m_uiIcyVeinsTimer;
    uint32 m_uiIceLanceTimer;
    uint32 m_uiFrostNovaTimer;
    bool bIsBinded;
    bool bCastedBindings;

    void Reset() 
    {
        m_uiFrostboltTimer = 1000;
        m_uiIceLanceTimer  = 200;
        m_uiFrostNovaTimer = 100;
        m_uiIcyVeinsTimer  = 4500;
        bIsBinded          = false ;
        bCastedBindings    = false ;
        
        m_creature->RemoveAurasDueToSpell(SPELL_BINDINGS_OF_SUBMISSION);        
    }
    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature); 
    }

    void JustDied(Unit* pKiller)
    {
        if(GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, GO_ARTRUISS_PYLACTERY, 60.0f))
            {
                pGo->SetRespawnTime(3*MINUTE);
                pGo->Respawn();
            }
    }
    
    void UpdateAI (uint32 const uiDiff)
    {
        if(m_creature->isInCombat() && !m_creature->getVictim())
        {
            EnterEvadeMode();
        }
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(!bIsBinded)
        {
            if (m_uiIceLanceTimer <= uiDiff)     
            {  
                DoCast(m_creature->getVictim(), SPELL_ICE_LANCE);
                m_uiIceLanceTimer = 7000;                    
            } else m_uiIceLanceTimer -= uiDiff;

            if (m_uiFrostNovaTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_FROST_NOVA);
                m_uiFrostNovaTimer = 14000;                    
            } else m_uiFrostNovaTimer -= uiDiff;

            if (m_uiFrostboltTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_FROSTBOLT);
                m_uiFrostboltTimer = 4000;                    
            } else m_uiFrostboltTimer -= uiDiff;

            if (m_uiIcyVeinsTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_ICY_VEINS);
                m_uiIcyVeinsTimer = 25000;                    
            } else m_uiIcyVeinsTimer -= uiDiff;
            
            if(!bCastedBindings &&(m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 30)
            {
                 m_creature->InterruptNonMeleeSpells(true);
                DoCast(m_creature->getVictim(), SPELL_BINDINGS_OF_SUBMISSION);
                DoScriptText(EMOTE_SHIELDED, m_creature); 
                bCastedBindings = true;
                bIsBinded = true;

            }
        }


    }


};
CreatureAI* GetAI_npc_artruis(Creature* pCreature)
{
    return new npc_artruisAI(pCreature);
} 
/*##################
# npc_jaloot_zepik #
##################*/ 
enum
{
    SPELL_TOMB_OF_HEARTLESS         = 52182,
    SPELL_Z_OPEN_WOUND              = 52873,
    SPELL_Z_SPIKE_TRAP              = 52886,
    SPELL_J_LIGHTNING_WHIRL         = 52943,
    SPELL_J_SPARK_FRENZY            = 52964,
    FACTION_MONSTER                 = 14,
    FACTION_TO_RESTORE              = 250,
    NPC_ARTRUIS_HEARTLESS           = 28659,
};
struct MANGOS_DLL_DECL npc_jaloot_zepikAI : public ScriptedAI
{
    npc_jaloot_zepikAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiZOpenWoundTimer; 
    uint32 m_uiZSpikeTrapTimer; 
    uint32 m_uiJLightningWhirlTimer; 
    uint32 m_uiJSparkFrenzyTimer;
    uint32 m_uiCheckArtruisTimer;

    void Reset() 
    {
        m_creature->setFaction(FACTION_TO_RESTORE);
        m_creature->CastSpell(m_creature, SPELL_TOMB_OF_HEARTLESS,false);
        m_uiZOpenWoundTimer = 2000;
        m_uiZSpikeTrapTimer = 4000;
        m_uiJLightningWhirlTimer = 2000;
        m_uiJSparkFrenzyTimer = 4000;
        m_uiCheckArtruisTimer = 5000;
    }

    void SpellHit(Unit* pCaster, const SpellEntry *pSpell)
    {
        switch (pSpell->Id)
        {
            case 52185: m_creature->RemoveAurasDueToSpell(SPELL_TOMB_OF_HEARTLESS); 
                        if(Creature* pArtruis = GetClosestCreatureWithEntry(m_creature, NPC_ARTRUIS_HEARTLESS, 60.0f))
                         {                             
                                m_creature->Attack( pArtruis->getVictim(),true);
                                m_creature->GetMotionMaster()->MoveChase(pArtruis->getVictim());
                         }
                        m_creature->setFaction(FACTION_MONSTER);
                        break;
        }
    }
    
    void AttackStart(Unit* pWho)
    {
        if(pWho->GetTypeId() == TYPEID_PLAYER)
        {
            switch(m_creature->GetEntry())
            {
                case NPC_ZEPIK: if(Creature* pJaloot = GetClosestCreatureWithEntry(m_creature, NPC_JALOOT, 60.0f))
                                {
                                    pJaloot->AddThreat(m_creature->getVictim(),9999.9f,false);
                                    pJaloot->Attack( m_creature->getVictim(),true);
                                }
                                break;

                case NPC_JALOOT: if(Creature* pZepik = GetClosestCreatureWithEntry(m_creature, NPC_ZEPIK, 60.0f))
                                {
                                      pZepik->AddThreat(m_creature->getVictim(),9999.9f,false);
                                      pZepik->Attack( m_creature->getVictim(),true);
                                }
                                break;

                default: break;
            }   
        }

    }
    void UpdateAI(const uint32 uiDiff)
    {
        if(m_creature->isInCombat())
        {
            if (m_uiCheckArtruisTimer <= uiDiff)     
             { 
             if(Creature* pArtruis = GetClosestCreatureWithEntry(m_creature, NPC_ARTRUIS_HEARTLESS, 30.0f))
             {
                 if(!pArtruis->isAlive())
                     EnterEvadeMode();
             }
                                
        } else m_uiCheckArtruisTimer -= uiDiff;

        }
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_creature->GetEntry())
        {
            case NPC_ZEPIK:
                 Zepik_UpdateAI(uiDiff);
                 break;

            case NPC_JALOOT:
                 Jaloot_UpdateAI(uiDiff);
                 break;
            default: break;
         }

        DoMeleeAttackIfReady();

    }

    void Zepik_UpdateAI(const uint32 uiDiff)
    {
            if (m_uiZOpenWoundTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_Z_OPEN_WOUND);
                m_uiZOpenWoundTimer = 4000;                    
            } else m_uiZOpenWoundTimer -= uiDiff;
            
            if (m_uiZSpikeTrapTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_Z_SPIKE_TRAP);
                m_uiZSpikeTrapTimer = 4000;                    
            } else m_uiZSpikeTrapTimer -= uiDiff;
    }

    void Jaloot_UpdateAI(const uint32 uiDiff)
    {
        if (m_uiJLightningWhirlTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_J_LIGHTNING_WHIRL);
                m_uiJLightningWhirlTimer = 4000;                    
            } else m_uiJLightningWhirlTimer -= uiDiff;
            
            if (m_uiJSparkFrenzyTimer <= uiDiff)     
            { 
                DoCast(m_creature->getVictim(), SPELL_J_SPARK_FRENZY);
                m_uiJSparkFrenzyTimer = 4000;                    
            } else m_uiJSparkFrenzyTimer -= uiDiff;

    }

    void JustDied(Unit* pKiller)
    {
        switch(m_creature->GetEntry())
        {
            case NPC_ZEPIK: if(Creature* pJaloot = GetClosestCreatureWithEntry(m_creature, NPC_JALOOT, 30.0f))
                             {
                                  pJaloot->setFaction(FACTION_TO_RESTORE);
                                  
                                  if(Creature* pArtruis = GetClosestCreatureWithEntry(pJaloot, NPC_ARTRUIS_HEARTLESS, 60.0f))
                                  {
                                      pJaloot->AddThreat(pArtruis, 999999.9f,true);
                                      pJaloot->Attack( pArtruis,true);
                                      m_creature->GetMotionMaster()->MoveChase(pArtruis);
                                      pArtruis->RemoveAurasDueToSpell(SPELL_BINDINGS_OF_SUBMISSION);
                                  }
                             }
                             break;

            case NPC_JALOOT: if(Creature* pZepik = GetClosestCreatureWithEntry(m_creature, NPC_ZEPIK, 60.0f))
                             {
                                  pZepik->setFaction(FACTION_TO_RESTORE);
                                  if(Creature* pArtruis = GetClosestCreatureWithEntry(pZepik, NPC_ARTRUIS_HEARTLESS, 60.0f))
                                  {
                                      pZepik->AddThreat(pArtruis, 999999.9f,true);
                                      pZepik->Attack( pArtruis,true);
                                      m_creature->GetMotionMaster()->MoveChase(pArtruis);
                                      pArtruis->RemoveAurasDueToSpell(SPELL_BINDINGS_OF_SUBMISSION);
                                  }
                             }
                             break;

            default: break;
        }
        if(Creature* pArtruis = GetClosestCreatureWithEntry(m_creature, NPC_ARTRUIS_HEARTLESS, 30.0f))
        {
            if (npc_artruisAI* pArtruisAI = dynamic_cast<npc_artruisAI*>(pArtruis->AI()))
            {
                pArtruisAI->bIsBinded = false;
            }
        }

    }

    void JustReachedHome()
    {
        m_creature->CastSpell(m_creature, SPELL_TOMB_OF_HEARTLESS,false);  
    } 

};

CreatureAI* GetAI_npc_jaloot_zepik(Creature* pCreature)
{
    return new npc_jaloot_zepikAI(pCreature);
}

void AddSC_sholazar_basin()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_injured_rainspeaker";
    pNewScript->GetAI = &GetAI_npc_injured_rainspeaker;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_injured_rainspeaker;
    //pNewScript->pGossipHello = &GossipHello_npc_injured_rainspeaker;
    //pNewScript->pGossipSelect = &GossipSelect_npc_injured_rainspeaker;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_mosswalker_victim";
    pNewScript->pGossipHello = &GossipHello_npc_mosswalker_victim;
    pNewScript->pGossipSelect = &GossipSelect_npc_mosswalker_victim;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_vekjik";
    pNewScript->pGossipHello = &GossipHello_npc_vekjik;
    pNewScript->pGossipSelect = &GossipSelect_npc_vekjik;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_rjr_target";
    pNewScript->GetAI = &GetAI_mob_rjr_target;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_taste_test";
    pNewScript->GetAI = &GetAI_mob_taste_test;
    pNewScript->pEffectDummyCreature = &EffectDummyCreature_mob_taste_test;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_still_at_it_quest";
    pNewScript->pGOHello = &GOHello_go_still_at_it_quest;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tipsy_mcmanus";
    pNewScript->GetAI = &GetAI_npc_tipsy_mcmanus;
    pNewScript->pGossipHello = &GossipHello_npc_tipsy_mcmanus;
    pNewScript->pGossipSelect = &GossipSelect_npc_tipsy_mcmanus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_mosswalker_victim";
    pNewScript->pGossipHello = &GossipHello_mob_mosswalker_victim;
    pNewScript->pGossipSelect = &GossipSelect_mob_mosswalker_victim;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_jaloot_zepik";
    pNewScript->GetAI = &GetAI_npc_jaloot_zepik;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_artruis";
    pNewScript->GetAI = &GetAI_npc_artruis;
    pNewScript->RegisterSelf(); 


}
