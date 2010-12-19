-- ################################################################
-- ####################### OBSIDIAN SANCTUM #######################
-- ################################################################

-- ScriptNames
UPDATE `creature_template` SET `ScriptName` = "boss_sartharion" WHERE `entry` = 28860;
UPDATE `creature_template` SET `ScriptName` = "mob_vesperon" WHERE `entry` = 30449;
UPDATE `creature_template` SET `ScriptName` = "mob_shadron" WHERE `entry` = 30451;
UPDATE `creature_template` SET `ScriptName` = "mob_tenebron" WHERE `entry` = 30452;
UPDATE `creature_template` SET `ScriptName` = "mob_acolyte_of_shadron" WHERE `entry` = 31218;
UPDATE `creature_template` SET `ScriptName` = "mob_acolyte_of_vesperon" WHERE `entry` = 31219;
UPDATE `creature_template` SET `ScriptName` = "mob_twilight_eggs" WHERE `entry` = 30882;
UPDATE `creature_template` SET `ScriptName` = "mob_twilight_whelp" WHERE `entry` IN (30890, 31214);
UPDATE `creature_template` SET `ScriptName` = "mob_fire_cyclone" WHERE `entry` = 30648;
UPDATE `creature_template` SET `ScriptName` = "mob_flame_tsunami" WHERE `entry` = 30616;

-- fix speed of tsunami
UPDATE `creature_template` SET speed_walk = 23 WHERE entry = 30616;

-- fix flying animation
UPDATE creature_template SET InhabitType = 3 WHERE entry IN (30451, 31520, 30452, 31534, 30449, 31535);

-- fix respawn time (7 days)
UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `map` = 615;

-- Shadow Fissure
UPDATE `creature_template` SET `AIName` = "EventAI" WHERE entry = 30641;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 30641;
INSERT INTO `creature_ai_scripts`VALUES
(3064101, 30641, 1, 0, 100, 2, 5000, 5000, 0, 0, 11, 57581, 0, 2, 37, 0, 0, 0, 0, 0, 0, 0, "Twilight Fissure - Cast Void Blast (Sartharion)"),
(3064102, 30641, 1, 0, 100, 4, 5000, 5000, 0, 0, 11, 59128, 0, 2, 37, 0, 0, 0, 0, 0, 0, 0, "Twilight Fissure - Cast Void Blast heroic (Sartharion)");

-- Warden of The Chamber - make them appear as dead after failing to defend the sanctum
UPDATE `creature` SET `DeathState` = 1 WHERE `guid` IN (131063, 131064);

-- Hatch Eggs - target Twilight Egg Controller
DELETE FROM `spell_script_target` WHERE `entry` IN (58542, 59189);
INSERT INTO `spell_script_target` VALUES
(58542, 1, 31138),
(59189, 1, 31138);

-- handling Twilight Eggs
UPDATE `creature_template` SET `ScriptName` = "mob_twilight_eggs" WHERE `entry` = 31204;
UPDATE `creature_template` SET `ScriptName` = "mob_twilight_egg_controller" WHERE `entry` = 31138;

-- Twilight Portal
UPDATE `gameobject_template` SET `ScriptName` = "obsidian_sanctum_portals" WHERE `entry` = 193988;

-- Disciple of Shadron (normal)
UPDATE `creature_template` SET
`faction_A` = 103,
`faction_H` = 103,
`minlevel` = 81,
`maxlevel` = 81,
`minhealth` = 130330,
`maxhealth` = 130330,
`minmana` = 4081,
`maxmana` = 4081,
`armor` = 10033,
`speed_walk` = 1.6,
`speed_run` = 1.14286,
`mindmg` = 464,
`maxdmg` = 604,
`attackpower` = 708,
`dmg_multiplier` = 2,
`minrangedmg` = 353,
`maxrangedmg` = 512,
`rangedattackpower` = 112,
`ScriptName` = "mob_acolyte_of_shadron"
WHERE `entry` = 30688;

