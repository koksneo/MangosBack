update `creature_template` set `minhealth`='8600', `maxhealth`='8600' where `entry` in (31127, 31126, 28167, 28169);
update `creature_template` set `minhealth`='8600', `maxhealth`='8600' where `entry` in (10002, 10003, 10004, 10005);
update `creature_template` set `faction_A`='35', `faction_H`='35' where `entry` in (31127, 31126, 28167, 28169);
update `creature_template` set `faction_A`='35', `faction_H`='35' where `entry` in (10002, 10003, 10004, 10005);
update `creature_template` set `minhealth`='15000', `maxhealth`='15000' where `entry` in (27737);
update `creature_template` set `minhealth`='25000', `maxhealth`='25000' where `entry` in (31208);

DELETE FROM `creature` WHERE (`id`=27744);
DELETE FROM `creature` WHERE (`id`=26530);
DELETE FROM `creature` WHERE (`id`=26529);
DELETE FROM `creature` WHERE (`id`=26532);
DELETE FROM `creature` WHERE (`id`=26533);

update `creature_template` set `AIName`='', `Scriptname`='npc_arthas' where `entry` in (26499);
update `creature_template` set `AIName`='', `Scriptname`='dark_conversion' where `entry` in (31127, 31126, 28167, 28169);
update `creature_template` set `AIName`='', `Scriptname`='npc_patricia' where `entry` in (31028);
update `creature_template` set `AIName`='', `Scriptname`='npc_time_riftCS' where `entry` in (28409);
update `creature_template` set `AIName`='', `Scriptname`='boss_salramm' where `entry` in (26530);
update `creature_template` set `AIName`='', `Scriptname`='boss_meathook' where `entry` in (26529);
update `creature_template` set `AIName`='', `Scriptname`='boss_lord_epoch' where `entry` in (26532);
update `creature_template` set `AIName`='', `Scriptname`='boss_malganis' where `entry` in (26533);
update `instance_template` set `script` = 'instance_culling_of_stratholme' WHERE map=595;

-- Spawning Salramm in the instance --
INSERT INTO creature VALUES (4458725,26530,595,1,1,0,0,2174.32,1307.32,131.866,4.32264,25,0,0,337025,62535,0,0);
-- heroic version --
INSERT INTO creature VALUES (4458726,26530,595,2,1,0,0,2178.93,1307.89,131.526,4.12069,25,0,0,421281,62535,0,0);
-- Spawning Meathook in the instance --
INSERT INTO creature VALUES (4458739,26529,595,1,1,0,0,2351.43,1218.03,130.078,4.64621,25,0,0,337025,0,0,0);
-- heroic version --
INSERT INTO creature VALUES (4458740,26529,595,2,1,0,0,2350.42,1215.31,130.23,4.76314,25,0,0,421281,0,0,0);
-- Spawning Lord Epoch in the instance --
INSERT INTO creature VALUES (4458741,26532,595,1,1,0,1820,2446.25,1111.97,148.077,3.37779,25,0,0,337025,41690,0,0);
-- heroic version --
INSERT INTO creature VALUES (4458742,26532,595,2,1,0,1820,2446.17,1111.64,148.076,3.25517,25,0,0,421281,41690,0,0);
-- Spawning Malganis in the instance
INSERT INTO creature VALUES (4459981,26533,595,1,1,0,0,2298.33,1501.03,128.362,5.11213,25,0,0,404430,41690,0,0);
-- heroic version --
INSERT INTO creature VALUES (4459615,26533,595,2,1,0,0,2298.9,1502.32,128.361,5.21301,25,0,0,505538,41690,0,0);
 

update `creature` set `spawntimesecs`='3600' where `id` in (31127, 31126, 28167, 28169);

/*
DELETE FROM `creature` WHERE (`guid`=4456649);
DELETE FROM `creature` WHERE (`guid`=4456653);

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (4456649, 26499, 595, 1, 0, 0, 1920.87, 1287.12, 142.935, 6.25562, 25, 0, 0, 44100, 7988, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (4456653, 26497, 595, 1, 0, 0, 1895.48, 1292.66, 143.706, 0.023475, 25, 0, 0, 100800, 88140, 0, 0);
*/

DELETE FROM `gameobject_template` WHERE (`entry`=188686);
DELETE FROM `gameobject_template` WHERE (`entry`=187711);
DELETE FROM `gameobject_template` WHERE (`entry`=187723);

INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `castBarCaption`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (188686, 0, 7831, 'Doodad_LD_hidden_door_room01', '', 1375, 6553632, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `castBarCaption`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (187711, 0, 3631, 'Crusaders\' Square Gate', '', 1375, 6553632, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `castBarCaption`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (187723, 0, 3631, 'Crusaders\' Square Gate', '', 1375, 6553632, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

update `gameobject` set `state` = '1' where `id` in (187711);
update `gameobject` set `spawntimesecs` = '-604800', `state` = '0' where `id` in (190663);

UPDATE `creature` set `curhealth` = '8600' where `id`=28167;
UPDATE `creature` set `curhealth` = '8600' where `id`=28169;
UPDATE `creature` set `curhealth` = '15000' where `id`=27737;
UPDATE `quest_template` set `SpecialFlags` = '1' where `entry`=13151;

DELETE FROM `script_texts` WHERE `comment` = 26499;
DELETE FROM `script_texts` WHERE `entry` IN ('-1594071','-1594072','-1594073','-1594074','-1594075','-1594076','-1594077','-1594078','-1594079','-1594080','-1594081','-1594082','-1594083');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594084','-1594085','-1594086','-1594087','-1594088,','-1594089','-1594090','-1594091','-1594092','-1594093','-1594094','-1594095','-1594096');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594097','-1594098','-1594099','-1594100','-1594101','-1594102','-1594103','-1594104','-1594105','-1594106','-1594107','-1594108','-1594109');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594110','-1594111','-1594112','-1594113','-1594114','-1594115','-1594116','-1594117','-1594118','-1594119','-1594120','-1594121','-1594122');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594123','-1594124','-1594125','-1594126','-1594127','-1594128','-1594129','-1594130','-1594131','-1594132','-1594133','-1594134','-1594135');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594136','-1594137','-1594138','-1594139','-1594140','-1594141','-1594142','-1594143','-1594144','-1594145','-1594146','-1594147','-1594148');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594149','-1594150','-1594151','-1594152','-1594153','-1594154','-1594155','-1594156','-1594157','-1594158','-1594159','-1594160','-1594161');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594162','-1594163','-1594164','-1594165','-1594166','-1594167','-1594168','-1594169','-1594170','-1594171','-1594172','-1594173','-1594174');
DELETE FROM `script_texts` WHERE `entry` IN ('-1594175','-1594176');

#####################################################################################################################################

