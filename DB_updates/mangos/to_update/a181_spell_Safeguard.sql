-- Safeguard
DELETE FROM `spell_chain` WHERE `spell_id` IN (46945, 46949);
INSERT INTO `spell_chain` VALUES
(46945, 0, 46945, 1, 0),
(46949, 46949, 46945, 2, 0);

DELETE FROM `spell_proc_event` WHERE `entry` = 46945;
INSERT INTO `spell_proc_event` VALUES
(46945, 1, 4, 0, 0, 0, 0x10000, 0x10000, 0x10000, 0, 0, 0, 0x00004000, 0, 0, 0, 0);
