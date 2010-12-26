-- BFD Twilight Lord Kelris
DELETE FROM creature_ai_scripts WHERE creature_id = 4832;
INSERT INTO creature_ai_scripts VALUES
('483201','4832','4','0','100','2','0','0','0','0','1','-566','0','0','0','0','0','0','0','0','0','0','Twilight Lord Kelris - Yell on Aggro'),
('483202','4832','0','0','100','3','2000','5000','7000','9000','11','15587','1','0','0','0','0','0','0','0','0','0','Twilight Lord Kelris - Casts Mind Blast'),
('483203','4832','0','0','100','3','9000','12000','15000','20000','11','8399','5','1','1','-567','0','0','0','0','0','0','Twilight Lord Kelris - Casts Sleep and Yell'),
('483204','4832','6','0','100','2','0','0','0','0','1','-568','0','0','34','10','3','0','0','0','0','0','Twilight Lord Kelris - Yell on Death');

REPLACE INTO creature_ai_texts VALUES
('-568','Just...Dust...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'5803','1','0','0','4832'),
('-567','Sleep...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'5804','1','0','0','4832'),
('-566','Who dares disturb my meditation!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'5802','1','0','0','4832');

UPDATE creature_template SET ScriptName = '', AIName = 'EventAI' WHERE entry = 4832;
-- Shrines (GO)
UPDATE gameobject_template SET ScriptName = 'go_shrine' WHERE entry IN (21118,21119,21120,21121);
