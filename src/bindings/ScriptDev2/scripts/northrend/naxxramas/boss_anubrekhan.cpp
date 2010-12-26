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
SDName: Boss_Anubrekhan
SD%Complete: 70
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_GREET                   = -1533000,
    SAY_AGGRO1                  = -1533001,
    SAY_AGGRO2                  = -1533002,
    SAY_AGGRO3                  = -1533003,
    SAY_TAUNT1                  = -1533004,
    SAY_TAUNT2                  = -1533005,
    SAY_TAUNT3                  = -1533006,
    SAY_TAUNT4                  = -1533007,
    SAY_SLAY                    = -1533008,

    EMOTE_CRYPT_GUARD           = -1533153,                 // NYI
    EMOTE_INSECT_SWARM          = -1533154,                 // NYI
    EMOTE_CORPSE_SCARABS        = -1533155,                 // NYI

    SPELL_IMPALE                = 28783,                    //May be wrong spell id. Causes more dmg than I expect
    SPELL_IMPALE_H              = 56090,
    SPELL_LOCUSTSWARM           = 28785,                    //This is a self buff that triggers the dmg debuff
    SPELL_LOCUSTSWARM_H         = 54021,

    //spellId invalid
    SPELL_SUMMONGUARD           = 29508,                    //Summons 1 crypt guard at targeted location

    SPELL_SELF_SPAWN_5          = 29105,                    //This spawns 5 corpse scarabs ontop of us (most likely the pPlayer casts this on death)
    SPELL_SELF_SPAWN_10         = 28864,                    //This is used by the crypt guards when they die
    SPELL_BERSERK               = 26662,

    NPC_CRYPT_GUARD             = 16573
};

