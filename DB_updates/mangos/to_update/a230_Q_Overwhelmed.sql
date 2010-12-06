-- Quest Overwhelmed (12288)

UPDATE creature_template SET ScriptName='', AIName='EventAI' WHERE entry =27463;

DELETE FROM creature_ai_scripts WHERE creature_id = 27463;
INSERT INTO creature_ai_scripts (id, creature_id, event_type, event_inverse_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, action2_type, action2_param1, action2_param2, action2_param3, action3_type, action3_param1, action3_param2, action3_param3, COMMENT)VALUES
('2746301', '27463', '8', '0', '100', '1', '48812', '-1', '0', '0', '33', '27466', '6', '0', '1', '-274631', '-274632', '-274633', '0', '0', '0', '0', 'Kill Credit');

DELETE FROM item_required_target WHERE targetEntry=27463;
INSERT INTO item_required_target (entry, TYPE, targetEntry)VALUES
('37568', '1', '27463');

DELETE FROM creature_ai_texts WHERE entry IN(-274631,-274632,-274633);
INSERT INTO creature_ai_texts (entry, content_default, COMMENT)VALUES
(-274631,"Ahh.....better.",'wounded_skirmisher'),
(-274632,"Thank you, $R.",'wounded_skirmisher'),
(-274633,"Whoa - I nearly died there.",'wounded_skirmisher');
