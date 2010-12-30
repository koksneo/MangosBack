-- Support for quest Atop the Woodlands (12083/12084)

-- Add trigger (26831) into the world
DELETE FROM creature WHERE id=26831;
INSERT INTO creature VALUES
(2683101,26831,571,1,1,0,0,2907.08,1817.69,130.849,1.08304,25,0,0,1,0,0,0),
(2683102,26831,571,1,1,0,0,2878.89,1813.92,133.439,1.49459,25,0,0,1,0,0,0);

-- Acid support for trigger (26831)
UPDATE creature_template SET 
AIName='EventAI',
modelid_1=11686,
modelid_2=11686
WHERE entry=26831;

DELETE FROM creature_ai_scripts WHERE id=2683101;
INSERT INTO creature_ai_scripts VALUES
(2683101,26831,8,0,100,1,47469,-1,0,0,16,26831,50547,6,0,0,0,0,0,0,0,0,'Atop the Woodlands Kill Credit Bunny - Quest Credit after spell hit');

DELETE FROM spell_script_target WHERE entry=50547;
INSERT INTO spell_script_target VALUES
(50547,1,26831);
