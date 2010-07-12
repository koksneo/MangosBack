/*
 * DBC to SQL Converter
 * Copyright (C) 2009  David Vas, Anubisss
 * <http://code.google.com/p/dbctosql/>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ACHIEVEMENT_CRITERIA_H__
#define __ACHIEVEMENT_CRITERIA_H__

char const *ACHIEVEMENT_CRITERIA_DBC    = "Achievement_Criteria.dbc";
char const *ACHIEVEMENT_CRITERIA_SQL    = "achievement_criteria_dbc.sql";
char const *ACHIEVEMENT_CRITERIA_TABLE  = "dbc_achievement_criteria";

#define ACHIEVEMENT_CRITERIA_DBC_CLIENT_BUILD   9947 // 3.1.3

#define ACHIEVEMENT_CRITERIA_DBC_COLUMN_NUMS    31
#define ACHIEVEMENT_CRITERIA_DBC_ROWS_NUMS      6682

// Achievement_Criteria.dbc struct: TrinityCore2 r4907
char const *achievement_criteria_translation[ACHIEVEMENT_CRITERIA_DBC_COLUMN_NUMS][2] =
{
    {"uint32",  "id"},          // ID
    {"uint32",  "1"},           // referredAchievement
    {"uint32",  "2"},           // requiredType
    {"uint32",  "3"},
    {"uint32",  "4"},
    {"uint32",  "5"},
    {"uint32",  "6"},
    {"uint32",  "7"},
    {"uint32",  "8"},
    {"char*",   "9"},           // name[0]
    {"char*",   "10"},          // name[1]
    {"char*",   "11"},          // name[2]
    {"char*",   "12"},          // name[3]
    {"char*",   "13"},          // name[4]
    {"char*",   "14"},          // name[5]
    {"char*",   "15"},          // name[6]
    {"char*",   "16"},          // name[7]
    {"char*",   "17"},          // name[8]
    {"char*",   "18"},          // name[9]
    {"char*",   "19"},          // name[10]
    {"char*",   "20"},          // name[11]
    {"char*",   "21"},          // name[12]
    {"char*",   "22"},          // name[13]
    {"char*",   "23"},          // name[14]
    {"char*",   "24"},          // name[15]
    {"uint32",  "25"},          // name_flags
    {"uint32",  "26"},          // completionFlag
    {"uint32",  "27"},          // groupFlag
    {"uint32",  "28"},          // unk1
    {"uint32",  "29"},          // timeLimit
    {"uint32",  "30"}           // showOrder
};

char const *ACHIEVEMENT_CRITERIA_TABLE_INDEX = achievement_criteria_translation[0][1];

#endif
