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
SDName: boss_eck
SDAuthor: 
SD%Complete: 0
SDComment: 
SDCategory: Gundrak
EndScriptData */

#include "precompiled.h"
#include "gundrak.h"

enum
{
//texts are currently missing

    SPELL_ECK_SPIT                            = 55814,
    SPELL_ECK_BITE                            = 55813,
    SPELL_ECK_SPRING                          = 55815,
    SPELL_ECK_BERSERK                         = 55816,
    SPELL_ECK_RESIDUE                         = 55817,
    NPC_RUIN_DWELLER                          = 29920
    
};

struct MANGOS_DLL_DECL boss_eckAI : public ScriptedAI
{
    boss_eckAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiSpit_Timer;
    uint32 m_uiBite_Timer;
    uint32 m_uiSpring_Timer;
    uint32 m_uiBerserk_Timer;
    uint32 m_uiVisible_Timer;
    bool   m_bIsVisible;
    bool   m_bIsBerserk;

    std::list<Creature*> lEckAdds;

    void Reset()
    {
        m_uiSpit_Timer = 7000;
        m_uiBite_Timer =3000;
        m_uiSpring_Timer = 10000;
        m_uiBerserk_Timer = 50000;
        m_uiVisible_Timer = 5000;
        m_bIsVisible = false;
        m_bIsBerserk=false;

        if(m_pInstance)
           m_pInstance->SetData(TYPE_ECK, NOT_STARTED);

        ChangeState(true);
        RespawnAdds();
    }

    void ChangeState(bool bOriginal)
    {
        if(bOriginal)
        {
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }    
        else 
        {
            m_creature->SetVisibility(VISIBILITY_ON);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    }

    void RespawnAdds()
    {
         GetCreatureListWithEntryInGrid(lEckAdds, m_creature, NPC_RUIN_DWELLER, 100.0f);
          for (std::list<Creature*>::const_iterator i = lEckAdds.begin(); i != lEckAdds.end(); i++){
              if (*i)
              {
                     if((*i)->isDead()) 
                        (*i)->Respawn();
              }
          }
    }

    void Aggro(Unit* pWho)
    {
       // DoScriptText(SAY_AGGRO, m_creature);
       if(m_pInstance)
          m_pInstance->SetData(TYPE_ECK, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if(m_pInstance)
           m_pInstance->SetData(TYPE_ECK, NOT_STARTED);
        ChangeState(true);
        RespawnAdds();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
           m_pInstance->SetData(TYPE_ECK, DONE);   
    }

    void SpellHitTarget(Unit* pUnit, const SpellEntry* pSpellEntry)
    {
        if (pSpellEntry->Id == SPELL_ECK_SPIT && pUnit->GetTypeId() == TYPEID_PLAYER && !pUnit->HasAura(SPELL_ECK_RESIDUE))
            pUnit->CastSpell(pUnit, SPELL_ECK_RESIDUE, true);
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        if(!m_bIsVisible)
        {
            if(m_uiVisible_Timer < uiDiff)
            {
                if(m_pInstance->GetData(TYPE_ECK) == SPECIAL)
                {
                    ChangeState(false);
                    m_bIsVisible=true;
                }
                else m_uiVisible_Timer=5000;

            }
            else m_uiVisible_Timer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSpit_Timer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_ECK_SPIT );
            m_uiSpit_Timer = 7000;
        }
        else m_uiSpit_Timer -= uiDiff;

        if (m_uiBite_Timer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_ECK_BITE );
            m_uiBite_Timer = 3000;
        }
        else m_uiBite_Timer -= uiDiff;

        if (m_uiSpring_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0)){
                DoCast(pTarget, SPELL_ECK_SPRING );
                DoResetThreat();
                m_creature->AddThreat(pTarget, 100.0f);
                }
            m_uiSpring_Timer = 10000;
        }
        else m_uiSpring_Timer -= uiDiff;

        if (!m_bIsBerserk) 
        {
            if (m_creature->GetHealthPercent() <= 20.0f || m_uiBerserk_Timer < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_ECK_BERSERK );
                m_uiBerserk_Timer = 0;
                m_bIsBerserk = true;
            }
            else m_uiBerserk_Timer -= uiDiff;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_eck(Creature* pCreature)
{
    return new boss_eckAI (pCreature);
}

void AddSC_boss_eck()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_eck";
    newscript->GetAI = &GetAI_boss_eck;
    newscript->RegisterSelf();
}
