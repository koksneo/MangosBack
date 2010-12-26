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
SDName: Borean_Tundra
SD%Complete: 100
SDComment: Quest support: 11708, 11692, 11961, 11876, 11590, 11676, 11940, 11919. Taxi vendors. 11570
SDCategory: Borean Tundra
EndScriptData */

/* ContentData
mob_elder
npc_fizzcrank_fullthrottle
npc_iruk
npc_kara_thricestar
mob_overseer
npc_surristrasz
npc_tiare
npc_lurgglbr
go_mammoth_trap
npc_beryl_sorcerer
go_scourge_cage
npc_nexus_drake
npc_nesingwary_trapper
go_caribou_trap
EndContentData */

#include "precompiled.h"
#include "ObjectMgr.h"
#include "escort_ai.h"
#include "follower_ai.h"

/*######
## mob_elder
######*/
enum
{
    SPELL_ANCESTOR_RITUAL               = 45536,
    SPELL_GREEN_BEAM                    = 39165,

    NPC_ELDER_KESUK                     = 25397,
    NPC_ELDER_SAGANI                    = 25398,
    NPC_ELDER_TAKRET                    = 25399,
    
    GO_ELDER_KESUK                      = 191088,
    GO_ELDER_SAGANI                     = 191089,
    GO_ELDER_TAKRET                     = 191090,

    POINT_ID                            = 1
};

struct MANGOS_DLL_DECL mob_elderAI : public ScriptedAI
{
    mob_elderAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bEventInProgress;
    uint64 uiPlayerGUID;
    uint32 m_uiResetTimer;

    void Reset()
    {
        uiPlayerGUID = 0;
        m_uiResetTimer = 10000;

        m_creature->InterruptSpell(CURRENT_CHANNELED_SPELL,false);
        m_creature->RemoveAllAuras();
        m_creature->SetDisplayId(m_creature->GetNativeDisplayId());
        m_creature->GetMotionMaster()->MoveTargetedHome();

        bEventInProgress = false;
    }

    void SpellHit(Unit* pCaster, SpellEntry const* pSpell)
    {
        if (!pCaster || bEventInProgress)
            return;

        if (pCaster->GetTypeId() == TYPEID_PLAYER && pSpell->Id == SPELL_ANCESTOR_RITUAL)
        {
            bEventInProgress = true;
            uiPlayerGUID = pCaster->GetGUID();
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->StopMoving();

            uint32 go_entry;
            switch (m_creature->GetEntry())
            {
                case NPC_ELDER_SAGANI:  go_entry = GO_ELDER_SAGANI; break;
                case NPC_ELDER_KESUK:   go_entry = GO_ELDER_KESUK; break;
                case NPC_ELDER_TAKRET:  go_entry = GO_ELDER_TAKRET; break;
                default: break;
            }
            
            float x,y,z;
            if (GameObject* pGo = GetClosestGameObjectWithEntry(pCaster, go_entry, DEFAULT_VISIBILITY_DISTANCE))
                pGo->GetNearPoint(pGo,x,y,z,2.0f,2.0f,pGo->GetOrientation());
            else 
            {
                error_log("SD2: mob_elder (%s entry %u) couldn't find gameobject entry %u. Please check your database",m_creature->GetName(),m_creature->GetEntry(),go_entry);
                Reset();
            }

            m_creature->GetMotionMaster()->MovePoint(POINT_ID,x,y,z);
        }
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE)
            return;

        Player* pPlayer = m_creature->GetMap()->GetPlayer(uiPlayerGUID);

        if (!pPlayer)
            return;

