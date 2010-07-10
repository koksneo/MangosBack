-- Support for quest Recharging the Batteries (10190)

-- Spell (34219)
-- Text
DELETE FROM creature_ai_texts WHERE entry=-188791;
INSERT INTO creature_ai_texts VALUES
(-188791,'Phase Hunter is very weak',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,2,0,0,'Phase hunter Text Emote');

-- Phase Hunter (18879) add phase 2
DELETE FROM creature_ai_scripts WHERE id IN (1887904,1887905,1887906);
INSERT INTO creature_ai_scripts VALUES
(1887904,18879,2,0,100,0,30,0,0,0,1,-188791,0,0,22,1,0,0,0,0,0,0,'Phase Hunter - Phase 2 at 30% HP'),

-- Update template after spell hit. Phase Hunter (18879) -> Drained Phase Hunter (19595)
(1887905,18879,8,1,100,0,34219,-1,0,0,36,19595,0,0,0,0,0,0,0,0,0,0,'Phase Hunter - Update template after spell hit');
