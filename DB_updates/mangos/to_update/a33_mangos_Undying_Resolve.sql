-- Undying Resolve (call Val'kyr spirit to revive Death Knight)
DELETE FROM `spell_proc_event` WHERE `entry` = 51915;
INSERT INTO `spell_proc_event` VALUES (51915, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16777216, 0, 0, 0, 600);
 
DELETE FROM `spell_area` WHERE `spell` = 51915;
INSERT INTO `spell_area`VALUES(51915, 4298, 0, 0, 0, 0, 0, 2, 1);


UPDATE `creature_template` SET `unit_flags` = `unit_flags`|2, `ScriptName` = "npc_valkyr_battlemaiden" WHERE `entry` = 28534;
 
-- make it fly instead of walking in the air
DELETE FROM `creature_template_addon` WHERE `entry` = 28534;
INSERT INTO `creature_template_addon`(`entry`, `mount`, `bytes1`, `b2_0_sheath`, `emote`, `moveflags`) VALUES (28534, 0, 33554432, 1, 0, 0);