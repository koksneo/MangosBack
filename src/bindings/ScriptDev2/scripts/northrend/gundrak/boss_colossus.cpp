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
SDName: Boss_Colossus
SD%Complete: 80%
SDComment: Some visual stuff missing
SDCategory: Gundrak
EndScriptData */

#include "precompiled.h"
#include "gundrak.h"

enum
{
    EMOTE_SURGE                 = -1604008,
    EMOTE_SEEP                  = -1604009,
    EMOTE_GLOW                  = -1604010,

    // collosus' abilities
    SPELL_EMERGE                = 54850,
    SPELL_MIGHTY_BLOW           = 54719,
    SPELL_MORTAL_STRIKES        = 54715,
    SPELL_MORTAL_STRIKES_H      = 59454,

    NPC_LIVING_MOJO             = 29830,

    // elemental's abilities
    SPELL_MERGE                 = 54878,
    SPELL_SURGE                 = 54801,
    SPELL_MOJO_VOLLEY           = 59453,
    SPELL_MOJO_VOLLEY_H         = 54849,
    SPELL_MOJO_WAVE             = 55626,
    SPELL_MOJO_WAVE_H           = 58993,
    SPELL_MOJO_PUDDLE           = 55627,
    SPELL_MOJO_PUDDLE_H         = 58994
};

/*######
## boss_colossus
######*/

struct MANGOS_DLL_DECL boss_colossusAI : public ScriptedAI
{
    boss_colossusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_gundrak*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        m_creature->addUnitState(UNIT_STAT_STUNNED);
        Reset();
    }

    instance_gundrak* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bFirstEmerge;
    bool m_bSecondEmerge;
    bool m_bSecondElemental;
    uint32 m_uiMightyBlowTimer;
    std::list<Creature*> m_lMojoList;

    void Reset()
    {
        m_bFirstEmerge      = false;
        m_bSecondEmerge     = false;
        m_bSecondElemental  = false; 
        m_uiMightyBlowTimer = 10000;
        m_lMojoList.clear();
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        m_creature->clearUnitState(UNIT_STAT_STUNNED);
    }

    void Agrro()
    {
        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_MORTAL_STRIKES : SPELL_MORTAL_STRIKES_H);
        m_creature->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COLOSSUS, IN_PROGRESS);

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        m_creature->clearUnitState(UNIT_STAT_STUNNED);
    }

    void EnterEvadeMode()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        m_creature->clearUnitState(UNIT_STAT_STUNNED);

        // ScriptedAI::EnterEvadeMode();
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);
        m_creature->LoadCreatureAddon();

        if (m_creature->isAlive())
            m_creature->GetMotionMaster()->MoveTargetedHome();

        m_creature->SetLootRecipient(NULL);

        Reset();
    }

    void JustReachedHome()
    {
        if(m_pInstance)
        {
            m_pInstance->SetData(TYPE_COLOSSUS, NOT_STARTED);
            m_pInstance->SetData(TYPE_ELEMENTAL, NOT_STARTED);
        }
        if(Creature* pElemental = GetClosestCreatureWithEntry(m_creature,NPC_ELEMENTAL, 100.0f))
        {
            if(pElemental->isAlive())
                pElemental->ForcedDespawn(10);
        }
    }

    void JustDied(Unit* pKiller)
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        m_creature->clearUnitState(UNIT_STAT_STUNNED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COLOSSUS, DONE);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_ELEMENTAL)
        {
            pSummoned->CastSpell(pSummoned, m_bIsRegularMode ? SPELL_MOJO_VOLLEY : SPELL_MOJO_VOLLEY_H, false);
            pSummoned->SetInCombatWithZone();
            pSummoned->setFaction(m_creature->getFaction());

            if(m_bSecondElemental)
            {
                pSummoned->SetHealth(pSummoned->GetMaxHealth()/2);
            }
        }
    }

    void SetCreature()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->addUnitState(UNIT_STAT_STUNNED);
        m_creature->SummonCreature(NPC_ELEMENTAL,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),0,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN , 7*DAY*IN_MILLISECONDS);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (!m_bFirstEmerge && m_creature->GetHealthPercent() < 50.0f)
        {
            m_bFirstEmerge = true;
            DoCastSpellIfCan(m_creature, SPELL_EMERGE);
            SetCreature();
        }
        if (!m_bSecondEmerge && m_creature->GetHealthPercent() < 5.0f)
        {
            m_bSecondEmerge = true;
            DoCastSpellIfCan(m_creature, SPELL_EMERGE);
            m_bSecondElemental =true;
            m_pInstance->SetData(TYPE_ELEMENTAL, SPECIAL);
            SetCreature();
        }
        else if (m_creature->GetHealth() - uiDamage <= 0)
        {
            // prevent boss from dying if players deal the final blow
            if (pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                uiDamage = 0;
                DoCastSpellIfCan(m_creature, SPELL_EMERGE);
            }
        }

    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiMightyBlowTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_MIGHTY_BLOW);
            m_uiMightyBlowTimer = 10000;
        }
        else
            m_uiMightyBlowTimer -= uiDiff;
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_colossus(Creature* pCreature)
{
    return new boss_colossusAI(pCreature);
};

