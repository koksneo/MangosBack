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

/* Script Data Start
SDName: Boss trollgore
SDAuthor: Tartalo modified for Mangos by Aramil
SD%Complete: 99%
Script Data End */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    SPELL_INFECTED_WOUND                = 49637,
    SPELL_CRUSH                         = 49639,
    SPELL_CONSUME                       = 49380,
    SPELL_CONSUME_H                     = 59803,
    SPELL_CORPSE_VISUAL                 = 51270,

    SPELL_SUMMON_INVADER_A              = 49456,
    SPELL_SUMMON_INVADER_B              = 49457,        // dunno what is for? 49458 will summon "corpse" of Invader after it's death

    SAY_AGGRO                           = -1600000,
    SAY_CONSUME                         = -1600001,
    SAY_DEATH                           = -1600002,
    SAY_EXPLODE                         = -1600003,
    SAY_KILL                            = -1600004,

    NPC_TROLLGORE_SUMMONER              = 40003,        // custom npc, when propper entry will be found - should be moved to instance_script
    NPC_DRAKTAR_INVIDER_C               = 27754         // "corpse" summoned by dead Draktar Invider using spell SPELL_SUMMON_INVADER_C (ACID)
};

struct MANGOS_DLL_DECL boss_trollgoreAI : public ScriptedAI
{
    boss_trollgoreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    uint32 m_uiConsumeTimer;
    uint32 uiAuraCountTimer;
    uint32 m_uiCrushTimer;
    uint32 m_uiInfectedWoundTimer;
    uint32 m_uiExplodeCorpseTimer;
    uint32 m_uiSpawnTimer;
    uint64 m_uiSummonerGUID;

    ScriptedInstance* pInstance;
    
    bool m_bIsRegularMode;    

    void Reset()
    {
        m_uiConsumeTimer = 15000;
        uiAuraCountTimer = 15500;
        m_uiCrushTimer = urand(1000, 5000);
        m_uiInfectedWoundTimer = urand(6000, 10000);
        m_uiExplodeCorpseTimer = 3000;
        m_uiSpawnTimer = urand(10000, 20000);

        if (pInstance)
            pInstance->SetData(DATA_TROLLGORE, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (Unit* pUnit = GetClosestCreatureWithEntry(m_creature, 40003, 50.0f))
            m_uiSummonerGUID = pUnit->GetGUID();

        if (pInstance)
            pInstance->SetData(DATA_TROLLGORE, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (pInstance)
        {
            pInstance->SetData(DATA_TROLLGORE, DONE);
        }
    }
    
    void KilledUnit(Unit *pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSpawnTimer <= uiDiff)
        {
            if (Creature* pUnit = m_creature->GetMap()->GetCreature(m_uiSummonerGUID))
            {
                for (uint8 i = 0; i < (m_bIsRegularMode ? 2 : 3); ++i)
                {
                    pUnit->CastSpell(pUnit, SPELL_SUMMON_INVADER_A, false);
                }
            }
            m_uiSpawnTimer = urand(30000, 40000);
        } else m_uiSpawnTimer -= uiDiff;

        if (m_uiConsumeTimer <= uiDiff)
        {
            // Make sure that Draktar corpse in nearby before processing
            // Maybe there is function checking if cast will be successful?
            Unit* pUnit = GetClosestCreatureWithEntry(m_creature, NPC_DRAKTAR_INVIDER_C, 2*INTERACTION_DISTANCE);
            if (pUnit && pUnit->isAlive() && !pUnit->HasAura(SPELL_CORPSE_VISUAL))
            {
                DoScriptText(SAY_CONSUME, m_creature);
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_CONSUME : SPELL_CONSUME_H);
            }
            m_uiConsumeTimer = 15000;
        } else m_uiConsumeTimer -= uiDiff;

        if (m_uiCrushTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CRUSH);
            m_uiCrushTimer = urand(10000, 15000);
        } else m_uiCrushTimer -= uiDiff;

        if (m_uiInfectedWoundTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_INFECTED_WOUND);
            m_uiInfectedWoundTimer = urand(25000, 35000);
        } else m_uiInfectedWoundTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI (pCreature);
}

void AddSC_boss_trollgore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_trollgore";
    pNewScript->GetAI = &GetAI_boss_trollgore;
    pNewScript->RegisterSelf();
}
