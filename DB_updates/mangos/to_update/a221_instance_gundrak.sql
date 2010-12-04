
-- Instance Gundrak

UPDATE creature_template SET
ScriptName='mob_sladran_summon_target'
WHERE entry=29682;

UPDATE creature_template SET
ScriptName='boss_sladran'
WHERE entry=29304;

UPDATE creature_template SET
ScriptName='mob_sladran_constrictor'
WHERE entry=29713;

UPDATE creature_template SET
ScriptName='mob_sladran_snake_wrap'
WHERE entry=29742;

UPDATE creature_template SET
ScriptName='boss_colossus',
unit_flags = unit_flags&~33600
WHERE entry IN (29307, 31365);

UPDATE creature_template SET
ScriptName='boss_drakari_elemental'
WHERE entry=29573;

UPDATE creature_template SET
ScriptName='mob_living_mojo'
WHERE entry=29830;

UPDATE creature_template SET
ScriptName='boss_galdarah'
WHERE entry=29306;

UPDATE creature_template SET
ScriptName='boss_moorabi'
WHERE entry=29305;

UPDATE creature_template SET
ScriptName='boss_eck'
WHERE entry=29932;

UPDATE gameobject_template SET
ScriptName='go_gundrak_altar'
WHERE entry IN(192518,192519,192520);


DELETE from creature_ai_scripts WHERE id IN(2983005,2983006);
INSERT into creature_ai_scripts VALUES
(2983005,29830,4,0,100,2,0,0,0,0,39,15,0,0,0,0,0,0,0,0,0,0,'Living Mojo(Normal) - call for help on aggro'),
(2983006,29830,4,0,100,4,0,0,0,0,39,15,0,0,0,0,0,0,0,0,0,0,'Living Mojo(Heroic) - call for help on aggro');


DELETE from creature_ai_scripts WHERE id=2992003;
INSERT into creature_ai_scripts VALUES
(2992003,29920,6,0,100,4,0,0,0,0,34,4,4,0,0,0,0,0,0,0,0,0,'Ruin Dweller - Set instance data on death');

DELETE from creature WHERE id=29932;
INSERT into creature VALUES
(13013383,29932,604,2,1,26644,0,1636.49,931.74,107.75,0.637,3600,0,0,431392,0,0,0);

UPDATE creature_template SET mechanic_immune_mask=mechanic_immune_mask|1|16|64|256|512|1024|2048|4096|8192|65536|131072|524288|8388608|536870912
WHERE entry IN (29304,29307,29573,29306,29305,31370,30530,31368,31365,31367,29932);

DELETE FROM spell_script_target WHERE entry IN (57068, 57071, 57072, 54878);
INSERT INTO spell_script_target VALUES
(57068, 1, 30298),
(57071, 1, 30298),
(57072, 1, 30298),
(54878, 1, 29307);
