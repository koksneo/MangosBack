####################################################################################

-- Missing items Tatiana <Master Jewelcrafting Trainer> by Grandres
DELETE FROM npc_vendor WHERE entry = 18774;
INSERT INTO npc_vendor VALUES
(18774,28458,0,0,0), -- Bold Tourmaline
(18774,28462,0,0,0), -- Bright Tourmaline
(18774,28466,0,0,0), -- Brilliant Amber
(18774,28459,0,0,0), -- Delicate Tourmaline
(18774,23131,0,0,0), -- Design: Bold Blood Garnet
(18774,28596,0,0,0), -- Design: Bright Blood Garnet
(18774,23148,0,0,0), -- Design: Brilliant Golden Draenite
(18774,23137,0,0,0), -- Design: Glinting Flame Spessarite
(18774,23144,0,0,0), -- Design: Glowing Shadow Draenite
(18774,23135,0,0,0), -- Design: Inscribed Flame Spessarite
(18774,23141,0,0,0), -- Design: Jagged Deep Peridot
(18774,23140,0,0,0), -- Design: Radiant Deep Peridot
(18774,23151,0,0,0), -- Design: Rigid Golden Draenite
(18774,28291,0,0,0), -- Design: Smooth Golden Draenite
(18774,23152,0,0,0), -- Design: Solid Azure Moonstone
(18774,23147,0,0,0), -- Design: Sovereign Shadow Draenite
(18774,23153,0,0,0), -- Design: Sparkling Azure Moonstone
(18774,23130,0,0,0), -- Design: Teardrop Blood Garnet
(18774,28469,0,0,0), -- Gleaming Amber
(18774,20815,0,0,0), -- Jeweler's Kite
(18774,20824,0,0,0), -- Simple Grinder
(18774,28465,0,0,0), -- Lustrous Zircon
(18774,28468,0,0,0), -- Rigid Amber
(18774,28461,0,0,0), -- Runed Tourmaline
(18774,28467,0,0,0), -- Smooth Amber
(18774,28463,0,0,0), -- Solid Zircon
(18774,28464,0,0,0), -- Sparkling Zircon
(18774,28460,0,0,0), -- Teardrop Tourmaline
(18774,28470,0,0,0); -- Thick Amber 

####################################################################################

-- Missing items Kalaen <Master Jewelcrafting Trainer> by Grandres
DELETE FROM npc_vendor WHERE entry = 18751;
INSERT INTO npc_vendor VALUES
(18751,28458,0,0,0), -- Bold Tourmaline
(18751,28462,0,0,0), -- Bright Tourmaline
(18751,28466,0,0,0), -- Brilliant Amber
(18751,28459,0,0,0), -- Delicate Tourmaline
(18751,23131,0,0,0), -- Design: Bold Blood Garnet
(18751,28596,0,0,0), -- Design: Bright Blood Garnet
(18751,23148,0,0,0), -- Design: Brilliant Golden Draenite
(18751,23137,0,0,0), -- Design: Glinting Flame Spessarite
(18751,23144,0,0,0), -- Design: Glowing Shadow Draenite
(18751,23135,0,0,0), -- Design: Inscribed Flame Spessarite
(18751,23141,0,0,0), -- Design: Jagged Deep Peridot
(18751,23140,0,0,0), -- Design: Radiant Deep Peridot
(18751,23151,0,0,0), -- Design: Rigid Golden Draenite
(18751,28291,0,0,0), -- Design: Smooth Golden Draenite
(18751,23152,0,0,0), -- Design: Solid Azure Moonstone
(18751,23147,0,0,0), -- Design: Sovereign Shadow Draenite
(18751,23153,0,0,0), -- Design: Sparkling Azure Moonstone
(18751,23130,0,0,0), -- Design: Teardrop Blood Garnet
(18751,28469,0,0,0), -- Gleaming Amber
(18751,20815,0,0,0), -- Jeweler's Kite
(18751,20824,0,0,0), -- Simple Grinder
(18751,28465,0,0,0), -- Lustrous Zircon
(18751,28468,0,0,0), -- Rigid Amber
(18751,28461,0,0,0), -- Runed Tourmaline
(18751,28467,0,0,0), -- Smooth Amber
(18751,28463,0,0,0), -- Solid Zircon
(18751,28464,0,0,0), -- Sparkling Zircon
(18751,28460,0,0,0), -- Teardrop Tourmaline
(18751,28470,0,0,0); -- Thick Amber

