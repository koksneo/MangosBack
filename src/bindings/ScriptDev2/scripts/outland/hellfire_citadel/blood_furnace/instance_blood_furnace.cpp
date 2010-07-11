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
SDName: Instance_Blood_Furnace
SD%Complete: 75
SDComment:
SDCategory: Blood Furnace
EndScriptData */

#include "precompiled.h"
#include "blood_furnace.h"

instance_blood_furnace::instance_blood_furnace(Map* pMap) : ScriptedInstance(pMap),
m_uiMakerGUID(0),
m_uiBroggokGUID(0),
m_uiKelidanGUID(0),
m_uiOpenedCell(0),
m_uiAlivePrisoners(0),

m_uiDoorFinalExitGUID(0),
m_uiDoorMakerFrontGUID(0),
m_uiDoorMakerRearGUID(0),
m_uiDoorBroggokFrontGUID(0),
m_uiDoorBrokkokRearGUID(0),
m_uiDoorKelidanExitGUID(0),
m_uiBroggokTargetGUID(0),

m_uiPrisonCell1GUID(0),
m_uiPrisonCell2GUID(0),
m_uiPrisonCell3GUID(0),
m_uiPrisonCell4GUID(0)
{
    Initialize();
}

void instance_blood_furnace::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    memset(&m_uiBoggokPrisonCell, 0, sizeof(4));
}


void instance_blood_furnace::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_MAKER:
            m_uiMakerGUID = pCreature->GetGUID();
            break;
        case NPC_BROGGOK:
            if (m_auiEncounter[3] != DONE)
                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_uiBroggokGUID = pCreature->GetGUID();
            break;
        case NPC_KELIDAN:
            m_uiKelidanGUID = pCreature->GetGUID();
            break;
        case NPC_FELL_ORC:
            if (m_auiEncounter[3] == DONE)
                break;
            // store only Broggok related Orcs
            float fPosX, fPosY, fPosZ, dx, dy;
            pCreature->GetRespawnCoord(fPosX, fPosY, fPosZ);
            dx = fPosX - 450.0f;
            dy = fPosY - 100.0f;
            if (sqrt((dx*dx) + (dy*dy)) > 60.0f)
                break;
            lFelOrcs.push_back(pCreature->GetGUID());
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            break;
    }
}

void instance_blood_furnace::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_DOOR_MAKER_FRONT:                       //the maker front door
            m_uiDoorMakerFrontGUID = pGo->GetGUID();
            break;
        case GO_DOOR_MAKER_REAR:                        //the maker rear door
            m_uiDoorMakerRearGUID = pGo->GetGUID();
            if (m_auiEncounter[0] == DONE)
                DoUseDoorOrButton(m_uiDoorMakerRearGUID);
            break;
        case GO_DOOR_BROGGOK_FRONT:                     //broggok front door
            m_uiDoorBroggokFrontGUID = pGo->GetGUID();
            break;
        case GO_DOOR_BROGGOK_REAR:                      //broggok rear door
            m_uiDoorBrokkokRearGUID = pGo->GetGUID();
            if (m_auiEncounter[3] == DONE)
                pGo->ResetDoorOrButton();
            break;
        case GO_DOOR_KELIDAN_EXIT:                      //kelidan exit door
            m_uiDoorKelidanExitGUID = pGo->GetGUID();
            if (m_auiEncounter[2] == DONE && pGo->GetGoState() == GO_STATE_READY)
                DoUseDoorOrButton(m_uiDoorKelidanExitGUID);
            break;
        case GO_DOOR_FINAL_EXIT:                        //final exit door
            m_uiDoorFinalExitGUID = pGo->GetGUID();
            if (m_auiEncounter[2] == DONE && pGo->GetGoState() == GO_STATE_READY)
               DoUseDoorOrButton(m_uiDoorFinalExitGUID);
            break;
        case 181813: m_uiPrisonCell1GUID = pGo->GetGUID();      break;//the maker cell front right
        case 181814: m_uiPrisonCell2GUID = pGo->GetGUID();      break;//the maker cell back right
        case 181816: m_uiPrisonCell3GUID = pGo->GetGUID();      break;//the maker cell front left
        case 181815: m_uiPrisonCell4GUID = pGo->GetGUID();      break;//the maker cell back left
        case GO_FELORC_CELL_DOOR_1: m_uiBoggokPrisonCell[0] = pGo->GetGUID();  break;
        case GO_FELORC_CELL_DOOR_2: m_uiBoggokPrisonCell[1] = pGo->GetGUID();  break;
        case GO_FELORC_CELL_DOOR_3: m_uiBoggokPrisonCell[2] = pGo->GetGUID();  break;
        case GO_FELORC_CELL_DOOR_4: m_uiBoggokPrisonCell[3] = pGo->GetGUID();  break;
    }
}

