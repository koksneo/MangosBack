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
SDName: Boss_Archavon_The_Stone_Watcher
SD%Complete: 0%
SDComment:
SDCategory: Vault of Archavon
EndScriptData */

#include "precompiled.h"
#include "vault_of_archavon.h"

enum                                                 // cast    | durat.| effect    | eitA/B
{
    SPELL_ROCK_SHARDS_PERIODIC              = 58678, //  0.5s   |    3s | proc 58941|  6/0 
    SPELL_CRUSHING_LEAP_N                   = 58960, //     0   |       | jump/missile| 53/0 87/0
    SPELL_CRUSHING_LEAP_H                   = 60894,
    SPELL_STOMP_N                           = 58663,
    SPELL_STOMP_H                           = 60880,
    SPELL_IMPALE_PERIODIC_SUMMON_AURA       = 53456,
    SPELL_IMPALE_DMG_N                      = 58666, //     0   |       | sch dmg + sanctuary  | 6 / 0
    SPELL_IMPALE                            = 58672, //     0   |   8   | control veh + stun | 38 / 0
    SPELL_IMPALE_DMG_H                      = 60882,
    SPELL_IMPALE_STUN                       = 50839,
    SPELL_BERSERK                           = 47008
};

struct MANGOS_DLL_DECL boss_archavonAI : public ScriptedAI
{
    boss_archavonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiBerserkTimer;
    uint32 m_uiRockShardsTimer;
    uint32 m_uiCrushingLeapTimer;
    uint32 m_uiStompTimer;

    void Reset()
    {
        m_uiBerserkTimer        = 5 *MINUTE*IN_MILLISECONDS;
        m_uiRockShardsTimer     = 20000;
        m_uiCrushingLeapTimer   = 25000;
        m_uiStompTimer          = 1 *MINUTE*IN_MILLISECONDS;
        m_creature->RemoveAurasDueToSpell(SPELL_IMPALE_PERIODIC_SUMMON_AURA);
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, IN_PROGRESS);

        DoCastSpellIfCan(m_creature, SPELL_IMPALE_PERIODIC_SUMMON_AURA, CAST_TRIGGERED);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBerserkTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BERSERK);
            m_uiBerserkTimer = 30 * MINUTE * IN_MILLISECONDS;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        if (m_uiRockShardsTimer <= uiDiff)
        {
            // according to YT vid target can be also pet
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_ROCK_SHARDS_PERIODIC);
            m_uiRockShardsTimer = 10000;
        }
        else
            m_uiRockShardsTimer -= uiDiff;

        if (m_uiCrushingLeapTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_CRUSHING_LEAP_N : SPELL_CRUSHING_LEAP_H) == CAST_OK)
                    m_uiCrushingLeapTimer = urand(30000, 35000);
        }
        else
            m_uiCrushingLeapTimer -= uiDiff;

        if (m_uiStompTimer <= uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_STOMP_N : SPELL_STOMP_H) == CAST_OK)
            {
                // hack
                float fPosX, fPosY, fPosZ;
                m_creature->GetClosePoint(fPosX, fPosY, fPosZ, m_creature->GetObjectBoundingRadius(), 50.0f);
                pVictim->SendMonsterMove(fPosX, fPosY, fPosZ, SPLINETYPE_NORMAL, SPLINEFLAG_PITCH_UP, 7000);
                m_uiStompTimer = 1 *MINUTE*IN_MILLISECONDS;
            }
        }
        else
            m_uiStompTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_archavon(Creature *pCreature)
{
    return new boss_archavonAI (pCreature);
}

void AddSC_boss_archavon()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_archavon";
    newscript->GetAI = &GetAI_boss_archavon;
    newscript->RegisterSelf();
}
