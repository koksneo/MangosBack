-- Totem beacon focus on MFF bunnies
DELETE FROM spell_script_target WHERE entry = 47129;
INSERT INTO spell_script_target VALUES
(47129,1,26258),
(47129,1,26355);

#####################################################################################################

-- Stamp Out Bonfire (visual dummy of desacrating)
DELETE FROM spell_script_target WHERE entry = 45437;
INSERT INTO spell_script_target VALUES
-- Alliance Bonfire
(45437,0,187943),
(45437,0,187929),
(45437,0,187945),
(45437,0,187946),
(45437,0,187930),
(45437,0,187944),
(45437,0,187914),
(45437,0,187927),
(45437,0,187564),
(45437,0,187916),
(45437,0,187920),
(45437,0,187923),
(45437,0,187924),
(45437,0,187925),
(45437,0,187926),
(45437,0,187928),
(45437,0,187931),
(45437,0,187932),
(45437,0,187934),
(45437,0,187936),
(45437,0,187938),
(45437,0,187940),
(45437,0,187921),
(45437,0,194044),
(45437,0,194045),
(45437,0,194035),
(45437,0,194032),

-- Horde Bonfire
(45437,0,187971),
(45437,0,187973),
(45437,0,187952),
(45437,0,187963),
(45437,0,187950),
(45437,0,187961),
(45437,0,187959),
(45437,0,187957),
(45437,0,187968),
(45437,0,187948),
(45437,0,187953),
(45437,0,187970),
(45437,0,187966),
(45437,0,187975),
(45437,0,187969),
(45437,0,187951),
(45437,0,187956),
(45437,0,187954),
(45437,0,187947),
(45437,0,187972),
(45437,0,187964),
(45437,0,187559),
(45437,0,187965),
(45437,0,194043),
(45437,0,194037),
(45437,0,194046),
(45437,0,194042),
(45437,0,187958),
(45437,0,194034),
(45437,0,194033);

-- Desacrate Fire! quests (for Horde, Eastern Plaguelands)
DELETE FROM gameobject_questrelation WHERE quest IN
(11761,11757,11581,11732,11739,11743,11748,11751,11755,11756,11737,11742,11745,11749);
DELETE FROM gameobject_involvedrelation WHERE quest IN
(11761,11757,11581,11732,11739,11743,11748,11751,11755,11756,11737,11742,11745,11749);

INSERT INTO gameobject_questrelation VALUES
(187944,11761),
(187940,11757),
(187564,11581),
(187914,11732),
(187929,11739),
(187926,11743),
(187931,11748),
(187934,11751),
(187938,11755),
(187921,11756),
(187920,11737),
(187925,11742),
(187928,11745),
(187932,11749);

INSERT INTO gameobject_involvedrelation VALUES
(187944,11761), -- STV
(187940,11757), -- Menethil Harbour
(187564,11581), -- Sentinel Hill
(187914,11732), -- Refuge Point (AH)
(187929,11739), -- Burning Steppes // pure guess of GO entry -- need sniff conflirmation
(187926,11743), -- Darkshire (Duskwood)
(187931,11748), -- Southshore (HF)
(187934,11751), -- Lakeshire (RM)
(187938,11755), -- Aerie Peak (Hinterlands)
(187921,11756), -- Chillwind Camp (WPL) // pure guess of GO entry -- need sniff conflirmation
(187920,11737), -- Blasted Lands
(187925,11742), -- Kharanos (DM)
(187928,11745), -- Goldshire (EF)
(187932,11749); -- Loch Modan
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN 
(11761,11757,11581,11732,11739,11743,11748,11751,11755,11756,11737,11742,11745,11749);

#####################################################################################################

-- Honor the Flame! quests (for Alliance, Eastern Kindomes)
DELETE FROM creature_questrelation WHERE quest IN
(11804,11810,11814,11819,11822,11826,11827,11808,11813,11816,11820,11832,11828,11583);
DELETE FROM creature_involvedrelation WHERE quest IN
(11804,11810,11814,11819,11822,11826,11827,11808,11813,11816,11820,11832,11828,11583);

INSERT INTO creature_questrelation VALUES
(25887,11804), -- Refuge Point (AH)
(25892,11810), -- Burning Steppes
(25896,11814), -- Darkshire
(25901,11819), -- Southshore
(25904,11822), -- Lakeshire
(25908,11826), -- The Hinterlands
(25909,11827), -- WPL
(25890,11808), -- Blasted Lands
(25895,11813), -- Dun Morogh
(25898,11816), -- Elwynn Forest
(25902,11820), -- Loch Modan
(25915,11832), -- Stranglethorn Vale
(25911,11828), -- Wetlands
(25910,11583); -- Westfall

