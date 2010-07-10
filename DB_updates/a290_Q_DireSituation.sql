-- A Dire situation (10506)

-- Rina's Diminution Powder (30251)
DELETE FROM item_required_target WHERE entry = 30251;
INSERT INTO item_required_target VALUES
(30251,1,20058);

-- Bloodmaul Dire Wolf (20058)
DELETE FROM creature_ai_scripts WHERE creature_id = 20058;
INSERT INTO creature_ai_scripts VALUES
(2005801,20058,0,0,100,1,2000,5000,16000,19000, 11,13443,1,0, 0,0,0,0, 0,0,0,0,'Bloodmaul Dire Wolf - Cast Rend'),
(2005802,20058,8,0,100,0,36310,-1,0,0, 33,21176,6,0, 0,0,0,0, 0,0,0,0,'Bloodmaul Dire Wolf - Quest Credit after spell hit');

UPDATE creature_template SET 
AIName= 'EventAI'
WHERE entry=20058;
