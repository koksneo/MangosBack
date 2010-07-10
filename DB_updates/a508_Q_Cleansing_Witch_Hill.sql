-- Support for quest Cleansing Witch Hill (11183)

-- Zelfrax (23864)
-- Npc should be attackable after spawn
UPDATE creature_template SET unit_flags=0, AIName='EventAI' WHERE entry=23864;
-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-238641,-238642);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-238641,'This land was mine long before your wretched kind set foot here.',1,'Zelfrax yell on spawn'),
(-238642,'All who venture here belong to me, including you!',1,'Zelfrax yell combat');
-- EventAI
DELETE FROM creature_ai_scripts WHERE creature_id=23864;
INSERT INTO creature_ai_scripts VALUES
(2386401,23864,11,0,100,0,0,0,0,0,1,-238641,0,0,0,0,0,0,0,0,0,0,'Zelfrax yell on spawn'),
(2386402,23864,4,0,100,0,0,0,0,0,1,-238642,0,0,0,0,0,0,0,0,0,0,'Zelfrax yell combat');
