-- Shadow Council Credit Marker
DELETE FROM spell_script_target WHERE entry = 32307;
INSERT INTO spell_script_target VALUES (32307,1,18388);

DELETE  FROM creature WHERE id = 18388;

DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (18388);
INSERT INTO `creature_ai_scripts` VALUES
(1838801,18388, 8,0,100,0, 32307,0,0,0, 37,0,0,0, 0,0,0,0, 0,0,0,0,'Shadow Council Credit Marker - forced despawn after quest credit');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 18388;


-- Kill'Sorrow NPCs
INSERT INTO `creature_ai_scripts` (`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(17148, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Deathsworn - summon Shadow Council Credit Marker'),
(17146, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Spellbinder - summon Shadow Council Credit Marker'),
(17147, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Cultist - summon Shadow Council Credit Marker'),
(18397, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Invader - summon Shadow Council Credit Marker'),
(18658, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Ritualist - summon Shadow Council Credit Marker'),
(21276, 6,0,100,0, 0,0,0,0, 12,18388,0,60000, 0,0,0,0, 0,0,0,0,'Kil\'sorrow Agent - summon Shadow Council Credit Marker');