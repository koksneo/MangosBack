-- Support for quest Master the Storm (11895)

UPDATE quest_template SET StartScript=11895 WHERE entry=11895;

DELETE FROM quest_start_scripts WHERE id=11895;
INSERT INTO quest_start_scripts 
(id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(11895,3,10,26045,45000,3401.71,4134.33,18.0544,5.66716);
