/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Alythess
SD%Complete: 90%
SDComment: 
SDAuthor: Aramilpl && ScrappyDoo (c) Andeeria
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

// texts
#define YELL_TWINS_AGGRO            -1940001
#define YELL_TWINS_BOTH_DEATH        -1940002
#define YELL_TWINS_SINGLE_DEATH        -1940003
#define YELL_TWINS_ENRAGE            -1940004

#define YELL_TWINS_SPELL_STURMKNOCKBACK        -1940010 
#define YELL_TWINS_SPELL_STURMKNOCKBACK0    -1940005 
#define YELL_TWINS_SPELL_STURMKNOCKBACK1    -1940006
#define YELL_TWINS_SPELL_STURMKNOCKBACK2    -1940007
#define YELL_TWINS_SPELL_STURMKNOCKBACK3    -1940008
#define YELL_TWINS_SPELL_STURMKNOCKBACK4    -1940009 

#define YELL_ALY_SLAY                         -1941000
#define YELL_TWINS_SPELL_LOHE                 -1941001
#define YELL_TWINS_SPELL_SCHATTENKLINGEN     -1941002

#define YELL_SACRO_SLAY                         -1942000
#define YELL_TWINS_SPELL_SCHATTENNOVA         -1942001
#define YELL_TWINS_SPELL_VERWIRRENDERS         -1942002

enum Spells
{
    //Lady Sacrolash
    SPELL_DARK_TOUCHED      =   45347,
    SPELL_SHADOW_BLADES     =   45248, //10 secs
    SPELL_DARK_STRIKE       =   45271,
    SPELL_SHADOW_NOVA       =   45329, //30-35 secs
    SPELL_CONFOUNDING_BLOW  =   45256, //25 secs

    //Shadow Image spells
    SPELL_SHADOWFURY        =   45270,
    SPELL_IMAGE_VISUAL      =   45263,

    //Misc spells
    SPELL_TWINS_ENRAGE      =   46587, //27680
    SPELL_EMPOWER           =   45366,
    SPELL_DARK_FLAME        =   45345,
    AURA_CONF               =   44867, // :D

    //Grand Warlock Alythess spells
    SPELL_PYROGENICS        =   45230, //15secs
    SPELL_FLAME_TOUCHED     =   45348,
    SPELL_CONFLAGRATION     =   45342, //30-35 secs
    SPELL_CONFLAGRATION_DEV =   46768, //dmg
    SPELL_BLAZE             =   45235, //on main target every 3 secs
    SPELL_FLAME_SEAR        =   46771,

    //
    SPELL_BANISH                    = 44836,
};

enum Creatures
{
    GRAND_WARLOCK_ALYTHESS  =   25166,
    MOB_SHADOW_IMAGE        =   25214,
    LADY_SACROLASH          =   25165
};


//############################################
//################## ALYTHESS ################
//############################################

struct MANGOS_DLL_DECL boss_alythessAI : public ScriptedAI
{
    boss_alythessAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

    ScriptedInstance* pInstance;  

    uint32 m_uiPyrogenicsTimer;
    uint32 m_uiFlameTouchedTimer;
    uint32 m_uiConflagrationTimer;
    uint32 m_uiConfCount;
    uint32 m_uiConfTimer;
    uint32 m_uiBlazeTimer;
    uint32 m_uiFlameSearTimer;
    uint32 m_uiEnrageTimer;
    uint64 m_uiConfTargetGUID;
    bool m_bIsEnraged;
    bool m_bIsBanished;

    void Reset()
    {    
        m_bIsBanished = false;
        m_uiPyrogenicsTimer = 100; 
        m_uiFlameTouchedTimer = 30000; 
        m_uiConflagrationTimer = 25000 + rand()%15000;
        m_uiBlazeTimer = 1000; 
        m_uiFlameSearTimer = 15000; 
        m_uiEnrageTimer = 360000; 
        m_uiConfTimer = 300000;
        m_uiConfCount = 10;
        m_uiConfTargetGUID = 0;

        if (pInstance)
        {
            pInstance->SetData(DATA_EREDAR_TWINS_EVENT, NOT_STARTED);
            pInstance->SetData(DATA_ALYSTHESS_EVENT, NOT_STARTED);
            //pInstance->SetData(DATA_SACROLASH_EVENT, NOT_STARTED);
        }

        // Respawn Second Twin NotWorking ;p
        /*
        if(pInstance)
        {
            if(Creature* Sacrolash = ((Creature*)Unit::GetUnit(*m_creature, pInstance->GetData64(DATA_SACROLASH))))
                if(!Sacrolash->isAlive())
                    Sacrolash->Respawn();
        }
        */
        m_bIsEnraged = false;
    }

