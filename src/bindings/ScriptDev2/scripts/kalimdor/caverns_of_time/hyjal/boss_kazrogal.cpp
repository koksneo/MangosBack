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
SDAuthor: ScrappyDoo
SDTester: Smaller
SD%Complete: 95%
SDComment: Playable
SDCategory: Caverns of Time, Mount Hyjal
EndScriptData */

#include "precompiled.h"
#include "hyjal.h"

enum
{
    SPELL_CLEAVE    = 31436,
    SPELL_WARSTOMP    = 31480,
    SPELL_MARK        = 31447,
    SPELL_MARK2        = 31463,

    SOUND_ONDEATH    = 11018,
    SOUND_ONSLAY1    = 11017,
    SOUND_ONSLAY2    = 11053,
    SOUND_ONSLAY3    = 11054,

    SOUND_MARK1        = 11016,
    SOUND_MARK2        = 11052,

    SOUND_ONAGGRO    = 11015,
};

class MANGOS_DLL_DECL KazrogalMark : public Aura
{
    public:
        KazrogalMark(SpellEntry *spellInfo, SpellEffectIndex eff, int32 *bp, Unit *target, Unit *caster) : Aura(spellInfo, eff, bp, target, caster, NULL)
            {}
};

struct MANGOS_DLL_DECL boss_kazrogalAI : public ScriptedAI
{
    boss_kazrogalAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 CleaveTimer;
    uint32 WarStompTimer;
    uint32 MarkTimer;
    uint32 BaseMarkTimer;
    uint32 MarkCount;
    uint32 MarkBlastTimer;

    void Reset()
    {
        MarkBlastTimer = 1000; 
        MarkCount = 1;
        CleaveTimer = 5000;
        WarStompTimer = 15000;
        MarkTimer = 60000;
        BaseMarkTimer = 60000;

        if(m_pInstance)
            m_pInstance->SetData(TYPE_KAZROGAL, NOT_STARTED);
    }

    void EnterCombat(Unit *who)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_KAZROGAL, IN_PROGRESS);
        DoPlaySoundToSet(m_creature, SOUND_ONAGGRO);
        m_creature->SetInCombatWithZone();
    }

    void KilledUnit(Unit *victim)
    {
        switch(rand()%3)
        {
            case 0:
                DoPlaySoundToSet(m_creature, SOUND_ONSLAY1);
                break;
            case 1:
                DoPlaySoundToSet(m_creature, SOUND_ONSLAY2);
                break;
            case 2:
                DoPlaySoundToSet(m_creature, SOUND_ONSLAY3);
                break;
        }
    }

    void JustDied(Unit *victim)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_KAZROGAL, DONE); 
            error_log("Debug: Azgalor - event DONE");                                            // usunac jesli wszystko bedzie OK
        }
        DoPlaySoundToSet(m_creature, SOUND_ONDEATH);
    }

    void CastMark()
    {
        SpellEntry *spellInfo = (SpellEntry *)GetSpellStore()->LookupEntry(SPELL_MARK);
        if (spellInfo)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                if (target && target->GetTypeId() == TYPEID_PLAYER && target->getPowerType() == POWER_MANA)
                {
                    for(uint32 i=0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        uint8 eff = spellInfo->Effect[SpellEffectIndex(i)];
                        if (eff >= TOTAL_SPELL_EFFECTS)
                            continue;
                        target->AddAura(new KazrogalMark(spellInfo, SpellEffectIndex(i), NULL, target, target));
                    }    
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(CleaveTimer < diff)
        {
            if(m_creature->getVictim())
                DoCast(m_creature->getVictim(), SPELL_CLEAVE);
            CleaveTimer = 6000+rand()%15000;
        }else CleaveTimer -= diff;

        if(WarStompTimer < diff)
        {
            DoCast(m_creature, SPELL_WARSTOMP);
            WarStompTimer = 60000;
        }else WarStompTimer -= diff;

        if(m_creature->HasAura(SPELL_MARK))
            m_creature->RemoveAurasDueToSpell(SPELL_MARK);

        if(MarkBlastTimer < diff)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                if (target && target->GetTypeId() == TYPEID_PLAYER && target->getPowerType() == POWER_MANA)
                    if(target->HasAura(SPELL_MARK))
                        if((target->GetPower(POWER_MANA)*100) / target->GetMaxPower(POWER_MANA) <= 1)
                            target->CastSpell(target, SPELL_MARK2, true);
            }
            MarkBlastTimer = 1000;
        }MarkBlastTimer -= diff;

        if(MarkTimer < diff)
        {
            CastMark();
            MarkTimer = BaseMarkTimer - MarkCount * 10000;
            if(MarkCount < 6)
                ++MarkCount;
            else
                MarkTimer = 5000;

        }else MarkTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_kazrogal(Creature *_Creature)
{
    return new boss_kazrogalAI (_Creature);
}

void AddSC_boss_kazrogal()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_kazrogal";
    newscript->GetAI = &GetAI_boss_kazrogal;
    newscript->RegisterSelf();
}
