-- Support for quest Finish me! (13232)

-- Dying Soldier gossip
UPDATE creature_template SET gossip_menu_id=31304 WHERE entry=31304;

DELETE FROM gossip_menu WHERE entry=31304;
INSERT INTO gossip_menu (entry,text_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(31304,14035,9,13232,0);

DELETE FROM gossip_menu_option WHERE menu_id=31304;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES
(31304,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0),
(31304,1,0,'Travel well, hero of the Alliance!',1,1,0,31341,9,13232);				

DELETE FROM gossip_scripts WHERE id=31341;
INSERT INTO gossip_scripts (id,delay,command,datalong,datalong2) VALUES
(31341,0,18,2,0),
(31341,0,8,31312,0);
