-- Support for quest The End of the Line (12107)

-- Acid support for triggers

UPDATE creature_template SET 
AIName='EventAI',
modelid_1=11686,
modelid_2=11686
WHERE entry IN (26889,26887);

DELETE FROM creature_ai_scripts WHERE creature_id IN (26889,26887);
INSERT INTO creature_ai_scripts VALUES
(2688901,26889,10,0,100,1,1,5,1000,1000,33,26889,6,0,0,0,0,0,0,0,0,0,'The End of the Line  - Area Credit at LOS'),
(2688701,26887,8,0,100,1,47634,-1,0,0,16,26887,50548,6,0,0,0,0,0,0,0,0,'The End of the Line: Ley Line Focus Bunny Beam on Ley Line Focus Control Talisman Spellhit');

-- Add into world missing triggers
DELETE FROM creature WHERE id=26887;
INSERT INTO creature VALUES
(2688701,26887,571,1,1,0,0,3070,1399.14,122.714,0.957148,25,0,0,1,0,0,0),
(2688702,26887,571,1,1,0,0,3045.74,1400.18,121.801,2.22478,25,0,0,1,0,0,0);



