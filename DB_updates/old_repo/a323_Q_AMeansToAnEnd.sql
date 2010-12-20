-- A Means to an End (12240)

-- Levine Family Termite Bunny (27353)
UPDATE creature_template SET modelid_1=17612 WHERE entry=27353;

-- Summon Foreman Kaleiki (27238)
DELETE FROM event_scripts WHERE id=17868;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(17868,0,10,27238,180000,2798.14,-199.626,139.161,0.410687);

-- Foreman Kaleiki (27238) stats
UPDATE creature_template SET
minlevel=72,
maxlevel=72,
minhealth=9610,
maxhealth=9610,
armor=7618,
faction_A=67, 
faction_H=67,
mindmg=155,
maxdmg=225,
attackpower=320,
dmg_multiplier=2
WHERE entry=27238;
