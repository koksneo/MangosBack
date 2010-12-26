-- Plagued Quarter::Loatheb
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16011,29718);
UPDATE creature_template SET `ScriptName` = 'boss_loatheb', `AIName` = '' WHERE `entry` IN (16011);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16011,29718);
UPDATE creature_template SET `ScriptName` = 'mob_fungalspore', `AIName` = '' WHERE `entry` IN (16286);
DELETE FROM creature_loot_template WHERE entry IN (16011,29718);
