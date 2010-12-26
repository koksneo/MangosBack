-- Kiljaeden 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'boss_kiljaden', `minhealth` = '12600000', `maxhealth` = '12600000', `minmana` = '2000000', `maxmana` = '2000000' WHERE `entry` IN (25315); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `AIName` = '', `minmana` = '165450', `maxmana` = '165450', `ScriptName` = 'mob_deceiver' WHERE `entry` IN (25588); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `minlevel` = '70', `maxlevel` = '70', `minhealth` = '78246', `maxhealth` = '78246', `minmana` = '78875', `maxmana` = '78875', `armor` = '2000', `faction_A` = '14', `faction_H` = '14', `mindmg` = '600', `maxdmg` = '1200', `attackpower` = '450', `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (25708); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '0', `minlevel` = '70', `maxlevel` = '70', `minhealth` = '20000', `maxhealth` = '20000', `minmana` = '78875', `maxmana` = '78875', `armor` = '2000', `faction_A` = '14', `faction_H` = '14', `mindmg` = '600', `maxdmg` = '1200', `attackpower` = '450', `AIName` = '', `ScriptName` = 'mob_orb' WHERE `entry` IN (25502); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'mob_armagedon', `minlevel` = '70', `maxlevel` = '70' WHERE `entry` IN (25735); 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `minhealth` = '100', `maxhealth` = '100',`ScriptName` = 'mob_killimp', `minlevel` = '70', `maxlevel` = '70' WHERE `entry` IN (25598); 

-- Blue Dragon
UPDATE `creature_template` SET `minhealth` = '50000', `maxhealth` = '50000',`ScriptName` = 'mob_bluedragon', `minlevel` = '71', `maxlevel` = '71' WHERE `entry` IN (25653); 
