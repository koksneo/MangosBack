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
SDName: Ebon_Hold
SD%Complete: 80
SDComment: Quest support: 12848, 12733, 12739(and 12742 to 12750), 12727, 12801, 12698
SDCategory: Ebon Hold
EndScriptData */

/* ContentData
npc_a_special_surprise
npc_death_knight_initiate
npc_unworthy_initiate_anchor
npc_unworthy_initiate
go_acherus_soul_prison
npc_eye_of_acherus
npc_valkyr_battlemaiden
npc_highlord_darion_mograine
npc_koltira_orbaz_tassarian_dawn_of_light
mob_acherus_ghoul
mob_warrior_of_the_frozen_wastes
mob_scarlet_ghoul
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_a_special_surprise
######*/

enum SpecialSurprise
{
    SAY_EXEC_START_1            = -1609025,                 // speech for all
    SAY_EXEC_START_2            = -1609026,
    SAY_EXEC_START_3            = -1609027,
    SAY_EXEC_PROG_1             = -1609028,
    SAY_EXEC_PROG_2             = -1609029,
    SAY_EXEC_PROG_3             = -1609030,
    SAY_EXEC_PROG_4             = -1609031,
    SAY_EXEC_PROG_5             = -1609032,
    SAY_EXEC_PROG_6             = -1609033,
    SAY_EXEC_PROG_7             = -1609034,
    SAY_EXEC_NAME_1             = -1609035,
    SAY_EXEC_NAME_2             = -1609036,
    SAY_EXEC_RECOG_1            = -1609037,
    SAY_EXEC_RECOG_2            = -1609038,
    SAY_EXEC_RECOG_3            = -1609039,
    SAY_EXEC_RECOG_4            = -1609040,
    SAY_EXEC_RECOG_5            = -1609041,
    SAY_EXEC_RECOG_6            = -1609042,
    SAY_EXEC_NOREM_1            = -1609043,
    SAY_EXEC_NOREM_2            = -1609044,
    SAY_EXEC_NOREM_3            = -1609045,
    SAY_EXEC_NOREM_4            = -1609046,
    SAY_EXEC_NOREM_5            = -1609047,
    SAY_EXEC_NOREM_6            = -1609048,
    SAY_EXEC_NOREM_7            = -1609049,
    SAY_EXEC_NOREM_8            = -1609050,
    SAY_EXEC_NOREM_9            = -1609051,
    SAY_EXEC_THINK_1            = -1609052,
    SAY_EXEC_THINK_2            = -1609053,
    SAY_EXEC_THINK_3            = -1609054,
    SAY_EXEC_THINK_4            = -1609055,
    SAY_EXEC_THINK_5            = -1609056,
    SAY_EXEC_THINK_6            = -1609057,
    SAY_EXEC_THINK_7            = -1609058,
    SAY_EXEC_THINK_8            = -1609059,
    SAY_EXEC_THINK_9            = -1609060,
    SAY_EXEC_THINK_10           = -1609061,
    SAY_EXEC_LISTEN_1           = -1609062,
    SAY_EXEC_LISTEN_2           = -1609063,
    SAY_EXEC_LISTEN_3           = -1609064,
    SAY_EXEC_LISTEN_4           = -1609065,
    SAY_PLAGUEFIST              = -1609066,
    SAY_EXEC_TIME_1             = -1609067,
    SAY_EXEC_TIME_2             = -1609068,
    SAY_EXEC_TIME_3             = -1609069,
    SAY_EXEC_TIME_4             = -1609070,
    SAY_EXEC_TIME_5             = -1609071,
    SAY_EXEC_TIME_6             = -1609072,
    SAY_EXEC_TIME_7             = -1609073,
    SAY_EXEC_TIME_8             = -1609074,
    SAY_EXEC_TIME_9             = -1609075,
    SAY_EXEC_TIME_10            = -1609076,
    SAY_EXEC_WAITING            = -1609077,
    EMOTE_DIES                  = -1609078,

    NPC_PLAGUEFIST              = 29053
};

