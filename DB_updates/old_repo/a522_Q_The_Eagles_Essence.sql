-- Support for quest The Eagle's Essence (10990)

DELETE FROM creature_ai_scripts where creature_id=22993;
INSERT INTO `creature_ai_scripts` VALUES 
(2299301,22993,11,0,100,0,0,0,0,0,21,0,0,0,20,0,0,0,18,2,0,0,'Guardian of the Eagle - Set Unattackable'),
(2299302,22993,11,0,100,0,0,0,0,0,5,27,0,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Emote Ready Unarmed'),
(2299303,22993,1,0,100,0,1000,1000,0,0,1,-240,0,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Say 1'),
(2299304,22993,1,0,100,0,7500,7500,0,0,1,-241,0,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Say 2'),
(2299305,22993,1,0,100,0,12000,12000,0,0,21,1,0,0,20,1,0,0,19,2,0,0,'Guardian of the Eagle - Set Attackable'),
(2299306,22993,1,0,100,0,12000,12000,0,0,5,0,0,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Remove Emote'),
(2299307,22993,0,0,100,1,100,100,7000,7000,11,9739,1,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Cast Wrath'),
(2299308,22993,0,0,100,1,3000,3000,7000,7000,11,40339,1,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Summon Eagle Add'),
(2299309,22993,0,0,100,1,10000,10000,13000,13000,11,40344,1,0,0,0,0,0,0,0,0,0,'Guardian of the Eagle - Cast Starfire');
