DELETE FROM item_required_target WHERE entry=33278;
INSERT INTO item_required_target (entry, TYPE, targetEntry)VALUES
('33278', '2', '24009'),
('33278', '2', '24010');

DELETE FROM spell_script_target WHERE entry=42793;
INSERT INTO spell_script_target (entry, TYPE, targetEntry)VALUES
('42793', '1', '24009'),
('42793', '1', '24010');

UPDATE creature_template SET ScriptName='spell_dummy_npc' WHERE entry IN(24009,24010);
