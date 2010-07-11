-- Anetheron
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_anetheron' WHERE `entry` = '17808';
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073741823', `flags_extra` = '256', `AIName` = '', `Scriptname` ='mob_towering_infernal' WHERE `entry` = '17818';

-- Kazrogal
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_kazrogal' WHERE `entry` = '17888';

-- Azgalor
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_azgalor' WHERE `entry` = '17842';

-- Summon
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = 'EventAI', `Scriptname` ='' WHERE `entry` = '17864';

DELETE FROM creature_ai_scripts WHERE creature_id IN (17864);
INSERT INTO creature_ai_scripts VALUES (NULL, '17864', '0', '0', '100', '3', '5000', '10000','15000','15000', '11', '31408', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Lesser DoomdGuard - Cast WarStomp');
INSERT INTO creature_ai_scripts VALUES (NULL, '17864', '0', '0', '100', '3', '6000', '12000','20000','25000', '11', '31406', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Lesser DoomdGuard - Cast Cripple');

-- Archimonde
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_archimonde' WHERE `entry` = '17968';

-- doomfire
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='mob_doomfire' WHERE `entry` = '18095';
-- doomfire targeting
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='mob_doomfire_targetting' WHERE `entry` = '18104';
-- ancient wisp
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='mob_ancient_wisp' WHERE `entry` = '17946';

DELETE FROM `creature_ai_scripts` WHERE creature_id IN (17946,18104,18095,17968,17842,17888,17808,17818);


