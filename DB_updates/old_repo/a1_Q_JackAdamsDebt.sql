-- Jack Adams dancing on the table
DELETE FROM creature_addon WHERE guid = 115895;
INSERT INTO creature_addon (guid,mount,bytes1,b2_0_sheath,b2_1_pvp_state,emote) VALUES
(115895,0,0,0,0,10);

UPDATE creature_template SET ScriptName = 'npc_olga', AIName = '' WHERE entry = 24639;
UPDATE creature_template SET ScriptName = 'npc_jack_adams', AIName = '' WHERE entry = 24788;

