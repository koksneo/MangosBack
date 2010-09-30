##################################   boss broggok   ##########################################################################
-- Cell door lever
DELETE FROM gameobject WHERE id = 181982;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('200120','181982','542','3','1','457.571','59.8315','9.61514','3.08808','0','0','0.999642','0.0267514','86400','0','1');

UPDATE gameobject_template SET ScriptName = 'go_cell_door_lever' WHERE entry = 181982;

-- Nascent Fel Orc
DELETE FROM `creature_ai_scripts` WHERE id = 1739803;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('1739803','17398','6','0','100','6','0','0','0','0','34','7','1','0','35','14','6','0','0','0','0','0','Fel Orc - broggok intro in progress & store killer guid');
