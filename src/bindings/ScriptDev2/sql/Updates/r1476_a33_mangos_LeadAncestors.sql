UPDATE creature_template SET ScriptName = 'mob_elder' WHERE entry IN (25397,25398,25399);

/* additional SQL data for DB development
delete FROM creature WHERE id IN (25397,25398,25399);
insert into creature values
-- NPC_ELDER_KESUK (orginal UDB guid)
('100832','25397','571','1','1','20559','0','3655.54','5617.75','33.8306','2.02428','300','0','0','9610','3309','0','0'),
-- NPC_ELDER_SAGANI (my guid)
('1049946','25398','571','1','1','20559','0','3567.32','5505.58','27.012','0.839093','300','0','0','1','3231','0','0'),
-- NPC_ELDER_TAKRET (my guid)
('1049945','25399','571','1','1','20559','0','3683.96','5569.8','34.8291','5.52323','300','0','0','1','3231','0','0');

DELETE FROM creature_addon WHERE guid IN (1049946,1049945);
insert into creature_addon values
('1049946','0','0','1','0','0',NULL),
('1049945','0','0','1','0','0',NULL);*/
