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
SDName: Boss_Broggok
SD%Complete: 70
SDComment: pre-event not made
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */

#include "precompiled.h"
#include "blood_furnace.h"

enum
{
    SAY_AGGRO               = -1542008,

    SPELL_SLIME_SPRAY       = 30913,
    H_SPELL_SLIME_SPRAY     = 38458,
    SPELL_POISON_CLOUD      = 30916,
    SPELL_POISON_BOLT       = 30917,
    H_SPELL_POISON_BOLT     = 38459,

    SPELL_POISON            = 30914
};

struct MANGOS_DLL_DECL boss_broggokAI : public ScriptedAI
{
    boss_broggokAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blood_furnace*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiAcidSprayTimer;
    uint32 m_uiPoisonSpawnTimer;
    uint32 m_uiPoisonBoltTimer;

    void Reset()
    {
        m_uiAcidSprayTimer   = 10000;
        m_uiPoisonSpawnTimer = 5000;
        m_uiPoisonBoltTimer  = 7000;
    }

    void Aggro(Unit *pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_BROGGOK_EVENT, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BROGGOK_EVENT, FAIL);
    }

    void JustpSummoned(Creature *pSummoned)
    {
        pSummoned->setFaction(16);
        pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        pSummoned->CastSpell(pSummoned, SPELL_POISON, false, 0, 0, m_creature->GetGUID());
    }

    void JustDied(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BROGGOK_EVENT, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiAcidSprayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? H_SPELL_SLIME_SPRAY : SPELL_SLIME_SPRAY);
            m_uiAcidSprayTimer = urand(4000, 12000);
        }
        else
            m_uiAcidSprayTimer -=uiDiff;

        if (m_uiPoisonBoltTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? H_SPELL_POISON_BOLT : SPELL_POISON_BOLT);
            m_uiPoisonBoltTimer = urand(4000, 12000);
        }
        else
            m_uiPoisonBoltTimer -=uiDiff;

        if (m_uiPoisonSpawnTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_POISON_CLOUD);
            m_uiPoisonSpawnTimer = 20000;
        }
        else
            m_uiPoisonSpawnTimer -=uiDiff;

        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_broggok_poisoncloudAI : public ScriptedAI
{
    mob_broggok_poisoncloudAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset() { }
    void MoveInLineOfSight(Unit *pWho) { }
    void AttackStart(Unit *pWho) { }
};

CreatureAI* GetAI_boss_broggok(Creature* pCreature)
{
    return new boss_broggokAI(pCreature);
}

CreatureAI* GetAI_mob_broggok_poisoncloud(Creature* pCreature)
{
    return new mob_broggok_poisoncloudAI(pCreature);
}

bool GOHello_go_cell_door_lever(Player* pPlayer, GameObject* pGo)
{
    instance_blood_furnace* m_pInstance = (instance_blood_furnace*)pGo->GetInstanceData();
    if (!m_pInstance || m_pInstance->GetData(TYPE_BROGGOK_INTRO_EVENT) != NOT_STARTED)
        return true;

    m_pInstance->SetData64(DATA_BROGGOK_TARGET, pPlayer->GetGUID());
    m_pInstance->SetData(TYPE_BROGGOK_INTRO_EVENT, IN_PROGRESS);
    return false;
}


void AddSC_boss_broggok()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_broggok";
    pNewScript->GetAI = &GetAI_boss_broggok;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_broggok_poisoncloud";
    pNewScript->GetAI = &GetAI_mob_broggok_poisoncloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_cell_door_lever";
    pNewScript->pGOHello = &GOHello_go_cell_door_lever;
    pNewScript->RegisterSelf();
}
