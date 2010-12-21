-- ===== 
-- Intro
-- =====

-- Horde

-- The Argent Tournament
UPDATE quest_template SET NextQuestInChain = 13829 WHERE entry = 13668;
-- Mastery Of Melee,Mastery Of The Charge,Mastery Of The Shield-Breaker
UPDATE quest_template SET PrevQuestId = 13668, NextQuestId = 13678, ExclusiveGroup = -13829 WHERE entry IN (13829,13838,13839);

-- Alliance

-- The Argent Tournament
UPDATE quest_template SET NextQuestInChain = 13828 WHERE entry = 13667;
-- Mastery Of Melee,Mastery Of The Charge,Mastery Of The Shield-Breaker
UPDATE quest_template SET PrevQuestId = 13667, NextQuestId = 13672, ExclusiveGroup = -13828 WHERE entry IN (13828,13837,13835);

-- ==================
-- Part One: Aspirant
-- ==================

-- Horde

-- Up To The Challenge
UPDATE quest_template SET PrevQuestId = 13829, NextQuestInChain = 13680 WHERE entry = 13678;
-- The Aspirant's Challenge
UPDATE quest_template SET PrevQuestId = 13678 WHERE entry = 13680;
-- A blade Fit For A Champion 
UPDATE quest_template SET PrevQuestId = -13678, ExclusiveGroup = 13673 WHERE entry = 13673;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13678, ExclusiveGroup = 13673 WHERE entry = 13674;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13678, ExclusiveGroup = 13673 WHERE entry = 13675;
-- Training In The Field
UPDATE quest_template SET PrevQuestId = -13678 WHERE entry = 13676;
-- Learning The Reins
UPDATE quest_template SET PrevQuestId = -13678 WHERE entry = 13677;

-- Alliance

-- Up To The Challenge
UPDATE quest_template SET PrevQuestId = 13828, NextQuestInChain = 13679 WHERE entry = 13672;
-- The Aspirant's Challenge
UPDATE quest_template SET PrevQuestId = 13672 WHERE entry = 13679;
-- A blade Fit For A Champion 
UPDATE quest_template SET PrevQuestId = -13672, ExclusiveGroup = 13666 WHERE entry = 13666;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13672, ExclusiveGroup = 13666 WHERE entry = 13669;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13672, ExclusiveGroup = 13666 WHERE entry = 13670;
-- Training In The Field
UPDATE quest_template SET PrevQuestId = -13672 WHERE entry = 13625;
-- Learning The Reins
UPDATE quest_template SET PrevQuestId = -13672 WHERE entry = 13671;

-- =================
-- Part Two: Valiant
-- =================

-- Horde

UPDATE quest_template SET PrevQuestId = 13794 WHERE entry IN (13707,13708,13711,13709,13710);
UPDATE quest_template SET RequiredRaces = 688 WHERE entry = 13707;
UPDATE quest_template SET RequiredRaces = 562 WHERE entry = 13708;
UPDATE quest_template SET RequiredRaces = 178 WHERE entry = 13711;
UPDATE quest_template SET RequiredRaces = 658 WHERE entry = 13709;
UPDATE quest_template SET RequiredRaces = 674 WHERE entry = 13710;

-- Orgrimmar

-- A Valiant Of Orgrimmar
UPDATE quest_template SET RequiredRaces = 2, PrevQuestId = 13680, NextQuestId = 13697 WHERE entry = 13691;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13726 WHERE entry = 13697;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13697, NextQuestInChain = 13736 WHERE entry = 13726;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13762 WHERE entry = 13762;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13762 WHERE entry = 13763;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13762 WHERE entry = 13764;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13765 WHERE entry = 13765;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13767 WHERE entry = 13767;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13697, ExclusiveGroup = 13856 WHERE entry = 13856;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13697 WHERE entry = 13707;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN (13697,13726,13762,13763,13764,13765,13767,13856);

-- Sen'jin

