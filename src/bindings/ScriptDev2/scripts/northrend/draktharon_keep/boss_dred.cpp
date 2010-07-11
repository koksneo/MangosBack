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

/* Script Data Start
SDName: Boss dred
SDAuthor: Manuel
SD%Complete: 100 %
SDComment:
SDCategory:
Script Data End */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    RAID_EMOTE_RISE_TALOON                      = -1999797,

    SPELL_BELLOWING_ROAR                        = 22686, // fears the group, can be resisted/dispelled
    SPELL_GRIEVOUS_BITE                         = 48920,
    SPELL_MANGLING_SLASH                        = 48873, //casted on the current tank, adds debuf
    SPELL_FEARSOME_ROAR                         = 48849,
    H_SPELL_FEARSOME_ROAR                       = 59422, //Not stacking, debuff
    SPELL_PIERCING_SLASH                        = 48878, //debuff -->Armor reduced by 75%
    SPELL_RAPTOR_CALL                           = 59416, //dummy
    SPELL_GUT_RIP                               = 49710,
    SPELL_REND                                  = 13738,

    NPC_DRAKKARI_GUTRIPPER                      = 26641,
    NPC_DRAKKARI_SCYTHECLAW                     = 26628
};

struct MANGOS_DLL_DECL boss_dredAI : public ScriptedAI
{
    boss_dredAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    uint32 BellowingRoarTimer;
    uint32 GrievousBiteTimer;
    uint32 ManglingSlashTimer;
    uint32 FearsomeRoarTimer;
    uint32 PiercingSlashTimer;
    uint32 RaptorCallTimer;
    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;

    void Reset()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DREK,NOT_STARTED);

        BellowingRoarTimer = 33000;
        GrievousBiteTimer  = 20000;
        ManglingSlashTimer = 18500;
        FearsomeRoarTimer  = urand(10000, 20000);
        PiercingSlashTimer = 17000;
        RaptorCallTimer    = urand(20000, 25000);
    }

    void EnterCombat(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DREK, IN_PROGRESS);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
         if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (BellowingRoarTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BELLOWING_ROAR);
            BellowingRoarTimer = 40000;
        }
        else
            BellowingRoarTimer -= uiDiff;

        if (GrievousBiteTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_GRIEVOUS_BITE);
            GrievousBiteTimer = 20000;
        }
        else
            GrievousBiteTimer -= uiDiff;

        if (ManglingSlashTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MANGLING_SLASH);
            ManglingSlashTimer = 20000;
        }
        else
            ManglingSlashTimer -= uiDiff;

        if (FearsomeRoarTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_FEARSOME_ROAR : H_SPELL_FEARSOME_ROAR);
            FearsomeRoarTimer = urand(16000, 18000);
        }
        else
            FearsomeRoarTimer -=uiDiff;

        if (PiercingSlashTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_PIERCING_SLASH);
            PiercingSlashTimer = 20000;
        }
        else
            PiercingSlashTimer -= uiDiff;

        if (RaptorCallTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                DoScriptText(RAID_EMOTE_RISE_TALOON, m_creature);
                DoCastSpellIfCan(pTarget, SPELL_RAPTOR_CALL);
            }
            RaptorCallTimer = urand(20000, 25000);
        }
        else
            RaptorCallTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DREK, DONE);
    }
};

CreatureAI* GetAI_boss_dred(Creature* pCreature)
{
    return new boss_dredAI (pCreature);
}

bool EffectDummyCreature_boss_dred(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    // select random raptor
    if (uiSpellId == SPELL_RAPTOR_CALL && uiEffIndex == EFFECT_INDEX_0)
    {
        // initialize list where nearby raptors will be stored
        std::list<Creature*>lRaptors;
        std::list<Creature*>lTemp;
        // lookup for NPC_DRAKKARI_GUTRIPPER
        GetCreatureListWithEntryInGrid(lTemp, pCaster, NPC_DRAKKARI_GUTRIPPER, 100.0f);
        if (!lTemp.empty())
        {
            // sore only those matching conditions
            for (std::list<Creature*>::iterator itr = lTemp.begin(); itr != lTemp.end(); ++itr)
                if ((*itr) && (*itr)->isAlive() && pCaster->isInAccessablePlaceFor(*itr))
                    lRaptors.push_back(*itr);

            // drop temp list before next type of mobs will be processed in the same list
            lTemp.clear();
        }
        GetCreatureListWithEntryInGrid(lTemp, pCaster, NPC_DRAKKARI_SCYTHECLAW, 100.0f);
        if (!lTemp.empty())
        {
            for (std::list<Creature*>::iterator itr = lTemp.begin(); itr != lTemp.end(); ++itr)
                if ((*itr) && (*itr)->isAlive() && pCaster->isInAccessablePlaceFor(*itr))
                    lRaptors.push_back(*itr);
            lTemp.clear();
        }

        if (lRaptors.empty())
            return false;

        std::list<Creature*>::iterator itr = lRaptors.begin();
        // select random raptor
        advance(itr, rand() % lRaptors.size());

        Unit* pTarget = pCaster->getVictim();
        // if everything OK - make raptor attack current target
        if (pTarget && (*itr))
            (*itr)->AI()->AttackStart(pTarget);
 
        //always return true when we are handling this spell and effect
        return true;
    }
    return false;
}

void AddSC_boss_dred()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_dred";
    newscript->GetAI = &GetAI_boss_dred;
    newscript->pEffectDummyCreature = &EffectDummyCreature_boss_dred;
    newscript->RegisterSelf();
}
