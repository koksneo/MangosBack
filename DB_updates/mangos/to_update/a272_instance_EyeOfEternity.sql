--
-- Eye of Eternity
--

-- Set instance script
UPDATE instance_template SET ScriptName = 'instance_eye_of_eternity' WHERE map = 616;

-- Update flags for NPCs/Vehicles
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30090; -- Vortex;
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35, VehicleEntry = 223, unit_flags = 0 WHERE entry IN (30234, 30248); -- Hover Disk
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35 WHERE entry = 30118; -- Portal (Malygos)
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30282; -- Arcane Overload
UPDATE creature_template SET mindmg = 1, maxdmg = 1, dmg_multiplier = 1 WHERE entry = 30592; -- Static Field

-- Set scriptnames and some misc data to bosses and GOs
UPDATE gameobject_template SET flags = 4, data0 = 43 WHERE gameobject_template.entry in (193967, 193905);
UPDATE `gameobject_template` SET ScriptName = "go_focusing_iris" WHERE `entry` IN (193958, 193960);
UPDATE creature_template SET ScriptName = 'boss_malygos', unit_flags = unit_flags & ~256 WHERE entry = 28859;
UPDATE creature_template SET InhabitType = 3 WHERE entry IN (28859, 31734);
UPDATE creature_template SET InhabitType = 3, mechanic_immune_mask = 617299803 WHERE entry IN (28859, 31734);
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE id = 28859; -- Malygos, don't move
UPDATE creature_template SET ScriptName = 'npc_nexus_lord' WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET ScriptName = 'npc_scion_of_eternity' WHERE entry = 30249; -- Scion of Eternity
UPDATE creature_template SET mechanic_immune_mask = 1072918979 WHERE entry IN (30249, 31751);
UPDATE creature_template SET faction_A = 14, faction_H = 14, ScriptName = 'npc_power_spark' WHERE entry = 30084; -- Power Spark
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry = 32187; -- Power Spark (1)
UPDATE creature_template SET ScriptName = "npc_arcane_overload" WHERE entry = 30282; -- Arcane Overload
UPDATE creature_template SET ScriptName = 'npc_alexstrasza' WHERE entry = 32295;
UPDATE `creature_template` SET speed_walk = 1 WHERE entry IN (30084, 32187); -- speed of power sparks
UPDATE `creature_template` SET InhabitType = 4 WHERE entry IN (32448, 32295); -- Alexstrasza and gift bunny npc fly

DELETE FROM `spell_script_target` WHERE `entry` IN (56505, 61028);
INSERT INTO `spell_script_target` VALUES
(61028, 1, 32448), -- Alexstrasza Gift
(56505, 1, 28859); -- Surge of Power breath dummy: 30334 casts on Malygos 28859

-- Fix Wyrmrest drakes creature info
UPDATE creature_template SET minhealth = 100000, maxhealth = 100000 WHERE entry = 32535;
-- allow drakes to be healed and use proper spell2 entry
UPDATE vehicle_data SET flags = flags|0x0010, Spell2 = 56092 WHERE entry = 165;
-- Hover Disk
DELETE FROM vehicle_seat_data WHERE seat = 2223;
INSERT INTO vehicle_seat_data (seat, flags) VALUES
(2223, 5);
-- make disk unattackable
UPDATE vehicle_data SET flags = flags|0x0080|0x0004|0x0008 WHERE entry = 223;

-- Fix Loot caches being not selectable
UPDATE gameobject_template SET faction = 35, flags = 0 WHERE entry IN (193967, 193905);

DELETE FROM `gameobject` WHERE `id` IN (193905, 193967);
INSERT INTO `gameobject` (id, map, spawnmask, phasemask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES
(193905, 616, 1, 1, 800.456, 1325.26, 271.312, 0, 0, 0, 0.999089, -0.196897, -600, 100, 1),
(193967, 616, 2, 1, 800.456, 1325.26, 271.312, 0, 0, 0, 0.999089, -0.196897, -600, 100, 1);

-- Fix loot for Malygos (Alexstrasza's Gift)
DELETE FROM reference_loot_template WHERE entry = 50008;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount) VALUES
(50008, 40474, 0, 1, 1, 1), -- Surge Needle Ring
(50008, 40497, 0, 1, 1, 1), -- Black Ice
(50008, 40489, 0, 1, 1, 1), -- Greatstaff of the Nexus
(50008, 40526, 0, 1, 1, 1), -- Gown of the Spell-Weaver
(50008, 40511, 0, 1, 1, 1), -- Focusing Energy Epaulets
(50008, 40475, 0, 1, 1, 1), -- Barricade of Eternity
(50008, 40488, 0, 1, 1, 1), -- Ice Spire Scepter
(50008, 40491, 0, 1, 1, 1), -- Hailstorm
(50008, 40519, 0, 1, 1, 1), -- Footsteps of Malygos
(50008, 40486, 0, 1, 1, 1); -- Necklace of the Glittering Chamber

DELETE FROM reference_loot_template WHERE entry = 50009;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount) VALUES
(50009, 40592, 0, 1, 1, 1), -- Boots of Healing Energies
(50009, 40566, 0, 1, 1, 1), -- Unravelling Strands of Sanity
(50009, 40194, 0, 1, 1, 1), -- Blanketing Robes of Snow
(50009, 40543, 0, 1, 1, 1), -- Blue Aspect Helm
(50009, 40590, 0, 1, 1, 1), -- Elevated Lair Pauldrons
(50009, 40560, 0, 1, 1, 1), -- Leggings of the Wanton Spellcaster
(50009, 40589, 0, 1, 1, 1), -- Legplates of Sovereignty
(50009, 40555, 0, 1, 1, 1), -- Mantle of Dissemination
(50009, 40591, 0, 1, 1, 1), -- Melancholy Sabatons
(50009, 40594, 0, 1, 1, 1), -- Spaulders of Catatonia
(50009, 40588, 0, 1, 1, 1), -- Tunic of the Artifact Guardian
(50009, 40549, 0, 1, 1, 1), -- Boots of the Renewed Flight
(50009, 40539, 0, 1, 1, 1), -- Chestguard of the Recluse
(50009, 40541, 0, 1, 1, 1), -- Frosted Adroit Handguards
(50009, 40562, 0, 1, 1, 1), -- Hood of Rationality
(50009, 40561, 0, 1, 1, 1), -- Leash of Heedless Magic
(50009, 40532, 0, 1, 1, 1), -- Living Ice Crystals
(50009, 40531, 0, 1, 1, 1), -- Mark of Norgannon
(50009, 40564, 0, 1, 1, 1), -- Winter Spectacle Gloves
(50009, 40558, 0, 1, 1, 1); -- Arcanic Tramplers

DELETE FROM gameobject_loot_template WHERE entry IN (26094, 26097);
INSERT INTO gameobject_loot_template (entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount) VALUES
(26094, 40752, 100, 0, 2, 2), -- Emblem of Heroism x2
(26094, 	1, 100, 0, -50008, 2), -- 2 items ilevel 213
(26094, 44650, 100, 0, 1, 1), -- Quest item, Judgement at the Eye of Eternity
(26094, 43953, 1, 0, 1, 1), -- Reins of the Blue Drake 	
-- End of 10m Malygos loot

(26097, 40753, 100, 0, 2, 2), -- Emblem of Valor x2
(26097, 	1, 100, 0, -50009, 4), -- 4 items ilevel 226
(26097, 44651, 100, 0, 1, 1), -- Quest item, Heroic Judgement at the Eye of Eternity
(26097, 43952, 1, 0, 1, 1); -- Reins of the Azure Drake
-- End of 25m Malygos loot
