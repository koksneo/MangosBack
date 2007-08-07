// Copyright 2007 by WarHead (United Worlds of Mangos)

#include "../../../sc_defines.h"

#define SPELL_SPELL_REFLECTION  23920
#define SPELL_IMPALE            26548
#define SPELL_WARLORDS_RAGE     36453

#define SOUND_INTRO         10390 // Intro
#define SOUND_REGENERATE    10391 // Regen - He should regenerate at two objects but don't know how.....
#define SOUND_AGGRO1        10392 // Aggro1
#define SOUND_AGGRO2        10393 // Aggro2
#define SOUND_AGGRO3        10394 // Aggro3
#define SOUND_SLAY1         10395 // Slay1
#define SOUND_SLAY2         10396 // Slay2
#define SOUND_DEATH         10397 // Death

struct MANGOS_DLL_DECL boss_warlord_kalithreshAI : public ScriptedAI
{
    boss_warlord_kalithreshAI(Creature *c) : ScriptedAI(c) {EnterEvadeMode();}

    uint32 Reflection_Timer;
    uint32 Impale_Timer;
    uint32 Rage_Timer;

    bool InCombat;

    int RandTime(int time) { return ((rand()%time)*1000); }
    
    void EnterEvadeMode()
    {
        Reflection_Timer = 10000;
        Impale_Timer = 30000;
        Rage_Timer = 60000;

        InCombat = false;

        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop();

        DoGoHome();
    }

    void KilledUnit(Unit* victim)
    {
        switch(rand()%2)
        {
            case 0:
                DoPlaySoundToSet(victim, SOUND_SLAY1);
                break;
            case 1:
                DoPlaySoundToSet(victim, SOUND_SLAY2);
                break;
        }
    }

    void JustDied(Unit* Killer)
    {
        DoPlaySoundToSet(m_creature, SOUND_DEATH);
    }

    void AttackStart(Unit *who)
    {
        if (!who) return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            if (!InCombat)
            {
                switch(rand()%3)
                {
                    case 0:
                        DoPlaySoundToSet(m_creature,SOUND_AGGRO1);
                        break;
                    case 1:
                        DoPlaySoundToSet(m_creature,SOUND_AGGRO2);
                        break;
                    case 2:
                        DoPlaySoundToSet(m_creature,SOUND_AGGRO3);
                        break;
                }
                InCombat = true;
            }
            DoStartMeleeAttack(who);
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who || m_creature->getVictim()) return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura()) who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                if (!InCombat)
                {
                    switch(rand()%3)
                    {
                        case 0:
                            DoPlaySoundToSet(m_creature,SOUND_AGGRO1);
                            break;
                        case 1:
                            DoPlaySoundToSet(m_creature,SOUND_AGGRO2);
                            break;
                        case 2:
                            DoPlaySoundToSet(m_creature,SOUND_AGGRO3);
                            break;
                    }
                    InCombat = true;
                }
                DoStartMeleeAttack(who);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostilTarget()) return;

        if (m_creature->getVictim() && m_creature->isAlive())
        {
            if (Reflection_Timer < diff)
            {
                DoCast(m_creature,SPELL_SPELL_REFLECTION);
                Reflection_Timer = RandTime(60);
            }else Reflection_Timer -= diff;

            if (Impale_Timer < diff)
            {
                Unit* target = NULL;
                target = SelectUnit(SELECT_TARGET_RANDOM,0);

                if (target)
                {
                    DoFaceTarget(target);
                    DoCast(target,SPELL_IMPALE);
                }
                else
                {
                    DoFaceTarget(m_creature->getVictim());
                    DoCast(m_creature->getVictim(),SPELL_IMPALE);
                }
                Impale_Timer = RandTime(40);
            }else Impale_Timer -= diff;

            if (Rage_Timer < diff)
            {
                DoCast(m_creature,SPELL_WARLORDS_RAGE);
                Rage_Timer = 600000;
            }else Rage_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_warlord_kalithresh(Creature *_Creature)
{
    return new boss_warlord_kalithreshAI (_Creature);
}

void AddSC_boss_warlord_kalithresh()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_warlord_kalithresh";
    newscript->GetAI = GetAI_boss_warlord_kalithresh;
    m_scripts[nrscripts++] = newscript;
}
