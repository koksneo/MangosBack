# Quest: Finding the Survivors (9948)

DELETE FROM script_texts WHERE entry IN (-1000040,-1000041,-1000042);
INSERT INTO script_texts (entry,content_default,type,comment) VALUES
(-1000040,'Death to the ogres!',1,'SAY_MAGHAR_THANKS_1'),
(-1000041,'Spirits watch for you.',1,'SAY_MAGHAR_THANKS_2'),
(-1000042,'Many Thanks, hero!',1,'SAY_MAGHAR_THANKS_3');
