-- Quest Rivenwood Captives (11296)

DELETE FROM creature WHERE id=24209;
INSERT INTO creature (id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType)VALUES
('24209', '571', '1', '1', '0', '542', '2127.63', '-3292.62', '152.45', '3.14', '300', '0', '0', '9291', '3231', '0', '0');

UPDATE creature_template SET AIName='EventAI' WHERE entry=24210;

DELETE FROM creature_ai_scripts WHERE creature_id= 24210;
INSERT INTO creature_ai_scripts VALUES
('2421001', '24210', '11', '0', '100', '0', '0', '0', '0', '0', '21', '0', '0', '0', '18', '2097152', '0', '0', '23', '1', '0', '0', 'Riven Widow Cocon-Prevent Combat Movement and Set Unit Flags and Set Phase 2 on Spawn'),
('2421002', '24210', '6', '1', '10', '0', '0', '0', '0', '0', '12', '23990', '0', '60000', '0', '0', '0', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Summon Gjalerbron Rune-Caster'),
('2421003', '24210', '6', '1', '10', '0', '0', '0', '0', '0', '12', '23989', '0', '60000', '0', '0', '0', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Summon Gjalerbron Sleep-Watcher'),
('2421004', '24210', '6', '1', '10', '0', '0', '0', '0', '0', '12', '23991', '0', '60000', '0', '0', '0', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Summon Gjalerbron Warrior'),
('2421005', '24210', '6', '1', '70', '0', '0', '0', '0', '0', '12', '24211', '0', '60000', '33', '24211', '6', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Summon Freed Winterhoof Longrunner'),
('2421006', '24210', '6', '1', '20', '0', '0', '0', '0', '0', '41', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Chance To Despawn on Death'),
('2421007', '24210', '7', '0', '100', '0', '0', '0', '0', '0', '22', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Riven Widow Cocoon-Set Phase to 0 on Evade');
