-- BFD shrine event summons should decrease internal instance_script counter while dying
DELETE FROM creature_ai_scripts WHERE creature_id IN (4977,4825,4978,4823) AND event_type = 6;
INSERT INTO creature_ai_scripts 
(`id`,`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('497702','4977','6','0','100','2', '0','0','0','0', '34','4','4','0','0','0','0','0','0','0','0','0','MOB_MURKSHALLOW_SOFTSHELL - Just Died'),
('482502','4825','6','0','100','2', '0','0','0','0', '34','4','4','0','0','0','0','0','0','0','0','0','MOB_AKUMAI_SNAPJAW - Just Died'),
('497803','4978','6','0','100','2', '0','0','0','0', '34','4','4','0','0','0','0','0','0','0','0','0','MOB_AKUMAI_SERVANT - Just Died'),
('482302','4823','6','0','100','2', '0','0','0','0', '34','4','4','0','0','0','0','0','0','0','0','0','MOB_BARBED_CRUSTACEAN - Just Died');
-- Twilight Lord Kelris 
REPLACE INTO `creature_ai_scripts` VALUES
('483204','4832', '6','0','100','2', '0','0','0','0', '1','-568','0','0', '34','10','3','0','0','0','0','0','Twilight Lord Kelris - Yell on Death');
