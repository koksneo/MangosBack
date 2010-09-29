# Quest: The Attack! (434)

DELETE from script_texts WHERE entry IN  (-1100000,-1100001,-1100002,-1100003,-1100004,-1100005,-1100006,-1100000,-1100007,-1100008,-1100009,-1100010,-1100011,-1100012,-1100013,-1100014);
INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1100000,'By your command!',0,'SAY_QUEST_ACCEPT_ATTACK'),
(-1100001,'Wait here. Spybot will make Lescovar come out as soon as possible. Be ready! Attack only after you''ve overheard their conversation.',0,'SAY_TYRION_1'),
(-1100002,'Good day to you both. I would speak to Lord Lescovar.',0,'SAY_SPYBOT_1'),
(-1100003,'Of course. He awaits you in the library.',0,'SAY_GUARD_1'),
(-1100004,'Thank you. The Light be with you both.',0,'SAY_SPYBOT_2'),
(-1100005,'Milord, your guest has arrived. He awaits your presence.',0,'SAY_SPYBOT_3'),
(-1100006,'Ah, thank you kindly. I will leave you to the library while I tend to this small matter.',0,'SAY_LESCOVAR_1'),
(-1100007,'I shall use the time wisely, milord. Thank you.',0,'SAY_SPYBOT_4'),
(-1100008,'It''s time for my meditation, leave me.',0,'SAY_LESCOVAR_2'),
(-1100009,'Yes, sir!',0,'SAY_GUARD_2'),
(-1100010,'There you are. What news from Westfall?',0,'SAY_LESCOVAR_3'),
(-1100011,'VanCleef sends word that the plans are underway. But he''s hear rumors about someone snooping about.',0,'SAY_MARZON_1'),
(-1100012,'Hmm, it could be that meddle Shaw. I will see what I can discover. Be off with you. I''ll contact you again soon.',0,'SAY_LESCOVAR_4'),
(-1100013,'That\'s it! That\'s what you were waiting for! KILL THEM!',1,'SAY_TYRION_2'),
(-1100014,'The Defias shall succeed! No meek adventurer will stop us!',0,'SAY_MARZON_2');

DELETE FROM script_waypoint WHERE entry = 1754;
INSERT INTO script_waypoint VALUES
(1754, 1, -8334.89, 394.130, 122.274, 0, ''),
(1754, 2, -8335.58, 393.519, 122.275, 0, ''),
(1754, 3, -8352.99, 379.932, 122.275, 0, ''),
(1754, 4, -8356.65, 385.247, 122.275, 0, ''),
(1754, 5, -8364.29, 395.317, 122.275, 0, ''),
(1754, 6, -8361.75, 402.852, 122.275, 0, ''),
(1754, 7, -8359.94, 410.92, 122.275, 0, ''),
(1754, 8, -8362.84, 415.409, 122.275, 0, ''),
(1754, 9, -8370.42, 424.6, 122.275, 0, ''),
(1754, 10, -8380.45, 437.115, 122.275, 0, ''),
(1754, 11, -8386.37, 444.906, 122.275, 0, ''),
(1754, 12, -8388.5, 447.314, 123.275, 0, ''),
(1754, 13, -8390.25, 449.247, 124.275, 0, ''),
(1754, 14, -8392.84, 452.397, 123.761, 0, ''),
(1754, 15, -8397.52, 457.326, 123.761, 0, ''),
(1754, 16, -8402.42, 461.646, 123.761, 0, ''),
(1754, 17, -8409.52, 462.677, 123.761, 0, '');

DELETE FROM script_waypoint WHERE entry = 8856;
INSERT INTO script_waypoint VALUES
(8856, 1, -8409.34, 453.345, 123.761, 0, ''),
(8856, 2, -8409.52, 462.677, 123.761, 0, ''),
(8856, 3, -8402.42, 461.646, 123.761, 0, ''),
(8856, 4, -8397.52, 457.326, 123.761, 0, ''),
(8856, 5, -8392.84, 452.397, 123.761, 0, ''),
(8856, 6, -8390.25, 449.247, 124.275, 0, ''),
(8856, 7, -8388.5, 447.314, 123.275, 0, ''),
(8856, 8, -8386.37, 444.906, 122.275, 0, ''),
(8856, 9, -8380.45, 437.115, 122.275, 0, ''),
(8856, 10, -8370.42, 424.6, 122.275, 0, ''),
(8856, 11, -8362.84, 415.409, 122.275, 0, ''),
(8856, 12, -8359.94, 410.92, 122.275, 0, ''),
(8856, 13, -8361.75, 402.852, 122.275, 0, ''),
(8856, 14, -8364.29, 395.317, 122.275, 0, ''),
(8856, 15, -8356.65, 385.247, 122.275, 0, ''),
(8856, 16, -8352.99, 379.932, 122.275, 0, ''),
(8856, 17, -8335.58, 393.519, 122.275, 0, ''),
(8856, 18, -8334.89, 394.13, 122.274, 0, '');