struct MANGOS_DLL_DECL npc_a_special_surpriseAI : public ScriptedAI
{
    npc_a_special_surpriseAI(Creature *pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiExecuteSpeech_Timer;
    uint32 m_uiExecuteSpeech_Counter;
    uint64 m_uiPlayerGUID;

    void Reset()
    {
        m_uiExecuteSpeech_Timer = 0;
        m_uiExecuteSpeech_Counter = 0;
        m_uiPlayerGUID = 0;
    }

    bool MeetQuestCondition(Player* pPlayer)
    {
        switch(m_creature->GetEntry())
        {
            case 29061:                                     // Ellen Stanbridge
                if (pPlayer->GetQuestStatus(12742) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29072:                                     // Kug Ironjaw
                if (pPlayer->GetQuestStatus(12748) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29067:                                     // Donovan Pulfrost
                if (pPlayer->GetQuestStatus(12744) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29065:                                     // Yazmina Oakenthorn
                if (pPlayer->GetQuestStatus(12743) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29071:                                     // Antoine Brack
                if (pPlayer->GetQuestStatus(12750) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29032:                                     // Malar Bravehorn
                if (pPlayer->GetQuestStatus(12739) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29068:                                     // Goby Blastenheimer
                if (pPlayer->GetQuestStatus(12745) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29073:                                     // Iggy Darktusk
                if (pPlayer->GetQuestStatus(12749) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29074:                                     // Lady Eonys
                if (pPlayer->GetQuestStatus(12747) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
            case 29070:                                     // Valok the Righteous
                if (pPlayer->GetQuestStatus(12746) == QUEST_STATUS_INCOMPLETE)
                    return true;
                break;
        }

        return false;
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_uiPlayerGUID || pWho->GetTypeId() != TYPEID_PLAYER || !pWho->IsWithinDist(m_creature, INTERACTION_DISTANCE))
            return;

        if (MeetQuestCondition((Player*)pWho))
            m_uiPlayerGUID = pWho->GetGUID();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiPlayerGUID && !m_creature->getVictim() && m_creature->isAlive())
        {
            if (m_uiExecuteSpeech_Timer < uiDiff)
            {
                Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID);

                if (!pPlayer)
                {
                    Reset();
                    return;
                }

                //TODO: simplify text's selection

                switch(pPlayer->getRace())
                {
                    case RACE_HUMAN:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_5, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_1, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_5, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_7, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_6, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_ORC:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_6, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_1, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_7, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_8, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_8, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_DWARF:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_2, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_2, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_3, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_2, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_5, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_2, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_3, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_NIGHTELF:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_5, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_1, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_6, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_2, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_7, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_UNDEAD_PLAYER:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_3, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_4, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_3, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_1, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_3, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_4, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_TAUREN:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_1, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_5, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_8, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_9, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_9, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_GNOME:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_4, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_1, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_4, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_6, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_5, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_TROLL:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_3, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_7, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_2, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_6, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_9, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_10, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_4, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_10, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_BLOODELF:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_1, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_1, m_creature, pPlayer); break;
                            //case 5: //unknown
                            case 6: DoScriptText(SAY_EXEC_THINK_3, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_1, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                    case RACE_DRAENEI:
                        switch(m_uiExecuteSpeech_Counter)
                        {
                            case 0: DoScriptText(SAY_EXEC_START_1, m_creature, pPlayer); break;
                            case 1: m_creature->SetStandState(UNIT_STAND_STATE_STAND); break;
                            case 2: DoScriptText(SAY_EXEC_PROG_1, m_creature, pPlayer); break;
                            case 3: DoScriptText(SAY_EXEC_NAME_1, m_creature, pPlayer); break;
                            case 4: DoScriptText(SAY_EXEC_RECOG_2, m_creature, pPlayer); break;
                            case 5: DoScriptText(SAY_EXEC_NOREM_1, m_creature, pPlayer); break;
                            case 6: DoScriptText(SAY_EXEC_THINK_4, m_creature, pPlayer); break;
                            case 7: DoScriptText(SAY_EXEC_LISTEN_1, m_creature, pPlayer); break;
                            case 8:
                                if (Creature* pPlaguefist = GetClosestCreatureWithEntry(m_creature, NPC_PLAGUEFIST, 85.0f))
                                    DoScriptText(SAY_PLAGUEFIST, pPlaguefist, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_EXEC_TIME_2, m_creature, pPlayer);
                                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                break;
                            case 10: DoScriptText(SAY_EXEC_WAITING, m_creature, pPlayer); break;
                            case 11:
                                DoScriptText(EMOTE_DIES, m_creature);
                                m_creature->SetDeathState(JUST_DIED);
                                m_creature->SetHealth(0);
                                return;
                        }
                        break;
                }

                if (m_uiExecuteSpeech_Counter >= 9)
                    m_uiExecuteSpeech_Timer = 15000;
                else
                    m_uiExecuteSpeech_Timer = 7000;

                ++m_uiExecuteSpeech_Counter;
            }
            else
                m_uiExecuteSpeech_Timer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_a_special_surprise(Creature* pCreature)
{
    return new npc_a_special_surpriseAI(pCreature);
}

/*######
## npc_death_knight_initiate
######*/

enum
{
    SAY_DUEL_A                  = -1609016,
    SAY_DUEL_B                  = -1609017,
    SAY_DUEL_C                  = -1609018,
    SAY_DUEL_D                  = -1609019,
    SAY_DUEL_E                  = -1609020,
    SAY_DUEL_F                  = -1609021,
    SAY_DUEL_G                  = -1609022,
    SAY_DUEL_H                  = -1609023,
    SAY_DUEL_I                  = -1609024,

    SPELL_DUEL                  = 52996,
    SPELL_DUEL_TRIGGERED        = 52990,
    SPELL_DUEL_VICTORY          = 52994,
    SPELL_DUEL_FLAG             = 52991,

    QUEST_DEATH_CHALLENGE       = 12733,
    FACTION_HOSTILE             = 2068
};

int32 m_auiRandomSay[] =
{
    SAY_DUEL_A, SAY_DUEL_B, SAY_DUEL_C, SAY_DUEL_D, SAY_DUEL_E, SAY_DUEL_F, SAY_DUEL_G, SAY_DUEL_H, SAY_DUEL_I
};

#define GOSSIP_ACCEPT_DUEL      "I challenge you, death knight!"

struct MANGOS_DLL_DECL npc_death_knight_initiateAI : public ScriptedAI
{
    npc_death_knight_initiateAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint64 m_uiDuelerGUID;
    uint32 m_uiDuelTimer;
    bool m_bIsDuelInProgress;

    void Reset()
    {
        if (m_creature->getFaction() != m_creature->GetCreatureInfo()->faction_A)
            m_creature->setFaction(m_creature->GetCreatureInfo()->faction_A);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);

        m_uiDuelerGUID = 0;
        m_uiDuelTimer = 5000;
        m_bIsDuelInProgress = false;
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (m_creature->getVictim())
            return;

        if (m_creature->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (!m_bIsDuelInProgress && pSpell->Id == SPELL_DUEL_TRIGGERED && pCaster->GetTypeId() == TYPEID_PLAYER)
        {
            m_uiDuelerGUID = pCaster->GetGUID();
            m_bIsDuelInProgress = true;
        }
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_bIsDuelInProgress && uiDamage > m_creature->GetHealth())
        {
            uiDamage = 0;

            if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiDuelerGUID))
                m_creature->CastSpell(pPlayer, SPELL_DUEL_VICTORY, true);

            //possibly not evade, but instead have end sequenze
            EnterEvadeMode();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_bIsDuelInProgress)
            {
                if (m_uiDuelTimer < uiDiff)
                {
                    m_creature->setFaction(FACTION_HOSTILE);

                    if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiDuelerGUID))
                        AttackStart(pPlayer);
                }
                else
                    m_uiDuelTimer -= uiDiff;
            }
            return;
        }

        // TODO: spells

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_death_knight_initiate(Creature* pCreature)
{
    return new npc_death_knight_initiateAI(pCreature);
}

bool GossipHello_npc_death_knight_initiate(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_DEATH_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ACCEPT_DUEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(13433, pCreature->GetGUID());
        return true;
    }
    return false;
}

bool GossipSelect_npc_death_knight_initiate(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_death_knight_initiateAI* pInitiateAI = dynamic_cast<npc_death_knight_initiateAI*>(pCreature->AI()))
        {
            if (pInitiateAI->m_bIsDuelInProgress)
                return true;
        }

        pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);

        int32 uiSayId = rand()% (sizeof(m_auiRandomSay)/sizeof(int32));
        DoScriptText(m_auiRandomSay[uiSayId], pCreature, pPlayer);

        pCreature->CastSpell(pPlayer, SPELL_DUEL, false);
        pCreature->CastSpell(pPlayer, SPELL_DUEL_FLAG, true);
    }
    return true;
}

/*######
## npc_koltira_deathweaver
######*/

enum eKoltira
{
    SAY_BREAKOUT1                   = -1609079,
    SAY_BREAKOUT2                   = -1609080,
    SAY_BREAKOUT3                   = -1609081,
    SAY_BREAKOUT4                   = -1609082,
    SAY_BREAKOUT5                   = -1609083,
    SAY_BREAKOUT6                   = -1609084,
    SAY_BREAKOUT7                   = -1609085,
    SAY_BREAKOUT8                   = -1609086,
    SAY_BREAKOUT9                   = -1609087,
    SAY_BREAKOUT10                  = -1609088,

    SPELL_KOLTIRA_TRANSFORM         = 52899,
    SPELL_ANTI_MAGIC_ZONE           = 52894,

    QUEST_BREAKOUT                  = 12727,

    NPC_CRIMSON_ACOLYTE             = 29007,
    NPC_HIGH_INQUISITOR_VALROTH     = 29001,
    NPC_KOLTIRA_ALT                 = 28447,

    //not sure about this id
    //NPC_DEATH_KNIGHT_MOUNT          = 29201,
    MODEL_DEATH_KNIGHT_MOUNT        = 25278
};

struct MANGOS_DLL_DECL npc_koltira_deathweaverAI : public npc_escortAI
{
    npc_koltira_deathweaverAI(Creature *pCreature) : npc_escortAI(pCreature) { Reset(); }

    uint32 m_uiWave;
    uint32 m_uiWave_Timer;
    uint64 m_uiValrothGUID;

    void Reset()
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            m_uiWave = 0;
            m_uiWave_Timer = 3000;
            m_uiValrothGUID = 0;
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                DoScriptText(SAY_BREAKOUT1, m_creature);
                break;
            case 1:
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case 2:
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                //m_creature->UpdateEntry(NPC_KOLTIRA_ALT); //unclear if we must update or not
                DoCastSpellIfCan(m_creature, SPELL_KOLTIRA_TRANSFORM);
                break;
            case 3:
                SetEscortPaused(true);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                DoScriptText(SAY_BREAKOUT2, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_ANTI_MAGIC_ZONE);  // cast again that makes bubble up
                break;
            case 4:
                SetRun(true);
                break;
            case 9:
                m_creature->Mount(MODEL_DEATH_KNIGHT_MOUNT);
                break;
            case 10:
                m_creature->Unmount();
                break;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (Player* pPlayer = GetPlayerForEscort())
        {
            pSummoned->AI()->AttackStart(pPlayer);
            pSummoned->AddThreat(m_creature);
        }

        if (pSummoned->GetEntry() == NPC_HIGH_INQUISITOR_VALROTH)
            m_uiValrothGUID = pSummoned->GetGUID();
    }

    void SummonAcolyte(uint32 uiAmount)
    {
        for(uint32 i = 0; i < uiAmount; ++i)
            m_creature->SummonCreature(NPC_CRIMSON_ACOLYTE, 1642.329f, -6045.818f, 127.583f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (HasEscortState(STATE_ESCORT_PAUSED))
        {
            if (m_uiWave_Timer < uiDiff)
            {
                switch(m_uiWave)
                {
                    case 0:
                        DoScriptText(SAY_BREAKOUT3, m_creature);
                        SummonAcolyte(3);
                        m_uiWave_Timer = 20000;
                        break;
                    case 1:
                        DoScriptText(SAY_BREAKOUT4, m_creature);
                        SummonAcolyte(3);
                        m_uiWave_Timer = 20000;
                        break;
                    case 2:
                        DoScriptText(SAY_BREAKOUT5, m_creature);
                        SummonAcolyte(4);
                        m_uiWave_Timer = 20000;
                        break;
                    case 3:
                        DoScriptText(SAY_BREAKOUT6, m_creature);
                        m_creature->SummonCreature(NPC_HIGH_INQUISITOR_VALROTH, 1642.329f, -6045.818f, 127.583f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
                        m_uiWave_Timer = 1000;
                        break;
                    case 4:
                    {
                        Creature* pTemp = m_creature->GetMap()->GetCreature(m_uiValrothGUID);

                        if (!pTemp || !pTemp->isAlive())
                        {
                            DoScriptText(SAY_BREAKOUT8, m_creature);
                            m_uiWave_Timer = 5000;
                        }
                        else
                        {
                            m_uiWave_Timer = 2500;
                            return;                         //return, we don't want m_uiWave to increment now
                        }
                        break;
                    }
                    case 5:
                        DoScriptText(SAY_BREAKOUT9, m_creature);
                        m_creature->RemoveAurasDueToSpell(SPELL_ANTI_MAGIC_ZONE);
                        m_uiWave_Timer = 2500;
                        break;
                    case 6:
                        DoScriptText(SAY_BREAKOUT10, m_creature);
                        SetEscortPaused(false);
                        break;
                }

                ++m_uiWave;
            }
            else
                m_uiWave_Timer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_koltira_deathweaver(Creature* pCreature)
{
    return new npc_koltira_deathweaverAI(pCreature);
}

bool QuestAccept_npc_koltira_deathweaver(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_BREAKOUT)
    {
        pCreature->SetStandState(UNIT_STAND_STATE_STAND);

        if (npc_koltira_deathweaverAI* pEscortAI = dynamic_cast<npc_koltira_deathweaverAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
    }
    return true;
}

/*######
##
######*/

enum
{
    SAY_START                       = -1609000,             // 8 texts in total, GetTextId() generates random with this as base
    SAY_AGGRO                       = -1609008,             // 8 texts in total, GetTextId() generates random with this as base

    //SPELL_CHAINED_PESANT_LH         = 54602,              // not used. possible it determine side, where to go get "weapon"
    //SPELL_CHAINED_PESANT_RH         = 54610,
    SPELL_CHAINED_PESANT_CHEST      = 54612,
    SPELL_CHAINED_PESANT_BREATH     = 54613,
    SPELL_INITIATE_VISUAL           = 51519,

    SPELL_BLOOD_STRIKE              = 52374,
    SPELL_DEATH_COIL                = 52375,
    SPELL_ICY_TOUCH                 = 52372,
    SPELL_PLAGUE_STRIKE             = 52373,

    NPC_ANCHOR                      = 29521,
    FACTION_MONSTER                 = 16,

    PHASE_INACTIVE_OR_COMBAT        = 0,
    PHASE_DRESSUP                   = 1,
    PHASE_ACTIVATE                  = 2
};

struct DisplayToSpell
{
    uint32 m_uiDisplayId;
    uint32 m_uiSpellToNewDisplay;
};

DisplayToSpell m_aDisplayToSpell[] =
{
    {25354, 51520},                                         // human M
    {25355, 51534},                                         // human F
    {25356, 51538},                                         // dwarf M
    {25357, 51541},                                         // draenei M
    {25358, 51535},                                         // nelf M
    {25359, 51539},                                         // gnome M
    {25360, 51536},                                         // nelf F
    {25361, 51537},                                         // dwarf F
    {25362, 51540},                                         // gnome F
    {25363, 51542},                                         // draenei F
    {25364, 51543},                                         // orc M
    {25365, 51546},                                         // troll M
    {25366, 51547},                                         // tauren M
    {25367, 51549},                                         // forsaken M
    {25368, 51544},                                         // orc F
    {25369, 51552},                                         // belf F
    {25370, 51545},                                         // troll F
    {25371, 51548},                                         // tauren F
    {25372, 51550},                                         // forsaken F
    {25373, 51551}                                          // belf M
};

/*######
## npc_unworthy_initiate_anchor
######*/

struct MANGOS_DLL_DECL npc_unworthy_initiate_anchorAI : public ScriptedAI
{
    npc_unworthy_initiate_anchorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiMyInitiate = 0;
        Reset();
    }

    uint64 m_uiMyInitiate;
    uint64 m_uiMyPrisonGUID;

    void Reset() { }

    void NotifyMe(Unit* pSource, uint64 uiPrisonGuid)
    {
        m_uiMyPrisonGUID = uiPrisonGuid;
        Creature* pInitiate = m_creature->GetMap()->GetCreature(m_uiMyInitiate);

        if (pInitiate && pSource)
        {
            pInitiate->SetLootRecipient(pSource);
            m_creature->CastSpell(pInitiate,SPELL_CHAINED_PESANT_BREATH,true);
        }
    }

    void RegisterCloseInitiate(uint64 uiGuid)
    {
        m_uiMyInitiate = uiGuid;
    }

    void ResetPrison()
    {
        if (GameObject* pPrison = m_creature->GetMap()->GetGameObject(m_uiMyPrisonGUID))
            pPrison->ResetDoorOrButton();
    }
};

CreatureAI* GetAI_npc_unworthy_initiate_anchor(Creature* pCreature)
{
    return new npc_unworthy_initiate_anchorAI(pCreature);
}

/*######
## npc_unworthy_initiate
######*/

struct MANGOS_DLL_DECL npc_unworthy_initiateAI : public ScriptedAI
{
    npc_unworthy_initiateAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pToTransform = NULL;

        uint32 uiDisplayCount = sizeof(m_aDisplayToSpell)/sizeof(DisplayToSpell);

        for (uint8 i=0; i<uiDisplayCount; ++i)
        {
            // check if we find a match, if not, it's NULL and produce error when used
            if (m_aDisplayToSpell[i].m_uiDisplayId == pCreature->GetDisplayId())
            {
                m_pToTransform = &m_aDisplayToSpell[i];
                break;
            }
        }

        m_uiNormFaction = pCreature->getFaction();
        Reset();
    }

    DisplayToSpell* m_pToTransform;

    uint64 m_uiMyAnchorGUID;
    uint32 m_uiNormFaction;
    uint32 m_uiAnchorCheckTimer;
    uint32 m_uiPhase;
    uint32 m_uiPhaseTimer;
    uint32 m_uiBloodStrike_Timer;
    uint32 m_uiDeathCoil_Timer;
    uint32 m_uiIcyTouch_Timer;
    uint32 m_uiPlagueStrike_Timer;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormFaction)
            m_creature->setFaction(m_uiNormFaction);

        m_uiMyAnchorGUID = 0;
        m_uiAnchorCheckTimer = 5000;
        m_uiPhase = PHASE_INACTIVE_OR_COMBAT;
        m_uiPhaseTimer = 7500;
        m_uiBloodStrike_Timer = 4000;
        m_uiDeathCoil_Timer = 6000;
        m_uiIcyTouch_Timer = 2000;
        m_uiPlagueStrike_Timer = 5000;
    }

    void JustReachedHome()
    {
        SetAnchor();
    }

    void JustRespawned()
    {
        if (Creature* pAnchor = GetAnchor())
        {
            if (npc_unworthy_initiate_anchorAI* pAnchorAI = dynamic_cast<npc_unworthy_initiate_anchorAI*>(pAnchor->AI()))
                pAnchorAI->ResetPrison();
        }

        Reset();
    }

    int32 GetTextId()
    {
        return m_uiPhase == PHASE_DRESSUP ? SAY_START-rand()%8 : SAY_AGGRO-rand()%8;
    }

    Creature* GetAnchor()
    {
        if (m_uiMyAnchorGUID)
            return m_creature->GetMap()->GetCreature(m_uiMyAnchorGUID);
        else
            return GetClosestCreatureWithEntry(m_creature, NPC_ANCHOR, INTERACTION_DISTANCE*2);
    }

    void SetAnchor()
    {
        if (Creature* pAnchor = GetAnchor())
        {
            if (npc_unworthy_initiate_anchorAI* pAnchorAI = dynamic_cast<npc_unworthy_initiate_anchorAI*>(pAnchor->AI()))
                pAnchorAI->RegisterCloseInitiate(m_creature->GetGUID());

            pAnchor->CastSpell(m_creature, SPELL_CHAINED_PESANT_CHEST, false);

            m_uiAnchorCheckTimer = 0;
            return;
        }

        m_uiAnchorCheckTimer = 5000;
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_CHAINED_PESANT_BREATH)
        {
            pCaster->InterruptNonMeleeSpells(true);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

            m_uiPhase = PHASE_DRESSUP;

            if (Player* pSource = m_creature->GetLootRecipient())
                DoScriptText(GetTextId(), m_creature, pSource);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiAnchorCheckTimer)
        {
            if (m_uiAnchorCheckTimer <= uiDiff)
                SetAnchor();
            else
                m_uiAnchorCheckTimer -= uiDiff;
        }

        if (m_uiPhase == PHASE_INACTIVE_OR_COMBAT)
        {
            if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                return;

            if (m_uiBloodStrike_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_BLOOD_STRIKE);
                m_uiBloodStrike_Timer = 9000;
            }
            else
                m_uiBloodStrike_Timer -= uiDiff;

            if (m_uiDeathCoil_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_DEATH_COIL);
                m_uiDeathCoil_Timer = 8000;
            }
            else
                m_uiDeathCoil_Timer -= uiDiff;

            if (m_uiIcyTouch_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_ICY_TOUCH);
                m_uiIcyTouch_Timer = 8000;
            }
            else
                m_uiIcyTouch_Timer -= uiDiff;

            if (m_uiPlagueStrike_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_PLAGUE_STRIKE);
                m_uiPlagueStrike_Timer = 8000;
            }
            else
                m_uiPlagueStrike_Timer -= uiDiff;

            DoMeleeAttackIfReady();
        }
        else
        {
            if (m_uiPhaseTimer < uiDiff)
            {
                if (m_uiPhase == PHASE_DRESSUP)
                {
                    if (m_pToTransform)
                    {
                        m_creature->CastSpell(m_creature, m_pToTransform->m_uiSpellToNewDisplay, true);
                        m_creature->CastSpell(m_creature, SPELL_INITIATE_VISUAL, false);
                    }
                    else
                        error_log("SD2: npc_unworthy_initiate does not have any spell associated with model");

                    m_uiPhase = PHASE_ACTIVATE;
                }
                else
                {
                    m_creature->setFaction(FACTION_MONSTER);

                    m_uiPhase = PHASE_INACTIVE_OR_COMBAT;

                    if (Player* pTarget = m_creature->GetLootRecipient())
                    {
                        DoScriptText(GetTextId(), m_creature, pTarget);
                        AttackStart(pTarget);
                    }
                }

                m_uiPhaseTimer = 5000;
            }
            else
                m_uiPhaseTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_unworthy_initiate(Creature* pCreature)
{
    return new npc_unworthy_initiateAI(pCreature);
}

/*######
## go_acherus_soul_prison
######*/

bool GOHello_go_acherus_soul_prison(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pAnchor = GetClosestCreatureWithEntry(pGo, NPC_ANCHOR, INTERACTION_DISTANCE))
    {
        if (npc_unworthy_initiate_anchorAI* pAnchorAI = dynamic_cast<npc_unworthy_initiate_anchorAI*>(pAnchor->AI()))
            pAnchorAI->NotifyMe(pPlayer, pGo->GetGUID());
    }

    return false;
}

/*######
## npc_eye_of_acherus
######*/

struct MANGOS_DLL_DECL npc_eye_of_acherusAI : public ScriptedAI
{
    npc_eye_of_acherusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetActiveObjectState(true);
        m_creature->SetLevel(55); //else one hack
        StartTimer = 2000;
        Active = false;
    }

    uint32 StartTimer;
    bool Active;

    void Reset(){}
    void AttackStart(Unit *) {}
    void MoveInLineOfSight(Unit*) {}

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE && uiPointId == 0)
            return;

            m_creature->MonsterTextEmote("The Eye of Acherus is in your control", m_creature, true);
            m_creature->CastSpell(m_creature, 51890, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_creature->isCharmed())
        {
            if (StartTimer < uiDiff && !Active)
            {
                m_creature->CastSpell(m_creature, 70889, true);
                m_creature->CastSpell(m_creature, 51892, true);
                char * text = "The Eye of Acherus launches towards its destination";
                m_creature->MonsterTextEmote(text, m_creature, true);
                m_creature->SetSpeedRate(MOVE_FLIGHT, 6.4f,true);
                m_creature->GetMotionMaster()->MovePoint(0, 1750.8276f, -5873.788f, 151.2266f);
                Active = true;
            }
            else StartTimer -= uiDiff;
        }
        else
        {
            m_creature->CleanupsBeforeDelete();
            m_creature->AddObjectToRemoveList();
        }
    }

    void JustDied(Unit*u)
    {
        m_creature->CleanupsBeforeDelete();
        m_creature->AddObjectToRemoveList();
    }
};

