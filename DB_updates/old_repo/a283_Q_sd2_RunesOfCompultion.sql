-- Overseer texts
DELETE FROM script_texts WHERE entry BETWEEN -1999844 AND -1999842;
INSERT INTO script_texts (`entry`, `content_default`,`comment`) VALUES
(-1999844,'You dare to defy the sons of iron?','Overseer(1)'),
(-1999843,'What do you think you\'re doing?','Overseer aggro(2)'),
(-1999842,'Fool! You will never get away with this!','Overseer aggro(3)');