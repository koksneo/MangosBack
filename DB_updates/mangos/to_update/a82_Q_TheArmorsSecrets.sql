-- Support for quest The Armor's Secrets (12980)

DELETE FROM creature WHERE id = 30190;
INSERT INTO creature VALUES 
(12040778,30190,571,1,1,0,0,8238.95,-428.464,970.724,5.26145,300,5,0,1,0,0,0);

UPDATE creature_template SET 
gossip_menu_id=30190,
minlevel=78,
maxlevel=79,
minhealth=11770,
maxhealth=12175,
minmana=3809,
maxmana=3893,
npcflag=npcflag|1
WHERE entry=30190;

DELETE from gossip_menu WHERE entry=30190;
INSERT into gossip_menu VALUES
(30190,0,9,12980,0,0,0,0);

DELETE FROM gossip_menu_option WHERE menu_id=30190;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id)VALUES
(30190,1,0,'Could you examine my Dark Armor, please ?',1,1,0,30190);

DELETE from gossip_scripts WHERE id=30190;
INSERT into gossip_scripts (id,delay,command,datalong,datalong2,datalong3,datalong4,data_flags,dataint) VALUES
(30190,1,0,0,30190,15,0,0x02,2000008000),
(30190,4,0,0,30190,15,0,0x02,2000008001),
(30190,9,0,0,30190,15,0,0x02,2000008002),
(30190,13,0,0,30190,15,0,0x02,2000008003),
(30190,17,0,0,30190,15,0,0x02,2000008004),
(30190,20,0,0,30190,15,0,0x02,2000008005),
(30190,24,0,0,30190,15,0,0x02,2000008006),
(30190,28,0,0,30190,15,0,0x02,2000008007),
(30190,32,0,0,30190,15,0,0x02,2000008008),
(30190,36,0,0,30190,15,0,0x02,2000008009),
(30190,36,8,30190,0,0,0,0,0);


DELETE FROM db_script_string WHERE entry BETWEEN 2000008002 AND 2000008011;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000008002,'Metallic specimen of foreign origin detected.'),
(2000008003,'Beginning analysis ...'),
(2000008004,'Specimen identified as an alloy of saronite and iron.'),
(2000008005,'The ore used in this sample originated deep within the crust of Azeroth and was recently unearthed.'),
(2000008006,'The saronite in this sample is nearly pure. Ores like this do not occur naturally on the surface of Azeroth.'),
(2000008007,'This ore can only have been created by a powerful, malevolent force. Attempting to access databanks for more information ...'),
(2000008008,'Access denied?'),
(2000008009,'Further information can only be accessed from the archives within Ulduar, by order of Keeper Loken.'),
(2000008010,'But one thing is for certain: this plate\'s size, thickness, and bolt holes point to a use as armor for a colossal structure.'),
(2000008011,'Directive completed. Returning to standby mode.');
