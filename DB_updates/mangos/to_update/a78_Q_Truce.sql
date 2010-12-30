-- Support for quest Truce?

-- add gossip to Drakuru
UPDATE creature_template SET
gossip_menu_id=26423
WHERE entry=26423;

DELETE FROM gossip_menu WHERE entry=26423;  
INSERT INTO gossip_menu (entry, text_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES  
(26423,12998,1,50001,0);

DELETE FROM gossip_menu_option WHERE menu_id=26423;  
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES 
(26423,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0),  
(26423,1,0,'Shake Drakuru\'s outstretched hand.',1,1,0,26423,1,50001,0);

DELETE FROM gossip_scripts WHERE id=26423 ;  
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES 
(26423,0,8,27921,0,0);

DELETE FROM spell_scripts WHERE id=50001;
INSERT INTO spell_scripts (id,delay,command,datalong,datalong2,datalong3,datalong4,data_flags,dataint) VALUES
(50001,0,0,1,0,0,0,0x01,2000007013);

DELETE FROM db_script_string WHERE entry=2000007013;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000007013,'AYYYIEEE!!');
