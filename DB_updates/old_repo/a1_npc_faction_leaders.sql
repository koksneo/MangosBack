-- King Varian Wrynn (King of Stormwind)
UPDATE creature_template SET ainame = 'EventAI' WHERE entry = 29611;
-- Tyrande Whisperwind (High Priestess of Elune)
UPDATE creature_template SET ainame = 'EventAI', flags_extra = 0 WHERE entry = 7999;

DELETE FROM creature_ai_scripts WHERE creature_id IN (29611,7999);
INSERT INTO creature_ai_scripts VALUES
('2961101','29611','4','0','100','0', '0','0','0','0', '39','50','0','0', '1','-99000','0','0', '0','0','0','0', 'King Varian Wrynn - Call for help'),
('2961102','29611','0','0','100','1', '10000','10000','30000','30000', '11','59688','1','0', '0','0','0','0', '0','0','0','0', 'King Varian Wrynn - heroic leap'),
('2961103','29611','0','0','100','1', '15000','15000','30000','30000', '11','41056','0','0', '0','0','0','0', '0','0','0','0', 'King Varian Wrynn - whirlwind'),
('2961104','29611','7','0','100','0', '0','0','0','0', '1','-98999','0','0', '0','0','0','0', '0','0','0','0', 'King Varian Wrynn - evade'),

('799901','7999','4','0','100','0', '0','0','0','0', '39','100','0','0', '1','-98998','0','0', '0','0','0','0', 'Tyrande Whisperwind - Call for help'),
('799902','7999','0','0','100','1', '1000','1000','30000','30000', '11','20687','4','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - Starfall'),
('799903','7999','0','0','100','1', '10000','10000','15000','15000', '11','20690','1','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - Moonfire'),
('799904','7999','9','0','100','1', '5','50','10000','10000', '11','20688','1','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - Slearing arrow'),
('799905','7999','9','0','100','1', '0','5','10000','10000', '11','20691','1','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - Cleave'),
('799906','7999','0','0','100','1', '30000','30000','30000','30000', '1','-98996','-98995','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - random speach'),
('799907','7999','6','0','100','0', '0','0','0','0', '1','-98997','0','0', '0','0','0','0', '0','0','0','0', 'Tyrande Whisperwind - death speach');



DELETE FROM creature_ai_texts WHERE entry IN (-99000,-98999,-98998,-98997,-98996,-98995);
INSERT INTO creature_ai_texts (`entry`,`content_default`,`sound`,`type`,`language`,`comment`) VALUES
(-99000,'Guards! Attention! We\'ve got visitors!',11277,6,0,'King Varian Wrynn - aggro'),
(-98999,'Is there noone left to test me?!',10293,6,0,'King Varian Wrynn - evade'),

(-98998,'Endu\'di Rifa!',5885,6,2,'Tyrande Whisperwind - aggro'),
(-98997,'NO! All... is... lost.',11068,6,0,'Tyrande Whisperwind - death'),
(-98996,'Give every ounce of strength! Do not despair!',11064,6,0,'Tyrande Whisperwind - fight random 1'),
(-98995,'Fight! Fight to your dying breath!',11063,6,0,'Tyrande Whisperwind - fight random 2');

-- King Magni Bronzebeard (Lord of Ironforge)
-- Prophet Velen
UPDATE creature_template SET ainame = 'EventAI' WHERE entry IN (2784,17468);

DELETE FROM creature_ai_scripts WHERE creature_id IN (2784,17468);
INSERT INTO creature_ai_scripts VALUES
('278401','2784','4','0','100','0', '0','0','0','0', '0','0','0','0', '1','-99999','-99998','0', '0','0','0','0', 'King Magni Bronzebeard - aggro'),
('278402','2784','2','0','100','0', '90','80','0','0', '39','50','0','0', '1','-99994','0','0', '0','0','0','0', 'King Magni Bronzebeard - Call for help'),
('278403','2784','0','0','100','1', '30000','30000','30000','30000', '1','-99999','-99998','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - random aggro yell'),
('278404','2784','5','0','100','1', '30000','30000','30000','30000', '1','-99996','-99997','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - random killed unit yell'),
('278405','2784','6','0','100','0', '0','0','0','0', '1','-99995','0','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - death'),
('278406','2784','0','0','100','1', '10000','10000','45000','45000', '11','19135','0','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - Avatar'),
('278407','2784','0','0','100','1', '20000','20000','45000','45000', '11','20686','0','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - Knockback'),
('278408','2784','0','0','100','1', '3000','3000','15000','15000', '11','20685','4','0', '0','0','0','0', '0','0','0','0', 'King Magni Bronzebeard - Storm Bolt'),

('1746801','17468','4','0','100','0', '0','0','0','0', '39','100','0','0', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Call for help'),
('1746802','17468','0','0','100','1', '12000','12000','30000','30000', '11','59701','0','0', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Holy Nova'),
('1746803','17468','0','0','100','1', '3000','3000','15000','15000', '11','33542','4','0', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Staff Strike'),
('1746804','17468','0','0','100','1', '6000','6000','15000','15000', '11','59703','1','0', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Smite'),
('1746805','17468','0','0','100','1', '15000','15000','30000','30000', '11','59700','1','0', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Holy Blast'),
('1746806','17468','2','0','100','1', '50','0','7000','7000', '11','59698','0','1', '0','0','0','0', '0','0','0','0', 'Prophet Velen - Prayer of Healing');

DELETE FROM creature_ai_texts WHERE entry IN (-99999,-99998,-99997,-99996,-99995,-99994);
INSERT INTO creature_ai_texts (`entry`,`content_default`,`sound`,`type`,`language`,`comment`) VALUES
(-99999,'Feel the fury of the mountain!',5896,6,0,'King Magni Bronzebeard - aggro1'),
(-99998,'For Khaz\'Modan!',5896,6,0,'King Magni Bronzebeard - aggro2'),
(-99997,'Press on! That\'s the way!',14245,6,0,'King Magni Bronzebeard - killed unit1'),
(-99996,'Keep it up now! Planty of death dealing for everyone!',14246,6,0,'King Magni Bronzebeard - killed unit2'),
(-99995,'Not yet! Nooot yeet....',14258,6,0,'King Magni Bronzebeard - death'),
(-99994,'Ha, that did it. Help\'s a-coming. Take this you glow-eying brute!',14277,6,0,'King Magni Bronzebeard call for help');



