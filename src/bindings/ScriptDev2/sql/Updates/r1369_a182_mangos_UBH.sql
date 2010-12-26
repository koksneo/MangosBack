-- The Black Stalker
UPDATE creature_template SET ScriptName = 'boss_black_stalker', AIName = '', minmana = 33000, maxmana = 33000 WHERE entry = 17882;
-- Spore Strider
UPDATE creature_template SET ScriptName = 'mob_spore_strider', AIName = '', minmana = 6000, maxmana = 6000 WHERE entry = 22299;
-- Spore Strider (heroic)
UPDATE creature_template SET minmana  = 6000, maxmana = 6000 WHERE entry = 22300;
-- SporeStrider/BlackStalker ACID
DELETE FROM creature_ai_scripts WHERE creature_id IN (22299,17882);

UPDATE instance_template SET script = 'instance_underbog' WHERE map = 546;
