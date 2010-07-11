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
SDName: Instance_Serpent_Shrine
SD%Complete: 90
SDComment:
SDCategory: Coilfang Resevoir, Serpent Shrine Cavern
EndScriptData */

#include "precompiled.h"
#include "serpent_shrine.h"

/* Serpentshrine cavern encounters:
0 - Hydross The Unstable event
1 - Leotheras The Blind Event
2 - The Lurker Below Event
3 - Fathom-Lord Karathress Event
4 - Morogrim Tidewalker Event
5 - Lady Vashj Event
*/

const int MAX_ENCOUNTER = 6;
const int MAX_GENERATOR = 4;
const int MAX_BRIDGE    = 3;

struct MANGOS_DLL_DECL instance_serpentshrine_cavern : public ScriptedInstance
{
    instance_serpentshrine_cavern(Map* pMap) : ScriptedInstance(pMap) { Initialize(); };

    std::string strSaveData;

    uint64 m_uiSharkkis;
    uint64 m_uiTidalvess;
    uint64 m_uiCaribdis;
    uint64 m_uiLadyVashj;
    uint64 m_uiKarathress;
    uint64 m_uiKarathressEvent_Starter;
    uint64 m_uiLeotheras;
    uint64 m_uiLeotherasEvent_Starter;

    uint64 m_uiHydrosGen;
    uint64 m_uiLeotherasGen;
    uint64 m_uiMorogrimGen;
    uint64 m_uiKarathressGen;
    uint64 m_uiLurkerGen;
    uint64 m_uiBridgeGen;

    uint64 m_auiCoilfangBridge_GUID[MAX_BRIDGE];

    uint32 m_auiShieldGenerator[MAX_GENERATOR];
    uint32 m_auiEncounter[MAX_ENCOUNTER];

    bool m_bBridgeActivated;

    void Initialize()
    {
        memset(&m_auiCoilfangBridge_GUID, 0, sizeof(m_auiCoilfangBridge_GUID));
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        memset(&m_auiShieldGenerator, 0, sizeof(m_auiShieldGenerator));

        m_uiSharkkis = 0;
        m_uiTidalvess = 0;
        m_uiCaribdis = 0;
        m_uiLadyVashj = 0;
        m_uiKarathress = 0;
        m_uiKarathressEvent_Starter = 0;
        m_uiLeotheras = 0;
        m_uiLeotherasEvent_Starter = 0;

        m_uiHydrosGen = 0;
        m_uiLeotherasGen = 0;
        m_uiMorogrimGen = 0;
        m_uiKarathressGen = 0;
        m_uiLurkerGen = 0;
        m_uiBridgeGen = 0;
        m_bBridgeActivated = false;
    }

