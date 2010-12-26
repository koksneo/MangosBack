/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum
{
    MAX_ENCOUNTER               = 14,
    HARD_MODE_ENCOUNTER         = 9,
    KEEPER_ENCOUNTER            = 4,
    TELEPORTER_ENCOUNTER        = 3,

    // boss types
    TYPE_LEVIATHAN              = 0,
    TYPE_IGNIS                  = 1,
    TYPE_RAZORSCALE             = 2,
    TYPE_XT002                  = 3,
    TYPE_ASSEMBLY               = 4,
    TYPE_KOLOGARN               = 5,
    TYPE_AURIAYA                = 6,
    TYPE_MIMIRON                = 7,
    TYPE_HODIR                  = 8,
    TYPE_THORIM                 = 9,
    TYPE_FREYA                  = 10,
    TYPE_VEZAX                  = 11,
    TYPE_YOGGSARON              = 12,
    TYPE_ALGALON                = 13,

    // hard mode bosses
    TYPE_LEVIATHAN_HARD         = 37,
    TYPE_XT002_HARD             = 38,
    TYPE_ASSEMBLY_HARD          = 39,
    TYPE_MIMIRON_HARD           = 40,
    TYPE_HODIR_HARD             = 41,
    TYPE_THORIM_HARD            = 42,
    TYPE_FREYA_HARD             = 43,
    TYPE_VEZAX_HARD             = 44,
    TYPE_YOGGSARON_HARD         = 45,

    // keepers help at Yogg
    TYPE_KEEPER_HODIR           = 46,
    TYPE_KEEPER_FREYA           = 47,
    TYPE_KEEPER_THORIM          = 48,
    TYPE_KEEPER_MIMIRON         = 49,

    // teleporters
    TYPE_LEVIATHAN_TP           = 50,
    TYPE_XT002_TP               = 51,
    TYPE_MIMIRON_TP             = 52,

    //other-> these won't be saved to db
    TYPE_RUNE_GIANT             = 14,
    TYPE_RUNIC_COLOSSUS         = 15,
    TYPE_LEVIATHAN_MK           = 16,
    TYPE_VX001                  = 17,
    TYPE_AERIAL_UNIT            = 18,
    TYPE_YOGG_BRAIN             = 22,
    TYPE_MIMIRON_PHASE          = 23,
    TYPE_YOGG_PHASE             = 24,
    TYPE_VISION_PHASE           = 25,

    // siege
    NPC_LEVIATHAN               = 33113,
    NPC_IGNIS                   = 33118,
    NPC_IRON_CONSTRUCT          = 33121,
    NPC_RAZORSCALE              = 33186,
    NPC_COMMANDER               = 33210,
    NPC_XT002                   = 33293,
    // antechamber
    NPC_STEELBREAKER            = 32867,
    NPC_MOLGEIM                 = 32927,
    NPC_BRUNDIR                 = 32857,
    NPC_KOLOGARN                = 32930,
    NPC_RIGHT_ARM               = 32934,
    NPC_LEFT_ARM                = 32933,
    NPC_AURIAYA                 = 33515,
    NPC_SANCTUM_SENTRY          = 34014,
    NPC_FERAL_DEFENDER          = 34035,
    // keepers
    NPC_MIMIRON                 = 33350,
    NPC_LEVIATHAN_MK            = 33432,
    NPC_VX001                   = 33651,
    NPC_AERIAL_UNIT             = 33670,
    NPC_HODIR                   = 32845,
    NPC_THORIM                  = 32865,
    NPC_RUNIC_COLOSSUS          = 32872,
    NPC_RUNE_GIANT              = 32873,
    NPC_JORMUNGAR_BEHEMOTH      = 32882,
    NPC_FREYA                   = 32906,
    NPC_BRIGHTLEAF              = 32915,
    NPC_IRONBRACH               = 32913,
    NPC_STONEBARK               = 32914,
    // madness
    NPC_VEZAX                   = 33271,
    NPC_ANIMUS                  = 33524,
    NPC_YOGGSARON               = 33288,
    NPC_ALGALON                 = 32871,
    NPC_SARA                    = 33134,
    NPC_YOGG_BRAIN              = 33890, 
    // keepers images used to start the encounter
    THORIM_IMAGE                = 33413,
    MIMIRON_IMAGE               = 33412,
    HODIR_IMAGE                 = 33411,
    FREYA_IMAGE                 = 33410,
    // Keepers used at yogg saron encounter
    KEEPER_FREYA                = 33241,
    KEEPER_HODIR                = 33213,
    KEEPER_MIMIRON              = 33244,
    KEEPER_THORIM               = 33242, 

    // loot chests
    // Kologarn
    GO_CACHE_OF_LIVING_STONE    = 195046,
    GO_CACHE_OF_LIVING_STONE_H	= 195047,
    // Hodir
    GO_CACHE_OF_WINTER          = 194307,
    GO_CACHE_OF_WINTER_H        = 194308,
    GO_CACHE_OF_RARE_WINTER     = 194200,
    GO_CACHE_OF_RARE_WINTER_H   = 194201,
    // Thorim
    GO_CACHE_OF_STORMS          = 194312,
    GO_CACHE_OF_RARE_STORMS     = 194313,
    GO_CACHE_OF_STORMS_H        = 194314,
    GO_CACHE_OF_RARE_STORMS_H   = 194315,
    // Alagon
    GO_GIFT_OF_OBSERVER_H       = 194821,
    GO_GIFT_OF_OBSERVER         = 194822,
    GO_GIFT_OF_OBSERVER_HH      = 194823,   // unk
    // Freya -> each chest is for a mode = more elders alive = more items in chest
    // 10 man
    GO_FREYA_GIFT               = 194324,//10 normal
    GO_FREYA_GIFT_1             = 194325,//10 1 elder
    GO_FREYA_GIFT_2             = 194326,//10 2 elders
    GO_FREYA_GIFT_3             = 194327,//10 3 elders
    // 25 man
    GO_FREYA_GIFT_H             = 194328,//25 normal
    GO_FREYA_GIFT_H_1           = 194329,//25 1 elder
    GO_FREYA_GIFT_H_2           = 194330,//25 2 elder
    GO_FREYA_GIFT_H_3           = 194331,//25 3 elders
    // Mimiron
    GO_CACHE_OF_INOV            = 194789,
    GO_CACHE_OF_INOV_H          = 194956,
    GO_CACHE_OF_INOV_HARD       = 194957,
    GO_CACHE_OF_INOV_HARD_H     = 194958,

    // doors
    // the siege
    GO_SHIELD_WALL              = 194416,
    GO_LEVIATHAN_GATE           = 194630,
    GO_XT002_GATE               = 194631,
    GO_BROKEN_HARPOON           = 194565,
    // archivum
    GO_KOLOGARN_BRIDGE          = 194232,
    GO_SHATTERED_DOOR           = 194553,
    GO_IRON_ENTRANCE_DOOR       = 194554,
    GO_ARCHIVUM_DOOR            = 194556,
    GO_ARCHIVUM_CONSOLE         = 194555,
    // planetarium: algalon
    GO_CELESTIAL_ACCES          = 194628,
    GO_CELESTIAL_ACCES_H        = 194752,
    GO_CELESTIAL_DOOR           = 194767,
    GO_UNIVERSE_FLOOR_ARCHIVUM  = 194715,
    GO_UNIVERSE_FLOOR_CELESTIAL = 194716,
    GO_AZEROTH_GLOBE            = 194148,
    // the keepers
    // hodir
    GO_HODIR_EXIT               = 194634,
    GO_HODIR_ICE_WALL           = 194441,
    GO_HODIR_ENTER              = 194442,
    // mimiron
    GO_MIMIRON_TRAM             = 194675,
    GO_MIMIRON_BUTTON           = 194739,
    GO_MIMIRON_DOOR_1           = 194774,
    GO_MIMIRON_DOOR_2           = 194775,
    GO_MIMIRON_DOOR_3           = 194776,
    GO_MIMIRON_TEL1             = 194741,
    GO_MIMIRON_TEL2             = 194742,
    GO_MIMIRON_TEL3             = 194743,
    GO_MIMIRON_TEL4             = 194744,
    GO_MIMIRON_TEL5             = 194740,
    GO_MIMIRON_TEL6             = 194746,
    GO_MIMIRON_TEL7             = 194747,
    GO_MIMIRON_TEL8             = 194748,
    GO_MIMIRON_TEL9             = 194745,
    GO_MIMIRON_ELEVATOR         = 194749,
    // Thorim
    GO_DARK_IRON_PORTCULIS      = 194560,
    GO_RUNED_STONE_DOOR         = 194557,
    GO_THORIM_STONE_DOOR        = 194558,
    GO_LIGHTNING_DOOR           = 194905,
    GO_LIGHTNING_FIELD          = 194559,
    GO_DOOR_LEVER               = 194264,
    //Yogg
    GO_ANCIENT_GATE             = 194255,
    GO_VEZAX_GATE               = 194750,
    GO_YOGG_GATE                = 194773,
    GO_BRAIN_DOOR1              = 194635,
    GO_BRAIN_DOOR2              = 194636,
    GO_BRAIN_DOOR3              = 194637,

    ACHIEV_IRON_COUNCIL         = 2888,
    ACHIEV_IRON_COUNCIL_H       = 2889,

    ACHIEV_KEEPERS              = 2890,
    ACHIEV_KEEPERS_H            = 2891,

    ACHIEV_CELESTIAL_DEFENDER   = 3259,     // realm first algalon
    SPELL_ALGALON_ACHIEV_TRIGG  = 65184,
    ACHIEV_DEATHS_DEMISE        = 3117,     // realm first yogg

    // World state used for algalon timer
    WORLD_STATE_TIMER           = 4132,
    WORLD_STATE_TIMER_COUNT     = 4131,
};

