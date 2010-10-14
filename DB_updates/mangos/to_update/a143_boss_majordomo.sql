-- Majordomo Executus and Ragnaros
-- spawn
DELETE FROM `creature` WHERE `id` IN (11502, 12018);
INSERT INTO `creature` VALUES
(12791715, 11502, 409, 1, 1, 0, 0, 838.385, -831.727, -230.226, 1.71053, 7200, 0, 0, 1099230, 0, 0, 0),
(12791705, 12018, 409, 1, 1, 0, 731, 750.857, -1180.16, -119.107, 2.86246, 7200, 0, 0, 666200, 0, 0, 0);

UPDATE `creature_template` SET `MovementType` = 0, `ScriptName` = "boss_majordomo" WHERE `entry` = 12018;

-- adds' faction
UPDATE `creature_template` SET `faction_A` = 1081, `faction_H` = 1081, `MovementType` = 0 WHERE `entry` IN (11663, 11664);

DELETE FROM `creature_ai_scripts` WHERE `id` IN (1166303, 1166304);
INSERT INTO `creature_ai_scripts` VALUES
(1166303, 11663, 4, 0, 100, 3, 0, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Flamewaker Healer - Call for help"),
(1166304, 11664, 4, 0, 100, 3, 0, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Flamewaker Elite - Call for help");

-- script texts
DELETE FROM `script_texts` WHERE `entry` = -1409019;
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(-1409019, "Very well, $N.", 0, 0, 0, 0, "majordomo SAY_GOSSIP_SUMMON");

-- Emote Yell for Ragnaros (very nervous guy)
UPDATE `script_texts` SET `emote` = 1 WHERE `entry` BETWEEN -1409018 AND -1409009;
