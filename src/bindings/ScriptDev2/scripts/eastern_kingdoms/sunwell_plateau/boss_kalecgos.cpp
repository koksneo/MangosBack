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
SDName: Boss_Kalecgos
SD%Complete: 95%
SDComment: PlayAble
SDCategory: Sunwell Plateau
SDAuthot: Scrappy Doo
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"
#include "WorldPacket.h"
#include "GameObject.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"

enum Says
{
    //kalecgos dragon form
    SAY_EVIL_AGGRO                  = -1580000,
    SAY_EVIL_SPELL1                 = -1580001,
    SAY_EVIL_SPELL2                 = -1580002,
    SAY_EVIL_SLAY1                  = -1580003,
    SAY_EVIL_SLAY2                  = -1580004,
    SAY_EVIL_ENRAGE                 = -1580005,

    //kalecgos humanoid form
    SAY_GOOD_AGGRO                  = -1580006,
    SAY_GOOD_NEAR_DEATH             = -1580007,
    SAY_GOOD_NEAR_DEATH2            = -1580008,
    SAY_GOOD_PLRWIN                 = -1580009,

    SAY_SATH_AGGRO                  = -1580010,
    SAY_SATH_DEATH                  = -1580011,
    SAY_SATH_SPELL1                 = -1580012,
    SAY_SATH_SPELL2                 = -1580013,
    SAY_SATH_SLAY1                  = -1580014,
    SAY_SATH_SLAY2                  = -1580015,
    SAY_SATH_ENRAGE                 = -1580016,
};

enum Spells
{
    MOB_KALEC                       = 24891,
    SPECTRAL_REALM                  = 25796,
    NORMAL_REALM                    = 25795,

    /*** Misc ***/
    SPELL_TAIL_LASH                 = 45122,
    SPELL_BANISH                    = 44836,
    SPELL_SPECTRAL_EXHAUSTION       = 44867,
    SPELL_ENRAGE2                   = 26662,

    /*** Kalecgos Dragon****/
    SPELL_SPECTRAL_BLAST            = 44866,
    SPELL_ARCANE_BUFFET             = 45018,
    SPELL_FROST_BREATH              = 44799,
    SPELL_CRAZED_RAGE               = 44806,                // this should be 44807 instead

    /*** Kalecgos Human ***/
    SPELL_REVITALIZE                = 45027,
    SPELL_HEROIC_STRIKE             = 45026,

    /*** Sathrovarr ***/
    SPELL_CORRUPTING_STRIKE         = 45029,
    SPELL_CURSE_OF_BOUNDLESS_AGONY  = 45032,
    SPELL_SHADOW_BOLT_VOLLEY        = 45031,
};

#define    DRAGON_REALM_Z                  53.079f
#define    DEMON_REALM_Z                   -74.558f
#define    GO_FAILED                       "You are unable to use this currently."

uint32 WildMagic[]= { 44978, 45001, 45002, 45004, 45006, 45010 };

/*//Wild Magic
class MANGOS_DLL_DECL WildMagicA : public Aura
{
    public:
        WildMagicA(SpellEntry* spellInfo, SpellEffectIndex eff, int32 *bp, Unit* target, Unit* caster) : Aura(spellInfo, eff, bp, target, caster, NULL)
            {}
};*/

//KalecgosDragon
struct MANGOS_DLL_DECL boss_kalecgosAI : public ScriptedAI
{
    boss_kalecgosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 m_uiNormalGUID;

    uint32 m_uiSpectralBlastTimer;
    uint32 m_uiTailLashTimer;
    uint32 m_uiArcaneBuffetTimer;
    uint32 m_uiFrostBreathTimer;
    uint32 m_uiWildMagicTimer;
    uint32 m_uiSathrovarrTimer;
    uint32 m_uiNextEnrageTimer;
    uint32 m_uiDoorTimer;

    bool bBanished;
    bool bEnraged;
    bool bSathrospawnd;
    bool bCheck;
    bool bIsDoorClosed;

