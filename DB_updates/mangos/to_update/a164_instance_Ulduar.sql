-- Instance Ulduar

-- *** Ignis the Furnace Master ***
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299839, `ScriptName` = "boss_ignis" WHERE `entry` = 33118;
UPDATE `creature_template` SET `ScriptName` = "mob_iron_construct" WHERE `entry` = 33121;
UPDATE `creature_template` SET `AIName` = "EventAI" WHERE `entry` = 33221;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 33221;
INSERT INTO `creature_ai_scripts` VALUES
(3322101, 33221, 0, 0, 100, 2, 3000, 3000, 0, 0, 11, 62548, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, "Scorch Trigger - Cast Scorch normal"),
(3322102, 33221, 0, 0, 100, 4, 3000, 3000, 0, 0, 11, 63476, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, "Scorch Trigger - Cast Scorch heroic"),
(3322103, 33221, 4, 0, 100, 6, 0, 0, 0, 0, 20, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, "Scorch Trigger - Disable Combat Movement on Aggro");
