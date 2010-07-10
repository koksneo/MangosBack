-- go_blood_filled_orb
UPDATE gameobject_template SET ScriptName = 'go_blood_filled_orb' WHERE entry = 182024;

-- Zelemar the Wrathful
DELETE FROM creature_ai_texts WHERE entry = -10000;
INSERT INTO creature_ai_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-10000,'Insolent fool! You thought to steal Zelemar\'s blood? You shall pay with your own!',1,'Zelemar the Wrathful - Aggro');

DELETE FROM creature_ai_scripts WHERE id = 1783001;
INSERT INTO creature_ai_scripts VALUES
(1783001,17830,4,0,100,2, 0,0,0,0, 1,-10000,0,0, 0,0,0,0, 0,0,0,0, 'Zelemar the Wrathful - Aggro yell');

UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 17830;
