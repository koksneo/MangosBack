-- Support for quest Salvaging Life's Strength (12805)

-- Item Lifeblood Gem (40397)
DELETE FROM item_required_target WHERE entry=40397;
INSERT INTO item_required_target VALUES
(40397,2,29124);
-- Add quest credit after spell hit to Lifeblood Elemental (29124)
DELETE FROM creature_ai_scripts WHERE id=2912402;
INSERT INTO creature_ai_scripts VALUES
(2912402,29124,8,0,100,0,54191,-1,0,0,33,29303,6,0,0,0,0,0,0,0,0,0,'Lifeblood Elemental - Quest credit after spell hit');