insert into `script_texts` (`entry`,`content_default`,`content_loc8`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
(-1594071, 'I\'m glad you could make it! Uther.','', 12828,0,0,1, '26499'),
(-1594072, 'Watch your tone, Boy. You may be the prince, but I\'m still your superrior as a paladin.','', 12839,0,0,25, '26499'),
(-1594073, 'As I could forget. Listen Uther, There is somthing about the plague you should know.','',12829,0,0,0, '26499'),
(-1594074, 'Oh no ... We are too late ... These people have ben infected. They may look fine now, but this is just mater of time before they will turn into the undead.','', 12830,0,0,1, '26499'),
(-1594075, 'What?','', 12840,0,0,5, '26499'),
(-1594076, 'This entire city must be purged.','', 12831,0,0,1, '26499'),
(-1594077, 'How can you even consider that? There got be some other way?','', 12841,0,0,1, '26499'),
(-1594078, 'Damn it Uther! As your future king, I order you to purge this city.','',12832,1,0,5, '26499'),
(-1594079, 'You are not my king yet boy.You know I whould obey that command ,even if you were!','',12842,1,0,22, '26499'),
(-1594080, 'Then I consider this as an act of treason.','', 12833,0,0,0, '26499'),
(-1594081, 'Treason? You lost your mind Arthas?','', 12843,0,0,5, '26499'),
(-1594082, 'Have I? Lord Uther. By my right of succession and suvenerity of my crown, I\'m here to releave you from command, and susspend your paladins from the service.','', 12834,0,0,1, '26499'),
(-1594083, 'Arthas? You can not just ...','', 12837,0,0,1, '26499'),
(-1594084, 'It\'s done! Those of you who have will to save this land follow me!, the rest of you get out of my sight.!','', 12835,0,0,0, '26499'),
(-1594085, 'You have crossed terible treshold, Arthas.','', 12844,0,0,25, '26499'),
(-1594086, 'Jaina?','', 12836,0,0,1, '26499'),
(-1594087, 'I\'m sorry,Arthas , I can\'t watch you do this.','', 12838,0,0,1, '26499'),
(-1594088, 'Take position here, I\'ll will lead a small force in stratholm and start the culling. We must contain and purge the infected people for the sake all of Lordaeron.','', 14327,0,0,1, '26499'),
(-1594089, 'Everyone looks ready! Remember these people are all infected with the plague, and they will die soon. We need to purge Stratholm and protect the remain of Lordaeron from the Scourge. Let\'s go.','', 14293,0,0,1, '26499'),
(-1594090, 'Greetings to you my lord. How we can help?','', 0,0,0,1, '26499'),
(-1594091, 'I can help you, only with a clean death.','', 14294,0,0,0, '26499'),
(-1594092, 'Help our prince has gone mad ...','', 0,0,0,0, '26499'),
(-1594093, 'This is only the beginning ..','', 14295,0,0,1, '26499'),
(-1594094, 'Yes. This is the beginning! I have ben waiting for you young Prince. Ahh, I\'m Mal\'Ganis.','', 14410,0,0,1, '26499'),
(-1594095, 'As you can see your people are now my people.I will now turn the city Household by household, Until the flame of life has ben snufed out ,forever ..','',14411,0,0,1, '26499'),
(-1594096, 'I won\'t allow it Mal\'Ganis. Beter these people die by my hand, than they become your slaves and serv you after death.','',14296,0,0,5, '26499'),
(-1594097, 'Mal\'Ganis will send some of his scourge minions to interfer with us. Those with you with strong stell and magic should go forward and destroy them. I will lead the remaining forces for purging stratholme of the infected.','',14885,0,0,1, '26499'),
(-1594098, 'Champions meet me at the Town Hall at once. We must take the fight with Mal\'Ganis !','',14297,0,0,1, '26499'),
(-1594099, 'Follow me, I know the way through.','',14298,0,0,1, '26499'),
(-1594100, 'Calm citizens. Everything is normal. To go home ... Aaaaaa ... What is it?','',0,0,0,1, '26499'),
(-1594101, 'Help ...','',0,0,0,0, '26499'),
(-1594102, 'Prince Arthas, what are you doing?','',0,0,0,0, '26499'),
(-1594103, 'Nenad ... You our prince, you\'re a defender of Lordaeron ....','',0,0,0,0, '26499'),
(-1594104, 'Paschady Milord ...','',0,0,0,0, '26499'),
(-1594105, 'What we have done to you?','',0,0,0,0, '26499'),
(-1594106, '<Lament>','',9676,0,0,18, '26499'),
(-1594107, 'Royal troops attacked us, who can escape ...','',0,1,0,0, '26499'),
(-1594108, 'What have you done? What is happening here?','',0,0,0,0, '26499'),
(-1594109, 'For what?','',0,0,0,0, '26499'),
(-1594110, 'Let\'s play?',13428,'',0,0,0, '26499'),
(-1594111, 'New toys.','',13429,1,0,0, '26499'),
(-1594112, 'This ... Not ... Fun ...','',13433,1,0,0, '26499'),
(-1594113, 'Boring ...','',13430,1,0,0, '26499'),
(-1594114, 'Why do not you move?','',13431,1,0,0, '26499'),
(-1594115, 'Come on, I did not finish ...','',13432,1,0,0, '26499'),
(-1594116, 'Prince Arthas Menethil, On this day, a powerful darknes has taken hold of your soul. The death that you had destined on others by visiting others,On this day will be your own.','',13408,0,0,0, '26499'),
(-1594117, 'I\'m doing what i have to , to save Lordaeron niether your words or actions will stop me.','',14309,0,0,5, '26499'),
(-1594118, 'We\'ll see about that young prince ...','',13409,0,0,0, '26499'),
(-1594119, '???????? ......','',13416,0,0,0, '26499'),
(-1594120, 'You have no future ...','',13413,1,0,0, '26499'),
(-1594121, 'The hour of our greatest triumph ..','',13414,1,0,0, '26499'),
(-1594122, 'You were destined to be defeated ...','',13415,1,0,0, '26499'),
(-1594123, 'Tic,tac,tic,tac...','',13410,1,0,0, '26499'),
(-1594124, 'Too slow ...','',13411,1,0,0, '26499'),
(-1594125, 'It\'s time to end ...','',13412,1,0,0, '26499'),
(-1594126, 'Do not touch me ...','',0,1,0,0, '26499'),
(-1594127, 'You are a monster, not the prince ...','',0,1,0,0, '26499'),
(-1594128, 'Run .....','',0,1,0,0, '26499'),
(-1594129, 'Remarcable late heroes of Lordaeron! It\'s time the dead ...','',0,1,0,0, '26499'),
(-1594130, 'Aaaaaa fun ....','',0,1,0,0, '26499'),
(-1594131, 'You are just a part of the master plan ...','',0,1,0,0, '26499'),
(-1594132, 'The fun is just beginning!','',0,1,0,0, '26499'),
(-1594133, 'Aaaa quality material ...','',0,1,0,0, '26499'),
(-1594134, 'Do not worry I\'ll find where you adapt ...','',0,1,0,0, '26499'),
(-1594135, 'I need a sample!','',0,1,0,0, '26499'),
(-1594136, 'So much power ... It will be my ....','',0,1,0,0, '26499'),
(-1594137, 'Your flesh attached to you!','',0,1,0,0, '26499'),
(-1594138, 'Familiarize yourself with my friends ...','',0,1,0,0, '26499'),
(-1594139, 'Living Stratholm Meet your savior ...','',0,1,0,0, '26499'),
(-1594140, 'Boom ... Ha-ha-ha-ha ...','',0,1,0,0, '26499'),
(-1594141, 'Blood ... Destruction ... Marvelous ...','',0,1,0,0, '26499'),
(-1594142, 'Yes! I am glad that I could get you through before the plague!','',14299,0,0,1, '26499'),
(-1594143, 'What is this sorrcery?','',14300,0,0,0, '26499'),
(-1594144, 'Mal\'Ganis it apers to have more thans scourge on his arsenal.We should do haste.','',14301,0,0,0, '26499'),
(-1594145, 'Again, that sorrcery, be prepared for anything.','',14302,0,0,0, '26499'),
(-1594146, 'Let\'s move on!.','',14303,0,0,0, '26499'),
(-1594147, 'Watch your backs they surrounded Us in this hole...','',14304,0,0,0, '26499'),
(-1594148, 'Mal\'Ganis is not making this easy ...','',14305,0,0,0, '26499'),
(-1594149, 'They are very persistent','',14306,0,0,0, '26499'),
(-1594150, 'What\'s more, he put me on the way?','',14307,0,0,0, '26499'),
(-1594151, 'The quickest way to Mal\'Ganis lays behind those bookshelf ahead','',14308,0,0,0, '26499'),
(-1594152, 'This will take only a moment.','',14310,0,0,0, '26499'),
(-1594153, 'I\' relieved that secret passage still works!','',14311,0,0,0, '26499'),
(-1594154, 'Let\'s go through this place as quick as possible. If the undead won\'t gonna kill us the fire might','',14312,0,0,0, '26499'),
(-1594155, 'Rest a moment here clean your luns, but be ready we must go soon again.','',14313,0,0,0, '26499'),
(-1594156, 'That\'s enough we have to move again , Mal\'Ganis awaits.','',14314,0,0,0, '26499'),
(-1594157,'Atlast , some luck! it looks like that Market Row not go cut by the fire. Mal\'Ganis it\'s supoused to be in Crussaders of squire, which is just ahead. Tell me whe you\'re ready to move forward.','',14315,0,0,0, '26499'),
(-1594158, 'Yes, Justice will be done.','',14316,0,0,0, '26499'),
(-1594159, 'It will be a worthy test of Prince Arthas!','',14413,1,0,0, '26499'),
(-1594160, 'Too easy ...','',14416,1,0,0, '26499'),
(-1594161, 'The dark lord is not happy with your intervention ...','',144107,1,0,0, '26499'),
(-1594162, 'I want Prince Arthas, not you ...','',14418,1,0,0, '26499'),
(-1594163, 'Anak Kiri ...','',14422,1,0,0, '26499'),
(-1594164, 'My pressure will sweep away the forces of King - Lich ...','',14423,1,0,0, '26499'),
(-1594165, 'Your death was in vain tiny mortal ...','',14424,1,0,0, '26499'),
(-1594166, 'Your time has came to an end ...','',14425,1,0,0, '26499'),
(-1594167, 'Arrrrhhhh ... I spent too much time in this weak litle shell ...','',14426,1,0,0, '26499'),
(-1594168, 'Earl Narath ... I Mal\'Ganis .... I am eternal ...','',14427,1,0,0, '26499'),
(-1594169, 'You will never defeat the Lich - King without my forces! I will have my revenge on him , and you...','',14429,1,0,0, '26499'),
(-1594170, 'We are going to finish this right now Mal\'Ganis. Just you and me ...','',14317,0,0,0, '26499'),
(-1594171, 'Your journey just begins young prince. Gather your forces and and meet me at the arctic land of, Northrend! It is there, we\'ll we shall setup the score beetwen us, It is there where your true destiny will unfold.','',14412,0,0,0, '26499'),
(-1594172, 'I will hunt you till the end of the earth if I have to... Did you heard me? To the end of erth!...','',14318,1,0,5, '26499'),
(-1594173, 'You performed well on this day! Anything that Mal\'Ganis left behind is yours take it as your reward. Now I need to begin some plans for an expedition into Northrend.','',14319,0,0,5, '26499'),
(-1594174, 'Relax!','',14414,1,0,0, '26499'),
(-1594175, 'You seam tired!','',14415,1,0,0, '26499'),
(-1594176, 'Enogh I have ben waisted my time here . I need to come by in my own world.','',14428,1,0,0, '26499');

DELETE FROM script_waypoint WHERE entry=26499;
INSERT INTO script_waypoint VALUES
   (26499, 0, 2099.876,1280.21,138.55, 0, 'WP1'),
   (26499, 1, 2120.757,1286.97,136.343, 30000, 'Summon Zombie'),
   (26499, 2, 2165.073,1279.338,133.40, 18000, 'Battle for Boss 1'),
   (26499, 3, 2186.441,1234.445,136.524, 5000, 'Open The Gate 01'),
   (26499, 4, 2210.385,1207.550,136.259, 0, 'WP2'),
   (26499, 5, 2243.594,1177.705,137.144, 0, 'WP3'),
   (26499, 6, 2286.883,1177.262,137.631, 0, 'Summon Zombie and Meathook'),
   (26499, 7, 2320.374,1179.954,133.926, 0, 'WP4 Meathook Order'),
   (26499, 8, 2354.626,1192.099,130.535, 15000, 'Battle For Boss 2 and Summon Zombie'),
   (26499, 9, 2390.256,1204.235,134.125, 0, 'House WP1'),
   (26499, 10, 2442.023,1219.205,133.999, 0, 'House WP2'),
   (26499, 11, 2446.945,1192.559,149.076, 0, 'House WP3'),
   (26499, 12, 2431.264,1189.590,149.076, 0, 'House WP4'),
   (26499, 13, 2418.487,1196.059,148.076, 0, 'House WP5'),
   (26499, 14, 2401.221,1191.705,148.076, 0, 'House WP6'),
   (26499, 15, 2417.584,1121.026,148.082, 0, 'House WP7'),
   (26499, 16, 2426.099,1107.088,148.076, 0, 'House WP8 and Summon Boss 3'),
   (26499, 17, 2427.063,1107.298,148.076, 20000, 'House WP9 Cinematic'),
   (26499, 18, 2428.013,1107.508,148.076, 6000, 'House WP10 Arthas Dialog'),
   (26499, 19, 2444.682,1111.705,148.076, 15000, 'Battle For Boss 3'),
   (26499, 20, 2457.133,1120.941,150.008, 0, 'House WP11'),
   (26499, 21, 2459.694,1127.012,150.008, 0, 'House WP12'),
   (26499, 22, 2469.617,1122.274,150.008, 0, 'House WP13'),
   (26499, 23, 2470.437,1122.794,150.008, 3000, 'Open Shkaf'),
   (26499, 24, 2471.662,1123.077,150.035, 3000, 'Shkaf Dialog'),
   (26499, 25, 2483.183,1125.042,149.905, 0, 'Secret WP1'),
   (26499, 26, 2487.867,1099.760,144.858, 0, 'Secret WP2'),
   (26499, 27, 2498.270,1101.929,144.599, 0, 'Secret WP3'),
   (26499, 28, 2492.114,1128.238,139.967, 0, 'Secret WP4'),
   (26499, 29, 2500.286,1130.183,139.982, 0, 'Room WP1'),
   (26499, 30, 2503.010,1119.241,139.978, 0, 'Room WP2'),
   (26499, 31, 2517.820,1122.645,132.066, 0, 'Room WP3'),
   (26499, 32, 2540.479,1129.061,130.868, 7000, 'Fire Street WP1'),
   (26499, 33, 2568.619,1157.794,126.906, 0, 'Fire Street WP2'),
   (26499, 34, 2556.074,1222.058,125.412, 20000, 'Fire Street WP3'),
   (26499, 35, 2521.531,1295.209,130.573, 0, 'Fire Street WP4'),
   (26499, 36, 2504.362,1348.667,132.944, 0, 'Fire Street WP5'),
   (26499, 37, 2450.594,1431.544,131.361, 0, 'Fire Street WP6'),
   (26499, 38, 2353.485,1404.839,128.531, 0, 'Knights Street WP1'),
   (26499, 39, 2329.882,1406.273,128.013, 0, 'Knights Street WP2'),
   (26499, 40, 2329.882,1406.273,128.013, 12000, 'Knights Street WP3'),
   (26499, 41, 2327.391,1412.475,127.692, 180000000, 'Knights Street WP4'),
   (26499, 42, 2329.882,1406.273,128.013, 0, 'Knights Street WP5');   -- Pustishka --


