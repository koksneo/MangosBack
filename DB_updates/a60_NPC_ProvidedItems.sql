-- Support for NPCs, who can give quest item again

UPDATE creature_template SET gossip_menu_id=entry WHERE entry IN (28518,19217,22127,26117);

## Stefan Vadu (28518)

DELETE FROM gossip_menu WHERE entry IN (28518,28517);
INSERT INTO gossip_menu (entry,text_id) VALUES
(28518,13270),
(28517,13501);

DELETE FROM gossip_menu_option WHERE menu_id=28518;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2) VALUES
(28518,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0),
(28518,1,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12713,0),
(28518,2,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12676,0),
(28518,3,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12677,0),
(28518,4,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12669,0),
(28518,5,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12661,0),
(28518,6,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12649,0),
(28518,7,0,'I\'ve lost my ensorcelled choker!',1,1,28517,2851,16,38699,1,9,12648,0);

DELETE FROM gossip_scripts WHERE id=2851;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(2851,0,17,38699,1,0);

## Ravandwyr (19217)

DELETE FROM gossip_menu WHERE entry=19217;
INSERT INTO gossip_menu (entry,text_id) VALUES
(19217,9828); 

DELETE FROM gossip_menu_option WHERE menu_id=19217;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2) VALUES
(19217,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0),
(19217,1,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10174,0),
(19217,2,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10188,0),
(19217,3,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10192,0),
(19217,4,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10301,0),
(19217,5,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10209,0),
(19217,6,0,'I\'ve lost Archmage Vargoth\'s Staff. Can you replace it?',1,1,0,2845,16,28455,1,9,10176,0);

DELETE FROM gossip_scripts WHERE id=2845;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(2845,0,17,28455,1,0);

## Wildlord Antelarion (22127)

DELETE FROM gossip_menu WHERE entry=22127;
INSERT INTO gossip_menu (entry,text_id) VALUES
(22127,10657); 

DELETE FROM gossip_menu_option WHERE menu_id=22127;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2) VALUES
(22127,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0),
(22127,1,0,'The Felsworn Gas Mask was destroyed, do you have another one?',1,1,0,3136,16,31366,1,9,10819,0), 
(22127,2,0,'The Felsworn Gas Mask was destroyed, do you have another one?',1,1,0,3136,16,31366,1,9,10820,0),
(22127,3,0,'The Felsworn Gas Mask was destroyed, do you have another one?',1,1,0,3136,16,31366,1,9,10821,0);

DELETE FROM gossip_scripts WHERE id=3136;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(3136,0,17,31366,1,0);

## Raelorasz (26117)

DELETE FROM gossip_menu WHERE entry IN (26117,26118);
INSERT INTO gossip_menu (entry,text_id) VALUES
(26117,12566), 
(26118,12568);

DELETE FROM gossip_menu_option WHERE menu_id=26117;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2) VALUES
(26117,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0), 
(26117,1,0,'What is the cause of this conflict?',1,1,9283,0,0,0,0,0,0,0),
(26117,2,0,'I seem to have lost the Augmeted Arcane Prison. Did I leave it here with you?',1,1,26118,3567,16,35671,1,9,11951,0),
(26117,3,0,'I seem to have lost the Augmeted Arcane Prison. Did I leave it here with you?',1,1,26118,3567,16,35671,1,9,11946,0), 
(26117,4,0,'I seem to have lost the Augmeted Arcane Prison. Did I leave it here with you?',1,1,26118,3567,16,35671,1,9,11967,0), 
(26117,5,0,'I seem to have lost the Augmeted Arcane Prison. Did I leave it here with you?',1,1,26118,3567,16,35671,1,9,11957,0);

DELETE FROM gossip_scripts WHERE id=3567;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(3567,0,17,35671,1,0);
