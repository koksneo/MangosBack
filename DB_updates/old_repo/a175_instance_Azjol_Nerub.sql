-- AZJOL NERUB

-- Krik Thir norm/hero
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (31612,28684);

-- Krik Thir mini bosy norm/hero
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_silthik' WHERE `entry` IN (28731);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_gashra' WHERE `entry` IN (28730);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_narjil' WHERE `entry` IN (28729);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = `mechanic_immune_mask`|1073463287 WHERE `entry` IN (31616,31615,31617);


-- Swarmer Infector norm/hero
UPDATE creature_template SET `AIName` = 'EventAI' WHERE `entry` = '28736';

-- Anubarak
UPDATE creature_template SET `mechanic_immune_mask` = mechanic_immune_mask |1073463287 WHERE `entry` IN (29120,31610);
-- ? SD2 ma tu normalny c++ skrypt
UPDATE creature_template SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (29120);

-- Trigger Invisible Mode
UPDATE `creature_template` SET `flags_extra` = '128' WHERE `entry` IN (29184);

