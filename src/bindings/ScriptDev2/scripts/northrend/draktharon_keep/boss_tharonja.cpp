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
SDName: Boss_Tharonja
SD%Complete: 90%
SDAuthor:
SDComment:
SDCategory: Drak'Tharon Keep
EndScriptData */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    SAY_AGGRO                       = -1600012,
    SAY_KILL_1                      = -1600013,
    SAY_KILL_2                      = -1600014,
    SAY_FLESH_1                     = -1600015,
    SAY_FLESH_2                     = -1600016,
    SAY_SKELETON_1                  = -1600017,
    SAY_SKELETON_2                  = -1600018,
    SAY_DEATH                       = -1600019,

    //skeletal spells (phase 1)
    SPELL_CURSE_OF_LIFE             = 49527,
    H_SPELL_CURSE_OF_LIFE           = 59972,
    SPELL_RAIN_OF_FIRE              = 49518,
    H_SPELL_RAIN_OF_FIRE            = 59971,
    SPELL_SHADOW_VOLLEY             = 49528,
    H_SPELL_SHADOW_VOLLEY           = 59973,
    SPELL_DECAY_FLESH               = 49356, //casted at end of phase 1, starts phase 2
    //flesh spells (phase 2)
    SPELL_GIFT_OF_THARON_JA         = 52509,
    SPELL_CLEAR_GIFT_OF_THARONJA    = 53242,
    SPELL_EYE_BEAM                  = 49544,
    H_SPELL_EYE_BEAM                = 59965,
    SPELL_LIGHTNING_BREATH          = 49537,
    H_SPELL_LIGHTNING_BREATH        = 59963,
    SPELL_POISON_CLOUD              = 49548,
    H_SPELL_POISON_CLOUD            = 59969,
    SPELL_RETURN_FLESH              = 53463, //Channeled spell ending phase two and returning to phase 1. This ability will stun the party for 6 seconds.

    // Phases
    SKELETAL                        = 0,                        
    GOING_FLESH                     = 1,
    FLESH                           = 2,
    GOING_SKELETAL                  = 3
};

/*######
## boss_tharonja
######*/

struct MANGOS_DLL_DECL boss_tharonjaAI : public ScriptedAI
{
    boss_tharonjaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bIsRegularMode;
    bool bFlashPhaseDone;
    uint32 uiPhaseTimer;
    uint32 uiCurseOfLifeTimer;
    uint32 uiRainOfFireTimer;
    uint32 uiShadowVolleyTimer;
    uint32 uiEyeBeamTimer;
    uint32 uiLightningBreathTimer;
    uint32 uiPoisonCloudTimer;
    uint8 Phase;

    void Reset()
    {
        uiPhaseTimer = 20000;
        uiCurseOfLifeTimer = 1000;
        uiRainOfFireTimer = urand(14000, 18000);
        uiShadowVolleyTimer = urand(8000, 10000);
        uiLightningBreathTimer = urand(3000, 4000);
        uiEyeBeamTimer = urand(4000, 8000);
        uiPoisonCloudTimer = urand(6000, 7000);
        Phase = SKELETAL;
        bFlashPhaseDone = false;
        //m_creature->SetDisplayId(m_creature->GetNativeDisplayId());
        
        if (m_pInstance)
            m_pInstance->SetData(TYPE_THARONJA, NOT_STARTED);
    }
   
    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature, pWho);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_THARONJA, IN_PROGRESS);
    }
   
    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch (Phase)
        {
            case SKELETAL:
                if (!bFlashPhaseDone)
                {
                    if (uiPhaseTimer <= uiDiff)
                    {
                        DoCastSpellIfCan(m_creature, SPELL_DECAY_FLESH, CAST_INTERRUPT_PREVIOUS);
                        ++Phase;
                        uiPhaseTimer = 6000;
                        break;
                    }
                    else
                        uiPhaseTimer -= uiDiff;
                }
                if (uiCurseOfLifeTimer <= uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_CURSE_OF_LIFE : H_SPELL_CURSE_OF_LIFE);
                    uiCurseOfLifeTimer = urand(10000, 15000);
                }
                else
                    uiCurseOfLifeTimer -= uiDiff;
               
                if (uiShadowVolleyTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature,  m_bIsRegularMode ? SPELL_SHADOW_VOLLEY : H_SPELL_SHADOW_VOLLEY);
                    uiShadowVolleyTimer = urand(8000, 10000);
                }
                else
                    uiShadowVolleyTimer -= uiDiff;
               
                if (uiRainOfFireTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_RAIN_OF_FIRE : H_SPELL_RAIN_OF_FIRE);
                    uiRainOfFireTimer = urand(14000, 18000);
                }
                else
                    uiRainOfFireTimer -= uiDiff;

                DoMeleeAttackIfReady();
                break;
            case GOING_FLESH:
                if (uiPhaseTimer <= uiDiff)
                {
                    DoScriptText(urand(0, 1) ? SAY_FLESH_1 : SAY_FLESH_2, m_creature);
                    DoCastSpellIfCan(m_creature, SPELL_GIFT_OF_THARON_JA, CAST_INTERRUPT_PREVIOUS);
                    uiPhaseTimer = 20000;
                    ++Phase;
                }
                else
                    uiPhaseTimer -= uiDiff;
                break;
            case FLESH:
                if (uiLightningBreathTimer <= uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_LIGHTNING_BREATH : H_SPELL_LIGHTNING_BREATH);
                    uiLightningBreathTimer = urand(6000, 7000);
                }
                else
                    uiLightningBreathTimer -= uiDiff;

                if (uiEyeBeamTimer <= uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_EYE_BEAM : H_SPELL_EYE_BEAM);
                    uiEyeBeamTimer = urand(4000, 6000);
                }
                else
                    uiEyeBeamTimer -= uiDiff;

                if (uiPoisonCloudTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_POISON_CLOUD : H_SPELL_POISON_CLOUD);
                    uiPoisonCloudTimer = urand(10000, 12000);
                }
                else
                    uiPoisonCloudTimer -= uiDiff;
               
                if (uiPhaseTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_RETURN_FLESH);
                    ++Phase;
                    uiPhaseTimer = 6000;
                }
                else
                    uiPhaseTimer -= uiDiff;

                DoMeleeAttackIfReady();
                break;
            case GOING_SKELETAL:
                if (uiPhaseTimer <= uiDiff)
                {
                    DoScriptText(urand(0, 1) ? SAY_SKELETON_1 : SAY_SKELETON_2, m_creature);
                    //m_creature->DeMorph();
                    Phase = SKELETAL;
                    uiPhaseTimer = 20000;
                    DoCastSpellIfCan(m_creature, SPELL_CLEAR_GIFT_OF_THARONJA, CAST_INTERRUPT_PREVIOUS);
                    // since 3.0.2 only one tranformation cycle allowed
                    bFlashPhaseDone = true;
                }
                else
                    uiPhaseTimer -= uiDiff;
                break;
        }
    }


    void KilledUnit(Unit *pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_KILL_1 : SAY_KILL_2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_THARONJA, DONE);
    }
};

CreatureAI* GetAI_boss_tharonja(Creature* pCreature)
{
    return new boss_tharonjaAI(pCreature);
}

void AddSC_boss_tharonja()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_tharonja";
    pNewScript->GetAI = &GetAI_boss_tharonja;
    pNewScript->RegisterSelf();
}
