-- Support for quest Unusual Activity (11886)

DELETE FROM creature_ai_texts WHERE entry IN (-258661,-258662,-258663,-253241,-253242);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-258661,'You are not allowed to interfere!',0,'Twilight MFF event aggro 1'),
(-258662,'The elements will crush you!',0,'Twilight MFF event aggro 2'),
(-258663,'Our vision will be realized!',0,'Twilight MFF event aggro 3'),
(-253241,'What is it you need?',0,'Earthen Ring Guide MFF event say 1'),
(-253242,'Have you discovered something?',0,'Earthen Ring Guide MFF event say 2');

## Earthen Ring Guide (25324)
UPDATE creature_template SET
minhealth=42,
maxhealth=42,
AIName='EventAI'
WHERE entry=25324;

-- Event Ai
DELETE FROM creature_ai_scripts WHERE creature_id=25324;
INSERT INTO creature_ai_scripts VALUES
(2532401,25324,10,0,100,0,1,5,0,0,1,-253241,-253242,0,22,1,0,0,0,0,0,0,'Earthen Ring Guide - Say on Spawn');


## Twilight Firesworn (25863)
UPDATE creature_template SET
minlevel=20,
maxlevel=21,
faction_A=834,
faction_H=834,
mindmg=31,
maxdmg=40,
minhealth=405,
maxhealth=432,
minmana=1202,
maxmana=1272,
mingold=20,
maxgold=28,
armor=872,
attackpower=72,
AIName='EventAI'
WHERE entry=25863;

