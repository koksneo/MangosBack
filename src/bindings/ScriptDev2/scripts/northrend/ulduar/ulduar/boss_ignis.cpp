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
SDName: Boss_Ignis
SD%Complete: 90%
SDComment: Slag Pot needs to be handled by vehicle patch for visual effect.
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

enum
{
    SAY_AGGRO                       = -1610020,
    SAY_SCORCH_1                    = -1610021,
    SAY_SCORCH_2                    = -1610022,
    SAY_SLAG_POT                    = -1610023,
    EMOTE_FLAME_JETS                = -1610024,
    SAY_SUMMON                      = -1610025,
    SAY_SLAY_1                      = -1610026,
    SAY_SLAY_2                      = -1610027,
    SAY_BERSERK                     = -1610028,
    SAY_DEATH                       = -1610029,

    // Ignis
    SPELL_FLAME_JETS                = 62680,
    SPELL_FLAME_JETS_H              = 63472,
    SPELL_SCORCH_CHANNELED          = 62546,
    SPELL_SCORCH_CHANNELED_H        = 63474,
    SPELL_CHARGE_SLAG_POT           = 62707,
    SPELL_CHARGE_SLAG_POT_H         = 63535,
    SPELL_SLAG_POT_AURA             = 62717,
    SPELL_SLAG_POT_AURA_H           = 63477,

    // Scorch trigger
    SPELL_SCORCH_AURA               = 62548,
    SPELL_SCORCH_AURA_H             = 63476,

    // Iron Constructs
    //NPC_IRON_CONSTRUCT            = 33121,
    SPELL_STONED                    = 62468,
    SPELL_HEAT_AURA                 = 65667,
    SPELL_MOLTEN                    = 62373,
    SPELL_BRITTLE                   = 67114,
    SPELL_BRITTLE_H                 = 62382,
    SPELL_SHATTER                   = 62383,
    SPELL_ACTIVATE_CONSTRUCT        = 62488,
    SPELL_STRENGTH_OF_THE_CREATOR   = 64473,

    // other stuff
    SPELL_SUMMON_SCORCH_TRIGGER     = 62551,
    SPELL_SLAG_IMBUED               = 62836,
    SPELL_SLAG_IMBUED2              = 63536,
    SPELL_MOLTEN_STUN               = 65208,            // couldn't find proper spell, so using this one
    SCORCH_DESPAWN_TIME             = 40000
};

/*######
## boss_ignis
######*/

struct MANGOS_DLL_DECL boss_ignisAI : public ScriptedAI
{
    boss_ignisAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_ulduar*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();

        Reset();
    }

    instance_ulduar* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiScorchTimer;
    uint32 m_uiSlagPotTimer;
    uint32 m_uiFlameJetsTimer;
    uint32 m_uiActivateConstructTimer;

    void Reset()
    {
        m_uiScorchTimer             = 12000;
        m_uiSlagPotTimer            = 19000;
        m_uiFlameJetsTimer          = 21000;
        m_uiActivateConstructTimer  = 25000;

        if (m_pInstance)
            for (std::list<uint64>::iterator i = m_pInstance->m_lIronConstructsGUIDs.begin(); i != m_pInstance->m_lIronConstructsGUIDs.end(); i++)
                if (Creature *pTmp = m_pInstance->instance->GetCreature(*i))
                    if (!pTmp->isAlive())
                        pTmp->Respawn();
    }
    
    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS , IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS, FAIL);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS, DONE);
    }

    void JustSummoned(Creature* pCreature)
    {
        if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SCORCH_CHANNELED : SPELL_SCORCH_CHANNELED_H) == CAST_OK  && !pCreature->IsInWater())
        {
            m_creature->AddThreat(pCreature, 100000000000000.0f, true);
            m_creature->SetFacingToObject(pCreature);
            pCreature->SetDisplayId(11686);
            pCreature->SetInCombatWithZone();
            pCreature->ForcedDespawn(SCORCH_DESPAWN_TIME);
        }
        else
            pCreature->ForcedDespawn();
    }

    void DamageTaken(Unit *pDoneBy, uint32 &uiDamage)
    {
        if (pDoneBy->HasAura(SPELL_SLAG_POT_AURA) || pDoneBy->HasAura(SPELL_SLAG_POT_AURA_H))
            uiDamage = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiScorchTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_SCORCH_TRIGGER, CAST_TRIGGERED) == CAST_OK)
                m_uiScorchTimer = urand(20000, 25000);
        }
        else m_uiScorchTimer -= uiDiff;

        if (m_uiSlagPotTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1), m_bIsRegularMode ? SPELL_CHARGE_SLAG_POT : SPELL_CHARGE_SLAG_POT_H) == CAST_OK)
                m_uiSlagPotTimer = urand(15000, 25000);
        }
        else m_uiSlagPotTimer -= uiDiff;

        if (m_uiFlameJetsTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_FLAME_JETS : SPELL_FLAME_JETS_H) == CAST_OK)
                m_uiFlameJetsTimer = urand(20000, 25000);
        }
        else m_uiFlameJetsTimer -= uiDiff;

        if (m_uiActivateConstructTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_ACTIVATE_CONSTRUCT) == CAST_OK)
                m_uiActivateConstructTimer = 15000;
        }
        else m_uiActivateConstructTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ignis(Creature* pCreature)
{
    return new boss_ignisAI(pCreature);
}

