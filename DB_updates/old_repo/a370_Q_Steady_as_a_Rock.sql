-- Object: Portable Seismograph
DELETE FROM gameobject WHERE id = 188367;
INSERT INTO gameobject VALUES (400000,188367,571,3,1,5065.13,-4814.98,222.059,2.57356,0,0,0.959937,0.280215,-25,0,1);
DELETE FROM event_scripts WHERE id='17566';
INSERT INTO event_scripts (id,delay,command,datalong,datalong2) VALUES
(17566,0,9,400000,25);