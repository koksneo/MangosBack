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
SDName: Instance_Blackfathom_Deeps
SD%Complete: 50
SDComment:
SDCategory: Blackfathom Deeps
EndScriptData */

#include "precompiled.h"
#include "blackfathom_deeps.h"

/* Encounter 0 = Twilight Lord Kelris
   Encounter 1 = Shrine event
   Must kill twilight lord for shrine event to be possible
 */

struct MANGOS_DLL_DECL instance_blackfathom_deeps : public ScriptedInstance
{
    instance_blackfathom_deeps(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint64 m_uiTwilightLordKelrisGUID;
    uint64 m_uiShrineOfGelihastGUID;
    uint64 m_uiAltarOfTheDeepsGUID;
    uint64 m_uiMainDoorGUID;
    // this values shouldn't drop below 0 but at any case lets make them int type
    int8  m_uiAddsCount;
    int8  m_uiShrinesLit;

    uint64 m_uiShrineGUID[SHRINES_COUNT];
    uint32 m_auiEncounter[MAX_ENCOUNTER];

    void Initialize()
    {
        memset(&m_uiShrineGUID, 0, sizeof(m_uiShrineGUID));
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        m_uiTwilightLordKelrisGUID = 0;
        m_uiShrineOfGelihastGUID = 0;
        m_uiAltarOfTheDeepsGUID = 0;
        m_uiMainDoorGUID = 0;
        m_uiAddsCount = 0;
        m_uiShrinesLit = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        if (pCreature->GetEntry() == 4832)
            m_uiTwilightLordKelrisGUID = pCreature->GetGUID();
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_SHRINE_1:
            case GO_SHRINE_2:
            case GO_SHRINE_3:
            case GO_SHRINE_4:
                for (uint8 i = 0; i < SHRINES_COUNT; ++i)
                {
                    if (m_uiShrineGUID[i] < 1)
                    {
                        m_uiShrineGUID[i] = pGo->GetGUID();
                        break;
                    }
                }
                pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            
            case 103015:    m_uiShrineOfGelihastGUID = pGo->GetGUID();  break;
            case 103016:    m_uiAltarOfTheDeepsGUID = pGo->GetGUID();   break;
            case 21117:     m_uiMainDoorGUID = pGo->GetGUID();          break;
        }
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_KELRIS:
                if (uiData == DONE)
                    for (uint8 i = 0; i < SHRINES_COUNT; ++i)
                    {
                        if (GameObject* pGo = instance->GetGameObject(m_uiShrineGUID[i]))
                            pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                    }

                m_auiEncounter[0] = uiData;
                break;

            case TYPE_SHRINE_EVENT:
                if (uiData == IN_PROGRESS)
                    ++m_uiShrinesLit;

                m_auiEncounter[1] = uiData;
                break;
              
            case DATA_SHRINE_SUMMONS:
                // used to manage summons
                // if TYPE_SHRINE_EVENT is not in progress lets return
                // there are exists mobs with the same entry not related to event
                if (m_auiEncounter[1] != IN_PROGRESS)
                    break;

                // case shrine summoned one more creature
                if (uiData == IN_PROGRESS)
                    ++m_uiAddsCount;

                // case summon just died
                if (uiData == SPECIAL)
                {
                    --m_uiAddsCount;
                    // if one more summon died lets check number of those that are alive
                    // if all shrines are lit and none of adds is alive we can assume that event is done
                    if (m_uiAddsCount < 1 && m_uiShrinesLit >= SHRINES_COUNT)
                        uiData = DONE;
                }
                // in case event is done lets open the door and finish TYPE_SHRINE_EVENT
                if (uiData == DONE)
                {
                    m_auiEncounter[2] = DONE;
                    DoUseDoorOrButton(m_uiMainDoorGUID);
                }
                m_auiEncounter[2] = uiData;
                break;
        }
    }
};

InstanceData* GetInstanceData_instance_blackfathom_deeps(Map* pMap)
{
    return new instance_blackfathom_deeps(pMap);
}

void AddSC_instance_blackfathom_deeps()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_blackfathom_deeps";
    newscript->GetInstanceData = &GetInstanceData_instance_blackfathom_deeps;
    newscript->RegisterSelf();
}
