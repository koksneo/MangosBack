-- Hira Snowdawn
DELETE FROM gossip_menu_option WHERE menu_id = 31238;
INSERT INTO gossip_menu_option VALUES
(31238, 0, 3, 'Train me', 5, 16, 0, 0, 0, 0, 0, NULL, 0,0,0, 0,0,0, 0,0,0),
(31238, 1, 2, 'I want to browse your goods.', 3, 128, 0, 0, 0, 0, 0, NULL, 15,80,1, 7,762,255, 0,0,0);

DELETE FROM npc_vendor WHERE entry = 31238;
INSERT INTO npc_vendor VALUES
('31238','49177','0','0','0');

DELETE FROM npc_trainer WHERE entry = 31238;
INSERT INTO npc_trainer VALUES
('31238','33389','40000','0','0','20'),
('31238','33392','500000','762','75','40'),
('31238','34092','2500000','762','150','60'),
('31238','34093','50000000','762','225','70');
