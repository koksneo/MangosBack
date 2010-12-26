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
SDName: Boss_Four_Horsemen
SD%Complete:
SDComment: Lady Blaumeux, Thane Korthazz, Sir Zeliek, Baron Rivendare
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    //all horsemen
    SPELL_BESERK            = 26662,

    //lady blaumeux
    SAY_BLAU_AGGRO          = -1533044,
    SAY_BLAU_TAUNT1         = -1533045,
    SAY_BLAU_TAUNT2         = -1533046,
    SAY_BLAU_TAUNT3         = -1533047,
    SAY_BLAU_SPECIAL        = -1533048,
    SAY_BLAU_SLAY           = -1533049,
    SAY_BLAU_DEATH          = -1533050,

    EMOTE_UNYIELDING_PAIN   = -1533156,                     // NYI

    SPELL_MARK_OF_BLAUMEUX  = 28833,
    SPELL_UNYILDING_PAIN    = 57381,
    SPELL_VOIDZONE          = 28863,
    SPELL_VOIDZONE_H        = 57463,
    SPELL_SHADOW_BOLT       = 57374,
    SPELL_SHADOW_BOLT_H     = 57464,

    //baron rivendare
    SAY_RIVE_AGGRO1         = -1533065,
    SAY_RIVE_AGGRO2         = -1533066,
    SAY_RIVE_AGGRO3         = -1533067,
    SAY_RIVE_SLAY1          = -1533068,
    SAY_RIVE_SLAY2          = -1533069,
    SAY_RIVE_SPECIAL        = -1533070,
    SAY_RIVE_TAUNT1         = -1533071,
    SAY_RIVE_TAUNT2         = -1533072,
    SAY_RIVE_TAUNT3         = -1533073,
    SAY_RIVE_DEATH          = -1533074,

    SPELL_MARK_OF_RIVENDARE = 28834,
    SPELL_UNHOLY_SHADOW     = 28882,
    SPELL_UNHOLY_SHADOW_H   = 57369,

    //thane korthazz
    SAY_KORT_AGGRO          = -1533051,
    SAY_KORT_TAUNT1         = -1533052,
    SAY_KORT_TAUNT2         = -1533053,
    SAY_KORT_TAUNT3         = -1533054,
    SAY_KORT_SPECIAL        = -1533055,
    SAY_KORT_SLAY           = -1533056,
    SAY_KORT_DEATH          = -1533057,

    SPELL_MARK_OF_KORTHAZZ  = 28832,
    SPELL_METEOR            = 26558,
    SPELL_METEOR_H          = 57467,

    //sir zeliek
    SAY_ZELI_AGGRO          = -1533058,
    SAY_ZELI_TAUNT1         = -1533059,
    SAY_ZELI_TAUNT2         = -1533060,
    SAY_ZELI_TAUNT3         = -1533061,
    SAY_ZELI_SPECIAL        = -1533062,
    SAY_ZELI_SLAY           = -1533063,
    SAY_ZELI_DEATH          = -1533064,

    SPELL_MARK_OF_ZELIEK    = 28835,
    SPELL_HOLY_WRATH        = 28883,
    SPELL_HOLY_WRATH_H      = 57466,
    SPELL_HOLY_BOLT         = 57376,
    SPELL_HOLY_BOLT_H       = 57465,
    SPELL_CONDEMANTION      = 57377,

    // horseman spirits
    SPELL_SPIRIT_OF_BLAUMEUX    = 28931,
    // SPELL_SPIRIT_OF_RIVENDARE   = 0, //does not exists
    SPELL_SPIRIT_OF_KORTHAZZ    = 28932,
    SPELL_SPIRIT_OF_ZELIEK      = 28934,

    // "afteraggro" destination point id
    CORNER_POINT            = 0
};

uint32 Horsemen[4] = {NPC_ZELIEK, NPC_THANE, NPC_BLAUMEUX, NPC_RIVENDARE}; 

// above this thistance creature switch to spam SPELL_UNYILDING_PAIN
#define MARK_DISTANCE 45.0f

float EngagePosition [4][3] =
{
    {2533.84f, -3016.21f, 241.32f}, // Korth'azz
    {2589.03f, -2956.95f, 241.32f}, // Baron Rivendare
    {2476.67f, -2967.28f, 241.27f}, // Lady Blaumeux
    {2538.64f, -2903.14f, 241.27f}  // Sir Zeliek 
};

