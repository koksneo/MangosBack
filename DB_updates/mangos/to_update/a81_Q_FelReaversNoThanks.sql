-- Support for quest Fel Reavers, No Thanks! (10855)

UPDATE quest_template SET
CompleteScript=10850
WHERE entry=10850;

DELETE from quest_end_scripts where id =10850;
INSERT INTO quest_end_scripts (id,delay,command,datalong,datalong2) VALUES
(10850,0,8,22293,0),
(10850,0,7,10855,15);

-- Legion Fel Cannon (21233)
UPDATE creature_template SET AIName='EventAI' WHERE entry=21233;

DELETE FROM creature_ai_scripts WHERE creature_id=21233;
INSERT INTO creature_ai_scripts VALUES
(2123301,21233,4,0,100,0,0,0,0,0,21,0,0,0,20,0,0,0,0,0,0,0,'Legion Fel Cannon - No movement and attack'),
(2123302,21233,9,0,100,1,30,100,10000,10000,24,0,0,0,0,0,0,0,0,0,0,0,'Legion Fel Cannon - Combat Stop'),
(2123303,21233,0,0,100,1,1000,1000,3000,3000,11,36238,1,3,0,0,0,0,0,0,0,0,'Legion Fel Cannon - Cast Fel Cannon Blast');
