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
SDName: Boss Volkhan
SD%Complete: 60%
SDComment: Not considered complete. Some events may fail and need further development
SDCategory: Halls of Lightning
EndScriptData */

#include "precompiled.h"
#include "halls_of_lightning.h"

enum
{
    SAY_AGGRO                               = -1602032,
    SAY_SLAY_1                              = -1602033,
    SAY_SLAY_2                              = -1602034,
    SAY_SLAY_3                              = -1602035,
    SAY_DEATH                               = -1602036,
    SAY_STOMP_1                             = -1602037,
    SAY_STOMP_2                             = -1602038,
    SAY_FORGE_1                             = -1602039,
    SAY_FORGE_2                             = -1602040,
    EMOTE_TO_ANVIL                          = -1602041,
    EMOTE_SHATTER                           = -1602042,

    SPELL_HEAT_N                            = 52387,
    SPELL_HEAT_H                            = 59528,
    SPELL_SHATTERING_STOMP_N                = 52237,
    SPELL_SHATTERING_STOMP_H                = 59529,

    SPELL_TEMPER                            = 52238,        //TARGET_SCRIPT boss->anvil
    SPELL_TEMPER_DUMMY                      = 52654,        //TARGET_SCRIPT anvil->boss
    SPELL_TEMPER_VISUAL                     = 52661,        //summons GO
    SPELL_SUMMON_MOLTEN_GOLEM               = 52405,

    //Molten Golem
    SPELL_BLAST_WAVE                        = 23113,
    SPELL_IMMOLATION_STRIKE_N               = 52433,
    SPELL_IMMOLATION_STRIKE_H               = 59530,
    SPELL_SHATTER_N                         = 52429,
    SPELL_SHATTER_H                         = 59527,

    SPELL_COOL_DOWN_PROC                    = 52441,
    SPELL_COOL_DOWN_AURA                    = 52443,

    NPC_BRITTLE_GOLEM                       = 28681,
    GO_VOLKHAN_ANVIL                        = 190858,

    POINT_ID_ANVIL                          = 0
};

/*######
## mob_molten_golem
######*/

struct MANGOS_DLL_DECL mob_molten_golemAI : public ScriptedAI
{
    mob_molten_golemAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bIsRegularMode;
    bool bScheduledToShatter;

    uint32 m_uiBlastTimer;
    uint32 m_uiImmolationTimer;
    uint32 m_uiShatterTimer;

    void Reset()
    {
        m_uiBlastTimer = 20000;
        m_uiImmolationTimer = urand(4000, 6000);
        m_uiShatterTimer = 3000;
        bScheduledToShatter = false;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        // probably should be done as a DummyEffect of CoolDown spell
        if (uiDamage > m_creature->GetHealth())
        {
            m_creature->RemoveAllAuras();
            m_creature->AttackStop();
            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->UpdateEntry(NPC_BRITTLE_GOLEM);
            m_creature->SetHealth(1);
            DoCastSpellIfCan(m_creature, SPELL_COOL_DOWN_PROC, (CAST_TRIGGERED | CAST_INTERRUPT_PREVIOUS));
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->addUnitState(UNIT_STAT_STUNNED);
            uiDamage = m_creature->GetHealth()-1;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bScheduledToShatter)
        {
            if (m_uiShatterTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHATTER_N : SPELL_SHATTER_H, CAST_TRIGGERED);
                // Probably should be done as a DummyEffect of Shatter spell
                m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
            else
                m_uiShatterTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() || m_creature->HasAura(SPELL_COOL_DOWN_AURA))
            return;

        if (m_uiBlastTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BLAST_WAVE);
            m_uiBlastTimer = 20000;
        }
        else
            m_uiBlastTimer -= uiDiff;

        if (m_uiImmolationTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_IMMOLATION_STRIKE_N : SPELL_IMMOLATION_STRIKE_H, CAST_AURA_NOT_PRESENT);
            m_uiImmolationTimer = 5000;
        }
        else
            m_uiImmolationTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_molten_golem(Creature* pCreature)
{
    return new mob_molten_golemAI(pCreature);
}

/*######
## Boss Volkhan
######*/

struct MANGOS_DLL_DECL boss_volkhanAI : public ScriptedAI
{
    boss_volkhanAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    std::list<uint64> m_lGolemGUIDList;

    bool m_bIsRegularMode;
    bool bAnvilSequence;

    uint32 m_uiTemperTimer;
    uint32 m_uiShatteringStompTimer;
    uint32 m_uiHeatTimer;

    uint32 m_uiHealthAmountModifier;

