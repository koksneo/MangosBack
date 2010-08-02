-- Support for Ayren Cloudbreaker and Unrestrained Dragonhawk (taxi npc in Isle of Queldanas)

-- Ayren Cloudbreaker (25059)
UPDATE creature_template SET gossip_menu_id=entry WHERE entry IN (25059,25236);
DELETE FROM gossip_menu WHERE entry=25059;
INSERT INTO gossip_menu (entry,text_id) VALUES
(25059,12252);

DELETE FROM gossip_menu_option WHERE menu_id=25059;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(25059,1,0,'Speaking of action, I\'ve been ordered to undertake an air strike.',1,1,0,34475,2,34475,1),
(25059,2,0,'I need to intercept the Dawnblade reinforcements.',1,1,0,34489,2,34489,1);

DELETE FROM gossip_scripts WHERE id IN (34475,34489);
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(34475,0,15,45071,2,0),
(34489,0,15,45113,2,0);

-- Unrestrained Dragonhawk (25236)
DELETE FROM gossip_menu WHERE entry=25236;
INSERT INTO gossip_menu (entry,text_id) VALUES
(25236,12371);

DELETE FROM gossip_menu_option WHERE menu_id=25236;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(25236,1,0,'<Ride the dragonhawk to Sun\'s Reach>',1,1,0,25236,0,0,0);

DELETE FROM gossip_scripts WHERE id=25236;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(25236,0,15,45353,2,0);