class MANGOS_DLL_DECL instance_ulduar : public ScriptedInstance
{
    public:
        instance_ulduar(Map* pMap);
        ~instance_ulduar() {}

        void Initialize();
        bool IsEncounterInProgress() const;

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);
        uint64 GetData64(uint32 uiData);

        const char* Save();
        void Load(const char* chrIn);

        // Dummy, leave till correct solution for hardmode found
        bool CheckConditionCriteriaMeet(Player const* pSource, uint32 uiMapId, uint32 uiInstanceConditionId);
        bool CheckAchievementCriteriaMeet(uint32 criteria_id, const Player *source);

        void OpenDoor(uint64 guid);
        void CloseDoor(uint64 guid);
        void DoOpenMadnessDoorIfCan();
        void OpenXtDoor();
        void CheckIronCouncil();
        void CheckKeepers();
        Player* GetPlayerInMap();
        void SpawnFriendlyKeeper(uint32 uiWho);

        std::list<uint64> m_lIronConstructsGUIDs;

    protected:
        
	// initialize the encouter variables
    std::string m_strInstData;
    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint32 m_auiHardBoss[HARD_MODE_ENCOUNTER];
    uint32 m_auiUlduarKeepers[KEEPER_ENCOUNTER];
    uint32 m_auiUlduarTeleporters[3];
    uint32 m_auiMiniBoss[6];

	// boss phases which need to be used inside the instance script
    uint32 m_uiMimironPhase;
    uint32 m_uiYoggPhase;
    uint32 m_uiVisionPhase;

	// creature guids
    uint64 m_uiLeviathanGUID;
    uint64 m_uiIgnisGUID;
    uint64 m_uiRazorscaleGUID;
    uint64 m_uiCommanderGUID;
    uint64 m_uiXT002GUID;
    uint64 m_auiAssemblyGUIDs[3];
    uint64 m_uiKologarnGUID;
    uint64 m_uiAuriayaGUID;
    uint64 m_uiMimironGUID;
    uint64 m_uiHodirGUID;
    uint64 m_uiThorimGUID;
    uint64 m_uiFreyaGUID;
    uint64 m_uiVezaxGUID;
    uint64 m_uiYoggSaronGUID;
    uint64 m_uiAlgalonGUID;
    uint64 m_uiRightArmGUID;
    uint64 m_uiLeftArmGUID;
    uint64 m_uiFeralDefenderGUID;
    uint64 m_uiElderBrightleafGUID;
    uint64 m_uiElderStonebarkGUID;
    uint64 m_uiElderIronbrachGUID;
    uint64 m_uiSaroniteAnimusGUID;
    uint64 m_uiRunicColossusGUID;
    uint64 m_uiRuneGiantGUID;
    uint64 m_uiJormungarGUID;
    uint64 m_uiLeviathanMkGUID;
    uint64 m_uiHodirImageGUID;
    uint64 m_uiFreyaImageGUID;
    uint64 m_uiThorimImageGUID;
    uint64 m_uiMimironImageGUID;
    uint64 m_uiSaraGUID;
    uint64 m_uiYoggBrainGUID;

    //doors & objects
    // The siege
    uint64 m_uiShieldWallGUID;
    uint64 m_uiLeviathanGateGUID;
    uint64 m_uiXT002GateGUID;
    uint64 m_uiBrokenHarpoonGUID;
    // Archivum
    uint64 m_uiIronCouncilDoorGUID;
    uint64 m_uiArchivumDoorGUID;
    uint64 m_uiArchivumConsoleGUID;
    uint64 m_uiUniverseFloorArchivumGUID;
    // Celestial planetarium
    uint64 m_uiCelestialDoorGUID;
    uint64 m_uiCelestialConsoleGUID;
    uint64 m_uiUniverseFloorCelestialGUID;
    uint64 m_uiAzerothGlobeGUID;
    // Kologarn
    uint64 m_uiShatteredHallsDoorGUID;
    uint64 m_uiKologarnBridgeGUID;
    // Hodir
    uint64 m_uiHodirEnterDoorGUID;
    uint64 m_uiHodirWallGUID;
    uint64 m_uiHodirExitDoorGUID;
    // Mimiron
    uint64 m_uiMimironTramGUID;
    uint64 m_uiMimironButtonGUID;
    uint64 m_uiMimironDoor1GUID;
    uint64 m_uiMimironDoor2GUID;
    uint64 m_uiMimironDoor3GUID;
    uint64 m_uiMimironElevatorGUID;
    uint64 m_uiMimironTelGUID[9];
    // Thorim
    uint64 m_uiArenaEnterDoorGUID;
    uint64 m_uiArenaExitDoorGUID;
    uint64 m_uiHallwayDoorGUID;
    uint64 m_uiThorimEnterDoorGUID;
    uint64 m_uiThorimLeverGUID;
    // Prison
    uint64 m_uiAncientGateGUID;
    uint64 m_uiVezaxGateGUID;
    uint64 m_uiYoggGateGUID;
    uint64 m_uiBrainDoor1GUID;
    uint64 m_uiBrainDoor2GUID;
    uint64 m_uiBrainDoor3GUID;

    // chests
    uint64 m_uiKologarnLootGUID;
    uint64 m_uiHodirLootGUID;
    uint64 m_uiHodirRareLootGUID;
    uint64 m_uiThorimLootGUID;
    uint64 m_uiThorimRareLootGUID;
    uint64 m_uiFreyaLootGUID;
    uint64 m_uiFreyaLoot1GUID;
    uint64 m_uiFreyaLoot2GUID;
    uint64 m_uiFreyaLoot3GUID;
    uint64 m_uiMimironLootGUID;
    uint64 m_uiMimironHardLootGUID;
    uint64 m_uiAlagonLootGUID;

};

#endif
