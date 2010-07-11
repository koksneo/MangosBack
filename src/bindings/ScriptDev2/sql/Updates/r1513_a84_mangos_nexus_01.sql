UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_telestra' WHERE `entry` IN (26731);

UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_anomalus' WHERE `entry` IN (26763);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_chaotic_rift' WHERE `entry` IN (26918);

UPDATE creature_template SET `AIName` = '', `Scriptname` = 'boss_ormorok' WHERE `entry` IN (26794);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_crystal_spike' WHERE `entry` IN (27099);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_crystalline_tangler' WHERE `entry` IN (32665);

UPDATE creature_template SET `dynamicflags` = '0', `unit_flags` = '0', `type_flags` = '0', `AIName` = '', `Scriptname` = 'boss_keristrasza' WHERE `entry` IN (26723);
UPDATE creature_template SET `dynamicflags` = '0', `unit_flags` = '0', `type_flags` = '0', `AIName` = '', `Scriptname` = '' WHERE `entry` IN (30540);

-- Kolurg 26798
-- UPDATE creature_template SET `heroic_entry` = '30397', `AIName` = '', `Scriptname` = 'boss_commander_kolurg' WHERE `entry` IN (26798);

-- Stoutbeard 26796
-- UPDATE creature_template SET `heroic_entry` = '30398', `AIName` = '', `Scriptname` = 'boss_commander_stoutbeard' WHERE `entry` IN (26796);

-- IDs Nexus mobs Faction 14
-- 26918,28231,26716,26722,26723,26727,26728,26729,26730,26731,26734,26735,26736,26737,26746,26761,26763,26782,26792,26792,26793,26794,26800,26802,26805,27949,30397,30398
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14' WHERE entry IN (26918,28231,26716,26722,26723,26727,26728,26729,26730,26731,26734,26735,26736,26737,26746,26761,26763,26782,26792,26792,26793,26794,26800,26802,26805,27949,30397,30398);