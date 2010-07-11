/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_BLOOD_FURNACE_H
#define DEF_BLOOD_FURNACE_H

enum
{
    MAX_ENCOUNTER                   = 4,

    GO_DOOR_FINAL_EXIT              = 181766,
    GO_DOOR_MAKER_FRONT             = 181811,
    GO_DOOR_MAKER_REAR              = 181812,
    GO_DOOR_BROGGOK_FRONT           = 181822,
    GO_DOOR_BROGGOK_REAR            = 181819,
    GO_DOOR_KELIDAN_EXIT            = 181823,

    // room before Broggok chamber
    GO_FELORC_CELL_DOOR_1           = 181817,   // front left
    GO_FELORC_CELL_DOOR_2           = 181818,   // front right
    GO_FELORC_CELL_DOOR_3           = 181820,   // back left
    GO_FELORC_CELL_DOOR_4           = 181821,   // back right

    NPC_MAKER                       = 17381,
    NPC_BROGGOK                     = 17380,
    NPC_FELL_ORC                    = 17398,
    NPC_KELIDAN                     = 17377,

    DATA_THE_MAKER                  = 1,
    DATA_BROGGOK                    = 2,
    DATA_KELIDAN_THE_MAKER          = 3,

    TYPE_THE_MAKER_EVENT            = 4,
    TYPE_BROGGOK_EVENT              = 5,
    TYPE_KELIDAN_EVENT              = 6,
    TYPE_BROGGOK_INTRO_EVENT        = 7,

    DATA_PRISON_CELL_MAKER1         = 10,
    DATA_PRISON_CELL_MAKER2         = 11,
    DATA_PRISON_CELL_MAKER3         = 12,
    DATA_PRISON_CELL_MAKER4         = 13,
    DATA_BROGGOK_TARGET             = 14
};

class MANGOS_DLL_DECL instance_blood_furnace : public ScriptedInstance
{
        public:
        instance_blood_furnace(Map* pMap);
        ~instance_blood_furnace() {}

        void Initialize();

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        void SetData64(uint32 uiType, uint32 uiData);

        uint32 GetData(uint32 uiData);
        uint64 GetData64(uint32 uiData);

        const char* Save() { return strInstData.c_str(); }
        void Load(const char* chrIn);

    protected:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string strInstData;

        uint8 m_uiOpenedCell;
        uint8 m_uiAlivePrisoners;

        uint64 m_uiMakerGUID;
        uint64 m_uiBroggokGUID;
        uint64 m_uiKelidanGUID;

        uint64 m_uiDoorFinalExitGUID;
        uint64 m_uiDoorMakerFrontGUID;
        uint64 m_uiDoorMakerRearGUID;
        uint64 m_uiDoorBroggokFrontGUID;
        uint64 m_uiDoorBrokkokRearGUID;
        uint64 m_uiDoorKelidanExitGUID;
        uint64 m_uiBroggokTargetGUID;

        uint64 m_uiPrisonCell1GUID;
        uint64 m_uiPrisonCell2GUID;
        uint64 m_uiPrisonCell3GUID;
        uint64 m_uiPrisonCell4GUID;

        uint64 m_uiBoggokPrisonCell[4];
        std::list<uint64> lFelOrcs;
};

#endif
