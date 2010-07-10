-- Spawns
-- Mole Machine
UPDATE gameobject_template SET flags = 36 WHERE entry = 188508;
REPLACE INTO  `gameobject` values('233715','188508','230','1','1','894.044','-143.76','-49.7569','0.634812','0','0','0.312103','0.950048','25','0','1');

-- Coren Direbrew
DELETE FROM creature WHERE id = 23872 OR guid = 1050065;
INSERT INTO `creature` VALUES ('1050065','23872','230','1','1','0','0','888.573','-172.031','-43.9241','3.77057','1200','0','0','1','0','0','0');

-- Assign to Brewfest
DELETE FROM game_event_creature WHERE guid = 1050065;
DELETE FROM game_event_gameobject WHERE guid = 233715;
INSERT INTO game_event_creature VALUES
(1050065,26);
INSERT INTO game_event_gameobject VALUES
(233715,26);

-- Brewfest correction
delete from game_event where entry = 26;
insert into `game_event` values('26','2009-09-20 18:00:00','2020-12-30 21:00:00','525600','20160','372','Brewfest');


DELETE FROM creature_ai_scripts WHERE creature_id IN (26764,26776,26822);
INSERT INTO creature_ai_scripts VALUES
('2676401','26764','0','0','100','3','1000','1000','7000','7000','11','47333','4','0','0','0','0','0','0','0','0','0','Ilsa Direbrew - Send First Mug'),
('2682201','26822','0','0','100','3','1000','1000','18000','18000','11','47442','4','0','0','0','0','0','0','0','0','0','Ursula Direbrew - Barreled'),
('2677601','26776','4','0','100','2','0','0','0','0','11','50313','1','16','0','0','0','0','0','0','0','0','Direbrew minion - Mole Machine Emerge');

-- Request Second Mug assigned to Ilsa Direbrew
DELETE FROM spell_script_target WHERE entry = 47344;
INSERT INTO spell_script_target VALUES
(47344,1,26764);


-- Coren Direbrew
UPDATE creature_template SET 
unit_flags = 33554434,
lootid = 23872,
minlevel = 73,
maxlevel = 73,
minhealth = 320000,
maxhealth = 320000,
armor = 7700,
mindmg = 316,
maxdmg = 450,
speed = 1.1,
dmg_multiplier = 35,
unit_class = 1,
minrangedmg = 278,
maxrangedmg = 413,
rangedattackpower = 58,
mechanic_immune_mask = 617299803,
flags_extra = 0,
scriptname = 'boss_coren_direbrew' WHERE entry = 23872;

-- Dark Iron Antagonist
UPDATE creature_template SET 
minlevel = 70,
maxlevel = 70,
faction_A = 674,
faction_H = 674,
minhealth = 12600,
maxhealth = 12600,
armor = 7700,
mindmg = 316,
maxdmg = 450,
speed = 1.1,
dmg_multiplier = 3,
minrangedmg = 278,
maxrangedmg = 413,
rangedattackpower = 58,
flags_extra = 0
WHERE entry = 23795;

-- Direbrew Minion
UPDATE creature_template SET 
minlevel = 70,
maxlevel = 70,
faction_A = 16,
faction_H = 16,
minhealth = 12600,
maxhealth = 12600,
armor = 7700,
mindmg = 316,
maxdmg = 450,
speed = 1.1,
dmg_multiplier = 3,
minrangedmg = 178,
maxrangedmg = 213,
rangedattackpower = 58,
flags_extra = 0,
AIName = 'EventAI'
WHERE entry = 26776;

-- Ursula Direbrew
UPDATE creature_template SET
faction_A = 16,
faction_H = 16,
minlevel = 73,
maxlevel = 73,
minhealth = 36000,
maxhealth = 36000,
armor = 7700,
mindmg = 316,
maxdmg = 450,
speed = 1.1,
dmg_multiplier = 3,
minrangedmg = 316,
maxrangedmg = 413,
rangedattackpower = 158,
flags_extra = 0,
AIName = 'EventAI'
WHERE entry = 26822;

-- Ursula Direbrew (Dark Iron Light Blue)
DELETE FROM creature_template_addon WHERE entry = 26822;
INSERT INTO creature_template_addon VALUES
(26822,0,0,0,0,0,'47759 0');

-- Ilsa Direbrew
UPDATE creature_template SET
faction_A = 16,
faction_H = 16,
minlevel = 73,
maxlevel = 73,
minhealth = 36000,
maxhealth = 36000,
armor = 7700,
mindmg = 316,
maxdmg = 450,
speed = 1.1,
dmg_multiplier = 3,
minrangedmg = 278,
maxrangedmg = 413,
rangedattackpower = 58,
flags_extra = 0,
equipment_id = 26764,
AIName = 'EventAI'
WHERE entry = 26764;

-- Ilsa Direbrew (Two tankards in hands)
DELETE FROM creature_equip_template WHERE entry = 26764;
INSERT INTO creature_equip_template VALUES
(26764,34140,34140,0);

-- Ilsa Direbrew (Dark Iron Light Blue)
DELETE FROM creature_template_addon WHERE entry = 26764;
INSERT INTO creature_template_addon VALUES
(26764,0,0,0,0,0,'47760 0');
-- Coren loot
DELETE FROM creature_loot_template WHERE entry = 23872;
INSERT INTO creature_loot_template (`entry`,`item`,`chanceorquestchance`,`groupid`,`mincountorref`,`maxcount`,`lootcondition`,`condition_value1`) VALUES
(23872,37863,4.0,1,1,1,0,0), -- remote
(23872,33977,1.8,1,1,1,0,0), -- Swift Brewfest Ram
(23872,37828,1.8,1,1,1,0,0), -- Great Brewfest Kodo
(23872,38280,0.0,2,1,1,6,469), -- Direbrew's Dire Brew (alliance)
(23872,38281,0.0,3,1,1,6,67), -- Direbrew's Dire Brew (horde)
-- level 70 trinkets
(23872,38288,0.0,4,1,1,0,0), -- Direbrew Hops
(23872,38289,0.0,4,1,1,0,0), -- Coren's Lucky Coin
(23872,38290,0.0,4,1,1,0,0), -- Dark Iron Smoking Pipe
(23872,38287,0.0,4,1,1,0,0), -- Empty Mug of Direbrew
(23872,37128,0.0,4,1,1,0,0), -- Balebrew Charm
(23872,37127,0.0,4,1,1,0,0); -- Brightbrew Charm
/*
-- level 80 trinkets availeble since 3.2.0
(23872,49118,0.0,4,1,1,0,0), -- Bubbling Brightbrew Charm
(23872,49116,0.0,4,1,1,0,0), -- Bitter Balebrew Charm
(23872,49074,0.0,4,1,1,0,0), -- Coren's Chromium Coaster
(23872,49076,0.0,4,1,1,0,0), -- Mithril Pocketwatch
(23872,49080,0.0,4,1,1,0,0), -- Brawler's Souvenir
(23872,49078,0.0,4,1,1,0,0), -- Ancient Pickled Egg*/
