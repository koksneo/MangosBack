-- Support for quest Grim(oire) Business (10998)

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=22911;

DELETE FROM creature_ai_scripts WHERE creature_id=22911;
INSERT INTO creature_ai_scripts VALUES
(2291101,22911,6,0,100,1,0,0,0,0,11,39862,0,3,0,0,0,0,0,0,0,0,'Summon Vimgols Vile Grimoire Chest'),
(2291102,22911,0,0,100,0,15000,15000,0,0,11,40545,0,1,0,0,0,0,0,0,0,0,'Vimgols Vile-cast unholy growth');