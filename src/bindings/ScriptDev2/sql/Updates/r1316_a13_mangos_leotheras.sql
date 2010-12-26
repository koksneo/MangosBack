UPDATE creature_template SET AIName = '', ScriptName = 'mob_greyheart_spellbinder' WHERE entry = 21806;
UPDATE creature_template SET AIName = '', ScriptName = 'mob_inner_demon' WHERE entry = 21857;
UPDATE creature_template SET AIName = '', ScriptName = 'boss_leotheras_the_blind_demonform' WHERE entry = 21875;
UPDATE creature_template SET AIName = '', ScriptName = 'boss_leotheras_the_blind' WHERE entry = 21215;

DELETE FROM creature_ai_scripts WHERE creature_id IN (21806,21857,21875,21215);



