-- Quest Findinf The keymaster (10256)
DELETE FROM event_scripts WHERE id=12857;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES 
(12857, 0, 10, 19938, 3000000, 2248.43, 2227.97, 138.56, 2.48121),
(12857, 1, 7, 10256, 10, 0, 0, 0, 0);


DELETE FROM creature_ai_scripts WHERE creature_id=19938;
INSERT INTO creature_ai_scripts VALUES
(1993801,19938,10,0,100,1,1,15,2000,2000,16,19938,34717,6,0,0,0,0,0,0,0,0,'Image of Comander Sarannis-quest credit after los');

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=19938;
