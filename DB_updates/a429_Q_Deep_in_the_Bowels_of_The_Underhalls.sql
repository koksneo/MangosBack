-- SUpport for quest Deep in the Bowels of The Underhalls (13042)

-- Apprentice Osterkilgr (30409)
UPDATE creature_template SET AIName='EventAI' WHERE entry=30409;

-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-304091,-304092);
INSERT INTO creature_ai_texts VALUES
(-304091,'You\'ve come for the doctor\'s plans! You\'ll only find death! ',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Apprentice Osterkilgr Yell1'),
(-304092,'The doctor entrusted me with the plans to Nergeld, our flesh giant amalgamation made entirely of vargul! It will be the most powerful creation of its kind and a whole legion of them will be created to destroy your pitiful forces!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,0,0,'Apprentice Osterkilgr Yell2');

-- EventAi

DELETE FROM creature_ai_scripts WHERE id IN (3040901,3040902,3040903,3040904,3040905,3040906,3040907,3040908,3040909,3040910,3040911);
INSERT INTO creature_ai_scripts VALUES
(3040901,30409,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Prevent Combat Movement and Set Phase to 0 on Spawn'), 
(3040902,30409,4,0,100,0,0,0,0,0,11,14034,1,0,23,1,0,0,1,-304091,0,0,'Apprentice Osterkilgr - Cast Fireball, Yell and Set Phase 1 on Aggro'),
(3040903,30409,9,5,100,1,0,40,3400,4800,11,14034,1,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Cast Fireball (Phase 1)'),
(3040904,30409,3,5,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Apprentice Osterkilgr - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'), 
(3040905,30409,9,5,100,0,35,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Start Combat Movement at 35 Yards (Phase 1)'), 
(3040906,30409,9,5,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Prevent Combat Movement at 15 Yards (Phase 1)'), 
(3040907,30409,9,5,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Start Combat Movement Below 5 Yards (Phase 1)'), 
(3040908,30409,3,3,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Set Phase 1 when Mana is above 15% (Phase 2)'),
(3040909,30409,0,0,100,1,3000,6000,20000,25000,11,60290,1,1,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Blast Wave'),
(3040910,30409,2,0,100,0,40,0,0,0,33,30412,6,0,1,-304092,0,0,0,0,0,0,'Apprentice Osterkilgr - Information beaten (Quest Credit)'), 
(3040911,30409,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Apprentice Osterkilgr - Set Phase to 0 on Evade');
