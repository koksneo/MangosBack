-- Support for quest Trust is Earned (11460)

-- Rock Falcon gossip
UPDATE creature_template SET gossip_menu_id=44363 WHERE entry=24752;

DELETE FROM gossip_menu WHERE entry=44363;
INSERT INTO gossip_menu VALUES
(44363,12168,9,11460,0,0,0,0);

DELETE FROM gossip_scripts WHERE id=44363;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(44363,0,15,44363,2,0);

DELETE FROM gossip_menu_option WHERE menu_id=44363;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(44363,0,0,'<Feed the grub to the rock falcon>',1,1,0,44363,2,34102,1);
