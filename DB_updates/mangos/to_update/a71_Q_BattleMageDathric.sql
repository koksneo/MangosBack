-- Support for quest Battle-Mage Dathric (10182)

DELETE FROM creature WHERE id=19549;

-- event 12608
DELETE FROM event_scripts WHERE id=12608;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,datalong3,data_flags,dataint,x,y,z,o) VALUES
(12608,0,10,19549,4000,0,0,0,2228.32,2312.22,89.3019,4.93928),
(12608,3,0,0,19543,15,0x02,2000007001,0,0,0,0);

DELETE FROM db_script_string WHERE entry=2000007001;
INSERT INTO db_script_string (entry,content_default) VALUES
(2000007001,'I don\'t know what I was thinking, going out without my sword. I would\'ve put it on if I\'d seen it here...');

UPDATE creature_template SET AIName='EventAI' WHERE entry=19549;

-- 19549 trigger
DELETE FROM creature_ai_scripts WHERE creature_id=19549;
INSERT INTO creature_ai_scripts VALUES
(1954901,19549,10,0,100,1,1,10,2000,2000,16,19549,34141,6,0,0,0,0,0,0,0,0,'Battle-Mage Dathric trigger - Quest Credit'),
(1954902,19549,1,0,100,0,1000,1000,1000,1000,32,19543,6,19543,0,0,0,0,0,0,0,0,'Battle-Mage Dathric trigger - Summon Battle-Mage Dathric');

DELETE FROM creature_ai_summons WHERE id=19543;
INSERT INTO creature_ai_summons VALUES
(19543,2228.93,2312.65,89.4176,3.86324,5000,'Battle-Mage Dathric Spawn Place');

-- Battle-Mage Dathric 19543
UPDATE creature_template SET MovementType=0 WHERE entry=19543;

DELETE FROM creature_ai_scripts WHERE creature_id=19543;
INSERT INTO creature_ai_scripts VALUES
(1954301,19543,9,0,100,1,0,5,12000,16000,11,36104,0,0,0,0,0,0,0,0,0,0,'Battle-Mage Dathric - Cast Torrent of Flames'),
(1954302,19543,0,0,100,1,9000,13000,19000,24000,11,17273,4,1,0,0,0,0,0,0,0,0,'Battle-Mage Dathric - Cast Pyroblast'),
(1954303,19543,11,0,100,0,0,0,0,0,2,35,0,0,0,0,0,0,0,0,0,0,'Battle-Mage Dathric - Friendly faction on Spawn'),
(1954304,19543,1,0,100,0,4000,4000,0,0,2,1810,0,0,0,0,0,0,0,0,0,0,'Battle-Mage Dathric - Change faction to default');
