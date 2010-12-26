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
SDName: Boss_Anomalus
SD%Complete: 50%
SDComment: TODO: remove hacks, add support for rift charging
SDCategory: Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

enum
{
    SAY_AGGRO                           = -1576006,
    SAY_RIFT                            = -1576007,
    SAY_SHIELD                          = -1576008,
    SAY_KILL                            = -1576009,
    SAY_DEATH                           = -1576010,
    EMOTE_OPEN_RIFT                     = -1576021,
    EMOTE_SHIELD                        = -1576022,

    // Anomalus
    SPELL_CREATE_RIFT                   = 47743,
    SPELL_CHARGE_RIFT                   = 47747,
    SPELL_RIFT_SHIELD                   = 47748,

    SPELL_SPARK                         = 47751,
    SPELL_SPARK_H                       = 57062,

    SPELL_ARCANE_FORM                   = 48019,
    // Chaotic Rift
    SPELL_RIFT_AURA                     = 47687,
    SPELL_RIFT_AURA_H                   = 47733,
    SPELL_RIFT_SUMMON_AURA              = 47732,
    SPELL_RIFT_SUMMON_AURA_H            = 47742,

    // Charged Chaotic Rift
    SPELL_CHARGED_RIFT_AURA             = 47733,
    SPELL_CHARGED_RIFT_SUMMON_AURA      = 47742
};

/*######
## boss_anomalus
######*/

struct MANGOS_DLL_DECL boss_anomalusAI : public ScriptedAI
{
    boss_anomalusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool   m_bChaoticRift;
    uint32 m_uiSparkTimer;
    uint64 m_uiChaoticRiftGUID;

    void Reset()
    {
        m_bChaoticRift = false;
        m_uiSparkTimer = 5000;

        Creature* pRift = m_creature->GetMap()->GetCreature(m_uiChaoticRiftGUID);
        if (pRift && pRift->isAlive())
            pRift->ForcedDespawn();

        m_uiChaoticRiftGUID = 0;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        Creature* pRift = m_creature->GetMap()->GetCreature(m_uiChaoticRiftGUID);
        if (pRift && pRift->isAlive())
            pRift->ForcedDespawn();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (urand(0, 1))
            DoScriptText(SAY_KILL, m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        DoScriptText(SAY_RIFT, m_creature);
        m_uiChaoticRiftGUID = pSummoned->GetGUID();

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            pSummoned->AI()->AttackStart(pTarget);
               
        pSummoned->CastSpell(pSummoned, SPELL_ARCANE_FORM, true);
        pSummoned->CastSpell(pSummoned, SPELL_CHARGED_RIFT_AURA, true);
        pSummoned->CastSpell(pSummoned, SPELL_CHARGED_RIFT_SUMMON_AURA, true);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (m_creature->HasAura(SPELL_RIFT_SHIELD))
            m_creature->RemoveAurasDueToSpell(SPELL_RIFT_SHIELD);
        m_creature->InterruptSpell(CURRENT_CHANNELED_SPELL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() || m_creature->HasAura(SPELL_RIFT_SHIELD))
             return;

        // Create additional Chaotic Rift at 50% HP
        if (!m_bChaoticRift && m_creature->GetHealthPercent() < 50.0f)
        {
            DoCastSpellIfCan(m_creature, SPELL_CREATE_RIFT, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_RIFT_SHIELD, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_CHARGE_RIFT, CAST_FORCE_CAST);
            DoScriptText(EMOTE_OPEN_RIFT, m_creature);
            DoScriptText(EMOTE_SHIELD, m_creature);
            DoScriptText(SAY_SHIELD, m_creature);
            m_bChaoticRift = true;
            return;
        }

        if (m_uiSparkTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_SPARK : SPELL_SPARK_H);

            m_uiSparkTimer = 5000;
        }
        else
            m_uiSparkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anomalus(Creature* pCreature)
{
    return new boss_anomalusAI(pCreature);
}

void AddSC_boss_anomalus()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_anomalus";
    newscript->GetAI = &GetAI_boss_anomalus;
    newscript->RegisterSelf();
}
