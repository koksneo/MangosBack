-- Jack Adams dancing on the table

DELETE FROM script_texts WHERE entry BETWEEN -1999855 AND -1999852;
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1999855,'<sigh> ... This is the end of me','Crusader Lamoof - moan'),
(-1999854,'<sigh> ... Well, I supposed it could be worse.','Crusader Lamoof - quest credit'),
(-1999853,'Thank you friend. If not your aid I would not be here any more.','Crusader Jonathan - quest credit'),
(-1999852,'I am in your debt. Thank you for my life','Crusader Josephine - quest credit');

DELETE FROM script_texts WHERE entry BETWEEN -1999818 AND -1999812;
INSERT INTO script_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-1999818,'Keep quiet, will you? If anyone catches on, we\'re both dead.',4,'Olga (0)'),
(-1999817,'All right, fellas! Who ordered the spiced rum? Was it you, Jackie boy?',0,'Olga (1)'),
(-1999816,'Sure thing, love. Put it on Harry\'s tab, will you? He owes me a drink!',0,'Jack Adams (2)'),
(-1999815,'It\'s ok sweetheart. This one is on the house',0,'Olga (3)'),
(-1999814,'Free rum? Why... that\'s me favourite kind!',0,'Jack Adams (4)'),
(-1999813,'Sweet Neptulon! That was... one drink... too many!',0,'Jack Adams (5)'),
(-1999812,'What are you lot looking at? Pour me another drink!',0,'Jack Adams (6)');
