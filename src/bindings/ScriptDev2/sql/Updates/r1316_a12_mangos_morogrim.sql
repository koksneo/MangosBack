-- Tidwalker Lurker (summon)
DELETE FROM creature_ai_scripts WHERE creature_id = 21920;

UPDATE creature_template SET ainame = '', scriptname = 'mob_tidewalker_lurker' WHERE entry = 21920;
