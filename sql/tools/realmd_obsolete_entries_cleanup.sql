UPDATE `account` SET `sessionkey` = NULL, `v` = NULL, `s` = NULL WHERE `active_realm_id` = 0;
DELETE FROM `account_banned` WHERE `id` NOT IN (SELECT `id` FROM `account`);
DELETE FROM `realmcharacters` WHERE `acctid` NOT IN (SELECT `id` FROM `account`);
