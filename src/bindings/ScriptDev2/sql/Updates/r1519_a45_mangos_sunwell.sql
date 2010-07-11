-- SWP KALECGOS

-- SpectralRift
UPDATE gameobject_template SET `type` = '22', `data0` = '0', `data3` = '1', `data6` = '0', `data10` = '0', `ScriptName` = 'kalecgos_teleporter' WHERE `entry` IN (187055);
-- Scriptnames KalecgosEvent
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalecgos' WHERE `entry` IN (24850); 
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_sathrovarr' WHERE `entry` IN  (24892);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalec' WHERE `entry` IN (24891);
-- Kalecgos SAthrovarr Pre WOTLK HP
UPDATE creature_template SET `minhealth` = '3700000', `maxhealth` = '3700000' WHERE `entry` IN (24850, 24892);

-- SWP FELMYST

-- Felmyst
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_felmyst' WHERE `entry` IN (25038); 
UPDATE creature_template SET `minlevel` = '70', `maxlevel` = '70',`ScriptName` = 'mob_felmyst_vapor' WHERE `entry` IN (25265); 
UPDATE creature_template SET `ScriptName` = 'mob_felmyst_trail' WHERE `entry` IN (25267); 
UPDATE creature_template SET `ScriptName` = 'mob_deathcloud' WHERE `entry` IN (25703); 

-- SWP MURU

-- Muru and Entropius
UPDATE `creature_template` SET `lootid` = '25840', `mingold` = '2250000', `maxgold` = '2750000', `minhealth` = '5200000', `maxhealth` = '5200000', `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_muru' WHERE `entry` IN (25741);
-- Dark Fiend
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `speed` = '0.6', `ScriptName` = 'dark_fiend' WHERE `entry` IN (25744); 
-- Void Sentinel
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'mob_voidsentinel' WHERE `entry` IN (25772); 
UPDATE `creature_template` SET `minmana` = '10000', `maxmana` = '10000' WHERE `entry` IN (25798, 25772);
-- Singularity
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14', `speed` = '1', `rank` = '1', `AIName` = '', `ScriptName` = 'mob_singularity' WHERE `entry` IN (25855); 

-- SWP KILJAEDEN

-- Kiljaeden 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'boss_kiljaden', `minhealth` = '12600000', `maxhealth` = '12600000', `minmana` = '2000000', `maxmana` = '2000000' WHERE `entry` IN (25315); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `AIName` = '', `minmana` = '165450', `maxmana` = '165450', `ScriptName` = 'mob_deceiver' WHERE `entry` IN (25588); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `minlevel` = '70', `maxlevel` = '70', `minhealth` = '78246', `maxhealth` = '78246', `minmana` = '78875', `maxmana` = '78875', `armor` = '2000', `faction_A` = '14', `faction_H` = '14', `mindmg` = '600', `maxdmg` = '1200', `attackpower` = '450', `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (25708); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `minlevel` = '70', `maxlevel` = '70', `minhealth` = '20000', `maxhealth` = '20000', `minmana` = '78875', `maxmana` = '78875', `armor` = '2000', `faction_A` = '14', `faction_H` = '14', `mindmg` = '600', `maxdmg` = '1200', `attackpower` = '450', `AIName` = '', `ScriptName` = 'mob_orb' WHERE `entry` IN (25502); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'mob_armagedon', `minlevel` = '70', `maxlevel` = '70' WHERE `entry` IN (25735); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `minhealth` = '100', `maxhealth` = '100',`ScriptName` = 'mob_killimp', `minlevel` = '70', `maxlevel` = '70' WHERE `entry` IN (25598); 
-- Blue Dragon
UPDATE `creature_template` SET `unit_flags` = '6',`npcflag` = '1', `minhealth` = '50000', `maxhealth` = '50000',`ScriptName` = 'dragon', `minlevel` = '71', `maxlevel` = '71', `RegenHealth` = '0' WHERE `entry` IN (25653); 
-- Shadow Spike
UPDATE `creature_template` SET `minhealth` = '1', `maxhealth` = '1', `faction_A` = '14', `faction_H` = '14', `ScriptName` = 'mob_shadowspike', `minlevel` = '71', `maxlevel` = '71' WHERE `entry` IN (30598); 

-- SWP EREDAR TWINS

-- Sacrolash
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'boss_sacrolash' WHERE `entry` IN (25165); 
-- Alysthes
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'boss_alythess' WHERE `entry` IN (25166); 
-- ShadowImage
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'npc_shadow_image' WHERE `entry` IN (25214); 