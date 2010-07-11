-- item (Arcane Binder)
DELETE FROM item_required_target WHERE entry = 34691;
INSERT INTO item_required_target VALUES
(34691,1,25316);

-- NPC captured arcane binder
UPDATE creature_template SET scriptname = 'npc_small_pet_handler' WHERE entry = 25474;
