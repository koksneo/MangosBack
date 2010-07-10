-- Disguise as a Brunnhildar Challanger
DELETE FROM `spell_area` WHERE `spell` IN (55012, 72914);
INSERT INTO `spell_area` VALUES
-- The Forlorn Mine
(55012, 4425, 12841,0,0,0,0,2,1), -- spell wlasciwy
(72914, 4425, 12841,0,0,0,0,2,1), -- transformacja, zeby schodzila po wyjsciu z obszaru
-- Brunnhildar Village
(55012, 4422, 12841,0,0,0,0,2,1),
(72914, 4422, 12841,0,0,0,0,2,1),
-- Valley of Ancient Winters
(55012, 4437, 12841,0,0,0,0,2,1),
(72914, 4437, 12841,0,0,0,0,2,1),
-- Dun Niffelem
(55012, 4438, 12841,0,0,0,0,2,1),
(72914, 4438, 12841,0,0,0,0,2,1),
-- Pit of the fang
(55012, 4535, 12841,0,0,0,0,2,1),
(72914, 4535, 12841,0,0,0,0,2,1),
-- Temple of Storms
(55012, 4430, 12841,0,0,0,0,2,1),
(72914, 4430, 12841,0,0,0,0,2,1),
-- The Foot Steppes
(55012, 4432, 12841,0,0,0,0,2,1),
(72914, 4432, 12841,0,0,0,0,2,1);


/* restored propper templates from UDB390 f*cked by previous commits
-- Mildred the Cruel
-- Brijana
update creature_template set
faction_a = 2109,
faction_h = 2109
WHERE entry IN (29885,29592);

-- observed that if Lynx3d vmaps are disabled in Northrend
-- Forlone Mine returns area 67 - dunno why
DELETE FROM spell_area WHERE spell IN (72914,55012);
INSERT INTO spell_area VALUES
-- Lok'lira's Bargain
(55012, 67, 12841,0,0,0,0,2,1),
-- Lok'lira's Bargain (hack - visual aura triggered by 55012,
-- maybe 55012 should have dummyAura in 3th effect instade dummyEffect?)
(72914, 67, 12841,0,0,0,0,2,1);
*/
