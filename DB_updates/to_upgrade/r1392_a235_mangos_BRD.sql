-- Mole Machine (Brewerfest event)
-- Event trigger (bunny)
UPDATE creature_template SET unit_flags = 33554432, ScriptName = 'mob_machine_bunny' WHERE entry IN (26834);

-- Mole Console
REPLACE INTO `gameobject_template` VALUES
('188498','2','6424','Mole Machine Console','','','','0','0','1','0','0','0','0','0','0','0','9454','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','go_mole_console'),
('186880','1','7510','Dark Iron Mole Machine','','','','0','36','1','0','0','0','0','0','95','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','');

-- Mole Machine
REPLACE INTO `gameobject` VALUES
('233401','186880','230','1','1','437.1','-1.96379','-70.7342','2.66842','0','0','0.972144','0.234384','25','100','1'),
-- Mole Machine Console
('233031','188498','230','1','1','416.985','7.24355','-71.0274','0.327595','0','0','0.163066','0.986615','25','100','0');
