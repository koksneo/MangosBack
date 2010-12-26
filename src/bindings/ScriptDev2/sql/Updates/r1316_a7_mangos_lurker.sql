-- Coilfang Guardian
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = '21873'; 
-- Coilfang Ambusher
UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = '21865';

-- Lurker Below
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'boss_the_lurker_below' WHERE `entry` = '21217';

-- out of combat bug
UPDATE `creature_template` SET `InhabitType` = '3' WHERE `entry` = '21217';
DELETE FROM `creature_model_info` WHERE modelid IN (20216);
INSERT INTO `creature_model_info` VALUES ('20216', '14', '15', '2', '0'); 

-- add lurker
DELETE FROM `creature` WHERE id IN (21217);
INSERT INTO `creature` VALUES (NULL, '21217', '548', '1', '0', '0', '40.4058', '-417.108', '-21.5911', '3.03312', '604800', '0', '0', '3794000', '0', '0', '0');

DELETE FROM creature_ai_scripts WHERE creature_id IN (21865);

-- Coilfang Ambusher AI update
INSERT INTO `creature_ai_scripts` VALUES ( NULL , '21865', '0', '0', '100', '6', '0', '0','0','0', '21', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Coilfang Ambusher - Stop Movement on Aggro');
INSERT INTO `creature_ai_scripts` VALUES ( NULL , '21865', '0', '0', '100', '7', '7300', '7300','7300','7300', '11', '29576', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Coilfang Ambusher - Multishoot');

 

 
