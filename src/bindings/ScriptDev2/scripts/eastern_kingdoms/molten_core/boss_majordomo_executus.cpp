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
SDName: Boss_Majordomo_Executus
SD%Complete: 30
SDComment: Correct spawning and Event NYI
SDCategory: Molten Core
EndScriptData */

#include "precompiled.h"
#include "molten_core.h"

#define SAY_AGGRO                   -1409003
#define SAY_SPAWN                   -1409004
#define SAY_SLAY                    -1409005
#define SAY_SPECIAL                 -1409006
#define SAY_DEFEAT                  -1409007

#define SAY_GOSSIP_SUMMON           -1409019
#define SAY_SUMMON_MAJ              -1409008
#define SAY_ARRIVAL1_RAG            -1409009
#define SAY_ARRIVAL2_MAJ            -1409010
#define SAY_ARRIVAL3_RAG            -1409011
#define SAY_ARRIVAL5_RAG            -1409012

#define TELE_X                      735.2462
#define TELE_Y                      -1176.1223
#define TELE_Z                      -119.1998

#define SPELL_MAGIC_REFLECTION      20619
#define SPELL_DAMAGE_REFLECTION     21075
#define SPELL_BLASTWAVE             20229
#define SPELL_AEGIS                 20620                   //This is self casted whenever we are below 50%
#define SPELL_TELEPORT              20618
#define SPELL_MAJORDOMO_TELEPORT    19484
#define SPELL_SUMMON_RAGNAROS       19774
#define SPELL_ELEMENTAL_FIRE        19773

#define ENTRY_FLAMEWALKER_HEALER    11663
#define ENTRY_FLAMEWALKER_ELITE     11664

#define FACTION_MAJORDOMO           1081

#define POINT_RESPAWN               1
#define POINT_SUMMON1               2
#define POINT_SUMMON2               3
#define POINT_SUMMON3               4

#define POINT_RESPAWN_X             748.208
#define POINT_RESPAWN_Y             -1179.98
#define POINT_RESPAWN_Z             -119.861
#define POINT_RESPAWN_O             2.91086

#define POINT_SUMMON1_X             839.1729
#define POINT_SUMMON1_Y             -811.2748
#define POINT_SUMMON1_Z             -229.5895

#define POINT_SUMMON_O              4.5210

#define GOSSIP_TEXTID_DOMO_1        4995
#define GOSSIP_TEXTID_DOMO_2        5011
#define GOSSIP_TEXTID_DOMO_3        5012

#define GOSSIP_ITEM_1                "Tell me more."
#define GOSSIP_ITEM_2                "What else do you have to say?"
#define GOSSIP_ITEM_3                "You challenged us and and we have come. Where is this master that you speak of?"

enum Phase
{
    PHASE_FIGHT                   = 0,
    PHASE_DEFEAT                  = 1,
    PHASE_SUMMON                  = 2
};

struct MANGOS_DLL_DECL boss_majordomoAI : public ScriptedAI
{
    boss_majordomoAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    std::list<uint64> m_lFlamewalkersList;

    uint8 m_uiPhase;
    uint8 m_uiEventCounter;
    uint8 m_uiFlamewalkersAlive;

    uint32 m_uiMagicReflection_Timer;
    uint32 m_uiDamageReflection_Timer;
    uint32 m_uiBlastwave_Timer;
    uint32 m_uiTeleportTimer;
    uint32 m_uiEscapeTimer;
    uint32 m_uiSaySummonTimer;

    bool m_bStartSummoning;

    void Reset()
    {
        m_creature->setFaction(FACTION_MAJORDOMO);

        m_uiMagicReflection_Timer  = 30000;                     //Damage reflection first so we alternate
        m_uiDamageReflection_Timer = 15000;
        m_uiBlastwave_Timer        = 10000;
        m_uiTeleportTimer          = 13000;
        m_uiEscapeTimer            = 30000;
        m_uiEventCounter           = 0;
        m_uiFlamewalkersAlive      = 0;
        m_uiSaySummonTimer         = 3000;

        m_bStartSummoning          = false;

        switch (m_pInstance->GetData(TYPE_MAJORDOMO) )
        {
            case NOT_STARTED:
            case FAIL:
                m_uiPhase = PHASE_FIGHT;
                break;
            case DONE:
                m_creature->setFaction(35);
                m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->SetVisibility(VISIBILITY_ON);
                m_uiPhase = PHASE_SUMMON;
                break;
               default:
                break;
        }
    }

