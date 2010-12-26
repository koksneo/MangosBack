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
SDName: Boss_Jedoga
SD%Complete: 95%
SDComment:
SDCategory: Ahn'kahet
*/

#include "precompiled.h"
#include "ahnkahet.h"

enum Sounds
{
    SAY_AGGRO                = -1619017,
    SAY_CALL_SACRIFICE1      = -1619018,
    SAY_CALL_SACRIFICE2      = -1619019,
    SAY_SACRIFICE1           = -1619020,
    SAY_SACRIFICE2           = -1619021,
    SAY_SLAY_1               = -1619022,
    SAY_SLAY_2               = -1619023,
    SAY_SLAY_3               = -1619024,
    SAY_DEATH                = -1619025,

    // preaching 1-5 when it is used?
    SAY_PREACHING1           = -1619026,
    SAY_PREACHING2           = -1619027,
    SAY_PREACHING3           = -1619028,
    SAY_PREACHING4           = -1619029,
    SAY_PREACHING5           = -1619030,

    SAY_VOLUNTEER_CHOOSEN    = -1619031,                    // I have been choosen!
    SAY_VOLUNTEER_SACRIFICED = -1619032,                    // I give myself to the master!

    SPELL_CYCLONE_STRIKE     = 56855,
    SPELL_CYCLONE_STRIKE_H   = 60030,
    SPELL_LIGHTNING_BOLT     = 56891,
    SPELL_LIGHTNING_BOLT_H   = 60032,
    SPELL_THUNDERSHOCK       = 56926,
    SPELL_THUNDERSHOCK_H     = 60029,
    SPELL_GIFT_OF_THE_HERALD = 56219,

    SPELL_SACRIFICE_VISUAL   = 56133,
    SPELL_SACRIFICE_BEAM     = 56150,

    NPC_TWILIGHT_INITIATE    = 30114,
    NPC_TWILIGHT_VOLUNTEER   = 30385,

    SPELL_ARCANE_LIGHTNING   = 60038,
    SPELL_BEAM_VISUAL        = 56312,
    SPELL_JEDOGA_SPHERE      = 56075,
    SPELL_VOLUNTEER_SPHERE   = 56102,

    PHASE_BEFORE_INTRO       = 0,
    PHASE_INTRO              = 1,
    PHASE_AFTER_INTRO        = 2,
    PHASE_READY_TO_ATTACK    = 3,
    PHASE_SACRIFICE_SEQUENCE = 4,

    POINT_IN_THE_AIR         = 0,
    POINT_AT_THE_GROUND      = 1,

    SUMMONS_NUMBER           = 20
};

float SpawnNode[9][3] = 
{
    // destination points
    {391.62f, -688.47f, -16.18f},
    {398.02f, -696.81f, -16.17f},
    {388.37f, -711.46f, -16.18f},
    {378.33f, -723.73f, -16.18f},
    {369.98f, -731.30f, -16.18f},
    {359.85f, -728.33f, -16.19f},
    // minions spawn point
    {370.51f, -742.15f, -15.98f},
    {406.07f, -697.21f, -15.98f},
    // POINT_AT_THE_GROUND
    {373.54f, -704.44f, -16.17f}
};

int32 SayPreaching[6] = {0, SAY_PREACHING1, SAY_PREACHING2, SAY_PREACHING3, SAY_PREACHING4, SAY_PREACHING5};

/*######
## boss_jedoga
######*/

struct MANGOS_DLL_DECL boss_jedogaAI : public ScriptedAI
{
    boss_jedogaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bSacrifice;

    std::list<uint64>lInitiates;
    std::list<uint64>lVolunteers;

    uint32 m_uiThundershockTimer;
    uint32 m_uiCycloneStrikeTimer;
    uint32 m_uiLightningBoltTimer;
    uint32 m_uiEventTimer;
    uint8 subevent;
    uint8 Phase;

