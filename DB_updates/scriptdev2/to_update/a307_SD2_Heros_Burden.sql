DELETE from script_texts WHERE entry IN  (-1780000,-1780001);

INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1780000,'Ah, the heroes. Your little friends said you would come. This certainly saves me the trouble of hunting you down myself!',1,'SAY_AGGRO'),
(-1780001,'Altruis is shielded. You must choose your side quickly to break his spell',3,'EMOTE_SHIELD');