uint64 instance_blood_furnace::GetData64(uint32 uiData)
{
    switch(uiData)
    {
        case DATA_THE_MAKER:            return m_uiMakerGUID;
        case DATA_BROGGOK:              return m_uiBroggokGUID;
        case DATA_PRISON_CELL_MAKER1:   return m_uiPrisonCell1GUID;
        case DATA_PRISON_CELL_MAKER2:   return m_uiPrisonCell2GUID;
        case DATA_PRISON_CELL_MAKER3:   return m_uiPrisonCell3GUID;
        case DATA_PRISON_CELL_MAKER4:   return m_uiPrisonCell4GUID;
        case DATA_BROGGOK_TARGET:       return m_uiBroggokTargetGUID;
    }
    return 0;
}

void instance_blood_furnace::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_THE_MAKER_EVENT:
            if (uiData == IN_PROGRESS)
                DoUseDoorOrButton(m_uiDoorMakerFrontGUID);
            else if (uiData == FAIL)
                DoUseDoorOrButton(m_uiDoorMakerFrontGUID);
            else if (uiData == DONE)
                DoUseDoorOrButton(m_uiDoorMakerFrontGUID);
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_BROGGOK_EVENT:
            if (uiData == IN_PROGRESS || uiData == FAIL)
                DoUseDoorOrButton(m_uiDoorBroggokFrontGUID);
            m_auiEncounter[1] = uiData;
            break;
        case TYPE_KELIDAN_EVENT:
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiDoorKelidanExitGUID);
                DoUseDoorOrButton(m_uiDoorFinalExitGUID);
            }
            m_auiEncounter[2] = uiData;
            break;
        case TYPE_BROGGOK_INTRO_EVENT:
            if (uiData == IN_PROGRESS)
            {
                // if we are here that means fellorc died and lever was pulled
                if (m_uiAlivePrisoners)
                    --m_uiAlivePrisoners;
                
                if (!m_uiAlivePrisoners)
                {
                    if (m_uiOpenedCell > 3)
                    {
                        // if none of felorcs left and all cages are opened lets `activate` Broggok
                        uiData = DONE;
                        Creature* pBroggok = instance->GetCreature(m_uiBroggokGUID);
                        if (pBroggok && pBroggok->isAlive())
                        {
                            pBroggok->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            if (Unit* pVictim = Unit::GetUnit(*pBroggok, m_uiBroggokTargetGUID))
                                pBroggok->AI()->AttackStart(pVictim);
                        }
                    }
                    else
                    {
                        // release next pack of felorcs
                        DoUseDoorOrButton(m_uiBoggokPrisonCell[m_uiOpenedCell]);
                        if (GameObject* pCellDoor = instance->GetGameObject(m_uiBoggokPrisonCell[m_uiOpenedCell]))
                        {
                            for (std::list<uint64>::iterator itr = lFelOrcs.begin(); itr != lFelOrcs.end(); ++itr)
                            {
                                Creature* pFelOrc = instance->GetCreature(*itr);
                                if (pFelOrc && pFelOrc->isAlive() && pFelOrc->GetDistance(pCellDoor) < 15.0f)
                                {
                                    pFelOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                    if (Unit* pVictim = Unit::GetUnit(*pFelOrc, m_uiBroggokTargetGUID))
                                    {
                                        pFelOrc->AI()->AttackStart(pVictim);
                                        // all players are immediatly put in combat when event begin
                                        pFelOrc->SetInCombatWithZone();
                                    }
                                    ++m_uiAlivePrisoners;
                                }
                            }
                        }
                        ++m_uiOpenedCell;
                        // Loop this until find populated cage (in case DC when intro in progress or bad DB data)
                        if (!m_uiAlivePrisoners)
                            SetData(TYPE_BROGGOK_INTRO_EVENT, IN_PROGRESS);
                    }
                }                   
            }
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiDoorBrokkokRearGUID);
            m_auiEncounter[3] = uiData;
            break;
        default:
            error_log("SD2: Instance Blood Furnace SetData with Type %u Data %u, but this is not implemented.",uiType,uiData);
            break;
    }
    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;
        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3];
        strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_blood_furnace::SetData64(uint32 uiType, uint32 uiData)
{
    if (uiType == DATA_BROGGOK_TARGET)
        m_uiBroggokTargetGUID = uiData;
}

uint32 instance_blood_furnace::GetData(uint32 uiData)
{
    switch(uiData)
    {
        case TYPE_THE_MAKER_EVENT:  return m_auiEncounter[0];
        case TYPE_BROGGOK_EVENT:    return m_auiEncounter[1];
        case TYPE_KELIDAN_EVENT:    return m_auiEncounter[2];
    }
    return 0;
}

void instance_blood_furnace::Load(const char* chrIn)
{
    if (!chrIn)
    {
       OUT_LOAD_INST_DATA_FAIL;
       return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS || m_auiEncounter[i] == FAIL)
            m_auiEncounter[i] = NOT_STARTED;

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_blood_furnace(Map* pMap)
{
    return new instance_blood_furnace(pMap);
}

void AddSC_instance_blood_furnace()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_blood_furnace";
    pNewScript->GetInstanceData = &GetInstanceData_instance_blood_furnace;
    pNewScript->RegisterSelf();
}
