-- VERY IMPORTANT NOTE: you must replace `mangos_realmd` with your own realm database name!

DELETE FROM `characters` WHERE `account` NOT IN (SELECT `id` FROM `mangos_realmd`.`account`) AND `account` != '0';
DELETE FROM `account_data` WHERE `account` NOT IN (SELECT `id` FROM `mangos_realmd`.`account`) AND `account` != '0';
DELETE FROM `character_tutorial` WHERE `account` NOT IN (SELECT `id` FROM `mangos_realmd`.`account`) AND `account` != '0';

DELETE FROM `character_account_data` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_achievement` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_achievement_progress` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_action` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_aura` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_battleground_data` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_declinedname` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_equipmentsets` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_gifts` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_glyphs` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_homebind` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_instance` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_inventory` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_pet` WHERE `owner` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_pet_declinedname` WHERE `owner` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_queststatus` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`) and `guid` < 100000;
DELETE FROM `character_queststatus` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`) and `guid` > 99999;
DELETE FROM `character_queststatus_daily` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_reputation` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_social` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_social` WHERE `friend` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_spell` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_spell_cooldown` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `character_talent` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);

DELETE FROM `guild_member` WHERE `guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `guild` WHERE (SELECT COUNT(*) FROM `guild_member` WHERE `guildid` = `guild`.`guildid`) = '0';
DELETE FROM `guild_bank_eventlog` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_bank_item` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_bank_right` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_bank_tab` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_eventlog` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_member` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
DELETE FROM `guild_rank` WHERE `guildid` NOT IN (SELECT `guildid` FROM `guild`);