    void DamageDeal(Unit* pDoneTo, uint32& uiDamage) 
    {
        if(pDoneTo->HasAura(SPELL_DARK_TOUCHED))
            pDoneTo->RemoveAurasDueToSpell(SPELL_DARK_TOUCHED,0);
    }

    void Aggro(Unit *who)
    {
        if(pInstance)
            pInstance->SetData(DATA_EREDAR_TWINS_EVENT, IN_PROGRESS);
        m_creature->SetInCombatWithZone();
        DoScriptText(YELL_TWINS_AGGRO, m_creature);
        DoPlaySoundToSet(m_creature, 12484);
    }
    
    void KilledUnit(Unit* victim)
    {
       DoScriptText(YELL_ALY_SLAY, m_creature);
       switch(rand()%3)
       {
            case 0: DoPlaySoundToSet(m_creature, 12490); break;
            case 1: DoPlaySoundToSet(m_creature, 12491); break;
        }
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(YELL_TWINS_SINGLE_DEATH, m_creature);
        DoPlaySoundToSet(m_creature, 12488);
        if (pInstance)
        {
            pInstance->SetData(DATA_ALYSTHESS_EVENT, DONE);
        }
    }

    void UpdateAI(const uint32 diff)
    {       
        
        // return since we have no target
        if(!m_creature->SelectHostileTarget() || !m_creature->getVictim())
           return;
        
        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (pInstance && pInstance->GetData(DATA_SACROLASH_EVENT) == DONE)
            {
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
            }

            if (pInstance && pInstance->GetData(DATA_EREDAR_TWINS_EVENT) == NOT_STARTED)
            {
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                ((boss_alythessAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
            }
            return;
        }

        /* Banish at 1% hp working */
        if (((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 1) && !m_bIsBanished)
        {
            if (pInstance && pInstance->GetData(DATA_SACROLASH_EVENT) != DONE)
            {
                pInstance->SetData(DATA_ALYSTHESS_EVENT, DONE);
                DoCast(m_creature, SPELL_BANISH, true);
                m_creature->SetVisibility(VISIBILITY_OFF);
            }
            m_bIsBanished = true;
        }

        if(m_uiConfCount = 10)
        {
            if(Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiConfTargetGUID))
                pTarget->RemoveAurasDueToSpell(AURA_CONF,0);
            ++m_uiConfCount;
        }

        if(m_uiConfCount < 10)
        {
            if(m_uiConfTimer < diff)
            {
                if (Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiConfTargetGUID))
                {
                    pTarget->CastSpell(pTarget, SPELL_CONFLAGRATION_DEV, true);

                    std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
                    for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
                        Unit *BurnedPlayer = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid());
                        if (BurnedPlayer && BurnedPlayer->GetTypeId() == TYPEID_PLAYER && BurnedPlayer->IsWithinDistInMap(pTarget, 8))
                        {
                            BurnedPlayer->CastSpell(BurnedPlayer, SPELL_CONFLAGRATION_DEV, true);
                        }
                    }    
                }
                ++m_uiConfCount;
                m_uiConfTimer = 1000;        
            }else m_uiConfTimer -= diff;
        }

        // does alysthes stand and cast spells, after someone is out of range she follows victim
        if(Unit *who = m_creature->getVictim())
        {
            if(who && who->IsInRange(m_creature, 0.0f, 15.0f, false))
                m_creature->StopMoving();
            else 
                m_creature->CanFreeMove();
        }

        // enrage
        if(m_uiEnrageTimer < diff && !m_bIsEnraged)
        {
            DoScriptText(YELL_TWINS_ENRAGE, m_creature);
            DoCast(m_creature, SPELL_TWINS_ENRAGE);
            m_bIsEnraged = true;
        }else m_uiEnrageTimer -= diff;
        
        // 100%
        if(m_uiPyrogenicsTimer < diff)
        {
            DoCast(m_creature, SPELL_PYROGENICS);
            m_uiPyrogenicsTimer = 35000;
        }else m_uiPyrogenicsTimer -= diff;
        
        // 100%
        if(m_uiFlameTouchedTimer < diff)
        {
            if(Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pVictim->CastSpell(pVictim, SPELL_FLAME_TOUCHED, true);
            m_uiFlameTouchedTimer = 30000;
        }else m_uiFlameTouchedTimer -= diff;
        
        // in progress
        if(m_uiConflagrationTimer < diff)
        {
            m_uiConfTargetGUID = 0;
            if (Unit *pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                m_uiConfTargetGUID = pVictim->GetGUID();
                pVictim->CastSpell(pVictim, AURA_CONF, true);
                pVictim->CastSpell(pVictim, SPELL_CONFLAGRATION_DEV, true);
            }
            m_uiConfTimer = 1000;
            m_uiConfCount = 0;
            m_uiConflagrationTimer = urand(20000, 21000);
        }else m_uiConflagrationTimer -= diff;
        
        // 50% nie zostawia sumona pod soba
        if(m_uiBlazeTimer < diff)
        {
            if(Unit *victim = m_creature->getVictim())
                DoCast(victim, SPELL_BLAZE);
            m_uiBlazeTimer = urand(5000,10000);
        }else m_uiBlazeTimer -= diff;
        
        // 100%
        if(m_uiFlameSearTimer < diff)
        {
            uint8 i = urand(3,5);
            for(uint8 k=0; k<i; ++k)
                if(Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0) )
                    DoCastSpellIfCan(pVictim, SPELL_FLAME_SEAR, CAST_TRIGGERED);
            m_uiFlameSearTimer = 30000;
        }else m_uiFlameSearTimer -= diff;
        
        DoMeleeAttackIfReady();
    }
};

