-- Quest Our boy wants to be a skyguard ranger (11030)
DELETE FROM gossip_menu WHERE entry=8672;  
INSERT INTO gossip_menu (entry, text_id,cond_1,cond_1_val_1) VALUES  
(8672,0,0,0);

DELETE FROM gossip_menu_option WHERE menu_id=8672;  
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES  
(8672,0,0,'I want to exchange my apexis shards for your mighty flask',1,1,0,8672,0,0); 

DELETE FROM gossip_scripts WHERE id=8672;  
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES 
(8672, 0, 15, 40964, 1, 0); -- spell Fel Crystalforge: Create 1 Flask