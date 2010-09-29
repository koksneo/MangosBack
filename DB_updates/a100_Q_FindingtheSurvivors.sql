-- Quest: Finding the Survivors (9948)

UPDATE gameobject_template SET ScriptName='go_warmaul_prison' WHERE entry=182493;

UPDATE creature_template SET AIName='EventAI' WHERE entry=18428;

DELETE FROM creature_ai_scripts WHERE creature_id=18428;
INSERT INTO creature_ai_scripts VALUES
(1842801,18428,10,0,100,1,1,5,15000,15000,1,-184281,-184282,-184283,0,0,0,0,0,0,0,0,'Mag\'har Prisoner - Say');

DELETE FROM creature_ai_texts WHERE entry IN (-184281,-184282,-184283);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-184283,'My Children will be made orphans!',1,'Mag\'har Prisoner Say3'),
(-184282,'Help! Help! They''re going to eat me!',1,'Mag\'har Prisoner Say2'),
(-184281,'The ogres have the keys! Kill the ogres and get me out of here!',1,'Mag\'har Prisoner Say1');
