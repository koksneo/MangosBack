-- Quest Boiling Point
-- Churn
UPDATE `creature_ai_scripts` SET action1_type = 2, action1_param1 = 0, action1_param2 = 0 WHERE id = 2541806;
DELETE FROM `creature_ai_scripts` WHERE id = 2541807;
INSERT INTO creature_ai_scripts VALUES
(2541807, 25418, 11, 0, 100, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Churn - Become hostile at respawn");

-- Simmer
UPDATE `creature_ai_scripts` SET action1_type = 2, action1_param1 = 0, action1_param2 = 0 WHERE id = 2541605;
DELETE FROM `creature_ai_scripts` WHERE id = 2541606;
INSERT INTO creature_ai_scripts VALUES
(2541606, 25418, 11, 0, 100, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Simmer - Become hostile at respawn");
