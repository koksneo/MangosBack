-- NPC Adventourus Dwarf(28604)

UPDATE creature_template SET
minlevel=75,
maxlevel=75,
minhealth=10635,
maxhealth=10635,
minmana=3561,
maxmana=3561,
mindmg=364,
maxdmg=460,
gossip_menu_id=28604,
ScriptName='',
npcflag=npcflag |1
WHERE entry=28604;

DELETE FROM gossip_menu WHERE entry=28604;  
INSERT INTO gossip_menu (entry, text_id,cond_1,cond_1_val_1) VALUES  
(28604,0,9,12634);

DELETE FROM gossip_menu_option WHERE menu_id=28604;  
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1) VALUES  
(28604,0,0,'Got a spare bunch of bananas?',1,1,0,28604,0,0), 
(28604,1,0,'Do you wanna some papayas?',1,1,0,28605,0,0),   
(28604,2,0,'Do you wanna some orange?',1,1,0,28606,0,0); 

DELETE FROM gossip_scripts WHERE id BETWEEN 28604 AND 28606 ;  
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES 
(28604, 0, 15, 52074, 2, 0), -- spell dwarf gives bananas(52074)
(28604, 2, 18, 20,0,0),
(28605, 0, 15, 52076, 2, 0), -- spell dwarf gives papayas(52076)  
(28605, 2, 18, 20,0,0),
(28606, 2, 18, 20,0,0),
(28606, 0, 15, 52073, 2, 0); -- spell dwarf gives orange(52073)
