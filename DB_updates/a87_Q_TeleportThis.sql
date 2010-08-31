-- Teleport This! (10857)

-- Missing spells
UPDATE creature_template SET spell3=38920 WHERE entry IN (16943,20928);
UPDATE creature_template SET spell1=37179, spell2=33962 WHERE entry=20928;

DELETE FROM spell_script_target WHERE entry=38920;
INSERT INTO spell_script_target VALUES
(38920,1,22348), 
(38920,1,22350),
(38920,1,22351);

UPDATE creature_template SET 
AIName='EventAI', 
unit_flags=unit_flags|33554432,
faction_A=35,
faction_H=35
WHERE entry IN (22348,22350,22351);

DELETE FROM creature_ai_scripts WHERE creature_id IN (22348,22350,22351);
INSERT INTO creature_ai_scripts VALUES
(2234801,22348,8,0,100,1,38920,-1,100,100,33,22348,6,0,0,0,0,0,0,0,0,0,'Western Gehenna Teleporter - Quest Credit'),
(2235001,22350,8,0,100,1,38920,-1,100,100,33,22350,6,0,0,0,0,0,0,0,0,0,'Central Gehenna Teleporter - Quest Credit'),
(2235101,22351,8,0,100,1,38920,-1,100,100,33,22351,6,0,0,0,0,0,0,0,0,0,'Eastern Gehenna Teleporter - Quest Credit');
