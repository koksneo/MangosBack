DELETE FROM spell_script_target WHERE entry IN (51366,51331,51332);
INSERT INTO spell_script_target VALUES
-- Hit Apple
(51331,1,28053),
-- Miss Apple, Hit Bird
(51366,1,28093),
-- Miss Apple (hit Lucky Wilhelm)
(51332,1,28054);

-- Apple
-- Lucky Wilhelm
-- Disable random movement
UPDATE creature SET spawndist = 0, MovementType = 0 WHERE guid IN (109999,109917);
-- Apple position
UPDATE creature SET position_z = -77.7, spawntimesecs = 30 WHERE guid = 109917;
-- Lucky Wilhelm sitting on stool
DELETE FROM creature_addon WHERE guid = 109999;
INSERT INTO creature_addon (guid,emote) VALUES
(109999,415);
-- Apple
-- Sholazar Tickbird
-- Enable flying
UPDATE creature_template SET InhabitType = 4 WHERE entry IN (28053,28093);

-- Item quest target to target Wilhelm (as wowhead comments points)  
DELETE FROM `item_required_target` WHERE ENTRY =38573;    
INSERT INTO `item_required_target` VALUES    
('38573','1','28054');

UPDATE creature_template SET ScriptName = 'mob_rjr_target' WHERE entry IN (28053,28054,28093);


