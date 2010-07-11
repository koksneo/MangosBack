-- Military Quarter::Gothik
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16060,29955);
UPDATE creature_template SET `ScriptName` = 'boss_gothik', `AIName` = '' WHERE `entry` IN (16060);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16060,29955);
DELETE FROM creature_loot_template WHERE entry IN (16060,29955);
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (16060);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29955);
