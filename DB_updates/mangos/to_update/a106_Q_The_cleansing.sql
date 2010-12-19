-- Quest The cleansing (11322)
DELETE FROM spell_script_target WHERE entry=50218;
INSERT INTO spell_script_target VALUES
(50218,1,27959);


DELETE from db_script_string WHERE entry BETWEEN 2000008010 AND 2000008013;
INSERT into db_script_string (entry,content_default) VALUES
(2000008010,'You think that you can get rid of me through meditation?'),
(2000008011,'Fool! I will destroy you and finally become that which has been building inside of you all these years!'),
(2000008012,'You cannot defeat me. I\'m an inseparable part of you!'),
(2000008013,'NOOOOOOOoooooooooo!');

DELETE from spell_scripts WHERE id=43365;
INSERT into spell_scripts (id,delay,command,datalong,datalong2,datalong3,datalong4,data_flags,dataint,x,y,z,o) VALUES
(43365,1,10,27959,30000,0,0,0,0,3035.99, -5092.22,722.615,0.771381),
(43365,1,0,1,27959,15,0,0x02,2000008010,0,0,0,0),
(43365,4,0,1,27959,15,0,0x02,2000008011,0,0,0,0),
(43365,9,0,1,27959,15,0,0x02,2000008012,0,0,0,0),
(43365,13,0,1,27959,15,0,0x02,2000008013,0,0,0,0);

UPDATE creature_template SET
minlevel=70,
maxlevel=70,
minhealth=8982,
maxhealth=8982,
armor=7461,
faction_A=15,
faction_H=15,
mindmg=315,
maxdmg=389,
dmg_multiplier=2,
attackpower=189
WHERE entry=27959;
