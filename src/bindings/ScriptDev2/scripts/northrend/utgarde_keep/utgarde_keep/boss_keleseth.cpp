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
SDName: Boss_Keleseth
SD%Complete: 60%
SDComment:
SDCategory: Utgarde Keep
EndScriptData */

#include "precompiled.h"
#include "utgarde_keep.h"

enum
{
    SAY_AGGRO               = -1574000,
    SAY_FROSTTOMB           = -1574001,
    SAY_SKELETONS           = -1574002,
    SAY_KILL                = -1574003,
    SAY_DEATH               = -1574004,
    EMOTE_FROST_TOMB        = -1574021,

    // Boss Spells
    SPELL_SHADOWBOLT        = 43667,
    SPELL_SHADOWBOLT_H      = 59389,

    SPELL_SUMMON_FROST_TOMB = 42714,
    SPELL_FROST_TOMB        = 48400,                        // stun and deal damage

    // Skeleton Spells
    SPELL_RESSURECTION      = 42704,
    SPELL_DECREPIFY         = 42702,
    SPELL_DECREPIFY_H       = 59397,
    SPELL_BONE_ARMOR        = 59386,                        // casted on boss, heroic only

    NPC_FROST_TOMB          = 23965,
    NPC_VRYKUL_SKELETON     = 23970
};

const float RUN_DISTANCE = 20.0;

static float fAddPosition[4] = {163.5727f, 252.1900f, 42.8684f, 5.57052f};

/*######
## mob_vrykul_skeleton
######*/

struct MANGOS_DLL_DECL mob_vrykul_skeletonAI : public ScriptedAI
{
    mob_vrykul_skeletonAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = m_creature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsDead;

    uint8  m_uiSubevent;
    uint32 m_uiCastTimer;
    uint32 m_uiReviveTimer;

    void Reset()
    {
        m_bIsDead = false;
        m_uiSubevent = 0;
        m_uiReviveTimer = 15000;
        m_uiCastTimer = urand(5000, 10000);                 // taken out of thin air
    }

    Creature* GetKeleseth()
    {
        if (!m_pInstance)
            return NULL;

        if (Creature* pKeleseth = m_pInstance->instance->GetCreature(m_pInstance->GetData64(NPC_KELESETH)))
            return pKeleseth;
        else 
            return NULL;
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!pWho || m_uiReviveTimer)
            return;

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho || m_bIsDead)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void Revive()
    {
        m_creature->SetHealth(m_creature->GetMaxHealth());
        m_creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);

        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            m_creature->GetMotionMaster()->MoveChase(pTarget);

        DoResetThreat();
        m_uiReviveTimer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        Creature* m_pKeleseth = GetKeleseth();
        if (!m_pKeleseth || !m_pKeleseth->isAlive())
        {
            uiDamage = m_creature->GetHealth();
            return;
        }

        if (m_bIsDead)
        {
            uiDamage = 0;
            return;
        }

        if (m_creature->GetHealth() <= uiDamage)
        {
            // start faking death
            uiDamage = 0;
            m_creature->SetHealth(0);
            m_creature->RemoveAllAuras();
            m_creature->GetMotionMaster()->Clear(false);
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
            m_bIsDead = true;
            m_uiSubevent = 0;
            return;
       }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bIsDead)
        {
            if (m_uiReviveTimer <= uiDiff)
            {
                // cosmetic change, if we allow movechase just after ressurecting, sceletons will move partialy under floor (emote animation)
                switch(m_uiSubevent)
                {
                    case 0:
                        SetCombatMovement(false);
                        m_creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        DoCastSpellIfCan(m_creature, SPELL_RESSURECTION, CAST_TRIGGERED);
                        m_uiReviveTimer = 4000;
                        ++m_uiSubevent;
                        return;
                    case 1:
                        DoResetThreat();
                        SetCombatMovement(true);
                        if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                            m_creature->GetMotionMaster()->MoveChase(pUnit);
                        m_bIsDead = false;
                        m_uiReviveTimer = 15000;
                        break;
                }
            }
            else
                m_uiReviveTimer -= uiDiff;

            return;
        }

        if (m_uiCastTimer < uiDiff)
        {
            if (m_bIsRegularMode)
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_DECREPIFY);
            else
            {
                Creature* m_pKeleseth = GetKeleseth();
                if (urand(0, 3))
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_DECREPIFY_H);
                else if (m_pKeleseth && m_pKeleseth->isAlive() && !m_pKeleseth->HasAura(SPELL_BONE_ARMOR))
                    DoCastSpellIfCan(m_pKeleseth, SPELL_BONE_ARMOR);
            }

            m_uiCastTimer = urand(5000, 15000);
        }
        else
            m_uiCastTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_vrykul_skeleton(Creature* pCreature)
{
    return new mob_vrykul_skeletonAI(pCreature);
}

