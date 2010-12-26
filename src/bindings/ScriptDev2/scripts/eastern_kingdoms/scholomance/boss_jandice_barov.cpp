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
SDName: Boss_jandicebarov
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_CURSEOFBLOOD          = 24673,
    SPELL_ILLUSION              = 17773,

    // Spells of Illusion of Jandice Barov
    SPELL_CLEAVE                = 15584
};

struct MANGOS_DLL_DECL boss_jandicebarovAI : public ScriptedAI
{
    boss_jandicebarovAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiCurseOfBlood_Timer;
    uint32 m_uiInvisible_Timer;
    bool bInvisible;

    void Reset()
    {
        m_uiCurseOfBlood_Timer = 15000;
        m_uiInvisible_Timer = 3000;
        bInvisible = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiInvisible_Timer < uiDiff)
        {
            if (!bInvisible)
            {
                DoCast(m_creature->getVictim(),SPELL_ILLUSION);
                m_creature->SetVisibility(VISIBILITY_OFF);
                m_creature->addUnitState(UNIT_STAT_STUNNED);
                bInvisible = true;
                m_uiInvisible_Timer = 3000;
                return;
            }

            if (bInvisible)
            {
                m_creature->clearUnitState(UNIT_STAT_STUNNED);
                m_creature->SetVisibility(VISIBILITY_ON);
                if (!m_creature->getThreatManager().isThreatListEmpty())
                    if (Unit* pVictim = m_creature->GetMap()->GetUnit(m_creature->getThreatManager().getCurrentVictim()->getUnitGuid()))
                        m_creature->getThreatManager().modifyThreatPercent(pVictim,-99);

             bInvisible = false;
             //25 seconds until we should cast this agian
             m_uiInvisible_Timer = 25000;
            }
        } else m_uiInvisible_Timer -= uiDiff;

        //m_uiCurseOfBlood_Timer
        if (m_uiCurseOfBlood_Timer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_CURSEOFBLOOD);
            m_uiCurseOfBlood_Timer = 30000;
        }else m_uiCurseOfBlood_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

// Illusion of Jandice Barov Script

struct MANGOS_DLL_DECL mob_illusionofjandicebarovAI : public ScriptedAI
{
    mob_illusionofjandicebarovAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 Cleave_Timer;

    void Reset()
    {
        Cleave_Timer = urand(2000, 8000);
        m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Cleave_Timer
        if (Cleave_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
            Cleave_Timer = urand(5000, 8000);
        }else Cleave_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jandicebarov(Creature* pCreature)
{
    return new boss_jandicebarovAI(pCreature);
}

CreatureAI* GetAI_mob_illusionofjandicebarov(Creature* pCreature)
{
    return new mob_illusionofjandicebarovAI(pCreature);
}

void AddSC_boss_jandicebarov()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_jandice_barov";
    newscript->GetAI = &GetAI_boss_jandicebarov;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_illusionofjandicebarov";
    newscript->GetAI = &GetAI_mob_illusionofjandicebarov;
    newscript->RegisterSelf();
}