//############################################
//################# SACROLASH ################
//############################################

struct MANGOS_DLL_DECL boss_sacrolashAI : public ScriptedAI
{
    boss_sacrolashAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
            
    ScriptedInstance* pInstance;
    
    uint32 m_uiEnrageTimer;
    uint32 m_uiDarkTouchedTimer;
    uint32 m_uiShadowNovaTimer;
    uint32 m_uiConfoundingBlowTimer;
    uint32 m_uiShadowBladesTimer;
    uint32 m_uiSummonShadowImage;
    uint64 m_uiTargetGUID[3];
    bool m_bIsEnraged;
    bool m_bIsBanished;

    void Reset()
    {    
        m_bIsBanished = false;
        m_uiEnrageTimer = 360000; 
        m_uiDarkTouchedTimer = 30000;
        m_uiShadowNovaTimer = 15000;
        m_uiConfoundingBlowTimer = 3000;
        m_uiShadowBladesTimer = 10000;
        m_uiSummonShadowImage = 30000;
        m_bIsEnraged = false;

        if (pInstance)
        {
            pInstance->SetData(DATA_EREDAR_TWINS_EVENT, NOT_STARTED);
            //pInstance->SetData(DATA_ALYSTHESS_EVENT, NOT_STARTED);
            pInstance->SetData(DATA_SACROLASH_EVENT, NOT_STARTED);
        }

        /*
        if(pInstance)
        {
            if(Creature* Alythess = ((Creature*)Unit::GetUnit(*m_creature, pInstance->GetData64(DATA_ALYTHESS))))
                if(!Alythess->isAlive())
                    Alythess->Respawn();
        }
        */
    }

    void DamageDeal(Unit* pDoneTo, uint32& uiDamage) 
    {
        if(pDoneTo->HasAura(SPELL_FLAME_TOUCHED))
            pDoneTo->RemoveAurasDueToSpell(SPELL_FLAME_TOUCHED,0);
    }

    void Aggro(Unit *who)
    {
        if(pInstance)
            pInstance->SetData(DATA_EREDAR_TWINS_EVENT, IN_PROGRESS);
        m_creature->SetInCombatWithZone();
        DoScriptText(YELL_TWINS_AGGRO, m_creature);
    }

    void KilledUnit(Unit* victim)
    {
       DoScriptText(YELL_SACRO_SLAY, m_creature);
       switch(rand()%2)
       {
            case 0: DoPlaySoundToSet(m_creature, 12486); break;
            case 1: DoPlaySoundToSet(m_creature, 12487); break;
       }
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(YELL_TWINS_SINGLE_DEATH, m_creature);
        DoPlaySoundToSet(m_creature, 12492);

        if (pInstance)
        {
            pInstance->SetData(DATA_SACROLASH_EVENT, DONE);
        }
    }

