-- Support for quest The Smoldering Ruins of Thaurissan (3701)

UPDATE gameobject_template SET flags=flags&~4 WHERE entry=153556;

-- A tormented voice (8887)
DELETE FROM creature WHERE id=8887;

DELETE FROM event_scripts WHERE id=3361;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES 
(3361,0,10,8887,3000,-7757.94, -2159.73, 133.439, -3.08923),
(3361,0,10,8887,3000,-7892.84, -2144.82, 120.545, 2.98451),
(3361,0,10,8887,3000,-7693.64, -2387.06, 147.656, 2.68781),
(3361,0,10,8887,3000,-7804.24, -2103.44, 133.439, -1.91986),
(3361,0,10,8887,3000,-7828.93, -2265.71, 137.186, -1.41372),
(3361,0,10,8887,3000,-7774.49, -2235, 134.134, -1.74533),
(3361,0,10,8887,3000,-7710.73, -2178.15, 131.896, -2.3911),
(3361,0,10,8887,3000,-7741.42, -1948.2, 136.462, -1.22173),
(3361,0,10,8887,3000,-7793.45, -1804.18, 132.184, 1.09956),
(3361,0,10,8887,3000,-7725.99, -2125.54, 133.439, -2.53073),
(3361,0,10,8887,3000,-7775.43, -2313.51, 137.082, -1.81514),
(3361,0,10,8887,3000,-7844.55, -1945.58, 137.301, 2.44346),
(3361,0,10,8887,3000,-7843.89, -1992.06, 139.809, -1.01229),
(3361,0,10,8887,3000,-7748.03, -2078.4, 133.439, -2.63545),
(3361,0,10,8887,3000,-7800.4, -1900.31, 135.089, -2.07694),
(3361,0,10,8887,3000,-7835.78, -2067.96, 136.252, 0.139626),
(3361,0,10,8887,3000,-7888.89, -2004.36, 135.828, 2.98451),
(3361,0,10,8887,3000,-7741.91, -2292.93, 136.29, 1.13446),
(3361,0,10,8887,3000,-7779.31, -1855.2, 134.131, 0.069813),
(3361,0,10,8887,3000,-7891.04, -2188.15, 133.436, 1.37881),
(3361,0,10,8887,3000,-7793.7, -1961.65, 134.118, -0.802851),
(3361,0,10,8887,3000,-7884.96, -2246.48, 136.311, -0.017453),
(3361,0,10,8887,3000,-7715.64, -1846.73, 135.942, -0.418879),
(3361,0,10,8887,3000,-7820.68, -2203.07, 133.439, 2.47837),
(3361,0,10,8887,3000,-7766.91, -2013.52, 135.337, -0.488692),
(3361,0,10,8887,3000,-7716.94, -2033.14, 133.439, 0.802851),
(3361,0,10,8887,3000,-6245.22, -3853.47, -58.7496, 4.46952),
(3361,0,10,8887,3000,-7848.99, -2053.11, 136.305, 5.74393);

UPDATE creature_template SET AIName='EventAI', unit_flags=unit_flags|33554432  WHERE entry=8887;

DELETE FROM creature_ai_scripts WHERE creature_id=8887;
INSERT INTO creature_ai_scripts VALUES
(888701,8887,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'A tormented voic - Random Phase on Spawn'),
(888702,8887,1,1,100,0,100,100,0,0,30,2,3,4,0,0,0,0,0,0,0,0,'A tormented voic - Random Phase on Spawn'),
(888703,8887,10,2,100,0,1,5,1000,1000,1,-88871,-88872,-88873,41,2000,0,0,0,0,0,0,'A tormented voic - Random Whisp (Phase 1)'),
(888704,8887,10,3,100,0,1,5,1000,1000,1,-88874,-88875,-88876,41,2000,0,0,0,0,0,0,'A tormented voic - Random Whisp (Phase 2)'),
(888705,8887,10,4,100,0,1,5,1000,1000,1,-88877,-88878,-88879,41,2000,0,0,0,0,0,0,'A tormented voic - Random Whisp (Phase 3)');

DELETE FROM creature_ai_texts WHERE entry IN (-88871,-88872,-88873,-88874,-88875,-88876,-88877,-88878,-88879);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-88871,'He cannot be defeated. <The relic burns to nothing. The memories it held are now your own. This city was destroyed by a being not of this world.>',4,'A tormented voice whisp1'),
(-88872,'Your existence is acknowledged. <The relic turns to dust. Your head throbs with newfound wisdom. Something evil lurks in the heart of the mountain.>',4,'A tormented voice whisp2'),
(-88873,'Help us, outsider. <The relic crumbles to dust. A vision of eight Dark Iron dwarves performing some sort of ritual fills your head.>',4,'A tormented voice whisp3'),
(-88874,'You will perish here. <Your mind fills with visions of chaos and destruction.>',4,'A tormented voice whisp4'),
(-88875,'Defiler... you will be punished for this incursion. <A symbol of flame radiates from the relic before it crumbles to the earth.>',4,'A tormented voice whisp5'),
(-88876,'Leave this place <The relic emits a white hot arc of flame. A memory is gained: A lone Dark Iron dwarf is surrounded by seven corpses, kneeling before a monolith of flame.>',4,'A tormented voice whisp6'),
(-88877,'Do not taint these ruins, mortal. <You are engulfed in a blinding flash of light. A creature composed entirely of flame is the only thing you can remember seeing.>',4,'A tormented voice whisp7'),
(-88878,'You will perish here. <Your mind fills with visions of chaos and destruction.>',4,'A tormented voice whisp8'),
(-88879,'Your existence is acknowledged. <The relic turns to dust. Your head throbs with newfound wisdom. Something evil lurks in the heart of the mountain.>',4,'A tormented voice whisp9');
