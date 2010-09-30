--     QUEST_MISSING_FRIENDS     = 10852

DELETE FROM script_texts  WHERE entry IN (-1000050,-1000051,-1000052);
INSERT INTO script_texts (entry,content_default,type,comment) VALUES
(-1000050,'Woot!',0,'Captive Child say1'),
(-1000051,'I think those weird bird guys were going to eat us. Gross!',0,'Captive Child say2'),
(-1000052,'Yay! We\'re free!',0,'Captive Child say3');
