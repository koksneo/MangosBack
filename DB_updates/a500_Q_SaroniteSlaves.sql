UPDATE creature_template SET
ScriptName = 'mob_mine_slave',
AIName = 'EventAI'
WHERE entry=31397;

UPDATE creature SET
spawntimesecs = 300
WHERE id = 31397;

DELETE FROM creature_ai_scripts WHERE creature_id = 31397;
INSERT INTO creature_ai_scripts VALUES
(3139701,31397,11,0,100,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,'Saronite Mine Slave- Set correct faction at spawn'),
(3139704,31397,7,0,100,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,'Saronite Mine Slave- Set correct faction on evade'),
(3139702,31397,0,0,100,1,100,100,15000,15000,11,3148,1,0,0,0,0,0,0,0,0,0,'Saronite Mine Slave- Cast head crack'),
(3139703,31397,0,0,100,0,10,10,0,0,11,8599,0,1,0,0,0,0,0,0,0,0,'Saronite Mine Slave- Cast enrage when the combat starts');

DELETE FROM `script_texts` WHERE `entry` IN (-1999000, -1999001,-1999002);
INSERT INTO `script_texts` (`entry`, `content_default`,`comment`,`type`) VALUES
(-1999000, "My life for you!",'npc saronite mine slave',1),
(-1999001, "NO ! You're wrong! The voices in my head are beatiful",'npc saronite mine slave',1),
(-1999002, "I must get further underground where he is! I must jump!",'npc saronite mine slave',1);