    void Reset()
    {
       if (m_pInstance)
       {
            m_pInstance->SetData(DATA_KALECGOS_EVENT,NOT_STARTED);
            m_pInstance->SetData(DATA_SATHROVARR_EVENT,NOT_STARTED);

            if (GameObject* pForceBarrier = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_FORCEFIELD)))
                pForceBarrier->SetGoState(GO_STATE_ACTIVE);
            if (GameObject* pWallA = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_A)))
                pWallA->SetGoState(GO_STATE_READY);
            if (GameObject* pWallB = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_B)))
                pWallB->SetGoState(GO_STATE_ACTIVE);
       }      

        m_uiSpectralBlastTimer      = urand(20000, 25000);
        m_uiTailLashTimer           = urand(25000, 40000);
        m_uiArcaneBuffetTimer       = 8000;
        m_uiFrostBreathTimer        = 15000;
        m_uiWildMagicTimer          = 10000;
        m_uiSathrovarrTimer         = 35000;
        m_uiDoorTimer               = 15000;

        m_uiNormalGUID = 0;

        bEnraged             = false;
        bSathrospawnd        = false;
        bCheck               = true;
        bBanished            = false;
        bIsDoorClosed        = false;      

        if (m_creature->HasAura(SPELL_CRAZED_RAGE))
            m_creature->RemoveAurasDueToSpell(SPELL_CRAZED_RAGE);

        if (m_creature->HasAura(SPELL_BANISH))
            m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
    }

    void Aggro(Unit* pWho)
    {
        m_uiDoorTimer = 15000;
        DoScriptText(SAY_EVIL_AGGRO, m_creature);
        if (m_pInstance)
            m_pInstance->SetData(DATA_KALECGOS_EVENT, IN_PROGRESS);

        if (Creature* pNormal = m_creature->SummonCreature(NORMAL_REALM, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, 0, TEMPSUMMON_TIMED_DESPAWN, 1200000))
            m_uiNormalGUID = pNormal->GetGUID();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
            if (GameObject* pForceBarrier = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_FORCEFIELD)))
                pForceBarrier->SetGoState(GO_STATE_ACTIVE);
            if (GameObject* pWallA = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_A)))
                pWallA->SetGoState(GO_STATE_ACTIVE);
            if (GameObject* pWallB = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_B)))
                pWallB->SetGoState(GO_STATE_ACTIVE);
        }
    }

    void CastWildMagic()
    {
        SpellEntry* pSpellInfo = (SpellEntry*)GetSpellStore()->LookupEntry(WildMagic[urand(1,6)]);
        if (pSpellInfo)
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (pTarget && pTarget->IsWithinDistInMap(m_creature, 50))
                {
                    for(uint8 i=0 ;i< MAX_EFFECT_INDEX; ++i)
                    {
                        uint8 eff = pSpellInfo->Effect[SpellEffectIndex(i)];
                        if (eff >= TOTAL_SPELL_EFFECTS)
                            continue;
                        //pTarget->AddAura(new WildMagicA(pSpellInfo, SpellEffectIndex(i), NULL, pTarget, pTarget));
                    }
                    m_uiWildMagicTimer = 19000;
                }else m_uiWildMagicTimer = 1000;
            }
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 1))
        {
            case 0: DoScriptText(SAY_EVIL_SLAY1, m_creature); break;
            case 1: DoScriptText(SAY_EVIL_SLAY2, m_creature); break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiDoorTimer < uiDiff && !bIsDoorClosed)
        {
            if (GameObject* pForceBarrier = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_FORCEFIELD)))
                pForceBarrier->SetGoState(GO_STATE_READY);
            if (GameObject* pWallA = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_A)))
                pWallA->SetGoState(GO_STATE_READY);
            if (GameObject* pWallB = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_KALECGOS_FIGHT_GATE_B)))
                pWallB->SetGoState(GO_STATE_READY);
            bIsDoorClosed = true;
        }m_uiDoorTimer -= uiDiff;

        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (m_pInstance && m_pInstance->GetData(DATA_SATHROVARR_EVENT) == DONE)
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);

            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == NOT_STARTED)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                ((boss_kalecgosAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
            }
            return;
        }

        /* Banish at 1% hp working */
        if (!bBanished && (m_creature->GetHealthPercent() < 1.0f))
        {
            if (m_pInstance)
                m_pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
            DoCast(m_creature, SPELL_BANISH, true);
            bBanished = true;
        }

        //Mising VMAPS workarroud, ANTY BUG :D
        if (Creature* pSpectral = m_creature->GetMap()->GetCreature(m_uiNormalGUID))
            if (m_creature->GetHealthPercent() > 1.0f)
                if (!m_creature->IsInRange(pSpectral, 0.0f, 50.0f, true))
                {
                    m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, m_creature->GetOrientation());
                    ((boss_kalecgosAI*)m_creature->AI())->Reset();
                    m_creature->AI()->EnterEvadeMode();
                }

        Unit* pWho = m_creature->getVictim();
        if(pWho && !pWho->IsInRange(m_creature, 0.0f, 50.0f, true))
        {
            m_creature->AddThreat(pWho, -100000.0f);
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                m_creature->AddThreat(pTarget, 100000.0f);
                m_creature->AI()->AttackStart(pTarget);
            }
        }
        //END 

        //Enrage at 10% both bosses
        if (!bEnraged)
        {
            if (m_pInstance && m_pInstance->GetData(DATA_SATHROVARR_EVENT) == SPECIAL)
            {
                if (Creature* pSathrovarr = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(DATA_SATHROVARR)))
                {
                    if (pSathrovarr->isAlive())
                        pSathrovarr->CastSpell(pSathrovarr, SPELL_CRAZED_RAGE, true);
                }
                m_uiNextEnrageTimer = 10000;
                bEnraged = true;
            }

        if (m_creature->GetHealthPercent() < 10.0f)
            {
                if (m_pInstance) 
                    m_pInstance->SetData(DATA_SATHROVARR_EVENT,SPECIAL);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                m_uiNextEnrageTimer = 10000;
                bEnraged = true;
            }
        } 
        else if (m_uiNextEnrageTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_CRAZED_RAGE, true);
            m_uiNextEnrageTimer = 10000;
        }else m_uiNextEnrageTimer -= uiDiff;

        //Simple Spelss
        if (m_uiArcaneBuffetTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_ARCANE_BUFFET) == CAST_OK)
            {

                m_uiArcaneBuffetTimer = 20000;
            }
        }
        else
            m_uiArcaneBuffetTimer -= uiDiff;

        if (m_uiFrostBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROST_BREATH) == CAST_OK)
            {
                if (!urand(0, 1))
                DoScriptText(SAY_EVIL_SPELL2, m_creature);

            m_uiFrostBreathTimer = 25000;
            }
        }
        else
            m_uiFrostBreathTimer -= uiDiff;

        if (m_uiTailLashTimer < uiDiff)
        {
            if (m_creature->getVictim())
                DoCast(m_creature->getVictim(), SPELL_TAIL_LASH);
            m_uiTailLashTimer = urand(25000, 40000);
        }else m_uiTailLashTimer -= uiDiff;

        if (m_uiWildMagicTimer < uiDiff)
        {
            CastWildMagic();
        }else m_uiWildMagicTimer -= uiDiff;
        //end of simple spells

        DoMeleeAttackIfReady();

        //Teleport To Spectral Realm
        if (m_uiSpectralBlastTimer < uiDiff)
        {
            ThreatList const& m_threatlist = m_creature->getThreatManager().getThreatList();
            if (m_threatlist.empty())
            {
                m_uiSpectralBlastTimer = 1000;
                return;
            }

            std::list<Unit*> targetList;
            for(ThreatList::const_iterator itr = m_threatlist.begin(); itr!= m_threatlist.end(); ++itr)
                if((*itr)->getTarget() && (*itr)->getTarget()->GetTypeId() == TYPEID_PLAYER && (*itr)->getTarget()->GetGUID() && !(*itr)->getTarget()->HasAura(SPELL_SPECTRAL_EXHAUSTION) && (*itr)->getTarget()->IsInRange(m_creature, 0.0f, 50.0f, true))
                    targetList.push_back((*itr)->getTarget());
            if(targetList.empty())
            {
                m_uiSpectralBlastTimer = 1000;
                return;
            }
        
            std::list<Unit*>::iterator i = targetList.begin();
            advance(i, rand()%targetList.size());
            if((*i))
            {
                if(m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == SPECIAL)
                {
                    m_uiSpectralBlastTimer = urand(20000, 25000);
                }
                else
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                        if ( pTarget == (*i))
                            return; 

                    m_creature->AddThreat((*i), -100000.0f);
                    (*i)->InterruptNonMeleeSpells(true);
                    (*i)->CastSpell((*i), SPELL_SPECTRAL_BLAST,true);
                    (*i)->CastSpell((*i), SPELL_SPECTRAL_EXHAUSTION,true);
                    ((Player*)(*i))->TeleportTo((*i)->GetMapId(), (*i)->GetPositionX(), (*i)->GetPositionY(), DEMON_REALM_Z, (*i)->GetOrientation());
                }
                m_uiSpectralBlastTimer = urand(20000, 25000);    
            }else m_uiSpectralBlastTimer = 1000;                
        }else m_uiSpectralBlastTimer -= uiDiff;

        if (m_uiSathrovarrTimer < uiDiff && !bSathrospawnd)
        {
            if (Creature* pSath = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(DATA_SATHROVARR)))
            {
                pSath->SetVisibility(VISIBILITY_ON);
                pSath->setFaction(14);
                bSathrospawnd = true;
                if(pSath->AI())
                    pSath->AI()->AttackStart(m_creature->getVictim());
            }
        }else m_uiSathrovarrTimer -= uiDiff;
    }
};

