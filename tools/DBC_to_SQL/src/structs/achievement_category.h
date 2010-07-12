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

#ifndef __ACHIEVEMENT_CATEGORY_H__
#define __ACHIEVEMENT_CATEGORY_H__

char const *ACHIEVEMENT_CATEGORY_DBC    = "Achievement_Category.dbc";
char const *ACHIEVEMENT_CATEGORY_SQL    = "achievement_category_dbc.sql";
char const *ACHIEVEMENT_CATEGORY_TABLE  = "dbc_achievement_category";

#define ACHIEVEMENT_CATEGORY_DBC_CLIENT_BUILD   9947 // 3.1.3

#define ACHIEVEMENT_CATEGORY_DBC_COLUMN_NUMS    20
#define ACHIEVEMENT_CATEGORY_DBC_ROWS_NUMS      82

// Achievement_Category.dbc struct: TrinityCore2 r4907
char const *achievement_category_translation[ACHIEVEMENT_CATEGORY_DBC_COLUMN_NUMS][2] =
{
    {"uint32",  "id"},          // ID
    {"int32",   "1"},           // parentCategory
    {"char*",   "2"},           // name[0]
    {"char*",   "3"},           // name[1]
    {"char*",   "4"},           // name[2]
    {"char*",   "5"},           // name[3]
    {"char*",   "6"},           // name[4]
    {"char*",   "7"},           // name[5]
    {"char*",   "8"},           // name[6]
    {"char*",   "9"},           // name[7]
    {"char*",   "10"},          // name[8]
    {"char*",   "11"},          // name[9]
    {"char*",   "12"},          // name[10]
    {"char*",   "13"},          // name[11]
    {"char*",   "14"},          // name[12]
    {"char*",   "15"},          // name[13]
    {"char*",   "16"},          // name[14]
    {"char*",   "17"},          // name[15]
    {"uint32",  "18"},          // name_flags
    {"uint32",  "19"},          // sortOrder
};

char const *ACHIEVEMENT_CATEGORY_TABLE_INDEX = achievement_category_translation[0][1];

#endif
