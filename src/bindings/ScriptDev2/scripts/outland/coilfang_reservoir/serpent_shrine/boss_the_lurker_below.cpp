/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: BOSS LURKER THE BELOW
SD%Complete: 90%
SDComment: Spout need core support.
SDCategory: Coilfang Resevoir, Serpent Shrine Cavern
EndScriptData */

#include "precompiled.h"
#include "serpent_shrine.h"

enum
{
    SPELL_WHIRL          = 37660,   // 37363 original   // 37660 
    SPELL_GEYSER         = 37478,   // 
    SPELL_SPOUT          = 37433,   // 42835 without  mechanic 360*
    SPELL_WATER_BOLT     = 37138,   // working correctly

    MOBID_COILFANG_GUARDIAN = 21873,
    MOBID_COILFANG_AMBUSHER = 21865,
    MOBID_COILFANG_FRENZY = 21508,
};

float AddPos[9][3] = 
{
    {2.855381f, -459.823914f, -19.182686f},        //MOVE_AMBUSHER_1 X, Y, Z
    {12.4f, -466.042267f, -19.182686f},            //MOVE_AMBUSHER_2 X, Y, Z
    {51.366653f, -460.836060f, -19.182686f},    //MOVE_AMBUSHER_3 X, Y, Z
    {62.597980f, -457.433044f, -19.182686f},    //MOVE_AMBUSHER_4 X, Y, Z
    {77.607452f, -384.302765f, -19.182686f},    //MOVE_AMBUSHER_5 X, Y, Z
    {63.897900f, -378.984924f, -19.182686f},    //MOVE_AMBUSHER_6 X, Y, Z
    {34.447250f, -387.333618f, -19.182686f},    //MOVE_GUARDIAN_1 X, Y, Z
    {14.388216f, -423.468018f, -19.625271f},    //MOVE_GUARDIAN_2 X, Y, Z
    {42.471519f, -445.115295f, -19.769423f}     //MOVE_GUARDIAN_3 X, Y, Z
};

struct MANGOS_DLL_DECL boss_the_lurker_belowAI : public ScriptedAI
{
    boss_the_lurker_belowAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
    
    ScriptedInstance* pInstance;

    uint32 WhirlTimer;
    uint32 GeyserTimer;
    uint32 SpoutTimer;
    uint32 Phase1Timer;
    uint32 Phase2Timer;
    uint32 BugTimer;
    uint32 WaterBoltTimer;
    uint32 CoilfangFrenzyTimer;
    Creature* Summoned;

    bool SpoutNow;
    bool Spawned;
    bool Phase1;

    void Reset()
    {
      if (pInstance)
          pInstance->SetData(TYPE_THELURKER_EVENT, NOT_STARTED);

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        WhirlTimer = 90000;     // 18s after spout
        GeyserTimer = 10000;    // random timer -> youtube
        BugTimer = 5000;
        SpoutTimer = 35000;     // every 45s phase1 , 1s when swithing to phase 1
        WaterBoltTimer = 3000;
        CoilfangFrenzyTimer = 1000;

        Phase1Timer = 180000;   // after 1 minute from start phase2
        Phase2Timer = 120000;   // after 2 minutes 

        SpoutNow = false;
        Spawned  = true;
        Phase1 = true;
    }

    void Aggro(Unit *who)
    {
        if (pInstance)
            pInstance->SetData(TYPE_THELURKER_EVENT, IN_PROGRESS);
    }

    void AttackStart(Unit *who)
    {
        if (who == m_creature)
            return;

        if (m_creature->Attack(who, true))
        {
            m_creature->SetInCombatWith(who);
            who->SetInCombatWith(m_creature);
        }
    }

    void JustDied(Unit *victim)
    {
        if (pInstance)
        {
            if (GameObject* pGo = m_creature->GetMap()->GetGameObject(pInstance->GetData64(DATA_LURKER_GEN)))
                pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);

            pInstance->SetData(TYPE_THELURKER_EVENT, SPECIAL);
        }

