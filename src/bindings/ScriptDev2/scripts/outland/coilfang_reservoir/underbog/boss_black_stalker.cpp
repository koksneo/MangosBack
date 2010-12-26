/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Black_Stalker
SD%Complete: 100
SDComment:
SDCategory: Underbog
EndScriptData */

#include "precompiled.h"
#include "def_underbog.h"

enum
{
    // Black Stalker Spells
    SPELL_STATIC_CHARGE         = 31715,
    SPELL_CHAIN_LIGHTNING       = 31717,
    SPELL_LEVITATE              = 31704,

    // Spore Strider (add) spell
    SPELL_LIGHTNING_BOLT        = 20824,

    MOB_SPORE_STRIDER           = 22299,
    STRIDERS_NO                 = 3
};

float SporeStriderLoc[6][4]=
{
    {119.0f, 33.33f, 25.66f, 6.01f},
    {124.78f, 48.4f, 25.66f, 5.48f},
    {149.26f, 58.35f, 25.66f, 4.79f},
    {137.25f, -10.95f, 25.66f, 1.86f},
    {160.77f, -15.36f, 25.66f, 1.96f},
    {175.66f, -11.0f, 25.66f, 2.29f}
};

struct MANGOS_DLL_DECL boss_black_stalkerAI : public ScriptedAI
{
    boss_black_stalkerAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsNormalMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint64 SporeStriderGUID[STRIDERS_NO];

    uint32 m_uiChainLightning_Timer;
    uint32 m_uiLevitate_Timer;

    uint32 m_uiSummonSporeStrider_Timer;

    uint32 m_uiLightninBolt_Timer;

    bool m_bIsNormalMode;

    void Reset()
    {
        m_uiChainLightning_Timer = 5000;
        m_uiLevitate_Timer = 10000;

        m_uiSummonSporeStrider_Timer = 10000;
        m_uiLightninBolt_Timer = 1000;
    }


    void Aggro(Unit* pWho)
    {
        if (m_pInstance && pWho)
            m_pInstance->SetData(TYPE_STALKER, IN_PROGRESS);
    }

    void JustDied(Unit* pVictim)
    {
        for (int i = 0; i < STRIDERS_NO; ++i)
        {
            // Despawn spawned Strider
            if (Creature* pOldStrider = m_creature->GetMap()->GetCreature(SporeStriderGUID[i]))
                pOldStrider->ForcedDespawn();
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_STALKER, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_STALKER, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->getVictim() && !m_creature->SelectHostileTarget())
            return;
        
        if (m_uiLevitate_Timer < uiDiff)
        {
            Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

            if (target)
                m_creature->CastSpell(target, SPELL_LEVITATE,false);                                

            m_uiLevitate_Timer = 30000;
        }else m_uiLevitate_Timer -= uiDiff;

        if (m_uiChainLightning_Timer < uiDiff)
        {
            m_creature->CastSpell(m_creature->getVictim(), SPELL_CHAIN_LIGHTNING,false);
            m_uiChainLightning_Timer = 5000 + rand()%10000;
        }else m_uiChainLightning_Timer -= uiDiff;

        if (m_uiSummonSporeStrider_Timer < uiDiff)
        {
            if (!m_bIsNormalMode)
            {
                for (int i = 0; i < STRIDERS_NO; ++i)
                {
                    // there is high chance that "old striders" will be despawned
                    if (urand(0, 2) > 0)
                        if (Creature* pOldStrider = m_creature->GetMap()->GetCreature(SporeStriderGUID[i]))
                            pOldStrider->ForcedDespawn();

                    // Spawn new striders
                    uint8 u = urand(i, 5);
                    if (Creature* pStrider = m_creature->SummonCreature(MOB_SPORE_STRIDER, SporeStriderLoc[u][0], SporeStriderLoc[u][1], SporeStriderLoc[u][2],SporeStriderLoc[u][3], TEMPSUMMON_TIMED_DESPAWN, 30000))
                    {
                        pStrider->setFaction(m_creature->getFaction());
                        SporeStriderGUID[i] = pStrider->GetGUID();
                        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        {
                            pStrider->AI()->AttackStart(pTarget);
                            pStrider->GetMotionMaster()->MoveChase(pTarget,10.0f);
                        }
                    }
                }
            }    
            m_uiSummonSporeStrider_Timer = urand(8000,12000);
        }else m_uiSummonSporeStrider_Timer -= uiDiff;


        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_spore_striderAI : public ScriptedAI
{
    mob_spore_striderAI(Creature* pCreature) : ScriptedAI(pCreature) 
    
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiLightningBolt_Timer;

    void Reset()
    {
        m_uiLightningBolt_Timer = 1000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_STALKER) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiLightningBolt_Timer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_LIGHTNING_BOLT);
            m_uiLightningBolt_Timer = 4000;
        } else m_uiLightningBolt_Timer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_spore_strider(Creature* pCreature)
{
    return new mob_spore_striderAI(pCreature);
}

CreatureAI* GetAI_boss_black_stalker(Creature* pCreature)
{
    return new boss_black_stalkerAI(pCreature);
}

void AddSC_boss_black_stalker()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_black_stalker";
    newscript->GetAI = &GetAI_boss_black_stalker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_spore_strider";
    newscript->GetAI = &GetAI_mob_spore_strider;
    newscript->RegisterSelf();
}