Player* GetClosestPlayer(Creature* m_creature, float fDistance)
{
    ThreatList const& t_list = m_creature->getThreatManager().getThreatList();
    if (t_list.empty())
        return NULL;

    Player* pTemp = NULL;

    for(ThreatList::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
    {
        Unit *pUnit = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid());
        if (!pUnit || !pUnit->isAlive())
            continue;

        if (pUnit->GetTypeId() == TYPEID_PLAYER && pUnit->GetDistance(m_creature) < fDistance)
        {
            pTemp = (Player*)pUnit;
            fDistance = pUnit->GetDistance(m_creature);
        }
    }

    if (pTemp)
        return pTemp;

    return NULL;
}

struct MANGOS_DLL_DECL npc_horsemen_tap_listAI : public ScriptedAI
{
    npc_horsemen_tap_listAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset(){}

    void EnterEvadeMode()
    {
        if (m_pInstance)
        {
            for (uint8 i = 0; i < 4; ++i)
            {
                if (Creature* pHorsemen = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(Horsemen[i])))
                {
                    if (pHorsemen->isAlive())
                        pHorsemen->AI()->EnterEvadeMode();
                    else
                        pHorsemen->Respawn();
                }
            }
        }
        ScriptedAI::EnterEvadeMode();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->getVictim()->GetDistance2d(2652.13f, -3081.41f) < 95.0f)
            EnterEvadeMode();

        if (m_pInstance && m_pInstance->GetData(TYPE_FOUR_HORSEMEN) == DONE)
            m_creature->ForcedDespawn();
    }
};

CreatureAI* GetAI_npc_horsemen_tap_list(Creature* pCreature)
{
    return new npc_horsemen_tap_listAI(pCreature);
}

struct MANGOS_DLL_DECL boss_lady_blaumeuxAI : public ScriptedAI
{
    boss_lady_blaumeuxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;

    bool   m_bIsRegularMode;
    uint8  m_uiMarksCasted;
    uint32 m_uiPainTimer;
    uint32 m_uiShadowBoltTimer;
    uint32 m_uiMarkTimer;
    uint32 m_uiVoidZoneTimer;
    uint32 m_uiCheckoutTapList;

    void Reset()
    {
        m_uiPainTimer       = 2000;
        m_uiShadowBoltTimer = 3000;
        m_uiMarkTimer       = 24000;
        m_uiVoidZoneTimer   = 15000;
        m_uiMarksCasted     = 0;
        m_uiCheckoutTapList = 0;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_BLAU_AGGRO, m_creature);
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MovePoint(CORNER_POINT, EngagePosition[2][0], EngagePosition[2][1], EngagePosition[2][2]);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BLAUMEUX, IN_PROGRESS);
    }

    void AttackedBy(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_pInstance)
            if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                pTapList->AddThreat(pWho);

        ScriptedAI::AttackedBy(pWho);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_BLAU_SLAY, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_BLAU_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SPIRIT_OF_BLAUMEUX, CAST_TRIGGERED);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BLAUMEUX, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BLAUMEUX, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiCheckoutTapList <= uiDiff)
            {
                if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                    if (Unit* pVictim = pTapList->getVictim())
                        m_creature->AI()->AttackStart(pVictim);
                m_uiCheckoutTapList = 2500;
            }
            else
                m_uiCheckoutTapList -= uiDiff;
            return;
        }

        Player* pPlayer = GetClosestPlayer(m_creature, MARK_DISTANCE);
        if (!pPlayer)
        {
            if (m_uiPainTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_UNYILDING_PAIN);
                m_uiPainTimer = 2000;
            }
            else
                m_uiPainTimer -= uiDiff;
            return;
        }
        else if (m_uiShadowBoltTimer <= uiDiff)
        {
            DoCastSpellIfCan(pPlayer, m_bIsRegularMode ? SPELL_SHADOW_BOLT : SPELL_SHADOW_BOLT_H);
            m_uiShadowBoltTimer = 3000;
        }
        else
            m_uiShadowBoltTimer -= uiDiff;

        // Mark of Blaumeux
        if (m_uiMarkTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MARK_OF_BLAUMEUX, CAST_INTERRUPT_PREVIOUS);
            ++m_uiMarksCasted;
            if (m_uiMarksCasted >= 100)
                DoCastSpellIfCan(m_creature, SPELL_BESERK);

            m_uiMarkTimer = 15000;
        }
        else
            m_uiMarkTimer -= uiDiff;

        // Void Zone
        if (m_uiVoidZoneTimer <= uiDiff)
        {
            if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pUnit, m_bIsRegularMode ? SPELL_VOIDZONE : SPELL_VOIDZONE_H);
            m_uiVoidZoneTimer = 15000;
        }
        else
            m_uiVoidZoneTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_lady_blaumeux(Creature* pCreature)
{
    return new boss_lady_blaumeuxAI(pCreature);
}

