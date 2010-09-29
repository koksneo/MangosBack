-- Support for quest Frostmaw (1136)

UPDATE gameobject_template SET displayid=1287 WHERE entry=19876;

DELETE FROM gameobject WHERE id=19876;
INSERT INTO gameobject VALUES
(761747,19876,0,1,1,263.339,-267.679,145.015,5.88296,0,0,0.198777,-0.980045,25,0,1);
