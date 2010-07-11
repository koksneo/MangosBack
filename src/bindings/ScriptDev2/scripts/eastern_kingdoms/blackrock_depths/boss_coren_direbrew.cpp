/* This Script is for Coren Direbrew event
 related to Brewfest
 unfortunately all spells related to this encounter are not working
 so to earn some time i hacked all spawns.
 encounter is composed of 2 parts:
 1)character with complete quest "Insult Coren Direbrew" can trigger event and force coren run to the basement where nonCombat part is performed (dialog with Antagonists)
 2)aftar questRewarded Coren becames attackable and attacks triggering player with assistance and spawns */

#include "precompiled.h"
#include "escort_ai.h"
#include "blackrock_depths.h"

enum
{
        QUEST_INSULT_COREN      = 12062,

        SAY_PAY                 = -1799998,
        SAY_AGGRO               = -1799997,

        SAY_IDLE1               = -1799996,
        SAY_IDLE2               = -1799995,
        SAY_IDLE3               = -1799994,
        SAY_IDLE4               = -1799993,

        SAY_ANTAGONIST1_1       = -1799992,
        SAY_ANTAGONIST1_2       = -1799991,
        SAY_ANTAGONIST1_3       = -1799990,
        SAY_ANTAGONIST2_1       = -1799989,
        SAY_ANTAGONIST2_2       = -1799988,
        SAY_ANTAGONIST2_3       = -1799987,
        SAY_ANTAGONIST4         = -1799986,

        MOB_ANTAGONIST          = 23795,
        MOB_ILSA                = 26764,
        MOB_URSULA              = 26822,
        MOB_MINION              = 26776
};

float Coord[6][4] = 
{
    {902.65f, -131.26f, -49.74f, 5.94f},// Antagonist1
    {902.85f, -134.45f, -49.74f, 0.49f},// Antagonist2
    {904.72f, -137.24f, -49.75f, 1.34f},// Antagonist3
    {905.53f, -128.06f, -49.74f, 5.04f},// Coren noncombat event movement point1
    {909.47f, -137.38f, -49.74f, 1.01f},// Coren noncombat event movement point2
    {898.79f, -140.91f, -49.75f, 0.48f} // Ursula and Ilsa spawn point
};

struct MANGOS_DLL_DECL boss_coren_direbrewAI : public npc_escortAI
{
    boss_coren_direbrewAI(Creature* pCreature) : npc_escortAI(pCreature) 
    {
       m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
       Reset();
    }

    ScriptedInstance* m_pInstance;

    bool EventStarted;
    bool LastPoint;
    bool AntagonistAttacked;
    bool IlsaSpawned;
    bool UrsulaSpawned;

    // Adds GUIDs
    uint64 Antagonist1GUID;
    uint64 Antagonist2GUID;
    uint64 Antagonist3GUID;

    uint32 AggroYell_Timer;
    uint32 Walk_Timer;
    uint32 Speach_Timer;
    uint32 Minion_Timer;

    uint8 Speach;
    uint8 Walk;
    uint8 Minion_SummoningPhase;
   
    void Reset() 
    {
        DespawnAdds();
        // Player cannot turn quest before quest event begins
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        // Coren cannot be attacked before quest rewareded
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetEscortPaused(false);
        
        EventStarted = false;
        LastPoint = false;
        AntagonistAttacked = false;
        IlsaSpawned = false;
        UrsulaSpawned = false;
        
        AggroYell_Timer = 10000;
        Walk_Timer = 0;
        Speach_Timer = 0;
        Speach = 0;
        Walk = 0;
        Minion_SummoningPhase = 0;

        Minion_Timer = 10000;
    }
   
   void SaySay(uint64 guid, int32 text)
   {
        Creature* pPointer = (Creature*)Unit::GetUnit(*m_creature, guid);
        if (pPointer && pPointer->isAlive())
            DoScriptText(text,pPointer,NULL);
   }

   void Despawn(uint64 guid)
   {
       if (Creature* pPointer = (Creature*)Unit::GetUnit(*m_creature, guid))
            pPointer->ForcedDespawn();
   }

