/*Loot i repa z trashy - dodac jesli bedzie potrzeba
-- Add Trah Loot
UPDATE `creature_template` SET `lootid` = '17899' WHERE `entry` IN (17899);
UPDATE `creature_template` SET `lootid` = '17898' WHERE `entry` IN (17898);
UPDATE `creature_template` SET `lootid` = '17895' WHERE `entry` IN (17895);
UPDATE `creature_template` SET `lootid` = '17905' WHERE `entry` IN (17905);
UPDATE `creature_template` SET `lootid` = '17897' WHERE `entry` IN (17897);
UPDATE `creature_template` SET `lootid` = '17906' WHERE `entry` IN (17906);
UPDATE `creature_template` SET `lootid` = '17907' WHERE `entry` IN (17907);
UPDATE `creature_template` SET `lootid` = '17908' WHERE `entry` IN (17908);
UPDATE `creature_template` SET `lootid` = '17916' WHERE `entry` IN (17916);

-- Add Trah Rep
UPDATE `creature_onkill_reputation` SET `RewOnKillRepFaction1` = '990', `MaxStanding1` = '7', `RewOnKillRepValue1` = '12' WHERE `creature_id` IN (17899,17898,17895,17905,17897,17906,17908,17916);
UPDATE `creature_onkill_reputation` SET `RewOnKillRepFaction1` = '990', `MaxStanding1` = '7', `RewOnKillRepValue1` = '60' WHERE `creature_id` IN (17907);*/

-- Anetheron
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_anetheron' WHERE `entry` = '17808';
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073741823', `flags_extra` = '256', `AIName` = '', `Scriptname` ='mob_towering_infernal' WHERE `entry` = '17818';
DELETE FROM creature_ai_scripts WHERE creature_id IN (17818,17808);


