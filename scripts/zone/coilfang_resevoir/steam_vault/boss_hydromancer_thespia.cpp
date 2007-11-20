/* Copyright (C) 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#include "../../../sc_defines.h"

#define SPELL_LIGHTNING_CLOUD       25033
#define SPELL_LUNG_BURST            31481 
#define SPELL_ENVELOPING_WINDS      31718
#define SPELL_FROST_BOLT_VOLLEY     36741

#define SAY_AGGRO_1                 "The depths will consume you!"
#define SAY_AGGRO_2                 "Meet your doom, surface dwellers!"
#define SAY_AGGRO_3                 "You will drown in blood!"
#define SAY_SLAY_1                  "To the depths of oblivion with you!"
#define SAY_SLAY_2                  "For my lady and master!"
#define SAY_SUMMON                  "Surge forth my pets!"
#define SAY_DEAD                    "Our matron will be.. the end of.. you.."

#define SOUND_AGGRO_1               10361
#define SOUND_AGGRO_2               10362
#define SOUND_AGGRO_3               10363
#define SOUND_SLAY_1                10364
#define SOUND_SLAY_2                10365
#define SOUND_SUMMON                10360
#define SOUND_DEAD                  10366

struct MANGOS_DLL_DECL boss_thespiaAI : public ScriptedAI
{
    boss_thespiaAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = (c->GetInstanceData()) ? ((ScriptedInstance*)c->GetInstanceData()) : NULL;
        EnterEvadeMode();
    }

    ScriptedInstance *pInstance;

    uint32 LightningCloud_Timer;
    uint32 LungBurst_Timer;
    uint32 EnvelopingWinds_Timer;

    bool InCombat;

    void EnterEvadeMode()
    {
        LightningCloud_Timer = 28000;
        LungBurst_Timer = 7000;
        EnvelopingWinds_Timer = 9000;

        InCombat = false;

        m_creature->RemoveAllAuras(); 
        m_creature->DeleteThreatList();
        m_creature->CombatStop();
        DoGoHome();
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISARM, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SILENCE, true); 
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CONFUSED, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM , true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR , true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DAZE, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SLEEP, true);

        if(pInstance)
            pInstance->SetData("HydromancerThespiaEvent", 0);
    }

    void JustDied(Unit* Killer)
    { 
        DoYell(SAY_DEAD, LANG_UNIVERSAL, NULL);
        DoPlaySoundToSet(m_creature,SOUND_DEAD);

        if(pInstance)
            pInstance->SetData("HydromancerThespiaEvent", 2);
    }

    void KilledUnit(Unit* victim)
    {
        if (rand()%2)
            return;

        switch(rand()%2)
        {        
        case 0:
            DoYell(SAY_SLAY_1, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature,SOUND_SLAY_1);
            break;

        case 1:
            DoYell(SAY_SLAY_2, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature,SOUND_SLAY_2);
            break;        
        }
    }

    void StartEvent()
    {
        switch(rand()%3)
        {
        case 0:
            DoYell(SAY_AGGRO_1, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature,SOUND_AGGRO_1);
            break;

        case 1:
            DoYell(SAY_AGGRO_2, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature,SOUND_AGGRO_2);
            break; 

        case 2:
            DoYell(SAY_AGGRO_3, LANG_UNIVERSAL, NULL);
            DoPlaySoundToSet(m_creature,SOUND_AGGRO_3);
            break;   
        }

        InCombat = true;

        if(pInstance)
            pInstance->SetData("HydromancerThespiaEvent", 1);
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            DoStartMeleeAttack(who);
            if (!InCombat)
                StartEvent();
        }
    }

    void MoveInLineOfSight(Unit *who)
    {  
        if (!who || m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH); 

                DoStartMeleeAttack(who);
                if (!InCombat)
                    StartEvent();            
            }
        }
    }  

    void UpdateAI(const uint32 diff)
    {

        if (!m_creature->SelectHostilTarget())
            return;

        //LightningCloud_Timer
        if (LightningCloud_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);

            DoCast(target, SPELL_LIGHTNING_CLOUD);
            LightningCloud_Timer = 28000;
        }else (LightningCloud_Timer -=diff);

        //LungBurst_Timer
        if (LungBurst_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);

            DoCast(target, SPELL_LUNG_BURST);
            LungBurst_Timer = 10000+rand()%5000;
        }else (LungBurst_Timer -=diff);

        //EnvelopingWinds_Timer
        if (EnvelopingWinds_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);

            DoCast(target, SPELL_ENVELOPING_WINDS);
            EnvelopingWinds_Timer = 10000+rand()%5000;
        }else (EnvelopingWinds_Timer -=diff);

        DoMeleeAttackIfReady();        
    }
};

struct MANGOS_DLL_DECL mob_coilfang_waterelementalAI : public ScriptedAI
{
    mob_coilfang_waterelementalAI(Creature *c) : ScriptedAI(c) {EnterEvadeMode();} 

    uint32 FrostBolt_Timer;

    void EnterEvadeMode()
    {
        FrostBolt_Timer = 10000;
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop();
        DoGoHome();
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            DoStartMeleeAttack(who);
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH); 
                DoStartMeleeAttack(who);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;    

        if (FrostBolt_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FROST_BOLT_VOLLEY);
            FrostBolt_Timer = 10000+rand()%5000;
        }else (FrostBolt_Timer -= diff);

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_thespiaAI(Creature *_Creature)
{
    return new boss_thespiaAI (_Creature);
}
CreatureAI* GetAI_mob_coilfang_waterelementalAI(Creature *_Creature)
{
    return new mob_coilfang_waterelementalAI (_Creature);
}

void AddSC_boss_hydromancer_thespia()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_hydromancer_thespia";
    newscript->GetAI = GetAI_boss_thespiaAI;
    m_scripts[nrscripts++] = newscript;

    newscript = new Script;
    newscript->Name="mob_coilfang_waterelemental"; // 17917
    newscript->GetAI = GetAI_mob_coilfang_waterelementalAI;
    m_scripts[nrscripts++] = newscript;
}