####################################################################################
-- Arcanum Enhancements replace items with required reputation 
-- Note! Nowadays MaNGOS doesn't support required reputation while buying
DELETE FROM npc_vendor WHERE item IN 
(50370,44152,50368,44159,44149,50367,50373,50372,44702,44701,44150,50369);
INSERT INTO npc_vendor VALUES
(32533,50370,0,0,0),
(32287,50368,0,0,0),
(32538,50367,0,0,0),
(32565,50373,0,0,0),
(32774,50373,0,0,0),
(32773,50372,0,0,0),
(32564,50372,0,0,0),
(30431,50369,0,0,0);

####################################################################################
-- Add missing item Greater Inscription of the Gladiator (44957)
DELETE FROM npc_vendor WHERE item=44957;
INSERT INTO npc_vendor VALUES
(12793,44957,0,0,2588),
(12781,44957,0,0,2588);

####################################################################################
-- Add and remove missing items - pvp vendors by Grandres
-- Alliance's vendors
-- Sergeant Major Clate (12785) missing items

-- Master Sergeant's Insignia (18442)
DELETE FROM npc_vendor where item=18442;
INSERT INTO npc_vendor (entry,item,maxcount,incrtime,ExtendedCost) VALUES
(12785,18442,0,0,838);

-- Master Sergeant's Insignia (18444)
DELETE FROM npc_vendor where item=18444;
INSERT INTO npc_vendor VALUES
(12785,18444,0,0,930);

-- Master Sergeant's Insignia (18443)
DELETE FROM npc_vendor where item=18443;
INSERT INTO npc_vendor VALUES
(12785,18443,0,0,491);

-- Sergeant's Cape (18440)
DELETE FROM npc_vendor where item=18440;
INSERT INTO npc_vendor VALUES
(12785,18440,0,0,1050);

-- Sergeant's Cape (18441)
DELETE FROM npc_vendor where item=18441;
INSERT INTO npc_vendor VALUES
(12785,18441,0,0,986);

-- Sergeant's Cape (16342)
DELETE FROM npc_vendor where item=16342;
INSERT INTO npc_vendor VALUES
(12785,16342,0,0,774);

-- Sergeant Major's Silk Cuffs (18457)
DELETE FROM npc_vendor where item=18457;
INSERT INTO npc_vendor VALUES
(12785,18457,0,0,931);

-- Sergeant Major's Silk Cuffs (18456)
DELETE FROM npc_vendor where item=18456;
INSERT INTO npc_vendor VALUES
(12785,18456,0,0,492);

-- Sergeant Major's Plate Wristguards (18447)
DELETE FROM npc_vendor where item=18447;
INSERT INTO npc_vendor VALUES
(12785,18447,0,0,931);

-- Sergeant Major's Plate Wristguards (18445)
DELETE FROM npc_vendor where item=18445;
INSERT INTO npc_vendor VALUES
(12785,18445,0,0,492);

-- Sergeant Major's Leather Armsplints (18453)
DELETE FROM npc_vendor where item=18453;
INSERT INTO npc_vendor VALUES
(12785,18453,0,0,931);

-- Sergeant Major's Leather Armsplints (18452)
DELETE FROM npc_vendor where item=18452;
INSERT INTO npc_vendor VALUES
(12785,18452,0,0,492);

-- Sergeant Major's Dragonhide Armsplints (18455)
DELETE FROM npc_vendor where item=18455;
INSERT INTO npc_vendor VALUES
(12785,18455,0,0,931);

-- Sergeant Major's Dragonhide Armsplints (18454)
DELETE FROM npc_vendor where item=18454;
INSERT INTO npc_vendor VALUES
(12785,18454,0,0,492);

