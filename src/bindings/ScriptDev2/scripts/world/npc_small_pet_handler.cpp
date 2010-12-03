/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Small Pet Handler
SDAuthor: ckegg
SD%Complete: 0%
SDComment: 
SDCategory: Pet behavior
EndScriptData */

#include "precompiled.h"

enum
{
    NPC_PANDA                   = 11325,
    SPELL_PANDA_SLEEP           = 19231,
    SPELL_PANDA_ROAR            = 40664,

    NPC_DIABLO                  = 11326,
    SPELL_DIABLO_FLAME          = 18874,
    //SPELL_DIABLO              = 18873,

    NPC_ZERGLING                = 11327,
    SPELL_ZERGLING              = 19227,
    //SPELL_ZERGLING            = 19226,

    NPC_WILLY                   = 23231,
    SPELL_WILLY_SLEEP           = 40663,
    //SPELL_WILLY               = 40619,
    //SPELL_WILLY               = 40638,

    NPC_DRAGON_KITE             = 25110,
    SPELL_DRAGON_KITE_LIGHTNING = 45197,

    NPC_BATTLE_BOT              = 34587,
    SPELL_BATTLE_BOT_MELEE      = 65694,

    NPC_MURKY                   = 15186,
    NPC_LURKY                   = 15358,
    SPELL_MURKY_DANCE           = 25165,

    NPC_EGBERT                  = 23258,
    SPELL_EGBERT_HAPPYNESS      = 40669,

    //NPC_KIRIN                   = ,
    SPELL_KIRIN_ARCANE          = 61479,

    NPC_MULGORE                 = 33219,
    SPELL_MULGORE_HAPPYNESS     = 62585,

    NPC_PENGU                   = 32595,
    NPC_CHILLY                  = 31128,
    SPELL_PENGU_SOUND           = 61635,

    NPC_STINKER                 = 23274,
    SPELL_STINKER_BROKEN_HEART  = 62004,

    NPC_SCORCHLING              = 25706,
    SPELL_SCORCHLING_BLAST      = 45889,

    NPC_SPRING_RABBIT           = 32791,
    SPELL_SPRING_RABBIT_IN_LOVE = 61728,
    SPELL_SPRING_RABBIT_JUMP    = 61724,

    NPC_STRAND_CRAWLERT         = 33226,
    SPELL_STRAND_CRAWLERT_BUBBLE = 62587,

    NPC_TELDRASSIL_SPROUTLING   = 33188,
    SPELL_SPROUTLING_SLEEP      = 62499,
    SPELL_SPROUTLING_DANCE      = 62504,

    NPC_TIRISFAL_BATLING        = 33197,
    NPC_VAMPIRIC_BATLING        = 28513,
    SPELL_TIRISFAL_BATLING_SOUND = 62545,

    NPC_TYRAEL                  = 29089,
    SPELL_TYRAEL_DANCE          = 54398,

    NPC_TRAIN_WRECKER           = 33404,
    SPELL_TRAIN_WRECKER_BLOW    = 62943,

    NPC_BLIZZARD_BEAR           = 32841,
    SPELL_BLIZZARD_BEAR_SIT     = 61853,

    NPC_MOJO                    = 24480,
    SPELL_FEELING_FROGGY        = 43906,
    SPELL_FROG_LOVE             = 62537,

    EMOTE_KISS                  = -1799979,

    NPC_CAPTURED_BERYL_SORCERER = 25474,

    NPC_ORPHANED_MAMMOTH        = 25861,
    SPELL_MAMMOTH_CREDIT        = 46231
};

struct MANGOS_DLL_DECL npc_small_pet_handlerAI : public ScriptedAI
{
    npc_small_pet_handlerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool m_bIsIdle;
    bool m_bIsInAction;
    uint32 m_uiCheckTimer;
    uint32 m_uiActionTimer;
    uint64 m_uiPlayerGUID;

