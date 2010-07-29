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

#ifndef __AREATRIGGERDEVELOP_H
#define __AREATRIGGERDEVELOP_H

#include "Common.h"
#include "Policies/Singleton.h"
#include <string>

struct AreaTriggerDevelopStructure
{
    uint32  ID;
    uint32  Type;
    uint32  Action;
};

typedef UNORDERED_MAP<uint8, AreaTriggerDevelopStructure> AreaTriggerDevelopMap;

// TYPE areatrigger_develop
#define AREATRIGGER_DEVELOP_NOPVP           1               // for develop, set no pvp

#define AREATRIGGER_DEVELOP_ZONE            1               // for zone actions
#define AREATRIGGER_DEVELOP_AREA            2               // for area actions

class AreaTriggerDevelop
{
    public:
        AreaTriggerDevelop();
        ~AreaTriggerDevelop();

        void LoadAreaTriggerDevelop();

        AreaTriggerDevelopStructure const* GetAreaTriggerDevelop(uint32 Id)
        {
            AreaTriggerDevelopMap::const_iterator map_itr = mAreaTriggerDevelopMap.find(Id);
            if(map_itr != mAreaTriggerDevelopMap.end())
                return &map_itr->second;

            return NULL;
        }

    private:
        AreaTriggerDevelopMap   mAreaTriggerDevelopMap;
};

#define sAreaTriggerDevelop MaNGOS::Singleton<AreaTriggerDevelop>::Instance()
#endif