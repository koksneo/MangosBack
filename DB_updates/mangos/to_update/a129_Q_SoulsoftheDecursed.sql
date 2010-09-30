# Quest: Souls of the Decursed (11899) 

DELETE FROM creature_ai_scripts WHERE creature_id=25814;
INSERT INTO creature_ai_scripts VALUES
(2581401,25814,4,0,5,0,0,0,0,0,1,-533,-534,-535,0,0,0,0,0,0,0,0,'Fizzcrank Mechagnome - Chance Say on Aggro'),
(2581402,25814,8,0,100,0,46485,-1,0,0,33,26096,6,0,0,0,0,0,0,0,0,0,'Fizzcrank Mechagnome - Soul Quest Credit ');

UPDATE creature_template SET unit_flags=unit_flags|33554432 WHERE entry=26096;
