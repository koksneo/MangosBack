-- support for q Crocolisk Mastery Ambush(12569)

DELETE from event_scripts WHERE id=18503;
INSERT into event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(18503,3,10,28317,60000,5442.93,4882.75,-198.528,1.43);
