-- Instance Ulduar

-- ****** Ignis the Furnace Master ******
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299839, `ScriptName` = "boss_ignis" WHERE `entry` = 33118;
UPDATE `creature_template` SET `ScriptName` = "mob_iron_construct" WHERE `entry` = 33121;
UPDATE `creature_template` SET `AIName` = "EventAI" WHERE `entry` = 33221;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 33221;
INSERT INTO `creature_ai_scripts` VALUES
(3322101, 33221, 0, 0, 100, 2, 3000, 3000, 0, 0, 11, 62548, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, "Scorch Trigger - Cast Scorch normal"),
(3322102, 33221, 0, 0, 100, 4, 3000, 3000, 0, 0, 11, 63476, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, "Scorch Trigger - Cast Scorch heroic"),
(3322103, 33221, 4, 0, 100, 6, 0, 0, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, "Scorch Trigger - Disable Combat Movement on Aggro");
-- Ignis loot
DELETE FROM `creature_loot_template` WHERE `entry` IN (33118, 33190);
INSERT INTO `creature_loot_template` VALUES
-- 10 man
(33118, 40753, 100, 0, 1, 1, 0, 0, 0),
(33118, 1, 100, 1, -33119, 2, 0, 0, 0),
-- 25 man
(33190, 45624, 100, 0, 1, 1, 0, 0, 0),
(33190, 1, 100, 1, -33191, 4, 0, 0, 0);

DELETE FROM `reference_loot_template` WHERE `entry` IN (33119, 33191);
INSERT INTO `reference_loot_template` VALUES
-- Ignis10
(33119, 45316, 0, 1, 1, 1, 0, 0, 0),
(33119, 45318, 0, 1, 1, 1, 0, 0, 0),
(33119, 45313, 0, 1, 1, 1, 0, 0, 0),
(33119, 45310, 0, 1, 1, 1, 0, 0, 0),
(33119, 45312, 0, 1, 1, 1, 0, 0, 0),
(33119, 45314, 0, 1, 1, 1, 0, 0, 0),
(33119, 45321, 0, 1, 1, 1, 0, 0, 0),
(33119, 45311, 0, 1, 1, 1, 0, 0, 0),
(33119, 45309, 0, 1, 1, 1, 0, 0, 0),
(33119, 45317, 0, 1, 1, 1, 0, 0, 0),
-- Ignis25
(33191, 45166, 0, 1, 1, 1, 0, 0, 0),
(33191, 45157, 0, 1, 1, 1, 0, 0, 0),
(33191, 45162, 0, 1, 1, 1, 0, 0, 0),
(33191, 45185, 0, 1, 1, 1, 0, 0, 0),
(33191, 45161, 0, 1, 1, 1, 0, 0, 0),
(33191, 45158, 0, 1, 1, 1, 0, 0, 0),
(33191, 45164, 0, 1, 1, 1, 0, 0, 0),
(33191, 45171, 0, 1, 1, 1, 0, 0, 0),
(33191, 45167, 0, 1, 1, 1, 0, 0, 0),
(33191, 45168, 0, 1, 1, 1, 0, 0, 0),
(33191, 45170, 0, 1, 1, 1, 0, 0, 0),
(33191, 45186, 0, 1, 1, 1, 0, 0, 0),
(33191, 45169, 0, 1, 1, 1, 0, 0, 0),
(33191, 45165, 0, 1, 1, 1, 0, 0, 0),
(33191, 45187, 0, 1, 1, 1, 0, 0, 0);

