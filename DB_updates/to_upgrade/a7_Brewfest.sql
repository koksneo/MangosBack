-- Maby duplicated with r1392_a246 but only this content is needed in future (C++ scripts parts excluded)
-- Spawns

################## creatures ################################
DELETE FROM creature WHERE id IN (26719,27584,28329,24495,27489);
INSERT INTO `creature` VALUES
-- Brewfest Spy
('9983250','26719','230','1','1','0','0','905.229','-198.137','-43.8','5.24116','120','0','0','1','0','0','0'),
-- Slurpo Fizzykeg <Brewfest Agent>
('9983249','28329','1','1','1','0','0','769.638','-4553.8','3.68778','0.0532369','120','0','0','1','0','0','0'),
-- Darna Honeybock <Brewfest Agent>
('9983248','27584','0','1','1','0','0','-5594.63','-531.25','400.15','1.13415','120','0','0','1','0','0','0'),
-- Blix Fixwidget
('9983247','24495','1','1','1','0','0','1172.38','-4288.77','21.2555','5.88808','25','0','0','7800','0','0','0'),
-- Ray'ma
('9983246','27489','1','1','1','0','0','1463.04','-4228.3','42.9591','1.01626','25','0','0','2215','0','0','0');


DELETE FROM game_event_creature WHERE guid IN (9983246,9983247,9983248,9983249,9983250);
INSERT INTO game_event_creature VALUES
(9983250,26),
(9983249,26),
(9983248,26),
(9983247,26),
(9983246,26);

DELETE FROM creature_addon WHERE guid IN (9983248,9983250);
INSERT INTO creature_addon (guid,mount,bytes1,bytes2,emote,moveflags,auras) VALUES
(9983250,0,0,0,415,0,''),
(9983248,0,0,0,415,0,'');

UPDATE creature_template SET npcflag = npcflag|3 WHERE entry IN (27584,28329,26719);

DELETE FROM creature_ai_scripts WHERE creature_id IN (26764,26776,26822);
INSERT INTO creature_ai_scripts VALUES
('2676401','26764','0','0','100','3','1000','1000','7000','7000','11','47333','4','0','0','0','0','0','0','0','0','0','Ilsa Direbrew - Send First Mug'),
('2682201','26822','0','0','100','3','1000','1000','18000','18000','11','47442','4','0','0','0','0','0','0','0','0','0','Ursula Direbrew - Barreled'),
('2677601','26776','4','0','100','2','0','0','0','0','11','50313','1','16','0','0','0','0','0','0','0','0','Direbrew minion - Mole Machine Emerge');

-- Coren Direbrew
UPDATE creature_template SET 
unit_flags = 33554434,
lootid = entry,
minlevel = 80,
maxlevel = 80,
minhealth = 302400,
maxhealth = 302400,
armor = 9729,
mindmg = 422,
maxdmg = 596,
speed_walk = 1.1,
speed_run = 1.1,
dmg_multiplier = 7.5,
attackpower = 642,
unit_class = 1,
minrangedmg = 345,
maxrangedmg = 509,
maxrangedmg = 103,
mechanic_immune_mask = 617299803,
faction_A=674,
faction_H=674,
flags_extra = 0,
scriptname = 'boss_coren_direbrew' WHERE entry = 23872;

-- Dark Iron Antagonist
UPDATE creature_template SET 
minlevel = 80,
maxlevel = 80,
faction_A = 736,
faction_H = 736,
minhealth = 12600,
maxhealth = 12600,
armor = 9729,
mindmg = 422,
maxdmg = 586,
speed_walk = 1.1,
speed_run = 1.1,
dmg_multiplier = 1,
attackpower = 642,
minrangedmg = 345,
maxrangedmg = 509,
maxrangedmg = 103,
flags_extra = 0
WHERE entry = 23795;

-- Direbrew Minion
UPDATE creature_template SET 
minlevel = 80,
maxlevel = 80,
faction_A = 1620,
faction_H = 1620,
minhealth = 10080,
maxhealth = 10080,
armor = 9729,
mindmg = 316,
maxdmg = 450,
attackpower=642,
speed_walk = 1.1,
speed_run = 1.1,
dmg_multiplier = 3,
minrangedmg = 422,
maxrangedmg = 586,
maxrangedmg = 103,
flags_extra = 0,
AIName = 'EventAI'
WHERE entry = 26776;

