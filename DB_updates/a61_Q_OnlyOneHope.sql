-- Support for quest Only One Hope

UPDATE creature_template SET flags_extra=flags_extra|128 WHERE entry=29647;
DELETE FROM creature WHERE id=29928;
INSERT INTO creature VALUES
(2992801,29647,571,1,1,26656,0,5796.48,-1594.16,235.111,2.16421,300,0,0,11379,0,0,0);
