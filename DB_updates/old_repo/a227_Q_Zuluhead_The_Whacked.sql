DELETE FROM creature_ai_texts WHERE entry = -99978;
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-99978,"Lord Illidan! Bless me with the power of the flight!",1,"Zuluhed the Whacked");
-- Zuluhed the Whacked, Demon Portal, Arcubus Distroyer
UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (11980,22336,22338);

DELETE FROM creature_ai_scripts WHERE creature_id IN (11980,22336,22338);
INSERT INTO creature_ai_scripts VALUES
(1198001, 11980,4,0,100,0, 0,0,0,0, 1,-99978,0,0, 0,0,0,0, 0,0,0,0, 'Zuluhed the Whacked - aggro'),
(1198002, 11980,2,0,100,0, 30,20,0,0, 11,38853,0,1, 0,0,0,0, 0,0,0,0, 'Zuluhed the Whacked - Nether Infusion'),
(1198003, 11980,0,0,100,1, 12000,14000,12000,14000, 11,19717,0,0, 0,0,0,0, 0,0,0,0, 'Zuluhed the Whacked - Rain of Fire'),
(1198004, 11980,0,0,100,1, 20000,20000,45000,45000, 11,38876,4,17, 0,0,0,0, 0,0,0,0, 'Zuluhed the Whacked - summon Demon Poral'),

(2233601,22336, 1,0,100,0, 4000,4000,0,0, 11,38877,0,0, 0,0,0,0, 0,0,0,0, 'Demon Portal'),

(2233801, 22338, 1,0,100,0, 30000,30000,0,0, 41,0,0,0, 0,0,0,0, 0,0,0,0, 'Arcubus Distroyer - force despawn if in OOC');

-- Zuluhed summon coords
UPDATE quest_start_scripts SET
`x` = -4181.29,
`y` = 327.32,
`z` = 123.18,
`o` = 1.78
WHERE id = 10866;
