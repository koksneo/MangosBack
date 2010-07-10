####################################################################################
-- Add Missing gossip menu options into Tatiana (18774), Kalaen (18751) 
DELETE FROM gossip_menu_option WHERE menu_id IN (7815,7818);
INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,option_id,npc_option_npcflag) VALUES
(7815,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2),
(7815,1,3,'Train me.',5,16),
(7815,2,1,'I want to browse your goods.',3,128),
(7818,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2),
(7818,1,3,'Train me.',5,16),
(7818,2,1,'I want to browse your goods.',3,128);

####################################################################################
# Dual Talent Specialization - Achievement - patch provided by Steve_o 			
# Missing gossip_menu option in class trainers - patch provided by Grandres and Koksneo 
-- Note! I'm not sure of this patch.It is sometimes possible, that we can active 'Learn about Dual Talent Specialization' when we have already learned Dual Specialization.
-- Maybe the condition of this bug is CONDITION_NO_AURA
-- The gossip_menu text isn't propely now. I need source for this issue.


-- Dual Talent Specialization - Achievement provided by Steve_O
DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` = 9619;
INSERT INTO `achievement_criteria_requirement` (`criteria_id`,`type`,`value1`) VALUES ('9619','0','63624');



#########
#Paladin#
#########

-- Alliance 
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4469;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4470;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4471;
INSERT INTO gossip_menu_option VALUES
(4469,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4469,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4470,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4470,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4471,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4471,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4471 WHERE entry IN (16679,16680,20406,16681,23128);

-- Horde
DELETE FROM gossip_menu_option WHERE menu_id=8111;
INSERT INTO gossip_menu_option VALUES
(8111,0,3,'I would like to train further in the ways of the Light.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(8111,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(8111,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(8111,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);

UPDATE creature_template SET gossip_menu_id=8111 WHERE entry IN (16679,16680,20406,16681,23128);

#########
#Warlock#
#########
-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id=4667;
INSERT INTO gossip_menu_option VALUES
(4667,0,3,'I am interested in warlock training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4667,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4667,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4667,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4667 WHERE entry IN (461,5172,5171,5496,5173);

-- Horde
DELETE FROM gossip_menu_option WHERE menu_id IN (4609,2383);
INSERT INTO gossip_menu_option VALUES
(2383,0,3,'I am interested in warlock training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(2383,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(2383,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(2383,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4609,0,3,'I am interested in warlock training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4609,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4609,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4609,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=2383 WHERE entry IN (461,5172,5171,5496,5173);

########
#Shaman#
########

-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id IN (7377,7357,8110);;
INSERT INTO gossip_menu_option VALUES
(7377,0,3,'Teach me the ways of spirits.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(7377,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(7377,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(7377,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(7357,0,3,'Teach me the ways of spirits.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(7357,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(7357,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(7357,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(8110,0,3,'Teach me the ways of spirits.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(8110,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(8110,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(8110,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=7357 WHERE entry IN (17519,17520,23127);


-- Horde

DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4516;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4528;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4529;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=4530;
DELETE FROM gossip_menu_option WHERE id IN (2,3) AND menu_id=5123;
INSERT INTO gossip_menu_option VALUES
(4516,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4516,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4528,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4528,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4529,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4529,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4530,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4530,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(5123,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(5123,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);

#########
#Warrior# - I didn't find gossip "training" text ;( 
#########

-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id IN (4649,4683,4697);
INSERT INTO gossip_menu_option VALUES
(4649,0,3,'Train me.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4649,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4649,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4649,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4683,0,3,'Train me.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4683,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4683,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4683,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4697,0,3,'Train me.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4697,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4697,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4697,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4649 WHERE entry IN (4089,5113,5114,16771,17120,17504);

-- Horde
UPDATE creature_template SET gossip_menu_id=4649
WHERE entry IN (4593,4595,3042,4594,3408,3041,3043,3353,3354);


########
#Hunter# - I don't know how text_id should be in gossip_menu, so I've made it similar for Alliance and Horde = 4551
########

DELETE FROM gossip_menu_option WHERE menu_id IN (4011,4023,4524,4010,4506,4551);
INSERT INTO gossip_menu_option VALUES
(4011,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4011,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4011,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4011,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4010,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4010,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4010,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4010,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4023,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4023,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4023,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4023,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4524,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4524,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4524,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4524,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4506,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4506,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4506,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4506,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4551,0,3,'I seek training in the ways of the Hunter.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4551,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4551,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4551,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4551 WHERE entry IN (4138,4146,4205,5115,5116,5117,5515,5516,5517,16672,16673,16674,16738,17122,17505);

#######
#Druid#
#######

-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id IN(4571,1403);
INSERT INTO gossip_menu_option VALUES
(4571,0,3,'Train me',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4571,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4571,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4571,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(1403,0,3,'Train me',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(1403,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(1403,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(1403,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4571 WHERE entry IN (5506,5504,5505);

-- Horde
DELETE FROM gossip_menu_option WHERE menu_id IN (4607,4606,3921);
INSERT INTO gossip_menu_option VALUES
(4607,0,3,'Train me',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4607,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4607,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4607,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4606,0,3,'Train me',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4606,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4606,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4606,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(3921,0,3,'Train me',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(3921,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(3921,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(3921,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4607 WHERE entry IN (16655);

######
#Mage#
######

-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id IN (4552);
DELETE FROM gossip_menu_option WHERE menu_id IN (4485) AND id=3;
INSERT INTO gossip_menu_option VALUES
(4552,0,3,'I am interested in mage training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4552,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4552,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4552,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4485,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4552 WHERE entry IN (17105,5498,17514,16749,17513);

-- Horde
DELETE FROM gossip_menu_option WHERE menu_id IN (64,4537,4539,4538);
INSERT INTO gossip_menu_option VALUES
(64,0,3,'I am interested in mage training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(64,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(64,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(64,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4537,0,3,'I am interested in mage training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4537,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4537,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4537,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4539,0,3,'I am interested in mage training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4539,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4539,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4539,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4538,0,3,'I am interested in mage training.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4538,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4538,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4538,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=64 WHERE entry IN (16653,16652,16651,3047,3049,3048,23103);


########
#Priest#
########

-- Alliance
DELETE FROM gossip_menu_option WHERE menu_id IN (4691,4680,4666,4463);
INSERT INTO gossip_menu_option VALUES
(4691,0,3,'I seek more training in the priestly ways.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4691,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4691,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4691,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4680,0,3,'I seek more training in the priestly ways.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4680,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4680,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4680,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4666,0,3,'I seek more training in the priestly ways.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4666,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4666,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4666,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0),
(4463,0,3,'I seek more training in the priestly ways.',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4463,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4463,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4463,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4691 WHERE entry IN (5484,11397,16756,17510);
-- Horde
UPDATE creature_template SET gossip_menu_id=4691 WHERE entry IN (6018,6014,16658,16660,16659,3046,3045,3044,4606,4607,4608);

#######
#Rogue# - I don't know how text_id should be in gossip_menu, so I've made it similar for Alliance and Horde = 4659
#######

DELETE FROM gossip_menu_option WHERE menu_id=4659;
INSERT INTO gossip_menu_option VALUES
(4659,0,3,'Can you train me how to use rogue skills?',5,16,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4659,1,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,'',0,0,0,0,0,0,0,0,0),
(4659,2,0,'I wish to unlearn my talents.',16,16,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(4659,3,0,'Learn about Dual Talent Specialization.',1,16,0,0,6,0,10000000,'Are you sure you wish to purchase a Dual Talent Specialization?',15,40,1,11,63624,1,0,0,0);
UPDATE creature_template SET gossip_menu_id=4659 WHERE entry IN 
(918,3327,3328,3401,4163,4214,4215,4582,4583,4584,5165,5166,5167,13283,16684,16685,16686);
