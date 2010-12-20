-- Runed Giant

UPDATE creature_template SET 
ScriptName='spell_dummy_npc',
AIName = 'EventAI'
WHERE entry IN (26417);

DELETE FROM creature_ai_scripts WHERE creature_id = 26417;
INSERT INTO creature_ai_scripts VALUES
(2641701,26417,0,0,100,1, 0,0,30000,30000, 11,49717,0,1, 0,0,0,0, 0,0,0,0, 'Runed Giant - Rune Fist - in Combat'),
(2641702,26417,0,0,100,1, 6000,9000,15000,15000, 11,55196,1,0, 0,0,0,0, 0,0,0,0, 'Runed Giant - Stomp'); 

-- item Gavrock's Runebreaker focus on Runed Giant
DELETE FROM item_required_target WHERE entry = 36796;
INSERT INTO item_required_target VALUES
(36796,1,26417);