-- A Valiant Of Sen'jin
UPDATE quest_template SET RequiredRaces = 128, PrevQuestId = 13680, NextQuestId = 13719 WHERE entry = 13693;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13727 WHERE entry = 13719;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13719, NextQuestInChain = 13737 WHERE entry = 13727;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13762 WHERE entry = 13768;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13762 WHERE entry = 13769;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13762 WHERE entry = 13770;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13765 WHERE entry = 13771;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13767 WHERE entry = 13772;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13719, ExclusiveGroup = 13856 WHERE entry = 13857;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13719 WHERE entry = 13708;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN (13719,13727,13768,13769,13770,13771,13772,13857);

-- Thunder Bluff

-- A Valiant Of Thunder Bluff
UPDATE quest_template SET RequiredRaces = 32, PrevQuestId = 13680, NextQuestId = 13720 WHERE entry = 13694;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13728 WHERE entry = 13720;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13720, NextQuestInChain = 13738 WHERE entry = 13728;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13762 WHERE entry = 13773;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13762 WHERE entry = 13774;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13762 WHERE entry = 13775;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13765 WHERE entry = 13776;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13767 WHERE entry = 13777;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13720, ExclusiveGroup = 13856 WHERE entry = 13858;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13720 WHERE entry = 13709;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN (13720,13728,13773,13774,13775,13776,13777,13858);

-- Undercity

-- A Valiant Of Undercity
UPDATE quest_template SET RequiredRaces = 16, PrevQuestId = 13680, NextQuestId = 13721 WHERE entry = 13695;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13729 WHERE entry = 13721;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13721, NextQuestInChain = 13739 WHERE entry = 13729;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13762 WHERE entry = 13778;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13762 WHERE entry = 13779;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13762 WHERE entry = 13780;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13765 WHERE entry = 13781;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13767 WHERE entry = 13782;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13721, ExclusiveGroup = 13856 WHERE entry = 13860;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13721 WHERE entry = 13710;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN (13721,13729,13778,13779,13780,13781,13782,13860);

-- Silvermoon City

-- A Valiant Of Silvermoon
UPDATE quest_template SET RequiredRaces = 512, PrevQuestId = 13680, NextQuestId = 13722 WHERE entry = 13696;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13731 WHERE entry = 13722;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13722, NextQuestInChain = 13740 WHERE entry = 13731;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13762 WHERE entry = 13783;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13762 WHERE entry = 13784;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13762 WHERE entry = 13785;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13765 WHERE entry = 13786;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13767 WHERE entry = 13787;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13722, ExclusiveGroup = 13856 WHERE entry = 13859;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13722 WHERE entry = 13711;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry IN (13722,13731,13783,13784,13785,13786,13787,13859);

-- Aliance

UPDATE quest_template SET PrevQuestId = 13794 WHERE entry IN (13593,13706,13703,13704,13705);
UPDATE quest_template SET RequiredRaces = 77 WHERE entry = 13705;
UPDATE quest_template SET RequiredRaces = 1097 WHERE entry = 13703;
UPDATE quest_template SET RequiredRaces = 1100 WHERE entry = 13593;
UPDATE quest_template SET RequiredRaces = 1093 WHERE entry = 13706;
UPDATE quest_template SET RequiredRaces = 1037 WHERE entry = 13704;

-- Stormwind City

-- A Valiant Of Stormwind
UPDATE quest_template SET RequiredRaces = 1, PrevQuestId = 13679, NextQuestId = 13718 WHERE entry = 13684;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13699 WHERE entry = 13718;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13718, NextQuestInChain = 13702 WHERE entry = 13699;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13603 WHERE entry = 13603;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13603 WHERE entry = 13600;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13603 WHERE entry = 13616;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13592 WHERE entry = 13592;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13665 WHERE entry = 13665;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13718, ExclusiveGroup = 13847 WHERE entry = 13847;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13718 WHERE entry = 13593;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN (13718,13699,13603,13600,13616,13592,13665,13847);

-- Darnassus