    void JustRespawned()
    {
        if (!m_pInstance)
            return;

        Reset();

        DespawnAdds();
        if (m_pInstance->GetData(TYPE_MAJORDOMO) >= DONE)
            return;
        SpawnAdds();
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MAJORDOMO, FAIL);

        m_creature->SetOrientation((float)POINT_RESPAWN_O);

        Reset();
        SpawnAdds();
    }

    void KilledUnit(Unit* victim)
    {
        if (urand(0, 4))
            return;

        DoScriptText(SAY_SLAY, m_creature);
    }

    void Aggro(Unit *pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_MAJORDOMO, IN_PROGRESS);

        m_creature->CallAssistance();
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_RESPAWN)
        {
            m_creature->SetOrientation((float)POINT_RESPAWN_O);
            return;
        }
        else if (uiPointId == POINT_SUMMON1)
        {
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->GetMotionMaster()->Initialize();
            m_creature->SetFacingTo((float)POINT_SUMMON_O);
            return;
        }
    }

    void SpawnAdds()
    {
        if (!m_pInstance)
            return;

        // Flamewalker Healers
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_HEALER, m_creature->GetPositionX()-1, m_creature->GetPositionY()+3, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()+0.3f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_HEALER, m_creature->GetPositionX()-3, m_creature->GetPositionY()+9, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()+0.4f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_HEALER, m_creature->GetPositionX()-1.5f, m_creature->GetPositionY()-3, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()-0.3f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_HEALER, m_creature->GetPositionX()-4.5f, m_creature->GetPositionY()-9, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()-0.4f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        // Flamewalker Elites
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_ELITE, m_creature->GetPositionX()-2, m_creature->GetPositionY()+6, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()+0.4f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_ELITE, m_creature->GetPositionX()-4, m_creature->GetPositionY()+12, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()+0.8f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_ELITE, m_creature->GetPositionX()-3.5f, m_creature->GetPositionY()-6, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()-0.4f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
        if (Creature* pFlamewalker = m_creature->SummonCreature(ENTRY_FLAMEWALKER_ELITE, m_creature->GetPositionX()-6, m_creature->GetPositionY()-12, m_creature->GetPositionZ()+1.0f, m_creature->GetOrientation()-0.8f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7*DAY*IN_MILLISECONDS))
        {
            m_lFlamewalkersList.push_back(pFlamewalker->GetGUID());
            m_uiFlamewalkersAlive++;
        }
    }

    void DespawnAdds()
    {
        if (m_lFlamewalkersList.empty())
            return;

        for(std::list<uint64>::iterator itr = m_lFlamewalkersList.begin(); itr != m_lFlamewalkersList.end(); ++itr)
        {
            Creature* pTemp = m_creature->GetMap()->GetCreature(*itr);
            if (pTemp && pTemp->isAlive())
                pTemp->ForcedDespawn();
        }
        m_lFlamewalkersList.clear();
        m_uiFlamewalkersAlive = 0;
    }

    void SummonedCreatureJustDied(Creature* pCreature)
    {
        if (!m_pInstance)
            return;

        m_lFlamewalkersList.remove(pCreature->GetGUID() );

        if (--m_uiFlamewalkersAlive == 0)
        {
            DoScriptText(SAY_DEFEAT, m_creature);
            m_uiPhase = PHASE_DEFEAT;

            // Set friendly faction and go to respawn point
            m_creature->setFaction(35);
            m_creature->GetMotionMaster()->MovePoint(POINT_RESPAWN, (float)POINT_RESPAWN_X, (float)POINT_RESPAWN_Y, (float)POINT_RESPAWN_Z);
        }
    }

    void BeginEvent()
    {
        m_creature->SetUInt32Value(UNIT_NPC_FLAGS, 0);            // disable gossip
        m_creature->SetSpeedRate(MOVE_WALK, 0.7f, true);
        m_creature->GetMotionMaster()->MovePoint(POINT_SUMMON1, (float)POINT_SUMMON1_X, (float)POINT_SUMMON1_Y, (float)POINT_SUMMON1_Z);
        m_bStartSummoning = true;
    }

    void UpdateAI (const uint32 uiDiff)
    {
       switch (m_uiPhase)
        {
            case PHASE_FIGHT:
            {
                if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                    return;

                //Cast Ageis if less than 50% hp
                if (m_creature->GetHealthPercent() < 50.0f)
                    DoCastSpellIfCan(m_creature,SPELL_AEGIS);

                //Blastwave_Timer
                if (m_uiBlastwave_Timer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature,SPELL_BLASTWAVE) == CAST_OK)
                        m_uiBlastwave_Timer = 10000;
                }else m_uiBlastwave_Timer -= uiDiff;

                // Teleport to the Burning Coals
                if (m_uiTeleportTimer < uiDiff)
                {
                    if (Unit* pTeleTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        pTeleTarget->NearTeleportTo((float)TELE_X, (float)TELE_Y, (float)TELE_Z, 0.5f);
                        pTeleTarget->CastSpell(pTeleTarget, SPELL_TELEPORT, true);
                        m_uiTeleportTimer = 13000;
                    }
                } else m_uiTeleportTimer -= uiDiff;

                DoMeleeAttackIfReady();
                break;
            }

            case PHASE_DEFEAT:
            {
                // Escape to Ragnaros' Lair
                if (m_uiEscapeTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_MAJORDOMO_TELEPORT) == CAST_OK)
                    {
                        m_creature->ForcedDespawn(2000);
                        m_uiEscapeTimer = 30000;
                    }
                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_MAJORDOMO, DONE);
                } else m_uiEscapeTimer -= uiDiff;
                break;
            }

            case PHASE_SUMMON:
                if (!m_bStartSummoning || !m_pInstance)
                    return;

                if (m_uiSaySummonTimer < uiDiff)
                {
                    switch (m_uiEventCounter)
                    {
                        case 0:
                            DoCastSpellIfCan(m_creature, SPELL_SUMMON_RAGNAROS);
                            DoScriptText(SAY_SUMMON_MAJ, m_creature);
                            m_uiSaySummonTimer = 13500;
                            m_uiEventCounter++;
                            break;
                        case 1:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                pRagnaros->SetVisibility(VISIBILITY_ON);
                                DoScriptText(SAY_ARRIVAL1_RAG, pRagnaros);
                                m_uiSaySummonTimer = 1000;
                                m_uiEventCounter++;
                            }
                            break;
                        case 2:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                pRagnaros->SetObjectScale(1.0f);
                                pRagnaros->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                m_uiSaySummonTimer = 13000;
                                m_uiEventCounter++;
                            }
                            break;
                        case 3:
                            DoScriptText(SAY_ARRIVAL2_MAJ, m_creature);
                            m_uiSaySummonTimer = 7000;
                            m_uiEventCounter++;
                            break;
                        case 4:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                DoScriptText(SAY_ARRIVAL3_RAG, pRagnaros);
                                pRagnaros->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                m_uiSaySummonTimer = 18000;
                                m_uiEventCounter++;
                            }
                            break;
                        case 5:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                //pRagnaros->CastSpell(m_creature, SPELL_ELEMENTAL_FIRE, false);    //doesn't work ;/
                                pRagnaros->HandleEmoteCommand(EMOTE_ONESHOT_SPELLCAST);
                                m_creature->SetFeignDeath(true, m_creature->GetGUID() );
                                m_uiSaySummonTimer = 2000;
                                m_uiEventCounter++;
                            }
                            break;
                        case 6:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                DoScriptText(SAY_ARRIVAL5_RAG, pRagnaros);
                                pRagnaros->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                m_uiSaySummonTimer = 10000;
                                m_uiEventCounter++;
                            }
                            break;
                        case 7:
                            if (Creature* pRagnaros = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_RAGNAROS) ) )
                            {
                                pRagnaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                                pRagnaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                                m_bStartSummoning = false;
                            }
                            break;
                        default:
                            return;
                    }
                } else m_uiSaySummonTimer -= uiDiff;
                break;
        }
    }
};

bool GossipHello_boss_majordomo(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DOMO_1,pCreature->GetGUID());
    return true;
}

bool GossipSelect_boss_majordomo(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction )
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DOMO_2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DOMO_3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
		     pPlayer->CLOSE_GOSSIP_MENU();
            if (boss_majordomoAI* pMajorDomoAI = dynamic_cast<boss_majordomoAI*>(pCreature->AI()))
            {
                DoScriptText(SAY_GOSSIP_SUMMON, pCreature, pPlayer);
                pMajorDomoAI->BeginEvent();
            }
            break;
    }
    return true;
}

CreatureAI* GetAI_boss_majordomo(Creature* pCreature)
{
    return new boss_majordomoAI(pCreature);
}

void AddSC_boss_majordomo()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_majordomo";
    newscript->GetAI = &GetAI_boss_majordomo;
    newscript->pGossipHello = &GossipHello_boss_majordomo;
    newscript->pGossipSelect = &GossipSelect_boss_majordomo;
    newscript->RegisterSelf();
}
