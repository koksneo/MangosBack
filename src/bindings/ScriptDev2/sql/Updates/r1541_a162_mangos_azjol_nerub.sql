-- AZJOL NERUB

-- Krik Thir norm/hero
UPDATE creature_template SET `mingold` = '4691', `maxgold` = '5691', `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_krikthir', `minmana` ='46854', `maxmana` ='46854' WHERE `entry` IN (28684);
UPDATE creature_template SET `mingold` = '4691', `maxgold` = '5691', `mechanic_immune_mask` = '1073463287', `minmana` = '54960', `maxmana` = '54960' WHERE `entry` IN (31612);
-- Krik Thir mini bosy norm/hero
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_silthik' WHERE `entry` IN (28731);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_gashra' WHERE `entry` IN (28730);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_narjil' WHERE `entry` IN (28729);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31616);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31615);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31617);
-- Swarmer Infector norm/hero
UPDATE creature_template SET `minhealth` ='4000', `maxhealth` ='4000', `minlevel` = '72', `maxlevel` = '72', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '28736';
UPDATE creature_template SET `minhealth` ='6556', `maxhealth` ='6556', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '31613';
-- Swarmer norm/hero no xp at kill
UPDATE creature_template SET `flags_extra` ='64' WHERE `entry` = '28735';
UPDATE creature_template SET `minhealth` ='328', `maxhealth` ='328', `minlevel` = '80', `maxlevel` = '80', `flags_extra` ='64' WHERE `entry` = '31614';
DELETE FROM creature WHERE id IN (28731,28730,28729);

-- Hadronox
UPDATE creature_template SET `mingold` = '4675', `maxgold` = '5675', `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_hadronox' WHERE `entry` IN (28921);
UPDATE creature_template SET `mingold` = '4675', `maxgold` = '5675', `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31611);
-- UPDATE creature SET position_x = '529.157715', position_y = '576.377502', position_z = '733.610474', orientation = '5.295866' WHERE guid = '127401';
DELETE FROM creature WHERE id = '28921';
INSERT INTO creature VALUES (NULL,28921,601,3,1,0,0,528.597,568.066,733.269,4.60437,86400,0,0,431392,0,0,0);


-- Anubarak
UPDATE creature_template SET `mingold` = '4684', `maxgold` = '5684', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (29120,31610);
UPDATE creature_template SET `mingold` = '4684', `maxgold` = '5684', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (29120);
-- Trigger Invisible Mode
UPDATE `creature_template` SET `flags_extra` = '128' WHERE `entry` IN (29184);
-- Anub'ar Webspinner Shadowcaster Necromancer venomancer
UPDATE `creature_template` SET `minmana` = '7500', `maxmana` = '7500' WHERE `entry` IN (29335,28733,29098,29064,29217);
UPDATE `creature_template` SET `minmana` = '8979', `maxmana` = '8979' WHERE `entry` IN (31609,31605,31602,31601,31607);
-- Venomncer melee dmg
UPDATE `creature_template` SET `mindmg` = '270', `maxdmg` = '395', `attackpower` = '143' WHERE `entry` IN (29217);
UPDATE `creature_template` SET `mindmg` = '346', `maxdmg` = '499', `attackpower` = '287' WHERE `entry` IN (31607);
-- guardian melee dmg
UPDATE `creature_template` SET `mindmg` = '307', `maxdmg` = '438', `attackpower` = '314', `dmg_multiplier` = '7.5' WHERE `entry` IN (29216);
UPDATE `creature_template` SET `mindmg` = '422', `maxdmg` = '586', `attackpower` = '642', `dmg_multiplier` = '13' WHERE `entry` IN (31599);

-- Azjol-Nerub::Loot Template
UPDATE creature_template SET `lootid` = '31612' WHERE `entry` IN (31612);
UPDATE creature_template SET `lootid` = '31611' WHERE `entry` IN (31611);
UPDATE creature_template SET `lootid` = '31610' WHERE `entry` IN (31610);

DELETE FROM creature_loot_template WHERE entry IN (31612,31611,31610);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Azjol-Nerub::Kirkthir hero loot id 31612
('31612', '43852', '1.4', '0', '1', '1', '0', '0', '0'),
('31612', '37218', '0', '1', '1', '1', '0', '0', '0'),
('31612', '37216', '0', '1', '1', '1', '0', '0', '0'),
('31612', '37219', '0', '1', '1', '1', '0', '0', '0'),
('31612', '37217', '0', '1', '1', '1', '0', '0', '0'),
-- Azjol-Nerub::Hadronox
('31611', '43852', '2', '0', '1', '1', '0', '0', '0'),
('31611', '37221', '0', '1', '1', '1', '0', '0', '0'),
('31611', '37230', '0', '1', '1', '1', '0', '0', '0'),
('31611', '37220', '0', '1', '1', '1', '0', '0', '0'),
('31611', '37222', '0', '1', '1', '1', '0', '0', '0'),
-- Azjol-Nerub::Anubarak
('31610', '41796', '7', '0', '1', '1', '0', '0', '0'),
('31610', '37232', '0', '1', '1', '1', '0', '0', '0'),
('31610', '37242', '0', '2', '1', '1', '0', '0', '0'),
('31610', '37238', '0', '2', '1', '1', '0', '0', '0'),
('31610', '37241', '0', '2', '1', '1', '0', '0', '0'),
('31610', '37236', '0', '1', '1', '1', '0', '0', '0'),
('31610', '37235', '0', '1', '1', '1', '0', '0', '0'),
('31610', '37237', '0', '1', '1', '1', '0', '0', '0'),
('31610', '37240', '0', '2', '1', '1', '0', '0', '0'),
('31610', '43102', '0', '3', '1', '1', '0', '0', '0'),
-- Azjol Nerub
('31612', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31611', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31610', '40752', '100', '0', '1', '1', '0', '0', '0');

-- Azjol-Nerub::ACID

-- Azjol Nerub Mobs
-- NORMAL (28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);
-- HEROIC (31608,31605,31606,31589,31594,31601,31590,31595,31602,31591,31596,31604,31609,31587,31607,31599,31592);

-- Update EVENTAI

UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);

-- DELETE EventAIScripts
DELETE FROM creature_ai_scripts WHERE creature_id IN           (28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);


INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES

-- Anub'ar Crusher
(NULL, '28922', '0', '0', '100', '3', '5000', '8000','15000','20000', '11', '53318', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Smash (Normal)'),
(NULL, '28922', '0', '0', '100', '5', '5000', '8000','15000','20000', '11', '59346', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Smash (Heroic)'),
(NULL, '28922', '0', '0', '100', '6', '10', '10','0','0', '11', '53801', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Frenzy'),

-- Anub'ar Venomancer
(NULL, '29217', '0', '0', '100', '3', '500', '500','4000','8000', '11', '53617', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt (Normal)'),
(NULL, '29217', '0', '0', '100', '5', '500', '500','4000','8000', '11', '59359', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt (Heroic)'),
(NULL, '29217', '0', '0', '100', '3', '5000', '8000','10000','14000', '11', '53616', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt Volley (Normal)'),
(NULL, '29217', '0', '0', '100', '5', '5000', '8000','10000','14000', '11', '59360', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt Volley (Heroic)'),

-- Anub'ar Guardian 
(NULL, '29216', '0', '0', '100', '3', '1000', '5000','5000','9000', '11', '53618', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast SunderArmor (Normal)'),
(NULL, '29216', '0', '0', '100', '5', '1000', '5000','5000','9000', '11', '59350', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast SunderArmor (Heroic)'),
(NULL, '29216', '0', '0', '100', '7', '3000', '4000','4000','8000', '11', '52532', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast Strike'),

-- Anub'ar Warrior 
(NULL, '28732', '0', '0', '100', '7', '6000', '6000','11000','11000', '11', '49806', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Warrior - Cast Cleave'),
(NULL, '28732', '0', '0', '100', '7', '3000', '5000','5000','7000', '11', '52532', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Warrior - Cast Strike'),

-- Anub'ar Shadowcaster 
(NULL, '28733', '0', '0', '100', '3', '500', '500','2000','4000', '11', '52534', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Bolt (Normal)'),
(NULL, '28733', '0', '0', '100', '5', '500', '500','2000','4000', '11', '59357', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Bolt (Heroic)'),
(NULL, '28733', '0', '0', '100', '3', '5000', '8000','11000','17000', '11', '52535', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Nova (Normal)'),
(NULL, '28733', '0', '0', '100', '5', '5000', '8000','11000','17000', '11', '59358', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Nova (Heroic)'),

-- Anub'ar Skirmisher
(NULL, '28734', '0', '0', '100', '7', '4000', '4000','8000','12000', '11', '52540', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Skirmisher - Cast Backstab'),

-- Anub'ar Champion
(NULL, '29062', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)'),
(NULL, '29062', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)'),
(NULL, '29062', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)'),
(NULL, '29062', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)'),

-- Anub'ar Crypt Fiend 
(NULL, '29063', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)'),
(NULL, '29063', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)'),
(NULL, '29063', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)'),
(NULL, '29063', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)'),

-- Anub'ar Necromancer
(NULL, '29064', '0', '0', '100', '7', '8000', '16000','16000','24000', '11', '53334', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Animate Bones'),
(NULL, '29064', '0', '0', '100', '7', '500', '500','2000','4000', '11', '53333', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Shadow Bolt'),

-- Anub'ar Champio
(NULL, '29096', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)'),
(NULL, '29096', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)'),
(NULL, '29096', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)'),
(NULL, '29096', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)'),

-- Anub'ar Crypt Fiend
(NULL, '29097', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)'),
(NULL, '29097', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)'),
(NULL, '29097', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)'),
(NULL, '29097', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)'),

-- Anub'ar Necromancer
(NULL, '29098', '0', '0', '100', '7', '8000', '16000','16000','24000', '11', '53334', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Animate Bones'),
(NULL, '29098', '0', '0', '100', '7', '500', '500','2000','4000', '11', '53333', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Shadow Bolt'),

-- Anub'ar Champion
(NULL, '29117', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)'),
(NULL, '29117', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)'),
(NULL, '29117', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)'),
(NULL, '29117', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)'),

-- Anub'ar Crypt Fiend
(NULL, '29118', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)'),
(NULL, '29118', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)'),
(NULL, '29118', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)'),
(NULL, '29118', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)'),

-- Anub'ar Prime Guard 
(NULL, '29128', '0', '0', '100', '3', '3000', '5000','10000','16000', '11', '54314', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Drain Power (Normal)'),
(NULL, '29128', '0', '0', '100', '5', '3000', '5000','10000','16000', '11', '59354', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Drain Power (Heroic)'),
(NULL, '29128', '0', '0', '100', '3', '6000', '9000','11000','11000', '11', '54309', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Mark Of Darkness (Normal)'),
(NULL, '29128', '0', '0', '100', '5', '6000', '9000','11000','11000', '11', '59352', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Mark Of Darkness (Heroic)'),

-- Anub'ar Webspinner 
(NULL, '29335', '0', '0', '100', '3', '500', '500','2000','4000', '11', '54290', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Shot (Normal)'),
(NULL, '29335', '0', '0', '100', '5', '500', '500','2000','4000', '11', '59362', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Shot (Heroic)'),
(NULL, '29335', '0', '0', '100', '7', '9000', '11000','9000','11000', '11', '52086', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Wrap');
