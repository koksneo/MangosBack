-- Heroic Training Dummy (31146) 

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=31146;

-- No movement and attack, combat reset
DELETE FROM creature_ai_scripts WHERE creature_id=31146;
INSERT INTO creature_ai_scripts VALUES
(3114601,31146,4,0,100,0,0,0,0,0,21,0,0,0,20,0,0,0,0,0,0,0,'Heroic Training Dummy - No movement and attack'),
(3114602,31146,9,0,100,1,30,100,10000,10000,24,0,0,0,0,0,0,0,0,0,0,0,'Heroic Training Dummy - Combat Stop');

DELETE FROM creature WHERE id=31146;
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType) VALUES
(48323, 31146, 1, 1, 1, 27510, 0, 9999.41, 2252.81, 1329.65, 3.75246, 180, 0, 0, 9999982, 0, 0, 0),
(48324, 31146, 1, 1, 1, 27510, 0, 9908.89, 2251.49, 1330.83, 5.8294, 180, 0, 0, 9999982, 0, 0, 0),
(48325, 31146, 0, 1, 1, 27510, 0, -4927.08, -1189.76, 501.737, 2.9147, 180, 0, 0, 9999982, 0, 0, 0),
(48326, 31146, 0, 1, 1, 27510, 0, 1764.94, 351.16, -62.205, 4.92183, 180, 0, 0, 9999982, 0, 0, 0),
(88224, 31146, 530, 1, 1, 27510, 0, -3839.4, -11318, -126.477, 4.17134, 180, 0, 0, 9999982, 0, 0, 0),
(151133, 31146, 0, 1, 1, 0, 0, -9118.64, 368.669, 93.5581, 1.37165, 25, 0, 0, 9999982, 0, 0, 0),
(151132, 31146, 1, 1, 1, 0, 0, 1544.55, -4430.83, 11.0681, 5.52732, 25, 0, 0, 9999982, 0, 0, 0);