-- Wild summoned Crusaders (Lamoof/Jonathan/Josephine) templates
UPDATE creature_template SET 
minlevel = 75,
maxlevel = 75,
minhealth = 10635,
maxhealth = 10635,
faction_A = 2070,
faction_H = 2070,
mindmg = 261,
maxdmg = 425,
attackpower = 158
WHERE entry IN (28136,28148,28142);

-- Dr Rogers and nearby crusader spawns
DELETE FROM creature WHERE id = 28125 OR guid IN (9000000,9000001);
INSERT INTO creature VALUES
('9000000','28125','571','1','1','0','0','5255.13','-3531.01','291.692','1.5844','300','0','0','9291','0','0','0'),
('9000001','28156','571','1','1','0','812','5249.38','-3530.32','291.693','1.10138','300','0','0','11001','0','0','0');

DELETE FROM creature_addon WHERE guid IN (117811,118251,118521,9000000,9000001);
INSERT INTO creature_addon VALUES
-- Crusaders lying
(117811,0,7,0,0,0,''),
(118251,0,7,0,0,0,''),
(118521,0,7,0,0,0,''),
(9000001,0,7,0,0,0,''),
-- Dr Rogers kneeling
(9000000,0,8,0,0,0,'');

-- Crusader's Bandage usable only on quest mobs
DELETE FROM item_required_target WHERE entry = 38330;
INSERT INTO item_required_target VALUES
(38330,1,28133),
(38330,1,28141),
(38330,1,28143);