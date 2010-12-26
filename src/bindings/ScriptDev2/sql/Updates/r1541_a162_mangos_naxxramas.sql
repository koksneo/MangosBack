-- NAXXRAMAS

-- Set to not working boses NON ATTACKABLE FLAG 
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE `entry` IN (15954,15936,16011,16061,16060,16064,16065,30549,16063,16028,15931,15932,15928,15989,15990,29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600);
-- North 15954,
-- Heigan 15936,
-- Loatheb 16011,
-- Instructor 16061,
-- Gothik 16060,
-- Horsameni 16064, 16065, 30549, 16063,
-- Patchewrk 16028,
-- Grobulus 15931,
-- Gluth 15932,
-- Tadius 15928,
-- Saphiron 15989,
-- Kelthuzad 15990
-- 25ppl ids
-- 29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600,

-- DOORS
UPDATE `gameobject_template` SET `flags` = '34' WHERE `entry` IN (194022);

-- Arachnid Quarter::AnubRekhan
UPDATE creature_template SET `ScriptName` = 'boss_anubrekhan', `AIName` = '' WHERE `entry` IN (15956);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15956,29249);
-- Arachnid Quarter::Crypt Guard
UPDATE creature_template SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (16573);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minlevel` = '81', `maxlevel` = '81', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (16573, 29256);

-- Arachnid Quarter::Faerlina
UPDATE creature_template SET `ScriptName` = 'boss_faerlina', `AIName` = '' WHERE `entry` IN (15953);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15953,29268);
-- Arachnid Quarter::Worshippers and folowers
DELETE FROM `creature` WHERE `id` IN (16506);
UPDATE creature_template SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (16506,16505);
UPDATE creature_template SET `minmana` ='58750', `maxmana` = '58750' WHERE `entry` IN (29273);

-- Arachnid Quarter::Maexna
UPDATE creature_template SET `ScriptName` = 'boss_maexxna', `AIName` = '' WHERE `entry` IN (15952);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15952,29278);
-- Arachnid Quarter::WebWrap
UPDATE `creature_template` SET `minhealth` = '5040', `maxhealth` = '5040' WHERE `entry` IN (16486);
UPDATE `creature_template` SET `minhealth` = '12600', `maxhealth` = '12600' WHERE `entry` IN (30183);

-- Plagued Quarter::Noth
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15954,29615);
UPDATE creature_template SET `ScriptName` = 'boss_noth', `AIName` = '' WHERE `entry` IN (15954);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15954,29615);


-- Naxxramas ACID

UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (16981);
-- DELETE EventAIScripts
DELETE FROM creature_ai_scripts WHERE creature_id IN (16981);
INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES
-- Plagued Guardian
(1698101, '16981', '0', '0', '100', '3', '5000', '15000','5000','10000', '11', '54890', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plagued Guardian - Cast Explosion (Normal)'),
(1698102, '16981', '0', '0', '100', '5', '5000', '15000','5000','10000', '11', '54891', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plagued Guardian - Cast Explosion (Heroic)');

-- NAXXRAMAS LOOT

DELETE FROM creature_loot_template WHERE entry IN (15956,29249,15953,29268,15952,29278,15954,29615);

-- Arachnid Quarter::AnubRekhan 
UPDATE creature_template SET `lootid` = '15956' WHERE `entry` IN (15956);
UPDATE creature_template SET `lootid` = '29249' WHERE `entry` IN (29249);

-- Arachnid Quarter::Faerlina
UPDATE creature_template SET `lootid` = '15953' WHERE `entry` IN (15953);
UPDATE creature_template SET `lootid` = '29268' WHERE `entry` IN (29268);

-- Arachnid Quarter::Maexxna 
UPDATE creature_template SET `lootid` = '15952' WHERE `entry` IN (15952);
UPDATE creature_template SET `lootid` = '29278' WHERE `entry` IN (29278);

-- Plagued Quarter::Noth
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (15954);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29615);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Arachnid Quarter::AnubRekhan 10ppl
('15956', '39193', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39140', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39139', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39191', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39190', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39189', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39188', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39146', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39141', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39192', '20', '2', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::AnubRekhan 25ppl
('29249', '39712', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39716', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39714', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39717', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39722', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39718', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39701', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39720', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39719', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39704', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39703', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39706', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39721', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39702', '20', '3', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Faerlina 10ppl
('15953', '39215', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39196', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39200', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39199', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39217', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39195', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39197', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39194', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39198', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39216', '20', '1', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Faerlina 25ppl
('29268', '39726', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39727', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39725', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39723', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39731', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39734', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39735', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39729', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39733', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39757', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39728', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39756', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39730', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39732', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39724', '2', '3', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Maexxna 10ppl
('15952', '39229', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39230', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39233', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39225', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39224', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39226', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39232', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39231', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39228', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39221', '20', '2', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Maexxna 25ppl
('29278', '40062', '20', '2', '1', '1', '0', '0', '0'),
('29278', '40063', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39764', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39768', '20', '3', '1', '1', '0', '0', '0'),
('29278', '40060', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39760', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39766', '20', '1', '1', '1', '0', '0', '0'),
('29278', '40061', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39765', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39758', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39767', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39763', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39759', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39761', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39762', '20', '2', '1', '1', '0', '0', '0'),
-- Emblem Heroism
('15956', '40752', '100', '0', '1', '1', '0', '0', '0'),
('15953', '40752', '100', '0', '1', '1', '0', '0', '0'),
('15952', '40752', '100', '0', '1', '1', '0', '0', '0'),
-- Emblem Valor
('29249', '40753', '100', '0', '1', '1', '0', '0', '0'),
('29268', '40753', '100', '0', '1', '1', '0', '0', '0'),
('29278', '40753', '100', '0', '1', '1', '0', '0', '0');
