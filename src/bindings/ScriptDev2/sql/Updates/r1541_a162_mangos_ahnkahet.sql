-- AHNKAHET

-- Ahn-Kahet::Nadox 29309 31456
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_nadox' WHERE `entry` IN (29309);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31456);
-- Ahn-Kahet::Swarmer
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '250', `maxdmg` = '500', `baseattacktime` = '2000', `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (30178);
UPDATE creature_template SET `flags_extra` = '64', `mindmg` = '500', `maxdmg` = '1000', `baseattacktime` = '2000', `minhealth` = '250', `maxhealth` = '250' WHERE `entry` IN (31448);
-- Ahn-Kahet::Guardian
UPDATE creature_template SET `armor` = '6000', `mindmg` = '1000', `maxdmg` = '2000', `baseattacktime` = '2000' WHERE `entry` IN (30176);
UPDATE creature_template SET `armor` = '6000', `mindmg` = '2000', `maxdmg` = '4000', `baseattacktime` = '2000' WHERE `entry` IN (31441);

-- Ahn-Kahet::Taladram
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_taldaram', `minmana` ='71220', `maxmana` ='71220' WHERE `entry` IN (29308);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minmana` = '83380', `maxmana` = '83380' WHERE `entry` IN (31469);
DELETE FROM creature WHERE id = '29308';
INSERT INTO creature VALUES (NULL,29308,619,3,1,0,0,529.114,-848.099,11.3082,1.42479,86400,0,0,458354,0,0,0);
-- Flame Sphere
UPDATE creature_template SET `minlevel` ='80', `maxlevel` = '80', `AIName` = '', `Scriptname` = 'mob_flame_sphere', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (30702);
-- DELETE FROM creature_ai_scripts WHERE creature_id IN (30702);
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '3', '500', '500','3000','3000', '11', '57748', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Normal)');
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '5', '500', '500','3000','3000', '11', '58938', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Heroic)');

