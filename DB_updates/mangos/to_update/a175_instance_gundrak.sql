##### GUNDRAK

DELETE FROM spell_script_target WHERE entry=54878;
INSERT INTO spell_script_target VALUES
(54878,1,29307),
(54878,1,31365);

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

-- Drakkari Colossus
UPDATE creature_template SET unit_flags=0 WHERE entry IN (29307,31365);

--Drakkari Frenzy
UPDATE creature_template SET dmg_multiplier=7 WHERE entry=29834;
UPDATE creature_template SET dmg_multiplier=15 WHERE entry=30928;

-- Living Mojo
DELETE from creature_ai_scripts WHERE id IN(2983005,2983006);
INSERT into creature_ai_scripts VALUES
(2983005,29830,4,0,100,2,0,0,0,0,39,15,0,0,0,0,0,0,0,0,0,0,'Living Mojo(Normal) - call for help on 
aggro'),
(2983006,29830,4,0,100,4,0,0,0,0,39,15,0,0,0,0,0,0,0,0,0,0,'Living Mojo(Heroic) - call for help on 
aggro');

-- immune masks (charm, fear, root, silence, sleep, snare, stun, freeze, knockout, polymorph, banish, shackle, horror, sapped)

UPDATE creature_template SET mechanic_immune_mask=mechanic_immune_mask|1|16|64|256|512|1024|2048|4096|8192|65536|131072|524288|8388608|536870912
WHERE entry IN (29304,29307,29573,29306,29305,31370,30530,31368,31365,31367);

###### Emblem of Herosim ######
# Moorabi 30530
DELETE FROM creature_loot_template WHERE entry=30530 AND item=40752;
INSERT INTO creature_loot_template VALUES
(30530, 40752, 100, 5, 1, 1, 0, 0, 0);
# Drakkari Colossus  31365
DELETE FROM creature_loot_template WHERE entry=31365 AND item=40752;
INSERT INTO creature_loot_template VALUES
(31365, 40752, 100, 5, 1, 1, 0, 0, 0);
# Gal'darah 31368
DELETE FROM creature_loot_template WHERE entry=31368 AND item=40752;
INSERT INTO creature_loot_template VALUES
(31368, 40752, 100, 5, 1, 1, 0, 0, 0);
# Slad'ran 31370
DELETE FROM creature_loot_template WHERE entry=31370 AND item=40752;
INSERT INTO creature_loot_template VALUES
(31370, 40752, 100, 5, 1, 1, 0, 0, 0);



