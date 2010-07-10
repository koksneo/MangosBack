-- Optional SQLs:
-- correcting DB bugs posted in UDB forums
UPDATE creature_template SET InhabitType = 4 WHERE entry = 22424;
UPDATE creature SET MovementType = 4 WHERE id = 22424;
DELETE FROM creature WHERE id = 18533;

-- Luanga the Imprisoner ACID
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 18533;
INSERT INTO `creature_ai_scripts` VALUES
(1853301,18533,4,0,100,0, 0,0,0,0, 11,32924,1,1, 1,-98989,0,0, 39,20,0,0,"Luanga the Imprisoner - Mekthorg the Wild - Power of Kran\'aish"),
(1853302,18533,0,0,80,1, 5000,5000,30000,30000, 11,32907,1,0, 0,0,0,0, 0,0,0,0,'Luanga the Imprisoner - Arakkoa Blast'),
(1853303,18533,0,0,80,1, 7000,7000,7000,7000, 11,12058,1,0, 0,0,0,0, 0,0,0,0,'Luanga the Imprisoner - Chain Lightning'),
(1853304,18533,0,0,80,1, 12000,12000,25000,25000, 11,12058,5,0 ,0,0,0,0, 0,0,0,0,'Luanga the Imprisoner - Lightning Cloud'),
(1853305,18533,0,0,80,1, 9000,9000,5000,5000, 11,11824,1,0, 0,0,0,0, 0,0,0,0,'Luanga the Imprisoner - Shock');

DELETE FROM creature_ai_texts WHERE entry IN (-98989);
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-98989,"Skywing! I will free you from your curse over my dead body!",1,'Luanga the Imprisoner - aggro');
