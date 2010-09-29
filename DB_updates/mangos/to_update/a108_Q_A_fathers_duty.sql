-- Quest A father's duty (11061)
DELETE FROM gossip_menu WHERE entry=8677;  
INSERT INTO gossip_menu (entry, text_id,cond_1,cond_1_val_1) VALUES  
(8677,0,0,0);

DELETE FROM gossip_menu_option WHERE menu_id=8677;  
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES  
(8677,0,0,'I want to exchange my apexis shards for your mighty flask',1,1,0,8677,0,0); 

DELETE FROM gossip_scripts WHERE id=8677;  
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES 
(8677, 0, 15, 40968, 1, 0); -- spell Bash'ir Crystalforge: Create 1 Flask
