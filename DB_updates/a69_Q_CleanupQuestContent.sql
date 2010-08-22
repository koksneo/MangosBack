-- Cleanup for Quest Content

## Old Naxxramas Quests


DELETE FROM creature_questrelation WHERE quest IN (9229,9230,9034,9036,9037,9038,9039,9040,9041,9042);
DELETE FROM quest_template WHERE entry IN (9229,9230,9034,9036,9037,9038,9039,9040,9041,9042);
DELETE FROM creature_involvedrelation WHERE quest IN (9229,9230,9034,9036,9037,9038,9039,9040,9041,9042);
