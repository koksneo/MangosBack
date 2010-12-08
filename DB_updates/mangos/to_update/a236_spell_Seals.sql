-- Paladin Seals proc
-- should be ppm but doesn't work, must use workaround with cooldown (similiar effect)

DELETE FROM `spell_proc_event` WHERE `entry` IN (20185, 20186);
INSERT INTO `spell_proc_event` VALUES
(20166, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4), -- Seal of Wisdom
(20165, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3), -- Seal of Light
(20164, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12); -- Seal of Justice
