-- Support for quest Defiling Uther's Tomb (9444)

-- This quest was bugged for a long time, so I had to use this hotfix ;/
# UPDATE quest_template SET ReqCreatureOrGOId1=-181653 WHERE entry=9444;
UPDATE quest_template SET ReqCreatureOrGOId1 =17253 WHERE entry=9444;

-- Uther's ghost (17233)

UPDATe creature_template SET MovementType=0, AIName='EventAI' WHERE entry=17233;
DELETE FROM creature_ai_scripts WHERE creature_id=17233;
INSERT INTO creature_ai_scripts VALUES
(1723301,17233,1,0,100,0,2000,2000,0,0,1,-172331,0,0,0,0,0,0,0,0,0,0,'Ghost od Uther Lightbringer - Say 1'),
(1723302,17233,1,0,100,0,7000,7000,0,0,1,-172332,0,0,0,0,0,0,0,0,0,0,'Ghost od Uther Lightbringer - Say 2'),
(1723303,17233,1,0,100,0,12000,12000,0,0,1,-172333,0,0,0,0,0,0,0,0,0,0,'Ghost od Uther Lightbringer - Say 3'),
(1723304,17233,1,0,100,0,17000,17000,0,0,1,-172334,0,0,0,0,0,0,0,0,0,0,'Ghost od Uther Lightbringer - Say 4');

DELETE FROM event_scripts WHERE id=10561;
INSERT INTO event_scripts VALUES
(10561,0,10,17233,21000,0,0,0,0,972.67,-1829.82,81.52,1.05),
(10561,0,7,9444,0,0,0,0,0,0,0,0,0),
(10561,0,8,17253,0,0,0,0,0,0,0,0,0);

DELETE FROM creature_ai_texts WHERE entry IN (-172331,-172332,-172333,-172334,-18541);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-172331,'Why do you do this? Did I somehow wrong you in life?',0,'Ghost of Uther Lightbringer say1'),
(-172332,'Ah, I see it now in your mind. This is the work of one of my former students... Mehlar Dawnblade. It is sad to know that his heart has turned so dark.',0,'Ghost of Uther Lightbringer say2'),
(-172333,'Return to him. Return to Mehlor and tell him that I forgive him and that I understand why he believes what he does.',0,'Ghost of Uther Lightbringer say3'),
(-172334,'I can only hope that he will see the Light and instead turn his energies to restoring once-beautiful Quel\'Thalas.',0,'Ghost of Uther Lightbringer say4'),
(-18541,'By the Light you will leave this tomb!',0,'High Priest Thel\'danis say1');

-- High Priest Thel'danis (1854)

UPDATE creature_template SET AIName='EventAI' WHERE entry=1854;
DELETE FROM creature_ai_scripts WHERE creature_id=1854;
INSERT INTO creature_ai_scripts VALUES
(185401,1854,4,0,100,0,0,0,0,0,1,-18541,0,0,11,10951,0,3,0,0,0,0,'High Priest Thel\'danis - Say on Aggro'),
(185402,1854,2,0,100,1,75,1,3000,10000,11,30155,0,1,0,0,0,0,0,0,0,0,'High Priest Thel\'danis - Cast Heal'),
(185403,1854,0,0,100,0,3000,3000,7000,7000,11,15498,1,0,0,0,0,0,0,0,0,0,'High Priest Thel\'danis - Cast Holy Smite');
