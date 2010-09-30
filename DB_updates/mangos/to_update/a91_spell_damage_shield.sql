-- Warrior - Damage Shield proc
DELETE FROM `spell_chain` WHERE `spell_id` IN (58872, 58874);
INSERT INTO `spell_chain` VALUES
(58872, 0, 58872, 1, 0),
(58874, 58872, 58872, 2, 0);

UPDATE `spell_proc_event` SET `procFlags` = 8|32, `procEx` = 1|2|64 WHERE `entry` = 58872;