        if (id == POINT_ID)
        {
            DoCast(m_creature,SPELL_GREEN_BEAM,false);
            // Because spell focus is m_creature not static gameobject or something we have to check if player actualy is near m_creature
            if (pPlayer->GetDistance(m_creature) < 5.0f)
                pPlayer->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetGUID()); 
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->HasAura(SPELL_GREEN_BEAM))
        {
            if (m_uiResetTimer <= uiDiff)
                Reset();
            else m_uiResetTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_elder(Creature* pCreature)
{
    return new mob_elderAI(pCreature);
}


/*######
## npc_fizzcrank_fullthrottle
######*/

#define GOSSIP_ITEM_GO_ON   "Go on."
#define GOSSIP_ITEM_TELL_ME "Tell me what's going on out here, Fizzcrank."

enum
{
    GOSSIP_TEXTID_FIZZCRANK1    = 12456,
    GOSSIP_TEXTID_FIZZCRANK2    = 12457,
    GOSSIP_TEXTID_FIZZCRANK3    = 12458,
    GOSSIP_TEXTID_FIZZCRANK4    = 12459,
    GOSSIP_TEXTID_FIZZCRANK5    = 12460,
    GOSSIP_TEXTID_FIZZCRANK6    = 12461,
    GOSSIP_TEXTID_FIZZCRANK7    = 12462,
    GOSSIP_TEXTID_FIZZCRANK8    = 12463,
    GOSSIP_TEXTID_FIZZCRANK9    = 12464,

    QUEST_THE_MECHAGNOMES       = 11708
};

bool GossipHello_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_MECHAGNOMES) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELL_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK7, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK8, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK9, pCreature->GetGUID());
            pPlayer->AreaExploredOrEventHappens(QUEST_THE_MECHAGNOMES);
            break;
    }
    return true;
}

/*######
## npc_iruk
######*/

#define GOSSIP_ITEM_IRUK        "<Search corpse for Issliruk's Totem.>"

enum
{
    QUEST_SPIRITS_WATCH_OVER_US     = 11961,
    SPELL_CREATE_TOTEM              = 46816
};

bool GossipHello_npc_iruk(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SPIRITS_WATCH_OVER_US) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_IRUK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_iruk(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,SPELL_CREATE_TOTEM,true);
    }

    return true;
}

/*######
## npc_kara_thricestar
######*/

#define GOSSIP_ITEM_THRICESTAR1      "Do you think I could take a ride on one of those flying machines?"
#define GOSSIP_ITEM_THRICESTAR2      "Kara, I need to be flown out the Dens of Dying to find Bixie."

enum
{
    QUEST_CHECK_IN_WITH_BIXIE       = 11692,
    SPELL_FIZZCRANK_AIRSTRIP        = 51446
};

bool GossipHello_npc_kara_thricestar(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isTaxi())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_THRICESTAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    if (pPlayer->GetQuestStatus(QUEST_CHECK_IN_WITH_BIXIE) == QUEST_STATUS_COMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THRICESTAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_kara_thricestar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->GetSession()->SendTaxiMenu(pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer, SPELL_FIZZCRANK_AIRSTRIP, false);
            break;
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


/*######
## npc_surristrasz
######*/

#define GOSSIP_ITEM_FREE_FLIGHT "I'd like passage to the Transitus Shield."
#define GOSSIP_ITEM_FLIGHT      "May I use a drake to fly elsewhere?"

enum
{
    SPELL_ABMER_TO_COLDARRA     = 46064
};

bool GossipHello_npc_surristrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isTaxi())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FREE_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_TAXIVENDOR);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_surristrasz(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        //TaxiPath 795 (amber to coldarra)
        pPlayer->CastSpell(pPlayer, SPELL_ABMER_TO_COLDARRA, true);
    }

    if (uiAction == GOSSIP_OPTION_TAXIVENDOR)
        pPlayer->GetSession()->SendTaxiMenu(pCreature);

    return true;
}

/*######
## npc_tiare
######*/

#define GOSSIP_ITEM_TELEPORT    "Teleport me to Amber Ledge, please."

enum
{
    SPELL_TELEPORT_COLDARRA     = 50135
};

bool GossipHello_npc_tiare(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tiare(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_TELEPORT_COLDARRA, true);
    }
    return true;
}

// Oh Noes, the Tadpoles! 
// HACKED!
enum Tadpole_Cage
{
    MOB_WINTERFIN_TADPOLE       = 25201,
    GO_TADPOLE_CAGE             = 187373,
    QUEST_OH_NOES_THE_TADPOLES  = 11560
};

int32 Speaches[7] =
{ 
    -1999806,-1999805,-1999804,           // negative
    -1999810,-1999809,-1999808,-1999807   // positive
};

struct MANGOS_DLL_DECL mob_tadpoleAI : public ScriptedAI
{
    mob_tadpoleAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool bIsFollowing;
    bool bIsResetingCage;
    uint32 Timer;

