-- q11253 Sniff Out The Enemy

-- check for missing objects
DELETE FROM `gameobject` WHERE `id` IN (300166,186585);
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(700101,300166,571,1,1,1860.18,-6181.96,24.4833,5.32578,0,0,0.460629,-0.887593,25,0,1), -- spawn trigger for summoning hound
(700102,186585,571,1,1,2321.67,-5987.85,1.99588,4.28904,0,0,0.839884,-0.542765,25,0,1); -- spawn missing scroll in cave

-- 2 scouts are supposed to be in the cave with the scroll
DELETE FROM `creature` WHERE `id`=24116;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(735140,24116,571,1,1,0,523,2319.14,-5985.04,2.13309,5.4907,120,0,0,7984,0,0,0),
(735141,24116,571,1,1,0,523,2314.73,-5988.56,1.92231,5.22366,120,0,0,7984,0,0,0);

-- change MovementType for Plaguehound
UPDATE `creature_template` SET MovementType = 2 WHERE entry = 24156;

-- Plaguehound roars
DELETE FROM creature_movement_scripts WHERE id=2415601;
INSERT INTO creature_movement_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, dataint2, comments) 
VALUES (2415601, 3, 1, 15, 0, 0, 0, 0, 0, 0,'plaguehound roars');

-- Plaguehound despawns
DELETE FROM creature_movement_scripts WHERE id=2415602;
INSERT INTO creature_movement_scripts (id, delay, command, datalong, datalong2, datalong3, datalong4, data_flags, dataint, dataint2, comments) 
VALUES (2415602, 0, 18, 0, 0, 0, 0, 0, 0, 0,'plaguehound despawns');

-- Plaguehound waypoints 
DELETE FROM creature_movement_template WHERE entry = 24156;
INSERT INTO creature_movement_template (entry, point, position_x, position_y, position_z, waittime, script_id, emote, spell, wpguid, orientation, model1, model2) 
VALUES 
(24156, 1, 1859.77, -6174.60, 24.1, 3000, 2415601, 0, 0, 0, 5.4907, 0, 0),
(24156, 2, 1872.45, -6170.60, 23.82, 3000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 3, 1881, -6170, 24, 0, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 4, 1987.14, -6176.68, 23.2, 1000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 5, 2012, -6174, 15, 1000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 6, 2016.71, -6127.40, 6.19, 1000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 7, 2192, -6112, 1.50, 1000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 8, 2302, -6036, 3, 1000, 0, 0, 0, 0, 5.4907, 0, 0),
(24156, 9, 2321.67, -5987.85, 1.99588, 1000, 2415602, 0, 0, 0, 4.28904, 0, 0);
