-- Support for quest Abjurist Belmara (10305)

DELETE FROM creature WHERE id=19547;

-- event 12607
DELETE FROM event_scripts WHERE id=12607;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,datalong3,data_flags,dataint,x,y,z,o) VALUES
(12607,0,10,19547,4000,0,0,0,2239.45,2389.64,112.748,3.61283),
(12607,3,0,0,19546,15,0x02,2000007004,0,0,0,0);

DELETE FROM db_script_string WHERE entry=2000007004;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000007004,'I can\'t sleep without a good bedtime story. Now I\'m cerain to rest well.');

UPDATE creature_template SET AIName='EventAI' WHERE entry=19547;

-- 19547 trigger
DELETE FROM creature_ai_scripts WHERE creature_id=19547;
INSERT INTO creature_ai_scripts VALUES
(1954701,19547,10,0,100,1,1,10,2000,2000,16,19547,34140,6,0,0,0,0,0,0,0,0,'Abjurist Belmara trigger - Quest Credit'),
(1954702,19547,1,0,100,0,1000,1000,1000,1000,32,19546,6,19546,0,0,0,0,0,0,0,0,'Abjurist Belmara trigger - Summon Abjurist Belmara');

DELETE FROM creature_ai_summons WHERE id=19546;
INSERT INTO creature_ai_summons VALUES
(19546,2240.49,2390.42,112.522,3.96646,5000,'Abjurist Belmara Spawn Place');

-- Abjurist Belmara 19546
UPDATE creature_template SET MovementType=0 WHERE entry=19546;

DELETE FROM creature_ai_scripts WHERE creature_id=19546;
INSERT INTO creature_ai_scripts VALUES
(1954601,19546,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Abjurist Belmara - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(1954602,19546,1,0,100,1,1000,1000,1800000,1800000,11,12544,0,1,0,0,0,0,0,0,0,0,'Abjurist Belmara - Cast Frost Armor on Spawn'),
(1954603,19546,4,0,100,0,0,0,0,0,11,34447,1,0,23,1,0,0,0,0,0,0,'Abjurist Belmara - Cast Arcane Missiles and Set Phase 1 on Aggro'),
(1954604,19546,9,13,100,1,0,30,3400,4800,11,34447,1,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Cast Arcane Missiles (Phase 1)'),
(1954605,19546,3,13,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Abjurist Belmara - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'),
(1954606,19546,9,13,100,0,25,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Start Combat Movement at 25 Yards (Phase 1)'),
(1954607,19546,9,13,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Prevent Combat Movement at 15 Yards (Phase 1)'),
(1954608,19546,9,13,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Start Combat Movement Below 5 Yards (Phase 1)'),
(1954609,19546,3,11,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Set Phase 1 when Mana is above 15% (Phase 2)'),
(1954610,19546,2,0,100,0,50,0,0,0,11,17740,0,1,0,0,0,0,0,0,0,0,'Abjurist Belmara - Cast Mana Shield at 50% HP'),
(1954611,19546,2,0,100,0,15,0,0,0,22,3,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Set Phase 3 at 15% HP'),
(1954612,19546,2,7,100,0,15,0,0,0,21,1,0,0,25,0,0,0,1,-47,0,0,'Abjurist Belmara - Start Combat Movement and Flee at 15% HP (Phase 3)'),
(1954613,19546,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Set Phase to 0 on Evade'),
(1954614,19546,11,0,100,0,0,0,0,0,2,35,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Friendly faction on Spawn'),
(1954615,19546,1,0,100,0,4000,4000,0,0,2,1810,0,0,0,0,0,0,0,0,0,0,'Abjurist Belmara - Friendly faction on Spawn');
