-- Allow MatureNetherwing to fly
UPDATE creature_template SET movementtype = 4 WHERE entry = 21648;
UPDATE creature SET movementtype = 4 WHERE id = 21648;
