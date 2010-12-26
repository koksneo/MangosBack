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
SDName: Boss_Ingvar
SD%Complete:
SDComment:
SDCategory: Utgarde Keep
EndScriptData */

#include "precompiled.h"
#include "utgarde_keep.h"

enum
{
    SAY_AGGRO_FIRST             = -1574005,
    SAY_AGGRO_SECOND            = -1574006,
    SAY_DEATH_FIRST             = -1574007,
    SAY_DEATH_SECOND            = -1574008,
    SAY_KILL_FIRST              = -1574009,
    SAY_KILL_SECOND             = -1574010,
    SAY_RESSURECTING            = -1999782,
    SAY_ANNHYLDE_REZ            = -1574023,
    EMOTE_ROAR                  = -1574022,

    NPC_ANNHYLDE                = 24068,

    //phase 1
    SPELL_CLEAVE                = 42724,

    SPELL_SMASH                 = 42669,
    SPELL_SMASH_H               = 59706,

    SPELL_ENRAGE                = 42705,
    SPELL_ENRAGE_H              = 59707,

    SPELL_STAGGERING_ROAR       = 42708,
    SPELL_STAGGERING_ROAR_H     = 59708,

    //phase 2
    SPELL_DARK_SMASH            = 42723,
    SPELL_DARK_SMASH_H          = 59709,

    SPELL_DREADFUL_ROAR         = 42729,
    SPELL_DREADFUL_ROAR_H       = 59734,

    SPELL_WOE_STRIKE            = 42730,
    SPELL_WOE_STRIKE_H          = 59735,

    SPELL_SHADOW_AXE            = 42748,

    //ressurection sequenze
    SPELL_SUMMON_BANSHEE        = 42912,
    SPELL_FEIGN_DEATH           = 42795,
    SPELL_TRANSFORM             = 42796,
    SPELL_SCOURGE_RES_SUMMON    = 42863,                    //summones a dummy target
    SPELL_SCOURGE_RES_HEAL      = 42704,                    //heals max HP
    SPELL_SCOURGE_RES_BUBBLE    = 42862,                    //black bubble
    SPELL_SCOURGE_RES_CHANNEL   = 42857,                    //the whirl from annhylde

    PHASE_BEFORE_RESSURECION    = 0,
    PHASE_RESS_SEQUENCE         = 1,
    PHASE_RESSURECTED           = 2
};

/*######
## boss_ingvar
######*/

struct MANGOS_DLL_DECL boss_ingvarAI : public ScriptedAI
{
    boss_ingvarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool m_bIsResurrected;

    uint8  m_uiPhase;
    uint8  m_uiSubevent;
    uint32 m_uiEventTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiSmashTimer;
    uint32 m_uiStaggeringRoarTimer;
    uint32 m_uiEnrageTimer;

    uint32 m_uiDreadfulRoarTimer;
    uint32 m_uiDarkSmashTimer;
    uint32 m_uiWoeStrikeTimer;
    uint32 m_uiShadowAxeTimer;

    uint64 m_uiAnnylideGUID;

    void Reset()
    {
        if (Creature* pAnnylide = m_creature->GetMap()->GetCreature(m_uiAnnylideGUID))
            pAnnylide->ForcedDespawn();
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        m_uiPhase = PHASE_BEFORE_RESSURECION;
        m_uiCleaveTimer = urand(5000, 7000);
        m_uiSmashTimer = urand(8000, 15000);
        m_uiStaggeringRoarTimer = urand(10000, 25000);
        m_uiEnrageTimer = 30000;
        m_uiEventTimer = 0;
        m_uiDreadfulRoarTimer = 0;
        m_uiDarkSmashTimer = urand(15000, 25000);
        m_uiWoeStrikeTimer = 5000;
        m_uiShadowAxeTimer = urand(20000, 30000);

        m_uiAnnylideGUID = 0;
    }

