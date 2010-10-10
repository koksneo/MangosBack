-- Support for quest Conjurer Luminrath (10306)

DELETE FROM creature WHERE id=19548;

-- event 12609
DELETE FROM event_scripts WHERE id=12609;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,datalong3,data_flags,dataint,x,y,z,o) VALUES
(12609,0,10,19548,4000,0,0,0,2191.15,2339.52,90.4991,5.95157),
(12609,3,0,0,19544,15,0x02,2000007002,0,0,0,0);

DELETE FROM db_script_string WHERE entry=2000007002;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000007002,'I can\'t possibly go out without my cloak. I hope it\'s in here...');

UPDATE creature_template SET AIName='EventAI' WHERE entry=19548;

-- 19548 trigger
DELETE FROM creature_ai_scripts WHERE creature_id=19548;
INSERT INTO creature_ai_scripts VALUES
(1954801,19548,10,0,100,1,1,10,2000,2000,16,19548,34142,6,0,0,0,0,0,0,0,0,'Conjurer Luminrath trigger - Quest Credit'),
(1954802,19548,1,0,100,0,1000,1000,1000,1000,32,19544,6,19544,0,0,0,0,0,0,0,0,'Conjurer Luminrath trigger - Summon Conjurer Luminrath');

DELETE FROM creature_ai_summons WHERE id=19544;
INSERT INTO creature_ai_summons VALUES
(19544,2193.74,2338.9,89.9965,3.99296 ,5000,'Conjurer Luminrath Spawn Place');

-- Conjurer Luminrath 19544
UPDATE creature_template SET MovementType=0 WHERE entry=19544;
-- faction 1810
DELETE FROM creature_ai_scripts WHERE creature_id=19544;
INSERT INTO creature_ai_scripts VALUES
(1954401,19544,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Conjurer Luminrath - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(1954402,19544,4,0,100,0,0,0,0,0,11,9532,1,0,23,1,0,0,0,0,0,0,'Conjurer Luminrath - Cast Lightning Bolt and Set Phase 1 on Aggro'),
(1954403,19544,9,13,100,1,0,40,3400,4800,11,9532,1,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Cast Lightning Bolt (Phase 1)'),
(1954404,19544,3,13,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Conjurer Luminrath - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'),
(1954405,19544,9,13,100,0,35,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Start Combat Movement at 35 Yards (Phase 1)'),
(1954406,19544,9,13,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Prevent Combat Movement at 15 Yards (Phase 1)'),
(1954407,19544,9,13,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Start Combat Movement Below 5 Yards (Phase 1)'),
(1954408,19544,3,11,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Set Phase 1 when Mana is above 15% (Phase 2)'),
(1954409,19544,9,0,100,1,0,5,19000,25000,11,36109,0,1,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Cast Blink'),
(1954410,19544,2,0,100,1,50,0,45000,60000,11,36110,0,1,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Summon Dancing Sword at 50% HP'), 
(1954411,19544,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Set Phase to 0 on Evade'), 
(1954412,19544,11,0,100,0,0,0,0,0,2,35,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Friendly faction on Spawn'),
(1954413,19544,1,0,100,0,4000,4000,0,0,2,1810,0,0,0,0,0,0,0,0,0,0,'Conjurer Luminrath - Friendly faction on Spawn');
