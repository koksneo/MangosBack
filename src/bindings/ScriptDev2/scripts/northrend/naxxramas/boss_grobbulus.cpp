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
SDName: Boss_Grobbulus
SD%Complete: 80%
SDComment: Need to check spell Mutating Injection
SDAuthor: aramilnaile
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SPELL_BERSERK               = 26662,
    SPELL_MUTATINGINJECTION     = 28169,
    SPELL_SLIMESPRAY            = 28157,
    SPELL_SLIMESPRAY_H          = 54364,
    SPELL_POISONCLOUD           = 28240,
    SPELL_POISONCLOUDAOE        = 59116,
    
    NPC_SLIME                   = 16290
};

// Grobbulus Structure
struct MANGOS_DLL_DECL boss_grobbulusAI : public ScriptedAI
{
    boss_grobbulusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;

    bool m_bIsRegularMode;
    bool m_bBerserking;
    
    uint32 m_uiBerserkTimer;
    uint32 m_uiPoisonCloudTimer;
    uint32 m_uiMutatingInjectionTimer;
    uint32 m_uiSlimeSprayTimer;

    void Reset()
    {
        m_uiBerserkTimer = 720000;                       // 12 minutes
        m_uiPoisonCloudTimer = 15000;                    // 15 seconds and last 75 seconds 
        m_uiMutatingInjectionTimer = 20000;              // 20 seconds
        m_uiSlimeSprayTimer = urand(15000, 30000);      // 15 seconds + random seconds (up to 15 seconds)
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GROBBULUS, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GROBBULUS, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GROBBULUS, NOT_STARTED);
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *pSpell)
    {
        if(pSpell->Id == SPELL_SLIMESPRAY || pSpell->Id == SPELL_SLIMESPRAY_H)
        {
            if (pTarget->GetTypeId() != TYPEID_PLAYER) 
                return; 

            if (Creature* pSlime = m_creature->SummonCreature(NPC_SLIME, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000))
                if (Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    pSlime->AI()->AttackStart(pVictim);
                }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        // Berserkering after 12 minutes
        if (!m_bBerserking && m_uiBerserkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BERSERK);
            m_bBerserking = true;
        } else m_uiBerserkTimer -= uiDiff;

        // Poison Cloud
        if (m_uiPoisonCloudTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_POISONCLOUD);
            m_uiPoisonCloudTimer = 15000;
        } else m_uiPoisonCloudTimer -= uiDiff;

        // Mutating Injection
        if (m_uiMutatingInjectionTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_MUTATINGINJECTION);

            m_uiMutatingInjectionTimer = 20000;
        } else m_uiMutatingInjectionTimer -= uiDiff;

        // Slime Spray
        if (m_uiSlimeSprayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SLIMESPRAY : SPELL_SLIMESPRAY_H);
            m_uiSlimeSprayTimer = urand(15000, 30000);
        } else m_uiSlimeSprayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

// Poison Cloud Structure
struct MANGOS_DLL_DECL npc_grobbulus_poison_cloudAI : public Scripted_NoMovementAI
{
    npc_grobbulus_poison_cloudAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        Reset();
    }

    uint32 Cloud_Timer;

    void Reset()
    {
        Cloud_Timer = 1000;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (Cloud_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_POISONCLOUDAOE);
            Cloud_Timer = 10000;
        }else Cloud_Timer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_grobbulus(Creature* pCreature)
{
    return new boss_grobbulusAI(pCreature);
}

CreatureAI* GetAI_npc_grobbulus_poison_cloud(Creature* pCreature)
{
    return new npc_grobbulus_poison_cloudAI(pCreature);
}

void AddSC_boss_grobbulus()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_grobbulus";
    NewScript->GetAI = &GetAI_boss_grobbulus;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "npc_grobbulus_poison_cloud";
    NewScript->GetAI = &GetAI_npc_grobbulus_poison_cloud;
    NewScript->RegisterSelf();
}