//Sathrovar
struct MANGOS_DLL_DECL boss_sathrovarrAI : public ScriptedAI
{
    boss_sathrovarrAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        m_uiKalecGUID = 0;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 m_uiKalecGUID;
    uint64 m_uiSpectralGUID;

    uint32 m_uiCorruptingStrikeTimer;
    uint32 m_uiCurseOfBoundlessAgonyTimer;
    uint32 m_uiShadowBoltVolleyTimer;
    uint32 m_uiCheckTimer;
    uint32 m_uiNextEnrageTimer;

    bool bBanished;
    bool bEnraged;
    bool bCheck;

    void Reset()
    {
       if (m_pInstance)
       {
            m_pInstance->SetData(DATA_KALECGOS_EVENT,NOT_STARTED);
            m_pInstance->SetData(DATA_SATHROVARR_EVENT,NOT_STARTED);
       }

        m_uiCorruptingStrikeTimer = 13000;
        m_uiCurseOfBoundlessAgonyTimer = 15000;
        m_uiShadowBoltVolleyTimer = 7000 + urand(0, 2000);
        m_uiCheckTimer = 2000;

        bBanished            = false;
        bEnraged             = false;
        bCheck               = true;

        m_uiKalecGUID = 0;
        m_uiSpectralGUID =0;

        TeleportAllPlayersBack();

        if (m_creature->HasAura(SPELL_CRAZED_RAGE))
            m_creature->RemoveAurasDueToSpell(SPELL_CRAZED_RAGE);

        if (m_creature->HasAura(SPELL_BANISH))
            m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_SATH_AGGRO, m_creature);

