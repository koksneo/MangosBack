-- All dummies (targets, focus, manekins etc)
UPDATE creature_template SET flags_extra = flags_extra|64 WHERE `name` LIKE '%dummy%';