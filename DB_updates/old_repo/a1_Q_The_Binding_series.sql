-- Binding (Voidwalker allinace)
REPLACE INTO `gameobject_template` VALUES ('199999','8','465','Stormwind Summoning Circle','','','','35','0','2','0','0','0','0','0','0','83','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','');
DELETE FROM `gameobject` WHERE id =199999;
INSERT INTO `gameobject` VALUES ('400000','199999','0','1','1','-8971.31','1041.68','52.8626','2.83392','0','0','0.988191','0.153228','25','0','1');

-- Binding (succubus/voidwalker) (horde)
DELETE FROM spell_script_target WHERE entry IN (9221,9223,9222,9224,8712,8712,7728,8674);
INSERT INTO spell_script_target VALUES
-- Summon Voidwalker/Succubus (Orgrimmar & UC)
(9221,0,37097),
(9223,0,37097),
(9222,0,105576),
(9224,0,105576),
-- Summon Felhunter (H/A)
(8712,0,92388),
-- Summon Voidwalker (alliance)
(7728,0,199999),
-- Summon Succubus (alliance)
(8674,0,199999);
