-- support for q An End to the Suffering

DELETE FROM creature_ai_scripts WHERE id IN(2841601,2841602,2841603,2841604,2841605);
INSERT INTO creature_ai_scripts VALUES
(2841601,28416,8,0,100,1,51964,-1,0,0,19,33536,0,0,2,16,0,0,0,0,0,0,'Revive Rhunok after spelhit'),
(2841602,28416,6,0,100,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,'Set correct faction on death'),
(2841603,28416,7,0,100,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,'Set correct faction on evade'),
(2841605,28416,0,0,100,1,1000,1000,25000,25000,11,57861,1,0,0,0,0,0,0,0,0,0,'Rhunok - Cast Roar of Rhunok'),
(2841604,28416,0,0,100,1,3000,3000,5000,5000,11,34298,1,0,0,0,0,0,0,0,0,0,'Rhunok - Cast Maul');

UPDATE creature_template SET
ScriptName='',
AIName='EventAI'
WHERE entry=28416;
