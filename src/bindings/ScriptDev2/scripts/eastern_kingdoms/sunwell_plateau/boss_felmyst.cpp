/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
 
/* ScriptData
SDName: Boss_Felmyst
SD%Complete: 75%
SDComment: PlayAble
SDCategory: Sunwell Plateau
SDAuthot: Scrappy Doo
EndScriptData */
 
/* ToDo
Land Phase          = 100%
Fly Phase           = 50%
DeatchCloud Spell   = 50%
*/

#include "precompiled.h"
#include "sunwell_plateau.h"
 
enum Sounds
{
    YELL_AGGRO          = -1930000,
    YELL_CLEAVE         = -1930001,
    YELL_CORROSION      = -1930002,
    YELL_NOXIOUSFUMES   = -1930003,
    YELL_SLAY1          = -1930004,
    YELL_SLAY2          = -1930005,
    YELL_SLAY3          = -1930006,
    YELL_DEATH          = -1930007,
};

enum Spells
{
    //Aura
    SPELL_SUNWELLRADIANCE_AURA  = 45769,
    SPELL_NOXIOUSFUMES_AURA     = 47002,
 
    //Land Phase
    SPELL_CLEAVE                = 19983, 
    SPELL_CORROSION             = 45866,
    SPELL_GASNOVA               = 45855,
    SPELL_ENCAPSULATE_CHANNEL   = 45661,
    SPELL_ENCAPSULATE_AOE       = 45662,
   
    //Flight Phase
    SPELL_VAPOR_DAMAGE          = 46931, // vapor damage, 4000
    SPELL_TRAIL_TRIGGER         = 45399, // trail to self, trigger 454
   
    //Other
    SPELL_ENRAGE                = 26662,
    SPELL_BERSERK               = 45078,

    //Fog of Mind Control
    SPELL_FOG_TRIGGER           = 45582, // Visual Effect
    SPELL_FOG_CHARM             = 45717, // Damage, Speed Increased
    SPELL_KILL                  = 5,

    //Image Of Players Spells
    SPELL_PRIEST                = 47077, // 100%
    SPELL_PALADIN               = 37369, // 100%
    SPELL_PALADIN2              = 37369, // 100%
    SPELL_WARLOCK               = 46190, // 100%
    SPELL_WARLOCK2              = 47076, // 100%
    SPELL_MAGE                  = 47074, // 100%
    SPELL_ROGUE                 = 45897, // 100%
    SPELL_WARRIOR               = 17207, // 100%
    SPELL_DRUID                 = 47072, // 100%
    SPELL_SHAMAN                = 47071, // 100%
    SPELL_HUNTER                = 48098, // 100%
};
 
enum Creatures
{
    MOB_FELMYST         = 25038,
    MOB_DEAD            = 25268, //undead podczas fly fazy
 
    MOB_MADRIGOSA       = 25160,
    MOB_FELMYST_VISUAL  = 25041,
    MOB_FLIGHT_LEFT     = 25357,
    MOB_FLIGHT_RIGHT    = 25358,
 
    MOB_VAPOR           = 25265,
    MOB_VAPOR_TRAIL     = 25267,

    MOB_DEATH_CLOUD     = 25703,

    CREATURE_IMAGE      = 25708,
};
 
struct MANGOS_DLL_DECL boss_felmystAI : public ScriptedAI
{
    boss_felmystAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

    ScriptedInstance* pInstance;
 
    //Ground Phase
    uint64 m_uiEncapsulateGUID;
    uint32 m_uiEnrageTimer;
    uint32 m_uiFlyPhaseTimer;
    uint32 m_uiNoxiousFumesTimer;
    uint32 m_uiCorrosionTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiEncapsulateTimer;
    uint32 m_uiGasNovaTimer;
    uint32 m_uiEncapsulateAOETimer;
    uint8  m_uiEncapsulateCount;
    uint8  m_uiMaxBreathCount;

    float m_fPosX;
    float m_fPosY;
    float m_fPosZ;

    bool m_bIsCastedNoxiousFumes;
    bool m_bIsFlyPhase;
 
