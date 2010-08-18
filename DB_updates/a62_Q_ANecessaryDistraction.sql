-- Support for quest A Necessary Distraction (10637)

-- Azaloth (21506)
UPDATE creature_template SET AIName='EventAI' WHERE entry=21506;

DELETE FROM creature_ai_scripts WHERE creature_id=21506;
INSERT INTO creature_ai_scripts VALUES
(2150601,21506,8,0,100,1,37834,-1,0,0,1,-21506,0,0,21,6,0,0,16,21892,37834,6,'Azaloth  - Yell and Start Combat Movements'),
(2150602,21506,3,0,100,0,0,0,0,0,0,28,0,37833,0,0,0,0,0,0,0,0,'Azaloth  - Yell and Start Combat Movements'),
(2150603,21506,0,0,100,1,4000,4000,8000,8000,11,40504,1,0,0,0,0,0,0,0,0,0,'Azaloth - Cast Cleave'),
(2150604,21506,0,0,100,1,3000,3000,17000,17000,11,11443,1,1,0,0,0,0,0,0,0,0,'Azaloth Cast Cripple'),
(2150605,21506,0,0,100,1,10000,12000,33000,33000,11,38741,4,3,0,0,0,0,0,0,0,0,'Azaloth - Cast Rain of Fire'),
(2150606,21506,0,0,100,1,6000,6000,14000,14000,11,38750,1,3,0,0,0,0,0,0,0,0,'Azaloth - Cast War Stomp');

DELETE FROM creature_ai_texts WHERE entry=-21506;
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-21506,'Illidan\s lapdogs! You will pay for my imprisonment with your lives!',1,'Azaloth yell1');
