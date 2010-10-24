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
SD%Complete: 20%
SDComment:
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

    // elemental's abilities
    SPELL_MERGE                 = 54878,
    SPELL_SURGE                 = 54801,
    SPELL_MOJO_VOLLEY           = 59453,
    SPELL_MOJO_VOLLEY_H         = 54849,
    SPELL_MOJO_PUDDLE           = 55627,
    SPELL_MOJO_PUDDLE_H         = 58994,
    SPELL_MOJO_WAVE             = 55626,
    SPELL_MOJO_WAVE_H           = 58993

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
        Reset();
    }

    instance_gundrak* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bFirstEmerge;
    bool m_bSecondEmerge;
    bool m_bSecondElemental;
    bool m_bIsInCombat;
    bool m_bIsMojoAlive;

    uint32 m_uiMightyBlowTimer;
    uint32 m_uiCheckTimer;

    std::list<Creature*> lMojos;

    void Reset()
    {
        m_bFirstEmerge      = false;
        m_bSecondEmerge     = false;
        m_bSecondElemental  = false; 
        m_bIsInCombat       = false;
        m_bIsMojoAlive      = false;
        m_uiMightyBlowTimer = 10000;
        m_uiCheckTimer      = 5000;
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->clearUnitState(UNIT_STAT_STUNNED);
        
       }

    void Agrro()
    {
        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_MORTAL_STRIKES : SPELL_MORTAL_STRIKES_H);
        m_creature->SetInCombatWithZone();
        if (m_pInstance)
            m_pInstance->SetData(TYPE_COLOSSUS, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_COLOSSUS, NOT_STARTED);
            m_pInstance->SetData(TYPE_ELEMENTAL, NOT_STARTED);
        if(Creature* pElemental = GetClosestCreatureWithEntry(m_creature,NPC_ELEMENTAL, 100.0f))
        {
            if(pElemental->isAlive())
                pElemental->ForcedDespawn(10);

        }

    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_COLOSSUS, DONE);
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_MERGE)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->clearUnitState(UNIT_STAT_STUNNED);
        }
    } 

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_ELEMENTAL)
        {
            pSummoned->CastSpell(pSummoned, m_bIsRegularMode ? SPELL_MOJO_VOLLEY : SPELL_MOJO_VOLLEY_H, false);
            pSummoned->SetInCombatWithZone();
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
            m_creature->SummonCreature(NPC_ELEMENTAL,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),0,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN , 99999999);

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
        if(!m_bIsInCombat)
        {
            if(m_uiCheckTimer < uiDiff)
            {
                
                uint8 j = 0;
                GetCreatureListWithEntryInGrid(lMojos, m_creature, NPC_LIVIN_MOJO, 10.0f);
                for (std::list<Creature*>::const_iterator i = lMojos.begin(); i != lMojos.end(); i++){
                            if (*i)
                            {
                                if((*i)->isAlive())
                                {m_bIsMojoAlive = true;}
                                
                            } }
                
                if(m_bIsMojoAlive){    
                    m_uiCheckTimer=5000; }
                else 
                {
                    m_uiCheckTimer=0; 
                    m_bIsInCombat=true; 
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_OOC_NOT_ATTACKABLE);
                }

            }
            else m_uiCheckTimer -= uiDiff;


        }
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
    bool m_bFirstMerge;
    instance_gundrak* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiMojoTimer;
    uint32 m_uiSurgeTimer;
    void Reset()
    {
        m_bFirstMerge = false;
        m_uiMojoTimer = 3000;
        m_uiSurgeTimer = 5000;

    }
    void JustReachedHome()
    {
        
        if(Creature* pColossus = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_COLOSSUS)))
        {
            ((boss_colossusAI*)pColossus->AI())->Reset();

        }
        m_creature->ForcedDespawn(10);
    } 
    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (!m_bFirstMerge && m_creature->GetHealthPercent() < 50.0f && !(m_pInstance->GetData(TYPE_ELEMENTAL) == SPECIAL))
        {
            m_bFirstMerge = true;
            if(Creature* pColossus = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_COLOSSUS))){
               // ((boss_colossusAI*)pColossus->AI())->Merge();} 
                m_creature->InterruptNonMeleeSpells(true);
                m_creature->CastSpell(pColossus, SPELL_MERGE,false);}
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

        if (m_uiMojoTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                    DoCast(pTarget, m_bIsRegularMode ? SPELL_MOJO_WAVE : SPELL_MOJO_WAVE_H);
            }
            m_uiMojoTimer = 3000;
        }
        else m_uiMojoTimer -= uiDiff;

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
}
