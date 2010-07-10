-- Support for quest The Bear God's Offspring (12231) and Children of Ursoc (12247)

UPDATE creature_template SET gossip_menu_id=entry,npcflag=npcflag|1 WHERE entry IN (27274,27275);

# Orsonn's Story (27274) 27322

DELETE FROM gossip_menu WHERE entry IN (27274,27322,27323);
INSERT INTO gossip_menu (entry,text_id) VALUES
(27274,12793),
(27322,12794),
(27323,12796);

DELETE FROM gossip_menu_option WHERE menu_id IN (27274,27322,27323);
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES
(27274,1,0,'You\'re free to go Orsonn, but first tell me what\'s wrong with the furbolg.',1,1,27322,0,0,0),
(27322,1,0,'What happened then?',1,1,27323,0,0,0),
(27323,1,0,'Thank you, Son of Ursoc. I\'ll see what can be done.',1,1,0,27274,0,0);

-- Quest credit
DELETE FROM gossip_scripts WHERE id=27274;
INSERT INTO gossip_scripts (id,delay,command,datalong,datalong2) VALUES
(27274,0,8,27322,0);

# Kodian's Story (27275) 27321

DELETE FROM gossip_menu WHERE entry IN (27275,27321);
INSERT INTO gossip_menu (entry,text_id) VALUES
(27275,12797),
(27321,12798);

DELETE FROM gossip_menu_option WHERE menu_id IN (27275,27321);
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES
(27275,1,0,'Who was this stranger?',1,1,27321,0,0,0),
(27321,1,0,'Thank you, Kodian. I\'ll do what I can.',1,1,0,27275,0,0);

-- Quest credit
DELETE FROM gossip_scripts WHERE id=27275;
INSERT INTO gossip_scripts (id,delay,command,datalong,datalong2) VALUES
(27275,0,8,27321,0);
