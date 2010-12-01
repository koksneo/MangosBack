-- Honor Among Thieves 
DELETE FROM `spell_chain` WHERE `spell_id` IN (51698, 51700, 51701); 
INSERT INTO `spell_chain` VALUES 
(51698, 0, 51698, 1, 0), 
(51700, 51698, 51698, 2, 0), 
(51701, 51700, 51698, 3, 0);

DELETE FROM `spell_proc_event` WHERE `entry` IN (51698); 
INSERT INTO `spell_proc_event` VALUES 
(51698, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0054110, 0x0040002, 0, 0, 1);
