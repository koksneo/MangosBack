-- Quest: Prisoners of Wyrmskull (11255)
UPDATE `gameobject_template` SET `ScriptName` = "go_dragonflayer_cage" WHERE `entry` BETWEEN 186566 AND 186575; 

UPDATE creature_template SET 
minhealth=4892 ,
maxhealth=4892,
minlevel=66,
maxlevel=66,
minmana=6588,
maxmana=6588,
mindmg=162,
maxdmg=234
WHERE entry=24099;

UPDATE creature_template SET 
minhealth=5588,
maxhealth=5588,
minlevel=68,
maxlevel=68,
minmana=6882,
maxmana=6882,
mindmg=213,
maxdmg=309
WHERE entry=24096 ;

UPDATE creature_template SET 
minhealth=6326,
maxhealth=6326,
minlevel=67,
maxlevel=67,
minmana=0,
maxmana=0,
mindmg=225,
maxdmg=314
WHERE entry=24097;

UPDATE creature_template SET 
minhealth=6116,
maxhealth=6116,
minlevel=66,
maxlevel=66,
minmana=2486,
maxmana=2486,
mindmg=195,
maxdmg=273
WHERE entry=24103;
