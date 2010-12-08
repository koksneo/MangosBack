-- Judgement of Wisdom / Light
-- should be 15 ppm but doesn't work, must use workaround 4sec. cooldown (similiar effect)
DELETE FROM `spell_proc_event` WHERE `entry` IN (20185, 20186);
INSERT INTO `spell_proc_event` VALUES
(20185, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4),
(20186, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
