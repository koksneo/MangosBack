/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Grizzly_Hills
SD%Complete:
SDComment: Quest support: 12138, 12198
SDCategory: Grizzly Hills
EndScriptData */

/* ContentData
npc_depleted_war_golem
EndContentData */

#include "precompiled.h"
#include "pet_ai.h"

/*######
## npc_depleted_war_golem
######*/

enum
{
    SAY_GOLEM_CHARGE            = -1000626,
    SAY_GOLEM_COMPLETE          = -1000627,

    NPC_LIGHTNING_SENTRY        = 26407,

    SPELL_CHARGE_GOLEM          = 47799,
    SPELL_GOLEM_CHARGE_CREDIT   = 47797,
};

struct MANGOS_DLL_DECL npc_depleted_war_golemAI : public ScriptedPetAI
{
    npc_depleted_war_golemAI(Creature* pCreature) : ScriptedPetAI(pCreature) { Reset(); }

    void Reset() { }

    void OwnerKilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetEntry() == NPC_LIGHTNING_SENTRY)
        {
            // Is distance expected?
            if (m_creature->IsWithinDistInMap(pVictim, 10.0f))
                m_creature->CastSpell(m_creature, SPELL_CHARGE_GOLEM, true);
        }
    }
};

CreatureAI* GetAI_npc_depleted_war_golem(Creature* pCreature)
{
    return new npc_depleted_war_golemAI(pCreature);
}

bool EffectAuraDummy_npc_depleted_war_golem(const Aura* pAura, bool bApply)
{
    if (pAura->GetId() != SPELL_CHARGE_GOLEM)
        return true;

    Creature* pCreature = (Creature*)pAura->GetTarget();

    if (!pCreature)
        return true;

    if (pAura->GetEffIndex() == EFFECT_INDEX_0)
    {
        if (bApply)
        {
            DoScriptText(SAY_GOLEM_CHARGE, pCreature);
            pCreature->addUnitState(UNIT_STAT_STUNNED);
        }
        else
        {
            DoScriptText(SAY_GOLEM_COMPLETE, pCreature);
            pCreature->clearUnitState(UNIT_STAT_STUNNED);

            // targets master
            pCreature->CastSpell(pCreature, SPELL_GOLEM_CHARGE_CREDIT, true);
        }
    }

    return true;
}

/*######
##mob_overseer
######*/
enum Overseer
{
    GO_RUNE_BRUNON                  = 188507,
    GO_RUNE_LOCHLI                  = 188506,
    GO_RUNE_KORGAN                  = 188505,
    GO_RUNE_DURVAL                  = 188471,
    GO_RUNE_BASIS                   = 188492,

    NPC_BRUNON                      = 26923,
    NPC_LOCHLI                      = 26922,
    NPC_KORGAN                      = 26921,
    NPC_DURVAL                      = 26920,

    MOB_RUNE_WEAVER                 = 26820,
    MAX_WEAVERS                     = 4,

    FACTION_FRIENDLY_ALL            = 35,
    FACTION_DARK_IRON               = 754,

    SPAWN_DISTANCE                  = 15,

    // Durval
    SPELL_RUNE_OF_DESTRUCTION       = 52715,
    // Korgan
    SPELL_CALL_LIGHTNING            = 32018,
    SPELL_SPELL_REVITALIZING_RUNE   = 52714,
    // Lohli
    SPELL_THUNDERSTORM              = 52717,

    SPELL_WEAVING_OOC               = 47463,

    SAY_AGGRO_1                     = -1999844,
    SAY_AGGRO_2                     = -1999843,
    SAY_AGGRO_3                     = -1999842
};