-- Disciple of Shadron (heroic)
UPDATE `creature_template` SET
`faction_A` = 103,
`faction_H` = 103,
`minlevel` = 81,
`maxlevel` = 81,
`minhealth` = 390990,
`maxhealth` = 390990,
`minmana` = 4081,
`maxmana` = 4081,
`armor` = 10033,
`speed_walk` = 1.6,
`speed_run` = 1.14286,
`mindmg` = 464,
`maxdmg` = 604,
`attackpower` = 708,
`dmg_multiplier` = 6,
`minrangedmg` = 353,
`maxrangedmg` = 512,
`rangedattackpower` = 112,
`ScriptName` = "mob_acolyte_of_shadron"
WHERE `entry` = 31544;

-- Disciple of Vesperon (normal)
UPDATE `creature_template` SET
`faction_A` = 103,
`faction_H` = 103,
`minlevel` = 81,
`maxlevel` = 81,
`minhealth` = 130330,
`maxhealth` = 130330,
`minmana` = 4081,
`maxmana` = 4081,
`armor` = 10033,
`speed_walk` = 1.6,
`speed_run` = 1.14286,
`mindmg` = 464,
`maxdmg` = 604,
`attackpower` = 708,
`dmg_multiplier` = 2,
`minrangedmg` = 353,
`maxrangedmg` = 512,
`rangedattackpower` = 112,
`ScriptName` = "mob_acolyte_of_vesperon"
WHERE `entry` = 30858;

-- Disciple of Vesperon (heroic)
UPDATE `creature_template` SET
`faction_A` = 103,
`faction_H` = 103,
`minlevel` = 81,
`maxlevel` = 81,
`minhealth` = 390990,
`maxhealth` = 390990,
`minmana` = 4081,
`maxmana` = 4081,
`armor` = 10033,
`speed_walk` = 1.6,
`speed_run` = 1.14286,
`mindmg` = 464,
`maxdmg` = 604,
`attackpower` = 708,
`dmg_multiplier` = 6,
`minrangedmg` = 353,
`maxrangedmg` = 512,
`rangedattackpower` = 112,
`ScriptName` = "mob_acolyte_of_vesperon"
WHERE `entry` = 31546;

-- Safe Area dummy creature - mark targets in 40yd radius to be not targeted by Sartharion's Pyrobuffet
UPDATE `creature_template` SET `spell1` = 56911 WHERE `entry` = 30494;

