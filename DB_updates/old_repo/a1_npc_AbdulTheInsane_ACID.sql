UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 24900;
DELETE FROM creature_ai_scripts WHERE creature_id = 24900;
INSERT INTO creature_ai_scripts VALUES
(2490001,24900, 4,0,100,0, 0,0,0,0, 1,-98990,0,0, 0,0,0,0, 0,0,0,0, 'Abdul the insane - aggro'),
(2490002,24900, 0,0,100,1, 0,0,60000,60000, 1,-98992,-98991,-98992, 0,0,0,0, 0,0,0,0, 'Abdul the insane - random yell'),
(2490003,24900, 0,0,100,1, 30000,30000,60000,60000, 1,-98994,-98993,-98994, 0,0,0,0, 0,0,0,0, 'Abdul the insane - random yell');


DELETE FROM creature_ai_texts WHERE entry BETWEEN -98994 AND -98990;
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-98994,'ABDUL IS STRONG LIKE BULL!',1,'Abdul the insane - random yell'),
(-98993,'ARE YOU CHALLENGING ME? I HAVE THE STRENGTH OF TEN MEN!',1,'Abdul the insane - random yell'),
(-98992,'Its power courses through me! I AM A GOD!',1,'Abdul the insane - random yell'),
(-98991,'HOW DARE YOU! ABDUL WILL PUT YOUR HEAD ON A PIKE!',1,'Abdul the insane - random yell'),
(-98990,'The fury of the Vrykul will consume you!',0,'Abdul the insane - aggro');

-- Abdul The Insane
UPDATE creature_template SET
mechanic_immune_mask = mechanic_immune_mask |16 |8388608 |536870912 |67108864
WHERE entry = 24900;
