-- UDB development part
-- Vault Warder, Stone Keeper (slow golems)
UPDATE creature_template SET speed_run = 0.4 WHERE entry IN (4857,10120);

-- Earthen Custodian
-- Earthen Guardian
-- Earthen HallShaper
-- Vault Warder
-- Stone Keeper
-- Achaedas
UPDATE creature_template SET 
unit_flags = unit_flags |0x02000000,
faction_A = 416,
faction_H = 416
WHERE entry IN (2748,7309,7076,7077,4857,10120);

-- Achaedas
REPLACE INTO creature_addon (guid,mount,bytes1,b2_0_sheath,auras) VALUES
(33537,0,0,4097,'10255 0');

-- Awake Guardian
DELETE FROM spell_script_target WHERE entry = 10259;
INSERT INTO spell_script_target VALUES 
(10259,1,7309),
(10259,1,7077);

UPDATE creature_ai_scripts SET
action2_type = 34,
action2_param1 = 1,
action2_param2 = 4
WHERE id = 485702;

UPDATE creature_template SET ScriptName = 'boss_archaedas' WHERE entry = 2748;
UPDATE creature_template SET ScriptName = 'mob_archaeras_add' WHERE entry IN (7309,7076,7077,10120);
UPDATE gameobject_template SET ScriptName = 'go_altar_of_keepers' WHERE entry = 130511;
UPDATE gameobject_template SET ScriptName = 'go_altar_of_archaedas' WHERE entry = 133234;

