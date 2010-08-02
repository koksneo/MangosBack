-- Support for quest Kickin'Nass and Takin manes (12630)

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=28519;

DELETE FROM creature WHERE id=28523;

UPDATE creature_template SET
flags_extra=flags_extra|128
WHERE entry=28523;

DELETE FROM creature_ai_scripts WHERE creature_id=28519;
INSERT into creature_ai_scripts VALUES
(2851901,28519,6, 0, 100, 0, 0, 0, 0, 0, 12, 28523, 0, 30000, 0, 0, 0, 0, 0, 0, 0, 0, 'Withered Troll-summon Nass Target KC Bunny after death');
