-- To Legion Hold
DELETE FROM `creature` WHERE `id` = 21502;
INSERT INTO `creature` (`id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawndist`) VALUES
('21502', '530', '-3300.39', '2927.24', '173.8', '2.54', '0');
UPDATE `creature_template` SET `ScriptName`='npc_razuun' WHERE (`entry`='21502');

DELETE FROM `scripted_areatrigger` WHERE (`entry`='4548');
INSERT INTO `scripted_areatrigger` (`entry`, `ScriptName`) VALUES
('4548', 'at_legionhold');
