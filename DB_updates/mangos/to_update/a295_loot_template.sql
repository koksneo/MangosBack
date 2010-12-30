#########################################################################################

-- Lieutenant Ta'zinni (Support for quest Atop the Woodlands)
DELETE FROM creature_loot_template WHERE entry=26815;
INSERT INTO creature_loot_template VALUES
(26815,36779,-100,3,1,1,16,36779,1),		-- Ley Line Focus Control Amulet
(26815,36780,-100,2,1,1,6,67,0), 		-- Lieutenant Ta'zinni's Letter
(26815,3,10,1,-42003,1,0,0,0),			-- Salted Venison
(26815,2,15,1,-24726,1,0,0,0),			-- Scrolls
(26815,1,75,0,-30000,1,0,0,0);			-- Some stuff

#########################################################################################

-- Apprentice Osterkilgr (Support for quest The Sum is Greater than the Parts)
DELETE FROM creature_loot_template WHERE entry=30409 AND NOT item=45912;
INSERT INTO creature_loot_template VALUES
(30409,43089,100,1,1,1,0,0,0), 			-- Vrykul Bones
(30409,42772,87,3,1,1,0,0,0),			-- Dr. Terrible's "Building a Better Flesh Giant"
(30409,0,100,0,-30000,1,0,0,0);			-- Some stuff

#########################################################################################

-- Wolves Across the Border (33) missing quest item
DELETE FROM creature_loot_template WHERE item=50432;
INSERT INTO creature_loot_template VALUES
(299,50432,-60,0,1,1,0,0,0),
(69,50432,-60,0,1,1,0,0,0);

