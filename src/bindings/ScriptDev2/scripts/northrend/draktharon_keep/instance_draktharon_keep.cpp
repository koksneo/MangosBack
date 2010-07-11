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
SDName: Instance_Draktharon_Keep
SD%Complete: 20%
SDComment:
SDCategory: Utgarde Keep
EndScriptData */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

/* m_auiEncounters:
1 - TYPE_TROLLGORE
2 - TYPE_NOVOS
3 - TYPE_DREK
4 - TYPE_THARONJA

helper encounters:
5 - TYPE_CRYSTAL_EVENT - related to 4 Ritual Crystals around boss_novos
*/

struct MANGOS_DLL_DECL instance_draktharon_keep : public ScriptedInstance
{
    instance_draktharon_keep(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint32 CrystalCounter;
    std::string strInstData;

    uint64 m_uiTrollgoreGUID;
    uint64 m_uiNovosGUID;
    uint64 m_uiDrekGUID;
    uint64 m_uiTharonjaGUID;

    uint64 m_uiRitualCrystalGUID[CRYSTAL_NUMBER];

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        m_uiTrollgoreGUID = 0;
        m_uiNovosGUID = 0;
        m_uiDrekGUID = 0;
        m_uiTharonjaGUID = 0;
        CrystalCounter = 0;
        for (uint8 i = 0; i < CRYSTAL_NUMBER; ++i)
        {
            m_uiRitualCrystalGUID[i] = 0;
        }
            
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case 26630: m_uiTrollgoreGUID = pCreature->GetGUID(); break;
            case 26631: m_uiNovosGUID = pCreature->GetGUID(); break;
            case 27483: m_uiDrekGUID = pCreature->GetGUID(); break;
            case 26632: m_uiTharonjaGUID = pCreature->GetGUID(); break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_RITUAL_CRYSTAL_SW:
            case GO_RITUAL_CRYSTAL_SE:
            case GO_RITUAL_CRYSTAL_NW:
            case GO_RITUAL_CRYSTAL_NE:
                for (uint8 i = 0; i < CRYSTAL_NUMBER; ++i)
                {
                    if (m_uiRitualCrystalGUID[i] == 0)
                    {
                        m_uiRitualCrystalGUID[i] = pGo->GetGUID();
                        break;
                    }
                }
        }
    }

    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            case DATA_TROLLGORE:
                return m_uiTrollgoreGUID;
            case DATA_NOVOS:
                return m_uiNovosGUID;
            case DATA_DREK:
                return m_uiDrekGUID;
            case DATA_THARONJA:
                return m_uiTharonjaGUID;
        }
        return 0;
    }

    uint32 GetData(uint32 uiData)
    {
        switch(uiData)
        {
            case TYPE_TROLLGORE:        return m_auiEncounter[0];
            case TYPE_NOVOS:            return m_auiEncounter[1];
            case TYPE_DREK:             return m_auiEncounter[2];
            case TYPE_THARONJA:         return m_auiEncounter[3];
            case TYPE_CRYSTAL_EVENT:    return m_auiEncounter[4];        
        }
        return 0;
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_TROLLGORE:
                m_auiEncounter[0] = uiData;
                break;
            case TYPE_NOVOS:
                m_auiEncounter[1] = uiData;
                break;
            case TYPE_DREK:
                m_auiEncounter[2] = uiData;
                break;
            case TYPE_THARONJA:
                m_auiEncounter[3] = uiData;
                break;
            case TYPE_CRYSTAL_EVENT:
                if (uiData == NOT_STARTED)
                {
                    CrystalCounter = 0;
                    for (uint8 i = 0; i < CRYSTAL_NUMBER; ++i)
                    {
                        if (GameObject* pGo = instance->GetGameObject(m_uiRitualCrystalGUID[i]))
                        {
                            pGo->SetGoState(GO_STATE_ACTIVE);
                            if (Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_CRYSTAL_CHANNEL_TARGET, INTERACTION_DISTANCE))
                                pCreature->InterruptNonMeleeSpells(false);
                        }
                    }
                }
                if (uiData == IN_PROGRESS)
                {
                    for (uint8 i = 0; i < CRYSTAL_NUMBER; ++i)
                    {
                        if (GameObject* pGo = instance->GetGameObject(m_uiRitualCrystalGUID[i]))
                            if (Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_CRYSTAL_CHANNEL_TARGET, INTERACTION_DISTANCE))
                                pCreature->CastSpell(pCreature, SPELL_BEAM_CHANNELING, false);
                    }
                }
                if (uiData == SPECIAL)
                {
                    ++ CrystalCounter;
                    for (uint8 i = 0; i < CRYSTAL_NUMBER; ++i)
                    {
                        GameObject* pGo = instance->GetGameObject(m_uiRitualCrystalGUID[i]);
                        if (pGo && pGo->GetGoState() == GO_STATE_ACTIVE)
                        {
                            pGo->SetGoState(GO_STATE_READY);
                            if (Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_CRYSTAL_CHANNEL_TARGET, INTERACTION_DISTANCE))
                                pCreature->InterruptNonMeleeSpells(false);
                            break;
                        }
                    }
                }
                if (CrystalCounter >= CRYSTAL_NUMBER)
                    uiData = DONE;
                m_auiEncounter[4] = uiData;
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

    const char* Save()
    {
        return strInstData.c_str();
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        std::istringstream loadStream(in);
        loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_draktharon_keep(Map* pMap)
{
    return new instance_draktharon_keep(pMap);
}

void AddSC_instance_draktharon_keep()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_draktharon_keep";
    newscript->GetInstanceData = GetInstanceData_instance_draktharon_keep;
    newscript->RegisterSelf();
}