    void Reset()
    {
        m_uiTemperTimer = 13500;
        m_uiShatteringStompTimer = 0;
        m_uiHeatTimer = 20000;

        DespawnGolem();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLKHAN, NOT_STARTED);
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_ID_ANVIL)
        {
            DoCastSpellIfCan(m_creature, SPELL_TEMPER, CAST_INTERRUPT_PREVIOUS);
            DoScriptText(urand(0, 1) ? SAY_FORGE_1 : SAY_FORGE_2, m_creature);
        }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLKHAN, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        DespawnGolem();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLKHAN, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void DespawnGolem()
    {
        if (m_lGolemGUIDList.empty())
            return;

        for(std::list<uint64>::iterator itr = m_lGolemGUIDList.begin(); itr != m_lGolemGUIDList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                    pTemp->ForcedDespawn();
            }
        }
        m_lGolemGUIDList.clear();
    }

    void JustSummoned(Creature* pSummoned)
    {
        m_lGolemGUIDList.push_back(pSummoned->GetGUID());

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            pSummoned->AI()->AttackStart(pTarget);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        // dunno if it is safe?
        m_lGolemGUIDList.remove(pSummoned->GetGUID());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTemperTimer < uiDiff)
        {
            DoScriptText(EMOTE_TO_ANVIL, m_creature);
            float fDestX, fDestY, fDestZ;
            m_creature->GetRespawnCoord(fDestX, fDestY, fDestZ);
            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovePoint(POINT_ID_ANVIL, fDestX, fDestY, fDestZ);
            m_uiTemperTimer = 60000;
        }
        else
            m_uiTemperTimer -= uiDiff;

        if (m_uiShatteringStompTimer < uiDiff)
        {
            if (!m_lGolemGUIDList.empty())
            {
                DoScriptText(urand(0, 1) ? SAY_STOMP_1 : SAY_STOMP_2, m_creature);
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHATTERING_STOMP_N : SPELL_SHATTERING_STOMP_H);
                DoScriptText(EMOTE_SHATTER, m_creature);
                // 100% sure that some kind of AoE effect should force them to die instead of iterating list
                for (std::list<uint64>::iterator itr = m_lGolemGUIDList.begin(); itr != m_lGolemGUIDList.end(); ++itr)
                {
                    Creature* pGolem = m_creature->GetMap()->GetCreature(*itr);
                    if (pGolem && pGolem->AI() && pGolem->isAlive() && pGolem->HasAura(SPELL_COOL_DOWN_AURA))
                        ((mob_molten_golemAI*)pGolem->AI())->bScheduledToShatter = true;
                }
            }
            m_uiShatteringStompTimer = 30000;
        }
        else
            m_uiShatteringStompTimer -= uiDiff;

        if (m_uiHeatTimer <= uiDiff)
        {
            if (!m_lGolemGUIDList.empty())
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_HEAT_N : SPELL_HEAT_H);
            m_uiHeatTimer = 10000;
        }
        else
            m_uiHeatTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_volkhan(Creature* pCreature)
{
    return new boss_volkhanAI(pCreature);
}

bool EffectDummyCreature_boss_volkhan(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    //always check spellid and effectindex
    if (uiSpellId == SPELL_TEMPER_DUMMY && uiEffIndex == EFFECT_INDEX_0 && pCreatureTarget->GetTypeId() == TYPEID_UNIT)
    {
        // summon 2 golems in random coords
        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_SUMMON_MOLTEN_GOLEM, true);
        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_SUMMON_MOLTEN_GOLEM, true);

        pCreatureTarget->GetMotionMaster()->MovementExpired(true);
        pCreatureTarget->GetMotionMaster()->Clear();
        if (Unit* pVictim = pCreatureTarget->getVictim())
            pCreatureTarget->GetMotionMaster()->MoveChase(pVictim);

        //always return true when we are handling this spell and effect
        return true;
    }
    return false;
}

/*######
## npc_volkhan_anvil
######*/

bool EffectDummyCreature_npc_volkhan_anvil(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    //always check spellid and effectindex
    if (uiSpellId == SPELL_TEMPER && uiEffIndex == EFFECT_INDEX_0)
    {
        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_TEMPER_VISUAL, true);
        // Unit::GetGameObject is not working - so hacked using gridsearcher
        // GO_VOLKHAN_ANVIL is a trap. so maybe DB data is broken that it is not "blowing" just after spawning
        // or a least some kind of "activating" function should be called
        if (GameObject* pTrap = GetClosestGameObjectWithEntry(pCreatureTarget, GO_VOLKHAN_ANVIL, INTERACTION_DISTANCE))
        {
            pTrap->SendGameObjectCustomAnim(pTrap->GetGUID());
            pTrap->RemoveFromWorld();
        }
        pCreatureTarget->CastSpell(pCaster, SPELL_TEMPER_DUMMY, true);
        //always return true when we are handling this spell and effect
        return true;
    }
    return false;
}

void AddSC_boss_volkhan()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_volkhan";
    newscript->GetAI = &GetAI_boss_volkhan;
    newscript->pEffectDummyCreature = &EffectDummyCreature_boss_volkhan;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_volkhan_anvil";
    newscript->pEffectDummyCreature = &EffectDummyCreature_npc_volkhan_anvil;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_molten_golem";
    newscript->GetAI = &GetAI_mob_molten_golem;
    newscript->RegisterSelf();
}
