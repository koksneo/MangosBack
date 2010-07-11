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
SDName: serpent_shrine
SD%Complete: 50
SDComment:  coilfang frenzy/scalding water when player zpos<=-21 ; mob_underbog_colossusAI: Acid Geysir targetting , mob_underbog_colossusAI: summon mushrooms which provide refreshing mist, go_serpentshrine_console: lock when boss alive
SDCategory: Coilfang Resevoir, Serpent Shrine Cavern
EndScriptData */

/* ContentData
go_serpentshrine_console                                    // Support for 'Serpentshrine Consoles' & 'Lady Vashj Bridge Console'
mob_underbog_colossusAI                                     // Underbog Colossus: Random Phases
EndContentData */

#include "precompiled.h"
#include "serpent_shrine.h"

void CheckFinalGen(ScriptedInstance* pInstance, Player* pPlayer, GameObject* pGo)
{
    error_log("gen check");
        if ((pInstance->GetData(TYPE_HYDROSS_EVENT) == DONE)
                && (pInstance->GetData(TYPE_THELURKER_EVENT) == DONE) && (pInstance->GetData(TYPE_LEOTHERAS_EVENT) == DONE)
                && (pInstance->GetData(TYPE_KARATHRESS_EVENT) == DONE) && (pInstance->GetData(TYPE_MOROGRIM_EVENT) == DONE))
                if (GameObject* pGoTemp = pGo->GetMap()->GetGameObject(pInstance->GetData64(DATA_BRIDGE_GEN)))
                    pGoTemp->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
}

bool GOHello_go_serpentshrine_console(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = ((ScriptedInstance*)pPlayer->GetInstanceData());

    if (!pInstance)
        return true;

    switch ((pGo->GetGOInfo())->id)
    {
        case 185114:
            if (pInstance->GetData(TYPE_HYDROSS_EVENT) == SPECIAL)
            {
                pInstance->SetData(TYPE_HYDROSS_EVENT, DONE);
                CheckFinalGen(pInstance, pPlayer, pGo);
                return false;
            }
            break;
        case 185115:
            if (pInstance->GetData(TYPE_THELURKER_EVENT) == SPECIAL)
            {
                pInstance->SetData(TYPE_THELURKER_EVENT, DONE);
                CheckFinalGen(pInstance, pPlayer, pGo);
                return false;
            }
            break;
        case 185116:
            if (pInstance->GetData(TYPE_LEOTHERAS_EVENT) == SPECIAL)
            {
                pInstance->SetData(TYPE_LEOTHERAS_EVENT, DONE);
                CheckFinalGen(pInstance, pPlayer, pGo);
                return false;
            }
            break;
        case 185117:
            if (pInstance->GetData(TYPE_KARATHRESS_EVENT) == SPECIAL)
            {
                pInstance->SetData(TYPE_KARATHRESS_EVENT, DONE);
                CheckFinalGen(pInstance, pPlayer, pGo);
                return false;
            }
        case 185118:
            if (pInstance->GetData(TYPE_MOROGRIM_EVENT) == SPECIAL)
            {
                pInstance->SetData(TYPE_MOROGRIM_EVENT, DONE);
                CheckFinalGen(pInstance, pPlayer, pGo);
                return false;
            }
            break;
        case 184568:
            if (pPlayer->isGameMaster() || (pInstance->GetData(TYPE_HYDROSS_EVENT) == DONE
                && pInstance->GetData(TYPE_THELURKER_EVENT) == DONE && pInstance->GetData(TYPE_LEOTHERAS_EVENT) == DONE
                && pInstance->GetData(TYPE_KARATHRESS_EVENT) == DONE && pInstance->GetData(TYPE_MOROGRIM_EVENT) == DONE))
            {
                pInstance->SetData(TYPE_LADYVASHJ_EVENT, SPECIAL);
                return false;
            }
            break;
    }
    return true;
}

enum
{
    SPELL_INITIAL_INFECTION         = 39032,
    SPELL_RAMPANT_INFECTION         = 39042,
    SPELL_SPORE_QUAKE               = 38976,

    SPELL_ENRAGE                    = 39031,
    SPELL_ATROPHIC_BLOW             = 39015,

    SPELL_ACID_GEYSER               = 38971,
    SPELL_SERPENTSHRINE_PARASITE    = 39044,

    SPELL_REFRESHING_MIST           = 38730,
    SPELL_TOXIC_POOL                = 38718,

    NPC_COLOSSUS_LURKER             = 22347,
    NPC_COLOSSUS_RAGER              = 22352,

    // NPC_REFRESHING_MIST          = missing               // Mushrooms which cast SPELL_REFRESHING_MIST
};
enum
{
    SPELLTARGET_SELF         = 0,
    SPELLTARGET_TOPAGGRO     = 1,
    SPELLTARGET_RANDOM       = 2
};

