-- Quest: HELP! (9923), Corki's Gone Missing Again! (9924), Cho'war the Pillager (9955)

DELETE FROM script_texts WHERE entry IN (-1999851,-1999891);
INSERT INTO script_texts (entry,content_default,type,comment) VALUES
(-1999851,'Thanks! I\'m sure my dad will reward you greatly! Bye!',0,'Corki say'),
(-1999891,'This is the last time I get caught! I promise! Bye!',0,'SAY_CORKI_GONE');
