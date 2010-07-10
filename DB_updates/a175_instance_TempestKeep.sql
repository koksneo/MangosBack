-- Kael'thas weapons scripts
UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (21269,21270,21271,21268,21273,21274,21272);
DELETE FROM creature_ai_scripts WHERE creature_id IN (21269,21270,21271,21268,21273,21274,21272);
INSERT INTO creature_ai_scripts VALUES
(2126901,21269,0,0,100,3, 1000,1000,10000,10000, 11,36981,0,0, 0,0,0,0, 0,0,0,0,'TK:Devastation - Whirlwind'),

(2127001,21270,0,0,100,3, 1000,1000,5000,5000, 11,36985,0,0, 0,0,0,0, 0,0,0,0,'TK:Cosmic Infuser - Holy Nova'),
(2127002,21270,2,0,100,3, 50,0,10000,10000, 11,36983,0,1, 0,0,0,0, 0,0,0,0,'TK:Cosmic Infuser - Heal'),

(2127101,21271,0,0,100,3, 1000,1000,5000,5000, 11,3391,1,0, 0,0,0,0, 0,0,0,0,'TK:Infinity Blade - Trash'),

(2126801,21268,0,0,100,3, 10000,10000,10000,10000, 11,36994,0,0, 0,0,0,0, 0,0,0,0,'TK:Netherstrand Longbow - Blink'),
(2126802,21268,0,0,100,3, 7000,7000,10000,10000, 11,36979,0,1, 0,0,0,0, 0,0,0,0,'TK:Netherstrand Longbow - Multishot'),
(2126803,21268,0,0,100,3, 500,500,2000,2000, 11,36980,1,0, 0,0,0,0, 0,0,0,0,'TK:Netherstrand Longbow -Shot'),

(2127301,21273,13,0,100,3, 5000,10000,0,0, 11,36988,1,0, 0,0,0,0, 0,0,0,0,'TK:Phaseshift Bulwark - Shield Bash'),

(2127401,21274,9,0,100,3, 0,15,5000,5000, 29,20,1,0, 11,36989,0,1, 0,0,0,0,'TK:Staff of Disintegration - Frost Nova + ranged position'),
(2127402,21274,0,0,100,3, 3000,3000,3000,3000, 0,0,0,0, 11,36990,1,0, 0,0,0,0,'TK:Staff of Disintegration - Frost Bolt'),

(2127201,21272,0,0,100,3, 1000,1000,3000,5000, 0,0,0,0, 11,36991,1,0, 0,0,0,0,'TK:Warp Slicer - Rend');