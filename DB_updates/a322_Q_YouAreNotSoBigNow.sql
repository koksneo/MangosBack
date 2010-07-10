-- Support for quest Hah... You're Not So Big Now! (11653)

-- Item Crafty's Ultra-Advanced Proto-Typical Shortening Blaster (34812)
DELETE FROM item_required_target WHERE entry=34812;
INSERT INTO item_required_target VALUES
(34812,1,25434),
(34812,1,25432);
