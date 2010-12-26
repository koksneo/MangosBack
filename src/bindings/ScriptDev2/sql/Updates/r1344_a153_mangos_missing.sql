UPDATE creature_template SET ScriptName = 'mob_parasitic_shadowfiend', AIName = '' WHERE entry = 23498;
UPDATE creature_template SET ScriptName = 'mob_shadowy_construct', AIName = '' WHERE entry = 23111;
UPDATE creature_template SET ScriptName = 'boss_kelthuzad', AIName = '' WHERE entry = 15990;
UPDATE creature_template SET ScriptName = 'boss_moam', AIName = '' WHERE entry = 15340;
UPDATE creature_template SET ScriptName = 'boss_kurinnaxx', AIName = '' WHERE entry = 15348;
UPDATE creature_template SET ScriptName = 'boss_ayamiss', AIName = '' WHERE entry = 15369;
UPDATE creature_template SET ScriptName = 'mob_webwrap', AIName = '' WHERE entry = 16486;

DELETE FROM creature_ai_scripts WHERE creature_id IN (23498,23111,15990,15340,15348,15369,16486);
