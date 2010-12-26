/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_OBSIDIAN_SANCTUM_H
#define DEF_OBSIDIAN_SANCTUM_H

enum
{
    MAX_ENCOUNTER               = 7,

    TYPE_SARTHARION_EVENT       = 1,

    // Hard Modes for loot conditions
    TYPE_SARTH_HARD_ONE         = 2,
    TYPE_SARTH_HARD_TWO         = 3,
    TYPE_SARTH_HARD_THREE       = 4,

    // solo fights
    TYPE_TENEBRON               = 5,
    TYPE_SHADRON                = 6,
    TYPE_VESPERON               = 7,

    DATA_SARTHARION             = 10,
    DATA_TENEBRON               = 11,
    DATA_SHADRON                = 12,
    DATA_VESPERON               = 13,

    DATA_ACOL_SHAD              = 14,
    DATA_ACOL_VESP              = 15,

    NPC_SARTHARION              = 28860,
    NPC_TENEBRON                = 30452,
    NPC_SHADRON                 = 30451,
    NPC_VESPERON                = 30449,

    // trash mobs
    NPC_ONYX_BROOD_GENERAL      = 30680,
    NPC_ONYX_BLAZE_MISTRESS     = 30681,
    NPC_ONYX_FLIGHT_CAPTAIN     = 30682,
    NPC_ONYX_SANCTUM_GUARDIAN   = 30453,

    GO_TWILIGHT_PORTAL          = 193988,

    // achievements
    ACHIEV_CRIT_VOLCANO_10      = 2047,
    ACHIEV_CRIT_VOLCANO_25      = 2048,
    ACHIEV_CRIT_ASSIST_10       = 2049,
    ACHIEV_CRIT_ASSIST_25       = 2052,
    ACHIEV_CRIT_DUO_10          = 2050,
    ACHIEV_CRIT_DUO_25          = 2053,
    ACHIEV_CRIT_ZONE_10         = 2051,
    ACHIEV_CRIT_ZONE_25         = 2054,
};

class MANGOS_DLL_DECL instance_obsidian_sanctum : public ScriptedInstance
{
 protected:
    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint64 m_uiSartharionGUID;
    uint64 m_uiTenebronGUID;
    uint64 m_uiShadronGUID;
    uint64 m_uiVesperonGUID;

    void Initialize();
    void OnCreatureCreate(Creature* pCreature);

 public:
    instance_obsidian_sanctum(Map* pMap);

    std::list<uint64> m_lTrashMobsGUIDlist;
    std::list<uint64> m_lEggsGUIDList;
    std::list<uint64> m_lWhelpsGUIDList;
    std::list<uint64> m_lBlazesGUIDList;
    //std::list<uint64> m_lHitByVolcanoGUIDList;
    uint64 m_uiAcolyteShadronGUID;
    uint64 m_uiAcolyteVesperonGUID;

    void SetData(uint32 uiType, uint32 uiData);
    uint32 GetData(uint32 uiType);
    uint64 GetData64(uint32 uiData);
    bool CheckConditionCriteriaMeet(Player const* pSource, uint32 uiMapId, uint32 uiInstanceConditionId);
    //bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);
};

#endif
