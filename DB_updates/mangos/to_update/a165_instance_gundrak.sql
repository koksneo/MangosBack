##### GUNDRAK

DELETE FROM spell_script_target WHERE entry=54878;
INSERT INTO spell_script_target VALUES
(54878,1,29307);

UPDATE creature_template SET
ScriptName='mob_sladran_summon_target'
WHERE entry=29682;

UPDATE creature_template SET
ScriptName='boss_sladran'
WHERE entry=29304;

UPDATE creature_template SET
ScriptName='boss_colossus'
WHERE entry=29307;

UPDATE creature_template SET
ScriptName='boss_drakari_elemental'
WHERE entry=29573;

UPDATE creature_template SET
ScriptName='boss_galdarah'
WHERE entry=29306;

UPDATE creature_template SET
ScriptName='boss_moorabi'
WHERE entry=29305;

UPDATE gameobject_template SET
ScriptName='go_gundrak_altar'
WHERE entry IN(192518,192519,192520);
