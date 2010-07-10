-- Hozzer - NPC related to quest The Jig is Up (random timers)
UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 24547;
DELETE FROM creature_ai_scripts WHERE creature_id = 24547;
INSERT INTO creature_ai_scripts VALUES
(2454701, 24547, 0, 0, 80, 1, 5000, 10000, 30000, 60000, 11, 64319, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hozzer - Knockback'),
(2454702, 24547, 0, 0, 80, 1, 1000, 3000, 3000, 9000, 11, 34298, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hozzer - Maul');
