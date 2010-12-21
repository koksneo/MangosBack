DELETE FROM npc_spellclick_spells WHERE npc_entry IN (31883,31893,31894,31895,31896,31897);
INSERT INTO npc_spellclick_spells VALUES
(31897,60123,0,0,0,2), -- rank 1
(31896,60123,0,0,0,2), -- rank 2
(31895,60123,0,0,0,2), -- rank 3
(31894,60123,0,0,0,2), -- rank 4
(31893,60123,0,0,0,2), -- rank 5
(31883,60123,0,0,0,2); -- rank 6

DELETE FROM creature_template_addon WHERE entry IN (31897,31896,31895,31894,31893,31883);
INSERT INTO creature_template_addon (entry,auras) VALUES
(31883,'59907 0'),
(31893,'59907 0'),
(31894,'59907 0'),
(31895,'59907 0'),
(31896,'59907 0'),
(31897,'59907 0');

