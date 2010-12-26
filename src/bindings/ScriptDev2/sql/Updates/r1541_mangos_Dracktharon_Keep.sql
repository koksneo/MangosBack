UPDATE gameobject_template SET ScriptName = '' WHERE entry IN (189299,189300,189301,189302);
UPDATE creature_template SET ScriptName = 'npc_novos_summon_target' WHERE entry = 27583;
UPDATE instance_template SET script = 'instance_draktharon_keep' WHERE map = 600;
