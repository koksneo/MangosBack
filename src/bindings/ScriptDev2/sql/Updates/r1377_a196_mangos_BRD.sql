-- Princess Moira Bronzebeard (faction change to prevent joining final BRD encounter and avoid crash) 
-- orginal faction template 734 have to be restored after aproppriate SD2 fix
UPDATE creature_template SET faction_A = 35, faction_H = 35 WHERE entry = 8929;
