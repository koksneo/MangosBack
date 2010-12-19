-- Support for quest Wanton Warlord (12151)

DELETE FROM event_scripts WHERE id=17767;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(17767,2,10,27002,3000000,2759.51,415.489,68.9819,2.84202);

DELETE FROM creature_ai_scripts WHERE creature_id=27002;
INSERT INTO creature_ai_scripts VALUES
(2700201,27002,11,0,100,0,0,0,0,0,1,-270021,0,0,0,0,0,0,0,0,0,0,'Grom\'thar the Thunderbringer - Yell on Spawn'),
(2700202,27002,9,0,100,1,5,45,19000,25000,11,52167,1,0,0,0,0,0,0,0,0,0,'Grom\'thar the Thunderbringer - Cast Magnataur Charge'),
(2700203,27002,0,0,100,1,7000,14000,12000,16000,11,52166,0,1,0,0,0,0,0,0,0,0,'Grom\'thar the Thunderbringer - Cast Thunder'),
(2700204,27002,6,0,100,0,0,0,0,0,1,-270022,0,0,0,0,0,0,0,0,0,0,'Grom\'thar the Thunderbringer - Yell on Death');

DELETE FROM creature_ai_texts WHERE entry IN (-270021,-270022);
INSERT INTO creature_ai_texts (entry, content_default, type, comment) VALUES
(-270021,'I\'ll consume your flesh and pick my teeth with your bones!',1,'Grom\'thar the Thunderbringer yell1'),
(-270022,'You\'re no magnataur! Where... did you... find... such strength?',1,'Grom\'thar the Thunderbringer yell2');