CreatureAI* GetAI_npc_eye_of_acherus(Creature* pCreature)
{
    return new npc_eye_of_acherusAI(pCreature);
}

/*######
## Val'kyr Battle-Maiden
######*/
 
#define SPELL_REVIVE                51918
#define OWNER_POINT                 0
 
struct MANGOS_DLL_DECL npc_valkyr_battlemaidenAI : public ScriptedAI
{
    npc_valkyr_battlemaidenAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pCreature->NearTeleportTo(m_creature->GetPositionX()+5.0f, m_creature->GetPositionY()+5.0f, m_creature->GetPositionZ()+10.0f, m_creature->GetOrientation(), false);
        Reset();
    }
 
    uint32 m_uiDespawnTimer;
 
    void Reset()
    {
        m_creature->GetMotionMaster()->MovePoint(OWNER_POINT, m_creature->GetPositionX()-5.0f, m_creature->GetPositionY()-5.0f, m_creature->GetPositionZ()-8.0f);
        m_uiDespawnTimer = 7000;
    }
 
    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;
 
        if (uiPointId == OWNER_POINT)
            if (Player *pPlayer = m_creature->GetMap()->GetPlayer(m_creature->GetCreatorGuid()) )
                DoCastSpellIfCan(pPlayer, SPELL_REVIVE);
    }
 
    void UpdateAI(uint32 const uiDiff)
    {
        if (m_uiDespawnTimer <= uiDiff)
        {
            m_uiDespawnTimer = 7000;
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_creature->ForcedDespawn(1000);
        }
        else m_uiDespawnTimer -= uiDiff;
    }
};
 
CreatureAI* GetAI_npc_valkyr_battlemaiden(Creature* pCreature)
{
    return new npc_valkyr_battlemaidenAI (pCreature);
}


/* LIGHT OF DAWN */
/*######
## npc_highlord_darion_mograine
######*/
enum mograine
{ 
    ENCOUNTER_DK_NUMBER               = 5,  // how many player queue to start the quest , or -
    ENCOUNTER_DK_TIMER                = 10, // *every 5 minutes. These have to be done in instance data
    ENCOUNTER_DEFENDER_NUMBER         = 38, // how many of defender
    ENCOUNTER_ABOMINATION_NUMBER      = 3,  // how many of abomination
    ENCOUNTER_BEHEMOTH_NUMBER         = 2,  // how many of behemoths (don't change!)
    ENCOUNTER_GHOUL_NUMBER            = 32, // how many of ghoul
    ENCOUNTER_WARRIOR_NUMBER          = 8,  // how many of warrior
    ENCOUNTER_TOTAL_DAWN              = 300,// Total number
    ENCOUNTER_TOTAL_SCOURGE           = 10000,

    WORLD_STATE_LIGHT_REMAINING       = 3590,
    WORLD_STATE_SCOURGE_REMAINING     = 3591,
    WORLD_STATE_REMAINING_SHOW        = 3592,
    WORLD_STATE_COUNTDOWN_SHOW        = 3603,
    WORLD_STATE_COUNTDOWN             = 3604,
    WORLD_STATE_EVENT_BEGIN           = 3605,

    SAY_LIGHT_OF_DAWN01               = -1609201, // pre text
    SAY_LIGHT_OF_DAWN02               = -1609202,
    SAY_LIGHT_OF_DAWN03               = -1609203,
    SAY_LIGHT_OF_DAWN04               = -1609204, // intro
    SAY_LIGHT_OF_DAWN05               = -1609205,
    SAY_LIGHT_OF_DAWN06               = -1609206,
    SAY_LIGHT_OF_DAWN07               = -1609207, // During the fight - Korfax, Champion of the Light
    SAY_LIGHT_OF_DAWN08               = -1609208, // Lord Maxwell Tyrosus
    SAY_LIGHT_OF_DAWN09               = -1609209, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN10               = -1609210,
    SAY_LIGHT_OF_DAWN11               = -1609211,
    SAY_LIGHT_OF_DAWN12               = -1609212,
    SAY_LIGHT_OF_DAWN13               = -1609213,
    SAY_LIGHT_OF_DAWN14               = -1609214,
    SAY_LIGHT_OF_DAWN15               = -1609215,
    SAY_LIGHT_OF_DAWN16               = -1609216,
    SAY_LIGHT_OF_DAWN17               = -1609217,
    SAY_LIGHT_OF_DAWN18               = -1609218,
    SAY_LIGHT_OF_DAWN19               = -1609219,
    SAY_LIGHT_OF_DAWN20               = -1609220,
    SAY_LIGHT_OF_DAWN21               = -1609221,
    SAY_LIGHT_OF_DAWN22               = -1609222,
    SAY_LIGHT_OF_DAWN23               = -1609223,
    SAY_LIGHT_OF_DAWN24               = -1609224,
    SAY_LIGHT_OF_DAWN25               = -1609225, // After the fight
    SAY_LIGHT_OF_DAWN26               = -1609226, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN27               = -1609227, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN28               = -1609228, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN29               = -1609229, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN30               = -1609230, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN31               = -1609231, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN32               = -1609232, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN33               = -1609233, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN34               = -1609234, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN35               = -1609235, // Darion Mograine
    SAY_LIGHT_OF_DAWN36               = -1609236, // Darion Mograine
    SAY_LIGHT_OF_DAWN37               = -1609237, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN38               = -1609238, // Darion Mograine
    SAY_LIGHT_OF_DAWN39               = -1609239, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN40               = -1609240, // Darion Mograine
    SAY_LIGHT_OF_DAWN41               = -1609241, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN42               = -1609242, // Highlord Alexandros Mograine
    SAY_LIGHT_OF_DAWN43               = -1609243, // The Lich King
    SAY_LIGHT_OF_DAWN44               = -1609244, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN45               = -1609245, // The Lich King
    SAY_LIGHT_OF_DAWN46               = -1609246, // The Lich King
    SAY_LIGHT_OF_DAWN47               = -1609247, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN48               = -1609248, // The Lich King
    SAY_LIGHT_OF_DAWN49               = -1609249, // The Lich King
    SAY_LIGHT_OF_DAWN50               = -1609250, // Lord Maxwell Tyrosus
    SAY_LIGHT_OF_DAWN51               = -1609251, // The Lich King
    SAY_LIGHT_OF_DAWN52               = -1609252, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN53               = -1609253, // Highlord Darion Mograine
    SAY_LIGHT_OF_DAWN54               = -1609254, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN55               = -1609255, // The Lich King
    SAY_LIGHT_OF_DAWN56               = -1609256, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN57               = -1609257, // The Lich King
    SAY_LIGHT_OF_DAWN58               = -1609258, // The Lich King
    SAY_LIGHT_OF_DAWN59               = -1609259, // The Lich King
    SAY_LIGHT_OF_DAWN60               = -1609260, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN61               = -1609261, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN62               = -1609262, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN63               = -1609263, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN64               = -1609264, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN65               = -1609265, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN66               = -1609266, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN67               = -1609267, // Highlord Tirion Fordring
    SAY_LIGHT_OF_DAWN68               = -1609268, // Highlord Darion Mograine

    EMOTE_LIGHT_OF_DAWN01             = -1609269,  // Emotes
    EMOTE_LIGHT_OF_DAWN02             = -1609270,
    EMOTE_LIGHT_OF_DAWN03             = -1609271,
    EMOTE_LIGHT_OF_DAWN04             = -1609272,
    EMOTE_LIGHT_OF_DAWN05             = -1609273,

    GO_LIGHT_OF_DAWN                  = 191330,
    GO_HOLY_LIGHTNING_H               = 191301, // lightnings wiping the scourge
    GO_HOLY_LIGHTNING_V               = 191302,
    SPELL_THE_LIGHT_OF_DAWN_Q         = 53606, // quest credit

    // ---- Dark Knight npc --------------------
    // Highlord Darion Mograine
    NPC_HIGHLORD_DARION_MOGRAINE      = 29173,
    SPELL_ANTI_MAGIC_ZONE1            = 52893,
    SPELL_DEATH_STRIKE                = 53639,
    SPELL_DEATH_EMBRACE               = 53635,
    SPELL_ICY_TOUCH1                  = 49723,
    SPELL_THE_LIGHT_OF_DAWN           = 53658,
    SPELL_THE_MIGHT_OF_MOGRAINE       = 53642, // on players when begins
    SPELL_UNHOLY_BLIGHT               = 53640,
    SPELL_ALEXANDROS_MOGRAINE_SPAWN   = 53667,
    SPELL_MOGRAINE_CHARGE             = 53679,
    SPELL_ASHBRINGER                  = 53701,

    // Koltira Deathweaver & Orbaz Bloodbane are using the same abilities
    NPC_KOLTIRA_DEATHWEAVER           = 29199,
    NPC_ORBAZ_BLOODBANE               = 29204, // this guy flees
    NPC_THASSARIAN                    = 29200, // he also does SPELL_THE_LIGHT_OF_DAWN 53658
    //SPELL_BLOOD_STRIKE              = 52374,
    SPELL_DEATH_GRIP                  = 49576,
    //SPELL_ICY_TOUCH                 = 52372,
    SPELL_PLAGUE_STRIKE1              = 50668,
    // all do SPELL_HERO_AGGRO_AURA   = 53627

    // Lich King
    NPC_THE_LICH_KING                 = 29183, // show up at end
    SPELL_APOCALYPSE                  = 53210,
    SELL_POST_APOCALYPSE              = 53211,
    SPELL_TELEPORT_VISUAL             = 52233,
    SPELL_SOUL_FEAST_ALEX             = 53677, // on Alexandros
    SPELL_SOUL_FEAST_TIRION           = 53685, // on Tirion
    SPELL_ICEBOUND_VISAGE             = 53274, // not sure what is it for
    SPELL_REBUKE                      = 53680,

    // others
    NPC_RAMPAGING_ABOMINATION         = 29186,
    SPELL_CLEAVE1                     = 53633,
    SPELL_SCOURGE_HOOK                = 50335,
    SPELL_SCOURGE_AGGRO_AURA          = 53624,

    NPC_FLESH_BEHEMOTH                = 29190, // giant guy
    SPELL_STOMP                       = 53634,
    SPELL_THUNDERCLAP                 = 36706,
    SPELL_HERO_AGGRO_AURA             = 53627,

    NPC_ACHERUS_GHOUL                 = 29219, // just ghoul....
    SPELL_GHOULPLOSION                = 53632,

    NPC_WARRIOR_OF_THE_FROZEN_WASTES  = 29206, // use SPELL_CLEAVE 53631

    NPC_HIGHLORD_ALEXANDROS_MOGRAINE  = 29227, // ghost
    NPC_DARION_MOGRAINE               = 29228, // ghost

    // ---- Dawn npc --------------------
    // Highlord Tirion Fordring
    NPC_HIGHLORD_TIRION_FORDRING      = 29175,
    EQUIP_HIGHLORD_TIRION_FORDRING    = 13262,
    SPELL_LAY_ON_HANDS                = 53778,
    SPELL_DAWN_OF_LIGHT               = 53644,
    SPELL_REBIRTH_OF_THE_ASHBRINGER   = 53702,
    SPELL_TIRION_CHARGE               = 53705,
    SPELL_TIRION_CHARGE_VISUAL        = 53706,
    SPELL_ASHBRINGER_NOVA             = 57544,

    // others
    NPC_KORFAX_CHAMPION_OF_THE_LIGHT  = 29176,
    SPELL_CLEAVE                      = 53631,
    SPELL_HEROIC_LEAP                 = 53625,

    NPC_LORD_MAXWELL_TYROSUS          = 29178,
    NPC_LEONID_BARTHALOMEW_THE_REVERED= 29179,
    NPC_DUKE_NICHOLAS_ZVERENHOFF      = 29180,

    NPC_COMMANDER_ELIGOR_DAWNBRINGER  = 29177,
    SPELL_HOLY_LIGHT2                 = 37979,

    NPC_RAYNE                         = 29181,
    SPELL_REJUVENATION                = 20664,
    SPELL_STARFALL                    = 20687,
    SPELL_TRANQUILITY                 = 25817,
    SPELL_WRATH                       = 21807,

    NPC_DEFENDER_OF_THE_LIGHT         = 29174, // also does SPELL_HEROIC_LEAP 53625
    SPELL_HOLY_LIGHT1                 = 29427,
    SPELL_HOLY_STRIKE                 = 53643,
    SPELL_HOLY_WRATH                  = 53638,
    SPELL_UPPERCUT                    = 53629,

    NPC_RIMBLAT_EARTHSHATTER          = 29182,
    SPELL_CHAIN_HEAL                  = 33642,
    SPELL_THUNDER                     = 53630
};

struct Locations
{ 
    float x, y, z, o;
    uint32 id;
};

static Locations LightofDawnLoc[]=
{ 
    {2281.335f, -5300.409f, 85.170f, 0},     // 0 Tirion Fordring loc
    {2283.896f, -5287.914f, 83.066f, 1.55f},  // 1 Tirion Fordring loc2
    {2281.461f, -5263.014f, 81.164f, 0},     // 2 Tirion charges
    {2262.277f, -5293.477f, 82.167f, 0},     // 3 Tirion run
    {2270.286f, -5287.73f,  82.262f, 0},     // 4 Tirion relocate
    {2269.511f, -5288.289f, 82.225f, 0},     // 5 Tirion forward
    {2265.547f, -5289.477f, 82.167f, 0},     // 6 Tirion runs to Darion
    {2270.286f, -5287.73f,  82.262f, 0},
    {2269.511f, -5288.289f, 82.225f, 0},
    {2273.205f, -5288.848f, 82.617f, 0},     // 9 Korfax loc1
    {2274.739f, -5287.926f, 82.684f, 0},     // 10 Korfax loc2
    {2253.673f, -5318.004f, 81.724f, 0},     // 11 Korfax kicked
    {2287.028f, -5309.644f, 87.253f, 0},     // 12 Maxwell loc1
    {2286.978f, -5308.025f, 86.83f, 0},      // 13 Maxwell loc2
    {2248.877f, -5307.586f, 82.166f, 0},     // 14 maxwell kicked
    {2278.58f,  -5316.933f, 88.319f, 0},     // 15 Eligor loc1
    {2278.535f, -5315.479f, 88.08f, 0},      // 16 Eligor loc2
    {2259.416f, -5304.505f, 82.149f, 0},     // 17 eligor kicked
    {2289.259f, -5280.355f, 82.112f, 0},     // 18 Koltira loc1
    {2289.02f,  -5281.985f, 82.207f, 0},     // 19 Koltira loc2
    {2273.289f, -5273.675f, 81.701f, 0},     // 20 Thassarian loc1
    {2273.332f, -5275.544f, 81.849f, 0},     // 21 Thassarian loc2
    {2281.198f, -5257.397f, 80.224f, 4.66f}, // 22 Alexandros loc1
    {2281.156f, -5259.934f, 80.647f, 0},     // 23 Alexandros loc2
    {2281.294f, -5281.895f, 82.445f, 1.35f}, // 24 Darion loc1
    {2281.093f, -5263.013f, 81.125f, 0},     // 25 Darion loc1
    {2281.313f, -5250.282f, 79.322f, 4.69f}, // 26 Lich King spawns
    {2281.523f, -5261.058f, 80.877f, 0},     // 27 Lich king move forwards
    {2272.709f, -5255.552f, 78.226f, 0},     // 28 Lich king kicked
    {2273.972f, -5257.676f, 78.862f, 0},     // 29 Lich king moves forward
    {2250.335f, -5330.409f, 81.995f, 0},     // 30 NPCs spawn point
    {2280.883f, -5322.627f, 88.715f, 1.721f}, // 31 Rayne
    {2269.213f, -5284.627f, 82.015f, 0.154f},// 32 Duke
    {2289.913f, -5274.627f, 81.875f, 3.754f},// 33 Leonid
    {2284.883f, -5316.627f, 88.515f, 1.721f},// 34 Earthshatter
};

