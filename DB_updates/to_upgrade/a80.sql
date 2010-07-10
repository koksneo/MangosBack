-- chain zaczynajacy sie od Q: http://www.wowhead.com/?quest=11573
-- 1. Orfus of Kamagua
-- 2. The Dead Rise!
-- 3. Elder Atuik and Kamagua
-- 4. Grezzix Spindlesnap
-- 5. Street "Cred"
-- 6. "Scoodles"
DELETE FROM `creature` WHERE id = 25233;
INSERT INTO `creature` 
VALUES('9000002','25233','571','1','1','0','0','1229.18','-3349.16','203.639','3.6438','25','0','0','9291','0','0','0');
 
DELETE FROM creature_addon WHERE guid = 9000002;
INSERT INTO creature_addon VALUES
(9000002,0,1,0,0,0,NULL);

DELETE FROM spell_area WHERE spell = 44017;
INSERT INTO spell_area VALUES
(44017,3990,11507,1,0,0,0,2,1),
(44017,3990,11508,1,0,0,0,2,1),
(44017,3990,11509,1,0,0,0,2,1),
(44017,3990,11510,1,0,0,0,2,1);
