-- SpectralRift
UPDATE gameobject_template SET `type` = '22', `data0` = '0', `data3` = '1', `data6` = '0', `data10` = '0', `ScriptName` = 'kalecgos_teleporter' WHERE `entry` IN (187055);
-- Scriptnames KalecgosEvent
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalecgos' WHERE `entry` IN (24850); 
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_sathrovarr' WHERE `entry` IN  (24892);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalec' WHERE `entry` IN (24891);
