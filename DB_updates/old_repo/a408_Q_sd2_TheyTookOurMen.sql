-- Quest "They took our men!"
-- rusty cage

DELETE FROM `script_texts` WHERE `entry` IN (-1999778,-1999777);
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(-1999778, "Time to hightail it! Thanks friend!", 0, 0, 0, 0, 'Goblin Prisoner - thanks1 (Q: They took out men)'),
(-1999777, "I'm free? I'm free!", 0, 0, 0, 0, 'Goblin Prisoner - thanks2 (Q: They took out men)');
