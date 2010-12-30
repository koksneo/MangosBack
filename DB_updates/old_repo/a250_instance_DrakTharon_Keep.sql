################### not related trash  #############################

-- Drakkari dead guardians realy dead
UPDATE creature SET 
DeathState = 1 WHERE id = 26620 AND guid IN (SELECT guid FROM creature_addon WHERE bytes1 = 7);
-- If dead ones are dead remove nonattackable and unselectable flags
UPDATE creature_template SET unit_flags = unit_flags &~2 &~33554432 WHERE entry IN (26620,31339);

DELETE FROM creature WHERE id IN (15631, 30534) AND map = 600;
INSERT INTO creature VALUES
-- Spotlight
('9000048','15631','600','3','1','0','0','-483.741','-722.726','30.2465','1.95575','25','0','0','4120','0','0','0'),
-- Elder Kilias
('9000049','30534','600','3','1','0','0','-483.819','-722.418','30.2465','1.74212','25','0','0','1','0','0','0');
-- Elder Kilias
UPDATE creature_template SET
npcflag = npcflag |1|2
WHERE entry = 30534;

-- Q: Kilias the Elder
DELETE FROM creature_questrelation WHERE quest = 13023;
DELETE FROM creature_involvedrelation WHERE quest = 13023;

INSERT INTO creature_questrelation VALUES
(30534,13023);
INSERT INTO creature_involvedrelation VALUES
(30534,13023);

REPLACE INTO game_event_creature VALUES
(9000048,7),
(9000049,7);

################### Novos the Summoner #############################
-- Crystal Channel Target
UPDATE creature_template SET 
InhabitType = 4,
scale = 0.1,
flags_extra = 2,
faction_A = 35,
faction_H = 35,
unit_flags = unit_flags|2|33554432
WHERE entry = 26712;

-- Novos Summon Target
UPDATE creature_template SET 
InhabitType = 4,
scale = 0.1,
flags_extra = 130,
faction_A = 35,
faction_H = 35,
unit_flags = unit_flags|2|33554432,
ScriptName = 'npc_novos_summon_target'
WHERE entry = 27583;

--  Crystal Handler (N)
UPDATE `creature_template` SET 
`minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '21000',
`maxhealth` = '22000',
`minmana` = '7800',
`maxmana` = '8100',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '450',
`maxdmg` = '600',
`AIName` = 'EventAI',
`dmg_multiplier` = '2' 
WHERE `entry` = 26627;

--  Crystal Handler (H)
UPDATE `creature_template` SET 
`minlevel` = '80',
`maxlevel` = '81',
`minhealth` = '42000',
`maxhealth` = '42000',
`minmana` = '8000',
`maxmana` = '9000',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '450',
`maxdmg` = '600',
`dmg_multiplier` = '3' 
WHERE `entry` = 31344;

-- Risen Shadowcaster (N)
UPDATE `creature_template` SET 
`minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '1600',
`maxhealth` = '1700',
`minmana` = '7800',
`maxmana` = '7900',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '450',
`maxdmg` = '600',
`AIName` = 'EventAI',
`dmg_multiplier` = '2' 
WHERE `entry` = 27600;

-- Risen Shadowcaster (H)
UPDATE `creature_template` SET 
`minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '3100',
`maxhealth` = '3200',
`minmana` = '8900',
`maxmana` = '9000',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '450',
`maxdmg` = '600',
`dmg_multiplier` = '3' 
WHERE `entry` = 31356;

-- Fetid Troll Corpse (N)
UPDATE `creature_template` SET 
`minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '2050',
`maxhealth` = '2100',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2'
WHERE `entry` = 27598;

-- Fetid Troll Corpse (H)
UPDATE `creature_template` SET 
`minlevel` = '80',
`maxlevel` = '80',
`minhealth` = '3700',
`maxhealth` = '3800',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '3'
WHERE `entry` = 31873;