struct MANGOS_DLL_DECL mob_underbog_colossusAI : public ScriptedAI
{
    mob_underbog_colossusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiMobType = rand()%3;
        Reset();
    }

    uint32 m_uiMobType;

    uint32 m_uiSpellId_1;
    uint32 m_uiSpellId_2;
    uint32 m_uiSpellTarget_1;
    uint32 m_uiSpellTarget_2;
    uint32 m_uiSpellTimer_1;
    uint32 m_uiSpellTimer_2;
    uint32 m_uiSpellTimer_Reset_1;
    uint32 m_uiSpellTimer_Reset_2;
    uint32 m_uiSpellTimer_Random_1;
    uint32 m_uiSpellTimer_Random_2;

    void Reset()
    {
        switch (m_uiMobType)
        {
            case 0:
                m_uiSpellId_1           = SPELL_ENRAGE;
                m_uiSpellId_2           = SPELL_ATROPHIC_BLOW;
                m_uiSpellTarget_1       = SPELLTARGET_SELF;
                m_uiSpellTarget_2       = SPELLTARGET_TOPAGGRO;
                m_uiSpellTimer_1        = 10900;
                m_uiSpellTimer_2        = 2800;
                m_uiSpellTimer_Reset_1  = 16100;
                m_uiSpellTimer_Reset_2  = 2400;
                m_uiSpellTimer_Random_1 = 800;
                m_uiSpellTimer_Random_2 = 4400;
                break;
            case 1:
                m_uiSpellId_1           = SPELL_SPORE_QUAKE;
                m_uiSpellId_2           = SPELL_INITIAL_INFECTION;
                m_uiSpellTarget_1       = SPELLTARGET_SELF;
                m_uiSpellTarget_2       = SPELLTARGET_RANDOM;
                m_uiSpellTimer_1        = 16000;
                m_uiSpellTimer_2        = 11400;
                m_uiSpellTimer_Reset_1  = 22100;
                m_uiSpellTimer_Reset_2  = 14400;
                m_uiSpellTimer_Random_1 = 11000;
                m_uiSpellTimer_Random_2 = 10500;
                break;
            case 2:
                m_uiSpellId_1           = SPELL_ACID_GEYSER;
                m_uiSpellId_2           = SPELL_SERPENTSHRINE_PARASITE;
                m_uiSpellTarget_1       = SPELLTARGET_SELF;
                m_uiSpellTarget_2       = SPELLTARGET_RANDOM;
                m_uiSpellTimer_1        = 16800;
                m_uiSpellTimer_2        = 14500;
                m_uiSpellTimer_Reset_1  = 27700;
                m_uiSpellTimer_Reset_2  = 20000;
                m_uiSpellTimer_Random_1 = 2000;
                m_uiSpellTimer_Random_2 = 10000;
                break;
        }
    }

    // void JustSummoned(Creature* pSummoned)
    // {
        // if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
            // pSummoned->AI()->AttackStart(pTarget);
    // }

    void JustDied(Unit* pVictim)
    {
        switch (rand()%5)
        {
            case 0:
                break;
            case 1:
                DoCast(m_creature,SPELL_TOXIC_POOL,true);
                break;
            case 2:
                for (uint8 i = 0; i < (2+rand()%2); ++i)
                {
                    float fPosX, fPosY, fPosZ;
                    m_creature->GetPosition(fPosX, fPosY, fPosZ);
                    m_creature->GetRandomPoint(fPosX, fPosY, fPosZ, 10.0f, fPosX, fPosY, fPosZ);

                    Creature* pSummoned = DoSpawnCreature(NPC_COLOSSUS_LURKER, fPosX, fPosY, fPosZ,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                    if (pSummoned && pSummoned->AI() && pTarget)
                        pSummoned->AI()->AttackStart(pTarget);
                }
                break;
            case 3:
                for (uint8 i = 0; i < (6+rand()%5); ++i)
                {
                    float fPosX, fPosY, fPosZ;
                    m_creature->GetPosition(fPosX, fPosY, fPosZ);
                    m_creature->GetRandomPoint(fPosX, fPosY, fPosZ, 10.0f, fPosX, fPosY, fPosZ);
                    Creature* pSummoned = DoSpawnCreature(NPC_COLOSSUS_RAGER, fPosX, fPosY, fPosZ,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                    if (pSummoned && pSummoned->AI() && pTarget)
                        pSummoned->AI()->AttackStart(pTarget);
                }
                break;
            case 4:
                m_creature->CastSpell(m_creature,SPELL_REFRESHING_MIST,true);
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //m_uiSpellTimer_1
        if (m_uiSpellTimer_1 < uiDiff)
        {
            switch (m_uiSpellTarget_1)
            {
                case SPELLTARGET_SELF:
                    DoCast(m_creature, m_uiSpellId_1);
                    break;
                case SPELLTARGET_TOPAGGRO:
                    DoCast(m_creature->getVictim(), m_uiSpellId_1);
                    break;
                case SPELLTARGET_RANDOM:
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget, m_uiSpellId_1);
                    break;
            }
            m_uiSpellTimer_1 = m_uiSpellTimer_Reset_1 + rand()%m_uiSpellTimer_Random_1;
        }else m_uiSpellTimer_1 -= uiDiff;

        //m_uiSpellTimer_2
        if (m_uiSpellTimer_2 < uiDiff)
        {
            switch (m_uiSpellTarget_2)
            {
                case SPELLTARGET_SELF:
                    DoCast(m_creature, m_uiSpellId_2);
                    break;
                case SPELLTARGET_TOPAGGRO:
                    DoCast(m_creature->getVictim(), m_uiSpellId_2);
                    break;
                case SPELLTARGET_RANDOM:
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCastSpellIfCan(pTarget, m_uiSpellId_2);
                    break;
            }
            m_uiSpellTimer_2 = m_uiSpellTimer_Reset_2 + rand()%m_uiSpellTimer_Random_2;
        }else m_uiSpellTimer_2 -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_underbog_colossus(Creature* pCreature)
{
    return new mob_underbog_colossusAI(pCreature);
}

void AddSC_serpentshrine_cavern()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "go_serpentshrine_console";
    newscript->pGOHello = &GOHello_go_serpentshrine_console;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_underbog_colossus";
    newscript->GetAI = &GetAI_mob_underbog_colossus;
    newscript->RegisterSelf();
}

