-- Quest The Light of Dawn
-- spells
DELETE FROM spell_script_target WHERE entry in (53658, 53679, 53701, 53705, 53706, 53677, 53685, 53778);
INSERT INTO spell_script_target VALUES
(53679, 1, 29183),
(53701, 1, 29175),
(53705, 1, 29183),
(53706, 1, 29183),
(53677, 1, 29227),
(53685, 1, 29175),
(53778, 1, 29173);

-- set sd2 scripts names and stats
UPDATE `creature_template` SET `ScriptName` = "npc_highlord_darion_mograine" WHERE `entry` = 29173;
UPDATE `creature_template` SET `ScriptName` = "npc_koltira_orbaz_tassarian_dawn_of_light" WHERE `entry` IN (29199, 29204, 29200);
UPDATE `creature_template` SET `ScriptName` = "mob_acherus_ghoul", AIName="" WHERE entry = 29219;
UPDATE `creature_template` SET `ScriptName` = "mob_warrior_of_the_frozen_wastes", AIName="" WHERE entry = 29206;
UPDATE `creature_template` SET `mindmg` = 197, `maxdmg` = 232, `attackpower` = 205, `dmg_multiplier` = 12.0, `minmana` = 63510, `maxmana` = 68670 WHERE entry = 29174;
UPDATE `creature_template` SET `mindmg` = 210, `maxdmg` = 254, `attackpower` = 233, `dmg_multiplier` = 12.0, `minmana` = 302685, `maxmana` = 302685 WHERE entry = 29182;
UPDATE `creature_template` SET `mindmg` = 220, `maxdmg` = 244, `attackpower` = 220, `dmg_multiplier` = 12.0, `minmana` = 356100, `maxmana` = 356100 WHERE entry = 29177;
UPDATE `creature_template` SET `mindmg` = 223, `maxdmg` = 274, `attackpower` = 220, `dmg_multiplier` = 12.0, `minmana` = 302685, `maxmana` = 302685 WHERE entry = 29181;
UPDATE `creature_template` SET `mindmg` = 225, `maxdmg` = 284, `attackpower` = 220, `dmg_multiplier` = 12.0 WHERE entry = 29178;