-- A Valiant Of Darnassus                 
UPDATE quest_template SET RequiredRaces = 8, NextQuestId = 13717, PrevQuestId = 13679 WHERE entry = 13689;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13725 WHERE entry = 13717;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13717, NextQuestInChain = 13735 WHERE entry = 13725;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13603 WHERE entry = 13757;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13603 WHERE entry = 13758;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13603 WHERE entry = 13759;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13592 WHERE entry = 13760;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13665 WHERE entry = 13761;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13717, ExclusiveGroup = 13847 WHERE entry = 13855;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13717 WHERE entry = 13706;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN (13717,13725,13757,13758,13759,13760,13761,13855);

-- Ironforge

-- A Valiant Of Ironforge       
UPDATE quest_template SET RequiredRaces = 4, PrevQuestId = 13679, NextQuestId = 13714 WHERE entry = 13685;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13713 WHERE entry = 13714;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13714, NextQuestInChain = 13732 WHERE entry = 13713;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13603 WHERE entry = 13741;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13603 WHERE entry = 13742;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13603 WHERE entry = 13743;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13592 WHERE entry = 13744;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13665 WHERE entry = 13745;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13714, ExclusiveGroup = 13847 WHERE entry = 13851;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13714 WHERE entry = 13703;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN (13714,13713,13741,13742,13743,13744,13745,13851);

-- Gnomeregan

-- A Valiant Of Gnomeregan              
UPDATE quest_template SET RequiredRaces = 64, PrevQuestId = 13679, NextQuestId = 13715 WHERE entry = 13688;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13723 WHERE entry = 13715;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13715, NextQuestInChain = 13733 WHERE entry = 13723;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13603 WHERE entry = 13746;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13603 WHERE entry = 13747;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13603 WHERE entry = 13748;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13592 WHERE entry = 13749;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13665 WHERE entry = 13750;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13715, ExclusiveGroup = 13847 WHERE entry = 13852;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13715 WHERE entry = 13704;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN (13715,13723,13746,13747,13748,13749,13750,13852);

-- Exodar

-- A Valiant Of The Exodar
UPDATE quest_template SET RequiredRaces = 1024, PrevQuestId = 13679, NextQuestId = 13716 WHERE entry = 13690;
-- The Valiant's Charge
UPDATE quest_template SET PrevQuestId = 0, NextQuestInChain = 13724 WHERE entry = 13716;
-- The Valiant's Challenge
UPDATE quest_template SET PrevQuestId = 13716, NextQuestInChain = 13734 WHERE entry = 13724;
-- A Blade Fit For A Champion
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13603 WHERE entry = 13752;
-- A Worthy Weapon
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13603 WHERE entry = 13753;
-- The Edge Of Winter
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13603 WHERE entry = 13754;
-- A Valiant's Field Training
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13592 WHERE entry = 13755;
-- The Grand Melee
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13665 WHERE entry = 13756;
-- At The Enemy's Gates
UPDATE quest_template SET PrevQuestId = -13716, ExclusiveGroup = 13847 WHERE entry = 13854;

-- Update Required Races to make Crusader title available
UPDATE quest_template SET NextQuestId = 13716 WHERE entry = 13705;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry IN (13716,13724,13752,13753,13754,13755,13756,13854);

-- ====================
-- Part Three: Champion
-- ====================

-- A Champion Rises
UPDATE quest_template SET NextQuestInChain = 13794, NextQuestId = 13794 WHERE entry IN (13702,13732,13733,13734,13735,13736,13737,13738,13739,13740);
-- Eadric the Pure
UPDATE quest_template SET PrevQuestId = 0 WHERE entry = 13794;
-- The Scourgebane
UPDATE quest_template SET PrevQuestId = 0,PrevQuestId = 13794 WHERE entry = 13795;
-- Contributin' To The Cause
UPDATE quest_template SET PrevQuestId = 0,PrevQuestId = 13794 WHERE entry = 13846;

-- ============================
-- Champion's Seal Daily Quests
-- ============================

-- Horde:

-- Among the Champions
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13811, RequiredRaces = 690 WHERE entry = 13811;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13811, MinLevel= 81, RequiredRaces = 690 WHERE entry = 13814;
-- Battle Before The Citadel
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13862, RequiredRaces = 690 WHERE entry = 13862;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13862, MinLevel= 81, RequiredRaces = 690 WHERE entry = 13863;
-- Taking Battle To The Enemy
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13810, RequiredRaces = 690 WHERE entry = 13810;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13810, MinLevel= 81, RequiredRaces = 690 WHERE entry = 13813;
-- Threat From Above
UPDATE quest_template SET PrevQuestId = 13664, ExclusiveGroup = 13809, RequiredRaces = 690 WHERE entry = 13809;
UPDATE quest_template SET PrevQuestId = 13664, ExclusiveGroup = 13809, MinLevel= 81, RequiredRaces = 690 WHERE entry = 13812;

-- Alliance:

-- Among the Champions
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13790, RequiredRaces = 1101 WHERE entry = 13790;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13790, MinLevel= 81, RequiredRaces = 1101 WHERE entry = 13793;
-- Battle Before The Citadel
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13861, RequiredRaces = 1101 WHERE entry = 13861;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13861, MinLevel= 81, RequiredRaces = 1101 WHERE entry = 13864;
-- Taking Battle To The Enemy
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13789, RequiredRaces = 1101 WHERE entry = 13789;
UPDATE quest_template SET PrevQuestId = 13794, ExclusiveGroup = 13789, MinLevel= 81, RequiredRaces = 1101 WHERE entry = 13791;
-- Threat From Above
UPDATE quest_template SET PrevQuestId = 13664, ExclusiveGroup = 13682, RequiredRaces = 1101 WHERE entry = 13682;
UPDATE quest_template SET PrevQuestId = 13664, ExclusiveGroup = 13682, MinLevel= 81, RequiredRaces = 1101 WHERE entry = 13788;                                                              

-- The Fate Of The Fallen
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14107;
-- Deathspeaker Kharos
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14105;
-- Drottinn Hrothgar
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14101;
-- Get Kraken!
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14108;
-- Mistcaller Yngvar
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14102;
-- Ornolf The Scarred
UPDATE quest_template SET PrevQuestId = 13794 WHERE entry = 14104;

UPDATE quest_template SET ExclusiveGroup = 14105 WHERE entry IN (14105,14101,14102,14104);
UPDATE quest_template SET ExclusiveGroup = 14108 WHERE entry IN (14108,14107);

-- ========================================================================
-- Daily Quests after completing The Sunreavers/Silver Covernant achievement 
-- ========================================================================

-- Horde
UPDATE quest_template SET RequiredMinRepFaction = 1124, RequiredMinRepValue = 42000, PrevQuestId = 13794 WHERE entry IN (14143,14136,14140,14144,14142,14145,14141,14092);
UPDATE quest_template SET ExclusiveGroup = 14143 WHERE entry IN (14143,14136,14140,14144);
UPDATE quest_template SET ExclusiveGroup = 14092 WHERE entry IN (14092,14141,14145); 

-- Alliance
UPDATE quest_template SET RequiredMinRepFaction = 1094, RequiredMinRepValue = 42000, PrevQuestId = 13794 WHERE entry IN (14074,14152,14080,14077,14096,14112,14090,14076);
UPDATE quest_template SET ExclusiveGroup = 14074 WHERE entry IN (14074,14152,14080,14077);
UPDATE quest_template SET ExclusiveGroup = 14076 WHERE entry IN (14076,14090,14112);

-- Gormok Wants His Snobolds
UPDATE quest_template SET ReqCreatureOrGOId2 = 29618, ReqSpellCast2 = 66474 WHERE entry IN (14141,14090);
-- The Light's Mercy
UPDATE quest_template SET ReqSpellCast1 = 66390 WHERE entry IN (14144,14077);

-- ======================
-- The Black Knight Chain 
-- ======================

