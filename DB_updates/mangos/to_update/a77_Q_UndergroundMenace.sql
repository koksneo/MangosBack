-- Quest Underground Menace

UPDATE creature_template SET
unit_flags=unit_flags &~33554432 
WHERE entry=28083;

DELETE from creature_ai_scripts WHERE creature_id=28083;
INSERT INTO creature_ai_scripts VALUES 
(2808301,28083,0,0,100,1,1000,1000,5000,5000,11,31747,1,1,0,0,0,0,0,0,0,0,'Serfex-cast poison'),
(2808302,28083,11,0,100,0,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Serfex-stop combat movement');
