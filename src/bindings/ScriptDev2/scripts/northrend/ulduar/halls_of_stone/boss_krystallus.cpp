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
SDName: Boss Krystallus
SDAuthor: Gelu thank ckegg for some ideas
SD%Complete: 80%
SDComment: Spell shatter must be fixed.
SDCategory: Halls of Stone
EndScriptData */


#include "precompiled.h"
#include "halls_of_stone.h"


enum
{
    SAY_AGGRO                          = -1599066,
    SAY_SHATTER                        = -1599067,
    SAY_KILL                           = -1599068,
    SAY_DEATH                          = -1599069,

    SPELL_BOULDER_TOSS                  = 50843,
    SPELL_BOULDER_TOSS_H                = 59742,
    SPELL_GROUND_SPIKE                  = 59750,
    SPELL_GROUND_SLAM                   = 50827,
    SPELL_SHATTER                       = 50810,
    SPELL_SHATTER_H                     = 61546,
    SPELL_SHATTER_EFFECT                = 50811,
    SPELL_SHATTER_EFFECT_H              = 61547,
    SPELL_STONED                        = 50812,
    SPELL_STOMP                         = 50868,
    SPELL_STOMP_H                       = 59744
};


/*######
## boss_krystallus
######*/

struct MANGOS_DLL_DECL boss_krystallusAI : public ScriptedAI
{
    boss_krystallusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsSlam;

    uint32 m_uiToss_Timer;
    uint32 m_uiSpike_Timer;
    uint32 m_uiSlam_Timer;
    uint32 m_uiShatter_Timer;
    uint32 m_uiStomp_Timer;

    void Reset()
    {
        m_bIsSlam = false;
        m_uiToss_Timer = urand(3000, 9000);
        m_uiSpike_Timer = urand(9000, 14000);
        m_uiSlam_Timer = urand(15000, 18000);
        m_uiStomp_Timer = urand(20000, 29000);
        m_uiShatter_Timer = 0;

        if(m_pInstance)
            m_pInstance->SetData(TYPE_KRYSTALLUS, NOT_STARTED);
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO,m_creature);

        if(m_pInstance)
            m_pInstance->SetData(TYPE_KRYSTALLUS, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KRYSTALLUS, DONE);
    }

    void SpellHitTarget(Unit* pTarget, const SpellEntry* pSpell)
    {
        //this part must be in core??
        if (pSpell->Id == SPELL_SHATTER || pSpell->Id == SPELL_SHATTER_H)
        {
            //this spell must have custom handling in the core, dealing damage based on distance
            pTarget->CastSpell(pTarget, m_bIsRegularMode ? SPELL_SHATTER_EFFECT : SPELL_SHATTER_EFFECT_H, true);

            if (pTarget->HasAura(SPELL_STONED))
                pTarget->RemoveAurasDueToSpell(SPELL_STONED);

            //clear this, if we are still performing
            if (m_bIsSlam)
            {
                m_bIsSlam = false;

                //and correct movement, if not already
                if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != CHASE_MOTION_TYPE)
                {
                    if (Unit *pTarget = m_creature->getVictim())
                        m_creature->GetMotionMaster()->MoveChase(pTarget);
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Boulder Toss
        if (m_uiToss_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_BOULDER_TOSS : SPELL_BOULDER_TOSS_H) == CAST_OK)
                    m_uiToss_Timer = urand(9000, 15000);
        }
        else
            m_uiToss_Timer -= uiDiff;

        // Spike - cast only on heroic mode
        if(!m_bIsRegularMode)
        {
            if (m_uiSpike_Timer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    if (DoCastSpellIfCan(pTarget, SPELL_GROUND_SPIKE) == CAST_OK)
                        m_uiSpike_Timer = urand(12000, 17000);
            }
            else
                m_uiSpike_Timer -= uiDiff;
        }
 
        // Stomp
        if (m_uiStomp_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_STOMP : SPELL_STOMP_H) == CAST_OK)
            m_uiStomp_Timer = urand(20000, 29000);
        }
        else
            m_uiStomp_Timer -= uiDiff;
 
        // Ground Slam
        if (m_uiSlam_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_GROUND_SLAM) == CAST_OK)
            {
                m_bIsSlam = true;
                m_uiShatter_Timer = 10000;
                m_uiSlam_Timer = urand(15000, 18000);
            }
        }
        else
            m_uiSlam_Timer -= uiDiff;
 
        // Shatter
        if (m_bIsSlam)
        {
            if (m_uiShatter_Timer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHATTER : SPELL_SHATTER_H) == CAST_OK)
                    m_bIsSlam = false;
            }
            else
                m_uiShatter_Timer -= uiDiff;
        }
 
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_krystallus(Creature* pCreature)
{
    return new boss_krystallusAI (pCreature);
}

void AddSC_boss_krystallus()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_krystallus";
    newscript->GetAI = &GetAI_boss_krystallus;
    newscript->RegisterSelf();
}
