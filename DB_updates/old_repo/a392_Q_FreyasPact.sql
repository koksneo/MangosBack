-- support for quest Freya's Pact(12621)

UPDATE creature_template SET gossip_menu_id=27801, ScriptName='' WHERE entry=27801; 

DELETE FROM gossip_menu WHERE entry BETWEEN 27801 AND 27803;  
INSERT INTO gossip_menu (entry, text_id,cond_1,cond_1_val_1) VALUES  
(27801,13303,9,12621),  
(27802,13304,0,0),  
(27803,13305,0,0);
   
   
DELETE FROM gossip_menu_option WHERE menu_id BETWEEN 27801 AND 27803;  
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES  
(27801,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0), 
(27801,1,0,'I want to stop the Scourge as much as you do. How can I help?',1,1,27802,0,9,12621),  
(27802,1,0,'You can trust me. I am no friend of the Lich King\'s.',1,1,27803,0,0,0),  
(27803,1,0,'I will not fail.',1,1,0,27801,0,0);  

-- spell Freya Conversation credit (52045) will be casted after clicking last gossip_option

DELETE FROM gossip_scripts WHERE id=27801;  
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES 
(27801, 0, 15, 52045, 1, 0);
