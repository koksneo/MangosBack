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
SDName: Instance_Obsidian_Sanctum
SD%Complete: 90%
SDComment:
SDCategory: Obsidian Sanctum
EndScriptData */

#include "precompiled.h"
#include "obsidian_sanctum.h"

/* Obsidian Sanctum encounters:
0 - Sartharion
*/

instance_obsidian_sanctum::instance_obsidian_sanctum(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
};

void instance_obsidian_sanctum::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

    m_uiSartharionGUID = 0;
    m_uiTenebronGUID   = 0;
    m_uiShadronGUID    = 0;
    m_uiVesperonGUID   = 0;

    m_uiAcolyteShadronGUID  = 0;
    m_uiAcolyteVesperonGUID = 0;

    m_lTrashMobsGUIDlist.clear();
    m_lTrashMobsGUIDlist.clear();
    m_lEggsGUIDList.clear();
    m_lWhelpsGUIDList.clear();
    m_lBlazesGUIDList.clear();
    //m_lHitByVolcanoGUIDList.clear();
}

void instance_obsidian_sanctum::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_SARTHARION:
            m_uiSartharionGUID = pCreature->GetGUID();
            break;
        //three dragons below set to active state once created.
        //we must expect bigger raid to encounter main boss, and then three dragons must be active due to grid differences
        case NPC_TENEBRON:
            m_uiTenebronGUID = pCreature->GetGUID();
            pCreature->SetActiveObjectState(true);
            break;
        case NPC_SHADRON:
            m_uiShadronGUID = pCreature->GetGUID();
            pCreature->SetActiveObjectState(true);
            break;
        case NPC_VESPERON:
            m_uiVesperonGUID = pCreature->GetGUID();
            pCreature->SetActiveObjectState(true);
            break;
        // trash mobs aggro when Sartharion is engaged
        case NPC_ONYX_BROOD_GENERAL:
        case NPC_ONYX_BLAZE_MISTRESS:
        case NPC_ONYX_FLIGHT_CAPTAIN:
        case NPC_ONYX_SANCTUM_GUARDIAN:
            m_lTrashMobsGUIDlist.push_back(pCreature->GetGUID());
            break;
    }
}

void instance_obsidian_sanctum::SetData(uint32 uiType, uint32 uiData)
{
    if (uiType < 1 || uiType > 7)
        return;

    m_auiEncounter[uiType - 1] = uiData;
}

uint32 instance_obsidian_sanctum::GetData(uint32 uiType)
{
    return m_auiEncounter[uiType - 1];
}

uint64 instance_obsidian_sanctum::GetData64(uint32 uiData)
{
    switch(uiData)
    {
        case DATA_SARTHARION:
            return m_uiSartharionGUID;
        case DATA_TENEBRON:
            return m_uiTenebronGUID;
        case DATA_SHADRON:
            return m_uiShadronGUID;
        case DATA_VESPERON:
            return m_uiVesperonGUID;
        case DATA_ACOL_SHAD:
            return m_uiAcolyteShadronGUID;
        case DATA_ACOL_VESP:
            return m_uiAcolyteVesperonGUID;
    }
    return 0;
}

bool instance_obsidian_sanctum::CheckConditionCriteriaMeet(Player const* pSource, uint32 uiMapId, uint32 uiInstanceConditionId)
{
    return (GetData(uiInstanceConditionId) == DONE);
}

/*bool instance_obsidian_sanctum::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 = 0)
{
    if (uiCriteriaId > 2048)
        return (GetData(uiMiscValue1) == DONE);

    switch (uiCriteriaId)
    {
        case ACHIEV_CRIT_VOLCANO_10:
            if (instance->IsRegularDifficulty())
            {
                for (std::list<uint64>::iterator i = m_lHitByVolcanoGUIDList.begin(); i != m_lHitByVolcanoGUIDList.end(); i++)
                    if (pSource->GetGUID() == *i)
                        return false;

                return true;
            }
            break;
        case ACHIEV_CRIT_VOLCANO_25:
            if (!instance->IsRegularDifficulty())
            {
                for (std::list<uint64>::iterator i = m_lHitByVolcanoGUIDList.begin(); i != m_lHitByVolcanoGUIDList.end(); i++)
                    if (pSource->GetGUID() == *i)
                        return false;

                return true;
            }
            break;
    }

    return false;
}*/

InstanceData* GetInstanceData_instance_obsidian_sanctum(Map* pMap)
{
    return new instance_obsidian_sanctum(pMap);
}

void AddSC_instance_obsidian_sanctum()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_obsidian_sanctum";
    newscript->GetInstanceData = GetInstanceData_instance_obsidian_sanctum;
    newscript->RegisterSelf();
}