        if (Creature* pKalec = m_creature->SummonCreature(MOB_KALEC, m_creature->GetPositionX() + 10, m_creature->GetPositionY() + 5, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100))
        {
            m_uiKalecGUID = pKalec->GetGUID();
            m_creature->AI()->AttackStart(pKalec);
            m_creature->AddThreat(pKalec, 1000000.0f);
        }

        if (Creature* pSpectral = m_creature->SummonCreature(SPECTRAL_REALM, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, 0, TEMPSUMMON_TIMED_DESPAWN, 1200000))
            m_uiSpectralGUID = pSpectral->GetGUID();
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_SATH_DEATH, m_creature);   

        if(m_pInstance)
            m_pInstance->SetData(DATA_SATHROVARR_EVENT,DONE);
    }

    void TeleportAllPlayersBack()
    {
        std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
        if (t_list.empty())
            return;

        for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
        {
            Unit* pTarget = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid());
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                pTarget->InterruptNonMeleeSpells(true);
                pTarget->CastSpell(pTarget,SPELL_SPECTRAL_EXHAUSTION, true);
                ((Player*)pTarget)->TeleportTo(pTarget->GetMapId(), pTarget->GetPositionX(), pTarget->GetPositionY(), DRAGON_REALM_Z, pTarget->GetOrientation());
            }
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 1))
        {
            case 0: DoScriptText(SAY_SATH_SLAY1, m_creature); break;
            case 1: DoScriptText(SAY_SATH_SLAY2, m_creature); break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                return;

        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (m_uiCheckTimer < uiDiff)
            {
                TeleportAllPlayersBack();
                m_uiCheckTimer = 30000;
            }
            else m_uiCheckTimer -= uiDiff;

            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == DONE)
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
            else if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == NOT_STARTED)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, m_creature->GetOrientation());
                ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
            }

            return;
        }

        if (!bBanished)
            if (Creature* pSpectral = m_creature->GetMap()->GetCreature(m_uiSpectralGUID))
                if (m_creature->GetHealthPercent() > 1.0f)
                    if (!m_creature->IsInRange(pSpectral, 0.0f, 50.0f, true))
                    {
                        m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, m_creature->GetOrientation());
                        ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                        m_creature->AI()->EnterEvadeMode();
                    }

        //If high Aggro teleported to normal realm attack Kalec or  next target
        Unit* pWho = m_creature->getVictim();
        if(pWho && !pWho->IsInRange(m_creature, 0.0f, 50.0f, true))
        {
            m_creature->AddThreat(pWho, -100000.0f);
            if(Creature* pKalec = m_creature->GetMap()->GetCreature(m_uiKalecGUID))
            {
                m_creature->AI()->AttackStart(pKalec);
                m_creature->AddThreat(pKalec, 100000.0f);
            }
            else if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                m_creature->AddThreat(pTarget, 100000.0f);
                m_creature->AI()->AttackStart(pTarget);
            }
        } 

        if (Creature* pKalec = m_creature->GetMap()->GetCreature(m_uiKalecGUID))
            if (!pKalec->isAlive())
            {
                TeleportAllPlayersBack();
                if ((boss_sathrovarrAI*)m_creature->AI())
                {
                    ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                    m_creature->AI()->EnterEvadeMode();
                    m_creature->GetMotionMaster()->MoveTargetedHome(); 
                }
            }

        // Banish at 1% hp working
        if (!bBanished && m_creature->GetHealthPercent() < 1.0f)
        {
            //Stop  Kalecgos portal creation if not bBanished
            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) != DONE)
                m_pInstance->SetData(DATA_KALECGOS_EVENT, SPECIAL);

            TeleportAllPlayersBack();
            m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, m_creature->GetOrientation());
            DoCast(m_creature, SPELL_BANISH, true);
            bBanished = true;
        } 

        //Enrage
        if (!bEnraged)
        {         
            if (m_pInstance && m_pInstance->GetData(DATA_SATHROVARR_EVENT) == SPECIAL)
            {
                DoScriptText(SAY_SATH_ENRAGE, m_creature);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                m_uiNextEnrageTimer = 10000;
                bEnraged = true;
            }

            if (m_creature->GetHealthPercent() < 10.0f)
            {
                if (m_pInstance) 
                    m_pInstance->SetData(DATA_SATHROVARR_EVENT,SPECIAL);
                DoScriptText(SAY_SATH_ENRAGE, m_creature);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                m_uiNextEnrageTimer = 10000;
                bEnraged = true;
            }
        } 
        else if (m_uiNextEnrageTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_CRAZED_RAGE, true);
            m_uiNextEnrageTimer = 10000;
        }else m_uiNextEnrageTimer -= uiDiff;

        if (m_uiCorruptingStrikeTimer < uiDiff)
        {
            if (urand(0, 1) == 0)
            {    
                DoScriptText(SAY_SATH_SPELL2, m_creature);
            }
            if (Unit* pVictim = m_creature->getVictim())
                DoCast(pVictim, SPELL_CORRUPTING_STRIKE);
            m_uiCorruptingStrikeTimer = 13000;
        }else m_uiCorruptingStrikeTimer -= uiDiff;

        if (m_uiCurseOfBoundlessAgonyTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_CURSE_OF_BOUNDLESS_AGONY);
            m_uiCurseOfBoundlessAgonyTimer = 20000;
        }else m_uiCurseOfBoundlessAgonyTimer -= uiDiff;

        if (m_uiShadowBoltVolleyTimer < uiDiff)
        {
            if (urand(0, 1) == 0)
            {    
                DoScriptText(SAY_SATH_SPELL1, m_creature);
            }
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_SHADOW_BOLT_VOLLEY, true);
            m_uiShadowBoltVolleyTimer = 15000;
        }else m_uiShadowBoltVolleyTimer -= uiDiff;

        //Remove Arcane Bufet in spectral Realm and Teleport Players back to normal if Exhaution ends.
        if (m_uiCheckTimer < uiDiff)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            if (t_list.empty())
                return;

            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                Unit* pTarget = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid());
                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(pTarget, 40))              
                {
                    if (pTarget->HasAura(SPELL_ARCANE_BUFFET))
                        pTarget->RemoveAurasDueToSpell(SPELL_ARCANE_BUFFET);

                    if (!pTarget->HasAura(SPELL_SPECTRAL_EXHAUSTION))
                    {
                        //remove target from threat  list
                        m_creature->AddThreat(pTarget, -100000.0f);
                        pTarget->InterruptNonMeleeSpells(true);
                        pTarget->CastSpell(pTarget,SPELL_SPECTRAL_EXHAUSTION, true);
                        ((Player*)pTarget)->TeleportTo(pTarget->GetMapId(), pTarget->GetPositionX(), pTarget->GetPositionY(), DRAGON_REALM_Z, pTarget->GetOrientation());
                    }
                }
            }
            m_uiCheckTimer = 3000;
        }m_uiCheckTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

