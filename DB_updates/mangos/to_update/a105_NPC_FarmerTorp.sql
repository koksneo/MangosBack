-- Farmer Torp (25607)

DELETE FROM creature WHERE id =25607;
INSERT INTO creature VALUES 
(12884801,25607,571,1,1,0,0,2869.423340,6385.351074,94.097244,5.26145,60,0,0,9122,0,0,0);

UPDATE creature_template SET
minlevel=70,
maxlevel=70,
minhealth=9122,
maxhealth=9122,
npcflag=npcflag|1|2 
WHERE entry='25607';
