-- Support for quest Who are They? (10040/10041)

-- Private Weeks (18715)
UPDATE creature_template SET gossip_menu_id=entry WHERE entry IN (18715,18716,18717,18719);

DELETE FROM gossip_menu WHERE entry=18715;
INSERT INTO gossip_menu (entry,text_id) VALUES
(18715,9517);

DELETE FROM gossip_menu_option WHERE menu_id=18715;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(18715,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0),
(18715,1,0,'Private Weeks, I need another disguise.',1,1,18751,18715,0,0,0);

DELETE FROM gossip_scripts WHERE id=18715;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(18715,0,15,32756,2,0);

-- Shadowy Initiate (18716)
REPLACE INTO gossip_menu (entry,text_id) VALUES
(18716,9502),
(1871,9503);

DELETE FROM gossip_menu_option WHERE menu_id=18716;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(18716,0,0,'What are you doing there?',1,1,1871,1876,0,0,0);

DELETE FROM gossip_scripts WHERE id=1876;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(1876,0,8,26464,0,0);

-- Shadowy Laborer (18717)
REPLACE INTO gossip_menu (entry,text_id) VALUES
(18717,9497),
(18771,9498);

DELETE FROM gossip_menu_option WHERE menu_id=18717;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(18717,0,0,'Why are you fixing all of this up?',1,1,18771,18717,0,0,0);

DELETE FROM gossip_scripts WHERE id=18717;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(18717,0,8,26465,0,0);

-- Shadowy Advisor (18719)
REPLACE INTO gossip_menu (entry,text_id) VALUES
(18719,9505),
(18791,9506);

DELETE FROM gossip_menu_option WHERE menu_id=18719;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(18719,0,0,'Advisor, what\'s the latest news?',1,1,18791,18719,0,0,0);

DELETE FROM gossip_scripts WHERE id=18716;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(18719,0,8,26466,0,0);
