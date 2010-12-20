-- Aponi Brightmane
UPDATE creature_template SET
-- Thunderbluff
faction_A = 104,
faction_H = 104,
minhealth = 3100,
maxhealth = 3200,
minmana = 2100,
maxmana = 2200,
mindmg = 100,
maxdmg = 300,
dmg_multiplier = 3,
minlevel = 55,
maxlevel = 55,
npcflag = npcflag|3
WHERE entry = 34526;

-- Aponi Brightmane
DELETE FROM creature WHERE id = 34526;
INSERT INTO creature VALUES
('9000007','34526','1','1','1','0','0','-1036.33','-302.449','159.03','2.2673','300','0','0','3111','2111','0','0');

-- Aponi Brightmane
DELETE FROM creature_addon WHERE guid = 9000007;
INSERT INTO creature_addon (guid,mount,bytes1) VALUES
(9000007,0,1);

-- Lok'lira the Crone
UPDATE creature_template SET
faction_A = 2109,
faction_H = 2109,
npcflag = npcflag |3
WHERE entry = 29975;

-- Lok'lira the Crone
DELETE FROM creature WHERE id = 29975;
INSERT INTO creature VALUES
('9000008','29975','571','1','1','0','0','6963.3','-1522.4','837.836','4.22549','300','0','0','12175','0','0','0');

-- Drom Frostgrip
UPDATE creature_template SET 
-- Frostborn
faction_A = 84,
faction_H = 84,
npcflag = npcflag|3
WHERE entry = 29751;

-- Drom Frostgrip
DELETE FROM creature WHERE id = 29751;
INSERT INTO creature VALUES
('9000009','29751','571','1','1','0','0','6930.1','19.4265','797.242','5.84432','300','0','0','126000','0','0','0');

-- Drom Frostgrip
DELETE FROM creature_addon WHERE guid = 9000009;
INSERT INTO creature_addon (guid,mount,bytes1) VALUES
(9000009,0,7);

-- The Iron Watcher
UPDATE creature_template SET 
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 4,
AIName = 'EventAI' 
WHERE entry = 30142;

-- The Iron Watcher
DELETE FROM creature WHERE id = 30142;
INSERT INTO creature VALUES
('9000010','30142','571','1','1','0','0','8408.94','-1962.46','1462.67','0.0443919','300','0','0','100800','0','0','0');

-- Boktar Bloodfury
DELETE FROM creature WHERE id = 29651;
INSERT INTO creature VALUES
('9000011','29651','571','1','1','0','0','7846.53','-811.645','1184.75','2.07769','300','0','0','12600','3994','0','0');

-- Creteus
UPDATE creature_template SET
faction_A = 1926,
faction_H = 1926,
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 4,
minlevel = 80,
maxlevel = 80,
minhealth = 126000,
maxhealth = 126000
WHERE entry = 30082;

-- Creteus
DELETE FROM creature WHERE id = 30082;
INSERT INTO creature VALUES
('9000012','30082','571','1','1','0','0','7270.86','-865.41','926.178','4.38383','300','0','0','126000','0','0','0');