struct MANGOS_DLL_DECL boss_anubrekhanAI : public ScriptedAI
{
    boss_anubrekhanAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_bHasTaunted = false;
        Reset();
    }

    instance_naxxramas* m_pInstance;

    std::list<uint64> m_lCryptGuardList;
    bool m_bIsRegularMode;
    bool m_bHasTaunted;
    bool m_bBerserking;
    bool m_bCanSummonNextGuard;

    uint32 m_uiImpaleTimer;
    uint32 m_uiLocustSwarmTimer;
    uint32 m_uiSummonTimer;
    uint32 m_uiBerserkTimer;

    void Reset()
    {
        m_uiImpaleTimer = 15000;                            // 15 seconds
        m_uiLocustSwarmTimer = urand(80000, 120000);        // Random time between 80 seconds and 2 minutes for initial cast
        m_uiSummonTimer = 30000;    						// 30 seconds 
        m_uiBerserkTimer = 300000;
        m_bBerserking = false;
        m_bCanSummonNextGuard = false;
        DespawnGuards();

        // Summon Guards only on initial spawn, else guards will be resummoned on JustReachedHome()
        if (m_pInstance && m_pInstance->GetData(TYPE_ANUB_REKHAN) == NOT_STARTED)
        {
            m_creature->SummonCreature(NPC_CRYPT_GUARD, m_creature->GetPositionX(), m_creature->GetPositionY()+10, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS);
            if (!m_bIsRegularMode)
                m_creature->SummonCreature(NPC_CRYPT_GUARD, m_creature->GetPositionX(), m_creature->GetPositionY()-10, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS);
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        //Force the player to spawn corpse scarabs via spell
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            pVictim->CastSpell(pVictim, SPELL_SELF_SPAWN_5, true);

        if (urand(0, 4))
            return;

        DoScriptText(SAY_SLAY, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
            case 2: DoScriptText(SAY_AGGRO3, m_creature); break;
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUB_REKHAN, IN_PROGRESS);
        
        if(m_lCryptGuardList.empty())
            return;

        for(std::list<uint64>::iterator itr = m_lCryptGuardList.begin(); itr != m_lCryptGuardList.end(); ++itr)
        {
            Creature* pCryptGuard = m_creature->GetMap()->GetCreature(*itr);
            if (pCryptGuard && pCryptGuard->isAlive() && pWho->isInAccessablePlaceFor(pCryptGuard) && pCryptGuard->IsHostileTo(pWho) && pCryptGuard->AI())
            {
                pCryptGuard->AddThreat(pWho,0.0f);
                pCryptGuard->AI()->AttackStart(pWho);
            }
        }
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUB_REKHAN, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ANUB_REKHAN, FAIL);
            m_creature->SummonCreature(NPC_CRYPT_GUARD, m_creature->GetPositionX(), m_creature->GetPositionY()+10, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS);
            if (!m_bIsRegularMode)
                m_creature->SummonCreature(NPC_CRYPT_GUARD, m_creature->GetPositionX(), m_creature->GetPositionY()-10, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS);
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!m_bHasTaunted && m_creature->IsWithinDistInMap(pWho, 60.0f))
        {
            switch(urand(0, 4))
            {
                case 0: DoScriptText(SAY_GREET, m_creature); break;
                case 1: DoScriptText(SAY_TAUNT1, m_creature); break;
                case 2: DoScriptText(SAY_TAUNT2, m_creature); break;
                case 3: DoScriptText(SAY_TAUNT3, m_creature); break;
                case 4: DoScriptText(SAY_TAUNT4, m_creature); break;
            }
            m_bHasTaunted = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void DespawnGuards()
    {
        if (m_lCryptGuardList.empty())
            return;

        for(std::list<uint64>::iterator itr = m_lCryptGuardList.begin(); itr != m_lCryptGuardList.end(); ++itr)
        {
            Creature* pTemp = m_creature->GetMap()->GetCreature(*itr);
            if (pTemp && pTemp->isAlive())
                pTemp->ForcedDespawn();
        }
        m_lCryptGuardList.clear();
    }

    void JustSummoned(Creature* pSummoned)
    {
        m_lCryptGuardList.push_back(pSummoned->GetGUID());
        pSummoned->SetRespawnTime(WEEK);
        pSummoned->SetRespawnDelay(WEEK);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bBerserking && m_uiBerserkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BERSERK);
            m_bBerserking = true;
        }else m_uiBerserkTimer -= uiDiff;

        // Impale
        if (m_uiImpaleTimer < uiDiff)
        {
            //Cast Impale on a random target
            //Do NOT cast it when we are afflicted by locust swarm
            if (!m_creature->HasAura(SPELL_LOCUSTSWARM) || !m_creature->HasAura(SPELL_LOCUSTSWARM_H))
            {
                if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCastSpellIfCan(target, m_bIsRegularMode ? SPELL_IMPALE : SPELL_IMPALE_H);
            }

            m_uiImpaleTimer = 15000;
        }
        else
            m_uiImpaleTimer -= uiDiff;

        // Locust Swarm
        if (m_uiLocustSwarmTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_LOCUSTSWARM :SPELL_LOCUSTSWARM_H);
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                Creature* pTemp = m_creature->SummonCreature(NPC_CRYPT_GUARD, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                if (pTemp && pTemp->AI() && pTemp->IsHostileTo(pTarget) && pTarget->isInAccessablePlaceFor(pTemp))
                {
                    pTemp->AddThreat(pTarget);
                    pTemp->AI()->AttackStart(pTarget);
                }
                m_uiSummonTimer = 30000; // 30 sec after initial locust swarm
                m_bCanSummonNextGuard = true;
            }
            m_uiLocustSwarmTimer = urand(90000, 120000);
        }
        else
            m_uiLocustSwarmTimer -= uiDiff;

        // Summon
        if (m_bCanSummonNextGuard)
        {
            if (m_uiSummonTimer <= uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                {
                    Creature* pTemp = m_creature->SummonCreature(NPC_CRYPT_GUARD, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                    if (pTemp && pTemp->AI() && pTemp->IsHostileTo(pTarget) && pTarget->isInAccessablePlaceFor(pTemp))
                    {
                        pTemp->AddThreat(pTarget);
                        pTemp->AI()->AttackStart(pTarget);
                    }
                }
                m_bCanSummonNextGuard = false;
            } else m_uiSummonTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anubrekhan(Creature* pCreature)
{
    return new boss_anubrekhanAI(pCreature);
}

void AddSC_boss_anubrekhan()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_anubrekhan";
    NewScript->GetAI = &GetAI_boss_anubrekhan;
    NewScript->RegisterSelf();
}
