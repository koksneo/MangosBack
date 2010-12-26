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
SDName: Boss Loken
SD%Complete: 60%
SDComment: Missing intro. Remove hack of Pulsing Shockwave when core supports. Aura is not working (59414)
SDCategory: Halls of Lightning
EndScriptData */

#include "precompiled.h"
#include "halls_of_lightning.h"

enum
{
    SAY_AGGRO                           = -1602018,
    SAY_INTRO_1                         = -1602019,
    SAY_INTRO_2                         = -1602020,
    SAY_SLAY_1                          = -1602021,
    SAY_SLAY_2                          = -1602022,
    SAY_SLAY_3                          = -1602023,
    SAY_DEATH                           = -1602024,
    SAY_NOVA_1                          = -1602025,
    SAY_NOVA_2                          = -1602026,
    SAY_NOVA_3                          = -1602027,
    SAY_75HEALTH                        = -1602028,
    SAY_50HEALTH                        = -1602029,
    SAY_25HEALTH                        = -1602030,
    EMOTE_NOVA                          = -1602031,

    SPELL_ARC_LIGHTNING                 = 52921,
    SPELL_LIGHTNING_NOVA_N              = 52960,
    SPELL_LIGHTNING_NOVA_H              = 59835,
    SPELL_LIGHTNING_NOVA_VISUAL         = 56495,

    SPELL_PULSING_SHOCKWAVE_N           = 52961,
    SPELL_PULSING_SHOCKWAVE_H           = 59836,
    SPELL_PULSING_SHOCKWAVE_AURA        = 59414
};

/*######
## Boss Loken
######*/

struct MANGOS_DLL_DECL boss_lokenAI : public ScriptedAI
{
    boss_lokenAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bIsRegularMode;

    uint32 m_uiArcLightning_Timer;
    uint32 m_uiLightningNova_Timer;
    uint32 m_uiHealthAmountModifier;

    void Reset()
    {
        m_uiArcLightning_Timer = 15000;
        m_uiLightningNova_Timer = 20000;

        m_uiHealthAmountModifier = 1;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_LOKEN, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_LOKEN, IN_PROGRESS);

        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_PULSING_SHOCKWAVE_N : SPELL_PULSING_SHOCKWAVE_H);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_LOKEN, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature);break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature);break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature);break;
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_creature->isInCombat() && pWho && !pWho->HasAura(SPELL_PULSING_SHOCKWAVE_AURA))
            DoCastSpellIfCan(m_creature, SPELL_PULSING_SHOCKWAVE_AURA, CAST_TRIGGERED);

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiLightningNova_Timer < uiDiff)
        {
            switch(urand(0, 2))
            {
                case 0: DoScriptText(SAY_NOVA_1, m_creature);break;
                case 1: DoScriptText(SAY_NOVA_2, m_creature);break;
                case 2: DoScriptText(SAY_NOVA_3, m_creature);break;
            }
            DoScriptText(EMOTE_NOVA, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_LIGHTNING_NOVA_VISUAL, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_LIGHTNING_NOVA_N : SPELL_LIGHTNING_NOVA_H);
            m_uiLightningNova_Timer = urand(18000, 21000);
        }
        else
            m_uiLightningNova_Timer -= uiDiff;

        if (m_uiArcLightning_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_ARC_LIGHTNING);

            m_uiArcLightning_Timer = urand(15000, 16000);
        }
        else
            m_uiArcLightning_Timer -= uiDiff;

        // Health check
        if (m_creature->GetHealthPercent() < float(100 - 25*m_uiHealthAmountModifier))
        {
            switch(m_uiHealthAmountModifier)
            {
                case 1: DoScriptText(SAY_75HEALTH, m_creature); break;
                case 2: DoScriptText(SAY_50HEALTH, m_creature); break;
                case 3: DoScriptText(SAY_25HEALTH, m_creature); break;
            }

            ++m_uiHealthAmountModifier;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_loken(Creature* pCreature)
{
    return new boss_lokenAI(pCreature);
}

void AddSC_boss_loken()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_loken";
    newscript->GetAI = &GetAI_boss_loken;
    newscript->RegisterSelf();
}