struct MANGOS_DLL_DECL boss_rivendare_naxxAI : public ScriptedAI
{
    boss_rivendare_naxxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool   m_bIsRegularMode;
    uint8  m_uiMarksCasted;
    uint32 m_uiMarkTimer;
    uint32 m_uiUnholyShadow;
    uint32 m_uiCheckoutTapList;

    void Reset()
    {
        m_uiMarkTimer       = 24000;
        m_uiUnholyShadow    = 15000;
        m_uiMarksCasted     = 0;
        m_uiCheckoutTapList = 500; 
    }

    void Aggro(Unit* pWho)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_RIVE_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_RIVE_AGGRO2, m_creature); break;
            case 2: DoScriptText(SAY_RIVE_AGGRO3, m_creature); break;
        }
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MovePoint(CORNER_POINT, EngagePosition[1][0], EngagePosition[1][1], EngagePosition[1][2]);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RIVENDARE, IN_PROGRESS);
    }

    void AttackedBy(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_pInstance)
            if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                pTapList->AddThreat(pWho);

        ScriptedAI::AttackedBy(pWho);
    }

    void MovementInform(uint32 uiMoveType, uint32 uiPointId)
    {
        if (uiMoveType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == CORNER_POINT)
        {
            SetCombatMovement(true);
            if (Unit* pUnit = m_creature->getVictim())
            {
                m_creature->GetMotionMaster()->Clear(true, true);
                m_creature->GetMotionMaster()->MoveChase(pUnit);
            }
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_RIVE_SLAY1 : SAY_RIVE_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_RIVE_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RIVENDARE, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_RIVENDARE, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiCheckoutTapList <= uiDiff)
            {
                if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                    if (Unit* pVictim = pTapList->getVictim())
                        m_creature->AI()->AttackStart(pVictim);
                m_uiCheckoutTapList = 2500;
            }
            else
                m_uiCheckoutTapList -= uiDiff;

            return;
        }

        // Mark of Rivendare
        if (m_uiMarkTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MARK_OF_RIVENDARE, CAST_INTERRUPT_PREVIOUS);
            
            ++m_uiMarksCasted;
            if (m_uiMarksCasted >= 100)
                DoCastSpellIfCan(m_creature, SPELL_BESERK);
            m_uiMarkTimer = 12000;
        }
        else
            m_uiMarkTimer -= uiDiff;

        // Unholy Shadow
        if (m_uiUnholyShadow <= uiDiff)
        {
            if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pUnit, m_bIsRegularMode ? SPELL_UNHOLY_SHADOW : SPELL_UNHOLY_SHADOW_H);
            m_uiUnholyShadow = 15000;
        }
        else
            m_uiUnholyShadow -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_rivendare_naxx(Creature* pCreature)
{
    return new boss_rivendare_naxxAI(pCreature);
}

struct MANGOS_DLL_DECL boss_thane_korthazzAI : public ScriptedAI
{
    boss_thane_korthazzAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool   m_bIsRegularMode;
    uint8  m_uiMarksCasted;
    uint32 m_uiMarkTimer;
    uint32 m_uiMeteorTimer;
    uint32 m_uiCheckoutTapList;

    void Reset()
    {
        m_uiMarkTimer       = 24000;
        m_uiMeteorTimer     = 15000;
        m_uiMarksCasted     = 0;
        m_uiCheckoutTapList = 1000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_KORT_AGGRO, m_creature);
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MovePoint(CORNER_POINT, EngagePosition[0][0], EngagePosition[0][1], EngagePosition[0][2]);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_THANE, IN_PROGRESS);
    }

    void AttackedBy(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_pInstance)
            if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                pTapList->AddThreat(pWho);

        ScriptedAI::AttackedBy(pWho);
    }

    void MovementInform(uint32 uiMoveType, uint32 uiPointId)
    {
        if (uiMoveType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == CORNER_POINT)
        {
            SetCombatMovement(true);
            if (Unit* pUnit = m_creature->getVictim())
            {
                m_creature->GetMotionMaster()->Clear(true, true);
                m_creature->GetMotionMaster()->MoveChase(pUnit);
            }
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KORT_SLAY, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_KORT_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SPIRIT_OF_KORTHAZZ, CAST_TRIGGERED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_THANE, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
           m_pInstance->SetData(TYPE_THANE, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiCheckoutTapList <= uiDiff)
            {
                if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                    if (Unit* pVictim = pTapList->getVictim())
                        m_creature->AI()->AttackStart(pVictim);
                m_uiCheckoutTapList = 2500;
            }
            else
                m_uiCheckoutTapList -= uiDiff;

            return;
        }

        // Mark of Korthazz
        if (m_uiMarkTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MARK_OF_KORTHAZZ, CAST_INTERRUPT_PREVIOUS);

            ++m_uiMarksCasted;
            if (m_uiMarksCasted >= 100)
                DoCastSpellIfCan(m_creature, SPELL_BESERK);
            m_uiMarkTimer = 12000;
        }
        else
            m_uiMarkTimer -= uiDiff;

        // Meteor
        if (m_uiMeteorTimer <= uiDiff)
        {
            if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pUnit, m_bIsRegularMode ?  SPELL_METEOR : SPELL_METEOR_H);
            m_uiMeteorTimer = 15000;
        }
        else
            m_uiMeteorTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_thane_korthazz(Creature* pCreature)
{
    return new boss_thane_korthazzAI(pCreature);
}

