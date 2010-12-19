-- Support for quest Quenching the Blade (10679)

DELETE FROM event_scripts WHERE id=14143;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2) VALUES
(14143,5,9,21611,60),
(14143,5,17,30876,1);
