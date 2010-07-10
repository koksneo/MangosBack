-- Support for quest From Their Corpses, Rise! (12813)

-- Missing visual aura for spell Darkmender's Tincture Spell (52741)

UPDATE creature_template SET AIName='EventAI' WHERE entry IN (29330,29329,29338,29400);
DELETE FROM creature_ai_scripts WHERE id IN (2933001,2933002,2933003,2932901,2932902,2932903,2933801,2933802,2933803,2933804,2933805,2940001);
INSERT INTO creature_ai_scripts VALUES

-- Onslaught Harbor Guard (29330)
(2933001,29330,0,0,100,1,3000,3000,10000,10000,11,18802,1,3,0,0,0,0,0,0,0,0,'Onslaught Harbor Guard - Frost Shot'),
(2933002,29330,9,0,100,1,5,30,2300,3900,11,6660,1,0,0,0,0,0,0,0,0,0,'Onslaught Harbor Guard - Cast Shoot and Set Ranged Weapon'),
(2933003,29330,8,0,100,0,52741,-1,0,0,11,54415,6,17,33,29398,0,0,41,0,0,0,'Onslaught Harbor Guard - Summon Corrupted Scarlet Onslaught after spell hit'),

-- Onslaught Paladin (29329)
(2932901,29329,4,0,100,0,0,0,0,0,11,19131,1,3,0,0,0,0,0,0,0,0,'Onslaught Paladin - Cast Shield Charge on Aggro'), 
(2932902,29329,0,0,100,1,4000,4000,9000,9000,11,32774,1,0,0,0,0,0,0,0,0,0,'Onslaught Paladin - Cast Avenger\'s Shield'),
(2932903,29329,8,0,100,0,52741,-1,0,0,11,54415,6,17,33,29398,0,0,41,0,0,0,'Onslaught Paladin - Summon Corrupted Scarlet Onslaught after spell hit'),


-- Onslaught Raven Bishop (29338)
(2933801,29338,0,0,100,1,3000,3000,9000,9000,11,50740,1,0,0,0,0,0,0,0,0,0,'Onslaught Raven Bishop - Cast Raven Flock'),
(2933802,29338,2,0,100,1,50,0,6000,6000,22,1,0,0,0,0,0,0,0,0,0,0,'Onslaught Raven Bishop - Set Phase 2 at 50% HP'),
(2933803,29338,0,1,100,1,2000,2000,7000,7000,11,50750,0,4,0,0,0,0,0,0,0,0,'Onslaught Raven Bishop - Cast Raven Heal (Phase 2)'),
(2933804,29338,2,1,100,1,100,51,6000,6000,23,-1,0,0,0,0,0,0,0,0,0,0,'Onslaught Raven Bishop - Set Phase 1 (Stop healing)'),
(2933805,29338,8,0,100,0,52741,-1,0,0,11,54415,6,17,33,29398,0,0,41,0,0,0,'Onslaught Raven Bishop - Summon Corrupted Scarlet Onslaught after spell hit'),

-- Corrupted Scarlet Onslaught (29400)
(2940001,29400,11,0,100,0,0,0,0,0,11,43014,0,1,0,0,0,0,0,0,0,0,'Corrupted Scarlet Onslaught - Cast Despan Self and run away');
