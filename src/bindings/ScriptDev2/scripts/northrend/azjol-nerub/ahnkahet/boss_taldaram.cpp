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
SDName: Boss_Taldaram
SD%Complete: 20%
SDComment:
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"
#include "ahnkahet.h"

enum
{
    SAY_AGGRO                       = -1619008,
    SAY_VANISH_1                    = -1619009,
    SAY_VANISH_2                    = -1619010,
    SAY_FEED_1                      = -1619011,
    SAY_FEED_2                      = -1619012,
    SAY_SLAY_1                      = -1619013,
    SAY_SLAY_2                      = -1619014,
    SAY_SLAY_3                      = -1619015,
    SAY_DEATH                       = -1619016,

    SPELL_BLOODTHIRST               = 55968,
    SPELL_CONJURE_FLAME_SPHERE      = 55931,
    SPELL_EMBRACE_OF_VAMPIRE        = 55959,
    H_SPELL_EMBRACE_OF_VAMPIRE      = 59513,
    SPELL_VANISH                    = 55964,
    SPELL_SHADOWSTEP_DUMMY          = 55965,
    SPELL_SHADOWSTEP_TELEPORT       = 55966,

    // dummy effect related spells
    SPELL_SUMMON_SPHERE_1           = 55895,
    SPELL_SUMMON_SPHERE_2           = 59511,
    SPELL_SUMMON_SPHERE_3           = 59512,
    SPELL_SPHERE_SUMMON_EFFECT      = 55891,
    SPELL_SPHERE_VISUAL             = 55928,
    SPELL_FLAME_SPHERE_PERIODIC     = 55926,
    H_SPELL_FLAME_SPHERE_PERIODIC   = 59508,
    SPELL_FLAME_SPHERE_DEATH_EFFECT = 55947,

    NPC_SPHERE_1                    = 30106,
    NPC_SPHERE_2                    = 31686,
    NPC_SPHERE_3                    = 31687
};


/*######
## boss_taldaram
######*/

struct MANGOS_DLL_DECL boss_taldaramAI : public ScriptedAI
{
    boss_taldaramAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool bVanished;
    bool bEmbraseSpeak;
    bool bAggroed;
    uint32 m_uiConjureSphereTimer;
    uint32 m_uiVanishTimer;
    uint32 m_uiBloodthirstTimer;
    uint32 m_uiEmbraseSpeachTimer;
    uint32 uiDmgTaken;

    void Reset()
    {
        m_uiConjureSphereTimer = 10000;
        m_uiVanishTimer = 15000;
        m_uiBloodthirstTimer = 3000;
        m_uiEmbraseSpeachTimer = 6000;
        uiDmgTaken = 0;
        bVanished = false;
        bEmbraseSpeak = false;
        bAggroed = false;
    }

    void Aggro(Unit* pWho)
    {
        // looks like Vanish is removing creature from combat
        if(!bAggroed)
        {
            DoScriptText(SAY_AGGRO, m_creature);
            bAggroed = true;
        }
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (!uiDamage)
            return;

        if (bVanished)
            uiDmgTaken = uiDmgTaken + uiDamage;

        // remove auras 
        if (m_bIsRegularMode)
        {
            if (uiDmgTaken > 20000)
            {
                m_creature->InterruptNonMeleeSpells(false, SPELL_EMBRACE_OF_VAMPIRE);
                bVanished = false;
                uiDmgTaken = 0;
            }
        }
        else if (uiDmgTaken > 40000)
        {
            m_creature->InterruptNonMeleeSpells(false, H_SPELL_EMBRACE_OF_VAMPIRE);
            bVanished = false;
            uiDmgTaken = 0;
        }
    }


    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TALDARAM, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiConjureSphereTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CONJURE_FLAME_SPHERE);
            m_uiConjureSphereTimer = urand(30000, 45000);
        }else m_uiConjureSphereTimer -= uiDiff;

        if (m_uiVanishTimer <= uiDiff)
        {
            DoScriptText(urand(0, 1)> 0 ? SAY_VANISH_1 : SAY_VANISH_2, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_SHADOWSTEP_DUMMY);
            m_uiVanishTimer = urand(30000, 45000);
            uiDmgTaken = 0;
            bVanished = true;
            bEmbraseSpeak = true;
        }else m_uiVanishTimer -= uiDiff;

        if (bEmbraseSpeak)
        {
            if (m_uiEmbraseSpeachTimer <= uiDiff)
            {
                DoScriptText(urand(0, 1)> 0 ? SAY_FEED_1 : SAY_FEED_2, m_creature);
                bEmbraseSpeak = false;
                m_uiEmbraseSpeachTimer = 9000;
            } else m_uiEmbraseSpeachTimer -= uiDiff;
        }

        if (m_uiBloodthirstTimer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_BLOODTHIRST);
            m_uiBloodthirstTimer = urand(3000, 5000);
        }else m_uiBloodthirstTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

