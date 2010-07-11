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
SDName: Boss_Amanitar
SD%Complete: 90%
SDComment:
SDCategory: Ahn'kahet
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_BASH                  = 57094,
    SPELL_ROOTS                 = 57095,
    SPELL_MINI                  = 57055,
    SPELL_BOLT                  = 57088,
    SPELL_POTENT_FUNGUS         = 56648,
    SPELL_POISON_CLOUD          = 57061,
    SPELL_GROW                  = 62559,
    SPELL_REMOVE_MUSHROOMS_POWER= 57283,

    MOB_HEALTHY_MUSHROOM        = 30435,
    MOB_POISONED_MUSHROOM       = 30391,

    // how many mushrooms will be summoned?
    MUSHROOMS_NUMBER            = 25
};

/*######
## boss_amanitar
######*/

struct MANGOS_DLL_DECL boss_amanitarAI : public ScriptedAI
{
    boss_amanitarAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}

    std::list<uint64>lMushrooms;
    uint32 m_uiBashTimer;
    uint32 m_uiBoltTimer;
    uint32 m_uiRootsTimer;
    uint32 m_uiMiniTimer;
    uint32 m_uiMushroomsTimer;

    void Reset()
    {
        m_uiBashTimer       = urand(10000, 25000);
        m_uiBoltTimer       = urand(10000, 20000);
        m_uiRootsTimer      = urand(10000, 15000);
        m_uiMiniTimer       = urand(25000, 30000);
        m_uiMushroomsTimer  = 5000;
    }

    void JustReachedHome()
    {
        DespawnMusrooms();
    }

    void JustDied(Unit* pKiller)
    {
        DespawnMusrooms();
        DoCastSpellIfCan(m_creature, SPELL_REMOVE_MUSHROOMS_POWER, CAST_TRIGGERED);
    }

    void SummonMushroom()
    {
        float x, y, z, posX, posY, posZ;
        m_creature->GetPosition(x, y, z);
        m_creature->GetRandomPoint(x, y, z, 45.0f, posX, posY, posZ);
        if (Unit* pMushroom = m_creature->SummonCreature(urand(0, 1) > 0 ? MOB_HEALTHY_MUSHROOM : MOB_POISONED_MUSHROOM, posX, posY, posZ, m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000))
            lMushrooms.push_back(pMushroom->GetGUID());
    }

    void DespawnMusrooms()
    {
        if (lMushrooms.empty())
            return;
        for (std::list<uint64>::iterator itr = lMushrooms.begin(); itr != lMushrooms.end(); ++itr)
        {
            if (Creature* pMushroom = (Creature*)Unit::GetUnit(*m_creature, *itr))
                pMushroom->ForcedDespawn();
        }
        lMushrooms.clear();
    }

    void Aggro(Unit* pWho)
    {
        for (uint8 i =  0; i < MUSHROOMS_NUMBER; ++i)
            SummonMushroom();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiBashTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_BASH);
            m_uiBashTimer = urand(5000, 10000);
        }else m_uiBashTimer -= uiDiff;

        if(m_uiBoltTimer <= uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget, SPELL_BOLT);
            m_uiBoltTimer = urand(8000, 16000);
        }else m_uiBoltTimer -= uiDiff;

        if(m_uiRootsTimer <= uiDiff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                DoCastSpellIfCan(pTarget, SPELL_ROOTS);
            m_uiRootsTimer = urand(10000, 15000);
        }else m_uiRootsTimer -= uiDiff;

        if(m_uiMiniTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MINI);
            m_uiMiniTimer = urand(25000, 35000);
        }else m_uiMiniTimer -= uiDiff;

        if(m_uiMushroomsTimer <= uiDiff)
        {
            m_uiMushroomsTimer = 5000;
            if (lMushrooms.empty())
                return;

            for (std::list<uint64>::iterator itr = lMushrooms.begin(), next; itr != lMushrooms.end(); itr = next)
            {
                next = itr;
                ++next;
                Creature* pMushroom = (Creature*)Unit::GetUnit(*m_creature, *itr);
                // if dead and despawned
                if(!pMushroom)
                {
                    lMushrooms.erase(itr);
                    SummonMushroom();
                    if (lMushrooms.empty())
                        break;
                    else
                        next = lMushrooms.begin();
                }
                // if dead or OOR
                else if(pMushroom->GetDistance(m_creature) > 45.0f || !pMushroom->isAlive())
                {
                    lMushrooms.erase(itr);
                    pMushroom->ForcedDespawn();
                    SummonMushroom();
                    if (lMushrooms.empty())
                        break;
                    else
                        next = lMushrooms.begin();
                }
            }
        }else m_uiMushroomsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_amanitar(Creature* pCreature)
{
    return new boss_amanitarAI(pCreature);
}

struct MANGOS_DLL_DECL mob_amanitars_mushroomAI : public Scripted_NoMovementAI
{
    mob_amanitars_mushroomAI(Creature *pCreature) : Scripted_NoMovementAI(pCreature) {Reset();}

    uint32 m_uiPoisonCloudTimer;
 
    void Reset()
    {
        m_uiPoisonCloudTimer = 0;
        DoCastSpellIfCan(m_creature, SPELL_GROW);
    }

    void JustDied(Unit* pKiller)
    {
        if(!pKiller)
            return;

        if (m_creature->GetEntry() == MOB_HEALTHY_MUSHROOM)
        {
            if (pKiller->HasAura(SPELL_MINI))
                pKiller->RemoveAurasDueToSpell(SPELL_MINI);
            else DoCastSpellIfCan(m_creature, SPELL_POTENT_FUNGUS, CAST_TRIGGERED);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->GetEntry() == MOB_POISONED_MUSHROOM)
        {
            if (m_uiPoisonCloudTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_POISON_CLOUD);
                m_uiPoisonCloudTimer = 3000;
            } else m_uiPoisonCloudTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_amanitars_mushroom(Creature* pCreature)
{
    return new mob_amanitars_mushroomAI(pCreature);
}

void AddSC_boss_amanitar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_amanitar";
    newscript->GetAI = &GetAI_boss_amanitar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_amanitars_mushroom";
    newscript->GetAI = &GetAI_mob_amanitars_mushroom;
    newscript->RegisterSelf();
}
