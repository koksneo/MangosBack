-- Set Shadow Sight gems despawned at default
UPDATE gameobject SET spawntimesecs = -150 WHERE id IN (184663,184664);
-- Also event handling gems is 252 not 253
UPDATE battleground_events SET event1 = 252 WHERE map IN (559,562,572) AND event1 = 253;