    void Reset() 
    {
        if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature,GO_TADPOLE_CAGE,2.0f))
        {
            pGo->SetGoState(GO_STATE_READY);
            pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        }

        bIsFollowing = false;
        bIsResetingCage = false;
        Timer = urand(15000, 30000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bIsFollowing || bIsResetingCage)
            if (Timer <= uiDiff)
            {
                if (bIsFollowing)
                {
                    DoScriptText(Speaches[urand(5, 6)],m_creature);
                    Timer = urand(28000,59000);
                }
                // if player is not eligeble for tadpole to follow lets reset him and his cage
                else if (bIsResetingCage)    
                    Reset();
            }else Timer -= uiDiff;
   }
};

CreatureAI* GetAI_mob_tadpole(Creature* pCreature)
{
    return new mob_tadpoleAI(pCreature);
}

bool GOHello_go_tadpole_cage(Player* pPlayer, GameObject* pGo)
{
    if (!pPlayer)
        return false;


    std::list<Creature*> lCreatureList;
    GetCreatureListWithEntryInGrid(lCreatureList, pGo, MOB_WINTERFIN_TADPOLE, 2.0f);

    if (!lCreatureList.empty())
    {
        for (std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
        {
            if ((*itr) && (*itr)->isAlive())
            {
                if (pPlayer->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) != QUEST_STATUS_INCOMPLETE)
                {
                    //choose one of negative speaches
                    DoScriptText(Speaches[urand(0, 2)],(*itr),pPlayer);
                    ((mob_tadpoleAI*)(*itr)->AI())->bIsResetingCage = true;
                    continue;
                }

                else if (Creature* pNewTadpole = (*itr)->SummonCreature(MOB_WINTERFIN_TADPOLE,(*itr)->GetPositionX(),(*itr)->GetPositionY(),(*itr)->GetPositionZ(),(*itr)->GetOrientation(),TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,urand(60000,120000)))
                {
                    pNewTadpole->GetMotionMaster()->MoveFollow(pPlayer, float(urand(1, 4)), 2*M_PI/float(urand(1, 20)));
                    pPlayer->KilledMonsterCredit((*itr)->GetEntry(),(*itr)->GetGUID());
                    (*itr)->ForcedDespawn();
                    if (pPlayer->getGender() == GENDER_MALE)
                        DoScriptText(Speaches[3],pNewTadpole,pPlayer);
                    else DoScriptText(Speaches[4],pNewTadpole,pPlayer);
                    ((mob_tadpoleAI*)pNewTadpole->AI())->bIsFollowing = true;
                }
            }
        }
    }

    lCreatureList.clear();
    // just open the door without despawn
    pGo->SetGoState(GO_STATE_ACTIVE);
    // and make cage not targetable
    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
    return true;
}

enum PrisonBreak
{
    QUEST_PRISON_BREAK          = 11587,
    SPELL_HEARTSTONE_VISUAL     = 45451,
    SPELL_PRISON_BREAK_CREDIT   = 45456,

    SAY_SUCCEDED                = -1999803,
    SAY_FAILED                  = -1999802
};

