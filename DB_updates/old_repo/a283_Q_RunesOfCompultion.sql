-- Rune-Weaver Channel focused on Directional Runes
DELETE FROM spell_script_target WHERE entry = 47463;
INSERT INTO spell_script_target VALUES
(47463,1,26920),
(47463,1,26921),
(47463,1,26922),
(47463,1,26923);

-- Directional Runes not targetable for player
UPDATE gameobject_template SET flags = flags|4 WHERE entry IN (188471,188505,188506,188507);

-- Removed Iron Rune-Weaver. They will be spawn by propper overseers in SD2 script
DELETE FROM creature WHERE id = 26820;

-- Spawn missing 4th Directional Rune
DELETE FROM gameobject WHERE id = 188507;
INSERT INTO gameobject VALUES
('400013','188507','571','1','1','3985.83','-5250.23','7.01735','0.05196','0','0','0.0259771','0.999663','300','100','0');

-- Spawn Overseers
DELETE FROM creature WHERE id IN (26921,26920,26922,26923);
INSERT INTO creature VALUES
('11457406','26920','571','1','1','0','749','4486.66','-4654.01','77.547','0.087266','300','0','0','10635','3561','0','0'),
('11457407','26921','571','1','1','0','749','4317.75','-4880.36','33.3857','-0.698132','300','0','0','8508','7981','0','0'),
('11457408','26922','571','1','1','0','749','4218.81','-5050.21','5.62514','-0.506145','300','0','0','10635','3561','0','0'),
('11457405','26923','571','1','1','0','870','3984.56','-5250.67','6.98164','0.336503','300','0','0','10635','3561','0','0');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 26820;

DELETE FROM creature_ai_scripts WHERE creature_id = 26820;
INSERT INTO creature_ai_scripts VALUES
(2682001,26820,1,0,100,0, 500,500,0,0 ,11,47463,0,0, 0,0,0,0, 0,0,0,0,'Iron Rune-Weaver: OOC Rune-Weaving'),
(2682002,26820,0,0,100,1, 1000,3000,30000,30000 ,11,52713,1,1, 0,0,0,0, 0,0,0,0,'Iron Rune-Weaver: Rune-Weaving');

-- Overseer Brunon
-- Overseer Durval
-- Overseer Lochli
UPDATE creature_template SET 
minlevel = 75,
maxlevel = 75,
minhealth = 10635,
maxhealth = 10635,
minmana = 3561,
maxmana = 3561,
faction_A = 754, -- Dark Iron Dwarfs
faction_H = 754,
mindmg = 120,
maxdmg = 180,
dmg_multiplier = 3,
attackpower = 2000,
scriptname = 'mob_overseer'
WHERE entry IN (26923,26922,26920);

-- Overseer Korgan
UPDATE creature_template SET 
minlevel = 75,
maxlevel = 75,
minhealth = 8508,
maxhealth = 8508,
minmana = 7981,
maxmana = 7981,
faction_A = 754,
faction_H = 754,
mindmg = 120,
maxdmg = 180,
dmg_multiplier = 3,
attackpower = 2000,
scriptname = 'mob_overseer'
WHERE entry IN (26921);