-- ****** Razorscale ******
UPDATE creature_template SET mechanic_immune_mask=617299803, `lootid` = `entry`, `InhabitType` = 7, `ScriptName`="boss_razorscale" WHERE entry=33186;
-- original x=587.547, y= -174.927, z = 391.517; make the boss fly before encounter starts
update creature set position_x = 590.346741, position_y = -226.947647, position_z = 460.897583 where id = 33186;
UPDATE gameobject_template SET flags= 6553648, ScriptName="go_broken_harpoon" WHERE entry = 194565;
-- only 2 harpoons for 10 man
update gameobject set spawnMask = 2 where guid in (73595, 73592);
-- mole machines & adds
UPDATE creature_template SET ScriptName = "mob_mole_machine" WHERE entry = 33245;
UPDATE creature_template SET ScriptName = "mob_dark_rune_watcher" WHERE entry = 33453;
UPDATE creature_template SET ScriptName = "mob_dark_rune_sentinel" WHERE entry = 33846;
UPDATE creature_template SET ScriptName = "mob_dark_rune_guardian" WHERE entry = 33388;
UPDATE creature_template SET ScriptName = "npc_expedition_commander" WHERE entry = 33210;
UPDATE creature_template SET ScriptName = "mob_devouring_flame_target" WHERE entry in (34189, 34188);
UPDATE creature_template SET unit_flags = 0 WHERE `entry` = 33233;
UPDATE `creature_template`SET `unit_flags` = `unit_flags`&~33554432 WHERE entry = 33282;
-- expedition NPCs - don't enter the fight
UPDATE `creature_template` SET `unit_flags` = `unit_flags`|2|33554432, `flags_extra` = `flags_extra`|2 WHERE `entry` IN (33259, 33816, 33287);
-- harpoon script target
DELETE FROM `spell_script_target` WHERE `entry` = 62505;
INSERT INTO `spell_script_target` VALUES
(62505, 1, 33186);
-- loot
DELETE FROM `creature_loot_template` WHERE `entry` IN (33186, 33724);
INSERT INTO `creature_loot_template` VALUES
-- 10 man
(33186, 40753, 100, 0, 1, 1, 0, 0, 0),
(33186, 1, 100, 1, -33187, 2, 0, 0, 0),
-- 25 man
(33724, 45624, 100, 0, 1, 1, 0, 0, 0),
(33724, 1, 100, 1, -33725, 4, 0, 0, 0);

DELETE FROM `reference_loot_template` WHERE `entry` IN (33187, 33725);
INSERT INTO `reference_loot_template` VALUES
-- Razorscale10
(33187, 45303, 0, 1, 1, 1, 0, 0, 0),
(33187, 45306, 0, 1, 1, 1, 0, 0, 0),
(33187, 45301, 0, 1, 1, 1, 0, 0, 0),
(33187, 45305, 0, 1, 1, 1, 0, 0, 0),
(33187, 45299, 0, 1, 1, 1, 0, 0, 0),
(33187, 45308, 0, 1, 1, 1, 0, 0, 0),
(33187, 45307, 0, 1, 1, 1, 0, 0, 0),
(33187, 45298, 0, 1, 1, 1, 0, 0, 0),
(33187, 45304, 0, 1, 1, 1, 0, 0, 0),
(33187, 45302, 0, 1, 1, 1, 0, 0, 0),
-- Razorscale25
(33725, 45151, 0, 1, 1, 1, 0, 0, 0),
(33725, 45149, 0, 1, 1, 1, 0, 0, 0),
(33725, 45150, 0, 1, 1, 1, 0, 0, 0),
(33725, 45139, 0, 1, 1, 1, 0, 0, 0),
(33725, 45138, 0, 1, 1, 1, 0, 0, 0),
(33725, 45147, 0, 1, 1, 1, 0, 0, 0),
(33725, 45510, 0, 1, 1, 1, 0, 0, 0),
(33725, 45148, 0, 1, 1, 1, 0, 0, 0),
(33725, 45141, 0, 1, 1, 1, 0, 0, 0),
(33725, 45140, 0, 1, 1, 1, 0, 0, 0),
(33725, 45142, 0, 1, 1, 1, 0, 0, 0),
(33725, 45143, 0, 1, 1, 1, 0, 0, 0),
(33725, 45146, 0, 1, 1, 1, 0, 0, 0),
(33725, 45144, 0, 1, 1, 1, 0, 0, 0),
(33725, 45137, 0, 1, 1, 1, 0, 0, 0);
