-- Data Mining (12860)

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=29746;

DELETE from creature_ai_scripts WHERE creature_id=29746;
INSERT INTO creature_ai_scripts VALUES 
(2974601,29746,8,0,100,1,55161,-1,0,0,33,29752,6,0,41,6000,0,0,0,0,0,0,'Databank-quest credit after spell hit and despawn(6sec delay)');
