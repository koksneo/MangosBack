-- Support for quest Stunning Defeat at the Ring (11300) by Grandres

-- Val'kyrs flying addon
DELETE FROM creature_addon WHERE guid IN (114183,114190,114191,114192);
DELETE FROM creature_addon WHERE guid BETWEEN 115488 AND 115499;
INSERT INTO creature_addon (guid,bytes1,b2_1_pvp_state,emote) VALUES
(115488,0,50331649,1),
(115489,0,50331649,1),
(115490,0,50331649,1),
(115491,0,50331649,1),
(115492,0,50331649,1),
(115493,0,50331649,1),
(115494,0,50331649,1),
(115495,0,50331649,1),
(115496,0,50331649,1),
(115497,0,50331649,1),
(115498,0,50331649,1),
(115499,0,50331649,1),
(114183,0,50331649,1),
(114190,0,50331649,1),
(114191,0,50331649,1),
(114192,0,50331649,1);

-- Daegarn say OOC
UPDATE creature_template SET AIName='EventAI' WHERE entry=24151;
DELETE FROM creature_ai_scripts WHERE creature_id=24151;
INSERT INTO creature_ai_scripts VALUES
(2415101,24151,1,0,70,1,38000,38000,48000,68000,1,-241511,-241512,0,0,0,0,0,0,0,0,0,'Daegarn say OOC'),
(2415102,24151,1,0,55,1,78000,78000,78000,78000,1,-241513,0,0,0,0,0,0,0,0,0,0,'Daegarn say OOC');

-- Texts
DELETE FROM creature_ai_texts WHERE entry IN (-241511,-241512,-241513,-242131,-242151,-242141,-239311,-239312);
INSERT INTO creature_ai_texts (entry,content_default,type,comment)  VALUES
(-241511,'What did you do with the people of this village!?',0,'Common Daegarn text'),
(-241512,'What do you want with me?',0,'Common Daegarn text'),
(-241513,'Release me, cowards! I\'ll show you what a dwarf is made of!',0,'Common Daegarn text'),
(-242131,'Firjus fears nothing! Release the combatants!',1,'Firjus the Soul Crusher yell'),
(-242151,'Firjus was unworthy! Test your battle prowess against a true soldier of the Lich King!',1,'Jlarborn the Strategist yell'),
(-242141,'Good... More flesh for the harvest...',1,'Yorus the Flesh Harvester yell'),
(-239311,'The ring will overflow with the blood of the interlopers! Oluf has come!',1,'Oluf the Violent yell'),
(-239312,'The ancient cipher falls on the ground.',3,'Oluf the Violent notify');

-- Add spawn place
DELETE FROM creature_ai_summons WHERE id=11300;
INSERT INTO creature_ai_summons VALUES
(11300,846.877,-4688.59,-94.1835,3.47087,300000,'24213-24215-24214');

######################################
# 1st Firjus the Soul Crusher (24213)#
######################################

