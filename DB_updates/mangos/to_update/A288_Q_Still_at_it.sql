UPDATE gameobject_template SET
ScriptName='go_still_at_it_quest'
WHERE entry IN(190638,190637,190635,190636,190639);

UPDATE creature_template SET
ScriptName='npc_tipsy_mcmanus'
WHERE entry=28566;

DELETE FROM `gameobject` WHERE guid = '200000';
INSERT INTO `gameobject` VALUES ('200000','190643','571','3','1','5545.45','5767.53','-77.8042','5.39307','0','0','0.959937','0.280215','-25','0','1');

DELETE from creature where id=28537;
INSERT into creature VALUES
(2853701,28537,571,1,1,0,0,5550.404,5768.214,-78.02,1.278,300,0,0,0,0,0,0);

DELETE from spell_script_target WHERE entry in(51932,51931,51933,51934,51935,51936);
INSERT into spell_script_target VALUES
(51932,1,28537),
(51931,1,28537),
(51933,1,28537),
(51934,1,28537),
(51935,1,28537),
(51936,1,28537);

UPDATE creature_template SET
flags_extra=flags_extra |128
WHERE entry=28537;