    void Aggro(Unit* pWho)
    {
        if (m_uiPhase == PHASE_BEFORE_RESSURECION)
            DoScriptText(SAY_AGGRO_FIRST, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        switch(m_uiPhase)
        {
            case PHASE_RESS_SEQUENCE:
                uiDamage = 0;
                break;

            case PHASE_BEFORE_RESSURECION:
                if (m_creature->GetHealth() <= uiDamage)
                {
                    uiDamage = 0;
                    m_creature->GetMotionMaster()->Clear(false);
                    m_creature->GetMotionMaster()->MoveIdle();

                    DoScriptText(SAY_DEATH_FIRST, m_creature);
                    m_creature->RemoveAllAuras();
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    m_creature->CastSpell(m_creature, SPELL_FEIGN_DEATH, true);
                    m_uiEventTimer = 3000;
                    m_uiPhase = PHASE_RESS_SEQUENCE;
                    m_uiSubevent = 0;
                }
                break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH_SECOND, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(m_uiPhase == PHASE_RESSURECTED ? SAY_KILL_SECOND : SAY_KILL_FIRST, m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_ANNHYLDE)
        {
            pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            pSummoned->SendMonsterMove(pSummoned->GetPositionX(), pSummoned->GetPositionY(), pSummoned->GetPositionZ() + 15.0f, SPLINETYPE_FACINGTARGET, SPLINEFLAG_FLYING, 0); 
            m_uiAnnylideGUID = pSummoned->GetGUID();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiPhase == PHASE_RESS_SEQUENCE)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                Creature* pAnnylide = m_creature->GetMap()->GetCreature(m_uiAnnylideGUID);
                switch(m_uiSubevent)
                {
                    case 0:
                        SetCombatMovement(false);
                        DoCastSpellIfCan(m_creature, SPELL_SUMMON_BANSHEE, CAST_TRIGGERED);
                        ++m_uiSubevent;
                        m_uiEventTimer = 4000;
                        break;
                    case 1:
                        if (pAnnylide)
                        {
                            DoScriptText(SAY_RESSURECTING, pAnnylide, m_creature);
                            pAnnylide->CastSpell(m_creature, SPELL_SCOURGE_RES_CHANNEL, false);
                        }
                         DoCastSpellIfCan(m_creature, SPELL_SCOURGE_RES_BUBBLE, CAST_TRIGGERED);
                        ++m_uiSubevent;
                        m_uiEventTimer = 15000;
                        break;
                    case 2:
                        m_creature->RemoveAurasDueToSpell(SPELL_SCOURGE_RES_BUBBLE);
                        m_creature->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                        DoCastSpellIfCan(m_creature, SPELL_SCOURGE_RES_HEAL, CAST_TRIGGERED);
                        m_uiEventTimer = 2000;
                        ++m_uiSubevent;
                        return;
                    case 3:
                        DoCastSpellIfCan(m_creature, SPELL_TRANSFORM, CAST_TRIGGERED);
                        if (pAnnylide)
                            pAnnylide->ForcedDespawn();
                        SetCombatMovement(true);
                        m_creature->GetMotionMaster()->Clear(false);
                        if (Unit* pUnit = m_creature->getVictim())                         
                            m_creature->GetMotionMaster()->MoveChase(pUnit);
                        DoScriptText(SAY_AGGRO_SECOND, m_creature);
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        m_uiPhase = PHASE_RESSURECTED;
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_uiPhase)
        {
            case PHASE_BEFORE_RESSURECION:
                if (m_uiCleaveTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
                    m_uiCleaveTimer = urand(2500, 7000);
                }
                else
                    m_uiCleaveTimer -= uiDiff;

                if (m_uiSmashTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SMASH : SPELL_SMASH_H);
                    m_uiSmashTimer = urand(8000, 15000);
                }
                else
                    m_uiSmashTimer -= uiDiff;

                if (m_uiStaggeringRoarTimer <= uiDiff)
                {
                    DoScriptText(EMOTE_ROAR, m_creature);
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_STAGGERING_ROAR : SPELL_STAGGERING_ROAR_H);
                    m_uiStaggeringRoarTimer = urand(15000, 30000);
                }
                else
                    m_uiStaggeringRoarTimer -= uiDiff;

                if (m_uiEnrageTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : SPELL_ENRAGE_H);
                    m_uiEnrageTimer = urand(10000, 20000);
                }
                else
                    m_uiEnrageTimer -= uiDiff;
                break;

            case PHASE_RESSURECTED:
                if (m_uiDreadfulRoarTimer <= uiDiff)
                {
                    DoScriptText(EMOTE_ROAR, m_creature);
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_DREADFUL_ROAR : SPELL_DREADFUL_ROAR_H);
                    m_uiDreadfulRoarTimer = 40000;
                }
                else
                    m_uiDreadfulRoarTimer -= uiDiff;

                if (m_uiDarkSmashTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_DARK_SMASH : SPELL_DARK_SMASH_H);
                    m_uiDarkSmashTimer = urand(15000, 25000);
                }
                else
                    m_uiDarkSmashTimer -= uiDiff;

                if (m_uiWoeStrikeTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_WOE_STRIKE : SPELL_WOE_STRIKE_H);
                    m_uiWoeStrikeTimer = urand(25000, 40000);
                }
                else
                    m_uiWoeStrikeTimer -= uiDiff;

                if (m_uiShadowAxeTimer <= uiDiff)
                {
                    if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pUnit, SPELL_SHADOW_AXE);
                    m_uiShadowAxeTimer = urand(30000, 45000);
                }
                else
                    m_uiShadowAxeTimer -= uiDiff;

                if (m_uiEnrageTimer <= uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : SPELL_ENRAGE_H);
                    m_uiEnrageTimer = urand(10000, 20000);
                }
                else
                    m_uiEnrageTimer -= uiDiff;

                break;
            default: break;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ingvar(Creature* pCreature)
{
    return new boss_ingvarAI(pCreature);
}

void AddSC_boss_ingvar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_ingvar";
    newscript->GetAI = &GetAI_boss_ingvar;
    newscript->RegisterSelf();
}