-- Ursula Direbrew
UPDATE creature_template SET
# faction_A = 16,
# faction_H = 16,
# minlevel = 73,
# maxlevel = 73,
# minhealth = 36000,
# maxhealth = 36000,
# armor = 7700,
# mindmg = 316,
# maxdmg = 450,
# speed = 1.1,
# dmg_multiplier = 3,
# minrangedmg = 316,
# maxrangedmg = 413,
# rangedattackpower = 158,
# flags_extra = 0,
AIName = 'EventAI'
WHERE entry = 26822;

-- Ursula Direbrew (Dark Iron Light Blue)
DELETE FROM creature_template_addon WHERE entry = 26822;
INSERT INTO creature_template_addon (entry,mount,bytes1,bytes2,emote,moveflags,auras) VALUES
(26822,0,0,0,0,0,'47759 0');

-- Ilsa Direbrew
UPDATE creature_template SET
faction_A = 14,
faction_H = 14,
minlevel = 80,
maxlevel = 80,
minhealth = 37800,
maxhealth = 37800,
armor = 9729,
mindmg = 422,
maxdmg = 586,
attackpower= 642,
speed_run = 1.1,
speed_walk= 1.1,
dmg_multiplier = 7.5,
minrangedmg = 345,
maxrangedmg = 509,
maxrangedmg = 103,
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
INSERT INTO creature_template_addon (entry,mount,bytes1,bytes2,emote,moveflags,auras) VALUES
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
# (23872,38288,0.0,4,1,1,0,0), -- Direbrew Hops
# (23872,38289,0.0,4,1,1,0,0), -- Coren's Lucky Coin
# (23872,38290,0.0,4,1,1,0,0), -- Dark Iron Smoking Pipe
# (23872,38287,0.0,4,1,1,0,0), -- Empty Mug of Direbrew
# (23872,37128,0.0,4,1,1,0,0), -- Balebrew Charm
# (23872,37127,0.0,4,1,1,0,0); -- Brightbrew Charm

-- level 80 trinkets availeble since 3.2.0
# (23872,49118,0.0,4,1,1,0,0), -- Bubbling Brightbrew Charm
# (23872,49116,0.0,4,1,1,0,0), -- Bitter Balebrew Charm
(23872,49074,0.0,4,1,1,0,0), -- Coren's Chromium Coaster
(23872,49076,0.0,4,1,1,0,0), -- Mithril Pocketwatch
(23872,49080,0.0,4,1,1,0,0), -- Brawler's Souvenir
(23872,49078,0.0,4,1,1,0,0); -- Ancient Pickled Egg

################## gameobjects ###############################

DELETE FROM gameobject WHERE id IN (188498,186880);
INSERT INTO `gameobject` VALUES
-- Mole Console (near portal)
('233031','188498','230','1','1','416.985','7.24355','-71.0274','0.327595','0','0','0.163066','0.986615','25','100','0'),
-- Mole machine (near portal)
('233401','186880','230','1','1','437.1','-1.96379','-70.7342','2.66842','0','0','0.972144','0.234384','25','100','1');

DELETE FROM game_event_gameobject WHERE guid IN (233032,233401);
INSERT INTO game_event_gameobject VALUES 
(233032,26),
(233401,26);

############### other #######################################

-- Brewfest correction
delete from game_event where entry = 26;
insert into `game_event` values('26','2009-09-20 18:00:00','2020-12-30 21:00:00','525600','20160','372','Brewfest');

DELETE FROM creature_questrelation WHERE id IN (27584,28329,26719);
INSERT INTO creature_questrelation VALUES
(26719,12062),
(28329,12318),
(27584,12318);

################# Insult Coren (12062)

UPDATE quest_template SET StartScript=12062 WHERE entry=12062;

DELETE FROM quest_start_scripts WHERE id=12062;
INSERT INTO quest_start_scripts VALUES
(12062,0,10,23872,18000000,0,0,0,0,891.346,-177.675,-43.9242,3.69433);
