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
SDName: boss_anetheron
SD%Complete: 
SDComment:
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */

#include "precompiled.h"
#include "hyjal.h"

enum
{
    // Yells: You are defenders of a doomed world. Flee here and perhaps you will prolong your pathetic lives. 
    SAY_AGGRO        = 10977,
    // Yells: The swarm is eager to feed.
    SAY_SWARM        = 10979,
    // Yells: Pestilence upon you! 
    SAY_SWARM2        = 11037,
    // Yells: You look tired.
    SAY_SLEEP        = 10978,
    // Yells: Sweet dreams.
    SAY_SLEEP2        = 11545,
    // Yells: Scream for me.
    SAY_SLAY        = 11038,
    // Yells: Pity, no time for a slow death.
    SAY_SLAY2        = 11039,
    // Yells: Your hopes, are lost. 
    SAY_SLAY3        = 10981,
    // Yells: Earth and Sky shall burn!
    SAY_INFERNO        = 11036,
    // Yells: Let fire rain from above! 
    SAY_INFERNO2    = 10980,
    // Yells: The clock... is still... ticking. 
    SAY_DEATH        = 10982,

    // Anetheron Spells
    SPELL_CARRION_SWARM     = 31306,
    SPELL_SLEEP             = 31298,  // affect all raid
    SPELL_VAMPIRIC_AURA     = 38196,  // working
    SPELL_INFERNO           = 31299,  // Summon Entry 17818
    SPELL_ENRAGE            = 26662,  // rage id
    SPELL_STUN                = 24647,  // - 2secs stun

    // Towering Infernal Spells
    SPELL_IMMOLATION        = 31304, //31303,   // 31304     
};

/*class MANGOS_DLL_DECL AnetheronSleep : public Aura
{
    public:
        AnetheronSleep(SpellEntry *spellInfo, SpellEffectIndex eff, int32 *bp, Unit *target, Unit *caster) : Aura(spellInfo, eff, bp, target, caster, NULL)
            {}
};*/

struct MANGOS_DLL_DECL boss_anetheronAI : public ScriptedAI
{
    boss_anetheronAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
    
    ScriptedInstance* pInstance;

    uint32 CarrionSwarmTimer;
    uint32 SleepTimer;
    uint32 VampiricAuraTimer;
    uint32 InfernoTimer;
    uint32 EnrageTimer;

    bool Enraged;

    void Reset()
    {
        if (pInstance)
            pInstance->SetData(TYPE_ANETHERON, NOT_STARTED);

        CarrionSwarmTimer = 15000; // blizzlike
        SleepTimer = 35000+rand()%10000; // yotuube?
        VampiricAuraTimer = 20000+rand()%5000; // youtube?
        InfernoTimer = 60000; // blizzlike

        EnrageTimer = 10*60*1000; // blizzlike
        Enraged = false;
    }

    void Aggro(Unit *who)
    {
        DoPlaySoundToSet(m_creature, SAY_AGGRO);

        if (pInstance)
        {
            pInstance->SetData(TYPE_ANETHERON, IN_PROGRESS);
            error_log("Debug: Anetheron event IN_PROGRESS zainicjowany przez %u", who->GetGUID()); // usunac jesli wszystko bedzie OK
        }
    }

    void KilledUnit(Unit *victim)
    {
        switch (rand()%3)
        {
            case 0: DoPlaySoundToSet(m_creature, SAY_SLAY); break;
            case 1: DoPlaySoundToSet(m_creature, SAY_SLAY2); break;
            case 2: DoPlaySoundToSet(m_creature, SAY_SLAY3); break;
        }
    }

    void JustDied(Unit *victim)
    {
        if (pInstance)
        {
            pInstance->SetData(TYPE_ANETHERON, DONE); 
            error_log("Debug: Anetheron - event DONE");                                            // usunac jesli wszystko bedzie OK

        }
        DoPlaySoundToSet(m_creature, SAY_DEATH);
    }

    void CastSleep()
    {
        SpellEntry *spellInfo = (SpellEntry *)GetSpellStore()->LookupEntry(SPELL_SLEEP);
        if (spellInfo)
            for(uint8 j=0; j<3; ++j)
            {
                if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                {
                    if (pTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        for(uint32 i=0; i < MAX_EFFECT_INDEX; ++i)
                        {
                            uint8 eff = spellInfo->Effect[SpellEffectIndex(i)];
                            if (eff >= TOTAL_SPELL_EFFECTS)
                                continue;
                            /*pTarget->AddAura(new AnetheronSleep(spellInfo, SpellEffectIndex(i), NULL, pTarget, pTarget));*/
                        }
                    }
                    else
                        --j;
                }
            }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
            return;

        if(CarrionSwarmTimer < diff)
        {
            DoPlaySoundToSet(m_creature, urand(0, 1) ? SAY_SWARM : SAY_SWARM2);
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                DoCastSpellIfCan(pTarget, SPELL_CARRION_SWARM);
                CarrionSwarmTimer = 15000;
            }
        }
        else
            CarrionSwarmTimer -= diff;


        if(SleepTimer < diff)
        {
            DoPlaySoundToSet(m_creature, urand(0, 1) ? SAY_SLEEP : SAY_SLEEP2);
            CastSleep();
            SleepTimer = urand(15000, 25000);                                                   //youtube timer
        }
        else
            SleepTimer -= diff;

        if(VampiricAuraTimer < diff)
        {
            DoCast(m_creature, SPELL_VAMPIRIC_AURA); 
            VampiricAuraTimer = urand(10000, 15000);                                              //youtube timer
        }
        else 
            VampiricAuraTimer -= diff;

        if(InfernoTimer < diff)
        {
            DoPlaySoundToSet(m_creature, urand(0, 1) ? SAY_INFERNO : SAY_INFERNO2);
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                pTarget->CastSpell(pTarget, SPELL_STUN, true);
                DoCastSpellIfCan(pTarget, SPELL_INFERNO, CAST_TRIGGERED);
                InfernoTimer = 60000;
            }
        }
        else
            InfernoTimer -= diff;

        if(!Enraged)
            if(EnrageTimer < diff)
            {
                DoCast(m_creature, SPELL_ENRAGE);
                Enraged = true;
            }
            else
                EnrageTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anetheron(Creature *_Creature)
{
    return new boss_anetheronAI (_Creature);
}

/*######
## Towering Infernal
######*/
                                   
struct MANGOS_DLL_DECL mob_towering_infernalAI : public ScriptedAI
{
    mob_towering_infernalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 Immolation_Timer;
    bool Immolation;

    void Reset()
    {
        uint32 Immolation_Timer = 1000;
        Immolation = false;
    }

    void Aggro(Unit* who) {}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(!Immolation)
        {
            DoCast(m_creature, SPELL_IMMOLATION);
            Immolation = true;
        }

        if(Immolation_Timer < diff)
        {
            if (Creature* Anetheron = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(DATA_ANETHERON)))
                if (m_creature->IsWithinDistInMap(Anetheron, 10.0f) && Anetheron->isAlive() && Anetheron->HasAura(SPELL_VAMPIRIC_AURA))
                    DoCast(m_creature, SPELL_VAMPIRIC_AURA);
            Immolation_Timer = 1000;
        }Immolation_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_towering_infernal(Creature* pCreature)
{
    return new mob_towering_infernalAI(pCreature);
}

void AddSC_boss_anetheron()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_anetheron";
    newscript->GetAI = &GetAI_boss_anetheron;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_towering_infernal";
    newscript->GetAI = &GetAI_mob_towering_infernal;
    newscript->RegisterSelf();
}