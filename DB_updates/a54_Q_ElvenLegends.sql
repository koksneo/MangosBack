-- Support for quest Elven Legends (7482/7481)

DELETE FROM gossip_menu WHERE entry=5743;
INSERT INTO gossip_menu (entry,text_id) VALUES
(5743,6919);

DELETE FROM gossip_menu_option WHERE menu_id=5743;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_script_id) VALUES
(5743,1,0,'Mourn the great loss.',1,1,57444);

DELETE FROM gossip_scripts WHERE id=57444;
INSERT INTO gossip_scripts (id,delay,command,datalong,datalong2,dataint) VALUES
(57444,0,7,7482,0,0),
(57444,0,7,7481,0,0);