    void Reset()
    {
        m_uiThundershockTimer  = 40000;
        m_uiCycloneStrikeTimer = 15000;
        m_uiLightningBoltTimer = 7000;
        m_bSacrifice           = false;

        m_uiEventTimer          = 1000;
        subevent                = 0;
        Phase                   = PHASE_BEFORE_INTRO;

        DespawnAdds(lInitiates);
        DespawnAdds(lVolunteers);

        if (m_pInstance)
        {
            if (Creature* pController = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_JEDOGA_CONTROLLER)))
                pController->RemoveAurasDueToSpell(SPELL_SACRIFICE_VISUAL);
        }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE || !m_pInstance)
            return;

        if (uiPointId == POINT_IN_THE_AIR)
        {
            m_creature->GetMotionMaster()->Clear(true, true);
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->StopMoving();            
        }

        if (uiPointId == POINT_AT_THE_GROUND)
        {
            m_creature->GetMotionMaster()->Clear(true, true);
            m_creature->m_movementInfo.RemoveMovementFlag(MOVEFLAG_FLYING);
            if (Unit* pVictim = m_creature->getVictim())
                m_creature->GetMotionMaster()->MoveChase(pVictim);
        }
    }


    void MoveToPosition(bool up)
    {      
        // aways the same diff in "z" so can be just modified by magic value instead of using getheight()
        if (up)
        {
            DoCastSpellIfCan(m_creature, SPELL_JEDOGA_SPHERE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->GetMotionMaster()->Clear(true, true);
            m_creature->m_movementInfo.AddMovementFlag(MOVEFLAG_FLYING);
            m_creature->GetMotionMaster()->MovePoint(POINT_IN_THE_AIR, SpawnNode[8][0], SpawnNode[8][1], SpawnNode[8][2] + 9);   
        }
        else // down
        {
            m_creature->RemoveAurasDueToSpell(SPELL_JEDOGA_SPHERE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->GetMotionMaster()->Clear(true, true);
            // send visual update to player
            m_creature->MonsterMove(SpawnNode[8][0], SpawnNode[8][1], SpawnNode[8][2], 3000);
            // actual move
            m_creature->GetMotionMaster()->MovePoint(POINT_AT_THE_GROUND, SpawnNode[8][0], SpawnNode[8][1], SpawnNode[8][2]);
        }
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {

        if (pSummoned->GetEntry() == NPC_TWILIGHT_INITIATE)
        {
            lInitiates.remove(pSummoned->GetGUID());

            if (lInitiates.empty())
            {
                Phase = PHASE_READY_TO_ATTACK;
                MoveToPosition(false);
            }
        }
        else if (pSummoned->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
        {
            lVolunteers.remove(pSummoned->GetGUID());
            m_bSacrifice = true;
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        DespawnAdds(lInitiates);
        DespawnAdds(lVolunteers);
    }

    void DespawnAdds(std::list<uint64>& List)
    {
        if (!List.empty())
        {
            for (std::list<uint64>::iterator itr = List.begin(); itr != List.end(); ++itr)
            {
                if (Creature* pSummon = m_creature->GetMap()->GetCreature(*itr))
                    pSummon->ForcedDespawn();
            }
            List.clear();
        }
    }

    void SpawnAdds(std::list<uint64>& List, uint32 uiEntry)
    {
        if (Creature* pSummon = m_creature->SummonCreature(uiEntry, SpawnNode[7][0], SpawnNode[7][1], SpawnNode[7][2], 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
        {
            uint8 uiPoint = urand(0, 2);
            float x,y,z;
            x = SpawnNode[uiPoint][0] -5 + urand(0, 10);
            y = SpawnNode[uiPoint][1] -5 + urand(0, 10);
            z = SpawnNode[uiPoint][2];

            pSummon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            pSummon->GetMotionMaster()->MovePoint(uiPoint, x, y, z);
            List.push_back(pSummon->GetGUID());
        }

        if (Creature* pSummon = m_creature->SummonCreature(uiEntry, SpawnNode[6][0], SpawnNode[6][1], SpawnNode[6][2], 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
        {
            uint8 uiPoint = urand(3, 5);
            float x,y,z;
            x = SpawnNode[uiPoint][0] -5 + urand(0, 10);
            y = SpawnNode[uiPoint][1] -5 + urand(0, 10);
            z = SpawnNode[uiPoint][2];

            pSummon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            pSummon->GetMotionMaster()->MovePoint(uiPoint, x, y, z);
            List.push_back(pSummon->GetGUID());
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        // start intro (summon initiates, speach, etc handled in UpdateAI)
        if (Phase == PHASE_BEFORE_INTRO && pWho->GetTypeId() == TYPEID_PLAYER && m_creature->GetDistance(pWho) <= 35.0f)
        {
            MoveToPosition(true);
            Phase = PHASE_INTRO;
            return;
        }

        // if passed intro return regular ScriptedAI behaviur
        if (Phase == PHASE_READY_TO_ATTACK)
            ScriptedAI::MoveInLineOfSight(pWho);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_JEDOGA, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (Phase == PHASE_INTRO)
            {
                if (m_uiEventTimer <= uiDiff)
                {
                    switch(subevent)
                    {
                        case 0:
                            if (lInitiates.size() < SUMMONS_NUMBER)
                                SpawnAdds(lInitiates, NPC_TWILIGHT_INITIATE);
                            else 
                                ++subevent;
                            m_uiEventTimer = 1500;
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            DoScriptText(SayPreaching[subevent], m_creature);
                            m_uiEventTimer = 10000;
                            ++subevent;
                            break;
                        case 6:
                            if (!lInitiates.empty())
                                for (std::list<uint64>::iterator itr = lInitiates.begin(); itr != lInitiates.end(); ++itr)
                                {
                                    if (Unit* pUnit = m_creature->GetMap()->GetUnit(*itr))
                                        pUnit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                }
                            subevent = 0;
                            Phase = PHASE_AFTER_INTRO;
                            m_uiEventTimer = 1500;
                            break;
                        default: break;
                    }
                } else m_uiEventTimer -= uiDiff;
            }
            return;
        }            

        if (Phase == PHASE_SACRIFICE_SEQUENCE)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                if (!m_pInstance)
                {
                    // this should not happen!
                    Phase = PHASE_READY_TO_ATTACK;
                    return;
                }

                Creature* pController = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_JEDOGA_CONTROLLER));
                if (!pController)
                {
                    // this should not happen!
                    Phase = PHASE_READY_TO_ATTACK;
                    return;
                }

                switch(subevent)
                {
                    case 0:
                        MoveToPosition(true);
                        ++subevent;
                        break;
                    case 1:
                        if (lVolunteers.size() < SUMMONS_NUMBER)
                            SpawnAdds(lVolunteers, NPC_TWILIGHT_VOLUNTEER);
                        else
                        {
                            DoScriptText(urand(0, 1) ? SAY_VOLUNTEER_CHOOSEN : SAY_VOLUNTEER_SACRIFICED, m_creature);
                            ++subevent;
                        }
                        break;
                    case 2:
                        pController->CastSpell(pController, SPELL_SACRIFICE_VISUAL, false);
                        DoCastSpellIfCan(m_creature, SPELL_SACRIFICE_BEAM);
                        ++subevent;
                        break;
                    case 3:
                        {
                            std::list<uint64>::iterator itr = lVolunteers.begin();
                            advance(itr, (rand()% (lVolunteers.size())));
                            if (Creature* pVolunteer = m_creature->GetMap()->GetCreature(*itr))
                            {
                                pVolunteer->RemoveAurasDueToSpell(SPELL_VOLUNTEER_SPHERE);
                                float x, y, z;
                                pController->GetPosition(x, y, z);
                                pVolunteer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                pVolunteer->GetMotionMaster()->MovePoint(7, x, y, z);
                                DoScriptText(SAY_VOLUNTEER_CHOOSEN, pVolunteer);
                            }
                            ++subevent;
                        }
                        break;
                    case 4:
                        if (m_creature->HasAura(SPELL_GIFT_OF_THE_HERALD))
                            m_bSacrifice = true;

                        if (m_bSacrifice)
                        {
                            pController->RemoveAurasDueToSpell(SPELL_SACRIFICE_VISUAL);
                            MoveToPosition(false);
                            Phase = PHASE_READY_TO_ATTACK;
                            subevent = 0;
                            return;
                        }
                        break;
                        default: break;
                }
                m_uiEventTimer = 1500;
            }
            else
                m_uiEventTimer -= uiDiff;

            return;
        }

        if(!m_bSacrifice && m_creature->GetHealthPercent() < 50.0f)
        {
            Phase = PHASE_SACRIFICE_SEQUENCE;
            return;
        }

        if(m_uiCycloneStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_CYCLONE_STRIKE : SPELL_CYCLONE_STRIKE_H);
            m_uiCycloneStrikeTimer = urand(10000, 20000);
        }
        else
            m_uiCycloneStrikeTimer -= uiDiff;

        if(m_uiLightningBoltTimer < uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_LIGHTNING_BOLT : SPELL_LIGHTNING_BOLT_H);
            m_uiLightningBoltTimer = urand(3000, 8000);
        }
        else
            m_uiLightningBoltTimer -= uiDiff;

        if(m_uiThundershockTimer < uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_THUNDERSHOCK : SPELL_THUNDERSHOCK_H);
            m_uiThundershockTimer = urand(8000, 16000);
        }
        else
            m_uiThundershockTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jedoga(Creature* pCreature)
{
    return new boss_jedogaAI(pCreature);
}

struct MANGOS_DLL_DECL mob_jedoga_addAI : public ScriptedAI
{
    mob_jedoga_addAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;

    void Reset() {}

    void JustReachedHome()
    {
            uint8 uiPoint = urand(0, 5);
            float x,y,z;
            x = SpawnNode[uiPoint][0] -5 + urand(0, 10);
            y = SpawnNode[uiPoint][1] -5 + urand(0, 10);
            z = SpawnNode[uiPoint][2];
            m_creature->GetMotionMaster()->MovePoint(uiPoint, x, y, z);
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (m_creature->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
            return;
       
        ScriptedAI::AttackedBy(pAttacker);
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE || !m_pInstance)
            return;

        if (uiPointId == 7)
        {
            if (Creature* pController = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_JEDOGA_CONTROLLER)))
                {
                    m_creature->SetFacingToObject(pController);
                    m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                    DoScriptText(SAY_VOLUNTEER_SACRIFICED, m_creature);
                    if (Creature* pJedoga = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_JEDOGA_SHADOWSEEKER)))
                    {
                        pJedoga->SetFacingToObject(m_creature);
                        pJedoga->CastSpell(m_creature, SPELL_SACRIFICE_BEAM, true);
                    }
                }
        }
        else
        {
            if (Creature* pJedoga = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_JEDOGA_SHADOWSEEKER)))
            {
                m_creature->SetFacingToObject(pJedoga);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                if (m_creature->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
                {
                    SetCombatMovement(false);
                    DoCastSpellIfCan(m_creature, SPELL_VOLUNTEER_SPHERE);
                }
            }
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE) ||
            m_creature->GetEntry() == NPC_TWILIGHT_VOLUNTEER)
            return;

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_jedoga_add(Creature* pCreature)
{
    return new mob_jedoga_addAI(pCreature);
}

void AddSC_boss_jedoga()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_jedoga";
    newscript->GetAI = &GetAI_boss_jedoga;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_jedoga_add";
    newscript->GetAI = &GetAI_mob_jedoga_add;
    newscript->RegisterSelf();
}
