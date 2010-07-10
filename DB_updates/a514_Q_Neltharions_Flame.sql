-- Support for quest Neltharion's Flame (12267)

DELETE FROM creature WHERE id=27450;
INSERT INTO creature VALUES
(2745001,27450,571,1,1,13069,0,4402.5,1863.74,158.629,3.27125,25,0,0,42,0,0,0),
(2745002,27450,571,1,1,13069,0,4399.82,1851.77,158.437,3.0427,25,0,0,42,0,0,0),
(101156,27450,571,1,1,13069,0,4412.9,1875.54,158.839,2.1552,25,0,0,42,0,0,0);

DELETE FROM spell_script_target WHERE entry=48790;
INSERT INTO spell_script_target VALUES
(48790,1,27450);

DELETE FROM spell_scripts WHERE id=48790;
INSERT INTO spell_scripts
(id,delay,command,datalong,datalong2,datalong3,data_flags,dataint) VALUES
(48790,0,8,27450,1,0,0,0);

DELETE FROM event_scripts WHERE id=18248;
INSERT INTO event_scripts
(id,delay,command,datalong,datalong2,datalong3,data_flags,dataint) VALUES
(18248,1,0,1,27355,50,0x02,2000008000),
(18248,4,0,1,27355,50,0x02,2000008001);

-- Texts for event_scripts
DELETE FROM db_script_string WHERE entry IN (2000008000,2000008001);
INSERT INTO db_script_string (entry,content_default) VALUES
(2000008000,'No... NO! What have you done?! So many ancient wyrms wasted... what magic could do this?'),
(2000008001,'Foolish errand $N... you will die for interrupting my work!');

-- Texts
DELETE FROM creature_ai_texts WHERE entry IN (-273551,-273552);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-273551,'You are a black wyrm no longer. Go... Go and serve the Scourge.',1,'Rothin the Decayin yell on aggro'),
(-273552,'This is not the end... death only... strengthens...',1,'Rothin the Decayin yell on death');

DELETE FROM creature_ai_scripts WHERE id IN (2735512,2735513);
INSERT INTO creature_ai_scripts VALUES
(2735512,27355,1,0,100,0,15000,15000,15000,15000,1,-273551,0,0,0,0,0,0,0,0,0,0,'Rothin the Decaying - Yell OOC'),
(2735513,27355,6,0,100,0,0,0,0,0,1,-273552,0,0,0,0,0,0,0,0,0,0,'Rothin the Decayin - Yell on Death');
