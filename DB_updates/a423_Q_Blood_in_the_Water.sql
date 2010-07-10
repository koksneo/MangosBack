-- Support for quest Blood in the Water (12810) by Tank

-- Gore Bladder (6509)

UPDATE creature_template SET AIName='EventAI' WHERE entry=29392;

DELETE FROM creature_ai_scripts WHERE id IN (2939201,2939202,2939203);
INSERT INTO creature_ai_scripts VALUES
 
-- Ravenous Jaws (29392)

(2939201,29392,0,0,100,1,4000,4000,9000,9000,11,3391,0,0,0,0,0,0,0,0,0,0,'Ravenous Jaws - Trash'),
(2939202,29392,6,0,100,0,0,0,0,0,11,47172,0,6,0,0,0,0,0,0,0,0,'Ravenous Jaws - Cast Underwater Blood on death'),
(2939203,29392,8,0,100,0,6509,-1,0,0,33,29391,6,0,28,0,47172,0,0,0,0,0,'Ravenous Jaws - Quest Credit after spell hit');

-- item required target for Gore Bladder (40551)
DELETE FROM item_required_target WHERE entry=40551;
INSERT INTO item_required_target VALUES
(40551,2,29392);