-- Event Ai
DELETE FROM creature_ai_scripts WHERE creature_id=25863;
INSERT INTO creature_ai_scripts VALUES
(2586301,25863,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Twilight Firesworn - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(2586302,25863,4,0,100,0,0,0,0,0,11,14034,1,0,23,1,0,0,1,-258661,-258662,-258663,'Twilight Firesworn - Cast Fireball, Say and Set Phase 1 on Aggro'),
(2586303,25863,9,5,100,1,0,40,3400,4800,11,20793,1,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Cast Fireball (Phase 1)'),
(2586304,25863,3,5,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Twilight Firesworn - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'),
(2586305,25863,9,5,100,0,35,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Start Combat Movement at 35 Yards (Phase 1)'),
(2586306,25863,9,5,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Prevent Combat Movement at 15 Yards (Phase 1)'),
(2586307,25863,9,5,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Start Combat Movement Below 5 Yards (Phase 1)'),
(2586308,25863,3,3,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Set Phase 1 when Mana is above 15% (Phase 2)'),
(2586309,25863,0,0,100,1,100,100,60000,60000,11,184,0,1,0,0,0,0,0,0,0,0,'Twilight Firesworn - Fire Shield II'),
(2586310,25863,2,0,100,0,35,0,30000,30000,1,-47,0,0,25,0,0,0,0,0,0,0,'Twilight Firesworn - Flee at 35% HP'),
(2586311,25863,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Twilight Firesworn - Set Phase to 0 on Evade');

## Twilight Speaker Viktor (25924)
UPDATE creature_template SET
minlevel=22,
maxlevel=22,
faction_A=834,
faction_H=834,
mindmg=31,
maxdmg=40,
minhealth=486,
maxhealth=486,
minmana=1357,
maxmana=1357,
mingold=20,
maxgold=28,
armor=872,
attackpower=72,
AIName='EventAI'
WHERE entry=25924;

-- Event Ai
DELETE FROM creature_ai_scripts WHERE creature_id=25924;
INSERT INTO creature_ai_scripts VALUES
(2592401,25924,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(2592402,25924,4,0,100,0,0,0,0,0,11,14034,1,0,23,1,0,0,0,0,0,0,'Twilight Speaker Viktor - Cast Fireball and Set Phase 1 on Aggro'),
(2592403,25924,9,5,100,1,0,40,3400,4800,11,20793,1,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Cast Fireball (Phase 1)'),
(2592404,25924,3,5,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Twilight Speaker Viktor - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'),
(2592405,25924,9,5,100,0,35,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Start Combat Movement at 35 Yards (Phase 1)'),
(2592406,25924,9,5,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Prevent Combat Movement at 15 Yards (Phase 1)'),
(2592407,25924,9,5,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Start Combat Movement Below 5 Yards (Phase 1)'),
(2592408,25924,3,3,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Set Phase 1 when Mana is above 15% (Phase 2)'),
(2592409,25924,0,0,100,1,100,100,60000,60000,11,184,0,1,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Fire Shield II'),
(2592410,25924,2,0,100,0,35,0,30000,30000,1,-47,0,0,25,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Flee at 35% HP'),
(2592411,25924,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Twilight Speaker Viktor - Set Phase to 0 on Evade');

## Twilight Flameguard (25866)
UPDATE creature_template SET
minlevel=20,
maxlevel=21,
faction_A=834,
faction_H=834,
mindmg=31,
maxdmg=40,
minhealth=482,
maxhealth=521,
mingold=20,
maxgold=28,
armor=872,
attackpower=72,
AIName='EventAI'
WHERE entry=25866;

-- Event Ai
DELETE FROM creature_ai_scripts WHERE creature_id=25866;
INSERT INTO creature_ai_scripts VALUES
(2586601,25866,4,0,100,0,0,0,0,0,1,-258661,-258662,-258663,0,0,0,0,0,0,0,0,'Twilight Flameguard - Say on Aggro'),
(2586602,25866,2,0,100,0,35,0,30000,30000,1,-47,0,0,25,0,0,0,0,0,0,0,'Twilight Flameguard - Flee at 35% HP');

#### Loot ######
UPDATE creature_template SET lootid=entry WHERE entry IN (25866,25863,25924);
DELETE FROM creature_loot_template WHERE entry IN (25866,25863,25924);
INSERT INTO creature_loot_template VALUES
(25866,35277,-70,1,1,1,0,0,0),		-- quest item
(25866,2589,27,0,1,3,0,0,0),		-- Linen Cloth
(25866,2592,27,0,1,2,0,0,0),		-- Wool Cloth
(25866,2698,1,0,1,1,0,0,0),		-- Recipe: Cooked Crab Claw
(25863,35277,-70,1,1,1,0,0,0),		-- quest item
(25863,2589,27,0,1,3,0,0,0),		-- Linen Cloth
(25863,2592,27,0,1,2,0,0,0),		-- Wool Cloth
(25863,2698,1,0,1,1,0,0,0),		-- Recipe: Cooked Crab Claw
(25924,35277,-80,1,1,1,0,0,0),		-- quest item
(25924,2589,27,0,1,3,0,0,0),		-- Linen Cloth
(25924,2592,27,0,1,2,0,0,0),		-- Wool Cloth
(25924,2698,1,0,1,1,0,0,0);		-- Recipe: Cooked Crab Claw

######################## Spawns by me. Not sniffed ################################################
-- Missing creatures add into world 

DELETE FROM creature WHERE id IN (25863,25866,25924);
INSERT INTO creature VALUES
(2592401,25924,1,1,1,0,0,3923.9,789.9,9.05769,0.750508,300,0,0,486,1357,0,0),
(2586601,25866,1,1,1,0,0,3958.57,823.016,6.09683,0.74054,300,5,0,521,0,0,1),
(2586602,25866,1,1,1,0,0,3982.36,841.999,2.56443,0.690331,300,5,0,521,0,0,1),
(2586603,25866,1,1,1,0,0,3945.94,834.062,7.80991,2.21313,300,5,0,521,0,0,1),
(2586604,25866,1,1,1,0,0,3934.96,753.987,6.63639,5.25824,300,5,0,521,0,0,1),
(2586605,25866,1,1,1,0,0,3926.69,765.568,7.77702,4.46073,300,5,0,521,0,0,1),
(2586606,25866,1,1,1,0,0,3887.86,763.413,6.00979,2.23319,300,5,0,521,0,0,1),
(2586607,25866,1,1,1,0,0,3870.98,785.064,3.42641,2.23319,300,5,0,521,0,0,1),
(2586608,25866,1,1,1,0,0,3903.97,799.964,7.83297,2.51514,300,5,0,521,0,0,1),
(2586609,25866,1,1,1,0,0,3941.87,858.115,0.999292,1.9204,300,5,0,521,0,0,1),
(2586301,25863,1,1,1,0,0,3898.1,817.742,2.16935,1.92369,300,5,0,432,1272,0,1),
(2586302,25863,1,1,1,0,0,3912.09,827.88,1.31645,2.44205,300,5,0,432,1272,0,1),
(2586303,25863,1,1,1,0,0,3922.91,813.284,7.79417,2.48211,300,5,0,432,1272,0,1),
(2586304,25863,1,1,1,0,0,3934.53,823.407,7.80139,2.34702,300,5,0,432,1272,0,1),
(2586305,25863,1,1,1,0,0,3933.07,851.871,1.13049,2.45148,300,5,0,432,1272,0,1),
(2586306,25863,1,1,1,0,0,3998.66,822.534,2.63403,0.727154,300,5,0,432,1272,0,1),
(2586307,25863,1,1,1,0,0,3962.7,845.893,7.98477,2.33018,300,5,0,432,1272,0,1),
(2586308,25863,1,1,1,0,0,3952.1,797.957,8.72479,6.00424,300,5,0,432,1272,0,1),
(2586309,25863,1,1,1,0,0,3992.04,802.012,5.78606,3.84675,300,5,0,432,1272,0,1),
(2586310,25863,1,1,1,0,0,3885.49,776.535,4.74122,2.26775,300,5,0,432,1272,0,1),
(2586311,25863,1,1,1,0,0,3877.05,800.316,2.65031,1.74004,300,5,0,432,1272,0,1),
(2586312,25863,1,1,1,0,0,3983.1,819.942,8.05236,5.95875,300,5,0,432,1272,0,1);

DELETE FROM game_event_creature WHERE guid IN 
(2586308,2586307,2586306,2586305,2586304,2586303,2586301,2586302,
2586309,2586310,2586311,2586312,2586608,2586609,2586607,2586606,
2586601,2586602,2586603,2586604,2586605,2592401);
INSERT INTO game_event_creature VALUES
(2586308,1),
(2586307,1),
(2586306,1),
(2586305,1),
(2586304,1),
(2586303,1),
(2586301,1),
(2586302,1),
(2586309,1),
(2586310,1),
(2586311,1),
(2586312,1),
(2586608,1),
(2586609,1),
(2586607,1),
(2586606,1),
(2586601,1),
(2586602,1),
(2586603,1),
(2586604,1),
(2586605,1),
(2592401,1);

-- Twilight Bonfire

DELETE FROM gameobject WHERE guid IN (518634,518632,518631,518630,518629);
INSERT INTO gameobject VALUES
(518634,187918,1,1,1,3956.34,853.976,7.98246,1.26527,0,0,0.591273,0.806472,180,100,1),
(518632,187918,1,1,1,3891.12,794.378,7.69436,3.14866,0,0,0.999994,-0.00353161,180,100,1),
(518631,187918,1,1,1,3923.43,758,7.77716,4.70139,0,0,0.710986,-0.703206,180,100,1),
(518630,187918,1,1,1,3948.18,812.025,9.06615,0.698797,0,0,0.342333,0.939579,180,100,1),
(518629,187918,1,1,1,3991.08,818.215,8.00368,5.85729,0,0,0.21134,-0.977413,180,100,1);

DELETE FROM game_event_gameobject WHERE guid IN (518634,518632,518631,518630,518629);
INSERT INTO game_event_gameobject VALUES
(518634,1),
(518632,1),
(518631,1),
(518630,1),
(518629,1);
