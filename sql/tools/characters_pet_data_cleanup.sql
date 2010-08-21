DELETE FROM `pet_aura` WHERE `guid` NOT IN (SELECT `id` FROM `character_pet`);
DELETE FROM `pet_aura` WHERE `caster_guid` NOT IN (SELECT `guid` FROM `characters`);
DELETE FROM `pet_spell` WHERE `guid` NOT IN (SELECT `id` FROM `character_pet`);
DELETE FROM `pet_spell_cooldown` WHERE `guid` NOT IN (SELECT `id` FROM `character_pet`);