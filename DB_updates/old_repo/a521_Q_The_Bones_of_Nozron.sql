-- Support for quest The Bones of Nozronn (12544)

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=28256;

-- event ai
DELETE FROM creature_ai_texts WHERE entry IN(-282560,-282561,-282562,-282563,-282564);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-282560,'So the oracIe has decided to aid you, outIander. Very weII, l will offer you what i know.',0,'Voice of Nozronn first text'),
(-282561,'Your companion seeks the shardhorn patriarch Farunn, who holds himself aIoof from his brothers.',0,'Voice of Nozronn second text'),
(-282562,'Farunn walks the lands north of what your people call the Bittertide Falls. You will find him alone, but you will see her requires no defenders.',0,'Voice of Nozronn third text'),
(-282563,'Return to your companion. TelI him to go forth and claim his prize in Farunn.',0,'Voice of Nozronn fourth text'),
(-282564,'Once he has done so, tell him to Ieave this land in peace. He does not belong here.',0,'Voice of Nozronn fifth text');

DELETE FROM event_scripts WHERE id=18481;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,x,y,z,o) VALUES
(18481,0,10,28256,300000,5202.92,5782.97,-71.5886,0.547677),
(18481,22,8,28256,0,0,0,0,0); 

DELETE FROM creature_ai_scripts WHERE id IN(2825600,2825601,2825602,2825603,2825604,2825605);
INSERT INTO creature_ai_scripts VALUES
(2825600,28256,1,0,100,0,1000,1000,0,0,1,-282560,0,0,0,0,0,0,0,0,0,0,'Voice of Nozronn-say '),
(2825601,28256,1,0,100,0,6000,6000,0,0,1,-282561,0,0,0,0,0,0,0,0,0,0,'Voice of Nozronn-say '),
(2825602,28256,1,0,100,0,12000,12000,0,0,1,-282562,0,0,0,0,0,0,0,0,0,0,'Voice of Nozronn-say '),
(2825603,28256,1,0,100,0,17000,17000,0,0,1,-282563,0,0,0,0,0,0,0,0,0,0,'Voice of Nozronn-say '),
(2825604,28256,1,0,100,0,22000,22000,0,0,1,-282564,0,0,0,0,0,0,41,0,0,0,'Voice of Nozronn-say ');
