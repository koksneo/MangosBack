-- Support for quest Survey Alcaz Island (11142)

-- Cassa Crimsonwing (23704)

UPDATE creature_template SET gossip_menu_id=entry, ScriptName='' WHERE entry=23704;

-- Missing text for gossip menu
DELETE FROM gossip_menu WHERE entry=23704;
INSERT INTO gossip_menu (entry,text_id) VALUES
(23704,1);

DELETE FROM gossip_menu_option WHERE menu_id=23704;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(23704,1,0,'<Ride the gryphons to Survey Alcaz Island>',1,1,0,23704,9,11142,0);

DELETE FROM gossip_scripts WHERE id=23704;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(23704,0,15,42295,2,0),
(23704,127,15,42316,2,0);
