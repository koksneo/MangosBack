-- Support for quest Defiling Uther's Tomb (9444)

-- This quest was bugged for a long time, so I had to use this hotfix ;/
# UPDATE quest_template SET ReqCreatureOrGOId1=-181653 WHERE entry=9444;
UPDATE quest_template SET ReqCreatureOrGOId1 =17253 WHERE entry=9444;

-- Uther's ghost (17233)

UPDATE creature_template SET MovementType=0 WHERE entry=17233;

DELETE FROM event_scripts WHERE id=10561;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,data_flags,dataint,x,y,z,o) VALUES
(10561,0,10,17233,21000,0,0,972.67,-1829.82,81.52,1.05),
(10561,0,7,9444,0,0,0,0,0,0,0),
(10561,0,8,17253,0,0,0,0,0,0,0),
-- Text
(10561,3,0,17233,30,0x04,2000000200,0,0,0,0),
(10561,7,0,17233,30,0x04,2000000201,0,0,0,0),
(10561,12,0,17233,30,0x04,2000000202,0,0,0,0),
(10561,17,0,17233,30,0x04,2000000203,0,0,0,0);

DELETE FROM db_script_string WHERE entry IN (2000000200,2000000201,2000000202,2000000203);
INSERT INTO db_script_string (entry,content_default) VALUES
(2000000200,'Why do you do this? Did I somehow wrong you in life?'),
(2000000201,'Ah, I see it now in your mind. This is the work of one of my former students... Mehlar Dawnblade. It is sad to know that his heart has turned so dark.'),
(2000000202,'Return to him. Return to Mehlor and tell him that I forgive him and that I understand why he believes what he does.'),
(2000000203,'I can only hope that he will see the Light and instead turn his energies to restoring once-beautiful Quel\'Thalas.');

DELETE FROM creature_ai_texts WHERE entry=-18541;
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-18541,'By the Light you will leave this tomb!',0,'High Priest Thel\'danis say1');

-- High Priest Thel'danis (1854)

UPDATE creature_template SET AIName='EventAI' WHERE entry=1854;
DELETE FROM creature_ai_scripts WHERE creature_id=1854;
INSERT INTO creature_ai_scripts VALUES
(185401,1854,4,0,100,0,0,0,0,0,1,-18541,0,0,11,10951,0,3,0,0,0,0,'High Priest Thel\'danis - Say on Aggro'),
(185402,1854,2,0,100,1,75,1,3000,10000,11,30155,0,1,0,0,0,0,0,0,0,0,'High Priest Thel\'danis - Cast Heal'),
(185403,1854,0,0,100,0,3000,3000,7000,7000,11,15498,1,0,0,0,0,0,0,0,0,0,'High Priest Thel\'danis - Cast Holy Smite');