    void UpdateAI(const uint32 diff)
    {
    
        // return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (pInstance && pInstance->GetData(DATA_ALYSTHESS_EVENT) == DONE)
            {
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
            }

            if (pInstance && pInstance->GetData(DATA_EREDAR_TWINS_EVENT) == NOT_STARTED)
            {
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                ((boss_alythessAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
            }
            return;
        }

        /* Banish at 1% hp working */
        if (((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 1) && !m_bIsBanished)
        {
            if (pInstance && pInstance->GetData(DATA_ALYSTHESS_EVENT) != DONE)
            {
                pInstance->SetData(DATA_SACROLASH_EVENT, DONE);
                DoCast(m_creature, SPELL_BANISH, true);
                m_creature->SetVisibility(VISIBILITY_OFF);
            }
            m_bIsBanished = true;
        }

        // enrage
        if(m_uiEnrageTimer < diff && !m_bIsEnraged)
        {
            DoScriptText(YELL_TWINS_ENRAGE, m_creature);
            DoCast(m_creature, SPELL_TWINS_ENRAGE);
            m_bIsEnraged = true;
        }else m_uiEnrageTimer -= diff;
        
        // 100%
        if(m_uiDarkTouchedTimer < diff)
        {
            if(Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0) )
                pVictim->CastSpell(pVictim, SPELL_DARK_TOUCHED, true);
            m_uiDarkTouchedTimer = urand(10000, 13000);
        }else m_uiDarkTouchedTimer -= diff;

        // 100%
        if(m_uiShadowBladesTimer < diff)
        {
            if(Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCastSpellIfCan(pVictim, SPELL_DARK_STRIKE);
                DoCastSpellIfCan(pVictim, SPELL_SHADOW_BLADES, CAST_TRIGGERED);
            }
            m_uiShadowBladesTimer = urand(10000,13000);
        }else m_uiShadowBladesTimer -= diff;
        
        // 100%
        if(m_uiShadowNovaTimer < diff)
        {
            if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_SHADOW_NOVA);
            m_uiShadowNovaTimer = urand(30000,40000);
        }else m_uiShadowNovaTimer -= diff;
        
        // 100%
        if(m_uiConfoundingBlowTimer < diff)
        {
            if(Unit *victim = m_creature->getVictim())
                DoCast(victim, SPELL_CONFOUNDING_BLOW);
            m_uiConfoundingBlowTimer = urand(25000,30000);
        }else m_uiConfoundingBlowTimer -= diff;
        
        // 100%
        if (m_uiSummonShadowImage < diff)
        {
            for(uint8 i=0; i<3; ++i)
            {
                if(Creature *image = m_creature->SummonCreature(MOB_SHADOW_IMAGE, m_creature->GetPositionX()+urand(4,10), m_creature->GetPositionY()+urand(4,10), m_creature->GetPositionZ(), 0.0,TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    image->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    image->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    image->setFaction(14); 

                    Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                    if (image->AI() && pTarget)
                        image->AI()->AttackStart(pTarget);
                }
            }
            m_uiSummonShadowImage = urand(30000,40000);
        } else m_uiSummonShadowImage -= diff;

        DoMeleeAttackIfReady();
    }
};

//############################################
//############## SHADOW IMAGE ################
//############################################
struct MANGOS_DLL_DECL npc_shadow_imageAI : public ScriptedAI
{
    npc_shadow_imageAI(Creature *c) : ScriptedAI(c)
    {
        Reset();
    }

    ScriptedInstance* pInstance; 
    
    uint32 m_uiDarkStrikeTimer;
    uint32 m_uiShadowfuryTimer;
    
    void Aggro(Unit* target) 
    {
        m_creature->SetInCombatWithZone();
    }
    
    void Reset()
    {    
        DoCast(m_creature,SPELL_IMAGE_VISUAL,true);

        m_uiDarkStrikeTimer = 1000;
        m_uiShadowfuryTimer = 7000;
    }
    
    void UpdateAI(const uint32 diff)
    {           
        if(m_uiDarkStrikeTimer < diff)
        {
            if(Unit *victim = m_creature->getVictim())
            {
                m_creature->CastSpell(victim, SPELL_DARK_STRIKE, false);
                victim->CastSpell(victim, SPELL_DARK_TOUCHED, true);
            }
            m_uiDarkStrikeTimer = 2000;
        }else m_uiDarkStrikeTimer -= diff;
        
        if(m_uiShadowfuryTimer < diff)
        {
            if(Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                m_creature->CastSpell(target, SPELL_SHADOWFURY, false);
            m_uiShadowfuryTimer = 8000;    
        }else m_uiShadowfuryTimer -= diff;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_npc_shadow_image(Creature *_Creature)
{
    return new npc_shadow_imageAI (_Creature);
}

CreatureAI* GetAI_boss_alythess(Creature *_Creature)
{
    return new boss_alythessAI (_Creature);
}

CreatureAI* GetAI_boss_sacrolash(Creature *_Creature)
{
    return new boss_sacrolashAI (_Creature);
}

void AddSC_boss_eredar_twins()
{
    Script *newscript;
    
    newscript = new Script;
    newscript->Name = "npc_shadow_image";
    newscript->GetAI = &GetAI_npc_shadow_image;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_alythess";
    newscript->GetAI = &GetAI_boss_alythess;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_sacrolash";
    newscript->GetAI = &GetAI_boss_sacrolash;
    newscript->RegisterSelf();
}
