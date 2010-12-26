-- UTGARDE PINNACLE instance template

-- Utgarde Pinnacle::Svala
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '345', `maxdmg` = '445', `attackpower` = '1500', `dmg_multiplier` = '7.5', `mechanic_immune_mask` = '1073463287', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '315000', `maxhealth` = '315000', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21', `AIName` = '', `Scriptname` = 'boss_svala' WHERE `entry` IN (26668);
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '345', `maxdmg` = '445', `attackpower` = '1500', `dmg_multiplier` = '13', `mechanic_immune_mask` = '1073463287', `minlevel` = '82', `maxlevel` = '82', `minhealth` = '431392', `maxhealth` = '431392', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (30810);
-- Utgarde Pinnacle::svala ritual channelerer
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '8121', `maxhealth` = '8121', `minmana` = '15976', `maxmana` = '15976',`AIName` = '', `Scriptname` = 'npc_svala_channeler' WHERE `entry` IN (27281);
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '81', `maxlevel` = '81', `minhealth` = '13033', `maxhealth` = '13033', `minmana` = '16324', `maxmana` = '16324' WHERE `entry` IN (30804);
-- Utgarde Pinnacle::RitualTarget
UPDATE `creature_template` SET `faction_A` = '35', `faction_H` = '35' WHERE `entry` IN (27327);

