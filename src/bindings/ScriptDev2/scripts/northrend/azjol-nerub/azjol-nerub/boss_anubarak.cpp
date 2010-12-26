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
SDName: Boss_Anubarak
SD%Complete: 20%
SDComment:
SDCategory: Azjol'NerubstrInstData
EndScriptData */


#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    SPELL_CARRION_BEETLES           = 53520,
    SPELL_SUMMON_CARRION_BEETLES    = 53521,
    SPELL_LEECHING_SWARM            = 53467,

    SPELL_IMPALE                    = 53454,
    H_SPELL_IMPALE                  = 59446,

    SPELL_POUND                     = 53472,
    H_SPELL_POUND                   = 59433,

    SPELL_SUBMERGE                  = 53421,

    CREATURE_GUARDIAN               = 29216,
    CREATURE_VENOMANCER             = 29217,
    CREATURE_DATTER                 = 29213,

    SAY_INTRO                       = -1601014,
    SAY_AGGRO                       = -1601015,
    SAY_KILL_1                      = -1601016,
    SAY_KILL_2                      = -1601017,
    SAY_KILL_3                      = -1601018,
    SAY_SUBMERGE_1                  = -1601019,
    SAY_SUBMERGE_2                  = -1601020,
    SAY_LOCUST_1                    = -1601021,
    SAY_LOCUST_2                    = -1601022,
    SAY_LOCUST_3                    = -1601023,
    SAY_DEATH                       = -1601024
};                          

struct MANGOS_DLL_DECL boss_anubarakAI : public ScriptedAI
{
    boss_anubarakAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_azjol_nerub*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_azjol_nerub* m_pInstance;

    bool bChanneling;
    bool m_bIsRegularMode;
    bool bSummoned_Guardian;
    bool bSummoned_Venomancer;
    bool bSummoned_Datter;
    uint8 Phase;
    uint32 m_uiPhase_Time;

    uint32 m_uiCarrionBittles_Timer;
    uint32 m_uiLeechingSwarm_Timer;
    uint32 m_uiImpale_Timer;
    uint32 m_uiSpellPound_Timer;
    uint32 m_uiSpellSubmerge_Timer;
    uint32 m_uiUnderground_Timer;
    uint32 m_uiVenomancer_Timer;
    uint32 m_uiDatter_Timer;

    void Reset()
    {

        m_uiCarrionBittles_Timer = 8000;
        m_uiLeechingSwarm_Timer = 20000;
        m_uiImpale_Timer = 9000;
        m_uiSpellPound_Timer = 15000;

        Phase = 0;
        m_uiPhase_Time = 0;
        bChanneling = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
        
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUBARAK, NOT_STARTED);
    }


    void Aggro(Unit *pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUBARAK, IN_PROGRESS);
    }


    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
           return;  

        if (bChanneling == true)
        {
            for (uint8 i = 0; i < 4; ++i)
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUMMON_CARRION_BEETLES);
            bChanneling = false;
        }

        if (Phase == 1)
        {
            if (m_uiImpale_Timer <= uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_IMPALE : H_SPELL_IMPALE);
                m_uiImpale_Timer = 9000;
            } else m_uiImpale_Timer -= uiDiff;

            if (!bSummoned_Guardian)
            {
                // has to be done by spell!!!!!
                for (uint8 i = 0; i < 2; ++i)
                {
                    if (Creature *Guardian = m_creature->SummonCreature(CREATURE_GUARDIAN,550,282,224,0,TEMPSUMMON_CORPSE_DESPAWN,0))
                    {
                        Guardian->AddThreat(m_creature->getVictim(), 0.0f);
                    }
                }
                bSummoned_Guardian = true;
            }

            if(!bSummoned_Venomancer)
            {
                // Has to be done by spell!!!!!
                if (m_uiVenomancer_Timer <= uiDiff)
                {
                    if (m_uiPhase_Time > 1)
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Creature *Venomancer = m_creature->SummonCreature(CREATURE_VENOMANCER,550,282,224,0,TEMPSUMMON_CORPSE_DESPAWN,0))
                            {
                                Venomancer->AddThreat(m_creature->getVictim(), 0.0f);
                            }
                        }
                        bSummoned_Venomancer = true;
                    }
                } else m_uiVenomancer_Timer -= uiDiff;
            }

            if(!bSummoned_Datter)
            {
                if (m_uiDatter_Timer <= uiDiff)
                {
                    // has to be done by spell!!!!
                    if (m_uiPhase_Time > 2)
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Creature *Datter = m_creature->SummonCreature(CREATURE_DATTER,550,282,224,0,TEMPSUMMON_CORPSE_DESPAWN,0))
                            {
                                Datter->AddThreat(m_creature->getVictim(), 0.0f);
                            }
                        }
                        bSummoned_Datter = true;
                    }
                } else m_uiDatter_Timer -= uiDiff;
            }

            if (m_uiUnderground_Timer <= uiDiff)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                Phase = 0;
            } else m_uiUnderground_Timer -= uiDiff;
        }

        if (Phase == 0)
        {
            if (m_uiLeechingSwarm_Timer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_LEECHING_SWARM, true);
                m_uiLeechingSwarm_Timer = 19000;
            } else m_uiLeechingSwarm_Timer -= uiDiff;

            if (m_uiCarrionBittles_Timer <= uiDiff)
            {
                bChanneling = true;
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_CARRION_BEETLES);
                m_uiCarrionBittles_Timer = 25000;
            } else m_uiCarrionBittles_Timer -= uiDiff;

            if (m_uiSpellPound_Timer <= uiDiff)
            {
                 DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_POUND : H_SPELL_POUND);
                 m_uiSpellPound_Timer = 16500;
            } else m_uiSpellPound_Timer -= uiDiff;
        }

        if ((m_uiPhase_Time == 0 && m_creature->GetHealthPercent() <= 75.0f)
            || (m_uiPhase_Time == 1 && m_creature->GetHealthPercent() <= 50.0f)
            || (m_uiPhase_Time == 2 && m_creature->GetHealthPercent() <= 25.0f))
        {
            ++m_uiPhase_Time;

            bSummoned_Guardian = false;
            bSummoned_Venomancer = false;
            bSummoned_Datter = false;

            m_uiUnderground_Timer = 40000;
            m_uiVenomancer_Timer = 25000;
            m_uiDatter_Timer = 32000;

            DoCastSpellIfCan(m_creature, SPELL_SUBMERGE);

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);

            Phase = 1;
        }

        if (Phase != 1)
            DoMeleeAttackIfReady();
    }
    
    void JustDied(Unit *pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUBARAK, DONE);
    }

    void KilledUnit(Unit *pVictim)
    {
        DoScriptText(urand(0, 1) > 0 ? SAY_KILL_2 : SAY_KILL_3, m_creature);
    }
};

CreatureAI* GetAI_boss_anubarak(Creature *pCreature)
{
    return new boss_anubarakAI (pCreature);
}

void AddSC_boss_anubarak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_anubarak";
    pNewScript->GetAI = &GetAI_boss_anubarak;
    pNewScript->RegisterSelf();
}
