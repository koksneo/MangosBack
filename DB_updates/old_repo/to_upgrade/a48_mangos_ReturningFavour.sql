-- Warmaul Ogre Credit Marker
DELETE FROM spell_script_target WHERE entry = 32314;
INSERT INTO spell_script_target VALUES (32314,1,18393);

DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (18393);
INSERT INTO `creature_ai_scripts` VALUES
(1839301,18393, 8,0,100,0, 32314,0,0,0, 37,0,0,0, 0,0,0,0, 0,0,0,0,'Warmaul Ogre Credit Marker - forced despawn after quest credit');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (18393,17138,18064);


-- Warmaul Ogre NPCs
INSERT INTO `creature_ai_scripts` (`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(17138, 6,0,100,0, 0,0,0,0, 12,18393,0,60000, 0,0,0,0, 0,0,0,0,'Warmaul Ogre Reaver - summon Warmaul Ogre Credit Marker'),
(18064, 6,0,100,0, 0,0,0,0, 12,18393,0,60000, 0,0,0,0, 0,0,0,0,'Warmaul Ogre Shaman - summon Warmaul Ogre Credit Marker'); 