/*######
## boss_drakari_elemental
######*/
struct MANGOS_DLL_DECL boss_drakari_elementalAI : public ScriptedAI
{
    boss_drakari_elementalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_gundrak*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_gundrak* m_pInstance;
    bool m_bIsRegularMode;

    bool m_bFirstMerge;
    uint32 m_uiMojoWaveTimer;
    uint32 m_uiMojoPuddleTimer;
    uint32 m_uiSurgeTimer;

    void Reset()
    {
        m_bFirstMerge       = false;
        m_uiMojoWaveTimer   = 3000;
        m_uiMojoPuddleTimer = 4000;
        m_uiSurgeTimer      = 5000;
    }

    void JustReachedHome()
    {
        if(Creature* pColossus = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_COLOSSUS)))
        {
            ((boss_colossusAI*)pColossus->AI())->EnterEvadeMode();
        }
        m_creature->ForcedDespawn(10);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (!m_bFirstMerge && m_creature->GetHealthPercent() < 50.0f && !(m_pInstance->GetData(TYPE_ELEMENTAL) == SPECIAL))
        {
            m_bFirstMerge = true;
            if (Creature* pColossus = m_pInstance->instance->GetCreature(ObjectGuid(m_pInstance->GetData64(NPC_COLOSSUS))))
            {
                //((boss_colossusAI*)pColossus->AI())->Merge();}
                m_creature->InterruptNonMeleeSpells(true);
                pColossus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                pColossus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                pColossus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                pColossus->clearUnitState(UNIT_STAT_STUNNED);
                m_creature->CastSpell(pColossus, SPELL_MERGE,true);
            }
            m_creature->ForcedDespawn(4000);
        }
    }

    void JustDied(Unit* pKiller)
    {
        if(Creature* pColossus = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_COLOSSUS)))
            pColossus->DealDamage(pColossus,pColossus->GetHealth(),NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiMojoWaveTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCast(pTarget, m_bIsRegularMode ? SPELL_MOJO_WAVE : SPELL_MOJO_WAVE_H);
            }
            m_uiMojoWaveTimer = 3000;
        }
        else m_uiMojoWaveTimer -= uiDiff;

        if (m_uiMojoPuddleTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, m_bIsRegularMode ? SPELL_MOJO_PUDDLE : SPELL_MOJO_PUDDLE_H);
            m_uiMojoPuddleTimer = urand(4000, 8000);
        }
        else m_uiMojoPuddleTimer -= uiDiff;

        if(m_uiSurgeTimer <uiDiff)
        { 
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCast(pTarget, SPELL_SURGE);
            }
            m_uiSurgeTimer = 5000;
        }
        else m_uiSurgeTimer -= uiDiff;
        
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_drakari_elemental(Creature* pCreature)
{
    return new boss_drakari_elementalAI(pCreature);
};

/*######
## mob_living_mojo
######*/

struct MANGOS_DLL_DECL mob_living_mojoAI : public ScriptedAI
{
    mob_living_mojoAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool m_bIsRegularMode;
    uint32 m_uiMojoPuddleTimer;
    uint32 m_uiMojoWaveTimer;

    void Reset()
    {
        m_uiMojoPuddleTimer = 2000;
        m_uiMojoWaveTimer   = 4000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiMojoPuddleTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, m_bIsRegularMode ? SPELL_MOJO_PUDDLE : SPELL_MOJO_PUDDLE_H);
            m_uiMojoPuddleTimer = urand(4000, 8000);
        }
        else m_uiMojoPuddleTimer -= uiDiff;

        if (m_uiMojoWaveTimer <= uiDiff)
        {
            DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_MOJO_WAVE : SPELL_MOJO_WAVE_H);
            m_uiMojoWaveTimer = urand(4000, 7000);
        }
        else m_uiMojoWaveTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_living_mojo(Creature* pCreature)
{
    return new mob_living_mojoAI(pCreature);
};

void AddSC_boss_colossus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_colossus";
    pNewScript->GetAI = &GetAI_boss_colossus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_drakari_elemental";
    pNewScript->GetAI = &GetAI_boss_drakari_elemental;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_living_mojo";
    pNewScript->GetAI = &GetAI_mob_living_mojo;
    pNewScript->RegisterSelf();
}
