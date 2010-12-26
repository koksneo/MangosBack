DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25593 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25599 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25595 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25597 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25509 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25484 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25798 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25837 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25485 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25799 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25508 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25506 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25483 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25373 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25486 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25367 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25363 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25371 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25370 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25507 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25372 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25368 ; 
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 25369 ; 

/* Apocalypse Guard 25593 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25593', '0', '0', '100', '1', '1000', '5000', '5000', '15000', '11', '40504', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Apocalypse Guard - Cleave'
), (
NULL , '25593', '0', '0', '70', '1', '5000', '15000', '5000', '25000', '11', '45029', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Apocalypse Guard - Corrupting Strike'
), (
NULL , '25593', '0', '0', '50', '1', '5000', '10000', '10000', '15000', '11', '46283', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Apocalypse Guard - Death Coil'
), (
NULL , '25593', '0', '0', '100', '0', '1000', '1000', '0', '0', '11', '46287', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Apocalypse Guard - Infernal Defense'
);
/* Cataclysm Hound 25599 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25599', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46292', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Cataclysm Hound - Cataclysm Breath'
), (
NULL , '25599', '2', '0', '100', '1', '30', '0', '0', '0', '11', '47399', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Cataclysm Hound - Enrage'
);

/* Chaos Gazer 25595 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25595', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46288', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Chaos Gazer - Petrify'
), (
NULL , '25595', '2', '0', '100', '1', '30', '10', '0', '0', '11', '46291', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Chaos Gazer - Drain Life'
), (
NULL , '25595', '0', '0', '100', '1', '5000', '50000', '10000', '15000', '11', '46290', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Chaos Gazer - Tentacle Sweep'
);

/* Oblivion Mage 25597 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25597', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46280', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Oblivion Mage - Polymorph'
), (
NULL , '25597', '0', '0', '100', '1', '5000', '10000', '10000', '15000', '11', '46279', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Oblivion Mage - Flame Buffet'
);

/* Priestess of Torment 25509 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25509', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46270', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Priestess of Torment - Whirlwind'
);

/* Shadowsword Assassin 25484 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25484', '1', '0', '100', '1', '1', '1', '0', '0', '11', '16380', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Assassin - Greater Invisibility'
), (
NULL , '25484', '0', '0', '100', '1', '5000', '10000', '10000', '15000', '11', '46463', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Assassin - Shadowstep'
);

/* Shadowsword Berserker 25798 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25798', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46160', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Berserker - Flurry'
);

/* Shadowsword Commander 25837 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25837', '0', '0', '100', '1', '1000', '2000', '40000', '55000', '11', '46763', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Commander - Battle Shout'
), (
NULL , '25837', '0', '0', '100', '1', '5000', '10000', '10000', '15000', '11', '46762', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Commander - Shield Slam'
);

/* Shadowsword Deathbringer 25485 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25485', '0', '0', '70', '1', '1000', '2000', '10000', '25000', '11', '46481', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Deathbringer - Disease Buffet'
);

/* Shadowsword Fury Mage 25799 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25799', '0', '0', '100', '1', '1000', '1000', '30000', '45000', '11', '46102', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Fury Mage - Spell Fury'
), (
NULL , '25799', '0', '0', '100', '1', '1000', '5000', '5000', '10000', '11', '46101', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Fury Mage - Fel Fireball'
);

/* Shadowsword Guardian 25508 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25508', '0', '0', '100', '1', '1000', '1000', '20000', '35000', '11', '46239', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Guardian - Bear Down'
);

/* Shadowsword Lifeshaper 25506 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25506', '0', '0', '100', '1', '1000', '5000', '20000', '35000', '11', '46466', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Lifeshaper - Drain Life'
);

/* Shadowsword Manafiend 25483 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25483', '0', '0', '100', '1', '1000', '5000', '10000', '25000', '11', '46453', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Manafiend - Drain Mana'
), (
NULL , '25483', '0', '0', '100', '1', '1000', '5000', '5000', '15000', '11', '46457', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Manafiend - Arcane Explosion'
);

/* Shadowsword Soulbinder 25373 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25373', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46442', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Soulbinder - Flash of Darkness'
), (
NULL , '25373', '0', '0', '100', '1', '1000', '5000', '5000', '10000', '11', '46434', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Soulbinder - Curse of Exhaustion'
), (
NULL , '25373', '0', '0', '100', '1', '5000', '20000', '10000', '25000', '11', '46427', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Soulbinder - Domination'
);

/* Shadowsword Vanquisher 25486 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25486', '0', '0', '100', '1', '1000', '5000', '10000', '25000', '11', '46469', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Vanquisher - Melt Armor'
), (
NULL , '25486', '0', '0', '100', '1', '1000', '5000', '5000', '15000', '11', 'Cleave', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Shadowsword Vanquisher - Cleave'
);

/* Sunblade Arch Mage 25367 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25367', '0', '0', '70', '1', '5000', '10000', '10000', '25000', '11', '46573', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Arch Mage - Blink'
), (
NULL , '25367', '0', '0', '100', '1', '6000', '10000', '1000', '20000', '11', '46553', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Arch Mage - Arcane Explosion'
), (
NULL , '25367', '0', '0', '100', '1', '5000', '5000', '10000', '25000', '11', '46555', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Arch Mage - Frost Nova'
);

/* Sunblade Cabalist 25363 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25363', '0', '0', '100', '1', '5000', '10000', '10000', '25000', '11', '47248', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Cabalist - Shadow Bolt'
), (
NULL , '25363', '0', '0', '100', '0', '1', '1', '0', '0', '11', '46553', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Cabalist - Summon Imp'
), (
NULL , '25363', '0', '0', '100', '1', '5000', '5000', '20000', '35000', '11', '46543', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Cabalist - Ignite Mana'
);

/* Sunblade Dawn Priest 25371 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25371', '0', '0', '100', '0', '1000', '1000', '0', '0', '11', '46565', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dawn Priest - Holyform'
), (
NULL , '25371', '0', '0', '100', '1', '5000', '10000', '10000', '20000', '11', '46564', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dawn Priest - Holy Nova'
), (
NULL , '25371', '2', '0', '100', '1', '60', '50', '50', '10', '11', '46563', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dawn Priest - Renew'
);

/* Sunblade Dusk Priest 25370 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25370', '0', '0', '100', '1', '1000', '5000', '10000', '25000', '11', '46561', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dusk Priest - Fear'
),(
NULL , '25370', '0', '0', '100', '1', '1000', '5000', '10000', '15000', '11', '46562', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dusk Priest - Mind Flay'
),(
NULL , '25370', '0', '0', '100', '1', '1000', '5000', '5000', '15000', '11', '46560', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Dusk Priest - Shadow Word: Pain'
);

/* Sunblade Protector 25507 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25507', '0', '0', '100', '1', '1000', '5000', '10000', '25000', '11', '46480', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Protector - Fel Lightning'
);

/* Sunblade Scout 25372 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25372', '0', '0', '100', '1', '1000', '5000', '10000', '15000', '11', '46558', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Scout - Sinister Strike'
);

/* Sunblade Slayer 25368 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25368', '0', '0', '100', '1', '1000', '5000', '5000', '15000', '11', '47001', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Scout - Shoot'
), (
NULL , '25368', '0', '0', '100', '1', '1000', '5000', '10000', '15000', '11', '46557', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Scout - Slaying Shot'
);

/* Sunblade Vindicator 25369 */
INSERT INTO `creature_ai_scripts` (`id` ,`creature_id` ,`event_type` ,`event_inverse_phase_mask` ,`event_chance` ,`event_flags` ,`event_param1` ,`event_param2` ,`event_param3` ,`event_param4` ,`action1_type` ,`action1_param1` ,`action1_param2` ,`action1_param3` ,`action2_type` ,`action2_param1` ,`action2_param2` ,`action2_param3` ,`action3_type` ,`action3_param1` ,`action3_param2` ,`action3_param3` ,`comment`)
VALUES (
NULL , '25369', '0', '0', '100', '1', '5000', '15000', '15000', '25000', '11', '39171', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Vindicator - Mortal Strike'
), (
NULL , '25369', '0', '0', '100', '1', '1000', '5000', '10000', '15000', '11', '46559', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Sunblade Vindicator - Cleave'
);

UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25593 ;
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25593 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25599 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25595 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25597 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25509 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25484 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25798 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25837 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25485 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25799 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25508 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25506 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25483 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25373 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25486 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25367 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25363 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25371 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25370 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25507 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25372 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25368 ; 
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = 25369 ; 
