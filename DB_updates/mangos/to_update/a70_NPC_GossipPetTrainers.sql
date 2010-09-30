-- Pet trainers. Gossip options

UPDATE creature_template SET gossip_menu_id=4783, npcflag=npcflag|1|16 WHERE entry IN(10090,3698,17484,4320,3545,16712,3622,16675,3620,10086,2879,3306,40405,543,2878,3688,10089,16271,10088,3624);

-- questrelation/involvedrelation
UPDATE creature_template SET npcflag=npcflag|2 WHERE entry IN (10090,16712,16675,16271,3624);

-- Gossip options
DELETE FROM gossip_menu_option WHERE menu_id=4783;
INSERT INTO gossip_menu_option VALUES
(4783,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4783,1,2,'I wish to unlearn my pet\'s skills.',17,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0);
