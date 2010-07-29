/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
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

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "Database/SQLStorage.h"
#include "Database/SQLStorageImpl.h"
#include "Policies/SingletonImp.h"
#include "ProgressBar.h"
#include "AreaTriggerDevelop.h"

INSTANTIATE_SINGLETON_1( AreaTriggerDevelop );

AreaTriggerDevelop::AreaTriggerDevelop()
{
}

AreaTriggerDevelop::~AreaTriggerDevelop()
{
}

void AreaTriggerDevelop::LoadAreaTriggerDevelop()
{
    mAreaTriggerDevelopMap.clear();

    QueryResult *result = WorldDatabase.Query("SELECT id, type, action FROM areatrigger_develop");
    
    if(!result)
    {
        barGoLink bar(1);

        bar.step();

        sLog.outString();
        sLog.outString(">> Loaded 0 area trigger develop. DB table 'area_trigger_develop' is empty.");
        return;
    }
    
    barGoLink bar((int)result->GetRowCount());

    do
    {
        Field *fields = result->Fetch();

        uint32 id = fields[0].GetUInt32();
        AreaTriggerDevelopStructure& data = mAreaTriggerDevelopMap[id];

        data.ID = id;
        data.Type = fields[1].GetUInt32();
        data.Action = fields[2].GetUInt32();

    }while(result->NextRow());

    delete result;

    sLog.outString();
    sLog.outString( ">> Loaded %lu area trigger develop", (unsigned long)mAreaTriggerDevelopMap.size() );
}