-- Restore to work Scrappy Scripts
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'boss_the_lurker_below' WHERE `entry` = '21217';


-- Underbog Colossus
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'mob_underbog_colossus' WHERE `entry` = '21251';

-- GOs
-- Serpentshrine Console
DELETE FROM gameobject WHERE id IN ('185114','185115','185116','185117','185118','184568','184203','184204','184205');
INSERT IGNORE INTO gameobject (guid, id, map, spawnMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
(150001,'185114','548','1','-246','-381','0','2.87108','0','0','0.990867','0.134846','0','100','1'),
(150002,'185115','548','1','123','-432.5','-1','4.82282','0','0','0.667007','-0.745051','0','100','1'),
(150003,'185116','548','1','373','-464','31','3.16015','0','0','0.999957','-0.00927618','0','100','1'),
(150004,'185117','548','1','457','-556','-6.5','1.60673','0','0','0.719697','0.694288','0','100','1'),
(150005,'185118','548','1','348','-683.75','-12.25','6.24922','0','0','0.0169802','-0.999856','0','100','1'),
-- Lady Vashj Bridge Console
(150006,'184568','548','1','48','-574','5','3.06844','0','0','0.999331','0.0365668','0','100','1'),
-- Coilfang Raid Bridge
(150007,'184203','548','1','27','-654.5','15.35','3.14159','0','0','0.999991','-0.00420371','-1','100','1'),
(150008,'184204','548','1','27','-654.5','15.26','3.14159','0','0','0.999991','-0.00420371','-1','100','1'),
(150009,'184205','548','1','27','-654.5','15.17','3.14159','0','0','0.999991','-0.00420371','-1','100','1');
UPDATE `gameobject_template` SET `flags` = '32', `ScriptName` = 'go_serpentshrine_console' WHERE `entry` IN ('185114','185115','185116','185117','185118','184568');
UPDATE `gameobject_template` SET `flags` = '36' WHERE `entry` IN ('184203','184204','184205');