   void Assault(uint64 guid, uint32 faction, Unit* pTarget)
   {
       Creature* pPointer = (Creature*)Unit::GetUnit(*m_creature, guid);
       if (pTarget && pPointer)
       {
           pPointer->setFaction(faction);
           pPointer->AI()->AttackStart(pTarget);
       }
   }

 
    void DespawnAdds()
    {
        Despawn(Antagonist1GUID);
        Despawn(Antagonist2GUID);
        Despawn(Antagonist3GUID);
        if (m_pInstance)
            if (GameObject* pMinionSummoner = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_MINIONSUMMONER)))
                pMinionSummoner->SetGoState(GO_STATE_READY);
    }

    void JustDied(Unit* pKiller)
    {
        DespawnAdds();
    }

    void WaypointReached (uint32 i) 
    {
        switch(i)
        {
        case 1:
            Creature* temp;
            temp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[0][0], Coord[0][1], Coord[0][2], Coord[0][3], TEMPSUMMON_DEAD_DESPAWN, 0);
            if (temp != NULL)
            {
                Antagonist1GUID = temp->GetGUID();
                temp = NULL;
            }
            temp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[1][0], Coord[1][1], Coord[1][2], Coord[1][3], TEMPSUMMON_DEAD_DESPAWN, 0);
            if (temp != NULL)
            {
                Antagonist2GUID = temp->GetGUID();
                temp = NULL;
            }
            temp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[2][0], Coord[2][1], Coord[2][2], Coord[2][3], TEMPSUMMON_DEAD_DESPAWN, 0);
            if (temp != NULL)
            {
                Antagonist3GUID = temp->GetGUID();
                temp = NULL;
            }
            break;
        case 12:
            // When escort is paused we need to restore questgiver flags
            m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            LastPoint = true;
            SetEscortPaused(true);
            break;
        }
    }

    void MoveInLineOfSight (Unit* pWho)
    {
        if (!pWho)
            return;

        if (EventStarted)
            return;

        if (pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        Player* pPlayer = (Player*)Unit::GetUnit(*m_creature,pWho->GetGUID());
        if (!pPlayer)
            return;

        if (!EventStarted && m_creature->GetDistance(pPlayer) < 10)
        {
            if (pPlayer->GetQuestStatus(QUEST_INSULT_COREN) == QUEST_STATUS_COMPLETE)
            {
                Start(false,true,pPlayer->GetGUID());
                EventStarted = true;
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff) 
    {
        if (!m_creature->isInCombat() || !m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            // After achieving last point of escort small noncombat event begins
            if (LastPoint)
            {
                void GetAntagonists();
                // Coren Walking in fornt of Antagonists
                if (Walk_Timer < uiDiff)
                {
                    m_creature->SetSplineFlags(SPLINEFLAG_WALKMODE);
                    switch(Walk)
                    {
                        case 0:
                            m_creature->SendMonsterMove(Coord[3][0],Coord[3][1],Coord[3][2],SPLINETYPE_NORMAL,SPLINEFLAG_WALKMODE,6000);
                            Walk = 1;
                            break;
                        case 1:
                            m_creature->SendMonsterMove(Coord[4][0],Coord[4][1],Coord[4][2],SPLINETYPE_NORMAL,SPLINEFLAG_WALKMODE,6000);
                            Walk = 0;
                            break;
                    }
                    Walk_Timer = 6000;
                }else Walk_Timer -= uiDiff;

                // Coren Yell and Antagonists response
                if (Speach_Timer < uiDiff)
                {
                    switch(Speach)
                    {
                    case 0:
                        DoScriptText(SAY_IDLE1,m_creature);
                        Speach = 1;
                        break;
                    case 1:
                        SaySay(Antagonist1GUID,SAY_ANTAGONIST2_1);
                        SaySay(Antagonist2GUID,SAY_ANTAGONIST2_2);
                        SaySay(Antagonist3GUID,SAY_ANTAGONIST2_3);
                        Speach = 2;
                        break;
                    case 2:
                        DoScriptText(SAY_IDLE2,m_creature);
                        Speach = 3;
                        break;
                    case 3:
                        SaySay(Antagonist1GUID,SAY_ANTAGONIST1_2);
                        SaySay(Antagonist2GUID,SAY_ANTAGONIST1_3);
                        SaySay(Antagonist3GUID,SAY_ANTAGONIST1_1);
                        Speach = 4;
                        break;
                    case 4:
                        DoScriptText(SAY_IDLE3,m_creature);
                        Speach = 5;
                        break;
                    case 5:
                        SaySay(Antagonist1GUID,SAY_ANTAGONIST1_1);
                        SaySay(Antagonist2GUID,SAY_ANTAGONIST1_2);
                        SaySay(Antagonist3GUID,SAY_ANTAGONIST1_3);
                        Speach = 6;
                        break;
                    case 6:
                        DoScriptText(SAY_IDLE4,m_creature);
                        Speach = 7;
                        break;
                    case 7:
                        SaySay(Antagonist1GUID,SAY_ANTAGONIST4);
                        SaySay(Antagonist2GUID,SAY_ANTAGONIST4);
                        SaySay(Antagonist3GUID,SAY_ANTAGONIST4);
                        Speach = 0;
                        break;
                    }
                    Speach_Timer = 5000;
                }else Speach_Timer -=uiDiff;
            }
        }
        else {

        //Force Antagonist to assist Coren in combat
        if (m_creature->getVictim() && !AntagonistAttacked)
        {
            Assault(Antagonist1GUID,m_creature->getFaction(),m_creature->getVictim());
            Assault(Antagonist2GUID,m_creature->getFaction(),m_creature->getVictim());
            Assault(Antagonist3GUID,m_creature->getFaction(),m_creature->getVictim());
            AntagonistAttacked = true;
        }

        if (!IlsaSpawned && ((m_creature->GetHealth()*100) / m_creature->GetMaxHealth() <= 66))
        {
            Creature* Ilsa = m_creature->SummonCreature(MOB_ILSA,Coord[5][0],Coord[5][1],Coord[5][2],Coord[5][3],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000);
            if (Ilsa && m_creature->getVictim()) // i know if(victim) was checked at the top but once got crash with multithreaded mangos
                {
                    Ilsa->AI()->AttackStart(m_creature->getVictim());
                    IlsaSpawned = true;
                }
        }

        if (!UrsulaSpawned && ((m_creature->GetHealth()*100) / m_creature->GetMaxHealth() <= 33))
        {
            Creature* Ursula = m_creature->SummonCreature(MOB_URSULA,Coord[5][0],Coord[5][1],Coord[5][2],Coord[5][3],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000);
            if (Ursula && m_creature->getVictim())// i know if(victim) was checked at the top but once got crash with multithreaded mangos
                {
                    Ursula->AI()->AttackStart(m_creature->getVictim());
                    UrsulaSpawned = true;
                }
        }

        if (Minion_Timer < uiDiff)
        {
            if (m_pInstance)
            {
                if (GameObject* pMinionSummoner = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_MINIONSUMMONER)))
                {
                    switch(Minion_SummoningPhase)
                    {
                        case 0:
                            pMinionSummoner->SetGoState(GO_STATE_ACTIVE);
                            if (m_creature->getVictim())
                                if (Creature* pMinion = m_creature->SummonCreature(MOB_MINION,pMinionSummoner->GetPositionX(),pMinionSummoner->GetPositionY(),pMinionSummoner->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000))
                                {
                                    pMinion->setFaction(m_creature->getFaction());
                                    pMinion->AI()->AttackStart(m_creature->getVictim());
                                }
                            Minion_Timer = 3000;
                            Minion_SummoningPhase = 1;
                            break;
                        case 1:
                            pMinionSummoner->SetGoState(GO_STATE_READY);
                            Minion_Timer = 20000;
                            Minion_SummoningPhase = 0;
                            break;
                    }
              }
            }else Minion_Timer = 20000;
        }else Minion_Timer -= uiDiff;

        if (AggroYell_Timer < uiDiff)
        {
            DoScriptText(SAY_AGGRO,m_creature);
            AggroYell_Timer = 45000 + (rand()%45000);
        }else AggroYell_Timer -= uiDiff;

        DoMeleeAttackIfReady();
        }
    }
};
CreatureAI* GetAI_boss_coren_direbrew(Creature* pCreature)
{
    return new boss_coren_direbrewAI(pCreature);
}

bool ChooseReward_boss_coren_direbrew(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 slot)
{

    if (pPlayer && pQuest->GetQuestId() == QUEST_INSULT_COREN)
        if (boss_coren_direbrewAI* pEscortAI = dynamic_cast<boss_coren_direbrewAI*>(pCreature->AI()))
        {
            DoScriptText(SAY_PAY,pCreature,pPlayer);
            pCreature->setFaction(16);
            pEscortAI->AttackStart(pPlayer);
            pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    return true;
}


void AddSC_boss_coren_direbrew()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_coren_direbrew";
    newscript->GetAI = &GetAI_boss_coren_direbrew;
    newscript->pChooseReward = &ChooseReward_boss_coren_direbrew;
    newscript->RegisterSelf();
}
