-- Dying Berserker (Icecrown)
UPDATE creature_template SET
gossip_menu_id = 20005,
regenhealth = 0,
npcflag = npcflag|1
WHERE entry = 31273;

-- Dying Soldier (Icecrown)
UPDATE creature_template SET
gossip_menu_id = 20007,
regenhealth = 0,
npcflag = npcflag|1
WHERE entry = 31304;

-- Dying Berserker (Icecrown)
UPDATE creature SET curhealth = 40 WHERE id = 31273;
-- Dying Soldier (Icecrown)
UPDATE creature SET curhealth = 40 WHERE id = 31304;

DELETE FROM gossip_menu WHERE entry IN (20005,20006,20007,20008);
INSERT INTO gossip_menu (entry,text_id) VALUES
(20005,13930),
(20006,13931),
(20007,13940),
(20008,13947);

DELETE FROM gossip_menu_option WHERE menu_id IN (20005,20007);
INSERT INTO gossip_menu_option (menu_id,id,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES
(20005,0,'Hold on, friend. Tell me what happend here.',1,1,20006,20005,9,13228),
(20007,0,'Stay with me, friend. I must know what happened here',1,1,20008,20006,9,13231);

DELETE FROM gossip_scripts WHERE id IN (20005,20007);
INSERT INTO gossip_scripts (id,command,datalong) VALUES
(20005,8,31272),
(20007,8,31312);