INSERT INTO creature_involvedrelation VALUES
(25887,11804), -- Refuge Point (AH)
(25892,11810), -- Burning Steppes
(25896,11814), -- Darkshire
(25901,11819), -- Southshore
(25904,11822), -- Lakeshire
(25908,11826), -- The Hinterlands
(25909,11827), -- WPL
(25890,11808), -- Blasted Lands
(25895,11813), -- Dun Morogh
(25898,11816), -- Elwynn Forest
(25902,11820), -- Loch Modan
(25915,11832), -- Stranglethorn Vale
(25911,11828), -- Wetlands
(25910,11583); -- Westfall

UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN 
(11804,11810,11814,11819,11822,11826,11827,11808,11813,11816,11820,11832,11828,11583);

UPDATE creature_template SET npcflag = npcflag | 3 WHERE entry IN (25909,25892);

-- Honor the Flame! quests (for Horde, Eastern Kindomes)
DELETE FROM creature_questrelation WHERE quest IN
(11840,11842,11844,11848,11850,11853,11584,11837,11857,11860,11862);
DELETE FROM creature_involvedrelation WHERE quest IN
(11840,11842,11844,11848,11850,11853,11584,11837,11857,11860,11862);

INSERT INTO creature_questrelation VALUES
(25923,11840), -- Arathi Highlands
(25925,11842), -- Badlands
(25927,11844), -- Burning Steppes
(25931,11848), -- Eversong Woods
(25933,11850), -- Ghostlands
(25935,11853), -- Hillsbrad Foothills
(25939,11584), -- Silverpine Forest
(25920,11837), -- Stranglethorn Vale
(25941,11857), -- Swamp of Sorrows
(25944,11860), -- The Hinterlands
(25946,11862); -- Tirisfal Glades
INSERT INTO creature_involvedrelation VALUES
(25923,11840), -- Arathi Highlands
(25925,11842), -- Badlands
(25927,11844), -- Burning Steppes
(25931,11848), -- Eversong Woods
(25933,11850), -- Ghostlands
(25935,11853), -- Hillsbrad Foothills
(25939,11584), -- Silverpine Forest
(25920,11837), -- Stranglethorn Vale
(25941,11857), -- Swamp of Sorrows
(25944,11860), -- The Hinterlands
(25946,11862); -- Tirisfal Glades

UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN 
(11840,11842,11844,11848,11850,11853,11584,11837,11857,11860,11862);

UPDATE creature_template SET npcflag = npcflag | 3 WHERE entry IN (25931,25933,25946);

############################################################################################################

-- Desacrate Fire! quests (for Horde, Eastern Kingdoms)
DELETE FROM gameobject_questrelation WHERE quest IN
(11764,11766,11768,11772,11774,11776,11580,11801,11781,11786,11784);
DELETE FROM gameobject_involvedrelation WHERE quest IN
(11764,11766,11768,11772,11774,11776,11580,11801,11781,11786,11784);

INSERT INTO gameobject_questrelation VALUES
(187947,11764), -- Arathi Highlands
(187954,11766), -- Badlands
(187956,11768), -- Burning Steppes
(194037,11772), -- Eversong Woods
(194046,11774), -- Ghostlands
(187964,11776), -- Hillsbrad Foothills
(187559,11580), -- Silverpine Forest
(187951,11801), -- Stranglethorn Vale
(187969,11781), -- Swamp of Sorrows
(187972,11784), -- The Hinterlands
(194043,11786); -- Tirisfal Glades

INSERT INTO gameobject_involvedrelation VALUES
(187947,11764), -- Arathi Highlands
(187954,11766), -- Badlands
(187956,11768), -- Burning Steppes
(194037,11772), -- Eversong Woods
(194046,11774), -- Ghostlands
(187964,11776), -- Hillsbrad Foothills
(187559,11580), -- Silverpine Forest
(187951,11801), -- Stranglethorn Vale
(187969,11781), -- Swamp of Sorrows
(187972,11784), -- The Hinterlands
(194043,11786); -- Tirisfal Glades

UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN 
(11764,11766,11768,11772,11774,11776,11580,11801,11781,11786,11784);

#############################   KALIMDOR    #################################################################

-- Honor the Flame! quests (for Horde, Kalimdor)
DELETE FROM creature_questrelation WHERE quest IN
(11841,11845,11846,11847,11849,11852,11836,11856,11838,11859,11861,11839);
DELETE FROM creature_involvedrelation WHERE quest IN
(11841,11845,11846,11847,11849,11852,11836,11856,11838,11859,11861,11839);

