UPDATE creature_template SET 
AIName = 'EventAI',
ScriptName = ''
WHERE entry IN (30211,30212,30209);

DELETE FROM creature_ai_scripts WHERE creature_id IN (30211,30212,30209);
INSERT INTO creature_ai_scripts VALUES
(3020901,30209,8,0,100,1, 56275,-1,0,0, 11,59687,0,0, 0,0,0,0, 0,0,0,0, 'Forge Credit - Explode after bombing'),
(3021101,30211,8,0,100,1, 56275,-1,0,0, 11,59687,0,0, 0,0,0,0, 0,0,0,0, 'Forge Credit - Explode after bombing'),
(3021201,30212,8,0,100,1, 56275,-1,0,0, 11,59687,0,0, 0,0,0,0, 0,0,0,0, 'Forge Credit - Explode after bombing');