    //FlyPhase Timers
    uint64 m_uiVictimGUID;
    uint32 m_uiDemonicVaporTimer;
    uint32 m_uiFogOfCorruptionTimer;
    uint32 m_uiLandPhaseTimer;
    uint32 m_uiDemonicVaporInitTimer;
    uint32 m_uiFogStartTimer;
    uint8  m_uiBreathCount;
    uint8  m_uiFogCount;
    uint8  m_uiMaxFogCount;

    bool m_bIsFogOfCorruption;
 
    void Reset()
    {
        //Ground Phase
        m_uiEncapsulateGUID     = 0;
        m_uiEnrageTimer         = 600000;
        m_uiFlyPhaseTimer       = 60000;
        m_uiNoxiousFumesTimer   = 1000;
        m_uiCorrosionTimer      = 29000;
        m_uiCleaveTimer         = 27000;
        m_uiEncapsulateTimer    = 18000;
        m_uiGasNovaTimer        = 25000;
        m_uiEncapsulateCount    = 6;

        m_bIsCastedNoxiousFumes = false;
        m_bIsFlyPhase           = false;

        //FlyPhase Timers
        m_uiVictimGUID            = 0;
        m_uiFogOfCorruptionTimer  = 5000;
        m_uiDemonicVaporInitTimer = 120000;
        m_uiBreathCount         = 10;
        m_uiFogCount            = 4;
        m_uiMaxBreathCount      = 2;
        m_uiMaxFogCount         = 3;

        m_fPosX                 = 0;
        m_fPosY                 = 0;
        m_fPosZ                 = 0;

        m_bIsFogOfCorruption    = false;

        //Event Resets
        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->setFaction(35);

        if(pInstance)
            pInstance->SetData(DATA_FELMYST_EVENT, NOT_STARTED);

        if(!m_creature->HasAura(SPELL_SUNWELLRADIANCE_AURA))
            DoCast(m_creature, SPELL_SUNWELLRADIANCE_AURA);
    }
 
    void Aggro(Unit *who)
    {
        m_creature->SetInCombatWithZone();
        DoScriptText(YELL_AGGRO, m_creature);
 
        if (pInstance)
            pInstance->SetData(DATA_FELMYST_EVENT, IN_PROGRESS);
    }
 
    void KilledUnit(Unit* victim)
    {
        switch(rand()%3)
        {
            case 0: DoScriptText(YELL_SLAY1, m_creature); break;
            case 1: DoScriptText(YELL_SLAY2, m_creature); break;
            case 2: DoScriptText(YELL_SLAY3, m_creature); break;
        }
        switch(rand()%2)
        {
            case 0: DoPlaySoundToSet(m_creature, 12480); break;
            case 1: DoPlaySoundToSet(m_creature, 12481); break;
        }
    }
 
    void JustDied(Unit* Killer)
    {
        DoScriptText(YELL_DEATH, m_creature);
        DoPlaySoundToSet(m_creature, 12483);

        if(pInstance)
            pInstance->SetData(DATA_FELMYST_EVENT, DONE);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if(pInstance && pInstance->GetData(DATA_BRUTALLUS_EVENT) == DONE && pInstance->GetData(DATA_FELMYST_EVENT) == NOT_STARTED)
        {
            m_creature->SetVisibility(VISIBILITY_ON);
            m_creature->setFaction(14);
        }
 
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
 
        if(m_uiEncapsulateCount < 5)
        {
            if(m_uiEncapsulateAOETimer < diff)
            {
                if(Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiEncapsulateGUID))
                {
                    pTarget->CastSpell(pTarget, SPELL_ENCAPSULATE_AOE, true);
                    ++m_uiEncapsulateCount;
                }
                m_uiEncapsulateAOETimer = 1000;

            }else m_uiEncapsulateAOETimer -= diff;
            return;
        }

        if(m_uiEnrageTimer < diff)
        {
            DoCast(m_creature, SPELL_ENRAGE, true);
            m_uiEnrageTimer = 30000;
        }m_uiEnrageTimer -= diff;
 
