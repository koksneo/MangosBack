-- HALLS OF LIGHTING

-- HallsOfLighting::Bengram
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_bjarngrim' WHERE `entry` IN (28586);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31533);

-- HallsOfLighting::Volkano
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_volkhan' WHERE `entry` IN (28587);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31536);
-- HallsOfLighting::Molten Golem norm/hero
UPDATE `creature_template` SET `AIName` = '', `Scriptname` = 'mob_molten_golem', `mindmg` = '200', `maxdmg` = '400', `attackpower` = '300', `armor` = '4000', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '25000', `maxhealth` = '25000', `faction_A` = '14', `faction_H` = '14', `type_flags` ='0' WHERE `entry` IN (28695);
UPDATE `creature_template` SET `mindmg` = '200', `maxdmg` = '400', `attackpower` = '300', `dmg_multiplier` = '5', `armor` = '4000', `faction_A` = '14', `faction_H` = '14', `type_flags` ='0' WHERE `entry` IN (30969);

-- HallsOfLighting::Ionar
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_ionar' WHERE `entry` IN (28546);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31537);
-- HallsOfLighting::Spark movement speed
UPDATE creature_template SET `speed` = '0.8' WHERE `entry` IN (28926,31867);

-- HallsOfLighting::Loken
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_loken' WHERE `entry` IN (28923);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31538);

-- HallsOfLighting::Thunderer and Siegebreaker flags remove
UPDATE `creature_template` SET `unit_flags` = '0',`type_flags` = '0' WHERE `entry` IN (28965,28961,30980,30982);


-- HALLS OF LIGHTING LOOT

DELETE FROM creature_loot_template WHERE entry IN (31533,31536,31537,31538);

-- HallsOfLighting::Bengram hero
UPDATE creature_template SET `lootid` = '31533' WHERE `entry` IN (31533);
-- HallsOfLighting::Volkano hero
UPDATE creature_template SET `lootid` = '31536' WHERE `entry` IN (31536);
-- HallsOfLighting::Ionar hero
UPDATE creature_template SET `lootid` = '31537' WHERE `entry` IN (31537);
-- HallsOfLighting::Loken hero
UPDATE creature_template SET `lootid` = '31538' WHERE `entry` IN (31538);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- HallsOfLighting::Bengram 5ppl heroic
('31533', '37826', '0', '1', '1', '1', '0', '0', '0'),
('31533', '37814', '0', '1', '1', '1', '0', '0', '0'),
('31533', '37818', '0', '1', '1', '1', '0', '0', '0'),
('31533', '37825', '0', '1', '1', '1', '0', '0', '0'),
('31533', '43852', '3', '0', '1', '4', '0', '0', '0'),

-- HallsOfLighting::Volkano 5ppl heroic
('31536', '37842', '0', '1', '1', '1', '0', '0', '0'),
('31536', '37843', '0', '1', '1', '1', '0', '0', '0'),
('31536', '37840', '0', '1', '1', '1', '0', '0', '0'),
('31536', '37841', '0', '1', '1', '1', '0', '0', '0'),
('31536', '43852', '3', '0', '1', '4', '0', '0', '0'),

-- HallsOfLighting::Ionar 5ppl heroic
('31537', '37846', '0', '1', '1', '1', '0', '0', '0'),
('31537', '37845', '0', '1', '1', '1', '0', '0', '0'),
('31537', '37847', '0', '1', '1', '1', '0', '0', '0'),
('31537', '37844', '0', '1', '1', '1', '0', '0', '0'),
('31537', '43852', '3', '0', '1', '4', '0', '0', '0'),
('31537', '37700', '27', '0', '2', '9', '0', '0', '0'),

