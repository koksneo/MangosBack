# Quest: Emergency Protocol: Section 8.2, Paragraph C (11795)

-- Fizzcrank Pilot (25841)

UPDATE creature_template SET gossip_menu_id=entry, npcflag=npcflag|1 WHERE entry=25841;
UPDATE creature SET Spawntimesecs=240 WHERE id=25841;

DELETE FROM gossip_menu WHERE entry=25841;
INSERT INTO gossip_menu (entry,text_id) VALUES
(25841,12489);

DELETE FROM gossip_menu_option WHERE menu_id=25841;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(25841,1,0,'Search for the pilot\'s insignia.',1,1,0,1248,9,11795,0);

DELETE FROM gossip_scripts WHERE id=1248;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(1248,0,15,46166,2,0),
(1248,0,18,1,0,0);