-- Ahn-Kahet::Jedoga
DELETE FROM creature WHERE id = '29310';
INSERT INTO creature VALUES (NULL,29310,619,3,1,0,0,371.352,-702.825,-16.1797,2.47565,86400,0,0,431392,0,0,0);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = 'boss_jedoga' WHERE `entry` IN (29310);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31465);
-- Volounteer
UPDATE creature_template SET `AIName` = '', `type_flags` = '0', `unit_flags` = '0', `Scriptname` = 'mob_volounteer' WHERE `entry` IN (30385);
UPDATE creature_template SET `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31474);

-- Ahn-Kahet::Amanitar
DELETE FROM creature WHERE id = '30258';
INSERT INTO creature VALUES (NULL,30258,619,2,1,0,0,345.169,-869.813,-77.6156,6.03587,86400,0,0,431392,0,0,0);
UPDATE creature_template SET `mindmg` = '500', `maxdmg` = '700', `armor` = '6000', `dmg_multiplier` = '13', `attackpower` = '2000', `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_amanitar' WHERE `entry` IN (30258);
UPDATE creature_template SET `mindmg` = '500', `maxdmg` = '700', `armor` = '6000', `dmg_multiplier` = '13', `attackpower` = '2000', `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287'  WHERE `entry` IN (31463);
-- Ahn-Kahet::Mushrooms
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_healthymushroom' WHERE `entry` IN (30391);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_poisonmushroom' WHERE `entry` IN (30435);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (31461,31462);
UPDATE creature_template SET `modelid_A` = '11686', `modelid_H` = '11686' WHERE `entry` IN (31461,31462,30435,30391);

-- Ahn-Kahet::Volazj
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_volazj' WHERE `entry` IN (29311);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31464);
-- Ahn-Kahet::twisted Visage 30625
UPDATE creature_template SET `mindmg` = '500', `maxdmg` = '1000', `baseattacktime` = '2000', `minhealth` = '12000', `maxhealth` = '12000', `maxmana` = '8000', `minmana` = '8000' WHERE `entry` IN (30625);

-- Ahnkahet creature_template
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0' WHERE `entry` IN (30413);


-- CREATURE_LOOT_TEMPLATE HEROIC

-- Ahn-Kahet::Heroic Boss LOOT
DELETE FROM creature_loot_template WHERE entry IN (31469,31456,31465,31464,31463);

-- Ahn-Kahet::Nadox
UPDATE creature_template SET `lootid` = '31469' WHERE `entry` IN (31469);
-- Ahn-Kahet::Taladram
UPDATE creature_template SET `lootid` = '31456' WHERE `entry` IN (31456);
-- Ahn-Kahet::Jedoga
UPDATE creature_template SET `lootid` = '31465' WHERE `entry` IN (31465);
-- Ahn-Kahet::Amanitar
UPDATE creature_template SET `lootid` = '31463' WHERE `entry` IN (31463);
-- Ahn-Kahet::Volazj
UPDATE creature_template SET `lootid` = '31464' WHERE `entry` IN (31464);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Ahn-Kahet::Nadox
('31469', '37592', '23', '1', '1', '1', '0', '0', '0'),
('31469', '37594', '23', '1', '1', '1', '0', '0', '0'),
('31469', '37591', '23', '1', '1', '1', '0', '0', '0'),
('31469', '37593', '23', '1', '1', '1', '0', '0', '0'),
('31469', '43852', '1.8', '0', '1', '1', '0', '0', '0'),

-- Ahn-Kahet::Taladram
('31456', '37612', '22', '1', '1', '1', '0', '0', '0'),
('31456', '37613', '22', '1', '1', '1', '0', '0', '0'),
('31456', '37614', '22', '1', '1', '1', '0', '0', '0'),
('31456', '37595', '22', '1', '1', '1', '0', '0', '0'),
('31456', '43852', '3', '0', '1', '1', '0', '0', '0'),

-- Ahn-Kahet::Jedoga
('31465', '43282', '23', '1', '1', '1', '0', '0', '0'),
('31465', '43281', '22', '1', '1', '1', '0', '0', '0'),
('31465', '43280', '22', '1', '1', '1', '0', '0', '0'),
('31465', '43283', '22', '1', '1', '1', '0', '0', '0'),
('31465', '43852', '3', '0', '1', '1', '0', '0', '0'),

-- Ahn-Kahet::Amanitar
('31463', '43284', '23', '1', '1', '1', '0', '0', '0'),
('31463', '43285', '23', '1', '1', '1', '0', '0', '0'),
('31463', '43286', '23', '1', '1', '1', '0', '0', '0'),
('31463', '43287', '22', '1', '1', '1', '0', '0', '0'),
('31463', '43852', '3', '0', '1', '1', '0', '0', '0'),

-- Ahn-Kahet::Volazj
('31464', '43102', '100', '3', '1', '1', '0', '0', '0'),
('31464', '37620', '20', '2', '1', '1', '0', '0', '0'),
('31464', '37618', '20', '1', '1', '1', '0', '0', '0'),
('31464', '37616', '20', '1', '1', '1', '0', '0', '0'),
('31464', '37617', '20', '1', '1', '1', '0', '0', '0'),
('31464', '37623', '19', '2', '1', '1', '0', '0', '0'),
('31464', '37622', '19', '2', '1', '1', '0', '0', '0'),
('31464', '37619', '19', '2', '1', '1', '0', '0', '0'),
('31464', '37615', '19', '1', '1', '1', '0', '0', '0'),
('31464', '41790', '15', '0', '1', '1', '0', '0', '0'),

-- Ahnkahet::Emblem of Heroism
('31463', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31469', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31456', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31465', '40752', '100', '0', '1', '1', '0', '0', '0'),
('31464', '40752', '100', '0', '1', '1', '0', '0', '0');

-- ACID
-- Update EVENTAI
UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (30278,30329,30416,30419,30418,30319,30179,30111,30285,30286,30284,30283,30277,30279);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (30278,30329,30416,30419,30418,30319,30179,30111,30285,30286,30284,30283,30277,30279);

INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES

-- deep crawler 30279
(NULL, '30279', '0', '0', '100', '3', '5000', '8000','15000','20000', '11', '56580', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'deep crawler - Cast Glutinus Poison (Normal)'),
(NULL, '30279', '0', '0', '100', '5', '5000', '8000','15000','20000', '11', '59108', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'deep crawler - Cast Glutinus Poison (Heroic)'),
(NULL, '30279', '2', '0', '100', '3', '10', '1','0','0', '11', '56581', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'deep crawler - Cast Fatal Sting (Normal)'),
(NULL, '30279', '2', '0', '100', '5', '10', '1','0','0', '11', '59109', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'deep crawler - Cast Fatal Sting (Heroic)'),

-- Ahn'kahar Slasher 30277
(NULL, '30277', '0', '0', '100', '7', '10000', '15000','15000','25000', '11', '42746', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Slasher - Cast Glutinus Cleave'),
(NULL, '30277', '0', '0', '100', '7', '20000', '36000','25000','40000', '11', '56643', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Slasher - Cast Glutinus Slash'),
(NULL, '30277', '0', '0', '100', '7', '15000', '30000','30000','30000', '11', '56646', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Slasher - Cast Enrage Time'),
(NULL, '30277', '2', '0', '100', '7', '10', '1','0','0', '11', '32714', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Slasher - Cast Enrage'),

-- Plague Walker 30283
(NULL, '30283', '4', '0', '100', '3', '0', '0','0','0', '11', '56709', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plague Walker - Cast Aura Hope (Normal)'),
(NULL, '30283', '4', '0', '100', '5', '0', '0','0','0', '11', '61459', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plague Walker - Cast Aura Hope (Heroic)'),
(NULL, '30283', '0', '0', '100', '7', '15000', '30000','30000','30000', '11', '56707', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plague Walker - Cast Contagion'),

-- Bonegrinder 30284
(NULL, '30284', '2', '0', '100', '7', '10', '1','0','0', '11', '8599', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bonegrinder - Cast Enrage'),
(NULL, '30284', '0', '0', '100', '3', '15000', '36000','25000','40000', '11', '56736', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bonegrinder - Cast Trample (Normal)'),
(NULL, '30284', '0', '0', '100', '5', '15000', '36000','25000','40000', '11', '59107', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bonegrinder - Cast Trample (Heroic)'),
(NULL, '30284', '0', '0', '100', '7', '15000', '36000','30000','50000', '11', '19134', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bonegrinder - Cast Fear'),

-- Frostbringer 30286
(NULL, '30286', '0', '0', '100', '3', '10000', '15000','15000','25000', '11', '57825', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Frostbringer - Cast FrostBolt (Normal)'),
(NULL, '30286', '0', '0', '100', '5', '10000', '15000','15000','25000', '11', '61461', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Frostbringer - Cast FrostBolt (Heroic)'),
(NULL, '30286', '0', '0', '100', '3', '20000', '30000','29000','35000', '11', '15063', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Frostbringer - Cast FrostNova (Normal)'),
(NULL, '30286', '0', '0', '100', '5', '20000', '30000','29000','35000', '11', '61462', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Frostbringer - Cast FrostNova (Heroic)'),
(NULL, '30286', '0', '0', '100', '7', '50000', '70000','80000','160000', '11', '56716', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Frostbringer - Cast Icy Winds'),

-- Eye of Taldaram 30285
(NULL, '30285', '0', '0', '100', '3', '25000', '40000','25000', '40000', '11', '56730', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast CounterSpell (Normal)'),
(NULL, '30285', '0', '0', '100', '5', '25000', '40000','25000', '40000', '11', '59111', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast CounterSpell (Heroic)'),
(NULL, '30285', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '17289', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast Shadow Shock (Normal)'),
(NULL, '30285', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '17439', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast Shadow Shock (Heroic)'),
(NULL, '30285', '0', '0', '100', '3', '40000', '60000','40000', '60000', '11', '56733', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast Shadowfury (Normal)'),
(NULL, '30285', '0', '0', '100', '5', '40000', '60000','40000', '60000', '11', '61463', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Eye of Taldaram - Cast Shadowfury (Heroic)'),

-- Twilight Worshipper 30111
(NULL, '30111', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '17290', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Worshipper - Cast Fireball (Normal)'),
(NULL, '30111', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '61567', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Worshipper - Cast Fireball (Heroic)'),
(NULL, '30111', '0', '0', '100', '3', '40000', '60000','40000', '60000', '11', '56858', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Worshipper - Cast Flamestrike (Normal)'),
(NULL, '30111', '0', '0', '100', '5', '40000', '60000','40000', '60000', '11', '61568', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Worshipper - Cast Flamestrike (Heroic)'),

-- Twilight Apostle 30179
(NULL, '30179', '4', '0', '100', '3', '0', '0','0', '0', '11', '12550', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Apostle - Cast Flamestrike (Normal)'),
(NULL, '30179', '4', '0', '100', '5', '0', '0','0', '0', '11', '61570', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Apostle - Cast Flamestrike (Heroic)'),
(NULL, '30179', '4', '0', '100', '7', '0', '0','0', '0', '11', '28902', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Apostle - BloodLust'),

-- Twilight Darkcaster 30319
(NULL, '30319', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '56898', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Darkcaster - Cast Corruption (Normal)'),
(NULL, '30319', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '61563', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Darkcaster - Cast Corruption (Heroic)'),
(NULL, '30319', '0', '0', '100', '7', '15000', '30000','15000', '30000', '11', '13338', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Darkcaster - Cast Curse'),
(NULL, '30319', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '12739', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Darkcaster - Cast Bolt (Normal)'),
(NULL, '30319', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '61562', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Twilight Darkcaster - Cast Bolt (Heroic)'),

-- Bound Air Elemental 30418
(NULL, '30418', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '22414', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Air Elemental - Cast LightBolt (Normal)'),
(NULL, '30418', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '59169', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Air Elemental - Cast LightBolt (Heroic)'),
(NULL, '30418', '0', '0', '100', '3', '25000', '40000','25000', '40000', '11', '46150', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Air Elemental - Cast Forked (Normal)'),
(NULL, '30418', '0', '0', '100', '5', '25000', '40000','25000', '40000', '11', '59152', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Air Elemental - Cast Forked (Heroic)'),

-- Bound Water Elemental 30419
(NULL, '30419', '0', '0', '100', '7', '15000', '30000','15000', '30000', '11', '56862', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Water Elemental - Cast WaterBolt'),
(NULL, '30419', '0', '0', '100', '3', '25000', '40000','25000', '40000', '11', '35735', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Water Elemental - Cast Spout (Normal)'),
(NULL, '30419', '0', '0', '100', '5', '25000', '40000','25000', '40000', '11', '39207', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Water Elemental - Cast Spout (Heroic)'),

-- Bound Fire Elemental 30416
(NULL, '30416', '0', '0', '100', '7', '25000', '30000','25000', '30000', '11', '12470', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Fire Elemental - Cast FireNova'),
(NULL, '30416', '0', '0', '100', '7', '15000', '30000','15000', '30000', '11', '17195', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Bound Fire Elemental - Cast Scorch'),

-- Savage Cave Beast 30329
(NULL, '30329', '2', '0', '100', '7', '10', '1', '0', '0', '11', '48193', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Savage Cave Beast - Cast Enrage'),
(NULL, '30329', '0', '0', '100', '7', '15000', '30000','15000', '30000', '11', '30471', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Savage Cave Beast - Cast Upprcut'),
(NULL, '30329', '4', '0', '100', '3', '0', '0','0', '0', '11', '56867', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Savage Cave Beast - Cast Cloud (Normal)'),
(NULL, '30329', '4', '0', '100', '5', '0', '0','0', '0', '11', '59116', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Savage Cave Beast - Cast Cloud (Heroic)'),

-- Ahn\'kahar Spell Flinger 30278
(NULL, '30278', '0', '0', '100', '3', '15000', '30000','15000', '30000', '11', '56698', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Spell Flinger - Cast Sickle (Normal)'),
(NULL, '30278', '0', '0', '100', '5', '15000', '30000','15000', '30000', '11', '59102', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Spell Flinger - Cast Sickle (Heroic)'),
(NULL, '30278', '0', '0', '100', '3', '25000', '40000','25000', '40000', '11', '56702', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Spell Flinger - Cast Blast (Normal)'),
(NULL, '30278', '0', '0', '100', '5', '25000', '40000','25000', '40000', '11', '59103', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Ahn\'kahar Spell Flinger - Cast Blast (Heroic)');