struct MANGOS_DLL_DECL mob_overseerAI : public ScriptedAI
{
    mob_overseerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        ManageWeavers();
    }

    float WeaverPOSITION[MAX_WEAVERS][3];
    uint64 WeaverGUID[MAX_WEAVERS];
    uint32 m_uiCheckoutTimer;
    uint32 m_uiRuneEntry;
    uint32 m_uiEventTimer;
    uint8 WeaversDead;

    void Reset()
    {
        m_uiCheckoutTimer = 1000;
        m_uiRuneEntry = 0;
        m_uiEventTimer = 10000;
    }

    void ManageWeavers()
    {
        // summoning weavers
        for (int i = 0; i < MAX_WEAVERS; ++i)
        {
            // if somehow overseer entered combat and than evaded before all weavers are dead and despawed (30sec from encounter)
            if (Creature* pWeaver = m_creature->GetMap()->GetCreature(WeaverGUID[i]))
            {
                if (!pWeaver->isAlive())
                {
                    pWeaver->Respawn();
                    pWeaver->Relocate(WeaverPOSITION[i][0], WeaverPOSITION[i][1], WeaverPOSITION[i][2]);
                    pWeaver->SetFacingToObject(m_creature);
                }
            }
            else 
            {
                // spawn weavers around overseer in regular distance
                float x, y, z; 
                m_creature->GetNearPoint(m_creature, x, y, z, m_creature->GetObjectBoundingRadius(), SPAWN_DISTANCE, (i*(6.20f/MAX_WEAVERS)));
                if (Creature* pWeaver = m_creature->SummonCreature(MOB_RUNE_WEAVER, x, y, z, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0))
                {
                    WeaverGUID[i] = pWeaver->GetGUID();
                    WeaverPOSITION[i][0] = x;
                    WeaverPOSITION[i][1] = y;
                    WeaverPOSITION[i][2] = z;                  
                    pWeaver->SetFacingToObject(m_creature);
                }
            }
        }

        switch(m_creature->GetEntry())
        {
            case NPC_BRUNON: m_uiRuneEntry = GO_RUNE_BRUNON; break;
            case NPC_LOCHLI: m_uiRuneEntry = GO_RUNE_LOCHLI; break;
            case NPC_KORGAN: m_uiRuneEntry = GO_RUNE_KORGAN; break;
            case NPC_DURVAL: m_uiRuneEntry = GO_RUNE_DURVAL; break;
        }

        // every reset
        if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, m_uiRuneEntry, INTERACTION_DISTANCE))
            if (pGo->GetGoState() == GO_STATE_READY)
                pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, GO_RUNE_BASIS, INTERACTION_DISTANCE))
            if (pGo->GetGoState() == GO_STATE_READY)
                pGo->SetGoState(GO_STATE_ACTIVE);

        m_creature->SetDisplayId(11686);
        SetEquipmentSlots(false, EQUIP_UNEQUIP, EQUIP_UNEQUIP, EQUIP_UNEQUIP);
        m_creature->setFaction(FACTION_FRIENDLY_ALL);

        WeaversDead = 0;
    }

    void JustReachedHome()
    {
        ManageWeavers();
    }

    void JustRespawned()
    {
        ManageWeavers();
    }

    void Aggro(Unit* pWho)
    {
        if (!pWho)
            return;

        switch(urand(0,2))
        {
            case 0: DoScriptText(SAY_AGGRO_1,m_creature); break;
            case 1: DoScriptText(SAY_AGGRO_2,m_creature); break;
            case 2: DoScriptText(SAY_AGGRO_3,m_creature); break;
        }
        ScriptedAI::Aggro(pWho);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == MOB_RUNE_WEAVER)
            ++WeaversDead;

            if (WeaversDead >= MAX_WEAVERS)
            {
                m_creature->setFaction(FACTION_DARK_IRON);
                m_creature->SetDisplayId(m_creature->GetNativeDisplayId());
                SetEquipmentSlots(true);

                if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, m_uiRuneEntry, INTERACTION_DISTANCE))
                    if (pGo->GetGoState() == GO_STATE_ACTIVE)
                        pGo->SetGoState(GO_STATE_READY);
                if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, GO_RUNE_BASIS, INTERACTION_DISTANCE))
                    if (pGo->GetGoState() == GO_STATE_ACTIVE)
                        pGo->SetGoState(GO_STATE_READY);
            }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // OOC
        if (m_uiCheckoutTimer <= uiDiff)
        {
            for (int i = 0; i < MAX_WEAVERS; ++i)
            {
                if (WeaverGUID[i] == 0)
                    continue;

                Creature* pWeaver = m_creature->GetMap()->GetCreature(WeaverGUID[i]);
                // return weavers to orginal spawn point
                if (pWeaver && pWeaver->isAlive())
                {
                    if (!pWeaver->SelectHostileTarget() || !pWeaver->getVictim())
                    {
                        if ((m_creature->GetDistance(pWeaver) > (SPAWN_DISTANCE + 1.5)) || (m_creature->GetDistance(pWeaver) < (SPAWN_DISTANCE - 1.5)))
                        {
                            pWeaver->GetMotionMaster()->Clear();
                            pWeaver->GetMotionMaster()->MovePoint(0, WeaverPOSITION[i][0], WeaverPOSITION[i][1], WeaverPOSITION[i][2]);
                        }
                        else if (!pWeaver->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                            pWeaver->CastSpell(m_creature, SPELL_WEAVING_OOC, false);
                    }
                    else if (pWeaver->HasAura(SPELL_WEAVING_OOC)) 
                        pWeaver->InterruptSpell(CURRENT_CHANNELED_SPELL);
                }
            }
            m_uiCheckoutTimer = 1000;
        } m_uiCheckoutTimer -= uiDiff;

        // in combat
        if(!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            if (Unit* pVictim = m_creature->getVictim())
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_DURVAL: DoCastSpellIfCan(pVictim, SPELL_RUNE_OF_DESTRUCTION);  break;
                    case NPC_LOCHLI: DoCastSpellIfCan(pVictim, SPELL_THUNDERSTORM);         break;
                    case NPC_KORGAN:
                        if (m_creature->GetHealthPercent() < 80.0f)
                            DoCastSpellIfCan(m_creature, SPELL_SPELL_REVITALIZING_RUNE);
                        else DoCastSpellIfCan(pVictim, SPELL_CALL_LIGHTNING);
                        break;
                    default: break;
                }
            }
            m_uiEventTimer = 30000;
        } else m_uiEventTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }                 
};

CreatureAI* GetAI_mob_overseer(Creature* pCreature)
{
    return new mob_overseerAI(pCreature);
}

void AddSC_grizzly_hills()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_depleted_war_golem";
    pNewScript->GetAI = &GetAI_npc_depleted_war_golem;
    pNewScript->pEffectAuraDummy = &EffectAuraDummy_npc_depleted_war_golem;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_overseer";
    pNewScript->GetAI = &GetAI_mob_overseer;
    pNewScript->RegisterSelf();
}