struct MANGOS_DLL_DECL mob_arcane_prisonerAI : public ScriptedAI
{
    mob_arcane_prisonerAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}
    
    bool bEventDone;
    uint32 m_uiEventTimer;

    void Reset() 
    {
        // small amount of time is needed to let npc fall on the ground
        m_uiEventTimer = 1000;
        bEventDone = false;
    }

    void UpdateAI (const uint32 uiDiff)
    {
        if (!bEventDone && m_uiEventTimer <= uiDiff)
        {
            bEventDone = true;
            // update server with position of NPC after it fall on the ground
            // this will prevent to spawn eventual corpse in the air (cosmetic effect)
            float x,y,z;
            m_creature->GetPosition(x, y, z);
            z = m_creature->GetMap()->GetTerrain()->GetHeight(x, y, MAX_HEIGHT, false);
            m_creature->Relocate(x, y, z+2);

            if (urand(0, 2) < 2)
            {
                DoScriptText(SAY_FAILED, m_creature, NULL);
                m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
            else
            {
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_creature->GetCreatorGuid()))
                {
                    DoScriptText(SAY_SUCCEDED, m_creature, pPlayer);
                    if (pPlayer->GetQuestStatus(QUEST_PRISON_BREAK) == QUEST_STATUS_INCOMPLETE)
                        DoCastSpellIfCan(pPlayer, SPELL_PRISON_BREAK_CREDIT, CAST_TRIGGERED);
                }
                DoCastSpellIfCan(m_creature, SPELL_HEARTSTONE_VISUAL);
            }
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_arcane_prisoner(Creature* pCreature)
{
    return new mob_arcane_prisonerAI(pCreature);
}

/*######
## npc_lurgglbr
######*/

enum
{
    QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS = 11570,
    GO_CAGE                             = 187369,

    SAY_START_1                         = -1000575,
    SAY_START_2                         = -1000576,
    SAY_END_1                           = -1000577,
    SAY_END_2                           = -1000578
};

struct MANGOS_DLL_DECL npc_lurgglbrAI : public npc_escortAI
{
    npc_lurgglbrAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiSayTimer = 0;
        m_uiSpeech = 0;
        Reset();
    }

    uint32 m_uiSayTimer;
    uint8 m_uiSpeech;

    void Reset()
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            m_uiSayTimer = 0;
            m_uiSpeech = 0;
        }
    }

    void JustStartedEscort()
    {
        if (GameObject* pCage = GetClosestGameObjectWithEntry(m_creature, GO_CAGE, INTERACTION_DISTANCE))
        {
            if (pCage->GetGoState() == GO_STATE_READY)
                pCage->Use(m_creature);
        }
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 1:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_START_2, m_creature, pPlayer);

                // Cage actually closes here, however it's normally determined by GO template and auto close time

                break;
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_creature->SetFacingToObject(pPlayer);
                    DoScriptText(SAY_START_1, m_creature, pPlayer);
                }
                break;
            case 25:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    DoScriptText(SAY_END_1, m_creature, pPlayer);
                    m_uiSayTimer = 3000;
                }
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiSayTimer)
            {
                if (m_uiSayTimer <= uiDiff)
                {
                    Player* pPlayer = GetPlayerForEscort();

                    if (!pPlayer)
                    {
                        m_uiSayTimer = 0;
                        return;
                    }

                    m_creature->SetFacingToObject(pPlayer);

                    switch(m_uiSpeech)
                    {
                        case 0:
                            DoScriptText(SAY_END_2, m_creature, pPlayer);
                            m_uiSayTimer = 3000;
                            break;
                        case 1:
                            pPlayer->GroupEventHappens(QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS, m_creature);
                            m_uiSayTimer = 0;
                            break;
                    }

                    ++m_uiSpeech;
                }
                else
                    m_uiSayTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_lurgglbr(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS)
    {
        if (npc_lurgglbrAI* pEscortAI = dynamic_cast<npc_lurgglbrAI*>(pCreature->AI()))
        {
            pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_PASSIVE);
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
        }
    }
    return true;
}

CreatureAI* GetAI_npc_lurgglbr(Creature* pCreature)
{
    return new npc_lurgglbrAI(pCreature);
}

/*#####
## go_mammoth_trap
#####*/

enum
{
    QUEST_HELP_THOSE_THAT    =  11876,
    NPC_TRAPPED_MAMMOTH      =  25850,
    SPELL_DESPAWN_SELF       =  43014
};