//KalecgosHuman
struct MANGOS_DLL_DECL boss_kalecAI : public ScriptedAI
{
    boss_kalecAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        m_uiSathGUID = 0;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiRevitalizeTimer;
    uint32 m_uiHeroicStrikeTimer;
    uint32 m_uiYellTimer;
    uint32 m_uiYellSequence;

    bool bSathDied;

    uint64 m_uiSathGUID;

    void Reset()
    {
        m_uiRevitalizeTimer = 5000;
        m_uiHeroicStrikeTimer = 3000;
        m_uiYellTimer = 5000;
        m_uiYellSequence = 0;

        bSathDied = false;

        if (m_pInstance)
            m_uiSathGUID = m_pInstance->GetData64(DATA_SATHROVARR);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiYellTimer < uiDiff)
        {
            switch(m_uiYellSequence)
            {
            case 0:
                DoScriptText(SAY_GOOD_AGGRO, m_creature);
                m_uiYellSequence++;
                break;
            case 1:
                if (m_creature->GetHealthPercent() < 50.0f) 
                {
                    DoScriptText(SAY_GOOD_NEAR_DEATH, m_creature);
                    m_uiYellSequence++;
                }
                break;
            case 2:
                if (m_creature->GetHealthPercent() < 10.0f) 
                {
                    DoScriptText(SAY_GOOD_NEAR_DEATH2, m_creature);
                    m_uiYellSequence++;
                }
                break;
            default:
                break;
            }
            m_uiYellTimer = 5000;
        }