-- Sergeant Major's Chain Armguards (18449)
DELETE FROM npc_vendor where item=18449;
INSERT INTO npc_vendor VALUES
(12785,18449,0,0,931);

-- Sergeant Major's Chain Armguards (18448)
DELETE FROM npc_vendor where item=18448;
INSERT INTO npc_vendor VALUES
(12785,18448,0,0,492);


-- Insygnia of the Alliance (18854)
DELETE FROM npc_vendor where item=18854;
INSERT INTO npc_vendor VALUES
(12785,18854,0,0,634);

-- Insygnia of the Alliance (18856)
DELETE FROM npc_vendor where item=18856;
INSERT INTO npc_vendor VALUES
(12785,18856,0,0,634);

-- Insygnia of the Alliance (18857)
DELETE FROM npc_vendor where item=18857;
INSERT INTO npc_vendor VALUES
(12785,18857,0,0,634);

-- Insygnia of the Alliance (18858)
DELETE FROM npc_vendor where item=18858;
INSERT INTO npc_vendor VALUES
(12785,18858,0,0,634);

-- Insygnia of the Alliance (18859)
DELETE FROM npc_vendor where item=18859;
INSERT INTO npc_vendor VALUES
(12785,18859,0,0,634);

-- Insygnia of the Alliance (18862)
DELETE FROM npc_vendor where item=18862;
INSERT INTO npc_vendor VALUES
(12785,18862,0,0,634);

-- Insygnia of the Alliance (18863)
DELETE FROM npc_vendor where item=18863;
INSERT INTO npc_vendor VALUES
(12785,18863,0,0,634);

-- Insygnia of the Alliance (18864)
DELETE FROM npc_vendor where item=18864;
INSERT INTO npc_vendor VALUES
(12785,18864,0,0,634);

-- Insygnia of the Alliance (29593)
DELETE FROM npc_vendor where item=29593;
INSERT INTO npc_vendor VALUES
(12785,29593,0,0,634);

-- Master Sergeant Biggins remove items, which it doesn't sell
DELETE FROM npc_vendor WHERE NOT item IN 
(44957,18606,18839,18841,15198,31838,31839,31852,31853,31840,31841,31854,31855,15196,32455,32453) AND entry=12781;

-- Lieutenant Rachel Vaccar (12778) add missing items

-- Medallion of the Alliance (28234)
DELETE FROM npc_vendor where item=28234;
INSERT INTO npc_vendor VALUES
(12778,28234,0,0,2404);

-- Medallion of the Alliance (28235)
DELETE FROM npc_vendor where item=28235;
INSERT INTO npc_vendor VALUES
(12778,28235,0,0,2404);

-- Medallion of the Alliance (28236)
DELETE FROM npc_vendor where item=28236;
INSERT INTO npc_vendor VALUES
(12778,28236,0,0,2404);

-- Medallion of the Alliance (28237)
DELETE FROM npc_vendor where item=28237;
INSERT INTO npc_vendor VALUES
(12778,28237,0,0,2404);

-- Medallion of the Alliance (28238)
DELETE FROM npc_vendor where item=28238;
INSERT INTO npc_vendor VALUES
(12778,28238,0,0,2404);

-- Medallion of the Alliance (30348)
DELETE FROM npc_vendor where item=30348;
INSERT INTO npc_vendor VALUES
(12778,30348,0,0,2404);

-- Medallion of the Alliance (30349)
DELETE FROM npc_vendor where item=30349;
INSERT INTO npc_vendor VALUES
(12778,30349,0,0,2404);

-- Medallion of the Alliance (30350)
DELETE FROM npc_vendor where item=30350;
INSERT INTO npc_vendor VALUES
(12778,30350,0,0,2404);

-- Medallion of the Alliance (30351)
DELETE FROM npc_vendor where item=30351;
INSERT INTO npc_vendor VALUES
(12778,30351,0,0,2404);

