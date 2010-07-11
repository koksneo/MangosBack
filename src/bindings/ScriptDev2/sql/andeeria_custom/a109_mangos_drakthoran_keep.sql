/* Boss damage */
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26630 LIMIT 1 ;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26631 LIMIT 1 ;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 27483 LIMIT 1 ;
UPDATE `creature_template` SET `dmg_multiplier` = '3' WHERE `entry` = 26632 LIMIT 1 ;

/* Novos the Summoner - summoned npc */
/* Crystal Handler */
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '21700',
`maxhealth` = '22000',
`minmana` = '7800',
`maxmana` = '8100',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '450',
`maxdmg` = '600',
`dmg_multiplier` = '2' WHERE `entry` =26627 LIMIT 1 ;
/* Risen Shadowcaster */
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '1645',
`maxhealth` = '1645',
`minmana` = '7800',
`maxmana` = '7800',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '450',
`maxdmg` = '600',
`dmg_multiplier` = '2' WHERE `entry` =27600 LIMIT 1 ;
/* Fetid Troll Corpse */
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '2050',
`maxhealth` = '2100',
`minmana` = '0',
`maxmana` = '0',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2' WHERE `entry` =27598 LIMIT 1 ;
/* Hulking Corpse */
UPDATE `creature_template` SET `minlevel` = '75',
`maxlevel` = '75',
`minhealth` = '12500',
`maxhealth` = '13000',
`minmana` = '0',
`maxmana` = '0',
`faction_A` = '16',
`faction_H` = '16',
`mindmg` = '550',
`maxdmg` = '700',
`dmg_multiplier` = '2' WHERE `entry` =27597 LIMIT 1 ;

/* Spell for Risen Shadowcaster and  Crystal Handler*/
INSERT INTO `creature_ai_scripts` (
`id` ,
`creature_id` ,
`event_type` ,
`event_inverse_phase_mask` ,
`event_chance` ,
`event_flags` ,
`event_param1` ,
`event_param2` ,
`event_param3` ,
`event_param4` ,
`action1_type` ,
`action1_param1` ,
`action1_param2` ,
`action1_param3` ,
`action2_type` ,
`action2_param1` ,
`action2_param2` ,
`action2_param3` ,
`action3_type` ,
`action3_param1` ,
`action3_param2` ,
`action3_param3` ,
`comment` 
)
VALUES (
NULL , '26627', '0', '0', '100', '0', '5000', '10000', '5000', '10000', '11', '49668', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Crystal Handler - Flash of Darkness'
), (
NULL , '27600', '0', '0', '100', '0', '5000', '10000', '5000', '10000', '11', '59016', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Risen Shadowcaster -Shadowbold'
);
