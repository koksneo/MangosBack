-- Quest Norgrannon's Shell (12872)
DELETE from spell_script_target WHERE entry=55197;
INSERT into spell_script_target VALUES
(55197,0,191760);

DELETE from event_scripts WHERE id=19410;
INSERT into event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(19410,0,10,29775,120000,7991.81,-827.674,968.263,2.89725);

DELETE from creature WHERE id=29775;

UPDATE creature_template SET
minlevel=80,
maxlevel=80,
minhealth=12600,
maxhealth=12600,
minmana=3994,
maxmana=3994,
armor=9786,
mindmg=476,
maxdmg=531,
dmg_multiplier=3,
AIName='EventAI',
lootid=entry
WHERE entry=29775;

DELETE from creature_ai_scripts WHERE creature_id=29775;
INSERT INTO creature_ai_scripts VALUES 
(2977501,29775,1,0,100,0,1000,1000,0,0,1,-297751,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977502,29775,1,0,100,0,6000,6000,0,0,1,-297752,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977503,29775,1,0,100,0,13000,13000,0,0,1,-297753,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977504,29775,1,0,100,0,23000,23000,0,0,1,-297754,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977505,29775,1,0,100,0,31000,31000,0,0,1,-297755,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977506,29775,1,0,100,0,39000,39000,0,0,1,-297756,0,0,0,0,0,0,0,0,0,0,'Archivist Mechaton- say'),
(2977507,29775,1,0,100,0,47000,47000,0,0,1,-297757,0,0,19,768,0,0,0,0,0,0,'Archivist Mechaton- say and remove unit_flags');


DELETE from creature_ai_texts WHERE entry BETWEEN -297757 AND -297751;
INSERT into creature_ai_texts (entry,content_default,comment) VALUES
(-297751,'Use of the Inventor\'s Disk detected. Emergency protocol gamma activated.','One of the Archivist Mechaton texts'),
(-297752,'Verifying status of Norgannon\'s shell..','One of the Archivist Mechaton texts'),
(-297753,'Norgannon\'s shell accounted for and secure. It will be available for transfer once user\'s identity has been verified.','One of the Archivist Mechaton texts'),
(-297754,'Standby to verify identity as keeper Mimir.','One of the Archivist Mechaton texts'),
(-297755,'Identity verification failed. User is not keeper Mimir.','One of the Archivist Mechaton texts'),
(-297756,'The Inventor\'s Disk has fallen into the hands of an unauthorized user. Activating defense protocol.','One of the Archivist Mechaton texts'),
(-297757,'Imposter must be dealt with. The Inventor\'s Disk must be recovered.','One of the Archivist Mechaton texts');

DELETE from creature_loot_template where entry=29775;
INSERT into creature_loot_template VALUES
(29775,41258,-100,0,1,1,0,0,0);





