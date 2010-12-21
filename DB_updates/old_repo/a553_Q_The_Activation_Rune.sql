-- Support for quest The Activation Rune (12547)

-- High Cultist Herenn (28601)

UPDATE creature_template SET 
AIName='EventAI',
minlevel=78,
maxlevel=78,
minhealth=11770,
maxhealth=11770,
minmana=3809,
maxmana=3809,
armor=9124,
faction_A=2080,
faction_H=2080,
mindmg=190,
maxdmg=270,
dmg_multiplier=2,
attackpower=528,
lootid=28601
WHERE entry=28601;

-- Add into world
DELETE FROM creature WHERE id=28601;
INSERT INTO creature VALUES
(2860101,28601,1,1,1,0,0,-6029.01,-1249.18,-146.821,3.06789,300,0,0,11770,3809,0,0);

-- Loot
DELETE FROM creature_loot_template WHERE entry=28601;
INSERT INTO creature_loot_template VALUES
(28601,26001,100,1,-26001,1,0,0,0),		-- gray stuff
(28601,30000,100,2,-30000,1,0,0,0),		-- consumable & gray stuff
(28601,38708,-100,0,1,1,0,0,0);			-- Omega Rune (quest item)

-- Say on aggro
DELETE FROM creature_ai_texts WHERE entry=-286011;
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-286011,'Fool! You led us to the only being that could stand up to our armies! You will never bring the Etymidian back to Northrend!',0,'High Cultist Herenn combat say');

DELETE FROM creature_ai_scripts WHERE creature_id=28601;
INSERT INTO creature_ai_scripts VALUES
(2860101,28601,4,0,100,0,0,0,0,0,1,-286011,0,0,0,0,0,0,0,0,0,0,'High Cultist Herenn - Say on Aggro');