-- Medallion of the Alliance (38589)
DELETE FROM npc_vendor where item=38589;
INSERT INTO npc_vendor VALUES
(12778,38589,0,0,2404);

-- Band of Triumph (28246)
DELETE FROM npc_vendor where item=28246;
INSERT INTO npc_vendor VALUES
(12778,28246,0,0,2253);

-- Band of Dominance (28247)
DELETE FROM npc_vendor where item=28247;
INSERT INTO npc_vendor VALUES
(12778,28247,0,0,2253);

-- Medallion of the Alliance (37864)
DELETE FROM npc_vendor where item=37864;
INSERT INTO npc_vendor VALUES
(12778,37864,0,0,2403);

-- Talisman of the Alliance (25829)
DELETE FROM npc_vendor where item=25829;
INSERT INTO npc_vendor VALUES
(12778,25829,0,0,125);

-- Sergeant's Heavy Cloak (28380)
DELETE FROM npc_vendor where item=28380;
INSERT INTO npc_vendor VALUES
(12778,28380,0,0,2269);

-- Sergeant's Heavy Cape (28379)
DELETE FROM npc_vendor where item=28379;
INSERT INTO npc_vendor VALUES
(12778,28379,0,0,2269);

-- Captain O'Neal (34080) add missing items

-- Ametrine (36931)
DELETE FROM npc_vendor where item=36931 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36931,0,0,2588);

-- Cardinal Ruby (36919)
DELETE FROM npc_vendor where item=36919 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36919,0,0,2588);

-- Dreadstone (36928)
DELETE FROM npc_vendor where item=36928 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36928,0,0,2588);

-- Eye of Zul (36934)
DELETE FROM npc_vendor where item=36934 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36934,0,0,2588);

-- King's Amber (36922)
DELETE FROM npc_vendor where item=36922 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36922,0,0,2588);

-- Majestic Zircon (36925)
DELETE FROM npc_vendor where item=36925 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,36925,0,0,2588);

-- Inscribed Ornate Topaz (28363)
DELETE FROM npc_vendor where item=28363 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28363,0,0,99);

-- Potent Ornate Topaz (28123)
DELETE FROM npc_vendor where item=28123 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28123,0,0,99);

-- Bold Ornate Ruby (28362)
DELETE FROM npc_vendor where item=28362 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28362,0,0,95);

-- Gleaming Ornate Dawnstone (28120)
DELETE FROM npc_vendor where item=28120 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28120,0,0,95);

-- Runed Ornate Ruby (28118)
DELETE FROM npc_vendor where item=28118 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28118,0,0,95);

-- Smooth Ornate Dawnstone (28119)
DELETE FROM npc_vendor where item=28119 and entry=34080;
INSERT INTO npc_vendor VALUES
(34080,28119,0,0,95);

-- Horde's vendors
-- First Sergeant Hola'mahi (12795) missing items

-- Senior Sergeant's Insignia (15200)
DELETE FROM npc_vendor where item=15200;
INSERT INTO npc_vendor VALUES
(12795,15200,0,0,838);

-- Senior Sergeant's Insignia (18428)
DELETE FROM npc_vendor where item=18428;
INSERT INTO npc_vendor VALUES
(12795,18428,0,0,930);

-- Senior Sergeant's Insignia (16335)
DELETE FROM npc_vendor where item=16335;
INSERT INTO npc_vendor VALUES
(12795,16335,0,0,491);

-- Sergeant's Cloak (18427)
DELETE FROM npc_vendor where item=18440;
INSERT INTO npc_vendor VALUES
(12795,18440,0,0,1050);

-- Sergeant's Cloak (16341)
DELETE FROM npc_vendor where item=18441;
INSERT INTO npc_vendor VALUES
(12795,18441,0,0,986);

-- Sergeant's Cloak (18461)
DELETE FROM npc_vendor where item=16342;
INSERT INTO npc_vendor VALUES
(12795,16342,0,0,774);

-- First Sergeant's Silk Cuffs (18437)
DELETE FROM npc_vendor where item=18437;
INSERT INTO npc_vendor VALUES
(12795,18437,0,0,931);