struct MANGOS_DLL_DECL npc_highlord_darion_mograineAI : public npc_escortAI
{ 
    npc_highlord_darion_mograineAI(Creature *pCreature) : npc_escortAI(pCreature)
    {
        m_pMap = m_creature->GetMap();
        Reset();
    }

    Map *m_pMap;

    std::list<uint64> lTargetsList;
    std::list<GameObject*> lLightningsHList;
    std::list<uint64> lLightningsHGUIDsList;
    std::list<GameObject*> lLightningsVList;
    std::list<uint64> lLightningsVGUIDsList;

    float x, y, z, o;

    bool bIsBattle;
    bool bIsBattleOver;
    uint32 uiStep;
    uint32 uiPhase_timer;
    uint32 uiTirionAppearsTimer;
    uint32 uiHolyLightningTimer;
    uint32 uiPrologueStep;
    uint32 uiPrologueStepTimer;
    uint32 uiUpdateWorldTimer;
    uint32 uiEventStartCountdown;
    uint32 uiScourgeKilled;
    uint32 uiDefendersKilled;
    uint32 uiTotal_dawn;
    uint32 uiTotal_scourge;
    uint32 uiSummon_counter;

    // Darion Mograine
    uint32 uiAnti_magic_zone;
    uint32 uiDeath_strike;
    uint32 uiDeath_embrace;
    uint32 uiIcy_touch;
    uint32 uiUnholy_blight;
    uint32 uiFight_speech;
    uint32 uiSpawncheck;
    uint32 uiTargetcheck;

    // Dawn
    uint64 uiTirionGUID;
    uint64 uiAlexandrosGUID;
    uint64 uiDarionGUID;
    uint64 uiKorfaxGUID;
    uint64 uiMaxwellGUID;
    uint64 uiEligorGUID;
    uint64 uiLeonidGUID;
    uint64 uiDukeGUID;
    uint64 uiRayneGUID;
    uint64 uiEarthshatterGUID;
    uint64 uiDefenderGUID[ENCOUNTER_DEFENDER_NUMBER];

    // Death
    uint64 uiKoltiraGUID;
    uint64 uiOrbazGUID;
    uint64 uiThassarianGUID;
    uint64 uiLichKingGUID;
    uint64 uiAbominationGUID[ENCOUNTER_ABOMINATION_NUMBER];
    uint64 uiBehemothGUID[ENCOUNTER_BEHEMOTH_NUMBER];
    uint64 uiGhoulGUID[ENCOUNTER_GHOUL_NUMBER];
    uint64 uiWarriorGUID[ENCOUNTER_WARRIOR_NUMBER];

    // Misc
    uint64 uiDawnofLightGUID;

    void Reset()
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            lLightningsHList.clear();
            lLightningsHGUIDsList.clear();
            lLightningsVList.clear();
            lLightningsVGUIDsList.clear();

            bIsBattle = false;
            bIsBattleOver = false;
            
            uiStep = 0;
            uiPhase_timer = 3000;
            
            uiEventStartCountdown = 300000; // 5 minutes until fight begins
            uiUpdateWorldTimer = 1000;      // every second update world state: show remaining forces
            uiPrologueStep = 0;             // Prologue, Mograine says his speech 2 minutes before battle begins
            uiPrologueStepTimer = 10000;    // Mograine's speech before the battle

            uiTirionAppearsTimer = 20500;   // Tirion will appear when over 100 defenders will die
            uiHolyLightningTimer = 4000;    // and then lightnings start striking at all the scourge in the area

            uiScourgeKilled = 0;
            uiDefendersKilled = 0;
            uiTotal_dawn = ENCOUNTER_TOTAL_DAWN;
            uiTotal_scourge = ENCOUNTER_TOTAL_SCOURGE;
            uiSummon_counter = 0;

            lTargetsList.clear();

            uiDawnofLightGUID = 0;

            uiAnti_magic_zone = 1000 + rand()%5000;
            uiDeath_strike = 5000 + rand()%5000;
            uiDeath_embrace = 5000 + rand()%5000;
            uiIcy_touch = 5000 + rand()%5000;
            uiUnholy_blight = 5000 + rand()%5000;

