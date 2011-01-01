UPDATE creature_template SET
ScriptName='npc_jaloot_zepik',
`mechanic_immune_mask` = mechanic_immune_mask|1 |4 |16 |64 |256 |512 |1024 |2048 |65536 |131072 |33554432 
WHERE entry IN(28667,28668);

DELETE FROM gameobject WHERE guid = '797658';
INSERT INTO gameobject VALUES ( 797658, 190777, 571, 1,1,5626.18, 3796.75, -91.2137, 4.1744, 0, 0, 0.8696, -0.493757, -25, 0, 1);

UPDATE creature_template SET
ScriptName='npc_artruis',
`mechanic_immune_mask` = mechanic_immune_mask|1 |4 |16 |64 |256 |512 |1024 |2048 |65536 |131072 |33554432 ,
AIName=''
WHERE entry=28659;

UPDATE creature_addon SET
auras='50726 0 52119 0 52119 1'
WHERE guid=88795;

UPDATE creature_addon SET
auras='54176 0'
WHERE guid=88796;


