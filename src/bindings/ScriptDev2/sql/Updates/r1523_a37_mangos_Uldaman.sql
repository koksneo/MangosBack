UPDATE instance_template SET script = 'instance_uldaman' WHERE map = 70;
UPDATE gameobject_template SET ScriptName = 'go_altar_of_keepers' WHERE entry = 130511;
UPDATE gameobject_template SET ScriptName = 'go_altar_of_archaedas' WHERE entry = 133234;
UPDATE creature_template SET ScriptName = 'mob_archaeras_add' WHERE entry IN (10120,7309,7076,7077);
UPDATE creature_template SET ScriptName = 'boss_archaedas' WHERE entry = 2748;


REPLACE INTO creature_ai_scripts VALUES
('485702','4857', '6','0','100','2',' 0','0','0','0', '11','9874','1','7', '34','1','4','0', '0','0','0','0','Stone Keeper - Cast Self Destruct on Death');

