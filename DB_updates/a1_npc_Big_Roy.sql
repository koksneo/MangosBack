-- Big Roy
UPDATE creature_template SET
InhabitType = 2,
mindmg = 300,
maxdmg = 600,
dmg_multiplier = 3,
minlevel = 71,
maxlevel = 71,
faction_A = 16,
faction_H = 16,
minhealth = 9200,
maxhealth = 9300
WHERE entry = 24785;

DELETE FROM creature WHERE id IN (24785);
INSERT INTO creature VALUES
-- Big Roy
('9000005','24785','571','1','1','0','0','-50.6926','-3285.65','-1.75731','5.6353','300','20','0','9291','0','0','1');