        if(!m_bIsFlyPhase)
        {
            if(m_uiFlyPhaseTimer < diff)
            {
                //Stop Moving
                m_creature->StopMoving();
                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMotionMaster()->MoveIdle();
                //Go Fly
                m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+20, m_creature->GetOrientation());     
                //FlyPhase Timers Start
                m_uiDemonicVaporInitTimer   = 5000;
                m_uiLandPhaseTimer          = 120000;
                m_uiFogStartTimer           = 40000;
                m_uiMaxFogCount             = 0;
                m_uiMaxBreathCount      = 0;
                m_bIsFlyPhase           = true;

                if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    pTarget->GetPosition(m_fPosX, m_fPosY, m_fPosZ);
                    return;
                }
            }else m_uiFlyPhaseTimer -= diff;
 
            //100%
            if(m_uiCorrosionTimer < diff)
            {
                DoScriptText(YELL_CORROSION, m_creature);
                if(m_creature->getVictim())
                    DoCast(m_creature->getVictim(), SPELL_CORROSION);
                m_uiCorrosionTimer = 24000;
            }else m_uiCorrosionTimer -= diff;
 
            //100%
            if(m_uiNoxiousFumesTimer < diff && !m_bIsCastedNoxiousFumes)
            {
                DoScriptText(YELL_NOXIOUSFUMES, m_creature);
                DoPlaySoundToSet(m_creature, 12478);
                DoCast(m_creature, SPELL_NOXIOUSFUMES_AURA);
                m_bIsCastedNoxiousFumes = true;
            }else m_uiNoxiousFumesTimer -= diff;
 
            //100%
            if(m_uiGasNovaTimer < diff)
            {
                DoCast(m_creature, SPELL_GASNOVA);
                m_uiGasNovaTimer = 25000;
            }else m_uiGasNovaTimer -= diff;
 
            //100%
            if(m_uiEncapsulateTimer < diff)
            {
                if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    m_uiEncapsulateGUID = pTarget->GetGUID();
                    DoCastSpellIfCan(pTarget, SPELL_ENCAPSULATE_CHANNEL);
                }
                m_uiEncapsulateTimer = 18000;
                m_uiEncapsulateAOETimer = 3000;
                m_uiEncapsulateCount = 0;
            }else m_uiEncapsulateTimer -= diff;
 
            //100%
            if(m_uiCleaveTimer < diff)
            {
                DoScriptText(YELL_CLEAVE, m_creature);

                if(m_creature->getVictim())
                    DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                m_uiCleaveTimer = 28000;
            }else m_uiCleaveTimer -= diff;
 
            DoMeleeAttackIfReady();
        }
        else
        {
            if((m_uiLandPhaseTimer < diff) && (m_uiMaxFogCount > 1))
            {
                m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()-20, m_creature->GetOrientation());
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                m_uiFlyPhaseTimer       = 60000;
                m_bIsFlyPhase           = false;
                return;
            }else m_uiLandPhaseTimer -= diff;

            if(m_uiDemonicVaporInitTimer < diff)
            {
                if(m_uiMaxBreathCount < 2)
                {
                    if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        m_uiVictimGUID = pTarget->GetGUID();
                        DoCastSpellIfCan(pTarget, SPELL_VAPOR_DAMAGE, CAST_TRIGGERED);
                        for(uint8 i=0; i<10; ++i) // i<10
                        {
                            Creature *Undead = m_creature->SummonCreature(MOB_DEAD, pTarget->GetPositionX()+urand(1,20), pTarget->GetPositionY()+urand(1,20), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
                            if(Undead && Undead->AI())
                                Undead->AI()->AttackStart(pTarget);
                        }
                    }
                    ++m_uiMaxBreathCount;
                    m_uiBreathCount = 0;
                    m_uiDemonicVaporTimer = 1000;
                    m_uiDemonicVaporInitTimer = 15000;
                }
            }else m_uiDemonicVaporInitTimer -= diff;

            if(m_uiDemonicVaporTimer < diff)
            {
                if(m_uiBreathCount < 5)
                {
                    if(Unit* pVictim = m_creature->GetMap()->GetUnit(m_uiVictimGUID))
                        m_creature->SummonCreature(MOB_VAPOR, pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 20000);
                    m_uiDemonicVaporTimer = 2000;
                    ++m_uiBreathCount;
                }
            }else m_uiDemonicVaporTimer -= diff;
            
            if((m_uiFogStartTimer < diff) && (m_uiMaxFogCount < 3))
            {
                switch(m_uiMaxFogCount)
                {
                    case 0: 
                        m_fPosX = 1463.829f;
                        m_fPosY = 611.512f;
                        m_fPosZ = 21.57f;
                        break;
                    case 1:
                        m_fPosX = 1471.506f;
                        m_fPosY = 591.810f;
                        m_fPosZ = 22.206f;
                        break;
                    case 2:
                        m_fPosX = 1502.767f;
                        m_fPosY = 599.811f;
                        m_fPosZ = 26.612f; 
                        m_uiLandPhaseTimer = 25000;
                        break;
                }
                m_bIsFogOfCorruption        = true;
                m_uiFogOfCorruptionTimer    = 2000;
                m_uiFogCount                = 0;
                ++m_uiMaxFogCount;
                m_uiFogStartTimer = 20000;
            }else m_uiFogStartTimer -= diff;

            if((m_uiFogOfCorruptionTimer < diff) && m_bIsFogOfCorruption)
            {
                switch(m_uiFogCount)
                {
                    case 0: m_creature->SummonCreature(MOB_DEATH_CLOUD, m_fPosX+30, m_fPosY+30, m_fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 10000); break;
                    case 1: m_creature->SummonCreature(MOB_DEATH_CLOUD, m_fPosX+15, m_fPosY+15, m_fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 10000); break;
                    case 2: m_creature->SummonCreature(MOB_DEATH_CLOUD, m_fPosX-15, m_fPosY-15, m_fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 10000); break;
                    case 3: m_creature->SummonCreature(MOB_DEATH_CLOUD, m_fPosX-30, m_fPosY-30, m_fPosZ, 0, TEMPSUMMON_TIMED_DESPAWN, 10000); m_bIsFogOfCorruption = false; break;
                }
                ++m_uiFogCount;
                m_uiFogOfCorruptionTimer = 2000;
            }else m_uiFogOfCorruptionTimer -= diff;
        }
    }
};
 
