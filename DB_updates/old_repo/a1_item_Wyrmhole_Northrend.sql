DELETE FROM spell_target_position WHERE id IN (67834,67835,67836,67837,67838,68081);
INSERT INTO spell_target_position VALUES
-- Borean Tundra - high above lake Kum'uya (player is falling after teleport, z coord unknown)
(67834, 571, 3172.33, 5608.70, 595.01, 1.18),
-- Sholazar Basin - at the top of Glimmering Pillar
(67835, 571, 6234.36, 4766.68, 224.71, 4.23),
-- Icecrown - on the mountain side
(67836, 571, 8113.86, 1352.32, 848.87, 0.26),
-- Storm Peaks - nearby Ulduar meeting stone
(67837, 571, 8992.79, -1222.29, 1058.40, 2.87),
-- Howling Fjord - a the top of Utgrade Keep
(67838, 571, 1180.55, -4876.56, 408.80, 0.43),
-- Underground (under Horde section of Dalaran)
(68081, 571, 5859.29, 516.25, 599.81, 3.15);

-- Wormhole (portal creature)
UPDATE creature_template SET 
npcflag = npcflag|1,
gossip_menu_id = 35646
WHERE entry = 35646;

DELETE FROM gossip_menu WHERE entry = 35646;
INSERT INTO gossip_menu VALUES
(35646,14785,0,0,0,0,0,0);

DELETE FROM gossip_menu_option WHERE menu_id = 35646;
INSERT INTO gossip_menu_option VALUES
(35646, 0, 0, 'Borean Tundra', 1, 1, 0, 0, 100, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0),
(35646, 1, 0, 'Howling Fjord', 1, 1, 0, 0, 101, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0),
(35646, 2, 0, 'Sholazar Basin', 1, 1, 0, 0, 102, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0),
(35646, 3, 0, 'Icecrown', 1, 1, 0, 0, 103, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0),
(35646, 4, 0, 'Storm Peaks', 1, 1, 0, 0, 104, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0),
(35646, 5, 0, 'Underground...', 1, 1, 0, 0, 105, 0, 0, NULL, 2,48933,1, 7,202,415, 0,0,0);

DELETE FROM gossip_scripts WHERE id IN (100,101,102,103,104,105);
INSERT INTO gossip_scripts (id,delay,command,datalong) VALUES
(100, 0, 15, 67834),
(101, 0, 15, 67838),
(102, 0, 15, 67835),
(103, 0, 15, 67836),
(104, 0, 15, 67837),
(105, 0, 15, 68081);
