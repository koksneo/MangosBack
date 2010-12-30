-- Support for quest The gearmaster(11798)

DELETE FROM event_scripts WHERE id=17209;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(17209,0,8,27995,0,0,0,0,0),
(17209,0,10,25834,300000,3999.99,4854.41,25.9699,4.69093);

-- Gearmaster Mechazod
UPDATE creature_template SET
AIName='EventAI'
WHERE entry=25834;

-- event ai
DELETE FROM creature_ai_texts WHERE entry IN(-258340,-258341,-258342,-258343,-258344);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-258340,'You were looking for me, child? Why do you come to kill me, $N I only wish to help.',0,'Gearmaster Mechazod first text'),
(-258341,'Now that I have been reassembled, we can return to a time of perfection... the time of the Titans!',0,'Gearmaster Mechazod second text'),
(-258342,'But, I can see it in your eyes, hear it in your pulse rate. You would destroy me despite my offer of immortality!',0,'Gearmaster Mechazod third text'),
(-258343,'Very well. It saddens me that it has come to this. I look upon all of you as if you were my children. I will slay you if I must!',0,'Gearmaster Mechazod fourth text'),
(-258344,'There is a noise behind you',3,'Something like raid notify');

DELETE FROM creature_ai_scripts WHERE id IN(2583400,2583401,2583402,2583403,2583404,2583405,2583406,2583407,2583408);
INSERT INTO creature_ai_scripts VALUES
(2583408,25834,0,0,100,0,10,10,0,0,18,2,0,0,0,0,0,0,0,0,0,0,'Gearmaster Mechazod-set flag non attackable'),
(2583400,25834,0,0,100,0,10,10,0,0,20,0,0,0,21,0,0,0,0,0,0,0,'Gearmaster mechazod-stop movement and auto attack'),
(2583407,25834,0,0,100,0,10,10,0,0,1,-258344,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod-text after spawn'),
(2583401,25834,0,0,100,0,1000,1000,0,0,1,-258340,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod-text after spawn'),
(2583402,25834,0,0,100,0,7000,7000,0,0,1,-258341,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod-text after spawn'),
(2583403,25834,0,0,100,0,12000,12000,0,0,1,-258342,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod-text after spawn'),
(2583404,25834,0,0,100,0,17000,17000,0,0,1,-258343,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod-text after spawn'),
(2583405,25834,0,0,100,0,18000,18000,0,0,19,2,0,0,0,0,0,0,0,0,0,0,'Gearmaster mechazod will now be able to attack and be attacked'),
(2583406,25834,0,0,100,0,18000,18000,0,0,20,1,0,0,21,1,0,0,0,0,0,0,'Gearmaster mechazod-start movement and auto attack');
