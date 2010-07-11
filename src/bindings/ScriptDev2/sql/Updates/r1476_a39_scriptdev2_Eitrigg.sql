-- Eitrigg Bow Emote handler
DELETE FROM script_texts WHERE entry IN (-1999899);
INSERT INTO script_texts (`entry`,`content_default`,`sound`,`type`,`emote`,`comment`) VALUES
(-1999899,'%s bows his head for a moment, as if in prayer.',0,2,2,'Eitrigg bow in prayer'); -- Bow