//DeatchCloud 100yard range -> mind control
struct MANGOS_DLL_DECL mob_deathcloudAI : public Scripted_NoMovementAI
{
    mob_deathcloudAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = (ScriptedInstance*)c->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
 
    uint64 m_uiImageGUID[25][2];
    uint32 m_uiCheckTimer;
    uint32 m_uiImageCount;
    uint32 m_uiImageCastTimer;
 
    void Reset()
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);
 
        m_uiCheckTimer      = 1000;
        m_uiImageCount      = 0;
        m_uiImageCastTimer  = 8000;
 
        DoCast(m_creature,SPELL_FOG_TRIGGER, true);
 
        for(uint8 i=0; i<25; ++i)
        {
            m_uiImageGUID[i][0] = 0;
            m_uiImageGUID[i][1] = 0;
        }
    }

    void Aggro(Unit* who)
    {
        m_creature->SetInCombatWithZone();
    }

    void SummonImageOf(Unit* victim)
    {
        uint32 m_uiSpell;
        switch(victim->getClass())
        {
            case CLASS_PRIEST:  m_uiSpell = SPELL_PRIEST; break;
            case CLASS_PALADIN: m_uiSpell = SPELL_PALADIN; break;
            case CLASS_WARLOCK: m_uiSpell = SPELL_WARLOCK; break;
            case CLASS_MAGE:    m_uiSpell = SPELL_MAGE; break;
            case CLASS_ROGUE:   m_uiSpell = SPELL_ROGUE; break;
            case CLASS_WARRIOR: m_uiSpell = SPELL_WARRIOR; break;
            case CLASS_DRUID:   m_uiSpell = SPELL_DRUID; break;
            case CLASS_SHAMAN:  m_uiSpell = SPELL_SHAMAN; break;
            case CLASS_HUNTER:  m_uiSpell = SPELL_HUNTER; break;
        }
        Creature* cImage = m_creature->SummonCreature(CREATURE_IMAGE, victim->GetPositionX(), victim->GetPositionY(), victim->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
        if(cImage)
        {
            cImage->setFaction(14);
            cImage->AI()->AttackStart(cImage->getVictim());
            cImage->SetDisplayId(victim->GetDisplayId());
            m_uiImageGUID[m_uiImageCount][0] = cImage->GetGUID();
            m_uiImageGUID[m_uiImageCount][1] = m_uiSpell;
            ++m_uiImageCount;
        }
        m_creature->CastSpell(victim, SPELL_KILL, false);
    }

    void UpdateAI(const uint32 diff)
    {
        //Image Attacks Timer
        if(m_uiImageCastTimer < diff)
        {
            for(uint8 i=0; i<m_uiImageCount; ++i)
            {
                if(Creature* cImage = m_creature->GetMap()->GetCreature(m_uiImageGUID[i][0]))
                {
                    if(!cImage->isDead())
                    {
                        if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                            cImage->CastSpell(pTarget, m_uiImageGUID[i][1], true);
                    }
                }
            }
            m_uiImageCastTimer = 8000;
        }else m_uiImageCastTimer -= diff;

        if(m_uiCheckTimer < diff)
        {
            //For Now we need to kill player and replace him by image (sinister from kiljaeden)
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                if(Unit *target = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
                    if(target && target->GetTypeId() == TYPEID_PLAYER && target->IsWithinDistInMap(m_creature, 20))
                    {
                        //Kill Player
                        SummonImageOf(target);
                    }
            }
            m_uiCheckTimer = 3000;
        }else m_uiCheckTimer -= diff;  
    }
};
 
