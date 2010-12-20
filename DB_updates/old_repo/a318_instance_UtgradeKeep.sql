-- Frost Tomb
UPDATE creature_template SET
unit_flags = unit_flags|2|33554432
WHERE entry IN (23965,31672);

##################################### Ingvar the Plunderer ####################################################################

-- Ingvar Throw Dummy 
UPDATE creature_template SET 
AIName = 'EventAI',
ScriptName = ''
WHERE entry = 23997;

UPDATE creature_template SET unit_flags = unit_flags |2|33554432  WHERE entry IN (23997,31835);

DELETE FROM creature_ai_scripts WHERE creature_id = 23997;
INSERT INTO creature_ai_scripts VALUES
(2399701, 23997, 4, 0, 100, 2, 0,0,0,0, 11,42750,0,1, 21,0,0,0, 0,0,0,0, ''),
(2399702, 23997, 4, 0, 100, 4, 0,0,0,0, 11,59719,0,1, 21,0,0,0, 0,0,0,0, ''),
(2399703, 23997, 0, 0, 100, 6, 30000,30000,0,0, 41,0,0,0, 0,0,0,0, 0,0,0,0, '');


UPDATE creature_template SET equipment_id = 23997 WHERE entry IN (23997,31835);
DELETE FROM creature_equip_template WHERE entry = 23997;
INSERT INTO creature_equip_template VALUES
(23997,35576,0,0);

-- Annhylde the Caller
UPDATE creature_template SET flags_extra = flags_extra | 128 WHERE entry = 23996;
UPDATE creature_template SET
faction_A = 35,
faction_H = 35,
InhabitType = 4
WHERE entry IN (24068,31655);

DELETE FROM spell_script_target WHERE entry = 42857;
INSERT INTO spell_script_target VALUES
(42857, 1, 23954);