struct MANGOS_DLL_DECL boss_sir_zeliekAI : public ScriptedAI
{
    boss_sir_zeliekAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool   m_bIsRegularMode;
    uint8  m_uiMarksCasted;
    uint32 m_uiCondemnationTimer;
    uint32 m_uiMarkTimer;
    uint32 m_uiHolyWrathTimer;
    uint32 m_uiHolyBoltTimer;
    uint32 m_uiCheckoutTapList;

    void Reset()
    {
        m_uiHolyBoltTimer       = 3000;
        m_uiMarkTimer           = 24000;
        m_uiHolyWrathTimer      = 12000;
        m_uiCondemnationTimer   = 2000;
        m_uiMarksCasted         = 0;
        m_uiCheckoutTapList     = 1500;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_ZELI_AGGRO, m_creature);
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MovePoint(CORNER_POINT, EngagePosition[3][0], EngagePosition[3][1], EngagePosition[3][2]);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZELIEK, IN_PROGRESS);
    }

    void AttackedBy(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_pInstance)
            if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                pTapList->AddThreat(pWho);

        ScriptedAI::AttackedBy(pWho);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_ZELI_SLAY, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_ZELI_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SPIRIT_OF_ZELIEK, CAST_TRIGGERED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZELIEK, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZELIEK, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiCheckoutTapList <= uiDiff)
            {
                if (Creature* pTapList = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_HORSEMEN_TAP_LIST)))
                    if (Unit* pVictim = pTapList->getVictim())
                        m_creature->AI()->AttackStart(pVictim);
                m_uiCheckoutTapList = 2500;
            }
            else
                m_uiCheckoutTapList -= uiDiff;

            return;
        }

        Player* pPlayer = GetClosestPlayer(m_creature, MARK_DISTANCE);
        if (!pPlayer)
        {
            if (m_uiCondemnationTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_CONDEMANTION);
                m_uiCondemnationTimer = 2000;
            }
            else
                m_uiCondemnationTimer -= uiDiff;
            return;
        }
        else if(m_uiHolyBoltTimer <= uiDiff)
        {
            DoCastSpellIfCan(pPlayer, m_bIsRegularMode ? SPELL_HOLY_BOLT : SPELL_HOLY_BOLT_H);
            m_uiHolyBoltTimer = 3000;
        }
        else
            m_uiHolyBoltTimer -= uiDiff;

        // Mark of Zeliek
        if (m_uiMarkTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MARK_OF_ZELIEK, CAST_INTERRUPT_PREVIOUS);
            ++m_uiMarksCasted;
            if (m_uiMarksCasted >= 100)
                DoCastSpellIfCan(m_creature, SPELL_BESERK);

            m_uiMarkTimer = 15000;
        }
        else
            m_uiMarkTimer -= uiDiff;

        // Holy Wrath
        if (m_uiHolyWrathTimer <= uiDiff)
        {
            if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pUnit, m_bIsRegularMode ? SPELL_HOLY_WRATH : SPELL_HOLY_WRATH_H);
            m_uiHolyWrathTimer = 12000;
        }
        else
            m_uiHolyWrathTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_sir_zeliek(Creature* pCreature)
{
    return new boss_sir_zeliekAI(pCreature);
}

void AddSC_boss_four_horsemen()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_lady_blaumeux";
    NewScript->GetAI = &GetAI_boss_lady_blaumeux;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "boss_rivendare_naxx";
    NewScript->GetAI = &GetAI_boss_rivendare_naxx;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "boss_thane_korthazz";
    NewScript->GetAI = &GetAI_boss_thane_korthazz;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "boss_sir_zeliek";
    NewScript->GetAI = &GetAI_boss_sir_zeliek;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "npc_horsemen_tap_list";
    NewScript->GetAI = &GetAI_npc_horsemen_tap_list;
    NewScript->RegisterSelf();
}