            uiFight_speech = 15000;
            uiSpawncheck = 1000;
            uiTargetcheck = 10000;

            ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_STAND);
            m_creature->Mount(25279);
            m_creature->SetSpeedRate(MOVE_RUN, 1.0f);

            if (!m_pMap)
                return;

            if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiRayneGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiEarthshatterGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                pTemp->SetDeathState(JUST_DIED);
            if (Creature* pTemp = m_pMap->GetCreature(uiKoltiraGUID))
                pTemp->Respawn();
            if (Creature* pTemp = m_pMap->GetCreature(uiOrbazGUID))
                pTemp->Respawn();
            if (Creature* pTemp = m_pMap->GetCreature(uiThassarianGUID))
                pTemp->Respawn();

            uiTirionGUID = NULL;
            uiKorfaxGUID = NULL;
            uiMaxwellGUID = NULL;
            uiEligorGUID = NULL;
            uiLeonidGUID = NULL;
            uiDukeGUID = NULL;
            uiRayneGUID = NULL;
            uiEarthshatterGUID = NULL;
            uiKoltiraGUID = NULL;
            uiOrbazGUID = NULL;
            uiThassarianGUID = NULL;
            uiLichKingGUID = NULL;

            for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
            {
                if (Creature* pTemp = m_pMap->GetCreature(uiGhoulGUID[i]))
                    pTemp->SetDeathState(JUST_DIED);
                uiGhoulGUID[i] = 0;
            }
            for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
            {
                if (Creature* pTemp = m_pMap->GetCreature(uiWarriorGUID[i]))
                    pTemp->SetDeathState(JUST_DIED);
                uiWarriorGUID[i] = 0;
            }
            for(uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
            {
                if (Creature* pTemp = m_pMap->GetCreature(uiAbominationGUID[i]))
                   pTemp->SetDeathState(JUST_DIED);
                uiAbominationGUID[i] = 0;
            }
            for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
                uiBehemothGUID[i] = 0;
            for(uint8 i = 0; i < ENCOUNTER_DEFENDER_NUMBER; ++i)
            {
                if (Creature* pTemp = m_pMap->GetCreature(uiDefenderGUID[i]))
                    pTemp->SetDeathState(JUST_DIED);
                uiDefenderGUID[i] = 0;
            }
        }
    }

    void EnterEvadeIfOutOfCombatArea(const uint32 uiDiff) { return; }
    void EnterEvadeMode(){return;}

    void SetHoldState(bool bOnHold)
    {
        SetEscortPaused(bOnHold);
    }

    void WaypointReached(uint32 i)
    {
        if (!m_pMap)
            return;

        switch(i)
        {
            case 0:
                m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                SetHoldState(true);
                break;
            case 3:
                if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, GO_LIGHT_OF_DAWN, 150.0f)) // make dawn of light effect off
                {
                    uiDawnofLightGUID = pGo->GetGUID();
                    pGo->SetPhaseMask(0, true);
                }
                // hide lightnings
                GetGameObjectListWithEntryInGrid(lLightningsHList, m_creature, GO_HOLY_LIGHTNING_H, 150.0f); // make dawn of light effect off
                GetGameObjectListWithEntryInGrid(lLightningsVList, m_creature, GO_HOLY_LIGHTNING_V, 150.0f);
                for (std::list<GameObject*>::const_iterator i = lLightningsHList.begin(); i != lLightningsHList.end(); i++)
                {
                    if (*i)
                    {
                        lLightningsHGUIDsList.push_back((*i)->GetGUID() );
                        (*i)->SetPhaseMask(0, true);
                    }
                }
                for (std::list<GameObject*>::const_iterator i = lLightningsVList.begin(); i != lLightningsVList.end(); i++)
                {
                    if (*i)
                    {
                        lLightningsVGUIDsList.push_back((*i)->GetGUID() );
                        (*i)->SetPhaseMask(0, true);
                    }
                }
                SpawnNPC();
                uiDefendersKilled = 0;      // reset, because this is initial spawn of Light forces

                if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                    DoScriptText(SAY_LIGHT_OF_DAWN07, pTemp);
                if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                    DoScriptText(SAY_LIGHT_OF_DAWN08, pTemp);
                break;
            case 4:
                m_creature->CastSpell(m_creature, SPELL_HERO_AGGRO_AURA, true);
                if (Creature* pTemp = m_pMap->GetCreature(uiKoltiraGUID))
                {
                    pTemp->SetSpeedRate(MOVE_RUN, 1.0f);
                    pTemp->CastSpell(pTemp, SPELL_HERO_AGGRO_AURA, true);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiThassarianGUID))
                {
                    pTemp->SetSpeedRate(MOVE_RUN, 1.0f);
                    pTemp->CastSpell(pTemp, SPELL_HERO_AGGRO_AURA, true);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiOrbazGUID))
                {
                    pTemp->SetSpeedRate(MOVE_RUN, 1.0f);
                    pTemp->CastSpell(pTemp, SPELL_HERO_AGGRO_AURA, true);
                }
                break;
            case 5:
                NPCsChangeTarget();
                bIsBattle = true;
                SetHoldState(true);
                break;
            case 6:
                m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
                if (m_creature->HasAura(SPELL_THE_MIGHT_OF_MOGRAINE, EFFECT_INDEX_0))
                    m_creature->RemoveAurasDueToSpell(SPELL_THE_MIGHT_OF_MOGRAINE);
                m_creature->Unmount();
                m_creature->GetMotionMaster()->Clear();
                m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                DoCast(m_creature, SPELL_THE_LIGHT_OF_DAWN);
                break;
            case 7:
            {
                Creature* pTirion = m_pMap->GetCreature(uiTirionGUID);

                if (pTirion)
                {
                    pTirion->GetMotionMaster()->MovementExpired(false);
                    pTirion->Unmount();
                    pTirion->AddSplineFlag(SPLINEFLAG_WALKMODE);
                }

                DoScriptText(EMOTE_LIGHT_OF_DAWN02, m_creature);
                if (m_creature->HasAura(SPELL_THE_LIGHT_OF_DAWN, EFFECT_INDEX_0))
                    m_creature->RemoveAurasDueToSpell(SPELL_THE_LIGHT_OF_DAWN);
                if (Creature* pTemp = m_pMap->GetCreature(uiKoltiraGUID))
                {
                    if (pTemp->HasAura(SPELL_THE_LIGHT_OF_DAWN, EFFECT_INDEX_0))
                        pTemp->RemoveAurasDueToSpell(SPELL_THE_LIGHT_OF_DAWN);
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[19].x, LightofDawnLoc[19].y, LightofDawnLoc[19].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiThassarianGUID))
                {
                    if (pTemp->HasAura(SPELL_THE_LIGHT_OF_DAWN, EFFECT_INDEX_0))
                        pTemp->RemoveAurasDueToSpell(SPELL_THE_LIGHT_OF_DAWN);
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[21].x, LightofDawnLoc[21].y, LightofDawnLoc[21].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[10].x, LightofDawnLoc[10].y, LightofDawnLoc[10].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[13].x, LightofDawnLoc[13].y, LightofDawnLoc[13].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[16].x, LightofDawnLoc[16].y, LightofDawnLoc[16].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[10].x, LightofDawnLoc[10].y, LightofDawnLoc[10].z);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiEarthshatterGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetFacingToObject(m_creature);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetFacingToObject(m_creature);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetFacingToObject(m_creature);
                }
                if (Creature* pTemp = m_pMap->GetCreature(uiRayneGUID))
                {
                    pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    pTemp->SetFacingToObject(m_creature);
                }
                JumpToNextStep(10000);
                break;
            }
            case 8:
                m_creature->GetMotionMaster()->MovementExpired(false);
                if (Unit* pTemp = m_pMap->GetUnit(uiTirionGUID) )
                    pTemp->SetFacingToObject(m_creature);

                DoScriptText(SAY_LIGHT_OF_DAWN27, m_creature);
                ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_KNEEL);

                if (Creature* pTemp = m_pMap->GetCreature(uiKoltiraGUID))
                    pTemp->SetStandState(UNIT_STAND_STATE_KNEEL);
                if (Creature* pTemp = m_pMap->GetCreature(uiThassarianGUID))
                    pTemp->SetStandState(UNIT_STAND_STATE_KNEEL);
                SetHoldState(true);
                break;
            case 9:
                DoScriptText(SAY_LIGHT_OF_DAWN33, m_creature);
                SetHoldState(true);
                break;
            case 10:
                SetHoldState(true);
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SPECIALATTACK1H);
                JumpToNextStep(1000);
                break;
            case 11:
                SetHoldState(true);
                JumpToNextStep(2000);
                break;
            case 12:
                m_creature->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_UNEQUIP));
                if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                    m_creature->CastSpell(pTemp, SPELL_ASHBRINGER, true);
                SetHoldState(true);
                break;
            case 13:
                // respawns another Darion for quest turn in
                // 1 minute for turning the quest in
                m_creature->SummonCreature(NPC_HIGHLORD_DARION_MOGRAINE, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000);
                m_creature->ForcedDespawn();
                if (Creature *pTemp = m_pMap->GetCreature(uiKoltiraGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn();
                if (Creature *pTemp = m_pMap->GetCreature(uiOrbazGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn();
                if (Creature *pTemp = m_pMap->GetCreature(uiThassarianGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn();
                if (Creature *pTemp = m_pMap->GetCreature(uiTirionGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn(60000);
                if (Creature *pTemp = m_pMap->GetCreature(uiKorfaxGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn(60000);
                if (Creature *pTemp = m_pMap->GetCreature(uiMaxwellGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn(60000);
                if (Creature *pTemp = m_pMap->GetCreature(uiEligorGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn(60000);
                if (Creature *pTemp = m_pMap->GetCreature(uiRayneGUID) )
                    if (pTemp->isAlive() )
                        pTemp->ForcedDespawn(60000);
                // show lightnings again
                for (std::list<uint64>::const_iterator i = lLightningsHGUIDsList.begin(); i != lLightningsHGUIDsList.end(); i++)
                    if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                        pGO->SetPhaseMask(128, true);
                for (std::list<uint64>::const_iterator i = lLightningsVGUIDsList.begin(); i != lLightningsVGUIDsList.end(); i++)
                    if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                        pGO->SetPhaseMask(128, true);
                break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        npc_escortAI::UpdateAI(diff);

        if (!m_pMap)
            return;

        if (!bIsBattle)
        {
            if (uiPhase_timer < diff)
            {
                // ******* Before battle *****************************************************************
                switch(uiStep)
                {
                    case 0:  // countdown
                        if (uiUpdateWorldTimer <= diff)
                        {
                            UpdateWorldState(m_pMap, WORLD_STATE_SCOURGE_REMAINING, ENCOUNTER_TOTAL_SCOURGE);
                            UpdateWorldState(m_pMap, WORLD_STATE_LIGHT_REMAINING, ENCOUNTER_TOTAL_DAWN);
                            UpdateWorldState(m_pMap, WORLD_STATE_REMAINING_SHOW, 1);
                            uiUpdateWorldTimer = 1000;
                        }
                        else uiUpdateWorldTimer -= diff;
                        break;

                    case 1:  // prologue
                        if (uiPrologueStepTimer <= diff)
                        {
                            switch (uiPrologueStep)
                            {
                                case 0:
                                    UpdateWorldState(m_pMap, WORLD_STATE_COUNTDOWN_SHOW, 1);
                                    DoScriptText(SAY_LIGHT_OF_DAWN01, m_creature);
                                    uiPrologueStepTimer = 200000;
                                    uiPrologueStep++;
                                    break;
                                case 1:
                                    DoScriptText(SAY_LIGHT_OF_DAWN02, m_creature);
                                    uiPrologueStepTimer = 50000;
                                    uiPrologueStep++;
                                    break;
                                case 2:
                                    DoScriptText(SAY_LIGHT_OF_DAWN03, m_creature);
                                    JumpToNextStep(40000);
                                    break;
                            }
                        }
                        else uiPrologueStepTimer -= diff;

                        if (uiEventStartCountdown <= diff)
                        {
                            JumpToNextStep(3000);
                        }
                        uiEventStartCountdown -= diff;

                        UpdateWorldState(m_pMap, WORLD_STATE_COUNTDOWN, GetRemainingTimeInMinutes() );
                        break;

                    case 2: // Event begins. "Soldiers, death knights, minions of the darkness..."
                        UpdateWorldState(m_pMap, WORLD_STATE_COUNTDOWN_SHOW, 0);
                        UpdateWorldState(m_pMap, WORLD_STATE_EVENT_BEGIN, 1);
                        DoScriptText(SAY_LIGHT_OF_DAWN04, m_creature);
                        if (Creature* pKoltira = GetClosestCreatureWithEntry(m_creature, NPC_KOLTIRA_DEATHWEAVER, 50.0f))
                        {
                            uiKoltiraGUID = pKoltira->GetGUID();
                            pKoltira->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pKoltira->SetSpeedRate(MOVE_RUN, 1.6f);
                        }
                        if (Creature* pOrbaz = GetClosestCreatureWithEntry(m_creature, NPC_ORBAZ_BLOODBANE, 50.0f))
                        {
                            uiOrbazGUID = pOrbaz->GetGUID();
                            pOrbaz->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pOrbaz->SetSpeedRate(MOVE_RUN, 1.6f);
                        }
                        if (Creature* pThassarian = GetClosestCreatureWithEntry(m_creature, NPC_THASSARIAN, 50.0f))
                        {
                            uiThassarianGUID = pThassarian->GetGUID();
                            pThassarian->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pThassarian->SetSpeedRate(MOVE_RUN, 1.6f);
                        }
                        JumpToNextStep(9000);
                        break;

                    case 3: // rise!
                        DoScriptText(SAY_LIGHT_OF_DAWN05, m_creature);
                        JumpToNextStep(3000);
                        break;

                    case 4: // summon ghoul
                        // Dunno whats the summon spell, so workaround
                        DoCast(m_creature, 33271); // shack effect

                        x = (m_creature->GetPositionX()-20) + float(urand(3, 40) );
                        y = (m_creature->GetPositionY()-20) + float(urand(3, 40) );
                        z = m_creature->GetPositionZ();
                        o = m_creature->GetAngle(x, y) + M_PI_F;

                        if (m_pMap)
                            z = m_pMap->GetTerrain()->GetHeight(x, y, z, false);

                        if (uiSummon_counter < ENCOUNTER_GHOUL_NUMBER)
                        {
                            if (Creature* pTemp = m_creature->SummonCreature(NPC_ACHERUS_GHOUL, x, y, z, o, TEMPSUMMON_CORPSE_DESPAWN, 300000))
                            {
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->setFaction(2084);
                                uiGhoulGUID[uiSummon_counter] = pTemp->GetGUID();
                                uiSummon_counter++;
                                uiPhase_timer = 500;
                            }
                        }
                        else
                        {
                            uiSummon_counter = 0;
                            JumpToNextStep(0);
                        }
                        break;

                    case 5: // summon warriors
                        DoCast(m_creature, 33271); // shack effect

                        x = (m_creature->GetPositionX()-20) + float(urand(1, 40) );
                        y = (m_creature->GetPositionY()-20) + float(urand(1, 40) );
                        z = m_creature->GetPositionZ();
                        o = m_creature->GetAngle(x, y) + M_PI_F;

                        if (m_pMap)
                            z = m_pMap->GetTerrain()->GetHeight(x, y, z, false);

                        if (uiSummon_counter < ENCOUNTER_WARRIOR_NUMBER)
                        {
                            if (Creature* pTemp = m_creature->SummonCreature(NPC_WARRIOR_OF_THE_FROZEN_WASTES, x, y, z, o, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000))
                            {
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->setFaction(2084);
                                uiWarriorGUID[uiSummon_counter] = pTemp->GetGUID();
                                uiSummon_counter++;
                                uiPhase_timer = 500;
                            }
                        }
                        else
                        {
                            uiSummon_counter = 0;
                            JumpToNextStep(0);
                        }
                        break;

                    case 6: // find behemoths
                    {
                        std::list<Creature*> lBehemoths;
                        int8 j = 0;
                        GetCreatureListWithEntryInGrid(lBehemoths, m_creature, NPC_FLESH_BEHEMOTH, 150.0f);
                        for (std::list<Creature*>::const_iterator i = lBehemoths.begin(); i != lBehemoths.end(); i++)
                            if (*i)
                            {
                                uiBehemothGUID[j++] = (*i)->GetGUID();
                                (*i)->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                (*i)->SetSpeedRate(MOVE_RUN, 1.6f);
                                (*i)->CastSpell(*i, SPELL_HERO_AGGRO_AURA, true);
                            }
                        JumpToNextStep(0);
                        break;
                    }
                    case 7:
                        DoScriptText(SAY_LIGHT_OF_DAWN06, m_creature);
                        JumpToNextStep(8000);
                        break;

                    case 8: // charge cheer
                        for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
                            if (Creature* pTemp = m_pMap->GetCreature(uiGhoulGUID[i]))
                                pTemp->HandleEmote(EMOTE_ONESHOT_OMNICAST_GHOUL);
                        for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
                            if (Creature* pTemp = m_pMap->GetCreature(uiWarriorGUID[i]))
                                pTemp->HandleEmote(EMOTE_ONESHOT_BATTLEROAR);
                        for(uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
                            if (Creature* pTemp = m_pMap->GetCreature(uiAbominationGUID[i]))
                                pTemp->HandleEmote(EMOTE_ONESHOT_BATTLEROAR);
                        for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
                            if (Creature* pTemp = m_pMap->GetCreature(uiBehemothGUID[i]))
                                pTemp->HandleEmote(EMOTE_ONESHOT_BATTLEROAR);
                        JumpToNextStep(2000);
                        break;

                    case 9: // charge begins
                        m_creature->CastSpell(m_creature, SPELL_THE_MIGHT_OF_MOGRAINE, true);
                        SetHoldState(false);
                        ScourgeArmyCharge();

                        JumpToNextStep(5000);
                        break;

                    // ******* After battle *****************************************************************
                    case 11: // Tirion starts to speak
                        UpdateWorldState(m_pMap, WORLD_STATE_EVENT_BEGIN, 0);
                        UpdateWorldState(m_pMap, WORLD_STATE_COUNTDOWN_SHOW, 0);
                        UpdateWorldState(m_pMap, WORLD_STATE_REMAINING_SHOW, 0);

                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            pTemp->setFaction(m_creature->getFaction() );
                            pTemp->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pTemp->SetFacingToObject(m_creature);
                            DoScriptText(SAY_LIGHT_OF_DAWN28, pTemp);
                        }
                        JumpToNextStep(18000);
                        break;

                    case 12:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN29, pTemp);
                        JumpToNextStep(13000);
                        break;

                    case 13:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN30, pTemp);
                        JumpToNextStep(12000);
                        break;

                    case 14:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            pTemp->HandleEmote(EMOTE_ONESHOT_NONE);
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_STAND);
                        DoScriptText(SAY_LIGHT_OF_DAWN31, m_creature);
                        JumpToNextStep(6000);
                        break;

                    case 15: // summon gate
                        if (Creature* pTemp = m_creature->SummonCreature(NPC_HIGHLORD_ALEXANDROS_MOGRAINE, LightofDawnLoc[22].x, LightofDawnLoc[22].y, LightofDawnLoc[22].z, LightofDawnLoc[22].o, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000))
                        {
                            pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            pTemp->CastSpell(pTemp, SPELL_ALEXANDROS_MOGRAINE_SPAWN, true);
                            uiAlexandrosGUID = pTemp->GetGUID();
                        }
                        JumpToNextStep(4000);
                        break;

                    case 16: // Alexandros out
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID))
                        {
                            pTemp->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[23].x, LightofDawnLoc[23].y, LightofDawnLoc[23].z);
                            DoScriptText(SAY_LIGHT_OF_DAWN32, pTemp);
                        }
                        SetHoldState(false); // makes darion turns back
                        JumpToNextStep(5000);
                        break;

                    case 17:
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_KNEEL);
                        DoScriptText(SAY_LIGHT_OF_DAWN34, m_creature);
                        JumpToNextStep(2000);
                        break;

                    case 18: // Darion's spirit out, runs to father
                        if (Creature* pTemp = m_creature->SummonCreature(NPC_DARION_MOGRAINE, LightofDawnLoc[24].x, LightofDawnLoc[24].y, LightofDawnLoc[24].z, LightofDawnLoc[24].o, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000))
                        {
                            DoScriptText(SAY_LIGHT_OF_DAWN35, pTemp);
                            pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[25].x, LightofDawnLoc[25].y, LightofDawnLoc[25].z);
                            uiDarionGUID = pTemp->GetGUID();
                        }
                        JumpToNextStep(4000);
                        break;

                    case 19: // runs to father
                        if (Creature* pTemp = m_pMap->GetCreature(uiDarionGUID))
                            DoScriptText(EMOTE_LIGHT_OF_DAWN03, pTemp);
                        JumpToNextStep(4000);
                        break;

                    case 20:
                        JumpToNextStep(0);
                        break;

                    case 21:
                        if (Creature* pTemp = m_pMap->GetCreature(uiDarionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN36, pTemp);
                        JumpToNextStep(4000);
                        break;

                    case 22:
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN37, pTemp);
                        JumpToNextStep(8000);
                        break;

                    case 23:
                        if (Creature* pTemp = m_pMap->GetCreature(uiDarionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN38, pTemp);
                        JumpToNextStep(7000);
                        break;

                    case 24:
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN39, pTemp);

                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID)) // Tirion moves forward here
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[1].x, LightofDawnLoc[1].y, LightofDawnLoc[1].z);

                        JumpToNextStep(14000);
                        break;

                    case 25:
                        if (Creature* pTemp = m_pMap->GetCreature(uiDarionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN40, pTemp);
                        JumpToNextStep(10000);
                        break;

                    case 26:
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN41, pTemp);
                        JumpToNextStep(5000);
                        break;

                    case 27:
                        if (Creature* pTemp = m_pMap->GetCreature(uiDarionGUID))
                            pTemp->SetDeathState(JUST_DIED);
                        JumpToNextStep(23000);
                        break;

                    case 28:
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN42, pTemp);
                        JumpToNextStep(6000);
                        break;

                    case 29: // lich king spawns
                        if (Creature* pTemp = m_creature->SummonCreature(NPC_THE_LICH_KING, LightofDawnLoc[26].x, LightofDawnLoc[26].y, LightofDawnLoc[26].z, LightofDawnLoc[26].o, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000))
                        {
                            pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pTemp->CastSpell(pTemp, SPELL_ICEBOUND_VISAGE, true);
                            DoScriptText(SAY_LIGHT_OF_DAWN43, pTemp);
                            uiLichKingGUID = pTemp->GetGUID();
                            if (Unit* pAlex = m_pMap->GetUnit(uiAlexandrosGUID))
                                pTemp->CastSpell(pAlex, SPELL_SOUL_FEAST_ALEX, false);
                        }
                        JumpToNextStep(3000);
                        break;

                    case 30:
                        if (Creature* pTemp = m_pMap->GetCreature(uiAlexandrosGUID)) // remove him
                            pTemp->DealDamage(pTemp, pTemp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);

                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            pTemp->InterruptNonMeleeSpells(false);
                            DoScriptText(SAY_LIGHT_OF_DAWN45, pTemp);
                        }
                        JumpToNextStep(3000);
                        break;

                    case 31:
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_STAND);
                        DoScriptText(SAY_LIGHT_OF_DAWN44, m_creature);
                        JumpToNextStep(3000);
                        break;

                    case 32:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[27].x, LightofDawnLoc[27].y, LightofDawnLoc[27].z);
                        JumpToNextStep(5000);
                        break;

                    case 33: // Darion supports to jump to lich king here
// disable              if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
// because mangos           DoCast(m_creature, SPELL_MOGRAINE_CHARGE); // jumping charge
// doesn't make it look well, so workarounds, Darion charges, looks better
                        m_creature->SetSpeedRate(MOVE_RUN, 3.0f);
                        m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        SetHoldState(false);
                        JumpToNextStep(0);
                        break;

                    case 35: // Lich king counterattacks
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            pTemp->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
                            DoScriptText(SAY_LIGHT_OF_DAWN46, pTemp);
                        }
                        m_creature->SetSpeedRate(MOVE_RUN, 6.0f);
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_DEAD);
                        SetHoldState(false); // Darion got kicked by lich king
                        JumpToNextStep(0);
                        break;

                    case 37:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN47, pTemp);

                        JumpToNextStep(3000);
                        break;

                    case 38:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN48, pTemp);
                        JumpToNextStep(10000);
                        break;

                    case 39:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            pTemp->HandleEmote(EMOTE_ONESHOT_POINT);
                        JumpToNextStep(3000);
                        break;

                    case 40:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN49, pTemp);
                        JumpToNextStep(16000);
                        break;

                    case 41: // Lich king - Soul Feast
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            if (Creature* pTirion = m_pMap->GetCreature(uiTirionGUID))
                            {
                                ((Unit*)pTirion)->SetStandState(UNIT_STAND_STATE_KNEEL);
                                pTemp->CastSpell(pTirion, SPELL_SOUL_FEAST_TIRION, false);
                                DoScriptText(EMOTE_LIGHT_OF_DAWN04, pTirion);
                            }
                        }
                        JumpToNextStep(1500);
                        break;

                    case 42: // Maxwell yells for attack
                        {
                            float fLichPositionX, fLichPositionY, fLichPositionZ;
                            if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            {
                                fLichPositionX = pTemp->GetPositionX();
                                fLichPositionY = pTemp->GetPositionY() - 2.0f;
                                fLichPositionZ = pTemp->GetPositionZ();
                            }

                            Creature* pTemp;

                            if (pTemp = m_pMap->GetCreature(uiEarthshatterGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                            }
                            if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                                DoScriptText(SAY_LIGHT_OF_DAWN50, pTemp);
                            }
                            if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->HandleEmoteCommand(EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                            }
                            if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                            }
                            if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                            }
                            if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID))
                            {
                                pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
                                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                                pTemp->SetSpeedRate(MOVE_RUN, 2.0f);
                                pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY, fLichPositionZ);
                            }
                        }
                        JumpToNextStep(4500);
                        break;

                    case 43: // Apocalypse!
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            DoScriptText(SAY_LIGHT_OF_DAWN51, pTemp);
                            pTemp->CastSpell(pTemp, SPELL_APOCALYPSE, true);
                        }

                        if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[14].x, LightofDawnLoc[14].y, LightofDawnLoc[14].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[11].x, LightofDawnLoc[11].y, LightofDawnLoc[11].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[17].x, LightofDawnLoc[17].y, LightofDawnLoc[17].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiDefenderGUID[0]))
                        {
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x+rand()%10, LightofDawnLoc[0].y+rand()%10, LightofDawnLoc[0].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiEarthshatterGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x+urand(10, 20), LightofDawnLoc[0].y+urand(1, 10), LightofDawnLoc[0].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x+urand(10, 20), LightofDawnLoc[0].y+urand(1, 10), LightofDawnLoc[0].z);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 6.0f);
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_DEAD);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x+urand(10, 20), LightofDawnLoc[0].y+urand(1, 10), LightofDawnLoc[0].z);
                        }
                        JumpToNextStep(3000);
                        break;

                    case 44: // make some of them stand up
                        if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                        {
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_STAND);
                            pTemp->SetFacingToObject(m_creature);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                        {
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_STAND);
                            pTemp->SetFacingToObject(m_creature);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                        {
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_STAND);
                            pTemp->SetFacingToObject(m_creature);
                        }
                        DespawnNPC(uiLeonidGUID);
                        DespawnNPC(uiDukeGUID);
                        DespawnNPC(uiEarthshatterGUID);
                        JumpToNextStep(1000);
                        break;

                    case 45: //Darion stands up
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_KNEEL);
                        DoScriptText(SAY_LIGHT_OF_DAWN52, m_creature);
                        JumpToNextStep(5000);
                        break;

                    case 46: // "not today"
                        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
                        m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_STAND);
                        DoScriptText(SAY_LIGHT_OF_DAWN53, m_creature);
                        SetHoldState(false); // Darion throws sword after reaching waypoint
                        JumpToNextStep(4000);
                        break;

                    case 47: // Ashbringer rebirth
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_DEAD);
                        DoScriptText(EMOTE_LIGHT_OF_DAWN05, m_creature);
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            ((Unit*)pTemp)->SetStandState(UNIT_STAND_STATE_STAND);
                            pTemp->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_HIGHLORD_TIRION_FORDRING));
                            pTemp->CastSpell(pTemp, SPELL_REBIRTH_OF_THE_ASHBRINGER, false);
                        }
                        JumpToNextStep(1000);
                        break;

                    case 48: // Show the cleansing effect (dawn of light)
                        if (GameObject* pGo = m_pMap->GetGameObject(uiDawnofLightGUID))
                            pGo->SetPhaseMask(128, true);
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            if (pTemp->HasAura(SPELL_REBIRTH_OF_THE_ASHBRINGER, EFFECT_INDEX_0))
                                pTemp->RemoveAurasDueToSpell(SPELL_REBIRTH_OF_THE_ASHBRINGER);
                            pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pTemp->CastSpell(pTemp, SPELL_ASHBRINGER_NOVA, false);
                            DoScriptText(SAY_LIGHT_OF_DAWN54, pTemp);
                            pTemp->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                        }
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            pTemp->RemoveAurasDueToSpell(SELL_POST_APOCALYPSE);
                            pTemp->InterruptNonMeleeSpells(false);
                        }
                        JumpToNextStep(2000);
                        break;

                    case 49:
                        JumpToNextStep(3000);
                        break;

                    case 50:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN55, pTemp);
                        JumpToNextStep(3500);
                        break;

                    case 51:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN56, pTemp);
                        JumpToNextStep(1000);
                        break;

                    case 52: // Tiron charges
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            pTemp->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            pTemp->SetSpeedRate(MOVE_RUN, 3.0f); // workarounds, make Tirion still running
                            pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            //pTemp->CastSpell(pTemp, SPELL_TIRION_CHARGE, false); // jumping charge, doesn't work properly
                            // workaround
                            float fLichPositionX, fLichPositionY, fLichPositionZ;
                            if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            {
                                fLichPositionX = pTemp->GetPositionX();
                                fLichPositionY = pTemp->GetPositionY();
                                fLichPositionZ = pTemp->GetPositionZ();
                            }
                            pTemp->SetSpeedRate(MOVE_RUN, 3.0f);
                            pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pTemp->GetMotionMaster()->MovePoint(0, fLichPositionX, fLichPositionY-2.0f, fLichPositionZ);
                        }
                        JumpToNextStep(1500);
                        break;

                    case 53: // continue the workaround
                        if (Creature* pTirion = m_pMap->GetCreature(uiTirionGUID))
                            pTirion->HandleEmoteCommand(EMOTE_ONESHOT_SPECIALATTACK1H);

                        JumpToNextStep(500);
                        break;

                    case 54:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            if (Creature* pTirion = m_pMap->GetCreature(uiTirionGUID))
                                pTemp->KnockBackFrom(pTirion, 10.0f, 3.0f);

                        JumpToNextStep(1000);
                        break;

                    case 55:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN57, pTemp);

                        JumpToNextStep(5000);
                        break;

                    case 56:
                        JumpToNextStep(0);
                        break;

                    case 57:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN58, pTemp);
                        JumpToNextStep(6000);
                        break;

                    case 58:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                        {
                            DoScriptText(SAY_LIGHT_OF_DAWN59, pTemp);
                            pTemp->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                        }
                        JumpToNextStep(8000);
                        break;

                    case 59:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID))
                            pTemp->CastSpell(pTemp, SPELL_TELEPORT_VISUAL, false);
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID)) // Tirion runs to Darion
                        {
                            pTemp->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            pTemp->SetSpeedRate(MOVE_RUN, 1.0f);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[6].x, LightofDawnLoc[6].y, LightofDawnLoc[6].z);
                        }
                        JumpToNextStep(2500);
                        break;

                    case 60:
                        if (Creature* pTemp = m_pMap->GetCreature(uiLichKingGUID)) // Lich king disappears here
                            DespawnNPC(pTemp->GetGUID() );

                        JumpToNextStep(5000);
                        break;

                    case 61:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            DoScriptText(SAY_LIGHT_OF_DAWN60, pTemp);
                            pTemp->CastSpell(m_creature, SPELL_LAY_ON_HANDS, true);
                        }
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_KNEEL);
                        JumpToNextStep(3000);
                        break;

                    case 62:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            pTemp->AddSplineFlag(SPLINEFLAG_WALKMODE);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[7].x, LightofDawnLoc[7].y, LightofDawnLoc[7].z);
                            m_creature->SetFacingToObject(pTemp);
                        }
                        JumpToNextStep(5500);
                        break;

                    case 63:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        {
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[8].x, LightofDawnLoc[8].y, LightofDawnLoc[8].z);
                            DoScriptText(SAY_LIGHT_OF_DAWN61, pTemp);
                        }
                        JumpToNextStep(15000);
                        break;

                    case 64:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN62, pTemp);
                        JumpToNextStep(7000);
                        break;

                    case 65:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN63, pTemp);
                        JumpToNextStep(10000);
                        break;

                    case 66:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN64, pTemp);
                        JumpToNextStep(11000);
                        break;

                    case 67:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN65, pTemp);
                        JumpToNextStep(10000);
                        break;

                    case 68:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN66, pTemp);
                        JumpToNextStep(7000);
                        break;

                    case 69:
                        if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                            DoScriptText(SAY_LIGHT_OF_DAWN67, pTemp);
                        JumpToNextStep(8000);
                        break;

                    case 70:
                        DoScriptText(SAY_LIGHT_OF_DAWN68, m_creature);
                        ((Unit*)m_creature)->SetStandState(UNIT_STAND_STATE_STAND);
                        JumpToNextStep(10000);
                        break;

                    case 71:
                        // search players with in 50 yards for quest credit
                        if (m_pMap)
                        {
                            Map::PlayerList const &PlayerList = m_pMap->GetPlayers();
                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                    if (i->getSource()->isAlive() && m_creature->IsWithinDistInMap(i->getSource(), 50))
                                        i->getSource()->CastSpell(i->getSource(), SPELL_THE_LIGHT_OF_DAWN_Q, false);
                            }
                        }
                        JumpToNextStep(1000);
                        break;

                    case 72:
                        SetHoldState(false); // Escort ends
                        JumpToNextStep(0);
                        break;
                }

            }else uiPhase_timer -= diff;
        }

        // ******* During battle *****************************************************************
        else
        {
            if (uiAnti_magic_zone < diff)
            {
                DoCast(m_creature, SPELL_ANTI_MAGIC_ZONE1);
                uiAnti_magic_zone = 25000 + urand(1, 5000);
            }else uiAnti_magic_zone -= diff;

            if (uiDeath_strike < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_DEATH_STRIKE);
                uiDeath_strike = 15000 + urand(1, 10000);
            }else uiDeath_strike -= diff;

            if (uiDeath_embrace < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_DEATH_EMBRACE);
                uiDeath_embrace = 50000 + urand(1, 10000);
            }else uiDeath_embrace -= diff;

            if (uiIcy_touch < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_ICY_TOUCH1);
                uiIcy_touch = 5000 + urand(1, 10000);
            }else uiIcy_touch -= diff;

            if (uiUnholy_blight < diff)
            {
                DoCast(m_creature->getVictim(), SPELL_UNHOLY_BLIGHT);
                uiUnholy_blight = 10000 + urand(1, 10000);
            }else uiUnholy_blight -= diff;

            if (uiFight_speech < diff)
            {
                switch(urand(0, 15) )
                {
                    case 0: DoScriptText(SAY_LIGHT_OF_DAWN09, m_creature);break;
                    case 1: DoScriptText(SAY_LIGHT_OF_DAWN10, m_creature);break;
                    case 2: DoScriptText(SAY_LIGHT_OF_DAWN11, m_creature);break;
                    case 3: DoScriptText(SAY_LIGHT_OF_DAWN12, m_creature);break;
                    case 4: DoScriptText(SAY_LIGHT_OF_DAWN13, m_creature);break;
                    case 5: DoScriptText(SAY_LIGHT_OF_DAWN14, m_creature);break;
                    case 6: DoScriptText(SAY_LIGHT_OF_DAWN15, m_creature);break;
                    case 7: DoScriptText(SAY_LIGHT_OF_DAWN16, m_creature);break;
                    case 8: DoScriptText(SAY_LIGHT_OF_DAWN17, m_creature);break;
                    case 9: DoScriptText(SAY_LIGHT_OF_DAWN18, m_creature);break;
                    case 10: DoScriptText(SAY_LIGHT_OF_DAWN19, m_creature);break;
                    case 11: DoScriptText(SAY_LIGHT_OF_DAWN20, m_creature);break;
                    case 12: DoScriptText(SAY_LIGHT_OF_DAWN21, m_creature);break;
                    case 13: DoScriptText(SAY_LIGHT_OF_DAWN22, m_creature);break;
                    case 14: DoScriptText(SAY_LIGHT_OF_DAWN23, m_creature);break;
                    case 15: DoScriptText(SAY_LIGHT_OF_DAWN24, m_creature);break;
                }
                uiFight_speech = 15000 + rand()%5000;
            }else uiFight_speech -= diff;

            // Check spawns
            if (uiSpawncheck < diff)
            {
                SpawnNPC();
                UpdateWorldState(m_pMap, WORLD_STATE_SCOURGE_REMAINING, ENCOUNTER_TOTAL_SCOURGE - uiScourgeKilled);
                UpdateWorldState(m_pMap, WORLD_STATE_LIGHT_REMAINING, ENCOUNTER_TOTAL_DAWN - uiDefendersKilled);
                if (uiDefendersKilled > 120)
                    bIsBattleOver = true;
                // check Might of Mograine (it sometimes fades ;/)
                if (!m_creature->HasAura(SPELL_THE_MIGHT_OF_MOGRAINE, EFFECT_INDEX_0) )
                    m_creature->CastSpell(m_creature, SPELL_THE_MIGHT_OF_MOGRAINE, true);

                uiSpawncheck = 1000;
            }
            else uiSpawncheck -= diff;

            // Check targets
            if (uiTargetcheck < diff)
            {
                NPCsChangeTarget();
                uiTargetcheck = 10000;
            }
            else uiTargetcheck -= diff;

            // Battle end
            if (bIsBattleOver)
            {
                if (uiTirionAppearsTimer < diff + 20000)
                {
                    if (!uiTirionGUID)
                    {
                        if (Creature* pTemp = m_creature->SummonCreature(NPC_HIGHLORD_TIRION_FORDRING, LightofDawnLoc[0].x - 50.0f, LightofDawnLoc[0].y + 40.0f, LightofDawnLoc[30].z - 5.0f, 1.528f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 900000))
                        {
                            DoScriptText(SAY_LIGHT_OF_DAWN25, pTemp);
                            uiTirionGUID = pTemp->GetGUID();
                            pTemp->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0, uint32(EQUIP_UNEQUIP));
                            pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            pTemp->setFaction(2089);
                            pTemp->Mount(8469);
                            pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x, LightofDawnLoc[0].y, LightofDawnLoc[0].z);
                        }
                    }
                    // lightnings appear
                    for (std::list<uint64>::const_iterator i = lLightningsHGUIDsList.begin(); i != lLightningsHGUIDsList.end(); i++)
                        if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                            pGO->SetPhaseMask(128, true);
                    for (std::list<uint64>::const_iterator i = lLightningsVGUIDsList.begin(); i != lLightningsVGUIDsList.end(); i++)
                        if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                            pGO->SetPhaseMask(128, true);
                }
                if (uiHolyLightningTimer < diff)
                {
                    uiHolyLightningTimer = 4000;
                    if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                        pTemp->CastSpell(pTemp, SPELL_DAWN_OF_LIGHT, true);
                }
                else uiHolyLightningTimer -= diff;

                if (uiTirionAppearsTimer < diff)
                {
                    bIsBattle = false;
                    uiTirionAppearsTimer = 300000;

                    // lightnings disappear
                    for (std::list<uint64>::const_iterator i = lLightningsHGUIDsList.begin(); i != lLightningsHGUIDsList.end(); i++)
                        if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                            pGO->SetPhaseMask(0, true);
                    for (std::list<uint64>::const_iterator i = lLightningsVGUIDsList.begin(); i != lLightningsVGUIDsList.end(); i++)
                        if (GameObject *pGO = m_pMap->GetGameObject(*i) )
                            pGO->SetPhaseMask(0, true);

                    m_creature->RemoveAllAuras();
                    m_creature->DeleteThreatList();
                    m_creature->CombatStop(true);
                    m_creature->InterruptNonMeleeSpells(false);
                    m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);

                    SpawnNPC();

                    for(uint8 i = 0; i < ENCOUNTER_DEFENDER_NUMBER; ++i)
                        DespawnNPC(uiDefenderGUID[i]);
                    for(uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
                        DespawnNPC(uiAbominationGUID[i]);
                    for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
                        if (Creature *pTmp = m_pMap->GetCreature(uiBehemothGUID[i]) )
                            pTmp->ForcedDespawn();
                    for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
                        DespawnNPC(uiGhoulGUID[i]);
                    for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
                        DespawnNPC(uiWarriorGUID[i]);

                    if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[9].x, LightofDawnLoc[9].y, LightofDawnLoc[9].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[12].x, LightofDawnLoc[12].y, LightofDawnLoc[12].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[15].x, LightofDawnLoc[15].y, LightofDawnLoc[15].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiEarthshatterGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[34].x, LightofDawnLoc[34].y, LightofDawnLoc[34].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[33].x, LightofDawnLoc[33].y, LightofDawnLoc[33].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[32].x, LightofDawnLoc[32].y, LightofDawnLoc[32].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiRayneGUID))
                    {
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[31].x, LightofDawnLoc[31].y, LightofDawnLoc[31].z);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiOrbazGUID))
                    {
                        DoScriptText(EMOTE_LIGHT_OF_DAWN01, pTemp);
                        pTemp->ForcedDespawn();
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiKoltiraGUID))
                    {
                        pTemp->GetMotionMaster()->MovementExpired(true);
                        pTemp->Unmount();
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[18].x, LightofDawnLoc[18].y, LightofDawnLoc[18].z);
                        pTemp->CastSpell(pTemp, SPELL_THE_LIGHT_OF_DAWN, false);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiThassarianGUID))
                    {
                        pTemp->GetMotionMaster()->MovementExpired(true);
                        pTemp->Unmount();
                        pTemp->RemoveAllAuras();
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[20].x, LightofDawnLoc[20].y, LightofDawnLoc[20].z);
                        pTemp->CastSpell(pTemp, SPELL_THE_LIGHT_OF_DAWN, false);
                    }
                    if (Creature* pTemp = m_pMap->GetCreature(uiTirionGUID))
                    {
                        pTemp->CombatStop(true);
                        pTemp->AttackStop();
                        pTemp->DeleteThreatList();
                        pTemp->InterruptNonMeleeSpells(false);
                        pTemp->GetMotionMaster()->MovementExpired(false);
                        pTemp->GetMotionMaster()->MovePoint(0, LightofDawnLoc[0].x, LightofDawnLoc[0].y + 3.0f, LightofDawnLoc[0].z - 0.5f);
                        DoScriptText(SAY_LIGHT_OF_DAWN26, pTemp);
                    }
                    m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                    SetHoldState(false);

                }
                else uiTirionAppearsTimer -= diff;

                DoMeleeAttackIfReady();
            }
        }
    }

    /************* HELPERS *************/

    void JumpToNextStep(uint32 uiTimer)
    {
        uiPhase_timer = uiTimer;
        uiStep++;
    }

    void ScourgeArmyCharge()
    {
        if (!m_pMap)
            return;

        Creature *pTemp;
        ShuffleTargetsList();
        std::list<uint64>::const_iterator target = lTargetsList.begin();

        for (uint8 i = 0; i < 3; i++)
        {
            uint64 guid = 0;
            switch (i)
            {
               case 0: guid = uiKoltiraGUID;   break;
               case 1: guid = uiThassarianGUID;break;
               case 2: guid = uiOrbazGUID;     break;
            }
            if (Creature* pTemp = m_pMap->GetCreature(guid) )
            {
                pTemp->SetSpeedRate(MOVE_RUN, 1.6f);
                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);    
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 100) )/10.0f, pTemp->GetAngle(m_creature) );
            }
        }
        for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiGhoulGUID[i]))
            {
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 150) )/10.0f, pTemp->GetAngle(m_creature) );
                SetRespawnPoint(pTemp);
            }
        for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiWarriorGUID[i]))
            {
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 150) )/10.0f, pTemp->GetAngle(m_creature) );
                SetRespawnPoint(pTemp);
            }
        for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiBehemothGUID[i]))
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 100) )/10.0f, pTemp->GetAngle(m_creature) );
    }

    void SwapAggro(Unit *death, Unit *dawn)
    {
        dawn->DeleteThreatList();
        ((Creature*)dawn)->AddThreat(death, 100000.0f);
        ((Creature*)death)->AI()->AttackStart(dawn);
        ((Creature*)death)->AddThreat(dawn, 100000.0f);
    }

    void NPCsChangeTarget()
    {
        if (!m_pMap)
            return;

        // non-summoned units follow Darion - don't move targeted home
        for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
            if (Creature *pTemp = m_pMap->GetCreature(uiBehemothGUID[i]))
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 150) )/10.0f, pTemp->GetAngle(m_creature) );
        for (uint8 i = 0; i < 3; i++)
        {
            uint64 guid = 0;
            switch (i)
            {
               case 0: guid = uiKoltiraGUID;   break;
               case 1: guid = uiThassarianGUID;break;
               case 2: guid = uiOrbazGUID;     break;
            }
            if (Creature* pTemp = m_pMap->GetCreature(guid) )
            {
                pTemp->SetSpeedRate(MOVE_RUN, 1.6f);
                pTemp->RemoveSplineFlag(SPLINEFLAG_WALKMODE);    
                pTemp->GetMotionMaster()->MoveFollow(m_creature, float(urand(30, 150) )/10.0f, pTemp->GetAngle(m_creature) );
            }
        }

        // swapping aggro so the battle would look more dynamic
        Creature *pTemp;
        ShuffleTargetsList();
        std::list<uint64>::const_iterator target = lTargetsList.begin();

        DoResetThreat();
        if (Unit *pVictim = m_pMap->GetCreature(*target++) )
            SwapAggro(m_creature, pVictim);

        for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiGhoulGUID[i]))
            {
                pTemp->DeleteThreatList();
                if (Unit *pVictim = m_pMap->GetCreature(*target++) )
                    SwapAggro(pTemp, pVictim);
                else
                    pTemp->GetMotionMaster()->MoveConfused();
            }
        for(uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiAbominationGUID[i]))
            {
                pTemp->DeleteThreatList();
                if (Unit *pVictim = m_pMap->GetCreature(*target++) )
                    SwapAggro(pTemp, pVictim);
                else
                    pTemp->GetMotionMaster()->MoveConfused();
            }
        for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
            if (pTemp = m_pMap->GetCreature(uiWarriorGUID[i]))
            {
                pTemp->DeleteThreatList();
                if (Unit *pVictim = m_pMap->GetCreature(*target++) )
                    SwapAggro(pTemp, pVictim);
                else
                    pTemp->GetMotionMaster()->MoveConfused();
            }
    }

    void ShuffleTargetsList()
    {
        // gather all hostile units to the list and shuffle it a little, but clear it first
        lTargetsList.clear();

        if (!m_pMap)
            return;

        uint8 j;

        j = urand(0, ENCOUNTER_DEFENDER_NUMBER - 1);
        for(uint8 i = 0; i < ENCOUNTER_DEFENDER_NUMBER; ++i)
        {
            if (Creature* pTemp = m_pMap->GetCreature(uiDefenderGUID[j]) )
                lTargetsList.push_back(pTemp->GetGUID() );
            j = ++j % ENCOUNTER_DEFENDER_NUMBER;
        }
        if (Creature* pTemp = m_pMap->GetCreature(uiLeonidGUID) )
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiDukeGUID) )
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiMaxwellGUID))
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiEarthshatterGUID) )
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiEligorGUID))
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiKorfaxGUID))
            lTargetsList.push_back(pTemp->GetGUID() );
        if (Creature* pTemp = m_pMap->GetCreature(uiRayneGUID))
            lTargetsList.push_back(pTemp->GetGUID() );
    }

    void SetRespawnPoint(Creature *pCreature)
    {
        if (!pCreature)
            return;

        float x, y, z, o;

        x = LightofDawnLoc[0].x;
        y = LightofDawnLoc[0].y;
        z = LightofDawnLoc[0].z;
        o = float(urand(0, 628)/100.0f);

        GetNearRandomPoint(x, y, z, 30);

        pCreature->SetSummonPoint(x, y, z, o);
    }

    void GetNearRandomPoint(float &x, float &y, float &z, uint8 radius)
    {
        x += float(urand(0, radius) );
        y += float(urand(0, radius) );
        if (m_pMap)
           z = m_pMap->GetTerrain()->GetHeight(x, y, z, false);
    }

    uint64 DoSpawnNPC(uint32 uiEntry, bool bDarkSide)
    {
        float x, y, z;
        uint32 uiFaction = bDarkSide ? 2084 : 2089;

        x = LightofDawnLoc[30].x + float(urand(1, 60) );
        y = LightofDawnLoc[30].y + float(urand(1, 60) );
        z = LightofDawnLoc[0].z + 1.0f;

        if (m_pMap)
            z = m_pMap->GetTerrain()->GetHeight(x, y, z, false);

        if (Creature *pTemp = m_creature->SummonCreature(uiEntry, x, y, z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 900000) )
        {
            pTemp->setFaction(uiFaction);
            if (uiEntry == NPC_DEFENDER_OF_THE_LIGHT)
                pTemp->SetDisplayId(26057 + urand(0, 1));
            if (bDarkSide)
                uiScourgeKilled++;
            else
                uiDefendersKilled++;

            return pTemp->GetGUID();
        }

        return 0;
    }

    void SpawnNPC()
    {
        if (!m_pMap)
            return;

        Creature* pTemp = NULL;

        // Death
        for(uint8 i = 0; i < ENCOUNTER_GHOUL_NUMBER; ++i)
            if (!(pTemp = m_pMap->GetCreature(uiGhoulGUID[i]) ) )
                uiGhoulGUID[i] = DoSpawnNPC(NPC_ACHERUS_GHOUL, true);
        for(uint8 i = 0; i < ENCOUNTER_ABOMINATION_NUMBER; ++i)
            if (!(pTemp = m_pMap->GetCreature(uiAbominationGUID[i])) )
                uiAbominationGUID[i] = DoSpawnNPC(NPC_RAMPAGING_ABOMINATION, true);
        for(uint8 i = 0; i < ENCOUNTER_WARRIOR_NUMBER; ++i)
            if (!(pTemp = m_pMap->GetCreature(uiWarriorGUID[i])) )
                uiWarriorGUID[i] = DoSpawnNPC(NPC_WARRIOR_OF_THE_FROZEN_WASTES, true);
        for(uint8 i = 0; i < ENCOUNTER_BEHEMOTH_NUMBER; ++i)
            if (!(pTemp = m_pMap->GetCreature(uiBehemothGUID[i])) )
                uiBehemothGUID[i] = DoSpawnNPC(NPC_FLESH_BEHEMOTH, true);

        // Dawn
        for(uint8 i = 0; i < ENCOUNTER_DEFENDER_NUMBER; ++i)
            if (!(pTemp = m_pMap->GetCreature(uiDefenderGUID[i])) )
            {
                uiDefenderGUID[i] = DoSpawnNPC(NPC_DEFENDER_OF_THE_LIGHT, false);
                if (Creature *pTmp = m_pMap->GetCreature(uiDefenderGUID[i]) )
                    m_creature->SetInCombatWith(pTmp);
            }
        if (!(pTemp = m_pMap->GetCreature(uiEarthshatterGUID)) )
        {
            uiEarthshatterGUID = DoSpawnNPC(NPC_RIMBLAT_EARTHSHATTER, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiEarthshatterGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiKorfaxGUID) ) )
        {
            uiKorfaxGUID = DoSpawnNPC(NPC_KORFAX_CHAMPION_OF_THE_LIGHT, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiKorfaxGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiMaxwellGUID) ) )
        {
            uiMaxwellGUID = DoSpawnNPC(NPC_LORD_MAXWELL_TYROSUS, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiMaxwellGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiEligorGUID) ) )
        {
            uiEligorGUID = DoSpawnNPC(NPC_COMMANDER_ELIGOR_DAWNBRINGER, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiEligorGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiRayneGUID) ) )
        {
            uiRayneGUID = DoSpawnNPC(NPC_RAYNE, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiRayneGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiDukeGUID) ) )
        {
            uiDukeGUID = DoSpawnNPC(NPC_DUKE_NICHOLAS_ZVERENHOFF, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiDukeGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
        if (!(pTemp = m_pMap->GetCreature(uiLeonidGUID) ) )
        {
            uiLeonidGUID = DoSpawnNPC(NPC_LEONID_BARTHALOMEW_THE_REVERED, false);
            if (Creature *pTmp = m_pMap->GetCreature(uiLeonidGUID) )
                m_creature->SetInCombatWith(pTmp);
        }
    }

    void DespawnNPC(uint64 uiGUID)
    {
        if (!m_pMap)
            return;

        if (Creature* pTemp = m_pMap->GetCreature(uiGUID))
            if (pTemp->isAlive())
            {
                pTemp->SetVisibility(VISIBILITY_OFF);
                pTemp->DealDamage(pTemp, pTemp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
    }

    uint32 GetRemainingTimeInMinutes()
    {
        return uiEventStartCountdown ? (uiEventStartCountdown - 1) / (MINUTE * IN_MILLISECONDS) + 1 : 0;
    }

    void UpdateWorldState(Map *map, uint32 uiStateId, uint32 uiStateData)
    {
        if (!map)
        {
            debug_log("SD2: UpdateWorldState attempt send data but no map found.");
            return;
        }

        Map::PlayerList const& lPlayers = map->GetPlayers();

        if (!lPlayers.isEmpty())
        {
            for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                if (Player* pPlayer = itr->getSource())
                    if (pPlayer->GetQuestStatus(12801) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->SendUpdateWorldState(uiStateId, uiStateData);
        }
        else
            debug_log("SD2: DoUpdateWorldState attempt send data but no players in map.");
    }
};
bool GossipHello_npc_highlord_darion_mograine(Player* pPlayer, Creature* pCreature)
{ 
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu( pCreature->GetGUID() );

    if (pPlayer->GetQuestStatus(12801) == QUEST_STATUS_INCOMPLETE && pCreature->GetPositionX() > 2300.0f)
        pPlayer->ADD_GOSSIP_ITEM( 0, "I am ready, Highlord. Let the siege of Light's Hope begin!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_highlord_darion_mograine(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{ 
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            ((npc_highlord_darion_mograineAI*)pCreature->AI())->uiStep = 1;
            ((npc_highlord_darion_mograineAI*)pCreature->AI())->Start(true, false, false, pPlayer->GetGUID());
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            break;
    }
    return true;
}

/*######
## npc orbaz, koltira, tassarian
######*/
struct MANGOS_DLL_DECL npc_koltira_orbaz_tassarian_dawn_of_lightAI : public ScriptedAI
{ 
    npc_koltira_orbaz_tassarian_dawn_of_lightAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }
    
    uint32 uiIcyTouchTimer;
    uint32 uiBloodStrikeTimer;
    uint32 uiPlagueStrikeTimer;

    void Reset()
    {
        uiIcyTouchTimer = urand(10000, 20000);
        uiBloodStrikeTimer = urand(10000, 20000);
        uiPlagueStrikeTimer = urand(10000, 20000);
    }

    bool EnterEvadeIfOutOfCombatArea(const uint32 uiDiff)
    {
        m_creature->GetMotionMaster()->MoveIdle();
        return false;
    }
    void EnterEvadeMode()
    {
        m_creature->GetMotionMaster()->MoveIdle();
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget() )
            return;

        if (uiIcyTouchTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_ICY_TOUCH);
            uiIcyTouchTimer = urand(10000, 20000);
        }
        else uiIcyTouchTimer -= uiDiff;

        if (uiBloodStrikeTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_BLOOD_STRIKE);
            uiBloodStrikeTimer = urand(10000, 20000);
        }
        else uiBloodStrikeTimer -= uiDiff;

        if (uiPlagueStrikeTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_PLAGUE_STRIKE1);
            uiPlagueStrikeTimer = urand(10000, 20000);
        }
        else uiPlagueStrikeTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## Acherus Ghoul (29219)
