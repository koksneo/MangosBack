-- Captive Mechagnome - emote state mining
DELETE FROM creature_addon WHERE guid IN (SELECT guid FROM creature WHERE id = 29384);
INSERT INTO creature_addon (guid,emote) SELECT guid,233 FROM creature WHERE id = 29384;
-- Captive Mechagnome - propper gossip text
DELETE FROM npc_gossip WHERE npc_guid IN (SELECT guid FROM creature WHERE id = 29384);
INSERT INTO npc_gossip (npc_guid,textid) SELECT guid,13682 FROM creature AS npc_guid WHERE id = 29384;