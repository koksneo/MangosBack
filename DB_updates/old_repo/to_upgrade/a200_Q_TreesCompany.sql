-- (new) Engineer "Spark" Overgrind 
REPLACE INTO `creature_template` VALUES 
('40001','0','0','0','16934','0','16934','0','Engineer \"Spark\" Overgrind','Envoy of Mekkatorque',NULL,'9','9','166','166','178','178','369','875','875','1','1.125','1','0','11','15','0','34','1','2000','0','2','36864','0','0','0','0','0','0','7','11','100','7','0','17243','0','0','0','0','0','0','0','0','7978','0','0','0','0','0','0','','1','3','1','1','0','23899','0','0','0','0','1','32','0','2','');

-- (new) Engineer "Spark" Overgrind (40001)|| Geezle(40001)
DELETE FROM creature WHERE id IN (40001,17243);
UPDATE creature_template SET 
AIName = 'EventAI',
ScriptName = ''
WHERE entry IN (40001,17243);

DELETE FROM creature_ai_scripts WHERE creature_id IN (40001,17243);
INSERT INTO creature_ai_scripts VALUES
(1724301,17243, 1,0,100,0, 2000,2000,0,0, 1,-99922,0,0, 0,0,0,0, 0,0,0,0 ,'Engineer "Spark" Overgrind - emote flag'),
(4000101,40001, 1,0,100,0, 3000,3000,0,0, 1,-99921,0,0, 0,0,0,0, 0,0,0,0 ,'Geezle - speech (What\'s the big idea, Spark...)'),
(1724302,17243, 1,0,100,0, 8000,8000,0,0, 1,-99920,0,0, 0,0,0,0, 0,0,0,0 ,'Engineer "Spark" Overgrind - speech (What\'s the big idea? You nearly...)'),
(1724303,17243, 1,0,100,0, 15000,15000,0,0, 1,-99919,0,0, 0,0,0,0, 0,0,0,0 ,'Engineer "Spark" Overgrind - speech (The Master has gone to great lengths...)'),
(4000102,40001, 1,0,100,0, 15000,15000,0,0, 1,-99918,0,0, 0,0,0,0, 0,0,0,0 ,'Geezle - speech (Relax, Spark! I have it all...)'),
(1724304,17243, 1,0,100,0, 21000,21000,0,0, 1,-99917,0,0, 0,0,0,0, 0,0,0,0 ,'Engineer "Spark" Overgrind - speech (Relax? Do you know what Kael...)'),
(1724305,17243, 1,0,100,0, 30000,30000,0,0, 1,-99916,0,0, 0,0,0,0, 0,0,0,0 ,'Engineer "Spark" Overgrind - speech (Our Bloodmyst scouts must have...)'),
(4000103,40001, 1,0,100,0, 30000,30000,0,0, 1,-99915,0,0, 0,0,0,0, 0,0,0,0 ,'Geezle - speech (Relax, Spark! I have it all...)');


-- Engineer "Spark" Overgrind (17243)|| Geezle(40001)
DELETE FROM creature_ai_texts WHERE COMMENT IN (40001,17243);
INSERT INTO creature_ai_texts (entry, content_default,`type`,emote,`comment`) VALUES
(-99922,'picks up the naga flag.',2,69,17243), -- work emote 
(-99921,'What\'s the big idea, Spark? Why\'d you call for this meeting?',0,6,40001), -- question emote 
(-99920,'What\'s the big idea? You nearly blew my cover, idiot! I told you to put the compass and navigation maps somewhere safe - not out in the open for any fool to discover.',1,5,17243), -- exclamation emote 
(-99919,'The Master has gone to great lengths to secure information about the whereabouts of the Exodar. You could have blown the entire operation, including the cover of our spy on the inside. ',0,0,17243),
(-99918,'Relax, Spark! I have it all under control. We\'ll strip mine the Exodar right out from under \'em - making both you and I very, very rich in the process.',0,11,40001), -- laugh emote 
(-99917,'Relax? Do you know what Kael\'thas does to those that fail him, Geezle? Eternal suffering and pain... Do NOT screw this up, fool! ',1,5,17243),
(-99916,'Our Bloodmyst scouts must have located our contact. The fool, Velen, will soon LEAVE himself OPEN AND defenseless -- long enough for us to strike! Now get out of my sight before I vaporize you... ',0,0,17243),
(-99915,'Yes, sir. It won\'t happen again... ',1,66,40001); -- laugh emote 

DELETE FROM event_scripts WHERE id = 10675;
INSERT INTO event_scripts VALUES
(10675, 0, 10, 17243, 37000, 0, -5082,-11252,0.61, 3.35),
(10675, 3, 10, 40001, 34000, 0, -5087,-11253,0.55, 6.27),
(10675, 30, 7, 9531, 30, 0, 0,0,0,0);

UPDATE quest_template SET 
reqcreatureorgoid1 = 0,
reqcreatureorgocount1 = 0, 
questflags = questflags|2,
specialflags = 2
WHERE entry = 9531;