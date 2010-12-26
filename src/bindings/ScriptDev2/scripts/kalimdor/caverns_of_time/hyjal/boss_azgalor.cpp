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
SDName: boss_azgalor
SD%Complete: 
SDComment:
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */

#include "precompiled.h"
#include "hyjal.h"

enum
{
    SAY_INTRO        = 10999,
    SAY_DOOM         = 11000,
    SAY_DOOM2        = 11046,
    SAY_AGGRO        = 11003,
    SAY_WOUND        = 11004,
    SAY_WOUND2       = 11005,
    SAY_SLAY         = 11001,
    SAY_SLAY2        = 11048,
    SAY_SLAY3        = 11047,
    SAY_DEATH        = 11002,

    // Azgalor
    SPELL_CLEAVE            = 31345,
    SPELL_RAIN              = 31340, 
    SPELL_FLAMES            = 31341,
    SPELL_HOWL              = 31344,
    SPELL_DOOM              = 31347,  // Summon Entry 17864
    SPELL_ENRAGE            = 26662,  // rage id  
};

/*class MANGOS_DLL_DECL AzgalorDoom : public Aura
{
    public:
        AzgalorDoom(SpellEntry *spellInfo, SpellEffectIndex eff, int32 *bp, Unit *target, Unit *caster) : Aura(spellInfo, eff, bp, target, caster, NULL)
            {}
};*/

struct MANGOS_DLL_DECL boss_azgalorAI : public ScriptedAI
{
    boss_azgalorAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
    
    ScriptedInstance* pInstance;

    uint32 CleaveTimer;
    uint32 RainTimer;
    uint32 HowlTimer;
    uint32 DoomTimer;
    uint32 EnrageTimer;

    void Reset()
    {
        if (pInstance)
            pInstance->SetData(TYPE_ANETHERON, NOT_STARTED);

        CleaveTimer = 10000;
        RainTimer = 20000;
        HowlTimer = 10000+rand()%5000;
        DoomTimer = 45000+rand()%5000;
        EnrageTimer = 600000;
    }

    void Aggro(Unit *who)
    {
        DoPlaySoundToSet(m_creature, SAY_INTRO);

        m_creature->SetInCombatWithZone();

        if (pInstance)
        {
            pInstance->SetData(TYPE_AZGALOR, IN_PROGRESS);
            error_log("Debug: Azgalor event IN_PROGRESS zainicjowany przez %u", who->GetGUID()); // usunac jesli wszystko bedzie OK
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
            pInstance->SetData(TYPE_AZGALOR, DONE); 
            error_log("Debug: Azgalor - event DONE");                                            // usunac jesli wszystko bedzie OK
        }
        DoPlaySoundToSet(m_creature, SAY_DEATH);
    }

    void CastDoom()
    {
        SpellEntry *spellInfo = (SpellEntry *)GetSpellStore()->LookupEntry(SPELL_DOOM);
        if (spellInfo)
            //target without tank
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
            {
                if (pTarget->GetTypeId() == TYPEID_PLAYER)
                {
                    for(uint8 i=0; i< MAX_EFFECT_INDEX; ++i)
                    {
                        uint8 eff = spellInfo->Effect[SpellEffectIndex(i)];
                        if (eff >= TOTAL_SPELL_EFFECTS)
                            continue;
                        //uint8 i=1;
                        /*pTarget->AddAura(new AzgalorDoom(spellInfo, SpellEffectIndex(i), NULL, pTarget, pTarget));*/
                    }
                }
                else
                    DoomTimer = 1000;
            }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
            return;

        if(m_creature->HasAura(SPELL_FLAMES))
            m_creature->RemoveAurasDueToSpell(SPELL_FLAMES);

        if(CleaveTimer < diff)
        {
            if(m_creature->getVictim())
            {
                DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                CleaveTimer = 10000;
            }
        }
        else
            CleaveTimer -= diff;

        if(RainTimer < diff)
        {
            switch (urand(0, 2))
            {
                case 0: DoPlaySoundToSet(m_creature, SAY_WOUND); break;
                case 1: DoPlaySoundToSet(m_creature, SAY_WOUND2); break;
                case 2: DoPlaySoundToSet(m_creature, SAY_AGGRO); break;
            }

            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                DoCastSpellIfCan(pTarget, SPELL_RAIN);
                pTarget->CastSpell(pTarget, SPELL_FLAMES, false);
                RainTimer = urand(20000, 35000);
            }                                
        }
        else
            RainTimer -= diff;

        if(HowlTimer < diff)
        {
            DoCast(m_creature, SPELL_HOWL); 
            HowlTimer = 15000+rand()%5000;                                            
        }
        else
            HowlTimer -= diff;

        if(DoomTimer < diff)
        {
            DoPlaySoundToSet(m_creature, urand(0, 1) ? SAY_DOOM : SAY_DOOM2);
            CastDoom();
            DoomTimer = urand(45000, 50000);
        }
        else
            DoomTimer -= diff;

        if(EnrageTimer < diff)
        {
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE);
            EnrageTimer = 300000;
        }
        else
            EnrageTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_azgalor(Creature *_Creature)
{
    return new boss_azgalorAI (_Creature);
}

void AddSC_boss_azgalor()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_azgalor";
    newscript->GetAI = &GetAI_boss_azgalor;
    newscript->RegisterSelf();
}