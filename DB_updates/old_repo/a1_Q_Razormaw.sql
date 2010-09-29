-- Razormaw
DELETE FROM creature_template_addon WHERE entry = 17592;
INSERT INTO creature_template_addon VALUES
('17592','0','16908544','4097','0','1073741824',NULL);
-- Razormaw
UPDATE creature_template SET 
unit_flags = 0,
AIName = 'EventAI',
ScriptName = ''
WHERE entry = 17592;
-- Razormaw
DELETE FROM creature_ai_scripts WHERE creature_id = 17592;
INSERT INTO creature_ai_scripts VALUES
(1759201,17592,0,0,100,1, 10000,10000,25000,25000, 11,31279,0,0, 0,0,0,0, 0,0,0,0,'Razormaw - Swipe'),
(1759202,17592,0,0,100,1, 20000,20000,25000,25000, 11,14100,0,0, 0,0,0,0, 0,0,0,0,'Razormaw - Terrifying Roar'),
(1759203,17592,0,0,100,1, 30000,30000,10000,10000, 11,8873,1,0, 0,0,0,0, 0,0,0,0,'Razormaw - Flame Breath');