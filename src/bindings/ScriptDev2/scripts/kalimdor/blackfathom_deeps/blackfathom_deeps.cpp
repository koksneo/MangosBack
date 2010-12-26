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
SDName: Blackfathom Deeps
SD%Complete:
SDComment:
SDCategory: Blackfathom Deeps
EndScriptData */

/* ContentData
go_shrine - 100% - event handled blizzlike

TO_DO:
* final altar and +stats buff
* npc summoning alliance players to Darnassus

EndContentData */

#include "precompiled.h"
#include "blackfathom_deeps.h"

enum Shrines
{
    MOB_MURKSHALLOW_SOFTSHELL   = 4977,
    MOB_AKUMAI_SNAPJAW          = 4825,
    MOB_AKUMAI_SERVANT          = 4978,
    MOB_BARBED_CRUSTACEAN       = 4823
};

float SummonPosition[10][4] =
{
    // tags next to coordinates indicates "box" from where add will be 
    {-769.22f, -164.50f, -25.87f, 3.12f},  // Left -2
    {-867.86f, -164.40f, -25.87f, 6.24f},  // Right-2
    {-767.30f, -154.32f, -25.88f, 3.08f},  // Left -3
    {-866.54f, -174.97f, -25.86f, 0.05f},  // Right-1    
    {-869.19f, -153.27f, -25.88f, 6.23f},  // Right-3
    {-769.33f, -174.18f, -25.87f, 3.20f},  // Left -1
    
    // in order to not make any explicits in summon part doubled 4 rows to summort m_uiAddsToSummon == 10
    {-867.86f, -164.40f, -25.87f, 6.24f},  // Right-2
    {-869.19f, -153.27f, -25.88f, 6.23f},  // Right-3
    {-769.33f, -174.18f, -25.87f, 3.20f},  // Left -1
    {-769.22f, -164.50f, -25.87f, 3.12f}   // Left -2
};

bool GOHello_go_shrine(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!m_pInstance || !pPlayer)
        return true;

    m_pInstance->SetData(TYPE_SHRINE_EVENT,IN_PROGRESS);

    uint8 m_uiAddsToSummon = 0;
    uint32 m_uiAddEntry = 0;

    // Assign amount and entry of spawned adds 
    switch(pGo->GetEntry())
    {
        case GO_SHRINE_1:
            m_uiAddsToSummon = 10;
            m_uiAddEntry = MOB_MURKSHALLOW_SOFTSHELL;
            break;
        case GO_SHRINE_2: 
            m_uiAddsToSummon = 3;
            m_uiAddEntry = MOB_AKUMAI_SNAPJAW;
            break;
        case GO_SHRINE_3: 
            m_uiAddsToSummon = 2;
            m_uiAddEntry = MOB_BARBED_CRUSTACEAN;
            break;
        case GO_SHRINE_4:
            m_uiAddsToSummon = 2;
            m_uiAddEntry = MOB_AKUMAI_SERVANT;
            break;
        default: break;
    }

    for (uint8 i = 0; i < m_uiAddsToSummon; ++i)
    {
        if (Creature* pSummon = pGo->SummonCreature(m_uiAddEntry, SummonPosition[i][0],SummonPosition[i][1],SummonPosition[i][2],SummonPosition[i][3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000))
        {
            // If summon successfully spawned lets make him attack
            pSummon->AI()->AttackStart(pPlayer);
            // and increase counter of adds
            m_pInstance->SetData(DATA_SHRINE_SUMMONS,IN_PROGRESS);
        }
    }
    return false;
}

void AddSC_blackfathom_deeps()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_shrine";
    newscript->pGOHello = &GOHello_go_shrine;
    newscript->RegisterSelf();
}
