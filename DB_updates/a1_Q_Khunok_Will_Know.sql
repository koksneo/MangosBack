-- Khu'nok Will Know  
UPDATE quest_template SET startscript = 11878 WHERE entry = 11878;  
-- Khu'nok Will Know (cast spell Call Mammoth Orphan)  
DELETE FROM quest_start_scripts WHERE id = 11878;  
INSERT INTO quest_start_scripts (id, delay, command, datalong) VALUES  
(11878,0,15,46232);  
   
-- Call Mammoth Orphan  
DELETE FROM spell_target_position WHERE id = 46233;  
INSERT INTO spell_target_position VALUES  
(46233,571,3192.96 ,5275.45 ,48.13,0.51);  