-- Nexus

UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_telestra' WHERE `entry` IN (26731);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_anomalus' WHERE `entry` IN (26763);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'mob_chaotic_rift' WHERE `entry` IN (26918);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_ormorok' WHERE `entry` IN (26794);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'mob_crystal_spike' WHERE `entry` IN (27099);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'mob_crystalline_tangler' WHERE `entry` IN (32665);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE entry IN (26731,26763,26794,30510,30529,30532,26723,30540);

-- Nexus::Crazed Mana-Surge flags remove
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0' WHERE `entry` IN (26737,30519);

-- Drop withcout badges and quest items need to be added soon

UPDATE creature_template SET `lootid` = '30510' WHERE `entry` IN (30510);
UPDATE creature_template SET `lootid` = '30532' WHERE `entry` IN (30532);
UPDATE creature_template SET `lootid` = '30529' WHERE `entry` IN (30529);
UPDATE creature_template SET `lootid` = '30540' WHERE `entry` IN (30540);

DELETE FROM creature_loot_template WHERE entry IN (30510,30532,30529,30540);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Nexus::Telestra
('30510', '43852', '1.4', '0', '1', '1', '0', '0', '0'),
('30510', '37134', '0', '1', '1', '1', '0', '0', '0'),
('30510', '37139', '0', '1', '1', '1', '0', '0', '0'),
('30510', '37138', '0', '1', '1', '1', '0', '0', '0'),
('30510', '37135', '0', '1', '1', '1', '0', '0', '0'),

-- Nexus::Ormorok 
('30532', '43852', '1.4', '0', '1', '1', '0', '0', '0'),
('30532', '37153', '0', '1', '1', '1', '0', '0', '0'),
('30532', '37152', '0', '1', '1', '1', '0', '0', '0'),
('30532', '37155', '0', '1', '1', '1', '0', '0', '0'),
('30532', '37151', '0', '1', '1', '1', '0', '0', '0'),

-- Nexus::Anomalus
('30529', '43852', '1.4', '0', '1', '1', '0', '0', '0'),
('30529', '37150', '0', '1', '1', '1', '0', '0', '0'),
('30529', '37149', '0', '1', '1', '1', '0', '0', '0'),
('30529', '37144', '0', '1', '1', '1', '0', '0', '0'),
('30529', '37141', '0', '1', '1', '1', '0', '0', '0'),

-- Nexus::Kelistrasza
('30540', '43852', '1.4', '0', '1', '1', '0', '0', '0'),
('30540', '43102', '0', '3', '1', '1', '0', '0', '0'),
('30540', '41794', '10', '4', '1', '1', '0', '0', '0'),
('30540', '37169', '0', '2', '1', '1', '0', '0', '0'),
('30540', '37166', '0', '1', '1', '1', '0', '0', '0'),
('30540', '37167', '0', '1', '1', '1', '0', '0', '0'),
('30540', '37165', '0', '1', '1', '1', '0', '0', '0'),
('30540', '37162', '0', '1', '1', '1', '0', '0', '0'),
('30540', '37170', '0', '2', '1', '1', '0', '0', '0'),
('30540', '37172', '0', '2', '1', '1', '0', '0', '0'),
('30540', '37171', '0', '2', '1', '1', '0', '0', '0'),

-- Emblem of Heroism
('30510', '40752', '100', '0', '1', '1', '0', '0', '0'),
('30532', '40752', '100', '0', '1', '1', '0', '0', '0'),
('30529', '40752', '100', '0', '1', '1', '0', '0', '0'),
('30540', '40752', '100', '0', '1', '1', '0', '0', '0');