/*######
## boss_keleseth
######*/

struct MANGOS_DLL_DECL boss_kelesethAI : public ScriptedAI
{
    boss_kelesethAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bSummonedAdds;
    std::list<uint64> lAddsList;

    uint32 m_uiFrostTombTimer; 
    uint32 m_uiSummonTimer;
    uint32 m_uiShadowboltTimer;

    void Reset() 
    {
        // timers need confirmation
        m_uiFrostTombTimer = 20000;
        m_uiSummonTimer = 5000 ;
        m_uiShadowboltTimer = 0;

        DespawnAdds();
    }

    void AttackStart(Unit* pWho)
    {
        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            m_creature->GetMotionMaster()->MoveChase(pWho, RUN_DISTANCE);
        }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void DespawnAdds()
    {
        if (!lAddsList.empty())
        {
            for(std::list<uint64>::iterator itr = lAddsList.begin(); itr != lAddsList.end(); ++itr)
            {
                if (Creature* pCrearture = m_creature->GetMap()->GetCreature(*itr))
                    (pCrearture)->ForcedDespawn();
            }
            lAddsList.clear();
        }
        m_bSummonedAdds = false;
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (pSummoned->GetEntry() == NPC_VRYKUL_SKELETON && pSummoned->AI())
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                pSummoned->AI()->AttackStart(pTarget);

        if (pSummoned->GetEntry() == NPC_FROST_TOMB)
            pSummoned->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_FROST, true);

        lAddsList.push_back(pSummoned->GetGUID());
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bSummonedAdds)
        {
            if (m_uiSummonTimer <= uiDiff)
            {
                for (uint8 i=0; i<4; ++i)
                    m_creature->SummonCreature(NPC_VRYKUL_SKELETON, fAddPosition[0]+rand()%7, fAddPosition[1]+rand()%7, fAddPosition[2], fAddPosition[3], TEMPSUMMON_CORPSE_DESPAWN, 0);
                m_bSummonedAdds = true;
            }
            else
                m_uiSummonTimer -= uiDiff;
        }

        if (m_uiShadowboltTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SHADOWBOLT : SPELL_SHADOWBOLT_H);
            m_uiShadowboltTimer = 3000;
        }
        else
            m_uiShadowboltTimer -= uiDiff;

        if (m_uiFrostTombTimer < uiDiff)
        {
            if (Unit* pTombTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                //DoCastSpellIfCan(pTombTarget, SPELL_SUMMON_FROST_TOMB);
                float fPosX, fPosY, fPosZ;
                pTombTarget->GetPosition(fPosX, fPosY, fPosZ);
 
                if (Creature* pFrostTomb = m_creature->SummonCreature(NPC_FROST_TOMB, fPosX, fPosY, fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 20000))
                {
                    pTombTarget->ClearDiminishings();
                    pFrostTomb->AddThreat(pTombTarget);
                    pFrostTomb->CastSpell(pTombTarget, SPELL_FROST_TOMB, false);
                }
 
                DoScriptText(SAY_FROSTTOMB, m_creature);
                DoScriptText(EMOTE_FROST_TOMB, m_creature, pTombTarget);
            }

            m_uiFrostTombTimer = urand(15000, 25000); 
        }
        else
            m_uiFrostTombTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_keleseth(Creature* pCreature)
{
    return new boss_kelesethAI(pCreature);
}

void AddSC_boss_keleseth()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_keleseth";
    newscript->GetAI = &GetAI_boss_keleseth;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_vrykul_skeleton";
    newscript->GetAI = &GetAI_mob_vrykul_skeleton;
    newscript->RegisterSelf();
}
