-- Support for quest Hard to Swallow (12049)

DELETE from creature_ai_scripts WHERE id BETWEEN 2629302 AND 2629306;
INSERT INTO creature_ai_scripts VALUES 
(2629302,26293,11,0,100,0,0,0,0,0,0,0,0,0,22,0,0,0,0,0,0,0,'Hulking Jormungar-Set Phase to 0 on Spawn'),
(2629303,26293,4,0,100,0,0,0,0,0,0,0,0,0,22,1,0,0,0,0,0,0,'Hulking Jormungar - Set Phase 1 on Aggro'),
(2629304,26293,2,0,100,0,70,50,0,0,22,3,0,0,1,-262930,0,0,0,0,0,0,'Hulking Jormungar - Set Phase 3 on 70% HP'),
(2629305,26293,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Hulking Jormungar- Set Phase to 0 on Evade'),
(2629306,26293,8,6,100,0,47305,-1,0,0,11,47315,0,7,11,47306,0,1,0,0,0,0,'Hulking Jormungar - Create jormungar meat and explode after spellhit(47305)');

DELETE FROM creature_ai_texts WHERE entry=-262930;
INSERT INTO creature_ai_texts (entry, content_default,type,comment) VALUES
(-262930,"The Hulking Jormungar falters for a moment, opening its mouth wide.",3,'Hulking Jormungar-raid emote');

DELETE FROM item_required_target WHERE entry=36732;
INSERT INTO item_required_target VALUES
(36732,1,26293);
