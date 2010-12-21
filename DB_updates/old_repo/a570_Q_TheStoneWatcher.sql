-- Spawn is static, no need to summon by Script
UPDATE quest_template SET CompleteScript = 0 WHERE entry IN (2946,2966);
DELETE FROM quest_end_scripts WHERE id IN (2946,2966);

-- The Stone Watcher (Uldum Pedestal as q giver)
DELETE FROM creature_questrelation WHERE quest = 2954;
DELETE FROM gameobject_questrelation WHERE quest = 2954;
INSERT INTO gameobject_questrelation VALUES
(142343,2954);

UPDATE creature_template SET gossip_menu_id = 20003 WHERE entry = 7918;
DELETE FROM gossip_menu_option WHERE menu_id BETWEEN 20003 AND 20008;
INSERT INTO gossip_menu_option VALUES
(20003,0,0,'What function do you serve?',1,1,20004,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20004,0,0,'What are the Plates of Uldum?',1,1,20005,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20005,0,0,'Where are the plates of Uldum?',1,1,20006,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20006,0,0,'Excuse me? We\'ve been "rescheduled for visitation? What does that mean?',1,1,20007,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20007,0,0,'So...what\'s inside Uldum?',1,1,20008,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20008,0,0,'I will return when I have the plates of Uldum.?',1,1,0,0,20008,0,0,NULL, 0,0,0, 0,0,0, 0,0,0);

DELETE FROM gossip_menu WHERE entry BETWEEN 20003 AND 20008;
INSERT INTO gossip_menu (entry,text_id) VALUES
(20003,1674),
(20004,1675),
(20005,1676),
(20006,1677),
(20007,1678),
(20008,1679);

DELETE FROM gossip_scripts WHERE id = 20008;
INSERT INTO gossip_scripts (id,delay,command,datalong) VALUES
(20008,0,7,2954);

-- Spawn is static, no need to summon by Script
UPDATE quest_template SET CompleteScript = 0 WHERE entry IN (2946,2966);
DELETE FROM quest_end_scripts WHERE id IN (2946,2966);

-- The Stone Watcher (Uldum Pedestal as q giver)
DELETE FROM creature_questrelation WHERE quest = 2954;
DELETE FROM gameobject_questrelation WHERE quest = 2954;
INSERT INTO gameobject_questrelation VALUES
(142343,2954);

UPDATE creature_template SET gossip_menu_id = 20003 WHERE entry = 7918;
DELETE FROM gossip_menu_option WHERE menu_id BETWEEN 20003 AND 20008;
INSERT INTO gossip_menu_option VALUES
(20003,0,0,'What function do you serve?',1,1,20004,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20004,0,0,'What are the Plates of Uldum?',1,1,20005,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20005,0,0,'Where are the plates of Uldum?',1,1,20006,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20006,0,0,'Excuse me? We\'ve been "rescheduled for visitation? What does that mean?',1,1,20007,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20007,0,0,'So...what\'s inside Uldum?',1,1,20008,0,0,0,0,NULL, 0,0,0, 0,0,0, 0,0,0),
(20008,0,0,'I will return when I have the plates of Uldum.?',1,1,0,0,20008,0,0,NULL, 0,0,0, 0,0,0, 0,0,0);

DELETE FROM gossip_menu WHERE entry BETWEEN 20003 AND 20008;
INSERT INTO gossip_menu (entry,text_id) VALUES
(20003,1674),
(20004,1675),
(20005,1676),
(20006,1677),
(20007,1678),
(20008,1679);

DELETE FROM gossip_scripts WHERE id = 20008;
INSERT INTO gossip_scripts (id,delay,command,datalong) VALUES
(20008,0,7,2954);

DELETE FROM creature WHERE id = 7918;
INSERT INTO `creature` VALUES
('9000030','7918','1','1','1','0','0','-9619.24','-2815.13','10.8955','1.54408','25','5','0','6900','0','0','0');
