
DELETE FROM `script_texts` WHERE `entry` IN (-1999000, -1999001,-1999002);
INSERT INTO `script_texts` (`entry`, `content_default`,`comment`,`type`) VALUES
(-1999000, "My life for you!",'npc saronite mine slave',1),
(-1999001, "NO ! You're wrong! The voices in my head are beatiful",'npc saronite mine slave',1),
(-1999002, "I must get further underground where he is! I must jump!",'npc saronite mine slave',1);
