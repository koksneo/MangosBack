-- Areatrigger for Etymidian quest chain
DELETE FROM areatrigger_teleport WHERE id ='5046';
INSERT INTO areatrigger_teleport (id, NAME, required_level, required_item, required_item2, heroic_key, heroic_key2, required_quest_done, required_quest_done_heroic, required_failed_text, target_map, target_position_x, target_position_y, target_position_z, target_orientation)VALUES
('5046', 'The_Waygate_Sholazar', '1', '0', '0', '0', '0', '12559', '0', '0', '1', '-6161.8', '-1332.13', '-168.965', '2.35776');

DELETE FROM areatrigger_teleport WHERE id ='5047';
INSERT INTO areatrigger_teleport (id, NAME, required_level, required_item, required_item2, heroic_key, heroic_key2, required_quest_done, required_quest_done_heroic, required_failed_text, target_map, target_position_x, target_position_y, target_position_z, target_orientation)VALUES
('5047', 'The_Waygate_Ungoro', '1', '0', '0', '0', '0', '12559', '0', '0', '571', '4885.993', '5175.694', '-84.863', '0.450570');
