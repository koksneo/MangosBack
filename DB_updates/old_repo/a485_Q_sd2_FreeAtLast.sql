-- Runed Giant
DELETE FROM script_texts WHERE entry IN (-1999773,-1999772,-1999771,-1999770,-1999769);
INSERT INTO script_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-1999773,'I thought I was doomed. Thank you for freeing me.',0,'Runed Giant - transformed 1'),
(-1999772,'You have my gratitude.',0,'Runed Giant - transformed 2'),
(-1999771,'I never thought I\'d be free from that terrible spell!',0,'Runed Giant - transformed 3'),
(-1999770,'Thank you, small one.',0,'Runed Giant - transformed 4'),
(-1999769,'The Runebeaker fails to free the Runed Giant, weakning it and causing it to attack! ',2,'Runed Giant - filed zapp approach');
