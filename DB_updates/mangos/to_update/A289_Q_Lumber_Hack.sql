-- Support for Refurbished Shredder related to quest Lumber Hack (12050)

DELETE FROM `npc_spellclick_spells` WHERE npc_entry IN (27061);
INSERT INTO `npc_spellclick_spells` VALUES (27061, 67373, 12050, 1, 12050, 1);


REPLACE INTO creature_template_addon VALUES (27061, 0, 0, 0, 0, 0,0, 55, NULL, NULL);
REPLACE INTO vehicle_data VALUES (55, 2, 47938,47921, 47939, 0, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO vehicle_seat_data VALUES (922, 1);