-- First Sergeant's Silk Cuffs (16486)
DELETE FROM npc_vendor where item=16486;
INSERT INTO npc_vendor VALUES
(12795,16486,0,0,492);

-- First Sergeant's Plate Bracers (18430)
DELETE FROM npc_vendor where item=18430;
INSERT INTO npc_vendor VALUES
(12795,18430,0,0,931);

-- First Sergeant's Plate Bracers (18429)
DELETE FROM npc_vendor where item=18429;
INSERT INTO npc_vendor VALUES
(12795,18429,0,0,492);

-- First Sergeant's Leather Armguards (18435)
DELETE FROM npc_vendor where item=18435;
INSERT INTO npc_vendor VALUES
(12795,18435,0,0,931);

-- First Sergeant's Leather Armguards (16497)
DELETE FROM npc_vendor where item=16497;
INSERT INTO npc_vendor VALUES
(12795,16497,0,0,492);

-- First Sergeant's Dragonhide Armguards (18436)
DELETE FROM npc_vendor where item=18436;
INSERT INTO npc_vendor VALUES
(12795,18436,0,0,931);

-- First Sergeant's Dragonhide Armguards (18434)
DELETE FROM npc_vendor where item=18434;
INSERT INTO npc_vendor VALUES
(12795,18434,0,0,492);

-- First Sergeant's Mail Wristguards (18432)
DELETE FROM npc_vendor where item=18432;
INSERT INTO npc_vendor VALUES
(12795,18432,0,0,931);

-- First Sergeant's Mail Wristguards (16532)
DELETE FROM npc_vendor where item=16532;
INSERT INTO npc_vendor VALUES
(12795,16532,0,0,492);


-- Insignia of the Horde (18834)
DELETE FROM npc_vendor where item=18834;
INSERT INTO npc_vendor VALUES
(12795,18834,0,0,634);

-- Insignia of the Horde (18845)
DELETE FROM npc_vendor where item=18845;
INSERT INTO npc_vendor VALUES
(12795,18845,0,0,634);

-- Insignia of the Horde (18846)
DELETE FROM npc_vendor where item=18846;
INSERT INTO npc_vendor VALUES
(12795,18846,0,0,634);

-- Insignia of the Horde (18849)
DELETE FROM npc_vendor where item=18849;
INSERT INTO npc_vendor VALUES
(12795,18849,0,0,634);

-- Insignia of the Horde (18850)
DELETE FROM npc_vendor where item=18850;
INSERT INTO npc_vendor VALUES
(12795,18850,0,0,634);

-- Insignia of the Horde (18851)
DELETE FROM npc_vendor where item=18851;
INSERT INTO npc_vendor VALUES
(12795,18851,0,0,634);

-- Insignia of the Horde (18852)
DELETE FROM npc_vendor where item=18852;
INSERT INTO npc_vendor VALUES
(12795,18852,0,0,634);

-- Insignia of the Horde (18853)
DELETE FROM npc_vendor where item=18853;
INSERT INTO npc_vendor VALUES
(12795,18853,0,0,634);

-- Insignia of the Horde (29592)
DELETE FROM npc_vendor where item=29592;
INSERT INTO npc_vendor VALUES
(12795,29592,0,0,634);

-- Legionnaire Teena (12788) add missing items

-- Medallion of the Horde (28239)
DELETE FROM npc_vendor where item=28239;
INSERT INTO npc_vendor VALUES
(12788,28239,0,0,2404);

-- Medallion of the Horde (28240)
DELETE FROM npc_vendor where item=28240;
INSERT INTO npc_vendor VALUES
(12788,28240,0,0,2404);

-- Medallion of the Horde (28241)
DELETE FROM npc_vendor where item=28241;
INSERT INTO npc_vendor VALUES
(12788,28241,0,0,2404);

-- Medallion of the Horde (28242)
DELETE FROM npc_vendor where item=28242;
INSERT INTO npc_vendor VALUES
(12788,28242,0,0,2404);

