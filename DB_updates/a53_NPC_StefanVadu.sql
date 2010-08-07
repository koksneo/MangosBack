-- Stefan Vadu (28518)
UPDATE creature_template SET gossip_menu_id=entry WHERE entry=28518;

DELETE FROM gossip_menu WHERE entry IN (28518,28517);
INSERT INTO gossip_menu (entry,text_id) VALUES
(28518,13270),
(28517,13501);

-- no item 38699, not completed quest 12713
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
