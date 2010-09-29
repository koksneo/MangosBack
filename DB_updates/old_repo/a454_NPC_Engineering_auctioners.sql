-- Engineering auctioners in Dalaran

-- Brassbolt Mechawrench (35594) Alliance
UPDATE creature_template SET
npcflag=npcflag|2097152
WHERE entry=35594;

-- Reginald Arcfire (35607) Horde
UPDATE creature_template SET
gossip_menu_id=10656,
npcflag=npcflag|2097152
WHERE entry=35607;

-- gossip 10656
DELETE FROM gossip_menu_option WHERE menu_id=10656;
INSERT INTO gossip_menu_option
(menu_id,id,option_icon,option_text,option_id,npc_option_npcflag,cond_1,cond_1_val_1,cond_1_val_2) VALUES
(10656,11,6,'GOSSIP_OPTION_AUCTIONEER',13,2097152,7,202,350);

# I could'nt find out special aura to make npc visible only for Horde and only for Alliance
# So this is only temporary solution :(

DELETE FROM creature_addon WHERE guid IN (85057,109626);
-- INSERT INTO creature_addon VALUES
-- (85057,0,65536,1,0,0,'60190 0'),
-- (109626,0,65536,1,0,0,'60191 0');


DELETE FROM creature WHERE id IN (35594,35607);
INSERT INTO creature VALUES
(85057,35594,571,1,1,0,0,5927.63,731.59,643.253,4.76475,180,0,0,5342,0,0,0),
(109626,35607,571,1,1,0,0,5931.29,731.346,643.174,4.74141,180,0,0,5342,0,0,0);
-- (109626,35607,571,1,1,0,0,5927.63,731.576,643.253,4.69494,180,0,0,5342,0,0,0);
# I commented old version db data