        if (!bSathDied)
            if (Creature* pSath = m_creature->GetMap()->GetCreature(m_uiSathGUID))
                if (pSath && !pSath->isAlive())
                {
                    DoScriptText(SAY_GOOD_PLRWIN, m_creature);
                    bSathDied = true;
                }

        if (m_uiRevitalizeTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_REVITALIZE, true);
            m_uiRevitalizeTimer = 4000;
        }else m_uiRevitalizeTimer -= uiDiff;

        if (m_uiHeroicStrikeTimer < uiDiff)
        {
            if (m_creature->getVictim())
            DoCast(m_creature->getVictim(), SPELL_HEROIC_STRIKE);
            m_uiHeroicStrikeTimer = 2000;
        }else m_uiHeroicStrikeTimer -= uiDiff;

        DoMeleeAttackIfReady();
        }
};

//Spectral Realm Rift
bool GOkalecgos_teleporter(Player* pPlayer, GameObject* pGo)
{
    //In theory, each portal can be used by up to 10 players before it expires (pCreature) wowwiki
    if (pPlayer->HasAura(SPELL_SPECTRAL_EXHAUSTION))
    {
        pPlayer->GetSession()->SendNotification(GO_FAILED);
            return true;
    }
    else
    {
        //Aura excaustion  jako oznacznik czasu spedzonego w  spectral realmie
        pPlayer->InterruptNonMeleeSpells(true);
        pPlayer->CastSpell(pPlayer, SPELL_SPECTRAL_EXHAUSTION, true);
        pPlayer->TeleportTo(pPlayer->GetMapId(), pPlayer->GetPositionX(), pPlayer->GetPositionY(), DEMON_REALM_Z, pPlayer->GetOrientation());
        return false;
    }
}

CreatureAI* GetAI_boss_kalecgos(Creature* pCreature)
{
    return new boss_kalecgosAI(pCreature);
}

CreatureAI* GetAI_boss_sathrovarr(Creature* pCreature)
{
    return new boss_sathrovarrAI(pCreature);
}

CreatureAI* GetAI_boss_kalec(Creature* pCreature)
{
    return new boss_kalecAI(pCreature);
}

void AddSC_boss_kalecgos()
{
    Script* newscript;

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_kalecgos;
    newscript->Name = "boss_kalecgos";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_sathrovarr;
    newscript->Name = "boss_sathrovarr";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_kalec;
    newscript->Name = "boss_kalec";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="kalecgos_teleporter";
    newscript->pGOHello = &GOkalecgos_teleporter;
    newscript->RegisterSelf();
}