-- Medallion of the Horde (28243)
DELETE FROM npc_vendor where item=28243;
INSERT INTO npc_vendor VALUES
(12788,28243,0,0,2404);

-- Medallion of the Horde (30343)
DELETE FROM npc_vendor where item=30343;
INSERT INTO npc_vendor VALUES
(12788,30343,0,0,2404);

-- Medallion of the Horde (30344)
DELETE FROM npc_vendor where item=30344;
INSERT INTO npc_vendor VALUES
(12788,30344,0,0,2404);

-- Medallion of the Horde (30345)
DELETE FROM npc_vendor where item=30345;
INSERT INTO npc_vendor VALUES
(12788,30345,0,0,2404);

-- Medallion of the Horde (30346)
DELETE FROM npc_vendor where item=30346;
INSERT INTO npc_vendor VALUES
(12788,30346,0,0,2404);

-- Medallion of the Horde (38588)
DELETE FROM npc_vendor where item=38588;
INSERT INTO npc_vendor VALUES
(12788,38588,0,0,2404);

-- Band of Triumph (28246)
DELETE FROM npc_vendor where item=28246;
INSERT INTO npc_vendor VALUES
(12788,28246,0,0,2253);

-- Band of Dominance (28247)
DELETE FROM npc_vendor where item=28247;
INSERT INTO npc_vendor VALUES
(12788,28247,0,0,2253);

-- Medallion of the Horde (37865)
DELETE FROM npc_vendor where item=37865;
INSERT INTO npc_vendor VALUES
(12788,37865,0,0,2403);

-- Talisman of the Horde (24551)
DELETE FROM npc_vendor where item=24551;
INSERT INTO npc_vendor VALUES
(12788,24551,0,0,125);

-- Sergeant's Heavy Cape (28378)
DELETE FROM npc_vendor where item=28378;
INSERT INTO npc_vendor VALUES
(12788,28378,0,0,2269);

-- Sergeant's Heavy Cloak (28377)
DELETE FROM npc_vendor where item=28377;
INSERT INTO npc_vendor VALUES
(12788,28377,0,0,2269);

-- Brave Stonehide (12793) remove items, which it doesn't sell
DELETE FROM npc_vendor WHERE NOT item IN 
(44957,18607,18839,18841,15197,31838,31839,31852,31853,31840,31841,31854,31855,15199,32455,32453) AND entry=12793;

-- Lady Palanseer (34040) add missing items

-- Ametrine (36931)
DELETE FROM npc_vendor where item=36931 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36931,0,0,2588);

-- Cardinal Ruby (36919)
DELETE FROM npc_vendor where item=36919 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36919,0,0,2588);

-- Dreadstone (36928)
DELETE FROM npc_vendor where item=36928 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36928,0,0,2588);

-- Eye of Zul (36934)
DELETE FROM npc_vendor where item=36934 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36934,0,0,2588);

-- King's Amber (36922)
DELETE FROM npc_vendor where item=36922 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36922,0,0,2588);

-- Majestic Zircon (36925)
DELETE FROM npc_vendor where item=36925 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,36925,0,0,2588);

-- Inscribed Ornate Topaz (28363)
DELETE FROM npc_vendor where item=28363 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28363,0,0,99);

-- Potent Ornate Topaz (28123)
DELETE FROM npc_vendor where item=28123 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28123,0,0,99);

-- Bold Ornate Ruby (28362)
DELETE FROM npc_vendor where item=28362 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28362,0,0,95);

-- Gleaming Ornate Dawnstone (28120)
DELETE FROM npc_vendor where item=28120 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28120,0,0,95);

-- Runed Ornate Ruby (28118)
DELETE FROM npc_vendor where item=28118 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28118,0,0,95);

-- Smooth Ornate Dawnstone (28119)
DELETE FROM npc_vendor where item=28119 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,28119,0,0,95);

-- Design: Mystic Sun Crystal (41559)
DELETE FROM npc_vendor where item=41559 and entry=34040;
INSERT INTO npc_vendor VALUES
(34040,41559,0,0,2426);