######*/
struct MANGOS_DLL_DECL mob_acherus_ghoulAI : public ScriptedAI
{
    mob_acherus_ghoulAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsReady      = false;
        m_bIsSpawned    = false;
        m_bIsInBattle   = (m_creature->GetPositionX() < 2300.0f) ? true : false;

        m_pMap = m_creature->GetMap();

        Reset();
    }

    Map *m_pMap;

    uint32 m_uiReadyTimer;
    uint32 m_uiGhoulplosionTimer;

    bool m_bIsReady;
    bool m_bIsSpawned;
    bool m_bIsInBattle;

    void EnterEvadeIfOutOfCombatArea(const uint32 uiDiff) { return; }

    void Reset()
    {
        m_uiReadyTimer  = 4000;
        m_uiGhoulplosionTimer = 30000;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsReady)
            return;

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void AttackStart(Unit *pWho)
    {
        if (!m_bIsReady)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if (!m_bIsReady)
        {
            if (!m_bIsSpawned)
            {
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                m_bIsSpawned = true;
            }

            if (m_uiReadyTimer <= uiDiff)
                m_bIsReady = true;
            else m_uiReadyTimer -= uiDiff;

            return;
        }

        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget() )
        {
            if (m_bIsInBattle && m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != CONFUSED_MOTION_TYPE)
                    m_creature->GetMotionMaster()->MoveConfused();

            return;
        }

        if (m_uiGhoulplosionTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_GHOULPLOSION);
            m_uiGhoulplosionTimer = 30000;
        }
        else m_uiGhoulplosionTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_warrior_of_the_frozen_wastes (53631)