    bool IsEncounterInProgress() const
    {
        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;

        return false;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case 21212: m_uiLadyVashj  = pCreature->GetGUID(); break;
            case 21214: m_uiKarathress = pCreature->GetGUID(); break;
            case 21966: m_uiSharkkis   = pCreature->GetGUID(); break;
            case 21965: m_uiTidalvess  = pCreature->GetGUID(); break;
            case 21964: m_uiCaribdis   = pCreature->GetGUID(); break;
            case 21215: m_uiLeotheras  = pCreature->GetGUID(); break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch (pGo->GetEntry())
        {
            case 185114:
                m_uiHydrosGen            = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                if (GetData(TYPE_HYDROSS_EVENT) == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 185115:
                m_uiLurkerGen            = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                if (GetData(TYPE_THELURKER_EVENT) == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 185116:
                m_uiLeotherasGen            = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                if (GetData(TYPE_LEOTHERAS_EVENT) == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 185117:
                m_uiKarathressGen            = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                if (GetData(TYPE_KARATHRESS_EVENT) == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 185118:
                m_uiMorogrimGen            = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                if (GetData(TYPE_MOROGRIM_EVENT) == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 184203:
                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                m_auiCoilfangBridge_GUID[0] = pGo->GetGUID();
                if (m_bBridgeActivated)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 184204:
                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                m_auiCoilfangBridge_GUID[1] = pGo->GetGUID();
                if (m_bBridgeActivated)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 184205:
                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                m_auiCoilfangBridge_GUID[2] = pGo->GetGUID();
                if (m_bBridgeActivated)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case 184568:
                m_uiBridgeGen = pGo->GetGUID();

                pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                
                if (m_bBridgeActivated)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
        }
    }

    void SetData64(uint32 uiType, uint64 uiData)
    {
        switch(uiType)
        {
            case DATA_KARATHRESS_STARTER:
                m_uiKarathressEvent_Starter = uiData;
 
            case DATA_LEOTHERAS_EVENT_STARTER:
                m_uiLeotherasEvent_Starter = uiData;
        }
    }

    uint64 GetData64(uint32 uiIdentifier)
    {
        switch(uiIdentifier)
        {
            case DATA_SHARKKIS:             return m_uiSharkkis;
            case DATA_TIDALVESS:            return m_uiTidalvess;
            case DATA_CARIBDIS:             return m_uiCaribdis;
            case DATA_LADYVASHJ:            return m_uiLadyVashj;
            case DATA_KARATHRESS:           return m_uiKarathress;
            case DATA_KARATHRESS_STARTER:   return m_uiKarathressEvent_Starter;
            case DATA_LEOTHERAS:            return m_uiLeotheras;
            case DATA_LEOTHERAS_EVENT_STARTER:    return m_uiLeotherasEvent_Starter;
            case DATA_HYDROS_GEN:            return m_uiHydrosGen;
            case DATA_LURKER_GEN:            return m_uiLurkerGen;
            case DATA_LEOTHERAS_GEN:        return m_uiLeotherasGen;
            case DATA_MOROGRIM_GEN:            return m_uiMorogrimGen;
            case DATA_KARATHRESS_GEN:        return m_uiKarathressGen;
            case DATA_BRIDGE_GEN:            return m_uiBridgeGen;
        }
        return 0;
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_HYDROSS_EVENT:        m_auiEncounter[0] = uiData; break;
            case TYPE_LEOTHERAS_EVENT:      m_auiEncounter[1] = uiData; break;
            case TYPE_THELURKER_EVENT:      m_auiEncounter[2] = uiData; break;
            case TYPE_KARATHRESS_EVENT:     m_auiEncounter[3] = uiData; break;
            case TYPE_MOROGRIM_EVENT:       m_auiEncounter[4] = uiData; break;
            case TYPE_LADYVASHJ_EVENT:
                if (uiData == NOT_STARTED)
                    memset(&m_auiShieldGenerator, 0, sizeof(m_auiShieldGenerator));
                if (uiData == SPECIAL)
                {
                    for (uint8 i = 0; i < MAX_BRIDGE; ++i)
                        DoUseDoorOrButton(m_auiCoilfangBridge_GUID[i]);
                    m_bBridgeActivated = true;
                }
                m_auiEncounter[5] = uiData;
                break;
            case TYPE_SHIELDGENERATOR1:     m_auiShieldGenerator[0] = uiData; break;
            case TYPE_SHIELDGENERATOR2:     m_auiShieldGenerator[1] = uiData; break;
            case TYPE_SHIELDGENERATOR3:     m_auiShieldGenerator[2] = uiData; break;
            case TYPE_SHIELDGENERATOR4:     m_auiShieldGenerator[3] = uiData; break;
        }

        if (uiData == DONE || uiData == SPECIAL)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5];

            strSaveData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    const char* Save()
    {
        return strSaveData.c_str();
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_HYDROSS_EVENT:    return m_auiEncounter[0];
            case TYPE_LEOTHERAS_EVENT:  return m_auiEncounter[1];
            case TYPE_THELURKER_EVENT:  return m_auiEncounter[2];
            case TYPE_KARATHRESS_EVENT: return m_auiEncounter[3];
            case TYPE_MOROGRIM_EVENT:   return m_auiEncounter[4];
            case TYPE_LADYVASHJ_EVENT:  return m_auiEncounter[5];
            case TYPE_SHIELDGENERATOR1: return m_auiShieldGenerator[0];
            case TYPE_SHIELDGENERATOR2: return m_auiShieldGenerator[1];
            case TYPE_SHIELDGENERATOR3: return m_auiShieldGenerator[2];
            case TYPE_SHIELDGENERATOR4: return m_auiShieldGenerator[3];
            case TYPE_VASHJ_PHASE3_CHECK:
                for(uint8 i = 0; i < MAX_GENERATOR; ++i)
                {
                    if (m_auiShieldGenerator[i] != DONE)
                        return NOT_STARTED;
                }
                return DONE;
        }
        return 0;
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);

        loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
            >> m_auiEncounter[4] >> m_auiEncounter[5];

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;

        if (GetData(TYPE_HYDROSS_EVENT) == DONE && GetData(TYPE_THELURKER_EVENT) == DONE
            && GetData(TYPE_LEOTHERAS_EVENT) == DONE && GetData(TYPE_KARATHRESS_EVENT) == DONE
            && GetData(TYPE_MOROGRIM_EVENT) == DONE)
                m_bBridgeActivated = true;
    }
};

InstanceData* GetInstanceData_instance_serpentshrine_cavern(Map* pMap)
{
    return new instance_serpentshrine_cavern(pMap);
}

void AddSC_instance_serpentshrine_cavern()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_serpent_shrine";
    newscript->GetInstanceData = &GetInstanceData_instance_serpentshrine_cavern;
    newscript->RegisterSelf();
}
