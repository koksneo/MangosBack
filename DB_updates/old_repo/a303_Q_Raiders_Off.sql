-- The Rider of the Unholy
-- The Rider of the Frost
-- The Rider of the Blood
DELETE FROM creature_ai_texts WHERE entry IN (-99991,-99992,-99993,-99990,-99989,-99988,-99987,-99981,-99980,-99979);
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-99993,'I\'ve been waiting.',1,'Baelok - aggro'),
(-99992, 'Don\'t stop now, I\'ve almost broken a sweat.',1,'Baelok - 50%HP'),
(-99991, 'I know no death. I will... be back... for you...',1,'Baelok - slain'),

(-99990,'I knew that you would come.',1,'Sapph - aggro'),
(-99989, 'You have some fight in you. I\'m impressed.',1,'Sapph - 50%HP'),
(-99988, 'Welcome to the world of the unliving.',1,'Sapph - killed unit'),
(-99987, 'Well fought...',1,'Sapph - slain'),

(-99981,'No shining army? No righteous words? It seems your \'honor\' suits you no longer.',1,'Rokir - aggro'),
(-99980,'Such noble boasts, but in the end, we\'ve brought you down to reality.',1,'Rokir - killed Unit'),
(-99979,': You too shall serve the Lich King.... your time comes.',1,'Rokir - slain');

-- Baelok, Dancingrune Weapon, Sapph, Rokir, Shambling Zombie
UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (30953,32496,30956,30954,32499,32503);
-- Dancingrune Weapon
UPDATE creature_template SET equipment_id = 685 WHERE entry = 32496;

DELETE FROM creature_ai_scripts WHERE creature_id IN (30953,32496,30956,30954,32499,32503);
INSERT INTO creature_ai_scripts VALUES
(3095301,30953, 4,0,100,0, 0,0,0,0, 1,-99993,0,0, 0,0,0,0, 0,0,0,0, 'Baelok - aggro'),
(3095302,30953, 2,0,100,0, 60,40,0,0, 1,-99992,0,0, 0,0,0,0, 0,0,0,0, 'Baelok - reached 50% HP'),
(3095303,30953, 6,0,100,0, 0,0,0,0, 1,-99991,0,0, 33,31159,6,0, 0,0,0,0, 'Baelok - slain'),
(3095304,30953, 0,0,80,1, 6000,8000,12000,16000, 11,61090,1,0, 0,0,0,0, 0,0,0,0, 'Baelok - Draw Soul'),
(3095305,30953, 0,0,80,1, 9000,15000,12000,16000, 11,61094,4,0, 0,0,0,0, 0,0,0,0, 'Baelok - Death Grip'),
(3095306,30953, 0,0,100,1, 18000,22000,22000,26000, 11,61086,1,17, 0,0,0,0, 0,0,0,0, 'Baelok - Summon Dancingrune Weapon'),

(3249601,32496, 0,0,100,1, 1000,2000,4000,6000, 11,60945,1,0, 0,0,0,0, 0,0,0,0, 'Dancingrune Weapon - Blood Strike'),

(3095601,30956, 4,0,100,0, 0,0,0,0, 1,-99990,0,0, 0,0,0,0, 0,0,0,0, 'Sapph - aggro'),
(3095602,30956, 2,0,100,0, 60,40,0,0, 1,-99989,0,0, 0,0,0,0, 0,0,0,0, 'Sapph - reached 50% HP'),
(3095603,30956, 5,0,100,0, 0,0,0,0, 1,-99988,0,0, 0,0,0,0, 0,0,0,0, 'Sapph - killed Unit'),
(3095604,30956, 6,0,100,0, 0,0,0,0, 1,-99987,0,0, 33,31161,6,0, 0,0,0,0, 'Sapph - slain'),
(3095605,30956, 0,0,100,1, 21000,22000,34000,36000, 11,61058,0,0, 0,0,0,0, 0,0,0,0, 'Sapph - Hungering Cold'),

(3095401,30954, 4,0,100,0, 0,0,0,0, 1,-99981,0,0, 0,0,0,0, 0,0,0,0, 'Rokir - aggro'),
(3095402,30954, 5,0,100,0, 0,0,0,0, 1,-99980,0,0, 0,0,0,0, 0,0,0,0, 'Rokir - killed Unit'),
(3095403,30954, 6,0,100,0, 0,0,0,0, 1,-99979,0,0, 33,31160,6,0, 0,0,0,0, 'Rokir - slain'),
(3095404,30954, 0,0,100,1, 7000,11000,11000,18000, 11,61112,0,0, 0,0,0,0, 0,0,0,0, 'Rokir - Death and Decay'),
(3095405,30954, 0,0,100,1, 3000,7000,13000,17000, 11,61109,1,0, 0,0,0,0, 0,0,0,0, 'Rokir - Plague Strike'),
(3095406,30954, 0,0,100,0, 20000,20000,0,0, 11,61088,1,17, 0,0,0,0, 0,0,0,0, 'Rokir - Zombie Armie'),

(3249901,32499, 0,0,100,1, 7000,11000,7000,11000, 11,61095,1,0, 0,0,0,0, 0,0,0,0, 'Shambling Zombie - Plague Blast'),
(3250301,32503, 0,0,100,1, 7000,11000,7000,11000, 11,61095,1,0, 0,0,0,0, 0,0,0,0, 'Shambling Zombie - Plague Blast');

-- Dancingrune Weapon
UPDATE creature_template SET equipment_id = 685 WHERE entry = 32496;
-- Shambling Zombie
UPDATE creature_template SET
minhealth = 12500,
maxhealth = 12700,
minlevel = 80,
maxlevel = 80,
faction_A = 21,
faction_H = 21,
mindmg = 150,
maxdmg = 250,
attackpower = 253,
dmg_multiplier = 2,
speed_walk = 0.4
WHERE entry IN (32503,32499);