        Spawned = true;
    }

    void SummonAdd(uint32 entry, float x, float y, float z)
    {
        Summoned = m_creature->SummonCreature(entry, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 180000);
        Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
        if(pTarget && Summoned->AI())
            Summoned->AI()->AttackStart(pTarget);
    }

    void UpdateAI(const uint32 diff)
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
           return;

        m_creature->GetMotionMaster()->Clear(false);

        //Phase Switcher
         if (Phase2Timer < diff)
        {
            Phase1 = false;
            Spawned = false;
            Phase2Timer = 180000;
        }Phase2Timer -= diff;

        if (Phase1Timer < diff)
        {
            SpoutNow = true;
            Phase1 = true;
            Phase1Timer = 180000;
        }Phase1Timer -= diff;

        //Phase 1
        if (Phase1)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
                return;

            m_creature->GetMotionMaster()->Clear(false);

            // anty ranged high aggro
            if(BugTimer < diff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    if(!m_creature->IsWithinDistInMap(pTarget, 3))
                        DoResetThreat();
                BugTimer = 5000;
            }BugTimer -= diff;

            // when switching 2phase 1 cast spout
            if (SpoutNow)
            {
                DoCast(m_creature->getVictim(), SPELL_SPOUT);
                SpoutNow = false;
                WhirlTimer = 14000;
            }

            if (SpoutTimer < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_SPOUT);
                SpoutTimer = 35000;
                WhirlTimer = 14000;
            }
            else
                SpoutTimer -= diff; 
                
            // inwater Coilfang Frenzy Summon
            if (CoilfangFrenzyTimer < diff)
            {
                Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                if(pTarget && !m_creature->IsWithinDistInMap(pTarget, 3))
                    if(pTarget->IsInWater())
                        SummonAdd(MOBID_COILFANG_FRENZY, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());

                CoilfangFrenzyTimer = 1000;
            }else CoilfangFrenzyTimer -= diff;

            if (WhirlTimer < diff)
            {
                DoCast(m_creature, SPELL_WHIRL);
                WhirlTimer = 90000;
            }WhirlTimer -= diff;

            if(GeyserTimer < diff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCastSpellIfCan(pTarget, SPELL_GEYSER);
                GeyserTimer = urand(10000, 15000);
            }GeyserTimer -= diff;

            //melee range checker
            if(WaterBoltTimer < diff)
            {
                Unit* target = NULL;
                int i = 0;
                bool meleeTarget = false;
                target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                if (!target)
                    target = m_creature->getVictim();

                while (target)
                {
                    if( m_creature->IsWithinDistInMap(target, 3))
                    {
                        meleeTarget = true;
                        break;
                    }
                    target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,i);
                    i++;
                }

                if(!meleeTarget)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget,SPELL_WATER_BOLT);
                    else
                        DoCast(m_creature->getVictim(),SPELL_WATER_BOLT);
                    WaterBoltTimer = 3000;
                } else DoMeleeAttackIfReady();
                    
            }else WaterBoltTimer -= diff;

            DoMeleeAttackIfReady();
        }

        //Phase 2
        if(!Spawned)
        {
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[0][0],AddPos[0][1],AddPos[0][2]);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[1][0],AddPos[1][1],AddPos[1][2]);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[2][0],AddPos[2][1],AddPos[2][2]);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[3][0],AddPos[3][1],AddPos[3][2]);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[4][0],AddPos[4][1],AddPos[4][2]);
            SummonAdd(MOBID_COILFANG_AMBUSHER,AddPos[5][0],AddPos[5][1],AddPos[5][2]);
            SummonAdd(MOBID_COILFANG_GUARDIAN,AddPos[6][0],AddPos[6][1],AddPos[6][2]);
            SummonAdd(MOBID_COILFANG_GUARDIAN,AddPos[7][0],AddPos[7][1],AddPos[7][2]);
            SummonAdd(MOBID_COILFANG_GUARDIAN,AddPos[8][0],AddPos[8][1],AddPos[8][2]);
            Spawned = true;
        }
    }
};

CreatureAI* GetAI_boss_the_lurker_below(Creature *_Creature)
{
    return new boss_the_lurker_belowAI (_Creature);
}

void AddSC_boss_the_lurker_below()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_the_lurker_below";
    newscript->GetAI = &GetAI_boss_the_lurker_below;
    newscript->RegisterSelf();
}