bool EffectDummyCreature_boss_taldaram(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    if (uiSpellId == SPELL_CONJURE_FLAME_SPHERE)
    {
        pCaster->CastSpell(pCaster, SPELL_SUMMON_SPHERE_1, true);
        
        if (pCaster->GetMap()->IsDungeon() && !pCaster->GetMap()->IsRegularDifficulty())
        {
            pCaster->CastSpell(pCaster, SPELL_SUMMON_SPHERE_2, true);
            pCaster->CastSpell(pCaster, SPELL_SUMMON_SPHERE_3, true);
        }
        return true;
    }
    return false;
}

CreatureAI* GetAI_boss_taldaram(Creature* pCreature)
{
    return new boss_taldaramAI(pCreature);
}

struct MANGOS_DLL_DECL mob_flame_sphereAI : public ScriptedAI
{
    mob_flame_sphereAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    };

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    void Reset() 
    {
        if (m_pInstance)
            if (Creature* pTaladaram = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_TALADARAN)))
            {
                float x, y, z;
                float fDistance = 50.0f;
                pTaladaram->GetPosition(x, y, z);
                // lets make them spawn over taldarams head
                z += 8.0f;
                m_creature->Relocate(x, y, z);
                m_creature->CastSpell(m_creature, SPELL_SPHERE_VISUAL, true);
                //pSummoned->CastSpell(pSummoned, SPELL_SPHERE_SUMMON_EFFECT, true);
                float destination_x, destination_y;
                // lets spawn them in the angles of triangle (none of function GetClosePoint, GetNearestPoint done the job:/)
                switch (m_creature->GetEntry())
                {
                    case NPC_SPHERE_1:
                        destination_x = x - sqrt(fDistance * fDistance * 2/3);
                        destination_y = y - fDistance * 1/3;
                        break;
                    case NPC_SPHERE_2:
                        destination_x = x + sqrt(fDistance * fDistance * 2/3);
                        destination_y = y - fDistance * 1/3;
                        break;
                    case NPC_SPHERE_3:
                        destination_x = x;
                        destination_y = y + fDistance * 2/3;
                        break;
                    default: break;
                }
                m_creature->GetMotionMaster()->MovePoint(0, destination_x, destination_y, z);
                m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_FLAME_SPHERE_PERIODIC : H_SPELL_FLAME_SPHERE_PERIODIC, false,0,0,pTaladaram->GetGUID());
            }
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == 0)
        {
            m_creature->RemoveAllAuras();
            DoCast(m_creature, SPELL_FLAME_SPHERE_DEATH_EFFECT,true);
        }
    }
    void MoveInLineOfSight(Unit* pWho) {}
    void AttackedBy(Unit* pWho) {}
};

CreatureAI* GetAI_mob_flame_sphere(Creature* pCreature)
{
    return new mob_flame_sphereAI(pCreature);
}

/*######
## go_nerubian_device
######*/

bool GOHello_go_nerubian_device(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    pInstance->SetData(TYPE_TALDARAM, SPECIAL);
    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
    return false;
}

void AddSC_boss_taldaram()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_taldaram";
    newscript->GetAI = &GetAI_boss_taldaram;
    newscript->pEffectDummyCreature = &EffectDummyCreature_boss_taldaram;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_nerubian_device";
    newscript->pGOHello = &GOHello_go_nerubian_device;
    newscript->RegisterSelf();

     newscript = new Script;
     newscript->Name = "mob_flame_sphere";
     newscript->GetAI = &GetAI_mob_flame_sphere;
     newscript->RegisterSelf();
}
