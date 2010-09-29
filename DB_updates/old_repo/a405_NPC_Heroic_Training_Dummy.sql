-- Heroic Training Dummy (31146) 

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=31146;

-- No movement and attack, combat reset
DELETE FROM creature_ai_scripts WHERE creature_id=31146;
INSERT INTO creature_ai_scripts VALUES
(3114601,31146,4,0,100,0,0,0,0,0,21,0,0,0,20,0,0,0,0,0,0,0,'Heroic Training Dummy - No movement and attack'),
(3114602,31146,9,0,100,1,30,100,10000,10000,24,0,0,0,0,0,0,0,0,0,0,0,'Heroic Training Dummy - Combat Stop');