######*/
struct MANGOS_DLL_DECL mob_warrior_of_the_frozen_wastesAI : public ScriptedAI
{
    mob_warrior_of_the_frozen_wastesAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsReady      = false;
        m_bIsSpawned    = false;
        m_bIsInBattle   = (m_creature->GetPositionX() < 2300.0f) ? true : false;

        Reset();
    }

    uint32 m_uiReadyTimer;
    uint32 m_uiCleaveTimer;

    bool m_bIsReady;
    bool m_bIsSpawned;
    bool m_bIsInBattle;

    void EnterEvadeIfOutOfCombatArea(const uint32 uiDiff) { return; }

    void Reset()
    {
        m_uiReadyTimer  = 4000;
        m_uiCleaveTimer = urand(3000, 5000);
    }

    void AttackStart(Unit *pWho)
    {
        if (!m_bIsReady)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsReady)
            return;

        CreatureAI::MoveInLineOfSight(pWho);
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if (!m_bIsReady)
        {
            if (!m_bIsSpawned)
            {
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                m_bIsSpawned = true;
            }

            if (m_uiReadyTimer <= uiDiff)
                m_bIsReady = true;
            else m_uiReadyTimer -= uiDiff;

            return;
        }

        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget() )
        {
            if (m_bIsInBattle && m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != CONFUSED_MOTION_TYPE)
                    m_creature->GetMotionMaster()->MoveConfused();

            return;
        }

        if (m_uiCleaveTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
            m_uiCleaveTimer = urand(13000, 15000);
        }
        else m_uiCleaveTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_highlord_darion_mograine(Creature* pCreature)
{ 
     return new npc_highlord_darion_mograineAI(pCreature);
}

