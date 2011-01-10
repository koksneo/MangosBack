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
SDName: Icecrown
SD%Complete: 100
SDComment: Quest support: 12807, Vendor support: 34885
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_arete
npc_dame_evniki_kapsalis
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_arete
######*/

#define GOSSIP_ARETE_ITEM1 "Lord-Commander, I would hear your tale."
#define GOSSIP_ARETE_ITEM2 "<You nod slightly but do not complete the motion as the Lord-Commander narrows his eyes before he continues.>"
#define GOSSIP_ARETE_ITEM3 "I thought that they now called themselves the Scarlet Onslaught?"
#define GOSSIP_ARETE_ITEM4 "Where did the grand admiral go?"
#define GOSSIP_ARETE_ITEM5 "That's fine. When do I start?"
#define GOSSIP_ARETE_ITEM6 "Let's finish this!"
#define GOSSIP_ARETE_ITEM7 "That's quite a tale, Lord-Commander."

enum
{
    GOSSIP_TEXTID_ARETE1        = 13525,
    GOSSIP_TEXTID_ARETE2        = 13526,
    GOSSIP_TEXTID_ARETE3        = 13527,
    GOSSIP_TEXTID_ARETE4        = 13528,
    GOSSIP_TEXTID_ARETE5        = 13529,
    GOSSIP_TEXTID_ARETE6        = 13530,
    GOSSIP_TEXTID_ARETE7        = 13531,

    QUEST_THE_STORY_THUS_FAR    = 12807
};

bool GossipHello_npc_arete(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_STORY_THUS_FAR) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_arete(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE7, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(QUEST_THE_STORY_THUS_FAR);
            break;
    }

    return true;
}

/*######
## npc_dame_evniki_kapsalis
######*/

enum
{
    TITLE_CRUSADER    = 123
};

bool GossipHello_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasTitle(TITLE_CRUSADER))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
    return true;
}

/*######
## npc_father_kamaros
######*/

enum FatherKamaros
{
    QUEST_IM_NOT_DEAD_YET_A         = 13221,
    QUEST_IM_NOT_DEAD_YET_H         = 13229,
    SPELL_SW_PAIN                   = 17146,
    SPELL_PW_SHIELD                 = 32595,
    SPELL_PW_FORTITUDE              = 58921,
    SPELL_HOLY_SMITE                = 25054,

    SAY_ESCORT_START_1              = -1999766,
    SAY_ESCORT_START_2              = -1999765,
    SAY_ESCORT_COMPLETE_1           = -1999764,
    SAY_ESCORT_COMPLETE_2           = -1999763,
};

struct MANGOS_DLL_DECL npc_father_kamarosAI : public npc_escortAI
{
    npc_father_kamarosAI(Creature* pCreature) : npc_escortAI(pCreature){Reset();}

    bool bSpoken;
    bool bFinalPointReached;
    uint32 m_uiSpeachInterval;
    uint32 m_uiSpellTimer;
   
    void Reset()
    {
        bSpoken = false;
        bFinalPointReached = false;
        m_uiSpeachInterval = 5000;
        m_uiSpellTimer     = 0;
    }

    void WaypointReached(uint32 uiPointId)
    {
        if (uiPointId == 30)
        {
            if (Player* pPlayer = GetPlayerForEscort())
            {
                m_creature->SetFacingToObject(pPlayer);
                DoScriptText(SAY_ESCORT_COMPLETE_1, m_creature, pPlayer);
                pPlayer->AreaExploredOrEventHappens(pPlayer->GetTeam() == HORDE ? QUEST_IM_NOT_DEAD_YET_H : QUEST_IM_NOT_DEAD_YET_A);
            }
            SetEscortPaused(true);
            bSpoken = true;
            SetRun(true);
        }
    }

