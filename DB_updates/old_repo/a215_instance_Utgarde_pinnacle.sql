-- UTGARDE PINNACLE instance template
/*
-- Utgarde Pinnacle::Svala
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '1', `maxdmg` = '1', `attackpower` = '1', `mechanic_immune_mask` = '1073463287', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '315000', `maxhealth` = '315000', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21', `AIName` = '', `Scriptname` = 'boss_svala' WHERE `entry` IN (26668);
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '1', `maxdmg` = '1', `attackpower` = '1', `dmg_multiplier` = '13', `mechanic_immune_mask` = '1073463287', `minlevel` = '82', `maxlevel` = '82', `minhealth` = '431392', `maxhealth` = '431392', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (30810);
-- Utgarde Pinnacle::svala ritual channelerer
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '8121', `maxhealth` = '8121', `minmana` = '15976', `maxmana` = '15976',`AIName` = '', `Scriptname` = 'npc_svala_channeler' WHERE `entry` IN (27281);
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '81', `maxlevel` = '81', `minhealth` = '13033', `maxhealth` = '13033', `minmana` = '16324', `maxmana` = '16324' WHERE `entry` IN (30804);
-- Utgarde Pinnacle::Skadi harpoonlancher
UPDATE gameobject_template SET ScriptName = 'go_skaldi_harpoonluncher' WHERE entry IN (192175,192176,192177);


-- Utgarde Pinnacle::Grouf not used in event for  now
-- DELETE FROM creature WHERE id = '26893';

-- Skadi the Ruthless(N)
UPDATE `creature_template` SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287, `AIName` = '', `Scriptname` = 'boss_skadi' WHERE `entry` IN (26693);
-- Skadi the Ruthless(H)
UPDATE `creature_template` SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (30807);

-- Ymirjar Harpooner(N)
-- Ymirjar Witch Doctor(N)
-- Ymirjar Warrior(N)
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '18262', `maxhealth` = '18262', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000' WHERE `entry` IN (26692,26690,26691);
-- Ymirjar Harpooner(H)
-- Ymirjar Witch Doctor(H)
-- Ymirjar Warrior(H)
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '26066', `maxhealth` = '26066', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000', `dmg_multiplier` ='7.5' WHERE `entry` IN (30819,30823,30822);
-- Ymirjar Witch Doctor(N)
UPDATE `creature_template` SET `minmana` = '4080', `maxmana` = '4080' WHERE `entry` IN (26691);
*/
-- Spirit Fount
UPDATE creature_template SET
faction_A = 14,
faction_H = 14,
minlevel = 82,
maxlevel = 82,
modelid_1 = 11686,
modelid_2 = 11686,
flags_extra = flags_extra &~128 &~2,
unit_flags = unit_flags|2|33554432,
AIName = ''
WHERE entry IN (30808,27339);

-- Avenging Spirit
UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 27386;
-- Avenging Spirit (N)
UPDATE creature_template SET
faction_A = 14,
faction_H = 14,
minhealth = 3000,
maxhealth = 3000,
minlevel = 80,
maxlevel = 80,
mindmg = 150,
maxdmg = 350,
dmg_multiplier = 3,
attackpower = 53
WHERE entry = 27386;

-- Avenging Spirit (H)
UPDATE creature_template SET
faction_A = 14,
faction_H = 14,
minhealth = 12000,
maxhealth = 12000,
minlevel = 80,
maxlevel = 80,
mindmg = 250,
maxdmg = 450,
dmg_multiplier = 3,
attackpower = 53
WHERE entry = 30756;

-- Avenging Spirit & Spirit Fount
UPDATE creature_template SET ScriptName = 'mob_ymiron_add' WHERE entry IN (27386,27339);


-- Avenging Spirit Summoner
UPDATE creature_template SET
unit_flags = unit_flags|2|33554432,
flags_extra = flags_extra &~128 |2,
modelid_1 = 11686,
modelid_2 = 11686,
AIName = 'EventAI'
WHERE entry IN (27392,30757);

-- Avengering Spirit Summoner
DELETE FROM creature_ai_scripts WHERE creature_id = 27392;
INSERT INTO creature_ai_scripts VALUES 
(2739201,27392,11,0,100,6, 0,0,0,0, 11,48593,0,0,0,0,0,0,0,0,0,0,'Avengering Spirit Summoner - Visual Effect'),
(2739202,27392,1,0,100,6, 2500,2500,0,0, 11,48592,0,0, 0,0,0,0, 0,0,0,0,'Avengering Spirit Summoner - Summon Spirit');

-- Kings Spirits (just invisible not triggers)
UPDATE creature_template SET 
flags_extra = flags_extra &~ 128 |2 
WHERE entry IN (27303,27307,27308,27309,30780,30782,30784,30786);

REPLACE INTO creature VALUES
('126128','27303','575','3','1','11686','0','370.639','-314.325','107.302','0.034907','604800','0','0','13945','0','0','0'),
('126147','27307','575','3','1','11686','0','413.959','-314.937','107.288','3.12414','604800','0','0','13945','0','0','0'),
('126148','27308','575','3','1','11686','0','413.568','-335.497','107.298','3.14159','604800','0','0','13945','0','0','0'),
('126149','27309','575','3','1','11686','0','370.12','-334.903','107.281','0.05236','604800','0','0','13945','0','0','0');

-- Spirit fount Beam
DELETE FROM spell_script_target WHERE entry = 48385;
INSERT INTO spell_script_target VALUES
(48385, 1, 27339);