    void Reset()
    {
        m_bIsIdle = false;
        m_bIsInAction = false;
        m_uiCheckTimer = 1000;
        m_uiActionTimer = 10000 + rand()%20000;
        m_uiPlayerGUID = 0;

        if (Unit* pOwner = m_creature->GetCharmerOrOwner())
        {
            m_creature->GetMotionMaster()->MoveFollow(pOwner, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
            m_uiPlayerGUID = pOwner->GetGUID();
        }
    }

    void AttackStart(Unit* who)
    {
        return;
    }

    void ReceiveEmote(Player* pPlayer, uint32 emote)
    {
        if (!pPlayer)
            return;
        switch (m_creature->GetEntry())
        {
            case NPC_MOJO:
                if (emote == TEXTEMOTE_KISS)
                {
                    m_creature->SetTargetGuid(pPlayer->GetObjectGuid());
                    DoScriptText(EMOTE_KISS,m_creature,pPlayer);
                    pPlayer->CastSpell(pPlayer,SPELL_FEELING_FROGGY,true);
                    DoCast(m_creature,SPELL_FROG_LOVE,true);
                }
                break;
            default: break;
        }
    }

    void MoveInLineOfSight (Unit* pWho)
    {
        if (!pWho)
            return;

        switch (m_creature->GetEntry())
        {
            case NPC_CAPTURED_BERYL_SORCERER:
                if (!m_creature->GetOwner())
                    return;
                if (m_creature->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                    return;
                if (pWho->GetEntry() == 25262 && (m_creature->GetDistance(pWho) < 2*INTERACTION_DISTANCE))
                {
                    ((Player*)(m_creature->GetOwner()))->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetGUID());
                    m_creature->ForcedDespawn();
                }
                break;
            case NPC_ORPHANED_MAMMOTH:
                if (!m_creature->GetOwner())
                    return;
                if ((m_creature->GetOwner())->GetTypeId() != TYPEID_PLAYER)
                    return;
                if (pWho->GetEntry() == 25862 && (m_creature->GetDistance(pWho) < 2*INTERACTION_DISTANCE))
                {
                    (m_creature->GetOwner())->CastSpell(m_creature->GetOwner(),SPELL_MAMMOTH_CREDIT,true);
                    m_creature->ForcedDespawn();
                }
                break;
            default: break;
        }
    }


    void UpdateAI(const uint32 uiDiff)
    {
        // Check if pet is moving
        if (m_uiCheckTimer < uiDiff)
        {
            if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
            {
                // Change speed if owner is mounted
                if (pPlayer->IsMounted())
                    m_creature->SetSpeedRate(MOVE_RUN, 2.0f, true);
                else
                    m_creature->SetSpeedRate(MOVE_RUN, 1.0f, true);

                // Check if owner is stopped
                if (pPlayer->isMoving() && m_bIsIdle)
                {
                    m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                    //m_creature->GetMotionMaster()->MoveFollow(pPlayer, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
                    if (m_creature->IsNonMeleeSpellCasted(false))
                        m_creature->InterruptNonMeleeSpells(false);
                    m_bIsIdle = false;
                    m_uiActionTimer = 10000 + rand()%20000;
                }
                else if (m_creature->IsWithinDistInMap(pPlayer, 1.5f) && !m_bIsIdle)
                {
                    m_bIsIdle = true;
                }
            }
            m_uiCheckTimer = 1000;
        }
        else
            m_uiCheckTimer -= uiDiff;

        // Return if pet is moving
        if (!m_bIsIdle)
        {
            m_bIsInAction = false;
            return;
        }

        // Do pet's action
        if (m_uiActionTimer < uiDiff)
        {
            // Do action
            if (!m_bIsInAction)
            {
                m_uiActionTimer = 30000 + rand()%30000; // Prevent stopping action too early
                m_bIsInAction = true;
                PetAction(m_creature->GetEntry());
            }
            // Stop action
            else
            {
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                if (m_creature->IsNonMeleeSpellCasted(false))
                    m_creature->InterruptNonMeleeSpells(false);
                m_uiActionTimer = 10000 + rand()%20000;
                m_bIsInAction = false;
            }
        }
        else
            m_uiActionTimer -= uiDiff;
    }

    void PetAction(uint32 uiPetGUID)
    {
        if (!uiPetGUID)
            return;

        switch(uiPetGUID)
        {
            case NPC_PANDA:
            {
                switch(rand()%2)
                {
                    case 0: DoCast(m_creature, SPELL_PANDA_SLEEP); break;
                    case 1: DoCast(m_creature, SPELL_PANDA_ROAR);  break;
                }
                break;
            }
            case NPC_DIABLO:
            {
                DoCast(m_creature, SPELL_DIABLO_FLAME);
                break;
            }
            case NPC_ZERGLING:
            {
                DoCast(m_creature, SPELL_ZERGLING);
                break;
            }
            case NPC_WILLY:
            {
                DoCast(m_creature, SPELL_WILLY_SLEEP);
                break;
            }
            case NPC_DRAGON_KITE:
            {
                if (Unit* pOwner = m_creature->GetCharmerOrOwner())
                    DoCast(pOwner, SPELL_DRAGON_KITE_LIGHTNING);
                break;
            }
            case NPC_BATTLE_BOT:
            {
                if (Creature* pBattleBot = GetClosestCreatureWithEntry(m_creature, NPC_BATTLE_BOT, 3.0f))
                {
                    m_creature->GetMotionMaster()->MovePoint(0, pBattleBot->GetPositionX()+rand()%5, pBattleBot->GetPositionY()+rand()%5, pBattleBot->GetPositionZ());
                    DoCast(m_creature, SPELL_BATTLE_BOT_MELEE);
                    pBattleBot->CastSpell(pBattleBot, SPELL_BATTLE_BOT_MELEE, false);
                    m_uiActionTimer = 3000; // make bot repeats the action
                    m_bIsInAction = false;
                }
                break;
            }
            case NPC_MURKY:
            case NPC_LURKY:
            {
                m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_DANCE);
                DoCast(m_creature, SPELL_MURKY_DANCE);
                break;
            }
            case NPC_EGBERT:
            {
                DoCast(m_creature, SPELL_EGBERT_HAPPYNESS);
                break;
            }
            case NPC_MULGORE:
            {
                DoCast(m_creature, SPELL_MULGORE_HAPPYNESS);
                break;
            }
            case NPC_PENGU:
            case NPC_CHILLY:
            {
                DoCast(m_creature, SPELL_PENGU_SOUND);
                m_uiActionTimer = 5000 + rand()%5000; // repeat
                m_bIsInAction = false;
                break;
            }
            case NPC_STINKER:
            {
                DoCast(m_creature, SPELL_STINKER_BROKEN_HEART);
                break;
            }
            case NPC_SCORCHLING:
            {
                DoCast(m_creature, SPELL_SCORCHLING_BLAST);
                break;
            }
            case NPC_SPRING_RABBIT:
            {
                switch(rand()%2)
                {
                    case 0: DoCast(m_creature, SPELL_SPRING_RABBIT_IN_LOVE); break;
                    case 1: DoCast(m_creature, SPELL_SPRING_RABBIT_JUMP);    break;
                }
                break;
            }
            case NPC_STRAND_CRAWLERT:
            {
                DoCast(m_creature, SPELL_STRAND_CRAWLERT_BUBBLE);
                break;
            }
            case NPC_TELDRASSIL_SPROUTLING:
            {
                switch(rand()%2)
                {
                    case 0: DoCast(m_creature, SPELL_SPROUTLING_SLEEP); break;
                    case 1: DoCast(m_creature, SPELL_SPROUTLING_DANCE); break;
                }
                break;
            }
            case NPC_TIRISFAL_BATLING:
            case NPC_VAMPIRIC_BATLING:
            {
                DoCast(m_creature, SPELL_TIRISFAL_BATLING_SOUND);
                break;
            }
            case NPC_TYRAEL:
            {
                DoCast(m_creature, SPELL_TYRAEL_DANCE);
                break;
            }
            case NPC_TRAIN_WRECKER:
            {
                DoCast(m_creature, SPELL_TRAIN_WRECKER_BLOW);
                break;
            }
            case NPC_BLIZZARD_BEAR:
            {
                DoCast(m_creature, SPELL_BLIZZARD_BEAR_SIT);
                break;
            }
        }
    }
};

CreatureAI* GetAI_npc_small_pet_handler(Creature* pCreature)
{
    return new npc_small_pet_handlerAI(pCreature);
}

void AddSC_npc_small_pet_handler()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_small_pet_handler";
    newscript->GetAI = &GetAI_npc_small_pet_handler;
    newscript->RegisterSelf();
}
