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
SDName: boss_krikthir_the_gatewatcher
SDAuthor: ScrappyDoo
SD%Complete: 95% 
SDComment: completed, scripts for mini boses can be removed after ACID support
exp from swarm need to be deleted in DB
SDCategory: Azjol Nerub
EndScriptData */

#include "precompiled.h"
#include "azjol-nerub.h"

enum Sounds
{
    SAY_AGGRO                                   = -1601011,
    SAY_SLAY_1                                  = -1601012,
    SAY_SLAY_2                                  = -1601013,
    SAY_SLAY_3                                  = -1601014,
    SAY_DEATH                                   = -1601015,
    SAY_SEND_GROUP_1_K                          = -1601018,
    SAY_SEND_GROUP_2_K                          = -1601019,
    SAY_SEND_GROUP_3_K                          = -1601020,
    SAY_SWARM_1                                 = -1601016,
    SAY_SWARM_2                                 = -1601017,
    SAY_PREFIGHT_1                              = -1601021,
    SAY_PREFIGHT_2                              = -1601022,
    SAY_PREFIGHT_3                              = -1601023,
};

enum Spells
{
    //KirikThir Spell
    SPELL_MIND_FLAY                     = 52586,
    H_SPELL_MIND_FLAY                   = 59367,
    SPELL_CURSE_OF_FATIGUE              = 52592,
    H_SPELL_CURSE_OF_FATIGUE            = 59368,
    SPELL_FRENZY                        = 28747,
    //Silthil Spell
    SPELL_POISON_SPRAY                  = 52493,
    H_SPELL_POISON_SPRAY                = 59366,
    //Grash Spells
    SPELL_ENRAGE                        = 52470,
    //Nargij Spell
    SPELL_BINDINGS_WEBS                 = 52524,
    H_SPELL_BINDINGS_WEBS               = 59365,
    //mini boss spells
    SPELL_INFECTED_BITE                 = 52469,
    H_SPELL_INFECTED_BITE               = 59364,
    SPELL_WEBWARP                       = 52086,
};

enum Creatures
    {
    MOB_SKIRMISHER                      = 28734,
    MOB_SHADOWCASTER                    = 28733,
    MOB_WARRIOR                         = 28732,

    MOB_SKITTERING_SWARMER              = 28735,
    MOB_SKITTERING_SWARMER_INFECTOR     = 28736,
    MOB_SILTHIK                         = 28731,
    MOB_GASHRA                          = 28730,
    MOB_NARJIL                          = 28729,
};

struct MANGOS_DLL_DECL boss_krikthirAI : public ScriptedAI
{
    boss_krikthirAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool   m_bIsRegularMode;
    bool   m_bIsEnraged;
    bool   m_bIsPhase;
    uint8  m_uiPhase;
    uint32 m_uiMindFlyTimer;
    uint32 m_uiSwarmTimer;
    uint32 m_uiCurseTimer;
    uint32 m_uiSoundTimer;
    uint64 m_uiMiniBossGUID[3];