-- TRASH ACID
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (30680, 30681, 30682, 30453);
INSERT INTO `creature_ai_scripts` VALUES
(3068001, 30680, 0, 0, 100, 7, 5000, 10000, 5000, 10000, 11, 13737, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Mortal Strike"),
(3068002, 30680, 4, 0, 100, 3, 0, 0, 0, 0, 11, 57740, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Devotion Aura (10man)"),
(3068003, 30680, 4, 0, 100, 5, 0, 0, 0, 0, 11, 58944, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Devotion Aura (25man)"),
(3068004, 30680, 2, 0, 100, 6, 1, 25, 0, 0, 11, 57742, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Avenging Fury at 25% HP"),
(3068005, 30680, 0, 0, 100, 3, 5000, 10000, 15000, 20000, 11, 57733, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Draconic Rage (10man)"),
(3068006, 30680, 0, 0, 100, 5, 5000, 10000, 15000, 20000, 11, 58942, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Brood General - Cast Draconic Rage (25man)"),

(3068101, 30681, 0, 0, 100, 3, 5000, 10000, 10000, 15000, 11, 57757, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Blaze Mistress - Cast Rain of Fire (10man)"),
(3068102, 30681, 0, 0, 100, 5, 5000, 10000, 10000, 15000, 11, 58936, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Blaze Mistress - Cast Rain of Fire (25man)"),
(3068103, 30681, 2, 0, 100, 7, 1, 50, 0, 0, 11, 57753, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Blaze Mistress - Cast Conjure Flame Orb at 50% HP"),
(3068104, 30681, 0, 0, 100, 3, 5000, 10000, 10000, 15000, 11, 39529, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Blaze Mistress - Cast Flame Shock (10man)"),
(3068105, 30681, 0, 0, 100, 5, 5000, 10000, 10000, 15000, 11, 58940, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Blaze Mistress - Cast Flame Shock (25man)"),

(3068201, 30682, 0, 0, 100, 7, 7000, 12000, 7000, 12000, 11, 57759, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Flight Captain - Cast Hammer Drop"),
(3068202, 30682, 0, 0, 100, 7, 5000, 10000, 5000, 10000, 11, 58953, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Flight Captain - Cast Pummel"),

(3045301, 30453, 0, 0, 100, 3, 5000, 10000, 10000, 15000, 11, 57728, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Sanctum Guardian - Cast Shockwave (10man)"),
(3045302, 30453, 0, 0, 100, 5, 5000, 10000, 10000, 15000, 11, 58947, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Sanctum Guardian - Cast Shockwave (25man)"),
(3045303, 30453, 0, 0, 100, 6, 5000, 7000, 0, 0, 11, 58948, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Sanctum Guardian - Cast Curse of Mending"),
(3045304, 30453, 2, 0, 100, 6, 1, 25, 0, 0, 11, 53801, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Onyx Sanctum Guardian - Cast Frenzy at 25% HP");

-- Drakes' templates - instance binding dependent on instance script; set lootid.
UPDATE `creature_template` SET `lootid` = `entry`, `flags_extra` = `flags_extra`&~1 WHERE `entry` IN (30449, 30451, 30452, 31535, 31520, 31534);

-- LOOT
DELETE FROM `creature_loot_template` WHERE `entry` IN (28860, 31311, 30449, 30451, 30452, 31535, 31520, 31534);
INSERT INTO `creature_loot_template` VALUES
-- normal mode loot
-- 10 man
(28860, 40426, 0, 2, 1, 1, 0, 0, 0),
(28860, 40427, 0, 2, 1, 1, 0, 0, 0),
(28860, 40428, 0, 2, 1, 1, 0, 0, 0),
(28860, 40429, 0, 2, 1, 1, 0, 0, 0),
(28860, 40430, 0, 2, 1, 1, 0, 0, 0),
(28860, 40613, 0, 1, 1, 1, 0, 0, 0),
(28860, 40614, 0, 1, 1, 1, 0, 0, 0),
(28860, 40615, 0, 1, 1, 1, 0, 0, 0),
(28860, 43345, 100, 0, 1, 1, 0, 0, 0),
(28860, 43347, 100, 0, 1, 1, 0, 0, 0),
(28860, 40752, 100, 0, 2, 2, 0, 0, 0),
-- HARD MODES LOOT
-- 1 drake 10man
(28860, 43988, 0, 3, 1, 1, 18, 615, 2),
(28860, 43989, 0, 3, 1, 1, 18, 615, 2),
(28860, 43990, 0, 3, 1, 1, 18, 615, 2),
(28860, 43991, 0, 3, 1, 1, 18, 615, 2),
(28860, 43992, 0, 3, 1, 1, 18, 615, 2),
(28860, 0, 100, 6, -28863, 1, 18, 615, 2),
-- 2 drakes 10man
(28860, 43993, 0, 4, 1, 1, 18, 615, 3),
(28860, 43994, 0, 4, 1, 1, 18, 615, 3),
(28860, 43995, 0, 4, 1, 1, 18, 615, 3),
(28860, 43996, 0, 4, 1, 1, 18, 615, 3),
(28860, 43998, 0, 4, 1, 1, 18, 615, 3),
(28860, 1, 100, 6, -28864, 1, 18, 615, 3),
-- 3 drakes 10man
(28860, 43986, 100, 5, 1, 1, 18, 615, 4),
(28860, 2, 100, 6, -28865, 1, 18, 615, 4),
-- 25 man
(31311, 31315, 100, 2, -31315, 2, 0, 0, 0),
(31311, 31316, 100, 1, -31316, 2, 0, 0, 0),
(31311, 43345, 100, 0, 1, 1, 0, 0, 0),
(31311, 43346, 100, 0, 1, 1, 0, 0, 0),
(31311, 40753, 100, 0, 2, 2, 0, 0, 0),
-- 1 drake 25man
(31311, 44000, 0, 4, 1, 1, 18, 615, 2),
(31311, 44002, 0, 4, 1, 1, 18, 615, 2),
(31311, 44003, 0, 4, 1, 1, 18, 615, 2),
(31311, 44004, 0, 4, 1, 1, 18, 615, 2),
(31311, 0, 100, 7, -31312, 1, 18, 615, 2),
-- 2 drakes 25man
(31311, 44005, 0, 5, 1, 1, 18, 615, 3),
(31311, 44006, 0, 5, 1, 1, 18, 615, 3),
(31311, 44007, 0, 5, 1, 1, 18, 615, 3),
(31311, 44008, 0, 5, 1, 1, 18, 615, 3),
(31311, 44011, 0, 5, 1, 1, 18, 615, 3),
(31311, 1, 100, 7, -31313, 1, 18, 615, 3),
-- 3 drakes 25man
(31311, 43954, 100, 6, 1, 1, 18, 615, 4),
(31311, 2, 100, 7, -31314, 1, 18, 615, 4),
-- Drakes' Emblems
(30449, 40752, 100, 0, 1, 1, 0, 0, 0),
(30451, 40752, 100, 0, 1, 1, 0, 0, 0),
(30452, 40752, 100, 0, 1, 1, 0, 0, 0),
(31535, 40753, 100, 0, 1, 1, 0, 0, 0),
(31520, 40753, 100, 0, 1, 1, 0, 0, 0),
(31534, 40753, 100, 0, 1, 1, 0, 0, 0);

-- references
DELETE FROM `reference_loot_template` WHERE `entry` IN (28863, 28864, 28865, 31312, 31313, 31314, 31315, 31316);
INSERT INTO `reference_loot_template` VALUES
-- 25 normal mode loot
-- items
(31315, 40432, 0, 2, 1, 1, 0, 0, 0),
(31315, 40433, 0, 2, 1, 1, 0, 0, 0),
(31315, 40438, 0, 2, 1, 1, 0, 0, 0),
(31315, 40439, 0, 2, 1, 1, 0, 0, 0),
(31315, 40453, 0, 2, 1, 1, 0, 0, 0),
(31315, 40437, 0, 2, 1, 1, 0, 0, 0),
(31315, 40431, 0, 2, 1, 1, 0, 0, 0),
(31315, 40446, 0, 2, 1, 1, 0, 0, 0),
(31315, 40451, 0, 2, 1, 1, 0, 0, 0),
(31315, 40455, 0, 2, 1, 1, 0, 0, 0),
-- tokens
(31316, 40628, 0, 1, 1, 1, 0, 0, 0),
(31316, 40629, 0, 1, 1, 1, 0, 0, 0),
(31316, 40630, 0, 1, 1, 1, 0, 0, 0),
-- hard modes loot
(28863, 40752, 100, 6, 1, 1, 18, 615, 2),
(28864, 40752, 100, 6, 1, 1, 18, 615, 3),
(28865, 40752, 100, 6, 1, 1, 18, 615, 4),
(31312, 40753, 100, 7, 1, 1, 18, 615, 2),
(31313, 40753, 100, 7, 1, 1, 18, 615, 3),
(31314, 40753, 100, 7, 1, 1, 18, 615, 4);

-- Satchel's loot - 5 emblems
DELETE FROM `item_loot_template` WHERE `entry` IN (43347, 43346);
INSERT INTO `item_loot_template` VALUES
(43347, 40752, 100, 0, 5, 5, 0, 0, 0),
(43346, 40753, 100, 0, 5, 5, 0, 0, 0);

-- Achievement development
-- Achievements
-- DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` BETWEEN 2047 AND 2054;
-- INSERT INTO `achievement_criteria_requirement` VALUES
-- (2047, 18, 0, 0),
-- (2048, 18, 0, 0),
-- (2049, 18, 2, 0),
-- (2052, 18, 2, 0),
-- (2050, 18, 3, 0),
-- (2053, 18, 3, 0),
-- (2051, 18, 4, 0),
-- (2054, 18, 4, 0);
