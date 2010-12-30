-- Quest: Journey to Undercity (9180)

UPDATE creature_template SET
modelid_1=11686
WHERE entry=21641;

UPDATE creature_template SET AIName='EventAI' WHERE entry=39048;
DELETE FROM creature_ai_scripts WHERE creature_id=39048;
INSERT into creature_ai_scripts VALUES
(3904801,39048,1,0,100,0,18000,18000,18000,18000,36,21628,0,0,0,0,0,0,0,0,0,0,'Sylvanas\' Lamenter- Update template to (21628)');

UPDATE quest_template SET CompleteScript=entry WHERE entry=9180;

DELETE FROM db_script_string WHERE entry=2000003000;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000003000,'%s looks down at the discarded necklace. In her sandess the lady incants a glamour, which beckons forth Highborne spirits. The chamber resonates with their ancient song about the Sin\'dorei...');

DELETE FROM quest_end_scripts WHERE id=9180;
INSERT INTO quest_end_scripts (id,delay,command,datalong,datalong2,datalong3,datalong4,data_flags,dataint,x,y,z,o) VALUES
(9180,0,15,36568,0,0,0,0,0,0,0,0,0),
(9180,0,0,2,10181,50,0,0x04,2000003000,0,0,0,0),
(9180,8,10,21641,18000,0,0,0,0,1296.11,310.007,-58.837,2.38355),
(9180,8,10,21641,18000,0,0,0,0,1284.25,319.589,-57.684,0.863689),
(9180,8,10,21641,18000,0,0,0,0,1284.13,308.994,-60.083,1.10803);

UPDATE creature_template SET modelid_1=28213 WHERE entry=10181;
UPDATE creature SET modelid=28213 WHERE id=10181;

-- Ambassador Sunsorrow (16287)
DELETE FROM gossip_menu WHERE entry=7179;
INSERT INTO gossip_menu (entry,text_id) VALUES
(7179,10378);

DELETE FROM gossip_menu_option WHERE menu_id=7178;
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,action_menu_id,action_script_id,cond_1,cond_1_val_1,cond_1_val_2,cond_2,cond_2_val_1,cond_2_val_2) VALUES
(7178,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,0,0,0),
(7178,1,0,'What is it that you have for me, ambassador?',1,1,7179,7179,16,30632,1,8,9180,0);

DELETE FROM gossip_scripts WHERE id=7179;
INSERT INTO gossip_scripts (id, delay, command, datalong, datalong2, dataint) VALUES
(7179,0,17,30632,1,0);