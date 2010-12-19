-- Support for quest  Lightning Definietely Strikes Twice (12537)

DELETE FROM event_scripts WHERE id IN(18475,18474);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2) VALUES 
(18475,0,9,532375,30000),
(18474,1,7,12537,15);

DELETE FROM gameobject WHERE guid=532375;
INSERT INTO gameobject VALUES 
(532375,190502,571,1,1,6206.51,4952.07,-98.9207,0.598737,0,0,0.294917,0.955523,-25,0,1);