#########################################################################################
-- Book of Glyph Mastery (45912) by Grandres (Yrael thx for id's)

REPLACE INTO creature_loot_template VALUES

(32482,45912,2,2,1,1,0,0,0),
-- (37229,45912,2,2,1,1,0,0,0),		-- !doesn't exist in db!
-- (37126,45912,1.1,2,1,1,0,0,0),	-- !doesn't exist in db!
(37031,45912,0.8,2,1,1,0,0,0),		-- !using deadstate!
(37546,45912,0.8,2,1,1,0,0,0),		-- !using deadstate!
(37545,45912,0.8,2,1,1,0,0,0),		-- !using deadstate!
-- (37034,45912,0.7,2,1,1,0,0,0),	-- !doesn't exist in db!
(37035,45912,0.7,2,1,1,0,0,0),		-- !using deadstate!
(37017,45912,0.7,2,1,1,0,0,0),		-- !using deadstate!
(37027,45912,0.7,2,1,1,0,0,0),		-- !using deadstate!
(29350,45912,0.7,2,1,1,0,0,0),	
(37146,45912,0.6,2,1,1,0,0,0),
(37144,45912,0.6,2,1,1,0,0,0),
(36998,45912,0.6,2,1,1,0,0,0),
(37149,45912,0.5,2,1,1,0,0,0),
(37003,45912,0.5,2,1,1,0,0,0),
-- (37228,45912,0.5,2,1,1,0,0,0),	-- !doesn't exist in db!
(37662,45912,0.4,2,1,1,0,0,0),
(31283,45912,0.4,2,1,1,0,0,0),
(37025,45912,0.4,2,1,1,0,0,0),
(36896,45912,0.4,2,1,1,0,0,0),
-- (37501,45912,0.4,2,1,1,0,0,0), 	-- !doesn't exist in db!
(31225,45912,0.4,2,1,1,0,0,0),
(37026,45912,0.4,2,1,1,0,0,0),
(37148,45912,0.4,2,1,1,0,0,0),
-- (37531,45912,0.4,2,1,1,0,0,0), 	-- !doesn't exist in db!
(32300,45912,0.3,2,1,1,0,0,0),
(37571,45912,0.3,2,1,1,0,0,0),
(30697,45912,0.3,2,1,1,0,0,0),
(37021,45912,0.3,2,1,1,0,0,0),
(31161,45912,0.3,2,1,1,0,0,0),
(28077,45912,0.3,2,1,1,0,0,0),
(31224,45912,0.3,2,1,1,0,0,0),
(37544,45912,0.3,2,1,1,0,0,0),
(31159,45912,0.2,2,1,1,0,0,0),
(31198,45912,0.2,2,1,1,0,0,0),
(37004,45912,0.2,2,1,1,0,0,0),
(32175,45912,0.2,2,1,1,0,0,0),
(32162,45912,0.2,2,1,1,0,0,0),
(31160,45912,0.2,2,1,1,0,0,0),
(32492,45912,0.2,2,1,1,0,0,0),
(32771,45912,0.2,2,1,1,0,0,0),
(26858,45912,0.1,2,1,1,0,0,0),
(28467,45912,0.1,2,1,1,0,0,0),
(32278,45912,0.1,2,1,1,0,0,0),
(30831,45912,0.1,2,1,1,0,0,0),
(28494,45912,0.1,2,1,1,0,0,0),
(28255,45912,0.1,2,1,1,0,0,0),
(30829,45912,0.1,2,1,1,0,0,0),
(30689,45912,0.1,2,1,1,0,0,0),
(32268,45912,0.1,2,1,1,0,0,0),
(32263,45912,0.1,2,1,1,0,0,0),
(30861,45912,0.1,2,1,1,0,0,0),
(28917,45912,0.1,2,1,1,0,0,0),
(32285,45912,0.1,2,1,1,0,0,0),
(26922,45912,0.1,2,1,1,0,0,0),
(32291,45912,0.1,2,1,1,0,0,0),
(30868,45912,0.1,2,1,1,0,0,0),
(29489,45912,0.1,2,1,1,0,0,0),
(26405,45912,0.1,2,1,1,0,0,0),
(37230,45912,0.1,2,1,1,0,0,0),
(29626,45912,0.1,2,1,1,0,0,0),
(31229,45912,0.1,2,1,1,0,0,0),
(29503,45912,0.1,2,1,1,0,0,0),
(30830,45912,0.1,2,1,1,0,0,0),
(27579,45912,0.1,2,1,1,0,0,0),
(31401,45912,0.1,2,1,1,0,0,0),
(37664,45912,0.1,2,1,1,0,0,0),
(37030,45912,0.1,2,1,1,0,0,0),
(31323,45912,0.1,2,1,1,0,0,0),
(32772,45912,0.1,2,1,1,0,0,0),
(26357,45912,0.05,2,1,1,0,0,0),
(29461,45912,0.05,2,1,1,0,0,0),
(28110,45912,0.05,2,1,1,0,0,0),
(30447,45912,0.05,2,1,1,0,0,0),
(28085,45912,0.05,2,1,1,0,0,0),
(30430,45912,0.05,2,1,1,0,0,0),
(29331,45912,0.05,2,1,1,0,0,0),
(29377,45912,0.05,2,1,1,0,0,0),
(28158,45912,0.05,2,1,1,0,0,0),
(28603,45912,0.05,2,1,1,0,0,0),
(28414,45912,0.05,2,1,1,0,0,0),
(30333,45912,0.05,2,1,1,0,0,0),
(30167,45912,0.05,2,1,1,0,0,0),
(30167,45912,0.05,2,1,1,0,0,0),
(31411,45912,0.05,2,1,1,0,0,0),
(31413,45912,0.05,2,1,1,0,0,0),
(26786,45912,0.05,2,1,1,0,0,0),
(26407,45912,0.05,2,1,1,0,0,0),
(30746,45912,0.05,2,1,1,0,0,0),
(28109,45912,0.05,2,1,1,0,0,0),
(29622,45912,0.05,2,1,1,0,0,0),
(28268,45912,0.05,2,1,1,0,0,0),
(29717,45912,0.05,2,1,1,0,0,0),
(30864,45912,0.05,2,1,1,0,0,0),
(31693,45912,0.05,2,1,1,0,0,0),
(30849,45912,0.05,2,1,1,0,0,0),
(32236,45912,0.05,2,1,1,0,0,0),
(29133,45912,0.05,2,1,1,0,0,0),
(29211,45912,0.05,2,1,1,0,0,0),
(32149,45912,0.05,2,1,1,0,0,0),
(28600,45912,0.05,2,1,1,0,0,0),
(30725,45912,0.05,2,1,1,0,0,0),
(29518,45912,0.05,2,1,1,0,0,0),
(26356,45912,0.05,2,1,1,0,0,0),
(31265,45912,0.05,2,1,1,0,0,0),
(29036,45912,0.05,2,1,1,0,0,0),
(28381,45912,0.05,2,1,1,0,0,0),
(27230,45912,0.05,2,1,1,0,0,0),
(32280,45912,0.05,2,1,1,0,0,0),
(27680,45912,0.05,2,1,1,0,0,0),
(29656,45912,0.05,2,1,1,0,0,0),
(28186,45912,0.05,2,1,1,0,0,0),
(29327,45912,0.05,2,1,1,0,0,0),
(27177,45912,0.05,2,1,1,0,0,0),
(29129,45912,0.05,2,1,1,0,0,0),
(30448,45912,0.05,2,1,1,0,0,0),
(29722,45912,0.05,2,1,1,0,0,0),
(32502,45912,0.05,2,1,1,0,0,0),
(26347,45912,0.05,2,1,1,0,0,0),
(30988,45912,0.05,2,1,1,0,0,0),
(28380,45912,0.05,2,1,1,0,0,0),
(28010,45912,0.05,2,1,1,0,0,0),
(30875,45912,0.05,2,1,1,0,0,0),
(28118,45912,0.05,2,1,1,0,0,0),
(28784,45912,0.05,2,1,1,0,0,0),
(28750,45912,0.05,2,1,1,0,0,0),
(28081,45912,0.05,2,1,1,0,0,0),
(30147,45912,0.05,2,1,1,0,0,0),
(28213,45912,0.05,2,1,1,0,0,0),
(30003,45912,0.05,2,1,1,0,0,0),
(29562,45912,0.05,2,1,1,0,0,0),
(28861,45912,0.05,2,1,1,0,0,0),
(28188,45912,0.05,2,1,1,0,0,0),
(28564,45912,0.05,2,1,1,0,0,0),
(30951,45912,0.05,2,1,1,0,0,0),
(28748,45912,0.05,2,1,1,0,0,0),
(29695,45912,0.05,2,1,1,0,0,0),
(29958,45912,0.05,2,1,1,0,0,0),
(32505,45912,0.05,2,1,1,0,0,0),
(28358,45912,0.05,2,1,1,0,0,0),
(31403,45912,0.05,2,1,1,0,0,0),
(32507,45912,0.05,2,1,1,0,0,0),
(31041,45912,0.05,2,1,1,0,0,0),
(28496,45912,0.05,2,1,1,0,0,0),
(28659,45912,0.05,2,1,1,0,0,0),
(31399,45912,0.05,2,1,1,0,0,0),
(29699,45912,0.05,2,1,1,0,0,0),
(28023,45912,0.05,2,1,1,0,0,0),
(31702,45912,0.05,2,1,1,0,0,0),
(26434,45912,0.05,2,1,1,0,0,0),
(28495,45912,0.05,2,1,1,0,0,0),
(27578,45912,0.05,2,1,1,0,0,0),
(26681,45912,0.05,2,1,1,0,0,0),
(29237,45912,0.05,2,1,1,0,0,0),
(31231,45912,0.05,2,1,1,0,0,0),
(29123,45912,0.05,2,1,1,0,0,0),
(28442,45912,0.05,2,1,1,0,0,0),
(31843,45912,0.05,2,1,1,0,0,0),
(26436,45912,0.05,2,1,1,0,0,0),
(27355,45912,0.05,2,1,1,0,0,0),
(32284,45912,0.05,2,1,1,0,0,0),
(28083,45912,0.05,2,1,1,0,0,0),
(27018,45912,0.05,2,1,1,0,0,0),
(31123,45912,0.05,2,1,1,0,0,0),
(29407,45912,0.05,2,1,1,0,0,0),
(29390,45912,0.05,2,1,1,0,0,0),
(26633,45912,0.05,2,1,1,0,0,0),
(28105,45912,0.05,2,1,1,0,0,0),
(30046,45912,0.05,2,1,1,0,0,0),
(28399,45912,0.05,2,1,1,0,0,0),
(32267,45912,0.05,2,1,1,0,0,0),
(30409,45912,0.05,2,1,1,0,0,0),
(31402,45912,0.05,2,1,1,0,0,0),
(28843,45912,0.05,2,1,1,0,0,0),
(28345,45912,0.05,2,1,1,0,0,0),
(29698,45912,0.05,2,1,1,0,0,0),
(28288,45912,0.05,2,1,1,0,0,0),
(26428,45912,0.05,2,1,1,0,0,0),
(29409,45912,0.05,2,1,1,0,0,0),
(31754,45912,0.05,2,1,1,0,0,0),
(29235,45912,0.05,2,1,1,0,0,0),
(29426,45912,0.05,2,1,1,0,0,0),
(29915,45912,0.05,2,1,1,0,0,0),
(30894,45912,0.05,2,1,1,0,0,0),
(30698,45912,0.05,2,1,1,0,0,0),
(28097,45912,0.05,2,1,1,0,0,0),
(28068,45912,0.05,2,1,1,0,0,0),
(28575,45912,0.05,2,1,1,0,0,0),
(30949,45912,0.05,2,1,1,0,0,0),
(26409,45912,0.05,2,1,1,0,0,0),
(28477,45912,0.05,2,1,1,0,0,0),
(27580,45912,0.05,2,1,1,0,0,0),
(28802,45912,0.05,2,1,1,0,0,0),
(29794,45912,0.05,2,1,1,0,0,0),
(29861,45912,0.05,2,1,1,0,0,0),
(28443,45912,0.05,2,1,1,0,0,0),
(28916,45912,0.05,2,1,1,0,0,0),
(30856,45912,0.05,2,1,1,0,0,0),
(30482,45912,0.05,2,1,1,0,0,0),
(31040,45912,0.05,2,1,1,0,0,0);


-- doesn't exist in db 
-- Frostwarden Handler (37531)
-- Frostwarden Sorceress (37229)
-- Frostwarden Warrior (37228)
-- Kor'kron Templar (37034)
-- Sister Svalna (37126)

-- Loot add to creatures

UPDATE creature_template SET lootid=29915 WHERE entry=29915;		-- Instructor Hroegar 
UPDATE creature_template SET lootid=32300 WHERE entry=32300;		-- Alumeth the Ascended 
UPDATE creature_template SET lootid=28494 WHERE entry=28494;		-- Kutube'sa 
UPDATE creature_template SET lootid=32492 WHERE entry=32492;		-- Frostbrood Matriarch 
UPDATE creature_template SET lootid=32502 WHERE entry=32502;		-- Ravaged Ghoul 
UPDATE creature_template SET lootid=36896 WHERE entry=36896;		-- Stonespine Gargoyle 
UPDATE creature_template SET lootid=36998 WHERE entry=36998;		-- Skybreaker Protector 
UPDATE creature_template SET lootid=37003 WHERE entry=37003;		-- Skybreaker Vindicator 
UPDATE creature_template SET lootid=37004 WHERE entry=37004;		-- Skybreaker Dreadblade 
UPDATE creature_template SET lootid=37017 WHERE entry=37017;		-- Skybreaker Assassin 
UPDATE creature_template SET lootid=37021 WHERE entry=37021;		-- Skybreaker Vicar 
UPDATE creature_template SET lootid=28358 WHERE entry=28358;		-- Venomtip 
UPDATE creature_template SET lootid=37025 WHERE entry=37025;		-- Stinky 
UPDATE creature_template SET lootid=37026 WHERE entry=37026;		-- Skybreaker Sorcerer 
UPDATE creature_template SET lootid=37027 WHERE entry=37027;		-- Skybreaker Hierophant 
UPDATE creature_template SET lootid=37030 WHERE entry=37030; 		-- Kor'kron Primalist 
UPDATE creature_template SET lootid=37031 WHERE entry=37031;		-- Kor'kron Oracle 
UPDATE creature_template SET lootid=32284 WHERE entry=32284;		-- Scourge Soulbinder 
UPDATE creature_template SET lootid=32267 WHERE entry=32267;		-- Animated Laborer 
UPDATE creature_template SET lootid=29626 WHERE entry=29626;		-- Tormar Frostgut 
UPDATE creature_template SET lootid=30409 WHERE entry=30409;		-- Apprentice Osterkilgr 
UPDATE creature_template SET lootid=30697 WHERE entry=30697;		-- Putrid Colossus 
UPDATE creature_template SET lootid=30698 WHERE entry=30698;		-- Morbidus 
UPDATE creature_template SET lootid=31159 WHERE entry=31159;		-- Baelok 
UPDATE creature_template SET lootid=31160 WHERE entry=31160; 		-- Rokir 
UPDATE creature_template SET lootid=31161 WHERE entry=31161;		-- Sapph 
UPDATE creature_template SET lootid=31225 WHERE entry=31225;		-- Plaguehoof 
UPDATE creature_template SET lootid=31283 WHERE entry=31283; 		-- Orbaz Bloodbane 
UPDATE creature_template SET lootid=31323 WHERE entry=31323; 		-- Lithe Stalker 
UPDATE creature_template SET lootid=31411 WHERE entry=31411;		-- Hulking Horror 
UPDATE creature_template SET lootid=28748 WHERE entry=28748;		-- Serpent-Touched Berserker 
UPDATE creature_template SET lootid=31413 WHERE entry=31413;		-- Hulking Horror 
UPDATE creature_template SET lootid=31702 WHERE entry=31702; 		-- Frostbrood Spawn 
UPDATE creature_template SET lootid=32162 WHERE entry=32162; 		-- Grimkor the Wicked 
UPDATE creature_template SET lootid=32175 WHERE entry=32175; 		-- Chosen Zealot 
UPDATE creature_template SET lootid=37035 WHERE entry=37035; 		-- Kor'kron Vanquisher 
UPDATE creature_template SET lootid=37144 WHERE entry=37144; 		-- Skybreaker Marksman 
UPDATE creature_template SET lootid=31224 WHERE entry=31224; 		-- Icefury 
UPDATE creature_template SET lootid=37664 WHERE entry=37664; 		-- Darkfallen Archmage 
UPDATE creature_template SET lootid=37662 WHERE entry=37662;		-- Darkfallen Commander 
UPDATE creature_template SET lootid=37571 WHERE entry=37571; 		-- Darkfallen Advisor 
UPDATE creature_template SET lootid=37546 WHERE entry=37546; 		-- Frenzied Abomination 
UPDATE creature_template SET lootid=37545 WHERE entry=37545; 		-- Spire Minion 
UPDATE creature_template SET lootid=37544 WHERE entry=37544; 		-- Spire Gargoyle 
UPDATE creature_template SET lootid=28105 WHERE entry=28105; 		-- Warlord Tartek 
UPDATE creature_template SET lootid=37230 WHERE entry=37230; 		-- Spire Frostwyrm 
UPDATE creature_template SET lootid=37149 WHERE entry=37149; 		-- Kor'kron Necrolyte 
UPDATE creature_template SET lootid=37148 WHERE entry=37148; 		-- Skybreaker Summoner 
UPDATE creature_template SET lootid=37146 WHERE entry=37146; 		-- Kor'kron Sniper 
UPDATE creature_template SET lootid=32482 WHERE entry=32482; 		-- Pustulent Colossus

#########################################################################################

-- Add Sea Turtle to drop in Northrend (by Bastek)
DELETE FROM fishing_loot_template WHERE item = 46109;
DELETE FROM gameobject_loot_template WHERE item = 46109 AND entry IN
(25662, 25663, 25664, 25665, 25668, 25669, 25670, 25671, 25673, 25674);
INSERT INTO gameobject_loot_template VALUES
(25662, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Glacial Salmon School
(25663, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Fangtooth Herring School
(25664, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Dragonfin Angelfish School
(25665, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Musselback Sculpin School
(25668, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Imperial Manta Ray School
(25669, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Borean Man O' War School
(25670, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Moonglow Cuttlefish School
(25671, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Deep Sea Monsterbelly School
(25673, 46109, 0.1, 2, 1, 1, 0, 0, 0), -- Nettlefish School
(25674, 46109, 0.1, 2, 1, 1, 0, 0, 0); -- Glassfin Minnow School

#########################################################################################