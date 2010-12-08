-- Halls of Stone

-- Krystallus
DELETE FROM `script_texts` WHERE `entry` IN (-1599065,-1599066,-1599067,-1599068);
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`)VALUES 
(-1599066, 'Crush....', 14176, 1, 0, 0, 'krystallus SAY_AGGRO'),
(-1599067, 'Break.... you....', 14178, 1, 0, 0, 'krystallus SAY_STONE'),
(-1599068, 'Ha...ha...ha...ha...', 14177, 1, 0, 0, 'krystallus SAY_KILL'),
(-1599069, 'Uuuuhhhhhhhhhh......', 14179, 1, 0, 0, 'krystallus SAY_DEATH');