INSERT INTO creature_questrelation VALUES
(25884,11841), -- Ashenvale
(25928,11845), -- Desolace
(25929,11846), -- Durotar (missing)
(25930,11847), -- Dustwallow Marsh
(25932,11849), -- Feralas
(25936,11852), -- Mulgore (missing)
(25919,11836), -- Silithus
(25940,11856), -- Stonetalon Mountains
(25921,11838), -- Tanaris
(25943,11859), -- The Barrens
(25945,11861), -- Thousand Needles
(25922,11839); -- Winterspring

INSERT INTO creature_involvedrelation VALUES
(25884,11841), -- Ashenvale
(25928,11845), -- Desolace
(25929,11846), -- Durotar (missing)
(25930,11847), -- Dustwallow Marsh
(25932,11849), -- Feralas
(25936,11852), -- Mulgore (missing)
(25919,11836), -- Silithus
(25940,11856), -- Stonetalon Mountains
(25921,11838), -- Tanaris
(25943,11859), -- The Barrens
(25945,11861), -- Thousand Needles
(25922,11839); -- Winterspring

UPDATE creature_template SET npcflag = npcflag|3 WHERE entry IN (25929,25936);

UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN 
(11841,11845,11846,11847,11849,11852,11836,11856,11838,11859,11861,11839);

-- Honor the Flame! quests (Alliance, Kalimdor)
DELETE FROM creature_questrelation WHERE quest IN
(11805,11806,11809,11811,11812,11815,11817,11831,11833,11824,11834);
DELETE FROM creature_involvedrelation WHERE quest IN
(11805,11806,11809,11811,11812,11815,11817,11831,11833,11824,11834);

INSERT INTO creature_questrelation VALUES
(25883,11805), -- Ashenvale
(25888,11806), -- Azuremyst Isle (missing)
(25891,11809), -- Bloodmyst Isle (missing)
(25893,11811), -- Darkshore
(25894,11812), -- Desolace
(25897,11815), -- Dustwallow Marsh
(25899,11817), -- Feralas (missing)
(25914,11831), -- Silithus
(25916,11833), -- Tanaris
(25906,11824), -- Teldrassil
(25917,11834); -- Winterspring

INSERT INTO creature_involvedrelation VALUES
(25883,11805), -- Ashenvale
(25888,11806), -- Azuremyst Isle (missing)
(25891,11809), -- Bloodmyst Isle (missing)
(25893,11811), -- Darkshore
(25894,11812), -- Desolace
(25897,11815), -- Dustwallow Marsh
(25899,11817), -- Feralas (missing)
(25914,11831), -- Silithus
(25916,11833), -- Tanaris
(25906,11824), -- Teldrassil
(25917,11834); -- Winterspring

UPDATE creature_template SET npcflag = npcflag|3 WHERE entry IN (25888,25891,25899);

UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN 
(11805,11806,11809,11811,11812,11815,11817,11831,11833,11824,11834);

-- Desacrate Fire! quests (for Horde, Kalimdor)
DELETE FROM gameobject_questrelation WHERE quest IN
(11734,11735,11738,11740,11741,11744,11746,11760,11762,11753,11763);
DELETE FROM gameobject_involvedrelation WHERE quest IN
(11734,11735,11738,11740,11741,11744,11746,11760,11762,11753,11763);
INSERT INTO gameobject_questrelation VALUES
(187916,11734), -- Ashenvale
(194032,11735), -- Azuremyst Isle (missing)
(194035,11738), -- Bloodmyst Isle (missing)
(187923,11740), -- Darkshore
(187924,11741), -- Desolace
(187927,11744), -- Dustwallow Marsh
(194044,11746), -- Feralas
(187943,11760), -- Silithus
(187945,11762), -- Tanaris
(187936,11753), -- Teldrassil
(187946,11763); -- Winterspring

INSERT INTO gameobject_involvedrelation VALUES
(187916,11734), -- Ashenvale
(194032,11735), -- Azuremyst Isle (missing)
(194035,11738), -- Bloodmyst Isle (missing)
(187923,11740), -- Darkshore
(187924,11741), -- Desolace
(187927,11744), -- Dustwallow Marsh
(194044,11746), -- Feralas (missing)
(187943,11760), -- Silithus
(187945,11762), -- Tanaris
(187936,11753), -- Teldrassil
(187946,11763); -- Winterspring

UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN 
(11734,11735,11738,11740,11741,11744,11746,11760,11762,11753,11763);