//Chmura AOE + sumon szkieletow in range
struct MANGOS_DLL_DECL mob_felmyst_vaporAI : public Scripted_NoMovementAI
{
    mob_felmyst_vaporAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = (ScriptedInstance*)c->GetInstanceData();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
    uint32 m_uiCheckTimer;
 
    void Reset()
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);
 
        m_uiCheckTimer = 1000;
 
        DoCast(m_creature,SPELL_TRAIL_TRIGGER, true);
    }
 
    void Aggro(Unit* who)
    {
        m_creature->SetInCombatWithZone();           
    }

    void UpdateAI(const uint32 diff)
    {
        //Summon Sceletons if Someone is near m_creature.
        if (m_uiCheckTimer < diff)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                if(Unit *target = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
                    if(target && target->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(target, 3))
                    {
                        Creature *Undead = m_creature->SummonCreature(MOB_DEAD, m_creature->GetPositionX()+urand(1,6), target->GetPositionY()+urand(1,6), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
                        if(Undead)
                            Undead->AI()->AttackStart(target);
                    }
            }
            m_uiCheckTimer = 3000;
        }m_uiCheckTimer -= diff;
    }
};
 
CreatureAI* GetAI_mob_deathcloud(Creature* _Creature)
{
    return new mob_deathcloudAI(_Creature);
}
 
CreatureAI* GetAI_mob_felmyst_vapor(Creature* _Creature)
{
    return new mob_felmyst_vaporAI(_Creature);
}
 
CreatureAI* GetAI_boss_felmyst(Creature *_Creature)
{
    return new boss_felmystAI(_Creature);
}
 
void AddSC_boss_felmyst()
{
    Script *newscript;
 
    newscript = new Script;
    newscript->Name = "boss_felmyst";
    newscript->GetAI = &GetAI_boss_felmyst;
    newscript->RegisterSelf();
 
    newscript = new Script;
    newscript->Name="mob_felmyst_vapor";
    newscript->GetAI = &GetAI_mob_felmyst_vapor;
    newscript->RegisterSelf();
 
    newscript = new Script;
    newscript->Name = "mob_deathcloud";
    newscript->GetAI = &GetAI_mob_deathcloud;
    newscript->RegisterSelf();
}