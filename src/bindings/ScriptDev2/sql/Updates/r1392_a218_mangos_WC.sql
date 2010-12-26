-- Wailing Caverns Encounters (TYPE_ data)
DELETE FROM creature_ai_scripts WHERE creature_id IN (3671,3669,3670,3673,3654) AND (action1_type = 34 OR action2_type = 34 OR action3_type = 34);
INSERT INTO creature_ai_scripts (`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `comment`)  VALUES
('3669','7','0','100','2','0','0','0','0','34','1','0','0','Lord Cobrahn - Data Type 0 on Evade'),
('3669','4','0','100','2','0','0','0','0','34','1','1','0','Lord Cobrahn - Data Type 1 on Aggro'),
('3669','6','0','100','2','0','0','0','0','34','1','3','0','Lord Cobrahn - Data Type 2 on Death'),

('3670','7','0','100','2','0','0','0','0','34','2','0','0','Lord Pythas - Data Type 0 on Evade'),
('3670','4','0','100','2','0','0','0','0','34','2','1','0','Lord Pythas - Data Type 1 on Aggro'),
('3670','6','0','100','2','0','0','0','0','34','2','3','0','Lord Pythas - Data Type 2 on Death'),

('3671','7','0','100','2','0','0','0','0','34','0','0','0','Lady Anacondra - Data Type 0 on Evade'),
('3671','4','0','100','2','0','0','0','0','34','0','1','0','Lady Anacondra - Data Type 1 on Aggro'),
('3671','6','0','100','2','0','0','0','0','34','0','3','0','Lady Anacondra - Data Type 2 on Death'),

('3673','7','0','100','2','0','0','0','0','34','3','0','0','Lord Serpentis - Data Type 0 on Evade'),
('3673','4','0','100','2','0','0','0','0','34','3','1','0','Lord Serpentis - Data Type 1 on Aggro'),
('3673','6','0','100','2','0','0','0','0','34','3','3','0','Lord Serpentis - Data Type 2 on Death'),

('3654','7','0','100','2','0','0','0','0','34','5','0','0','Mutanous the Devourer - Data Type 0 on Evade'),
('3654','4','0','100','2','0','0','0','0','34','5','1','0','Mutanous the Devourer - Data Type 1 on Aggro'),
('3654','6','0','100','2','0','0','0','0','34','5','3','0','Mutanous the Devourer - Data Type 2 on Death');

DELETE FROM spell_target_position WHERE id = 8136;
INSERT INTO spell_target_position VALUES
(8136,43,116.35,239.8,-95.08,3.1);

DELETE FROM npc_gossip WHERE npc_guid = 18675;
INSERT INTO npc_gossip VALUES
(18675,698);

UPDATE instance_template SET script = 'instance_wailing_caverns' WHERE map = 43;

-- disciple of naralex
UPDATE creature_template SET ScriptName = 'npc_disciple_of_naralex' WHERE entry = 3678;
