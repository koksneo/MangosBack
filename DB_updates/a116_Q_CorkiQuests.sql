-- Support for quest HELP! (9923), Corki's Gone Missing Again! (9924), Cho'war the Pillager (9955)

# Connect with sd2
UPDATE gameobject_template SET ScriptName='go_corkis_prison', data2=3000 WHERE entry IN (182349,182350,182521);
#
UPDATE creature_template SET npcflag=npcflag&~1 WHERE entry=18369;
# Corki Spawns
DELETE FROM creature WHERE guid IN (65849,65786);
INSERT INTO creature VALUES
(65849,18369,530,1,1,0,0,-2563.89,6288.29,15.295,5.23599,300,0,0,25000,0,0,0),
(65786,18445,530,1,1,0,0,-918.143,8663.94,172.542,0.523599,300,0,0,24895,0,0,0);

# Quest relations and involved relations
DELETE FROM creature_questrelation WHERE quest IN (9923,9924,9954,9955);
INSERT INTO creature_questrelation VALUES
(18369,9923),
(18183,9924),
(18183,9954),
(18445,9955);
DELETE FROM creature_involvedrelation WHERE quest IN (9923,9924,9954,9955);
INSERT INTO creature_involvedrelation VALUES
(18183,9923),
(18183,9924),
(18445,9954),
(18183,9955);


# Warmaul Chef Bufferlo (18440)

UPDATE creature_template SET AIName='EventAI', equipment_id=1380 WHERE entry=18440;

DELETE FROM creature_ai_scripts WHERE creature_id=18440;
INSERT INTO creature_ai_scripts VALUES
(1844001,18440,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Random Phase'),
(1844002,18440,1,1,100,0,40000,40000,40000,40000,30,2,3,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Random Phase'),
(1844003,18440,4,0,100,0,0,0,0,0,1,-184401,-184402,-184403,11,31994,6,3,22,0,0,0,'Warmaul Chef Bufferlo - Yell on Aggro and Cast Shoulder Charge'),
(1844004,18440,1,2,100,0,1000,1000,0,0,1,-184404,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 1 (Phase 2)'),
(1844005,18440,1,2,100,0,6000,6000,0,0,1,-184405,0,0,22,1,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 2 and Set Phase 1 (Phase 2)'),
(1844006,18440,1,3,100,0,1000,1000,0,0,1,-184406,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 1 (Phase 3)'),
(1844007,18440,1,3,100,0,6000,6000,0,0,1,-184407,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 2 (Phase 3)'),
(1844008,18440,1,3,100,0,11000,11000,0,0,1,-184408,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 3 (Phase 3)'),
(1844009,18440,1,3,100,0,16000,16000,0,0,1,-184409,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 4 (Phase 3)'),
(1844010,18440,1,3,100,0,21000,21000,0,0,1,-184410,0,0,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 5 (Phase 3)'),
(1844011,18440,1,3,100,0,26000,26000,0,0,1,-184411,0,0,22,1,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Say 6 (Phase 3)'),
(1844012,18440,9,0,100,1,8,25,5000,5000,11,31994,6,3,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Cast Shoulder Charge'),
(1844013,18440,0,0,100,1,5000,10000,5000,10000,11,32378,1,3,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Cast Filet'),
(1844014,18440,0,0,100,1,5000,10000,5000,10000,11,32376,1,3,0,0,0,0,0,0,0,0,'Warmaul Chef Bufferlo - Cast Tenderize');

DELETE FROM creature_ai_texts WHERE entry IN (-184401,-184402,-184403,-184404,-184405,-184406,-184407,-184408,-184409,-184410,-184411);
INSERT INTO creature_ai_texts (entry,content_default,type,comment) VALUES
(-184401,'IT DUZ WUT IT\'S TOLD!',1,'Warmaul Chef Bufferlo Aggro 1'),
(-184402,'GET IN DA STEW!',1,'Warmaul Chef Bufferlo Aggro 2'),
(-184403,'YOU GUD IN DA BELLY!',1,'Warmaul Chef Bufferlo Aggro 3'),
(-184404,'Your daddy pay Warmaul and maybe we no eat you.',0,'Warmaul Chef Bufferlo say 1'),
(-184405,'Ha-ha! Just kidding. We eat you for shure anyway.',0,'Warmaul Chef Bufferlo say 2'),
(-184406,'First you need da spices.',0,'Warmaul Chef Bufferlo Recipe 1'),
(-184407,'Da salt goes into da pot...',0,'Warmaul Chef Bufferlo Recipe 2'),
(-184408,'Den you put da pepper in da pot...',0,'Warmaul Chef Bufferlo Recipe 3'),
(-184409,'Now we gonna kick it pu a notch wit da secret ingra... ingor... inrag... da secret sauce!',0,'Warmaul Chef Bufferlo Recipe 4'),
(-184410,'And last, we put in da Corki!',0,'Warmaul Chef Bufferlo Recipe 5'),
(-184411,'BAM! Look at dat gristle sizzle!',0,'Warmaul Chef Bufferlo Recipe 6');

# Cho'war the Pillager (18423)

UPDATE creature_template SET AIName='EventAI' WHERE entry=18423;

DELETE FROM creature_ai_scripts WHERE creature_id=18423;
INSERT INTO creature_ai_scripts VALUES
(1842301,18423,4,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Cho\'war the Pillager - Random Phase'),
(1842302,18423,9,0,100,1,8,25,5000,5000,11,32323,6,3,0,0,0,0,0,0,0,0,'Cho\'war the Pillager - Cast Charge'),
(1842303,18423,0,0,100,1,5000,10000,5000,10000,11,17963,1,0,0,0,0,0,0,0,0,0,'Cho\'war the Pillager - Cast Sundering Cleave'),
(1842304,18423,0,0,100,1,5000,10000,5000,10000,11,15708,1,3,0,0,0,0,0,0,0,0,'Cho\'war the Pillager - Cast Mortal Strike');
