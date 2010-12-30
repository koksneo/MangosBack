-- HACK ALLERT!: couldn't find propper creature spell-focus so created new one
-- this should be redone if some new data come
-- if it is not appying than you have to change custom entry to freeone
DELETE FROM creature_template where entry = 40002;
INSERT INTO `creature_template` VALUES
(40002, 0, 0, 0, 0, 0, 1141, 0, 1141, 0, 'Arcane Prison Spell Focus', NULL, NULL, 0, 1, 1, 64, 64, 0, 0, 20, 35, 35, 0, 0.91, 1.14286, 1, 0, 2, 2, 0, 1, 1, 2000, 2200, 0, 33554434, 0, 0, 0, 0, 0, 0, 1.76, 2.42, 100, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 0.01, 1, 0, 0, 0, 0, 0, 0, 0, 88, 1, 0, 0, 0 , 0, 130, '');
DELETE FROM creature WHERE id = 40002;
INSERT INTO creature VALUES
('9000004','40002','571','1','1','0','0','3485.32','6115.87','74.2931','2.77507','300','0','0','1','0','0','0'),
('9000003','40002','571','1','1','0','0','3393.04','6239.82','78.7484','-1.53589','300','0','0','1','0','0','0'),
('9000002','40002','571','1','1','0','0','3262.55','6161.63','75.9939','0.104719','300','0','0','1','0','0','0');

-- Rescue Arcane Prisoner
-- Summon Prisoner
DELETE FROM spell_script_target WHERE entry IN (45449,45446,45448);
INSERT INTO spell_script_target VALUES
(45449,1,40002),
(45446,1,40002),
(45448,1,40002);

-- Arcane Prisoner
UPDATE creature_template SET 
`minlevel` = 72,
`maxlevel` = 73,
`minhealth` = 7600,
`maxhealth` = 8000,
`minmana` = 7500,
`maxmana` = 7700
WHERE entry IN (25320,25318);

-- Q Prison Break - Arcane Prisoners (Alliance & Horde)
UPDATE creature_template SET ScriptName = 'mob_arcane_prisoner' WHERE entry IN (25320,25318);

