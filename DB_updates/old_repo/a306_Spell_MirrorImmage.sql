-- Mirror Immage summon
UPDATE creature_template SET 
speed_walk = 1.5,
modelid_1 = 11686,
modelid_2 = 11686,
AIName = '',
ScriptName = 'mob_mirror_image'
WHERE entry = 31216;
 
DELETE FROM creature_ai_scripts WHERE creature_id = 31216;

DELETE FROM spell_bonus_data WHERE entry IN (59637,59638);
INSERT INTO spell_bonus_data (entry, direct_bonus, dot_bonus, ap_bonus, comments) VALUES
(59637, 0.1, 0, 0, 'Mirror Image - Fire Blast'),
(59638, 0.05, 0, 0, 'Mirror Image - Frostbolt');



