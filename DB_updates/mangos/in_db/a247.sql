-- poprawa wymogów pre-questów (mini-chain) dla Karuk's Oath (11613) 
UPDATE `quest_template` SET PrevQuestId = 11662 WHERE entry = 11613; 
UPDATE `quest_template` SET NextQuestInChain = 11613 WHERE entry = 11662; 
UPDATE `quest_template` SET NextQuestId = 11662, ExclusiveGroup = -11656, NextQuestInChain = 11662 WHERE entry = 11656; 
UPDATE `quest_template` SET NextQuestId = 11662, ExclusiveGroup = -11656, NextQuestInChain = 11662 WHERE entry = 11661;

-- dostawienie triggera dla quest itemu - DZIA£A
DELETE FROM `gameobject` WHERE `id`=300174;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(3457145,300174,571,1,1,2793.03,7019.35,5.07623,1.41949,0,0,0.651642,0.758527,25,0,1);
 
-- przyzywanie rogiem pierwszego Crewmana - DZIA£A
DELETE FROM `event_scripts` WHERE `id`=16889;
INSERT INTO `event_scripts`(`id`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(16889,0,10,32577,120000,0,2794.393555,7037.020996,-0.452053,4.663200);
 
-- zmiany statystyk Crewmanów i dodanie EventAI - DZIA£A
UPDATE `creature_template`SET `mindmg`=125,`maxdmg`=198,`attackpower`= ROUND((`mindmg`+ `maxdmg`) / 4 * 7),`mindmg`= ROUND(`mindmg`- `attackpower`/ 7),`maxdmg`= ROUND(`maxdmg`- `attackpower`/ 7),`faction_A`=14,`faction_H`=14,`minhealth`=6986,`maxhealth`=7984,`minlevel`=68,`maxlevel`=69,`AIName`= 'EventAI' WHERE `entry` IN (32577,32578,32579,32580);
 
-- ustawienie EventAI dla Crewmanów - po œmierci przyzwanie nastêpnego, ostatni Crewman przyzywa Orabusa - DZIA£A
DELETE FROM `creature_ai_scripts`WHERE `creature_id`IN (32577,32578,32579,32580);
INSERT INTO `creature_ai_scripts`VALUES
(3257701,32577,6,0,100,0,0,0,0,0,12,32578,1,120000,0,0,0,0,0,0,0,0, 'on death summon next crewman'),
(3257801,32578,6,0,100,0,0,0,0,0,12,32579,1,120000,0,0,0,0,0,0,0,0, 'on death summon next crewman'),
(3257901,32579,6,0,100,0,0,0,0,0,12,32580,1,120000,0,0,0,0,0,0,0,0, 'on death summon next crewman'),
(3258001,32580,6,0,100,0,0,0,0,0,12,32576,1,120000,0,0,0,0,0,0,0,0, 'on death summon Orabus');