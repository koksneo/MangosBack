--  quest electr-shock goodness (10411)
UPDATE creature_template SET
AIName='EventAI'
WHERE entry IN(20778,20501);

DELETE from creature_ai_scripts WHERE creature_id IN(20778,20501);
INSERT into creature_ai_scripts VALUES
(2077801,20778,2,0,100,0,30,0,0,0,12,20805,1,0,12,20805,1,0,12,20805,1,0,'Void Waste- summon globule at 30% HP'),
(2050101,20501,2,0,100,0,30,0,0,0,12,20806,1,0,12,20806,1,0,12,20806,1,0,'seeping sludge- summon globule at 30% HP');

-- NPC Dimensius the All-Devouring (19554)
UPDATE creature_template SET
AIName='EventAI',
unit_flags=unit_flags &~33554432 &~512 &~256
WHERE entry=19554;

DELETE from creature_ai_scripts WHERE creature_id=19554;
INSERT into creature_ai_scripts VALUES
(1955400,19554,0,0,100,1,1000,1000,4000,4000,11,37500,1,1,0,0,0,0,0,0,0,0,'Dimensius-cast shadow spiral'),
(1955401,19554,0,0,100,1,2500,2500,10000,10000,11,37412,1,1,0,0,0,0,0,0,0,0,'Dimensius-cast shadow vault');