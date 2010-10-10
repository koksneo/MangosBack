-- Support for quest Cohlien Frostweaver (10307)

DELETE FROM creature WHERE id=19550;

-- event 12610
DELETE FROM event_scripts WHERE id=12610;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,datalong3,data_flags,dataint,x,y,z,o) VALUES
(12610,0,10,19550,4000,0,0,0,2202.37,2412.08,109.269,5.2709),
(12610,3,0,0,19545,15,0x02,2000007003,0,0,0,0);

DELETE FROM db_script_string WHERE entry=2000007003;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000007003,'Phew! There\'s my lucky hat. I\'ve been looking for it everywhere.');

UPDATE creature_template SET AIName='EventAI' WHERE entry=19550;

-- 19550 trigger
DELETE FROM creature_ai_scripts WHERE creature_id=19550;
INSERT INTO creature_ai_scripts VALUES
(1955001,19550,10,0,100,1,1,10,2000,2000,16,19550,34144,6,0,0,0,0,0,0,0,0,'Cohlien Frostweaver trigger - Quest Credit'),
(1955002,19550,1,0,100,0,1000,1000,1000,1000,32,19545,6,19545,0,0,0,0,0,0,0,0,'Cohlien Frostweaver trigger - Summon Cohlien Frostweaver');

DELETE FROM creature_ai_summons WHERE id=19545;
INSERT INTO creature_ai_summons VALUES
(19545,2203.13,2411.59,108.772,2.54312,5000,'Cohlien Frostweaver Spawn Place');

-- Cohlien Frostweaver 19545
UPDATE creature_template SET MovementType=0 WHERE entry=19545;
-- faction 1810
DELETE FROM creature_ai_scripts WHERE creature_id=19545;
INSERT INTO creature_ai_scripts VALUES
(1954501,19545,1,0,100,0,0,0,0,0,21,0,0,0,22,0,0,0,0,0,0,0,'Cohlien Frostweaver - Prevent Combat Movement and Set Phase to 0 on Spawn'),
(1954502,19545,4,0,100,0,0,0,0,0,11,9672,1,0,23,1,0,0,0,0,0,0,'Cohlien Frostweaver - Cast Frostbolt and Set Phase 1 on Aggro'),
(1954503,19545,9,13,100,1,0,40,3400,4800,11,9672,1,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Cast Frostbolt (Phase 1)'),
(1954504,19545,3,13,100,0,7,0,0,0,21,1,0,0,23,1,0,0,0,0,0,0,'Cohlien Frostweaver - Start Combat Movement and Set Phase 2 when Mana is at 7% (Phase 1)'),
(1954505,19545,9,13,100,0,35,80,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Start Combat Movement at 35 Yards (Phase 1)'),
(1954506,19545,9,13,100,0,5,15,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Prevent Combat Movement at 15 Yards (Phase 1)'),
(1954507,19545,9,13,100,0,0,5,0,0,21,1,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Start Combat Movement Below 5 Yards (Phase 1)'),
(1954508,19545,3,11,100,1,100,15,100,100,23,-1,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Set Phase 1 when Mana is above 15% (Phase 2)'),
(1954509,19545,9,0,100,1,0,8,15000,19000,11,11831,0,1,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Cast Frost Nova'),
(1954510,19545,0,0,100,1,3000,5000,45000,60000,11,33245,0,1,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Cast Ice Barrier'),
(1954511,19545,2,0,100,0,15,0,0,0,22,3,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Set Phase 3 at 15% HP'),
(1954512,19545,2,7,100,0,15,0,0,0,21,1,0,0,25,0,0,0,1,-47,0,0,'Cohlien Frostweaver - Start Combat Movement and Flee at 15% HP (Phase 3)'),
(1954513,19545,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Set Phase to 0 on Evade'),
(1954514,19545,11,0,100,0,0,0,0,0,2,35,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Friendly faction on Spawn'),
(1954515,19545,1,0,100,0,4000,4000,0,0,2,1810,0,0,0,0,0,0,0,0,0,0,'Cohlien Frostweaver - Friendly faction on Spawn');