-- Desacrate Fire! quests (for Alliance, Eastern Kingdoms)
DELETE FROM gameobject_questrelation WHERE quest IN
(11765,11769,11770,11771,11773,11777,11800,11780,11802,11783,11785,11803);
DELETE FROM gameobject_involvedrelation WHERE quest IN
(11765,11769,11770,11771,11773,11777,11800,11780,11802,11783,11785,11803);

INSERT INTO gameobject_questrelation VALUES
(187948,11765), -- Ashenvale
(187957,11769), -- Desolace
(???,11770), -- Durotar (missing)
(187959,11771), -- Dustwallow Marsh
(187961,11773), -- Feralas
(???,11777), -- Mulgore (missing)
(187950,11800), -- Silithus
(187968,11780), -- Stonetalon Mountains
(187952,11802), -- Tanaris
(187971,11783), -- The Barrens
(187973,11785), -- Thousand Needles
(187953,11803); -- Winterspring
INSERT INTO gameobject_involvedrelation VALUES
(187948,11765), -- Ashenvale
(187957,11769), -- Desolace
(???,11770), -- Durotar (missing)
(187959,11771), -- Dustwallow Marsh
(187961,11773), -- Feralas
(???,11777), -- Mulgore (missing)
(187950,11800), -- Silithus
(187968,11780), -- Stonetalon Mountains
(187952,11802), -- Tanaris
(187971,11783), -- The Barrens
(187973,11785), -- Thousand Needles
(187953,11803); -- Winterspring

UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN 
(11765,11769,11770,11771,11773,11777,11800,11780,11802,11783,11785,11803);

UPDATE gameobject SET id = 187965 WHERE guid = 709412;

##################################   Outlands   ##############################################################

-- Honor the Flame! quests (for Horde, Outlands)
DELETE FROM creature_questrelation WHERE quest IN
(11843,11851,11854,11835,11855,11858,11863);
DELETE FROM creature_involvedrelation WHERE quest IN
(11843,11851,11854,11835,11855,11858,11863);

DELETE FROM creature_questrelation WHERE id = 25937; 
DELETE FROM creature_involvedrelation WHERE id = 25937; 

INSERT INTO creature_questrelation VALUES
(25926,11843), -- Blade's Edge Mountains (missing)
(25934,11851), -- Hellfire Peninsula
(25937,11854), -- Nagrand
(25918,11835), -- Netherstorm (missing)
(25938,11855), -- Shadowmoon Valley (missing)
(25942,11858), -- Terokkar Forest
(25947,11863); -- Zangarmarsh

INSERT INTO creature_involvedrelation VALUES
(25926,11843), -- Blade's Edge Mountains (missing)
(25934,11851), -- Hellfire Peninsula
(25937,11854), -- Nagrand
(25918,11835), -- Netherstorm (missing)
(25938,11855), -- Shadowmoon Valley (missing)
(25942,11858), -- Terokkar Forest
(25947,11863); -- Zangarmarsh

UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN 
(11843,11851,11854,11835,11858,11863);

UPDATE creature_template SET npcflag = npcflag|3 WHERE entry IN (25918,25938);

-- Honor the Flame! quests (for Alliance, Outlands)
DELETE FROM creature_questrelation WHERE quest IN
(11807,11818,11821,11830,11823,11825,11829);
DELETE FROM creature_involvedrelation WHERE quest IN
(11807,11818,11821,11830,11823,11825,11829);

INSERT INTO creature_questrelation VALUES
(25889,11807), -- Blade's Edge Mountains (missing)
(25900,11818), -- Hellfire Peninsula
(25903,11821), -- Nagrand (missing)
(25913,11830), -- Netherstorm (missing)
(25905,11823), -- Shadowmoon Valley (missing)
(25907,11825), -- Terokkar Forest (missing)
(25912,11829); -- Zangarmarsh (missing)

INSERT INTO creature_involvedrelation VALUES
(25889,11807), -- Blade's Edge Mountains (missing)
(25900,11818), -- Hellfire Peninsula
(25903,11821), -- Nagrand (missing)
(25913,11830), -- Netherstorm (missing)
(25905,11823), -- Shadowmoon Valley (missing)
(25907,11825), -- Terokkar Forest (missing)
(25912,11829); -- Zangarmarsh (missing)

UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN 
(11807,11818,11821,11830,11823,11825,11829);
UPDATE creature_template SET npcflag = npcflag|3 WHERE entry IN (25889,25903,25913,25907,25912,25905);

##############################################################################################################

-- Erathean ring elder
UPDATE creature_template SET 
faction_A=1725, 
faction_H=1725 
WHERE entry IN (26221,16781);
