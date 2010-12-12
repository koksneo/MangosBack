##The Conquest Pit: Bear Wrestling!##

DELETE FROM quest_start_scripts WHERE id= 12427;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, X, Y, z, o)VALUES
('12427', '1', '10', '27715', '250000', '0', '0', '0', '0', '3246.94', '-2340.55', '91.960', '1.057');

UPDATE creature_template SET minlevel=74,maxlevel=74,minhealth=102820,maxhealth=102820,faction_A=14,faction_H=14,mindmg=350,maxdmg=590 WHERE entry =27715;

UPDATE quest_template SET StartScript= 12427 WHERE entry =12427;

DELETE FROM creature_ai_scripts WHERE id=2771504;
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2771504', '27715', '6', '0', '100', '0', '0', '0', '0', '0', '26', '12427', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Kill-Credit on Kill');

##The Conquest Pit: Mad Furbolg Fighting##


DELETE FROM quest_start_scripts WHERE id= 12428;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, X, Y, z, o)VALUES
('12428', '1', '10', '27716', '250000', '0', '0', '0', '0', '3246.94', '-2340.55', '91.960', '1.057');

UPDATE quest_template SET StartScript= 12428 WHERE entry =12428;

DELETE FROM creature_ai_scripts WHERE id=2771613;
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2771613', '27716', '6', '0', '100', '0', '0', '0', '0', '0', '26', '12428', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Kill-Credit on Kill');


##The Conquest Pit: Blood and Metal##

DELETE FROM quest_start_scripts WHERE id= 12429;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, X, Y, z, o)VALUES
('12429', '1', '10', '27717', '250000', '0', '0', '0', '0', '3246.94', '-2340.55', '91.960', '1.057');

UPDATE quest_template SET StartScript= 12429 WHERE entry =12429;

DELETE FROM creature_ai_scripts WHERE id=2771713;
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2771713', '27717', '6', '0', '100', '0', '0', '0', '0', '0', '26', '12429', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Kill-Credit on Kill');

UPDATE creature_template SET minlevel=75,maxlevel=75,minmana=3561,maxmana=3561,minhealth=127620,maxhealth=127620,faction_A=14,faction_H=14,mindmg=350,maxdmg=550 WHERE entry =27717;


##The Conquest Pit: Death Is Likely##

DELETE FROM quest_start_scripts WHERE id= 12430;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, X, Y, z, o)VALUES
('12430', '1', '10', '27718', '250000', '0', '0', '0', '0', '3246.94', '-2340.55', '91.960', '1.057');

UPDATE quest_template SET StartScript= 12430 WHERE entry =12430;

DELETE FROM creature_ai_scripts WHERE id IN(2771805,2771806);
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2771805', '27718', '0', '0', '100', '1', '13000', '15000', '10000', '15000', '11', '58460', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Horgrenn Hellcleave - Cast Brutal Strike'),
('2771806', '27718', '6', '0', '100', '0', '0', '0', '0', '0', '26', '12430', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Kill-Credit on Kill');

UPDATE creature_template SET minlevel=75,maxlevel=75,equipment_id=764,minhealth=159525,maxhealth=159525,faction_A=14,faction_H=14,mindmg=450,maxdmg=600 WHERE entry =27718;


##The Conquest Pit: Final Showdown##

DELETE FROM quest_start_scripts WHERE id= 12431;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, X, Y, z, o)VALUES
('12431', '1', '10', '27727', '250000', '0', '0', '0', '0', '3246.94', '-2340.55', '91.960', '1.057');

UPDATE quest_template SET StartScript= 12431 WHERE entry =12431;

DELETE FROM creature_ai_scripts WHERE id=2772705;
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2772705', '27727', '6', '0', '100', '0', '0', '0', '0', '0', '26', '12431', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Kill-Credit on Kill');

UPDATE creature_template SET minlevel=76,maxlevel=76,minhealth=95620,maxhealth=95620,faction_A=14,faction_H=14,mindmg=450,maxdmg=600 WHERE entry =27727;
