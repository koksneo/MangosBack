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
SDName: Boss_Gluth
SD%Complete: 70
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    EMOTE_SPOTED_ZOMBIE     = -1533119,
    EMOTE_DEVOURED_ZOMBIE   = -1999780, 
    EMOTE_DECIMATE          = -1999781,
    EMOTE_PERIODIC_ENRAGE   = -1999779,

    SPELL_MORTALWOUND       = 25646,
    SPELL_DECIMATE          = 28374,
    SPELL_ENRAGE            = 28371,
    SPELL_ENRAGE_H          = 54427,
    SPELL_BERSERK           = 26662,
    SPELL_ZOMBIE_CHOW1      = 28239,
    SPELL_ZOMBIE_CHOW2      = 28404,


    NPC_ZOMBIE_CHOW         = 16360,

    GATES                   = 8
};

float GatePosition[GATES][3] = 
{
    {3269.590f, -3161.287f, 297.423f},
    {3277.797f, -3170.352f, 297.423f},
    {3267.049f, -3172.820f, 297.423f},
    {3252.157f, -3132.135f, 297.423f},
    {3259.990f, -3126.590f, 297.423f},
    {3259.815f, -3137.576f, 297.423f},
    {3303.046f, -3180.682f, 297.423f},
    {3313.283f, -3180.766f, 297.423f}
};

struct MANGOS_DLL_DECL boss_gluthAI : public ScriptedAI
{
    boss_gluthAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;

    std::list<uint64> lZombies;
    uint32 m_uiSearchZombieTimer;
    uint32 m_uiMortalWoundTimer;
    uint32 m_uiDecimateTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiSummonTimer;
    uint32 m_uiBerserkTimer;

    void Reset()
    {
        m_uiSearchZombieTimer = 1000;
        m_uiMortalWoundTimer = 8000;
        m_uiDecimateTimer = 100000;
        m_uiEnrageTimer = urand(15000, 20000);
        m_uiSummonTimer = 10000;

        m_uiBerserkTimer = MINUTE*8*IN_MILLISECONDS;

        DespawnZombies();
    }

    void DespawnZombies()
    {
        if (lZombies.empty())
            return;

        for (std::list<uint64>::iterator itr = lZombies.begin(); itr != lZombies.end(); ++itr)
        {
            Creature* pZombie = (Creature*)Unit::GetUnit(*m_creature, *itr);
            if (pZombie && pZombie->isAlive())
                pZombie->ForcedDespawn();
        }
        lZombies.clear();
    }

    void JustSummoned(Creature* pZombie)
    {
        pZombie->GetMotionMaster()->Clear();
        pZombie->GetMotionMaster()->MoveFollow(m_creature, 0.0f, 0.0f);
        lZombies.push_back(pZombie->GetGUID());
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GLUTH, DONE);

        DespawnZombies();
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GOTHIK, FAIL);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GLUTH, IN_PROGRESS);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Seatch and devour Zombie
        if (m_uiSearchZombieTimer < uiDiff)
        {
            if (Creature* pZombie = GetClosestCreatureWithEntry(m_creature, NPC_ZOMBIE_CHOW, 10.0f))
            {
                DoScriptText(EMOTE_SPOTED_ZOMBIE, m_creature);
                m_creature->SetFacingToObject(pZombie);
                if (DoCastSpellIfCan(pZombie, SPELL_ZOMBIE_CHOW1) == CAST_OK)
                {
                    m_creature->SetFacingToObject(pZombie);
                    m_creature->SetHealth(m_creature->GetHealthPercent() < 95.0f ? 
                        (m_creature->GetHealth() + m_creature->GetMaxHealth() * 0.05f) : m_creature->GetMaxHealth());
                    DoScriptText(EMOTE_DEVOURED_ZOMBIE, m_creature);
                    lZombies.remove(pZombie->GetGUID());
                }
            }
        } 
        else 
            m_uiSearchZombieTimer -= uiDiff;

        // Mortal Wound
        if (m_uiMortalWoundTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTALWOUND);
            m_uiMortalWoundTimer = 10000;
        }
        else
            m_uiMortalWoundTimer -= uiDiff;

        // Decimate
        if (m_uiDecimateTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_DECIMATE);
            DoScriptText(EMOTE_DECIMATE, m_creature);
            for (std::list<uint64>::iterator itr = lZombies.begin(); itr != lZombies.end(); ++itr)
            {
                Creature* pZombie = (Creature*)Unit::GetUnit(*m_creature, *itr);
                if (pZombie && pZombie->isAlive())
                {
                    pZombie->GetMotionMaster()->Clear();
                    pZombie->GetMotionMaster()->MoveFollow(m_creature, 0.0f, 0.0f);
                }
            }
            m_uiDecimateTimer = 100000;
        }
        else
            m_uiDecimateTimer -= uiDiff;

        // Periodic Enrage
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : SPELL_ENRAGE_H);
            DoScriptText(EMOTE_PERIODIC_ENRAGE, m_creature);
            m_uiEnrageTimer = urand(15000, 20000);
        }
        else
            m_uiEnrageTimer -= uiDiff;

        // Summon
        if (m_uiSummonTimer < uiDiff)
        {
            for (uint8 i = 0; i < (m_bIsRegularMode ? 1 : 2); ++i)
            {
                uint8 m_uiGate = urand(1, GATES) - 1;
                m_creature->SummonCreature(NPC_ZOMBIE_CHOW, GatePosition[m_uiGate][0], GatePosition[m_uiGate][1], GatePosition[m_uiGate][2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 80000);
            }
            m_uiSummonTimer = 10000;
        }
        else
            m_uiSummonTimer -= uiDiff;

        // Berserk
        if (m_uiBerserkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BERSERK, CAST_TRIGGERED);
            m_uiBerserkTimer = MINUTE*5*IN_MILLISECONDS;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_gluth(Creature* pCreature)
{
    return new boss_gluthAI(pCreature);
}

struct MANGOS_DLL_DECL mob_zombie_chowAI : public ScriptedAI
{
    mob_zombie_chowAI(Creature* pCreature) : ScriptedAI(pCreature)
    {Reset();}

    void Reset() {}

    void MoveInLineOfSight(Unit* pWho){}

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (!pDoneBy)
            return;

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != CHASE_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveChase(pDoneBy);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_zombie_chow(Creature* pCreature)
{
    return new mob_zombie_chowAI(pCreature);
}

void AddSC_boss_gluth()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_gluth";
    NewScript->GetAI = &GetAI_boss_gluth;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_zombie_chow";
    NewScript->GetAI = &GetAI_mob_zombie_chow;
    NewScript->RegisterSelf();
}
