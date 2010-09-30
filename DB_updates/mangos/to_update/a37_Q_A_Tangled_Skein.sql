-- Support for quest A Tangled Skein (12555)
UPDATE creature_template SET 
AIName = 'EventAI' ,
flags_extra=flags_extra |64
WHERE entry = 28274;

DELETE FROM creature_ai_scripts WHERE creature_id=28274;
INSERT INTO creature_ai_scripts VALUES
(2827401,28274,8,0,100,0,51165,-1,0,0,11,53236,0,7,11,51314,0,0,22,3,0,0,'Plague Sprayer - After Spellhit cast explode and summon wasted plague sprayer'),
(2827402,28274,8,0,100,0,51165,-1,0,0,33,28289,6,0,0,0,0,0,0,0,0,0,'Plague Sprayer - Quest Credit'),
(2827403,28274,0,3,100,0,1000,1000, 0, 0, 24, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 'Plague Sprayer-despawn'),
(2827404,28274,11, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 'Plague Sprayer-Set Phase to 0 on Spawn, prevent combat movement');