    void Reset() 
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        m_uiPhase           = 0;
        m_uiMindFlyTimer    = urand(10000,15000);
        m_uiSwarmTimer      = 15000;
        m_uiCurseTimer      = 20000;
        m_uiSoundTimer      = 25000;
        m_bIsPhase          = false;
        m_bIsEnraged        = false; 

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KRIKTHIR, NOT_STARTED);
    }

    void SpawnGroups(uint8 i)
    {
        uint32 ID[3];
        float fSpawnY = 0;
        float fSpawnX = 0;

        switch (i)
        {
            case 0: ID[0] = MOB_SILTHIK; ID[1] = MOB_SKIRMISHER; ID[2] = MOB_SHADOWCASTER; fSpawnX = 546.393f; fSpawnY = 665.541f; break;
            case 1: ID[0] = MOB_GASHRA; ID[1] = MOB_WARRIOR; ID[2] = MOB_SKIRMISHER; fSpawnX = 529.4408f; fSpawnY = 660.663f; break;
            case 2: ID[0] = MOB_NARJIL; ID[1] = MOB_SHADOWCASTER; ID[2] = MOB_WARRIOR; fSpawnX = 508.576f; fSpawnY = 668.013f; break;
        }

        Creature* pMiniBoss = m_creature->SummonCreature(ID[0], fSpawnX, fSpawnY, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        if(pMiniBoss) 
        {
            if(m_creature->getVictim())
                pMiniBoss->AI()->AttackStart(m_creature->getVictim());
            m_uiMiniBossGUID[i] = pMiniBoss->GetGUID();
        }

        for(uint8 k=1; k<3; ++k)
        {
            Creature* pTrash = m_creature->SummonCreature(ID[k], fSpawnX+1, fSpawnY+1, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            if(pTrash)
                if(m_creature->getVictim())
                    pTrash->AI()->AttackStart(m_creature->getVictim());
        }
    }

    void Aggro(Unit* pWho)
    {
        m_creature->StopMoving();
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveIdle();

        SpawnGroups(0);
        ++m_uiPhase;
        DoScriptText(SAY_SEND_GROUP_1_K, m_creature);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_KRIKTHIR, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_KRIKTHIR, DONE);
    }

    void SummonSwarm()
    {
        for(uint8 j=0; j<16; ++j)
        {
            uint32 ID = MOB_SKITTERING_SWARMER;
            if(j<3)
                ID = MOB_SKITTERING_SWARMER_INFECTOR;
            Creature* pSummoned = m_creature->SummonCreature(ID, m_creature->GetPositionX()+rand()%20, m_creature->GetPositionY()+rand()%20, m_creature->GetPositionZ()+rand()%20, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
            Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
            if (pSummoned && pSummoned->AI() && pTarget)
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void KilledUnit(Unit *pVictim)
    {
        // how could it be possible?
        if (pVictim == m_creature)
            return;

        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature);break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature);break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature);break;
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KRIKTHIR, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(!m_bIsPhase)
        {
            if(m_uiSoundTimer < uiDiff)
            {
                switch(urand(0, 3))
                {
                    case 0: DoScriptText(SAY_PREFIGHT_1, m_creature);break;
                    case 1: DoScriptText(SAY_PREFIGHT_2, m_creature);break;
                    case 2: DoScriptText(SAY_PREFIGHT_3, m_creature);break;
                }
                m_uiSoundTimer = 40000;
            }m_uiSoundTimer -= uiDiff;
        }

        if(!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;  

        if(!m_bIsPhase)
        {
            m_creature->StopMoving();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();

            if(m_pInstance)
            {            
                if(m_uiPhase == 3)
                    if(Creature* pMiniBoss = m_creature->GetMap()->GetCreature(m_uiMiniBossGUID[2]))
                        if(!pMiniBoss->isAlive())
                        {
                            m_uiMindFlyTimer = urand(10000,15000);
                            m_uiSwarmTimer     = 16000;
                            m_uiCurseTimer     = 20000;
                            DoScriptText(SAY_AGGRO, m_creature);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            if(m_creature->getVictim())
                                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                            m_bIsPhase = true;
                        }

                if(m_uiPhase == 2)
                    if(Creature* pMiniBoss = m_creature->GetMap()->GetCreature(m_uiMiniBossGUID[1]))
                        if(!pMiniBoss->isAlive())  
                        {
                            DoScriptText(SAY_SEND_GROUP_2_K, m_creature);
                            SpawnGroups(2);
                            ++m_uiPhase;
                        }

                if(m_uiPhase == 1)
                    if(Creature* pMiniBoss = m_creature->GetMap()->GetCreature(m_uiMiniBossGUID[0]))
                        if(!pMiniBoss->isAlive())          
                        {
                            DoScriptText(SAY_SEND_GROUP_1_K, m_creature);
                            SpawnGroups(1);
                            ++m_uiPhase;
                        }
            }
            return;
        }

        if(m_creature->GetHealthPercent() <= 10.0f)
        {
            if(!m_bIsEnraged)
            {
                DoCast(m_creature, SPELL_FRENZY);
                m_bIsEnraged = true;
            }
        }

        if(m_uiMindFlyTimer < uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_MIND_FLAY : H_SPELL_MIND_FLAY); 
            m_uiMindFlyTimer = urand(15000, 20000);
        }
        else
            m_uiMindFlyTimer -= uiDiff;

        if(m_uiCurseTimer < uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_CURSE_OF_FATIGUE : H_SPELL_CURSE_OF_FATIGUE); 
            m_uiCurseTimer = urand(25000, 35000);
        }
        else
            m_uiCurseTimer -= uiDiff;

        if(m_uiSwarmTimer < uiDiff)
        {
            DoScriptText(urand(0, 1) ? SAY_SWARM_1 : SAY_SWARM_2, m_creature);
            SummonSwarm();
            m_uiSwarmTimer = 15000;
        }
        else
            m_uiSwarmTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_krikthir(Creature *pCreature)
{
    return new boss_krikthirAI (pCreature);
}

//Silithik
struct MANGOS_DLL_DECL mob_silthikAI : public ScriptedAI
{
    mob_silthikAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiPoisonSprayTimer;
    uint32 m_uiInfectedBiteTimer;
    uint32 m_uiWebWarpTimer;

    void Reset()
    {
        m_uiPoisonSprayTimer = 5000;
        m_uiInfectedBiteTimer = 1000;
        m_uiWebWarpTimer = urand(15000, 25000);
    }

    void UpdateAI(const uint32 uiDiff) 
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiPoisonSprayTimer <uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_POISON_SPRAY : H_SPELL_POISON_SPRAY);
            m_uiPoisonSprayTimer = urand(15000,30000);
        }
        else
            m_uiPoisonSprayTimer -= uiDiff;

        if(m_uiInfectedBiteTimer < uiDiff)
        {
            if(m_creature->getVictim())
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_INFECTED_BITE : H_SPELL_INFECTED_BITE); 
            m_uiInfectedBiteTimer = urand(9000,18000);
        }
        else
            m_uiInfectedBiteTimer -= uiDiff;

        if(m_uiWebWarpTimer <uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, SPELL_WEBWARP);
            m_uiWebWarpTimer = urand(25000,35000);
        }
        else
            m_uiWebWarpTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_silthik(Creature *pCreature)
{
    return new mob_silthikAI (pCreature);
}