bool GOHello_go_mammoth_trap(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_HELP_THOSE_THAT) == QUEST_STATUS_INCOMPLETE)
    {
        Creature *pCreature = GetClosestCreatureWithEntry(pGo, NPC_TRAPPED_MAMMOTH, INTERACTION_DISTANCE);
        if(pCreature)
        {
            pPlayer->KilledMonsterCredit(NPC_TRAPPED_MAMMOTH, pCreature->GetGUID());
            pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

/*######
## npc_beryl_sorcerer
######*/

enum eBerylSorcerer
{
    NPC_CAPTURED_BERLY_SORCERER         = 25474,
    NPC_LIBRARIAN_DONATHAN              = 25262,

    SPELL_ARCANE_CHAINS                 = 45611,
    SPELL_COSMETIC_CHAINS               = 54324,
    SPELL_COSMETIC_ENSLAVE_CHAINS_SELF  = 45631
};

struct MANGOS_DLL_DECL npc_beryl_sorcererAI : public FollowerAI
{
    npc_beryl_sorcererAI(Creature* pCreature) : FollowerAI(pCreature) { 
        Reset(); 
    }

    bool bEnslaved;
    uint64 uiChainerGUID;

    void Reset()
    {
         m_creature->setFaction(14);
         bEnslaved = false;
    }
    void EnterCombat(Unit* pWho)
    {
            AttackStart(pWho);
    }
    
    void SpellHit(Unit* pCaster, SpellEntry const* pSpell)
    {
        if (pSpell->Id == SPELL_ARCANE_CHAINS && pCaster->GetTypeId() == TYPEID_PLAYER && !bEnslaved)
            {
                EnterEvadeMode(); //We make sure that the npc is not attacking the player!
                m_creature->setFaction(35);
                uiChainerGUID = pCaster->GetGUID();
                if(Player *pChainer = m_creature->GetMap()->GetPlayer(uiChainerGUID))
                {
                StartFollow(pChainer, 35, NULL);
                m_creature->UpdateEntry(NPC_CAPTURED_BERLY_SORCERER);
                DoCast(m_creature, SPELL_COSMETIC_ENSLAVE_CHAINS_SELF, true);
               
                bEnslaved = true;
                }
            }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
            FollowerAI::MoveInLineOfSight(pWho);

            if (pWho->GetEntry() == NPC_LIBRARIAN_DONATHAN && m_creature->IsWithinDistInMap(pWho, INTERACTION_DISTANCE))
            {
                if(Player *pChainer = m_creature->GetMap()->GetPlayer(uiChainerGUID))
                {
                    pChainer->KilledMonsterCredit(NPC_CAPTURED_BERLY_SORCERER,m_creature->GetGUID());
                    SetFollowComplete();
                    m_creature->ForcedDespawn(1000);
                }
            }
     }
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->getVictim())
                return;

            DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_beryl_sorcerer(Creature* pCreature)
{
    return new npc_beryl_sorcererAI(pCreature);
}

/*#####
## go_scourge_cage
#####*/

enum
{
    QUEST_MERCIFUL_FREEDOM      =  11676,
    NPC_SCOURGE_PRISONER        =  25610,
};

bool GOHello_go_scourge_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_MERCIFUL_FREEDOM) == QUEST_STATUS_INCOMPLETE)
    {
        Creature *pCreature = GetClosestCreatureWithEntry(pGo, NPC_SCOURGE_PRISONER, INTERACTION_DISTANCE);
        if(pCreature)
        {
            pPlayer->KilledMonsterCredit(NPC_SCOURGE_PRISONER, pCreature->GetGUID());
            pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

/*######
## npc_nexus_drake_hatchling
######*/

enum
{
    SPELL_DRAKE_HARPOON             = 46607,
    SPELL_RED_DRAGONBLOOD           = 46620,
    SPELL_DRAKE_HATCHLING_SUBDUED   = 46691,
    SPELL_SUBDUED                   = 46675,

    NPC_RAELORASZ                   = 26117,
    DRAKE_HUNT_KILL_CREDIT          = 26175,

    QUEST_DRAKE_HUNT                = 11919,
    QUEST_DRAKE_HUNT_D              = 11940

};

struct MANGOS_DLL_DECL npc_nexus_drakeAI : public FollowerAI
{
    npc_nexus_drakeAI(Creature* pCreature) : FollowerAI(pCreature) { Reset(); }
    
     uint64 uiHarpoonerGUID;
     bool bWithRedDragonBlood;
     bool bIsFollowing;

     void Reset()
     {
         bWithRedDragonBlood = false;
         bIsFollowing = false;
     }

     void EnterCombat(Unit* pWho)
     {
         AttackStart(pWho);
     }
     
     void SpellHit(Unit* pCaster, SpellEntry const* pSpell)
     {
            if (pSpell->Id == SPELL_DRAKE_HARPOON && pCaster->GetTypeId() == TYPEID_PLAYER)
            {
                uiHarpoonerGUID = pCaster->GetGUID();
                DoCast(m_creature, SPELL_RED_DRAGONBLOOD, true);
            }
            m_creature->Attack(pCaster,true);
            bWithRedDragonBlood = true;
     }

     void MoveInLineOfSight(Unit *pWho)
     {
         FollowerAI::MoveInLineOfSight(pWho);


         if (pWho->GetEntry() == NPC_RAELORASZ && m_creature->IsWithinDistInMap(pWho, INTERACTION_DISTANCE))
         {
           if (Player *pHarpooner = m_creature->GetMap()->GetPlayer(uiHarpoonerGUID))
                 {
                    
                     pHarpooner->KilledMonsterCredit(DRAKE_HUNT_KILL_CREDIT,m_creature->GetGUID());
                     pHarpooner->RemoveAurasByCasterSpell(SPELL_DRAKE_HATCHLING_SUBDUED,uiHarpoonerGUID);
                     SetFollowComplete();
                     uiHarpoonerGUID = 0;
                     m_creature->ForcedDespawn(1000);
                 }
              
          }
      }
     
     void UpdateAI(const uint32 uidiff)
        {
            if (bWithRedDragonBlood && uiHarpoonerGUID && !m_creature->HasAura(SPELL_RED_DRAGONBLOOD))
            {
                if (Player *pHarpooner = m_creature->GetMap()->GetPlayer(uiHarpoonerGUID))
                {
                    EnterEvadeMode();
                    StartFollow(pHarpooner, 35, NULL);

                    DoCast(m_creature, SPELL_SUBDUED, true);
                    pHarpooner->CastSpell(pHarpooner, SPELL_DRAKE_HATCHLING_SUBDUED, true);

                    m_creature->AttackStop();
                    bIsFollowing = true;
                    bWithRedDragonBlood = false;
                }
            }
            if(bIsFollowing && !m_creature->HasAura(SPELL_SUBDUED))
            {
                m_creature->ForcedDespawn(1000);
            }

            if (!m_creature->getVictim())
                return;

            DoMeleeAttackIfReady();
        }
};

/*######
## npc_nesingwary_trapper
######*/
enum
{
    NPC_NESINGWARY_TRAPPER  = 25835,
    GO_QUALITY_FUR          = 187983,

    SAY_PHRASE_1            = -1000599,
    SAY_PHRASE_2            = -1000600,
    SAY_PHRASE_3            = -1000601,
    SAY_PHRASE_4            = -1000602
};

struct MANGOS_DLL_DECL npc_nesingwary_trapperAI : public ScriptedAI
{
    npc_nesingwary_trapperAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint8 m_uiPhase;
    uint32 m_uiPhaseTimer;
    uint64 m_uiPlayerGUID;
    uint64 m_uiGobjectTrapGUID;

    void Reset()
    {
        m_uiPhase = 0;
        m_uiPhaseTimer = 0;
        m_uiPlayerGUID = 0;
        m_uiGobjectTrapGUID = 0;
    }

    void StartAction(uint64 uiPlayerGUID, uint64 uiGoTrapGUID)
    {
        m_uiPhase = 1;
        m_uiPhaseTimer = 3000;
        m_uiPlayerGUID = uiPlayerGUID;
        m_uiGobjectTrapGUID = uiGoTrapGUID;

        switch (urand(0, 3))
        {
            case 0: DoScriptText(SAY_PHRASE_1, m_creature); break;
            case 1: DoScriptText(SAY_PHRASE_2, m_creature); break;
            case 2: DoScriptText(SAY_PHRASE_3, m_creature); break;
            case 3: DoScriptText(SAY_PHRASE_4, m_creature); break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->getVictim() && m_uiPhase)
        {
            if (m_uiPhaseTimer <= uiDiff)
            {
                switch(m_uiPhase)
                {
                    case 1:
                        if (GameObject* pTrap = m_creature->GetMap()->GetGameObject(m_uiGobjectTrapGUID))
                        {
                            if (pTrap->isSpawned())
                                m_creature->GetMotionMaster()->MovePoint(0, pTrap->GetPositionX(), pTrap->GetPositionY(), pTrap->GetPositionZ());
                        }
                        break;
                    case 2:
                        if (GameObject* pTrap = m_creature->GetMap()->GetGameObject(m_uiGobjectTrapGUID))
                        {
                            if (pTrap->isSpawned())
                            {
                                pTrap->Use(m_creature);

                                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                                {
                                    if (pPlayer->isAlive())
                                        pPlayer->KilledMonsterCredit(m_creature->GetEntry());
                                }
                            }
                        }
                        break;
                }

                m_uiPhase = 0;
            }
            else
                m_uiPhaseTimer -= uiDiff;
        }
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        m_creature->HandleEmote(EMOTE_ONESHOT_LOOT);
        m_uiPhaseTimer = 2000;
        m_uiPhase = 2;
    }
};

CreatureAI* GetAI_npc_nesingwary_trapper(Creature* pCreature)
{
    return new npc_nesingwary_trapperAI(pCreature);
}

/*######
## go_caribou_trap
######*/

bool GOHello_go_caribou_trap(Player* pPlayer, GameObject* pGo)
{
    float fX, fY, fZ;
    pGo->GetClosePoint(fX, fY, fZ, pGo->GetObjectBoundingRadius(), 2*INTERACTION_DISTANCE, frand(0, M_PI_F*2));

    if (Creature* pCreature = pGo->SummonCreature(NPC_NESINGWARY_TRAPPER, fX, fY, fZ, pGo->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 10000))
    {
        if (npc_nesingwary_trapperAI* pTrapperAI = dynamic_cast<npc_nesingwary_trapperAI*>(pCreature->AI()))
            pTrapperAI->StartAction(pPlayer->GetGUID(), pGo->GetGUID());

        pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);

        if (GameObject* pGoFur = GetClosestGameObjectWithEntry(pGo, GO_QUALITY_FUR, INTERACTION_DISTANCE))
        {
            if (!pGoFur->isSpawned())
            {
                pGoFur->SetRespawnTime(10);
                pGoFur->Refresh();
            }
        }
    }

    return true;
}


CreatureAI* GetAI_npc_nexus_drake(Creature* pCreature)
{
    return new npc_nexus_drakeAI(pCreature);
}

void AddSC_borean_tundra()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mob_arcane_prisoner";
    newscript->GetAI = &GetAI_mob_arcane_prisoner;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tadpole_cage";
    newscript->pGOHello = &GOHello_go_tadpole_cage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_tadpole";
    newscript->GetAI = &GetAI_mob_tadpole;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_elder";
    newscript->GetAI = &GetAI_mob_elder;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_fizzcrank_fullthrottle";
    newscript->pGossipHello = &GossipHello_npc_fizzcrank_fullthrottle;
    newscript->pGossipSelect = &GossipSelect_npc_fizzcrank_fullthrottle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_iruk";
    newscript->pGossipHello = &GossipHello_npc_iruk;
    newscript->pGossipSelect = &GossipSelect_npc_iruk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_kara_thricestar";
    newscript->pGossipHello = &GossipHello_npc_kara_thricestar;
    newscript->pGossipSelect = &GossipSelect_npc_kara_thricestar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_overseer";
    newscript->GetAI = &GetAI_mob_overseer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nesingwary_trapper";
    newscript->GetAI = &GetAI_npc_nesingwary_trapper;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_caribou_trap";
    newscript->pGOHello = &GOHello_go_caribou_trap;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_surristrasz";
    newscript->pGossipHello = &GossipHello_npc_surristrasz;
    newscript->pGossipSelect = &GossipSelect_npc_surristrasz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tiare";
    newscript->pGossipHello = &GossipHello_npc_tiare;
    newscript->pGossipSelect = &GossipSelect_npc_tiare;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lurgglbr";
    newscript->GetAI = &GetAI_npc_lurgglbr;
    newscript->pQuestAccept = &QuestAccept_npc_lurgglbr;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_mammoth_trap";
    newscript->pGOHello = &GOHello_go_mammoth_trap;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_beryl_sorcerer";
    newscript->GetAI = &GetAI_npc_beryl_sorcerer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_scourge_cage";
    newscript->pGOHello = &GOHello_go_scourge_cage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nexus_drake";
    newscript->GetAI = &GetAI_npc_nexus_drake;
    newscript->RegisterSelf();
}
