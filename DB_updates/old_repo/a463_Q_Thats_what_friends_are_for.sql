-- Support for That's what friends are for (12903) by NoFantasy

UPDATE creature_template SET AIName='EventAI' WHERE entry IN (29468,29454,29455);

DELETE FROM creature_ai_scripts WHERE creature_id IN (29468,29454,29455);
INSERT INTO creature_ai_scripts VALUES 
(2946801, 29468, 10, 0, 100, 1, 1, 5, 2000, 2000, 33, 29468, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'That\'s What Friends Are For - Credit at LOS (Quest: 12903)'),
(2945401, 29454, 10, 0, 100, 1, 1, 5, 2000, 2000, 33, 29454, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'That\'s What Friends Are For - Credit at LOS (Quest: 12903)'),
(2945501, 29455, 10, 0, 100, 1, 1, 5, 2000, 2000, 33, 29455, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'That\'s What Friends Are For - Credit at LOS (Quest: 12903)');