-- Add spell Head Crush (43348) and Cleave (15284)
DELETE FROM creature_ai_scripts WHERE id IN (2421301,2421302,2421303,2421304,2421305);
INSERT INTO creature_ai_scripts VALUES
(2421301,24213,4,0,100,0,0,0,0,0,1,-242131,0,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Yell on Aggro'), 
(2421302,24213,0,0,100,1,3000,5000,5000,7000,11,15284,1,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Cleave'), 
(2421303,24213,0,0,75,1,5000,8000,8000,14000,11,43348,1,1,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Head Crush'), 

-- Summon on death
(2421305,24213,6,0,100,0,0,0,0,0,32,24215,6,11300,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Summon Jlarborn the Strategist on Death');
UPDATE creature_template SET AIName='EventAI' where entry=24213;

######################################
# 2nd Jlarborn the Strategist (24215)#
######################################

-- Add spell Arcing Smash (8374), Shield Bash (38233), Shield Block (12169), Shield Charge (15749)
DELETE FROM creature_ai_scripts WHERE id IN (2421501,2421502,2421503,2421504,2421505,2421506);
INSERT INTO creature_ai_scripts VALUES
(2421501,24215,4,0,100,0,0,0,0,0,1,-242151,0,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Yell on Aggro'),
(2421502,24215,9,0,100,1,8,25,20000,25000,11,15749,1,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Shield Charge'), 
(2421503,24215,0,0,75,1,2000,2000,6000,6000,11,8374,1,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Arcing Smash'), 
(2421504,24215,13,0,75,1,1000,6000,0,0,11,38233,1,1,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Shield Bash'), 
(2421505,24215,0,0,100,1,7000,11000,11000,18000,11,15284,0,0,0,0,0,0,0,0,0,0,'Firjus the Soul Crusher - Cast Shield Block'), 

-- Summon on death
(2421506,24215,6,0,100,0,0,0,0,0,32,24214,6,11300,0,0,0,0,0,0,0,0,'Jlarborn the Strategist - Summon Yorus the Flesh Harvester on Death');
UPDATE creature_template SET AIName='EventAI' WHERE entry=24215;

########################################
# 3rd Yorus the Flesh Harvester (24214)#
########################################

-- Add spell Cleave (15284) and Whirlwind (41056)
DELETE FROM creature_ai_scripts WHERE id IN(2421401,2421402,2421403,2421404);
INSERT INTO creature_ai_scripts VALUES
(2421401,24214,4,0,100,0,0,0,0,0,1,-242141,0,0,0,0,0,0,0,0,0,0,'Yorus the Flesh Harvester - Yell on Aggro'),
(2421402,24214,0,0,100,1,3000,5000,5000,7000,11,15284,1,0,0,0,0,0,0,0,0,0,'Yorus the Flesh Harvester - Cast Cleave'),
(2421403,24214,0,0,100,1,15000,15000,30000,30000,11,41056,0,1,0,0,0,0,0,0,0,0,'Yorus the Flesh Harvester - Cast Whirlwind'),

-- Summon on death
(2421404,24214,6,0,100,0,0,0,0,0,32,23931,6,11300,0,0,0,0,0,0,0,0,'Yorus the Flesh Harvester - Summon Oluf the Violent on Death');
UPDATE creature_template SET AIName='EventAI' WHERE entry=24214;

###############################
# 4th Oluf the Violent (23931)#
###############################

-- Add spell Cleave (15284), Demoralizing Shout (13730), Whirlwind (41056), Net (6533), Throw Dragonflayer Harpoon (42870)
DELETE FROM creature_ai_scripts WHERE id IN(2393101,2393102,2393103,2393104,2393105,2393106,2393107);
INSERT INTO `creature_ai_scripts` VALUES
(2393101,23931,4,0,100,0,0,0,0,0,1,-239311,0,0,0,0,0,0,0,0,0,0,'Oluf the Violent - Yell on Aggro'),
(2393102,23931,0,0,100,1,3000,5000,5000,7000,11,15284,1,0,0,0,0,0,0,0,0,0,'Oluf the Violent - Cast Cleave'),
(2393103,23931,0,0,100,1,4000,4000,17200,25200,11,13730,0,1,0,0,0,0,0,0,0,0,'Oluf the Violent - Cast Demoralizing Shout'),
(2393104,23931,0,0,100,1,15000,15000,30000,30000,11,41056,0,1,0,0,0,0,0,0,0,0,'Oluf the Violent - Cast Whirlwind'),
(2393105,23931,9,0,100,1,10,20,1000,1000,11,6533,1,0,0,0,0,0,0,0,0,0,'Oluf the Violent - Cast Net'),
(2393106,23931,9,0,100,1,15,30,2000,2000,11,42870,1,1,0,0,0,0,0,0,0,0,'Oluf the Violent - Cast Throw Dragonflayer Harpoon'),

-- Drop Ancient Cipher (43326)
(2393107,23931,6,0,100,0,0,0,0,0,11,43326,0,3,1,-239312,0,0,0,0,0,0,'Oluf the Violent - Spawn Ancient Cipher and Notify on Death');
UPDATE creature_template SET AIName='EventAI' WHERE entry=23931;
