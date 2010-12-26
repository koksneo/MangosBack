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
SDName: Boss_Patchwerk
SD%Complete: 100
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_AGGRO1            = -1533017,
    SAY_AGGRO2            = -1533018,
    SAY_SLAY              = -1533019,
    SAY_DEATH             = -1533020,

    EMOTE_GENERIC_BERSERK   = -1000004,
    EMOTE_GENERIC_ENRAGED   = -1000003,

    SPELL_HATEFULSTRIKE   = 28308,
    SPELL_HATEFULSTRIKE_H = 59192,
    SPELL_ENRAGE          = 28131,
    SPELL_BERSERK         = 26662,
    SPELL_SLIMEBOLT       = 32309
};

struct MANGOS_DLL_DECL boss_patchwerkAI : public ScriptedAI
{
    boss_patchwerkAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiHatefulStrikeTimer;
    uint32 m_uiBerserkTimer;
    uint32 m_uiSlimeboltTimer;
    bool   m_bEnraged;
    bool   m_bBerserk;

    void Reset()
    {
        m_uiHatefulStrikeTimer = 1000;                      //1 second
        m_uiBerserkTimer = MINUTE*6*IN_MILLISECONDS;         //6 minutes
        m_uiSlimeboltTimer = 10000;
        m_bEnraged = false;
        m_bBerserk = false;
    }

    void KilledUnit(Unit* pVictim)
    {
        if (urand(0, 4))
            return;

        DoScriptText(SAY_SLAY, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_PATCHWERK, DONE);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(urand(0, 1)?SAY_AGGRO1:SAY_AGGRO2, m_creature);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_PATCHWERK, IN_PROGRESS);

        // call all creatures in area
        if (!m_pInstance->lPatchwerkAreaMobs.empty())
            for (std::list<uint64>::iterator itr = m_pInstance->lPatchwerkAreaMobs.begin(); itr != m_pInstance->lPatchwerkAreaMobs.end(); ++itr)
            {
                Creature* pCreature = m_creature->GetMap()->GetCreature(*itr);
                if (pCreature && pCreature->isAlive() && !pCreature->isInCombat() && pCreature->AI())
                    pCreature->AI()->AttackStart(pWho);
            }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_PATCHWERK, FAIL);
    }

    void DoHatefulStrike()
    {
        // The ability is used on highest HP target choosen of the top 2 (3 heroic) targets on threat list being in melee range
        // Targets must be less than first in threat, but at least second/third highest threat. This requirement does not apply if only one target is in melee range.
        Unit* pTarget = NULL;
        Unit *pMainTarget = NULL;
        uint32 uiHighestHP = 0;
        uint32 uiTargets = m_bIsRegularMode ? 2 : 3;

        ThreatList const& tList = m_creature->getThreatManager().getThreatList();

        if (!tList.empty())
            pMainTarget = m_creature->GetMap()->GetUnit(tList.front()->getUnitGuid());

        for (ThreatList::const_iterator iter = tList.begin();iter != tList.end(); ++iter)
        {
            if (!uiTargets--)
                break;

            if (Unit* pTempTarget = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid()))
            {
                if (pTempTarget == pMainTarget)
                    continue;

                if (pTempTarget->GetHealth() > uiHighestHP && m_creature->IsWithinDistInMap(pTempTarget, ATTACK_DISTANCE))
                {
                    uiHighestHP = pTempTarget->GetHealth();
                    pTarget = pTempTarget;
                }
            }
        }

        // no target within melee range, so check the main target
        if (!pTarget && pMainTarget)
            if (m_creature->IsWithinDistInMap(pMainTarget, ATTACK_DISTANCE) )
                pTarget = pMainTarget;

        // if main target is not within melee range, then select any nearby target
        if (!pTarget)
            pTarget = m_creature->SelectRandomUnfriendlyTarget(0, ATTACK_DISTANCE);

        if (pTarget)
            DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_HATEFULSTRIKE : SPELL_HATEFULSTRIKE_H);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Hateful Strike
        if (m_uiHatefulStrikeTimer < uiDiff)
        {
            DoHatefulStrike();
            m_uiHatefulStrikeTimer = 1000;
        }
        else
            m_uiHatefulStrikeTimer -= uiDiff;

        // Soft Enrage at 5%
        if (!m_bEnraged)
        {
            if (m_creature->GetHealthPercent() < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_ENRAGE) == CAST_OK)
                {
                    DoScriptText(EMOTE_GENERIC_ENRAGED, m_creature);
                    m_bEnraged = true;
                }
            }
        }

        // Berserk after 6 minutes
        if (!m_bBerserk)
        {
            if (m_uiBerserkTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
                {
                    DoScriptText(EMOTE_GENERIC_BERSERK, m_creature);
                    m_bBerserk = true;
                }
            }
            else
                m_uiBerserkTimer -= uiDiff;
        }
        else
        {
            // Slimebolt - casted only while Berserking to prevent kiting
            if (m_uiSlimeboltTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_SLIMEBOLT);
                m_uiSlimeboltTimer = 5000;
            }
            else
                m_uiSlimeboltTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_patchwerk(Creature* pCreature)
{
    return new boss_patchwerkAI(pCreature);
}

/******
** mob_living_poison
******/
enum
{
    ENTRY_LIVING_POISON   = 16027,
    SPELL_EXPLODE         = 28433,
    FROGGER_DEST_DISTANCE = 36
};
struct MANGOS_DLL_DECL mob_living_poisonAI : public ScriptedAI
{
    mob_living_poisonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsTempSummon = m_creature->IsTemporarySummon();
        Reset();
    }

    bool m_bIsTempSummon;
    uint32 uiSummonTimer;

    void Reset()
    {
        uiSummonTimer = 6000;
        if (!m_bIsTempSummon)
            m_creature->SetVisibility(VISIBILITY_OFF);
    }

    void MoveInLineOfSight(Unit* pVictim)
    {
        if (!m_bIsTempSummon || !m_creature->IsHostileTo(pVictim) )
            return;

        if (m_creature->GetDistance2d(pVictim) < 4.5f)
            DoCastSpellIfCan(m_creature, SPELL_EXPLODE, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsTempSummon)
            return;

        if (uiSummonTimer < uiDiff)
        {
            if (Creature* pCreature = m_creature->SummonCreature(ENTRY_LIVING_POISON, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 15000) )
            {
                float fPointX, fPointY;
                m_creature->GetNearPoint2D(fPointX, fPointY, float(FROGGER_DEST_DISTANCE), m_creature->GetOrientation());
                pCreature->GetMotionMaster()->MovePoint(1, fPointX, fPointY, pCreature->GetPositionZ() );
            }
            uiSummonTimer = 6000;
        }
        else uiSummonTimer -= uiDiff;
    }

};
CreatureAI* GetAI_mob_living_poison(Creature* pCreature)
{
    return new mob_living_poisonAI(pCreature);
}

void AddSC_boss_patchwerk()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_patchwerk";
    NewScript->GetAI = &GetAI_boss_patchwerk;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_living_poison";
    NewScript->GetAI = &GetAI_mob_living_poison;
    NewScript->RegisterSelf();
}
