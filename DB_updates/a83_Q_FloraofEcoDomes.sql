-- Support for quest Flora of Eco-Domes (10426)

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=20774;

DELETE from creature_ai_scripts WHERE creature_id=20774;
INSERT INTO creature_ai_scripts VALUES 
(2077401,20774,8,0,100,0,35772,-1,0,0,16,20983,35772,6,36,20983,0,0,0,0,0,0,'Quest credit and entry change to mutated farahlon'),
(2077402,20774,0,0,100,1,1000,1000,11000,11000,11,12747,1,1,0,0,0,0,0,0,0,0,'Farahlon lasher-cast entagling roots'),
(2077403,20774,0,0,100,1,2500,2500,5000,5000,11,36604,1,1,0,0,0,0,0,0,0,0,'Farahlon lasher-cast Flanking Growth'),
(2077404,20774,0,0,100,1,10000,10000,40000,40000,11,3019,1,1,0,0,0,0,0,0,0,0,'Farahlon lasher-cast Frenzy');
