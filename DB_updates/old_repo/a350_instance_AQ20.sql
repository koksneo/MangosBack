###############################   Moam    ################################################
DELETE FROM script_texts WHERE entry = -1999796;
INSERT INTO script_texts (`entry`, `content_default`, `type`, `comment`) VALUES
(-1999796, '%s drains your mana and turns to stone.',2,'Moam - casting energize');
UPDATE creature SET curmana = 0 WHERE id = 15340; 
UPDATE creature_template SET minmana = 0 WHERE entry = 15340;

-- mana fiend (summon)
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 15527;
INSERT INTO `creature_ai_scripts` VALUES
('1552701','15527','0','0','100','3','5000','5000','5000','5000','11','25679','0','0','0','0','0','0','0','0','0','0','Mana Fiend - Cast Arcane Explosion'),
('1552702','15527','0','0','100','3','10000','10000','10000','10000','11','15122','4','0','0','0','0','0','0','0','0','0','Mana Fiend - Cast Counterspell');
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 15527;

###############################  general  #################################################

UPDATE creature_template SET dmg_multiplier=26 WHERE entry IN (15348,15340,15341,15339,15369,15370);
