-- Support for quest A hero's Headgear

DELETE FROM item_required_target WHERE entry=39651;
INSERT INTO item_required_target VALUES
(39651,2,28877);

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=28877;

DELETE FROM creature_ai_scripts WHERE id=2887702;
INSERT INTO creature_ai_scripts VALUES
(2887702,28877,8,0,100,0,53145,-1,0,0,11,53162,0,3,0,0,0,0,0,0,0,0,'Summon stormwatcher head after spellhit');
