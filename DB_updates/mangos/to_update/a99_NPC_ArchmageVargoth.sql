# Gossip support for npc Archmage Vargoth. Related with  achievement "Higher Learning"

UPDATE creature_template SET gossip_menu_id=entry WHERE entry=19481;

DELETE FROM gossip_menu WHERE entry IN (19481,19482);
INSERT INTO gossip_menu (entry,text_id) VALUES
(19481,14192),
(19482,14194);

DELETE FROM gossip_menu_option WHERE menu_id IN (19481,19482);
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2,cond_3,cond_3_val_1,cond_3_val_2) VALUES
(19481,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0,0,0,0),
(19481,1,0,'I have book that might interest you. Would you like to have a look?',1,1,19482,0,2,43824,1,20,1956,0,17,61472,1),
(19482,1,0,'Thank You! I will be sure to notify you if I find anything else.',1,1,0,1948,2,43824,1,20,1956,0,17,61472,1);

DELETE FROM gossip_scripts WHERE id=1948;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(1948,0,17,44738,1,0);
