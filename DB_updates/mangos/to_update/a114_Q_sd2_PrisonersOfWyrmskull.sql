# Quest: Prisoners of Wyrmskull (11255)

DELETE from script_texts WHERE entry IN (-1700001,-1700002,-1700003);
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1700001,'I will help you out before I head back to Valgarde. It\'s the least I could do.',0,0,0,0,'Valgarde prisoner SAY_THANKS_1'),
(-1700002,'Thanks, friend. Looking for another to join your group?',0,0,0,0,'Valgarde prisoner SAY_THANKS_2'),
(-1700003,'Many thanks! Allow me to repay you by killing a few dozen of these beasts!',0,0,0,0,'Valgarde prisoner SAY_THANKS_3');