-- Hulking Corpse (N)
UPDATE `creature_template` SET 
`minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '12500',
`maxhealth` = '13000',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2' 
WHERE `entry` = 27597;

-- Hulking Corpse (H)
UPDATE `creature_template` SET 
`minlevel` = '80',
`maxlevel` = '81',
`minhealth` = '26000',
`maxhealth` = '26100',
`faction_A` = '21',
`faction_H` = '21',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '3' 
WHERE `entry` = 31348;

-- Rotted Troll Corpse (N & H)
UPDATE creature_template SET 
faction_A = 21,
faction_H = 21,
minlevel = 80,
maxlevel = 80,
minhealth = 3700,
maxhealth = 3800,
mindmg = 150,
maxdmg = 250,
attackpower = 150,
dmg_multiplier = 2
WHERE entry IN (32786,32787);

-- Novos the Summoner (N & H)
UPDATE creature_template SET
faction_A = 21,
faction_H = 21
WHERE entry in (31350, 26631);

-- Delete all Crystal Target creature addon befor replacing triggers
DELETE FROM creature_addon WHERE guid IN (SELECT guid FROM creature WHERE id = 26712);

DELETE FROM creature WHERE id IN (26712,27583);
INSERT INTO creature VALUES
-- Crystal Channel Target
('127498','26712','600','3','1','15468','0','-392.416','-724.865','33','3.14159','86400','0','0','4050','0','0','0'),
('127499','26712','600','3','1','15468','0','-365.279','-751.087','33','3.14159','86400','0','0','4050','0','0','0'),
('127500','26712','600','3','1','15468','0','-365.410','-724.865','33','3.14159','86400','0','0','4050','0','0','0'),
('127501','26712','600','3','1','15468','0','-392.286','-751.087','33','3.14159','86400','0','0','4050','0','0','0'),
-- Novos Summon Target
('127502','27583','600','3','1','0','0','-379.329','-813.393','62.2485','0','86400','2','0','1','0','0','1');
-- Novos the Summoner - disable random movement
UPDATE creature SET 
MovementType = '0',
SpawnDist = '0'
WHERE id = 26631;

-- Delete crystals from crystal handler loot_template. Since 3.0.3 they are not neccessary
DELETE FROM creature_loot_template WHERE item = 38555;

-- Crystals
UPDATE gameobject SET animprogress = 100 WHERE id IN (189299,189300,189301,189302);

/* Boss damage */
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26630;
-- King Dred
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 27483;
-- Prophet Tharonja
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26632;

UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (26627,27600);
DELETE FROM `creature_ai_scripts` WHERE creature_id IN (26627,27600);
INSERT INTO `creature_ai_scripts` VALUES
-- Crystal Handler 
(2662701,26627, 0,0,100,7, 5000,10000,5000,10000, 11,49668,1,0, 0,0,0,0, 0,0,0,0, 'Crystal Handler - Flash of Darkness'),
(2662702,26627, 6,0,100,6, 0,0,0,0, 34,9,4,0, 0,0,0,0, 0,0,0,0, 'Crystal Handler - Update Crystal Event at death'),

-- Risen Shadowcaster - modified ranged movement that he cannot cast in midair
(2760001,27600, 1,0,100,6, 2000,2000,0,0, 21,0,0,0, 22,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(2760002,27600, 4,0,100,2, 2000,2000,0,0, 11,51363,1,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster (Normal) - Cast Fireball and Set Phase 1 on Aggro'),
(2760003,27600, 9,5,100,3, 0,40,5400,6800, 11,51363,1,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster (Normal) - Cast Fireball (Phase 1)'),
(2760004,27600, 4,0,100,4, 2000,2000,0,0, 11,59016,1,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster (Heroic) - Cast Fireball and Set Phase 1 on Aggro'),
(2760005,27600, 9,5,100,5, 0,40,5400,6800, 11,59016,1,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster (Heroic) - Cast Fireball (Phase 1)'),
(2760006,27600, 3,5,100,6, 15,0,0,0, 21,1,0,0, 23,1,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement and Set Phase 2 when Mana is at 15% (Phase 1)'),
(2760007,27600, 9,5,100,6, 35,80,0,0, 21,1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement at 35 Yards (Phase 1)'),
(2760008,27600, 9,5,100,6, 5,15,0,0, 21,0,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Prevent Combat Movement at 15 Yards (Phase 1)'),
(2760009,27600, 9,5,100,6, 0,5,0,0, 21,1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Start Combat Movement Below 5 Yards'),
(2760010,27600, 3,3,100,7, 100,15,100,100, 23,-1,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Set Phase 1 when Mana is above 15% (Phase 2)'),
(2760011,27600, 7,0,100,6, 0,0,0,0, 22,0,0,0, 0,0,0,0, 0,0,0,0, 'Risen Shadowcaster - Set Phase to 0 on Evade');

-- Beam channel
-- ATTENTION: HACK COMMING! - this should work in reverse mode (from Novos to crystal targets) 
-- but in case that core does not support multiple SCRIPT_TARGET targets should i could'nt find any other way
DELETE FROM spell_script_target WHERE entry = 52106;
INSERT INTO spell_script_target VALUES
(52106,1,26631);

################### Prophet Tharon'Ja ##############################
-- Tharon'ja spawn
DELETE FROM `creature` WHERE id = 26632;
INSERT INTO `creature` VALUES ('9000047','26632','600','3','1','0','0','-237.689','-675.933','131.865','1.60904','286400','0','0','512278','4169','0','0');

-- The Prophet Tharon'ja (N)
UPDATE creature_template SET
faction_a = 21,
faction_h = 21,
minlevel = 71,
maxlevel = 75,
attackpower = 726,
dmg_multiplier = 7,
mindmg = 463,
maxdmg = 640,
minhealth = 275000,
maxhealth = 276000
WHERE entry = 26632;

-- The Prophet Tharon'ja (H)
UPDATE creature_template SET
faction_a = 21,
faction_h = 21,
minlevel = 82,
maxlevel = 82,
attackpower = 726,
dmg_multiplier = 13,
mindmg = 463,
maxdmg = 640,
minhealth = 510000,
maxhealth = 520000
WHERE entry = 31360;

###################   Trollgore   ####################################
DELETE FROM spell_script_target WHERE entry IN (49555,59807,49405);
INSERT INTO spell_script_target VALUES
-- Corpse Explosion focused on Draktaron Invider "A"
(49555,1,27754),
(59807,1,27754),
-- Taunt Invider Trigger focused on Trollgore
(49405,1,26630); 

-- Draktaron Invider "C"
UPDATE creature_template SET
unit_flags = unit_flags|2|33554432
WHERE entry = 27754;

-- Trollgore Summon Target (hax)
DELETE FROM creature_template WHERE entry = 40003;
INSERT INTO `creature_template` VALUES 
(40003, 0, 0, 0, 0, 0, 169, 0, 11686, 0, 'Trollgore Summon Target', '', '', 0, 1, 1, 1, 1, 0, 0, 7, 35, 35, 0, 1, 1.14286, 0.1, 1, 2, 2, 0, 24, 7.5, 2000, 0, 1, 33554434, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 130, '');
-- Trollgore Summon Target
DELETE FROM creature WHERE id = 40003;
INSERT INTO `creature` VALUES
('9000875','40003','600','3','1','0','0','-262.336','-660.278','26.5184','3.13495','25','0','0','1','0','0','0');

-- Trollgore at the foot of the steps
DELETE FROM creature where guid = 127422;
INSERT INTO creature VALUES
('127422','26630','600','3','1','0','0','-294.981','-659.024','10.9238','3.14124','3600','5','0','431392','0','0','0');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (27709);

DELETE FROM creature_ai_scripts WHERE creature_id IN (27709);
INSERT INTO creature_ai_scripts VALUES
(2770901, 27709,6,0,100,6, 0,0,0,0, 11,49458,0,17, 0,0,0,0, 0,0,0,0, 'Drakthar Invader - summon own corpse'),
(2770902, 27709,11,0,100,6, 0,0,0,0, 11,49405,0,0, 0,0,0,0, 0,0,0,0, 'Drakthar Invader - summon own corpse');

-- Drakari Invader "C"
DELETE FROM creature_template_addon WHERE entry = 27754;
INSERT INTO creature_template_addon (entry,mount,bytes1,b2_0_sheath) VALUES
(27754,0,7,1);

UPDATE creature_template SET ScriptName = 'boss_dred' WHERE entry = 27483;


