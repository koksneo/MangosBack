-- Telluric Poultice
DELETE FROM item_required_target WHERE entry = 41988;
INSERT INTO item_required_target VALUES
(41988, 1, 30035);

-- Fallen Earthen Defender
UPDATE creature_template SET RegenHealth = 0 WHERE entry = 30035;