-- ACID scripts for mobs taking part in the battle
UPDATE creature_template SET ScriptName='mob_eventai', AIName='EventAI',unit_flags=0,type_flags=8 WHERE entry IN (29199,29204,29200,29174,29182,29186,29190,29176,29178,29179,29180,29177,29181);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (29174, 29182, 29186, 29190, 29176, 29177, 29181);
INSERT INTO `creature_ai_scripts` VALUES
('2917401', '29174', '14', '0', '100', '3', '10000', '50', '5000', '10000', '11', '29427', '6', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light - SPELL_HOLY_LIGHT1'),
('2917402', '29174', '4', '0', '100', '0', '0', '0', '0', '0', '11', '53625', '1', '5', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light aggro'),
('2917403', '29174', '0', '0', '100', '3', '10000', '20000', '10000', '20000', '11', '53625', '5', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light - SPELL_HEROIC_LEAP'),
('2917404', '29174', '0', '0', '100', '3', '10000', '20000', '10000', '20000', '11', '53643', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light - SPELL_HOLY_STRIKE'),
('2917405', '29174', '0', '0', '50', '3', '10000', '20000', '10000', '20000', '11', '53638', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light - SPELL_HOLY_WRATH'),
('2917406', '29174', '0', '0', '100', '3', '10000', '20000', '10000', '20000', '11', '53629', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Defender of the Light - SPELL_UPPERCUT'),
('2918201', '29182', '14', '0', '100', '3', '10000', '50', '5000', '10000', '11', '33642', '6', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Rimblat Earthshatter - SPELL_CHAIN_HEAL'),
('2918202', '29182', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '53630', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rimblat Earthshatter - SPELL_THUNDER'),
('2918601', '29186', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '53633', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rampaging Abomination - SPELL_CLEAVE1'),
('2918602', '29186', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '50335', '5', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rampaging Abomination - SPELL_SCOURGE_HOOK'),
('2919001', '29190', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '53634', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flesh Behemoth - SPELL_SCOURGE_HOOK'),
('2919002', '29190', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '36706', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flesh Behemoth - SPELL_THUNDERCLAP'),
('2919003', '29190', '0', '0', '100', '3', '5000', '10000', '5000', '10000', '11', '53627', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flesh Behemoth - SPELL_THUNDERCLAP'),
('2917601', '29176', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '53631', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Korfax - SPELL_CLEAVE'),
('2917602', '29176', '0', '0', '100', '3', '10000', '20000', '10000', '10000', '11', '53625', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Korfax - SPELL_CLEAVE'),
('2917701', '29177', '14', '0', '100', '3', '10000', '50', '5000', '10000', '11', '37979', '6', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Commander Eligor Dawnbringer - SPELL_HOLY_LIGHT2'),
('2918101', '29181', '14', '0', '100', '3', '10000', '50', '5000', '10000', '11', '20664', '6', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Rayne - SPELL_REJUVENATION'),
('2918102', '29181', '14', '0', '100', '3', '10000', '50', '5000', '10000', '11', '25817', '6', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Rayne - SPELL_TRANQUILITY'),
('2918103', '29181', '0', '0', '100', '3', '10000', '20000', '10000', '20000', '11', '20687', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rayne - SPELL_STARFALL'),
('2918104', '29181', '0', '0', '100', '3', '10000', '20000', '10000', '20000', '11', '21807', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rayne - SPELL_WRATH');

-- add gameobjects
-- light of dawn
DELETE FROM `gameobject` WHERE `id` IN (191330);
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(191330,609,1,128,2283.896,-5287.914,83.066,1,0.0,0.0,0.0,1.0,180,0,1);
-- lightnings
DELETE FROM `gameobject` WHERE `id` IN (191301, 191302);
INSERT INTO `gameobject`(`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(191301, 609, 1, 128, 2246.65, -5260.35, 75.498, 5.78817, 0, 0, 0.244988, -0.969526, 25, 0, 1),
(191301, 609, 1, 128, 2247.22, -5300.06, 82.1673, 0.05475, 0, 0, 0.02737, -0.999625, 25, 0, 1),
(191301, 609, 1, 128, 2283.08, -5251.11, 79.9662, 4.39801, 0, 0, 0.80908, -0.587698, 25, 0, 1),
(191301, 609, 1, 128, 2326.34, -5259.73, 83.4946, 3.74222, 0, 0, 0.955244, -0.295818, 25, 0, 1),
(191301, 609, 1, 128, 2326.13, -5315.91, 81.9966, 2.46987, 0, 0, 0.944127, 0.329582, 25, 0, 1),
(191301, 609, 1, 128, 2279.89, -5280.95, 82.3786, 1.42529, 0, 0, 0.653838, 0.756634, 25, 0, 1),
(191301, 609, 1, 128, 2280.44, -5312.76, 87.6922, 5.41119, 0, 0, 0.422317, -0.906448, 25, 0, 1),
(191302, 609, 1, 128, 2254.7, -5291.1, 82.0513, 0.969759, 0, 0, 0.466102, 0.884731, 25, 0, 1),
(191302, 609, 1, 128, 2277.55, -5263.64, 80.8495, 4.57081, 0, 0, 0.755349, -0.655322, 25, 0, 1),
(191302, 609, 1, 128, 2299.66, -5279.83, 81.7709, 3.5655, 0, 0, 0.977622, -0.210371, 25, 0, 1),
(191302, 609, 1, 128, 2301.1, -5305.76, 81.9966, 3.1571, 0, 0, 0.99997, -0.00775119, 25, 0, 1);
