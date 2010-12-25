-- support for quest The summoning chamber (10585)

DELETE FROM `spell_script_target` WHERE `entry` = 37285;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('37285', '1', '21211');
UPDATE `creature_template` SET `faction_A`='14', `faction_H`='14' WHERE (`entry`='21735'); 
