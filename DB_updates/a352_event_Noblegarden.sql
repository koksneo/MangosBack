DELETE FROM creature WHERE id IN (32836,32837);
INSERT INTO creature VALUES
-- Noblegarden Merchant
(1049900,32836,0,1,1,0,0,-9471.77,180.1741,56.3399,1.58526,180,5,0,1,0,0,0),
(1049901,32836,0,1,1,0,0,-5595.21,-522.867,399.652,2.95967,180,5,0,1,0,0,0),
(1049902,32836,1,1,1,0,0,9820.85,954.461,1308.78,5.26288,180,5,0,1,0,0,0),
(1049903,32836,530,1,1,0,0,-4123.21,-12464.2,44.494,3.718093,180,5,0,1,0,0,0),
(1049904,32837,0,1,1,0,0,21808.15,239.949,33.6338,3.58315,180,5,0,1,0,0,0),
(1049905,32837,1,1,1,0,0,339.902,-4674.8,16.4579,4.96339,180,5,0,1,0,0,0),
(1049906,32837,1,1,1,0,0,-2355.09,-349.293,-8.95692,5.16854,180,5,0,1,0,0,0),
(1049907,32837,530,1,1,0,0,10344.4,-6397.77,38.531,5.518078,180,5,0,1,0,0,0);

DELETE FROM game_event_creature WHERE guid BETWEEN 1049900 AND 1049907;
INSERT INTO game_event_creature VALUES
(1049900,9),
(1049901,9),
(1049902,9),
(1049903,9),
(1049904,9),
(1049905,9),
(1049906,9),
(1049907,9);

DELETE FROM item_loot_template WHERE entry = 45072;
INSERT INTO item_loot_template (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
-- bright coloured egg
(45072,44791,100,0,1,2,0,0,0), -- Noblegarden Chocolate
(45072,44806,20.5,0,1,1,0,0,0), -- Brightly Colored Shell Fragment
(45072,44792,1,0,1,1,0,0,0), -- Blossoming Branch
(45072,44800,0.8,0,1,1,0,0,0), -- Spring Robes
(45072,6833,0.7,0,1,1,0,0,0), -- White Tuxedo Shirt
(45072,44803,0.7,0,1,1,0,0,0), -- Spring Circlet
(45072,44794,0.5,0,1,1,0,0,0), -- Spring Rabbits Foot
(45072,45073,0.3,0,1,1,0,0,0), -- Spring Flowers
(45072,6835,0.1,0,1,1,0,0,0), -- Black Tuxedo Pants
(45072,19028,0.6,0,1,1,0,0,0); -- Elegant Dress

DELETE FROM gameobject_loot_template WHERE entry = 4984;
INSERT INTO gameobject_loot_template (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
-- bright coloured egg
(4984,6833,0.6,0,1,1,0,0,0),
(4984,6835,0.6,0,1,1,0,0,0),
(4984,7806,33.33,0,1,1,0,0,0),
(4984,7807,33.33,0,1,1,0,0,0),
(4984,7808,33.33,0,1,1,0,0,0),
(4984,19028,0.6,0,1,1,0,0,0),
(4984,45072,100,0,1,2,0,0,0);