    void JustStartedEscort()
    {
        SetEscortPaused(true);
        bSpoken = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bSpoken)
        {
            if (m_uiSpeachInterval < uiDiff)
            {
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(bFinalPointReached ? SAY_ESCORT_START_2 : SAY_ESCORT_COMPLETE_2, m_creature, pPlayer);
                bSpoken = false;
                m_uiSpeachInterval = 5000;
                SetEscortPaused(false);
            }
            else
                m_uiSpeachInterval -= uiDiff;
        }
        npc_escortAI::UpdateAI(uiDiff);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSpellTimer < uiDiff)
        {
            Player* pPlayer = GetPlayerForEscort();
            switch(urand(0, 3))
            {
                case 0: DoCastSpellIfCan(pPlayer, SPELL_PW_SHIELD); break;
                case 1: DoCastSpellIfCan(m_creature, SPELL_PW_SHIELD); break;
                case 2: DoCastSpellIfCan(m_creature->getVictim(), SPELL_SW_PAIN); break;
                case 3: DoCastSpellIfCan(m_creature->getVictim(), SPELL_HOLY_SMITE); break;
            }
            m_uiSpellTimer = 5000;
        }
        else
            m_uiSpellTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_father_kamaros(Creature* pCreature)
{
    return new npc_father_kamarosAI (pCreature);
}

bool QuestAccept_npc_father_kamaros(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    switch(pQuest->GetQuestId())
    {
        case QUEST_IM_NOT_DEAD_YET_A:
        case QUEST_IM_NOT_DEAD_YET_H:
        {
            if (npc_father_kamarosAI* pEscortAI = dynamic_cast<npc_father_kamarosAI*>(pCreature->AI()))
            {
                pCreature->SetStandState(UNIT_STAND_STATE_STAND);
                pCreature->SetFacingToObject(pPlayer);
                DoScriptText(SAY_ESCORT_START_1, pCreature, pPlayer);
                pCreature->CastSpell(pPlayer, SPELL_PW_FORTITUDE, false);
                pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
            }
        }
        break;
    }
    return true;
}

/*######
## mob_saronite_mine_slave (31397)
######*/

enum
{
    QUEST_SLAVES_TO_SARNOITE_A       = 13300, //Alliance version
    SPELL_DESPAWN_SELF               = 43014,
    NPC_SLAVES_TO_SARONITE_CREDIT    = 31866,
    QUEST_SLAVES_TO_SARNOITE_H       = 13302,  //Horde version
    SARONITE_SLAVE_TEXTID            = 14068,
    SARONITE_SLAVE_TEXT1             = -1999000,
    SARONITE_SLAVE_TEXT2             = -1999001,
    SARONITE_SLAVE_TEXT3             = -1999002
};

#define GOSSIP_EVENT_FREE      "Go on, you're free. Get out of here!"

bool GossipHello_mob_mine_slave(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if ( (pPlayer->GetQuestStatus(QUEST_SLAVES_TO_SARNOITE_A) == QUEST_STATUS_INCOMPLETE) ||
        (pPlayer->GetQuestStatus(QUEST_SLAVES_TO_SARNOITE_H) == QUEST_STATUS_INCOMPLETE) )
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_EVENT_FREE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(SARONITE_SLAVE_TEXTID, pCreature->GetGUID());
    return true;
}

bool GossipSelect_mob_mine_slave(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        switch (urand(0, 10))
        {
            case 0:
                switch(urand(1, 3))
                {
                    case 1: DoScriptText(SARONITE_SLAVE_TEXT1, pCreature); break;
                    case 2: DoScriptText(SARONITE_SLAVE_TEXT2, pCreature); break;
                    case 3: DoScriptText(SARONITE_SLAVE_TEXT3, pCreature); break;
                }
                pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, true);
                break;

            case 1:
                pCreature->setFaction(16);
                pCreature->AI()->AttackStart(pPlayer);
                break;

            default:
                pPlayer->KilledMonsterCredit(NPC_SLAVES_TO_SARONITE_CREDIT, pCreature->GetGUID());
                pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, true);
                break;
        }
    }
    return true;
}

void AddSC_icecrown()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_arete";
    newscript->pGossipHello = &GossipHello_npc_arete;
    newscript->pGossipSelect = &GossipSelect_npc_arete;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dame_evniki_kapsalis";
    newscript->pGossipHello = &GossipHello_npc_dame_evniki_kapsalis;
    newscript->pGossipSelect = &GossipSelect_npc_dame_evniki_kapsalis;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_father_kamaros";
    newscript->GetAI = &GetAI_npc_father_kamaros;
    newscript->pQuestAccept = &QuestAccept_npc_father_kamaros;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_mine_slave";
    newscript->pGossipHello =  &GossipHello_mob_mine_slave;
    newscript->pGossipSelect = &GossipSelect_mob_mine_slave;
    newscript->RegisterSelf();
}