CreatureAI* GetAI_npc_koltira_orbaz_tassarian_dawn_of_light(Creature* pCreature)
{ 
     return new npc_koltira_orbaz_tassarian_dawn_of_lightAI (pCreature);
}

CreatureAI* GetAI_mob_warrior_of_the_frozen_wastes(Creature* pCreature)
{
    return new mob_warrior_of_the_frozen_wastesAI(pCreature);
}

CreatureAI* GetAI_mob_acherus_ghoul(Creature* pCreature)
{
    return new mob_acherus_ghoulAI(pCreature);
};

/*######
## Scarlet Ghoul (The Gift That Keeps On Giving
######*/

enum
{
    SPELL_HARVESTER_PING_DUMMY  = 52514,
    ENTRY_GOTHIK                = 28658,

    SAY_SCARLET_GHOUL_SPAWN1    = -1609286,
    SAY_SCARLET_GHOUL_SPAWN2    = -1609285,
    SAY_SCARLET_GHOUL_SPAWN3    = -1609284,
    SAY_SCARLET_GHOUL_SPAWN4    = -1609283,
    SAY_SCARLET_GHOUL_SPAWN5    = -1609282,
    SAY_SCARLET_GHOUL_SPAWN6    = -1609281,

    SAY_SCARLET_GOTHIK1         = -1609280,
    SAY_SCARLET_GOTHIK2         = -1609279,
    SAY_SCARLET_GOTHIK3         = -1609278,
    SAY_SCARLET_GOTHIK4         = -1609277,
    SAY_SCARLET_GOTHIK5         = -1609276,
};

struct MANGOS_DLL_DECL mob_scarlet_ghoulAI : public ScriptedAI
{
    mob_scarlet_ghoulAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsSpawned = false;
        fDist = (float)urand(1, 5);
        m_uiCreatorGUID = m_creature->GetCreatorGuid().GetRawValue();
        if (Player* pOwner = m_creature->GetMap()->GetPlayer(m_uiCreatorGUID) )
            fAngle = m_creature->GetAngle(pOwner);

        Reset();
    }

    uint64 m_uiCreatorGUID;
    uint64 m_uiHarvesterGUID;

    uint32 m_uiWaitForThrowTimer;

    bool m_bWaitForThrow;
    bool m_bIsSpawned;

    float fAngle;
    float fDist;

    void Reset()
    {
        m_uiWaitForThrowTimer   = 3000;
        m_bWaitForThrow         = false;
        m_uiHarvesterGUID       = 0;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bWaitForThrow && pWho->GetEntry() == ENTRY_GOTHIK && m_creature->GetDistance(pWho) < 15.0f)
        {
            m_uiHarvesterGUID = pWho->GetGUID();

            if (Player* pOwner = m_creature->GetMap()->GetPlayer(m_uiCreatorGUID) )
            {
                pOwner->KilledMonsterCredit(m_creature->GetEntry(), m_creature->GetGUID() );
                // this will execute if m_creature survived Harvester's wrath
                float x, y, z, o;
                o = float(urand(53, 57))/10.0f;
                pWho->GetNearPoint(pWho, x, y, z, pWho->GetObjectBoundingRadius(), 5.0f, o);
                m_creature->GetMotionMaster()->MovePoint(0, x, y, z);
                m_bWaitForThrow = true;
            }
        }
    }

    void AttackStart(Unit *pWho) { return; }

    void UpdateAI(uint32 const uiDiff)
    {
        if (!m_bIsSpawned)
        {
            DoScriptText(SAY_SCARLET_GHOUL_SPAWN1 + urand(0, 5), m_creature);
            m_bIsSpawned = true;
        }

        if (m_bWaitForThrow)
        {
            if (m_uiWaitForThrowTimer <= uiDiff)
            {
                if (Creature* pGothik = m_creature->GetMap()->GetCreature(m_uiHarvesterGUID) )
                {
                    if (pGothik->AI()->DoCastSpellIfCan(m_creature, roll_chance_i(50) ? 52519 : 52521) == CAST_OK)
                        DoScriptText(SAY_SCARLET_GOTHIK1 + urand(0, 4), pGothik);

                    m_uiWaitForThrowTimer = 5000;
                    m_creature->KnockBackFrom(pGothik, 15.0, 5.0);
                    m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                }
                else m_bWaitForThrow = false;
            }
            else m_uiWaitForThrowTimer -= uiDiff;
            return;
        }

        Player* pOwner = m_creature->GetMap()->GetPlayer(m_uiCreatorGUID);
        if (!pOwner || !pOwner->IsInWorld())
        {
            m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            return;
        }

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveFollow(pOwner, fDist, fAngle);
        }
    }
};

CreatureAI* GetAI_mob_scarlet_ghoul(Creature* pCreature)
{
    return new mob_scarlet_ghoulAI(pCreature);
};

void AddSC_ebon_hold()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_a_special_surprise";
    pNewScript->GetAI = &GetAI_npc_a_special_surprise;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_death_knight_initiate";
    pNewScript->GetAI = &GetAI_npc_death_knight_initiate;
    pNewScript->pGossipHello = &GossipHello_npc_death_knight_initiate;
    pNewScript->pGossipSelect = &GossipSelect_npc_death_knight_initiate;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_koltira_deathweaver";
    pNewScript->GetAI = &GetAI_npc_koltira_deathweaver;
    pNewScript->pQuestAccept = &QuestAccept_npc_koltira_deathweaver;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_unworthy_initiate";
    pNewScript->GetAI = &GetAI_npc_unworthy_initiate;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_unworthy_initiate_anchor";
    pNewScript->GetAI = &GetAI_npc_unworthy_initiate_anchor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_acherus_soul_prison";
    pNewScript->pGOHello = &GOHello_go_acherus_soul_prison;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_eye_of_acherus";
    pNewScript->GetAI = &GetAI_npc_eye_of_acherus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_valkyr_battlemaiden";
    pNewScript->GetAI = &GetAI_npc_valkyr_battlemaiden;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_highlord_darion_mograine";
    pNewScript->GetAI = &GetAI_npc_highlord_darion_mograine;
    pNewScript->pGossipHello =  &GossipHello_npc_highlord_darion_mograine;
    pNewScript->pGossipSelect = &GossipSelect_npc_highlord_darion_mograine;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_koltira_orbaz_tassarian_dawn_of_light";
    pNewScript->GetAI = &GetAI_npc_koltira_orbaz_tassarian_dawn_of_light;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_acherus_ghoul";
    pNewScript->GetAI = &GetAI_mob_acherus_ghoul;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_warrior_of_the_frozen_wastes";
    pNewScript->GetAI = &GetAI_mob_warrior_of_the_frozen_wastes;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_scarlet_ghoul";
    pNewScript->GetAI = &GetAI_mob_scarlet_ghoul;
    pNewScript->RegisterSelf();
}
