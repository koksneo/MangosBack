-- Support for quest An Innocent Disguise (11891)

UPDATE creature_template SET AIName='EventAI' WHERE entry IN (25949,25951);

-- Text
DELETE FROM creature_ai_texts WHERE entry IN (-259491,-259492,-259493,-259511,-259512);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-259491,'These stones should be the last of them. Our coordination with Neptulon\'s forces will be impeccable.',0,'Ice Caller Briatha say 1'),
(-259492,'And your own preparations? Will the Frost Lord have a path to the portal?',0,'Ice Caller Briatha say 2'),
(-259493,'The ritual in coilfang will bring Ahune through once he is fully prepared, and the resulting clash between Firelord and Frostlord will rend the foundations of this world. Our ultimate goals are in reach at last...',0,'Ice Caller Briatha say 3'),
(-259511,'Yess. The Tidehunter will be pleased at this development. The Firelord\'s hold will weaken.',0,'Heretic Emissary say 1'),
(-259512,'Skar\'this has informed us well. We have worked our way into the slave pens and await your cryomancerss.',0,'Heretic Emissary say 2');

-- Add spawn place
DELETE FROM creature_ai_summons WHERE id=25949;
INSERT INTO creature_ai_summons VALUES
(25949,4194.78,1170.19,6.98884,1.14791,27000,'Ice Caller Briatha - Midsummer Fire Festival');

-- Ice Caller Briatha (25949)
DELETE FROM creature_ai_scripts WHERE creature_id=25949;
INSERT INTO creature_ai_scripts VALUES
(2594901,25949,1,0,100,0,1000,1000,0,0,1,-259491,0,0,0,0,0,0,0,0,0,0,'Ice Caller Briatha say 1'),
(2594902,25949,1,0,100,0,12000,12000,0,0,1,-259492,0,0,0,0,0,0,0,0,0,0,'Ice Caller Briatha say 2'),
(2594903,25949,1,0,100,0,24000,24000,0,0,1,-259493,0,0,26,11891,0,0,0,0,0,0,'Ice Caller Briatha say 3'),
(2594904,25949,10,0,100,1,1,10,24000,24000,15,11891,6,0,0,0,0,0,0,0,0,0,'Ice Caller Briatha say 3');

-- Heretic Emissary (25951) ~24 sek.
DELETE FROM creature_ai_scripts WHERE creature_id=25951;
INSERT INTO creature_ai_scripts VALUES
(2595101,25951,11,0,100,1,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Heretic Emissary Set Phase 1 on Spawn'),
(2595102,25951,10,1,100,1,1,10,1000,1000,22,2,0,0,0,0,0,0,0,0,0,0,'Heretic Emissary Set Phase 2 on unit range'),
(2595103,25951,10,2,100,1,1,10,35000,35000,32,25949,0,25949,0,0,0,0,0,0,0,0,'Heretic Emissary Summon Ice Caller Briatha'),
(2595104,25951,1,2,100,0,6000,6000,0,0,1,-259511,0,0,0,0,0,0,0,0,0,0,'Heretic Emissary say 1'),
(2595105,25951,1,2,100,0,18000,18000,0,0,1,-259512,0,0,22,0,0,0,0,0,0,0,'Heretic Emissary say 2');
