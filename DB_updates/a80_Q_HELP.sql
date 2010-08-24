-- Support for quest HELP! (9923)

UPDATE gameobject_template SET ScriptName='go_corkis_prison', data2=3000 WHERE entry=182349;

DELETE FROM creature WHERE guid=65849;
INSERT INTO creature VALUES
(65849,18369,530,1,1,0,0,-2563.89,6288.29,15.295,5.23599,300,0,0,25000,0,0,0);

DELETE FROM creature_questrelation WHERE id=18369;
INSERT INTO creature_questrelation VALUES
(18369,9923),
(18369,9924);

DELETE FROM creature_involvedrelation WHERE id=18369;
INSERT INTO creature_involvedrelation VALUES
(18369,9954);

UPDATE creature_template SET AIName='EventAI' WHERE entry=18369;

DELETE FROM creature_ai_scripts WHERE creature_id=18369;
INSERT INTO creature_ai_scripts VALUES
(1836901,18369,10,0,100,1,1,20,15000,35000,1,-183691,0,0,0,0,0,0,0,0,0,0,'Corki - Say');

DELETE FROM creature_ai_texts WHERE entry=-183691;
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-183691,'I want my daddy!',0,'Corki Say1');
