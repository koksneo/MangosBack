-- Mojo (companion) emots "kiss"
DELETE FROM script_texts WHERE entry = -1799979;
INSERT INTO script_texts (`entry`,`content_default`,`type`,`emote`,`comment`) VALUES
(-1799979,'%s blows $N to kiss',2,17,'emote kiss');