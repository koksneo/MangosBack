-- Military Quarter::Razovius
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16061,29940);
UPDATE creature_template SET `ScriptName` = 'boss_razuvious', `AIName` = '' WHERE `entry` IN (16061);
UPDATE creature_template SET `ScriptName` = 'mob_understudies', `AIName` = '' WHERE `entry` IN (16803);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16061,29940);
DELETE FROM creature_loot_template WHERE entry IN (16061,29940);
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (16061);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29940);
