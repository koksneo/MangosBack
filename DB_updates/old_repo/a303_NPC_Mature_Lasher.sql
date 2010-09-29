-- Mature Lasher (34300) improve dmg by Grandres
UPDATE creature_template SET
armor=9728,
mindmg=210,
maxdmg=290,
dmg_multiplier=2,
attackpower=642,
dynamicflags=1,
lootid=34300,
AIName='EventAI'
WHERE entry=34300;

-- ACID add spell Dream Lash (51901)

-- Mature Lasher (34300)
DELETE FROM creature_ai_scripts WHERE id=3430001;
INSERT INTO creature_ai_scripts VALUES
(3430001,34300,0,0,75,1,1400,4800,5800,10800,11,51901,1,0,0,0,0,0,0,0,0,0,'Mature Lasher  - Cast Dream Lash');

-- Emerald Lasher (27254)
UPDATE creature_template SET AIName='EventAI' WHERE entry=27254;
DELETE FROM creature_ai_scripts WHERE id=2725401;
INSERT INTO creature_ai_scripts VALUES
(2725401,27254,0,0,75,1,1400,4800,5800,10800,11,51901,1,0,0,0,0,0,0,0,0,0,'Emerald Lasher - Cast Dream Lash');

-- Living Lasher (30845)
UPDATE creature_template SET AIName='EventAI' WHERE entry=30845;
DELETE FROM creature_ai_scripts WHERE id=3084501;
INSERT INTO creature_ai_scripts VALUES
(3084501,34300,0,0,75,1,1400,4800,5800,10800,11,51901,1,0,0,0,0,0,0,0,0,0,'Living Lasher  - Cast Dream Lash');
