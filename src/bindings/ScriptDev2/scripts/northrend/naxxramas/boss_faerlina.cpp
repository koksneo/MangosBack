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
SDName: Boss_Faerlina
SD%Complete: 100
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_GREET                   = -1533009,
    SAY_AGGRO                   = -1533010,
    SAY_FRENZY1                 = -1533011,
    SAY_FRENZY2                 = -1533012,
    SAY_FRENZY3                 = -1533013,
    SAY_SLAY1                   = -1533014,
    SAY_SLAY2                   = -1533015,
    SAY_DEATH                   = -1533016,
    EMOTE_FRENZY                = -1999776,
    EMOTE_WIDOWS_EMBRACE        = -1999775,

    //SOUND_RANDOM_FRENZY        = 8955,                             //soundId containing the 4 aggro sounds, we not using this

    SPELL_POSIONBOLT_VOLLEY     = 28796,
    SPELL_POSIONBOLT_VOLLEY_H   = 54098,
    SPELL_FRENZY                = 28798,
    SPELL_FRENZY_H              = 54100,
    SPELL_WIDOWS_EMBRACE        = 28732,
    SPELL_WIDOWS_EMBRACE_H      = 54097,
    SPELL_RAIN_OF_FIRE          = 28794,                            //Not sure if targeted AoEs work if casted directly upon a pPlayer
    SPELL_RAIN_OF_FIRE_H        = 54099
};
struct MANGOS_DLL_DECL boss_faerlinaAI : public ScriptedAI
{
    boss_faerlinaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_bHasTaunted = false;
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiPoisonBoltVolleyTimer;
    uint32 m_uiRainOfFireTimer;
    uint32 m_uiFrenzyTimer;
    bool   m_bHasTaunted;

    void Reset()
    {
        m_uiPoisonBoltVolleyTimer = 8000;
        m_uiRainOfFireTimer = 16000;
        m_uiFrenzyTimer = 60000;
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (!pSpell)
            return;

        if (pSpell->Id == (m_bIsRegularMode ? SPELL_WIDOWS_EMBRACE : SPELL_WIDOWS_EMBRACE_H))
        {
            DoScriptText(EMOTE_WIDOWS_EMBRACE, m_creature);
            if (m_creature->HasAura(m_bIsRegularMode ? SPELL_FRENZY : SPELL_FRENZY_H))
            {
                m_creature->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_FRENZY : SPELL_FRENZY_H);
                m_uiFrenzyTimer = 60000;
            }
            else
                m_uiFrenzyTimer = 30000;
        }
    }

    void Aggro(Unit* pWho)
    {

        DoScriptText(SAY_AGGRO, m_creature);
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FAERLINA, IN_PROGRESS);

            for (std::list<uint64>::iterator itr = m_pInstance->lFaelinasAdds.begin(); itr != m_pInstance->lFaelinasAdds.end(); ++itr)
            {
                Creature* pAdd = m_creature->GetMap()->GetCreature(*itr);
                if (pAdd && !pAdd->isInCombat() && pAdd->AI())
                    pAdd->AI()->AttackStart(pWho);
            }
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!m_bHasTaunted && m_creature->IsWithinDistInMap(pWho, 60.0f))
        {
            DoScriptText(SAY_GREET, m_creature);
            m_bHasTaunted = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FAERLINA, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FAERLINA, FAIL);
            for (std::list<uint64>::iterator itr = m_pInstance->lFaelinasAdds.begin(); itr != m_pInstance->lFaelinasAdds.end(); ++itr)
            {
                Creature* pAdd = m_creature->GetMap()->GetCreature(*itr);
                if (pAdd && !pAdd->isAlive())
                    pAdd->Respawn();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Poison Bolt Volley
        if (m_uiPoisonBoltVolleyTimer < uiDiff)
        {
            if (!m_creature->HasAura(m_bIsRegularMode ? SPELL_WIDOWS_EMBRACE : SPELL_WIDOWS_EMBRACE_H))
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_POSIONBOLT_VOLLEY : SPELL_POSIONBOLT_VOLLEY_H);
            m_uiPoisonBoltVolleyTimer = 11000;
        }
        else
            m_uiPoisonBoltVolleyTimer -= uiDiff;

        // Rain Of Fire
        if (m_uiRainOfFireTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_RAIN_OF_FIRE : SPELL_RAIN_OF_FIRE_H);

            m_uiRainOfFireTimer = 16000;
        }
        else
            m_uiRainOfFireTimer -= uiDiff;

        //Frenzy_Timer
        if (m_uiFrenzyTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_FRENZY : SPELL_FRENZY_H, CAST_INTERRUPT_PREVIOUS) == CAST_OK)
            {
                switch(urand(0, 2))
                {
                    case 0: DoScriptText(SAY_FRENZY1, m_creature); break;
                    case 1: DoScriptText(SAY_FRENZY2, m_creature); break;
                    case 2: DoScriptText(SAY_FRENZY3, m_creature); break;
                }
                DoScriptText(EMOTE_FRENZY, m_creature);
            }
            m_uiFrenzyTimer = 61000;
        }
        else 
            m_uiFrenzyTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_faerlina(Creature* pCreature)
{
    return new boss_faerlinaAI(pCreature);
}

void AddSC_boss_faerlina()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_faerlina";
    pNewScript->GetAI = &GetAI_boss_faerlina;
    pNewScript->RegisterSelf();
}
