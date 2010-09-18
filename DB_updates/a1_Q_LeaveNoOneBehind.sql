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

-- Crusader's Bandage usable only on quest mobs
DELETE FROM item_required_target WHERE entry = 38330;
INSERT INTO item_required_target VALUES
(38330,1,28133),
(38330,1,28141),
(38330,1,28143);