//Gashra
struct MANGOS_DLL_DECL mob_gashraAI : public ScriptedAI
{
    mob_gashraAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiEnrageTimer;
    uint32 m_uiInfectedBiteTimer;
    uint32 m_uiWebWarpTimer;

    void Reset()
    {
        m_uiEnrageTimer = 5000;
        m_uiInfectedBiteTimer = 1000;
        m_uiWebWarpTimer = urand(15000, 25000);
    }

    void UpdateAI(const uint32 uiDiff) 
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiEnrageTimer <uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE);
            m_uiEnrageTimer = urand(15000, 25000);
        }
        else
            m_uiEnrageTimer -= uiDiff;

        if(m_uiInfectedBiteTimer < uiDiff)
        {
            if(m_creature->getVictim())
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_INFECTED_BITE : H_SPELL_INFECTED_BITE); 
            m_uiInfectedBiteTimer = urand(9000,18000);
        }
        else
            m_uiInfectedBiteTimer -= uiDiff;

        if(m_uiWebWarpTimer <uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, SPELL_WEBWARP);
            m_uiWebWarpTimer = urand(25000,35000);
        }
        else
            m_uiWebWarpTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_gashra(Creature *pCreature)
{
    return new mob_gashraAI (pCreature);
}

//Gashra
struct MANGOS_DLL_DECL mob_narjilAI : public ScriptedAI
{
    mob_narjilAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool   m_bIsRegularMode;
    uint32 m_uiWebTimer;
    uint32 m_uiInfectedBiteTimer;
    uint32 m_uiWebWarpTimer;

    void Reset()
    {
        m_uiWebTimer = 5000;
        m_uiInfectedBiteTimer = 1000;
        m_uiWebWarpTimer = urand(15000, 25000);
    }

    void Aggro(Unit *pWho)
    {
        DoScriptText(SAY_SEND_GROUP_3_K, m_creature);
    }

    void UpdateAI(const uint32 uiDiff) 
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiWebTimer <uiDiff)
        {
            if(m_creature->getVictim())
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_BINDINGS_WEBS : H_SPELL_BINDINGS_WEBS);
            m_uiWebTimer = urand(15000, 25000);
        }else m_uiWebTimer -= uiDiff;

        if(m_uiInfectedBiteTimer < uiDiff)
        {
            if(m_creature->getVictim())
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_INFECTED_BITE : H_SPELL_INFECTED_BITE); 
            m_uiInfectedBiteTimer = urand(9000,18000);
        }else m_uiInfectedBiteTimer -= uiDiff;

        if(m_uiWebWarpTimer <uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, SPELL_WEBWARP);
            m_uiWebWarpTimer = urand(25000,35000);
        }else m_uiWebWarpTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_narjil(Creature *pCreature)
{
    return new mob_narjilAI (pCreature);
}

void AddSC_boss_krikthir()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_krikthir";
    newscript->GetAI = &GetAI_boss_krikthir;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_silthik";
    newscript->GetAI = &GetAI_mob_silthik;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_gashra";
    newscript->GetAI = &GetAI_mob_gashra;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_narjil";
    newscript->GetAI = &GetAI_mob_narjil;
    newscript->RegisterSelf();
}