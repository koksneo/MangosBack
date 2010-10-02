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
SDName: Boss_Razuvious
SD%Complete: 75%
SDComment: TODO: Timers and sounds need confirmation, implement spell Hopeless
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SAY_AGGRO1               = -1533120,
    SAY_AGGRO2               = -1533121,
    SAY_AGGRO3               = -1533122,
    SAY_SLAY1                = -1533123,
    SAY_SLAY2                = -1533124,
    SAY_COMMAND1             = -1533125,
    SAY_COMMAND2             = -1533126,
    SAY_COMMAND3             = -1533127,
    SAY_COMMAND4             = -1533128,
    SAY_DEATH                = -1533129,

    SPELL_UNBALANCING_STRIKE = 26613,
    SPELL_DISRUPTING_SHOUT   = 55543,
    SPELL_DISRUPTING_SHOUT_H = 29107,
    SPELL_JAGGED_KNIFE       = 55550,
    SPELL_HOPELESS           = 29125
};

struct MANGOS_DLL_DECL boss_razuviousAI : public ScriptedAI
{
    boss_razuviousAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiUnbalancingStrikeTimer;
    uint32 m_uiDisruptingShoutTimer;
    uint32 m_uiJaggedKnifeTimer;
    uint32 m_uiCommandSoundTimer;
    uint32 m_uiOOCSequenceTimer;
    uint8 m_uiOOCSequence;
    uint8 m_uiCurrentNode;
    Creature* pUnderstudy;
    bool m_bInPoint;

    void Reset()
    {
        m_uiUnbalancingStrikeTimer  = 30000;                 // 30 seconds
        m_uiDisruptingShoutTimer    = 15000;                 // 15 seconds
        m_uiJaggedKnifeTimer        = urand(10000, 15000);
        m_uiCommandSoundTimer       = 40000;                 // 40 seconds
        m_uiOOCSequenceTimer        = 30000;
        m_uiOOCSequence             = 0;
        m_uiCurrentNode             = 0;
        m_bInPoint                  = false;
        pUnderstudy                 = NULL;
    }

    void KilledUnit(Unit* Victim)
    {
        if (urand(0, 3))
            return;

        switch(urand(0, 1))
        {
            case 0: DoScriptText(SAY_SLAY1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY2, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_HOPELESS, CAST_TRIGGERED);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RAZUVIOUS, DONE);
    }

    void Aggro(Unit* pWho)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
            case 2: DoScriptText(SAY_AGGRO3, m_creature); break;
        }

        if (m_pInstance)
        {
            for (std::list<uint64>::iterator itr = m_pInstance->lUnderstudyGUID.begin(); itr != m_pInstance->lUnderstudyGUID.end(); ++itr)
            {
                if (Creature* pUnderstudy = m_pInstance->instance->GetCreature(*itr))
                    pUnderstudy->AI()->AttackStart(pWho);
            }

            m_pInstance->SetData(TYPE_RAZUVIOUS, IN_PROGRESS);
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            if (m_pInstance)
            {
                for (std::list<uint64>::iterator itr = m_pInstance->lUnderstudyGUID.begin(); itr != m_pInstance->lUnderstudyGUID.end(); ++itr)
                {
                    Creature* pUnderstudy = m_pInstance->instance->GetCreature(*itr);
                    if (pUnderstudy && !pUnderstudy->isAlive())
                        pUnderstudy->Respawn();
                }

                m_pInstance->SetData(TYPE_RAZUVIOUS, FAIL);
            }
        }
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != WAYPOINT_MOTION_TYPE)
            return;
       
        // m_uiCurrentNode+1 != uiPointId ensure us that he won't loop in single waypoint few times
        if (m_pInstance && !m_pInstance->lUnderstudyGUID.empty() && m_uiCurrentNode+1 != uiPointId)
        {
            pUnderstudy = NULL;
            for (std::list<uint64>::iterator itr = m_pInstance->lUnderstudyGUID.begin(); itr != m_pInstance->lUnderstudyGUID.end(); ++itr)
            {
                Creature* pTemp = m_pInstance->instance->GetCreature(*itr);
                if (pTemp && pTemp->isAlive() && pTemp->GetDistance(m_creature) < 4.0f)
                {
                    pUnderstudy = pTemp;
                    m_creature->GetMotionMaster()->MoveIdle();
                    m_bInPoint = true;
                    m_uiOOCSequence = 0;
                    m_uiOOCSequenceTimer = 1000;
                    m_uiCurrentNode = uiPointId;
                    break;
                }
            }
        }

        // !! HACK !!
        // lets reset movement in last point beacuse when creature reach last waypoint in his list
        // WaypointMovementGenerator() stops sending MovementInform() to AI
        if (uiPointId == 14)
            m_creature->GetMotionMaster()->Initialize();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_bInPoint && pUnderstudy)
            {
                if (m_uiOOCSequenceTimer < uiDiff)
                {
                    switch(m_uiOOCSequence)
                    {
                        case 0:
                            m_creature->SetFacingToObject(pUnderstudy);
                            break;
                        case 1:
                            pUnderstudy->HandleEmoteState(EMOTE_STATE_NONE);
                            pUnderstudy->SetFacingToObject(m_creature);                            
                            break;
                        case 2:
                            m_creature->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                            break;
                        case 3:
                            pUnderstudy->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                            break;
                        case 4:
                            pUnderstudy->AI()->EnterEvadeMode();
                            m_creature->GetMotionMaster()->MovementExpired();
                            m_bInPoint = false;
                            return;
                    }
                    ++m_uiOOCSequence;
                    m_uiOOCSequenceTimer = 2000;
                }
                else
                    m_uiOOCSequenceTimer -= uiDiff;
            }
            return;
        }

        // Unbalancing Strike
        if (m_uiUnbalancingStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_UNBALANCING_STRIKE);
            m_uiUnbalancingStrikeTimer = 30000;
        }
        else
            m_uiUnbalancingStrikeTimer -= uiDiff;

        // Disrupting Shout
        if (m_uiDisruptingShoutTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_DISRUPTING_SHOUT : SPELL_DISRUPTING_SHOUT_H);
            m_uiDisruptingShoutTimer = 25000;
        }
        else
            m_uiDisruptingShoutTimer -= uiDiff;

        // Jagged Knife
        if (m_uiJaggedKnifeTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_JAGGED_KNIFE);
            m_uiJaggedKnifeTimer = 10000;
        }
        else
            m_uiJaggedKnifeTimer -= uiDiff;

        // Random say
        if (m_uiCommandSoundTimer < uiDiff)
        {
            switch(urand(0, 3))
            {
                case 0: DoScriptText(SAY_COMMAND1, m_creature); break;
                case 1: DoScriptText(SAY_COMMAND2, m_creature); break;
                case 2: DoScriptText(SAY_COMMAND3, m_creature); break;
                case 3: DoScriptText(SAY_COMMAND4, m_creature); break;
            }

            m_uiCommandSoundTimer = 40000;
        }
        else
            m_uiCommandSoundTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_razuvious(Creature* pCreature)
{
    return new boss_razuviousAI(pCreature);
}

void AddSC_boss_razuvious()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_razuvious";
    NewScript->GetAI = &GetAI_boss_razuvious;
    NewScript->RegisterSelf();
}
