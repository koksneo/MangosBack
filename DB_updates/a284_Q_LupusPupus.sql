-- Wolf Bait (35121) - item
DELETE FROM item_required_target WHERE entry = 35121;
INSERT INTO item_required_target VALUES
(35121,1,25791);

-- Oil-stained Wolf (25791)
-- Summon Wolf Droppings (46075)  
DELETE FROM creature_ai_scripts WHERE id IN (2579101);
INSERT INTO creature_ai_scripts VALUES
(2579101,25791, 8,0,100,0 ,53326,-1,0,0, 11,46075,0,3, 0,0,0,0, 0,0,0,0, 'Oil-stained Wolf - Spawn Wolf Droppings ');
UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 25791;