-- HallsOfLighting::Loken 5ppl heroic
('31538', '37850', '0', '1', '1', '1', '0', '0', '0'),
('31538', '37851', '0', '1', '1', '1', '0', '0', '0'),
('31538', '37849', '0', '1', '1', '1', '0', '0', '0'),
('31538', '37848', '0', '1', '1', '1', '0', '0', '0'),
('31538', '37853', '0', '2', '1', '1', '0', '0', '0'),
('31538', '37852', '0', '2', '1', '1', '0', '0', '0'),
('31538', '37855', '0', '2', '1', '1', '0', '0', '0'),
('31538', '37854', '0', '2', '1', '1', '0', '0', '0'),
('31538', '41799', '9', '0', '1', '1', '0', '0', '0'),
('31538', '43102', '100', '0', '1', '1', '0', '0', '0'),

-- Haals Of lighting
('31533', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31536', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31537', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31538', '40752', '100', '0', '1', '1', '0', '0', '0');

-- HALLS OF LIGHTING ACID

-- Update EVENTAI
UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (28580,28578,28579,28583,28584,28965,28838,28961,28836,28835,28837,28920,28826,28547);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (28580,28578,28579,28583,28584,28965,28838,28961,28836,28835,28837,28920,28826,28547);

-- Hardened Steel Skycaller
INSERT INTO creature_ai_scripts VALUES (NULL, '28580', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52755', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Skycaller - Cast MultiShoot (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28580', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59147', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Skycaller - Cast MultiShoot (Heroic)');

-- Hardened Steel Reaver
INSERT INTO creature_ai_scripts VALUES (NULL, '28578', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '15655', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Reaver - Cast ShieldSlam (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28578', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59142', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Reaver - Cast ShieldSlam (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28578', '0', '0', '100', '7', '4000', '8000','16000','24000', '11', '42724', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Reaver - Cast Cleave ');

-- Hardened Steel Berserker
INSERT INTO creature_ai_scripts VALUES (NULL, '28579', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52740', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Berserker - Cast Hurl Weapon (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28579', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59259', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Berserker - Cast Hurl Weapon (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28579', '2', '0', '100', '7', '30', '0','0','0', '11', '61369', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Hardened Steel Berserker - Enrage ');

-- Blistering Steamrager
INSERT INTO creature_ai_scripts VALUES (NULL, '28583', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52531', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Blistering Steamrager - Cast Steam Blust (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28583', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59141', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Blistering Steamrager - Cast Steam Blust (Heroic)');

-- Unbound Firestorm
INSERT INTO creature_ai_scripts VALUES (NULL, '28584', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52624', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Unbound Firestorm - Cast Steam Blust (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28584', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59183', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Unbound Firestorm - Cast Steam Blust (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28584', '0', '0', '100', '3', '10000', '15000','10000', '15000', '11', '53788', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Unbound Firestorm - Cast Steam Blust (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28584', '0', '0', '100', '5', '10000', '15000','10000', '15000', '11', '59182', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Unbound Firestorm - Cast Steam Blust (Heroic)');

-- Titanium Thunderer
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52885', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Deadly Throw (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59180', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Deadly Throw (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '3', '7000', '16000','25000','35000', '11', '52879', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Deflection (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '5', '7000', '16000','25000','35000', '11', '59181', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Deflection (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '3', '10000', '15000','10000', '15000', '11', '52904', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Throw (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28965', '0', '0', '100', '5', '10000', '15000','10000', '15000', '11', '59179', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Thunderer - Cast Throw (Heroic)');

-- Titanium Vanguard
INSERT INTO creature_ai_scripts VALUES (NULL, '28838', '0', '0', '100', '7', '4000', '8000','16000','24000', '11', '58619', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Vanguard - Cast Charge');
INSERT INTO creature_ai_scripts VALUES (NULL, '28838', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '53059', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Vanguard - Cast Poison Spear (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28838', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59178', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Vanguard - Cast Poison Spear (Heroic)');

-- Titanium Siegebreaker
INSERT INTO creature_ai_scripts VALUES (NULL, '28961', '0', '0', '100', '7', '10000', '20000','20000','35000', '11', '23600', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Siegebreaker - Cast PiercingHowl');
INSERT INTO creature_ai_scripts VALUES (NULL, '28961', '0', '0', '100', '7', '15000', '18000','16000','24000', '11', '52890', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Siegebreaker - Cast Penetration Strike');
INSERT INTO creature_ai_scripts VALUES (NULL, '28961', '0', '0', '100', '7', '25000', '35000','30000','40000', '11', '19134', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Siegebreaker - Cast Fightering Shout');
INSERT INTO creature_ai_scripts VALUES (NULL, '28961', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52891', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Siegebreaker - Cast Blade Tuning (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28961', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59173', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Titanium Siegebreaker - Cast Blade Tuning (Heroic)');

-- Stormforged Runeshaper
INSERT INTO creature_ai_scripts VALUES (NULL, '28836', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '53049', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Runeshaper - Cast Flurry (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28836', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '61581', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Runeshaper - Cast Flurry (Heroic)');

-- Stormforged Construct
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '53167', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Forked Lighting (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59152', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Forked Lighting (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '3', '7000', '16000','25000','35000', '11', '53068', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Rune Punch (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '5', '7000', '16000','25000','35000', '11', '59151', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Rune Punch (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '3', '10000', '15000','10000', '15000', '11', '61579', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Runic Focus (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28835', '0', '0', '100', '5', '10000', '15000','10000', '15000', '11', '61596', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Construct - Cast Runic Focus (Heroic)');

-- Stormforged Sentinel
INSERT INTO creature_ai_scripts VALUES (NULL, '28837', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '34423', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Sentinel - Cast Renew (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28837', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '37978', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Sentinel - Cast Renew (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28837', '0', '0', '100', '3', '10000', '15000','10000', '15000', '11', '53045', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Sentinel - Cast Slepp (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28837', '0', '0', '100', '5', '10000', '15000','10000', '15000', '11', '59165', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Sentinel - Cast Sleep (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28837', '0', '0', '100', '7', '10000', '12000','15000', '25000', '11', '53047', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Sentinel - Cast Storming Below');

-- Stormforged Giant
INSERT INTO creature_ai_scripts VALUES (NULL, '28920', '0', '0', '100', '7', '10000', '16000','30000', '50000', '11', '32315', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Giant - Cast SoulStrike');
INSERT INTO creature_ai_scripts VALUES (NULL, '28920', '0', '0', '100', '3', '10000', '15000','10000', '15000', '11', '53072', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Giant - Cast Stormbolt (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28920', '0', '0', '100', '5', '10000', '15000','10000', '15000', '11', '59155', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Giant - Cast Stormbolt (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28920', '0', '0', '100', '3', '15000', '25000','15000', '25000', '11', '53071', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Giant - Cast ThunderStorm (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28920', '0', '0', '100', '5', '15000', '25000','15000', '25000', '11', '59154', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormforged Giant - Cast ThunderStorm (Heroic)');

-- Stormfury Revenant
INSERT INTO creature_ai_scripts VALUES (NULL, '28826', '0', '0', '100', '3', '15000', '25000','15000', '25000', '11', '53043', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormfury Revenant - Cast ElectroShock (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28826', '0', '0', '100', '5', '15000', '25000','15000', '25000', '11', '59168', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormfury Revenant - Cast ElectroShock (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28826', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '52905', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormfury Revenant - Cast ThunderBolt (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28826', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59167', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Stormfury Revenant - Cast ThunderBolt (Heroic)');

-- Storming Vortex
INSERT INTO creature_ai_scripts VALUES (NULL, '28547', '0', '0', '100', '3', '5000', '10000','20000','30000', '11', '53044', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Storming Vortex - Cast LightingBolt (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28547', '0', '0', '100', '5', '5000', '10000','20000','30000', '11', '59169', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Storming Vortex - Cast LightingBolt (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28547', '0', '0', '100', '7', '10000', '16000','30000', '50000', '11', '60236', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Storming Vortex - Cast Cyclone');
