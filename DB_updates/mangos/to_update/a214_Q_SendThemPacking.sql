-- Quest Send Them Packing (11224)
UPDATE `creature_template` SET AIName='EventAI' WHERE entry= 23977;

DELETE FROM creature_ai_scripts WHERE creature_id = 23977;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`,`event_flags`, `event_param1`,`event_param2` ,`event_param3`,`event_param4` , `action1_type`, `action1_param1`, `action1_param2`,`action1_param3`,`action2_type`, `action2_param1`,`comment`) VALUES 
(2397701, 23977, 22, 0 , 125, 9 , 11224 , 0 , 11, 42721, 6, 4 , 41 , 2 ,'Abandoned Mule - Cast Spell Kill Credit after /raise ');