/*######
## mob_iron_construct
######*/

struct MANGOS_DLL_DECL mob_iron_constructAI : public ScriptedAI
{
    mob_iron_constructAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_ulduar*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();

        Reset();
    }

    instance_ulduar* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsStoned;
    bool m_bIsActive;
    uint32 m_uiBrittleCheckTimer;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_bIsStoned = false;
        m_bIsActive = false;
        m_uiBrittleCheckTimer = 500;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (!m_bIsActive)
        {
            uiDamage = 0;
            return;
        }

        if (m_creature->HasAura(SPELL_BRITTLE, EFFECT_INDEX_0) || m_creature->HasAura(SPELL_BRITTLE_H, EFFECT_INDEX_0))
        {
            uint32 m_uiShatterDmg = m_bIsRegularMode ? 3000 : 5000;
            if (uiDamage > m_uiShatterDmg)
            {
                uiDamage = 0;
                if (DoCastSpellIfCan(m_creature, SPELL_SHATTER, CAST_TRIGGERED) == CAST_OK)
                {
                    m_creature->ForcedDespawn(1000);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    // Strength of the Creator stack decreasing hack
                    if (m_pInstance)
                        if (Creature *pIgnis = m_pInstance->instance->GetCreature(m_pInstance->GetData64(TYPE_IGNIS)) )
                            if (SpellAuraHolder *pHolder = pIgnis->GetSpellAuraHolder(SPELL_STRENGTH_OF_THE_CREATOR) )
                                pHolder->SetStackAmount(pHolder->GetStackAmount()-1);
                }
            }
        }
    }

    void SpellHit(Unit* pCaster, const SpellEntry *spellInfo)
    {
        if (spellInfo->Id == SPELL_ACTIVATE_CONSTRUCT)
        {
            m_creature->RemoveAurasDueToSpell(SPELL_STONED);

            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_bIsActive = true;
            m_creature->SetInCombatWithZone();

            if (Unit *pVictim = ((Creature*)pCaster)->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0) )
                m_creature->AI()->AttackStart(pVictim);

            pCaster->CastSpell(pCaster, SPELL_STRENGTH_OF_THE_CREATOR, true);
        }
        else if (spellInfo->Id == SPELL_HEAT_AURA)
        {
            if (Aura* pHeat = m_creature->GetAura(SPELL_HEAT_AURA, EFFECT_INDEX_1) )
            {
                if (pHeat->GetStackAmount() > 9)
                {
                    m_creature->RemoveAurasDueToSpell(SPELL_HEAT_AURA);
                    DoCastSpellIfCan(m_creature, SPELL_MOLTEN, CAST_TRIGGERED);
                    DoCastSpellIfCan(m_creature, SPELL_MOLTEN_STUN, CAST_TRIGGERED);
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bIsStoned)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_STONED) == CAST_OK)
                m_bIsStoned = true;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
            return;

        if (!m_bIsActive)
            m_creature->AI()->EnterEvadeMode();

        if (m_uiBrittleCheckTimer <= uiDiff)
        {
            if (m_creature->HasAura(SPELL_MOLTEN) && !m_creature->HasAura(SPELL_BRITTLE) )
            {
                if (m_creature->IsInWater())
                {
                    if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_BRITTLE : SPELL_BRITTLE_H, CAST_TRIGGERED) == CAST_OK)
                        m_creature->RemoveAurasDueToSpell(SPELL_MOLTEN);
                }
            }
            m_uiBrittleCheckTimer = 500;
        }
        else m_uiBrittleCheckTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_iron_construct(Creature* pCreature)
{
    return new mob_iron_constructAI(pCreature);
}

void AddSC_boss_ignis()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_ignis";
    newscript->GetAI = &GetAI_boss_ignis;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_iron_construct";
    newscript->GetAI = &GetAI_mob_iron_construct;
    newscript->RegisterSelf();
}