-- Utgarde Pinnacle::Gortok
-- Boss replace removeing frozen efect
DELETE FROM creature WHERE id = '26687';
INSERT INTO creature VALUES (NULL,26687,575,3,1,0,0,320.406,-452.745,104.723,3.17097,86400,0,0,431392,0,0,0);
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_gortok' WHERE `entry` IN (26687);
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (30774);
-- Utgarde Pinnacle::Gortok add flags Rhino etc.
UPDATE `creature_template` SET `faction_A` = '35', `faction_H` = '35', `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (26684,30803,26683,30772,26685,30790,26686,30770);

-- Utgarde Pinnacle::Skadi  boss_skadi
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_skadi' WHERE `entry` IN (26693);
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (30807);
-- Utgarde Pinnacle::Grouf not used in event for  now
DELETE FROM creature WHERE id = '26893';
-- Utgarde Pinnacle::Adds
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '18262', `maxhealth` = '18262', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000' WHERE `entry` IN (26692,26690,26691);
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '26066', `maxhealth` = '26066', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000', `dmg_multiplier` ='7.5' WHERE `entry` IN (30819,30823,30822);
UPDATE `creature_template` SET `minmana` = '4080', `maxmana` = '4080' WHERE `entry` IN (26691);
-- Utgarde Pinnacle::Skadi harpoonlancher
UPDATE gameobject_template SET ScriptName = 'go_skaldi_harpoonluncher' WHERE entry IN (192175,192176,192177); 

-- Utgarde Pinnacle::King Ymiron
UPDATE `creature_template` SET `minmana` = '10000', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_ymiron' WHERE `entry` IN (26861);
UPDATE `creature_template` SET `minmana` = '10000', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (30788);
-- Utgarde Pinnacle::delete not necesary mobs
DELETE FROM `creature` WHERE `id` IN (27303,27309,27308,27307);
-- Utgarde Pinnacle::Avenging Spirit norm hero
UPDATE `creature_template` SET `minlevel` = '80', `maxlevel` = '80', `maxhealth` = '3000', `minhealth` = '3000' WHERE entry IN (27386);
UPDATE `creature_template` SET `dmg_multiplier` = '7.5' WHERE `entry` IN (30756);
UPDATE `creature_template` SET `type_flags` = '0', `faction_A` = '14', `faction_H` = '14', `armor` = '3000', `mindmg` = '200', `maxdmg` = '300', `attackpower` = '1000' WHERE entry IN (27386,30756);
-- Utgarde Pinnacle::Spirit Fount
UPDATE `creature_template` SET `unit_flags` = '33554560', `modelid_A` = '11686', `minlevel` = '80', `maxlevel` = '82', `faction_A` = '14', `faction_H` = '14', `speed` = '0.4', `flags_extra` = '0' WHERE entry IN (30808,27339);

-- Utgarde Pinnacle::ACID
UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (26686,26684,26683,26685,26690,26691,26692);
-- DELETE EventAIScripts
DELETE FROM creature_ai_scripts WHERE creature_id IN (26686,26684,26683,26685,26690,26691,26692);
INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES
-- Ymirjar Warrior
(2669001, '26690', '0', '0', '100', '7', '5000', '15000','30000','50000', '11', '48639', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Warrior - Cast Hamstring'),
(2669002, '26690', '0', '0', '100', '7', '5000', '15000','10000','15000', '11', '48640', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Warrior - Cast Strike'),
-- Ymirjar Witch Doctor
(2669101, '26691', '0', '0', '100', '3', '5000', '15000','5000','10000', '11', '49085', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Witch Doctor - Cast Shadow Bolt (Normal)'),
(2669102, '26691', '0', '0', '100', '5', '5000', '15000','5000','10000', '11', '59246', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Witch Doctor - Cast Shadow Bolt (Heroic)'),
(2669103, '26691', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '49089', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Witch Doctor - Cast Shrink (Normal)'),
(2669104, '26691', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59247', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Witch Doctor - Cast Shrink (Heroic)'),
-- Ymirjar Harpooner
(2669201, '26692', '0', '0', '100', '7', '5000', '15000','30000','50000', '11', '49092', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Harpooner - Cast Net'),
(2669202, '26692', '0', '0', '100', '7', '5000', '15000','10000','15000', '11', '49091', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ymirjar Harpooner - Cast Throw'),
-- Utgarde Pinnacle::Furoiuces Rhino
(2668601, '26686', '0', '0', '100', '3', '5000', '15000','20000','40000', '11', '48130', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Gore (Normal)'),
(2668602, '26686', '0', '0', '100', '5', '5000', '15000','20000','40000', '11', '59264', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Gore (Heroic)'),
(2668603, '26686', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48105', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Grevius Wond (Normal)'),
(2668604, '26686', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59263', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Grevius Wond (Heroic)'),
(2668605, '26686', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48131', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Stomp'),
-- Utgarde Pinnacle::Furbolg
(2668401, '26684', '0', '0', '100', '7', '5000', '15000','20000','40000', '11', '48139', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Crazed'),
(2668402, '26684', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48140', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Chain Lighting (Normal)'),
(2668403, '26684', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59273', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Chain Lighting (Heroic)'),
(2668404, '26684', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48144', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Terrifing Roar'),
-- Utgarde Pinnacle::Worgen
(2668301, '26683', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48138', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Enrage'),
(2668302, '26683', '2', '0', '100', '7', '30', '0', '0','0', '11', '48142', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Enrage Perm'),
(2668303, '26683', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48137', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Mortal Wound (Normal)'),
(2668304, '26683', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59265', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Mortal Wound (Heroic)'),
-- Utgarde Pinnacle::Jormungar
(2668501, '26685', '0', '0', '100', '7', '5000', '10000','15000','20000', '11', '48132', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Acid Split (Heroic)'),
(2668502, '26685', '0', '0', '100', '3', '5000', '15000','30000','50000', '11', '48136', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Summon (Normal)'),
(2668503, '26685', '0', '0', '100', '5', '5000', '15000','30000','50000', '11', '59272', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Summon (Heroic)'),
(2668504, '26685', '0', '0', '100', '3', '5000', '15000','10000','15000', '11', '48133', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Breath (Normal)'),
(2668505, '26685', '0', '0', '100', '5', '5000', '15000','10000','15000', '11', '59271', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Breath (Heroic)');

-- Utgarde Pinnacle::LOOT TEMPLATE
UPDATE `creature_template` SET `lootid` = '26692' WHERE `entry` IN (26692,30819);
DELETE FROM `creature_loot_template` WHERE `entry` IN (26692,30819);
INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES
-- Harpooner loot
('26692', '37372', '50', '1', '1', '1', '0', '0', '0');