UPDATE quest_template SET PrevQuestId = 13794, NextQuestId = 13641, NextQuestInChain = 13641 WHERE entry IN (13633, 13634);
UPDATE quest_template SET NextQuestInChain = 13643 WHERE entry = 13641;
UPDATE quest_template SET NextQuestInChain = 13654, PrevQuestId = 13641 WHERE entry = 13643;
UPDATE quest_template SET NextQuestInChain = 13663, PrevQuestId = 13643 WHERE entry = 13654;
UPDATE quest_template SET NextQuestInChain = 13664, PrevQuestId = 13654 WHERE entry = 13663;
UPDATE quest_template SET NextQuestInChain = 14016, PrevQuestId = 13663 WHERE entry = 13664;
UPDATE quest_template SET NextQuestInChain = 14017, PrevQuestId = 13664 WHERE entry = 14016;
UPDATE quest_template SET PrevQuestId = 14016 WHERE entry = 14017;

-- The Black Knight's Orders 
UPDATE quest_template SET SrcItemId = 0, SrcItemCount = 0, ReqSourceId4 = 0, ReqCreatureOrGOId1 = 0, ReqCreatureOrGOCount1 = 0 WHERE entry = 13663;

-- ==================
-- Hrothgar's Landing
-- ==================

-- Battle Plans Of The Kvaldir
DELETE FROM quest_template WHERE entry = 24442;
INSERT INTO quest_template (entry,method,zoneorsort,minlevel,questlevel,QuestFlags,SrcItemId,SrcItemCount,Title,Details,Objectives,OfferRewardText,RequestItemsText,ReqItemId1,ReqItemId2,ReqItemCount1,ReqItemCount2,RewRepFaction1,RewRepValue1,RewOrReqMoney,RewMoneyMaxLevel) VALUES (24442,2,-241,77,80,128,49676,1,'Battle Plans Of The Kvaldir','Looking over the captured attack plans, you find a map of the Eastern Kingdoms and Kalimdor with major settlements marked. Reading over the orders, you learn that Kvaldir captains have drafted plans for a series of devastating raids.

According to the orders, the attacks are to begin after Mistcaller Yngvar "consults the Heart of the Mists." Perhaps you could delay the attacks by capturing the omen from the Mistcaller\'s Cave on the western side of Hrothgar\'s Landing and notify Justicar Mariel Trueheart.','Recover the Heart of the Mists and bring it and the Kvaldir Attack Plans to Justicar Mariel Trueheart at the Argent Tournament Grounds.','<Mariel accepts the orders and the captured seeing crystal and examines both.>

Good work, $N, and quick thinking. I\'m sure the theft of this trinket won\'t slow them down for long, but I think you\'ve bought us time to warn the leaders of the Horde and Alliance about the impending attacks.','Yes?',49676,49678,1,1,1106,250,74000,132300);


##############################################################
##################### N P Cs #################################
##############################################################

UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 10080, maxhealth = 10080, minmana = 8814, maxmana = 8814, rank =0 WHERE entry =35573;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =35576;
UPDATE creature_template SET minlevel =79, maxlevel =79, minhealth = 12175, maxhealth = 12175, minmana = 3893, maxmana = 3893, rank =0 WHERE entry =35578;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 10080, maxhealth = 10080, minmana = 8814, maxmana = 8814, rank =0 WHERE entry =35475;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana = 39940, maxmana = 39940, rank =3 WHERE entry =36120;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana =0, maxmana =0, rank =3 WHERE entry =36121;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 322560, maxhealth = 322560, minmana = 634608, maxmana = 634608, rank =3 WHERE entry =36119;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana =0, maxmana =0, rank =3 WHERE entry =36122;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 322560, maxhealth = 322560, minmana = 634608, maxmana = 634608, rank =3 WHERE entry =36124;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 3722, maxhealth = 3722, minmana = 3561, maxmana = 3561, rank =0 WHERE entry =35290;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =35292;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =34771;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =34914;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =34772;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 3486250, maxhealth = 3486250, minmana =0, maxmana =0, rank =3 WHERE entry =35469;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =35483;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 5787175, maxhealth = 5787175, minmana = 4258, maxmana = 4258, rank =3 WHERE entry =36065;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 5787175, maxhealth = 5787175, minmana = 4258, maxmana = 4258, rank =3 WHERE entry =36066;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =36101;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =36102;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 37800, maxhealth = 37800, minmana =0, maxmana =0, rank =1 WHERE entry =35984;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =35462;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =35467;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =34794;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =34880;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =34912;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 50000, maxhealth = 50000, minmana =0, maxmana =0, rank =0 WHERE entry =35117;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 322560, maxhealth = 322560, minmana = 634608, maxmana = 634608, rank =3 WHERE entry =36114;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 4652, maxhealth = 4652, minmana =0, maxmana =0, rank =0 WHERE entry =35291;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana = 599100, maxmana = 599100, rank =3 WHERE entry =36116;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 3486250, maxhealth = 3486250, minmana =0, maxmana =0, rank =3 WHERE entry =35470;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =35499;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 3486250, maxhealth = 3486250, minmana =0, maxmana =0, rank =1 WHERE entry =35482;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =34882;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =34885;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =35094;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 11667, maxhealth = 11667, minmana =0, maxmana =0, rank =0 WHERE entry =35344;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana = 39940, maxmana = 39940, rank =3 WHERE entry =36109;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 322560, maxhealth = 322560, minmana = 634608, maxmana = 634608, rank =3 WHERE entry =36108;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =35293;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 403200, maxhealth = 403200, minmana =0, maxmana =0, rank =3 WHERE entry =36118;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =1 WHERE entry =35476;
UPDATE creature_template SET minlevel =78, maxlevel =78, minhealth = 11770, maxhealth = 11770, minmana =0, maxmana =0, rank =0 WHERE entry =35579;
UPDATE creature_template SET minlevel =79, maxlevel =79, minhealth = 12175, maxhealth = 12175, minmana = 3893, maxmana = 3893, rank =0 WHERE entry =35577;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana = 3994, maxmana = 3994, rank =0 WHERE entry =35575;
UPDATE creature_template SET minlevel =80, maxlevel =80, minhealth = 12600, maxhealth = 12600, minmana =0, maxmana =0, rank =0 WHERE entry =34881;
UPDATE creature_template SET minlevel =72, maxlevel =73, minhealth = 9610, maxhealth =9940, minmana =0, maxmana =0, rank=0 WHERE entry =34788;
UPDATE creature_template SET minlevel =75, maxlevel =75, minhealth = 10635, maxhealth = 10635, minmana =0, maxmana =0, rank =0 WHERE entry =35472;
UPDATE creature_template SET minlevel =25, maxlevel =25, minhealth = 699, maxhealth = 699, minmana =0, maxmana =0, rank =0 WHERE entry =36069;

-- Stormwind, Ironforge, Gnomeregan, Silvermoon, Thunder Bluff,   
-- Orgrimmar, Sen'Jin, Undercity, Exodar, Darnassus champions  
UPDATE creature_template SET npcflag=0, spell1=63010, spell2=65147, flags_extra=2, faction_A=35, faction_H=35 WHERE entry IN (33747,33740,33746,33748,33745,33749,33739,33738,33744);

-- Fill current mana with propper random values
UPDATE creature SET 
curhealth = (SELECT FLOOR(RAND(1)*(maxhealth - minhealth) + minhealth) FROM creature_template WHERE creature.id = creature_template.entry)
WHERE curhealth < (SELECT minhealth FROM creature_template WHERE creature.id = creature_template.entry);

UPDATE creature SET 
curmana = (SELECT FLOOR(RAND(1)*(maxmana - minmana) + minmana) FROM creature_template WHERE creature.id = creature_template.entry)
WHERE curmana < (SELECT minmana FROM creature_template WHERE creature.id = creature_template.entry);
