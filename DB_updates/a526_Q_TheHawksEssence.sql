-- Support for quest The Hawk's Essence (10992)

DELETE FROM creature_ai_scripts where creature_id=22992;
INSERT INTO creature_ai_scripts VALUES 
(2299201, 22992, 11, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 20, 0, 0, 0, 18, 2, 0, 0, 'Guardian of the Hawk - Set Unattackable'),
 (2299202, 22992, 11, 0, 100, 0, 0, 0, 0, 0, 5, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Emote Ready Unarmed'),
 (2299203, 22992, 1, 0, 100, 0, 1000, 1000, 0, 0, 1, -238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Say 1'),
(2299204, 22992, 1, 0, 100, 0, 7500, 7500, 0, 0, 1, -239, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Say 2'),
(2299205, 22992, 1, 0, 100, 0, 12000, 12000, 0, 0, 21, 1, 0, 0, 20, 1, 0, 0, 19, 2, 0, 0, 'Guardian of the Hawk - Set Attackable'),
(2299206, 22992, 1, 0, 100, 0, 12000, 12000, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Remove Emote'),
(2299207, 22992, 0, 0, 100, 1, 2000, 2000, 60000, 60000, 11, 40412, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Cast Curse of Blood'),
(2299208, 22992, 0, 0, 100, 1, 5000, 5000, 10000, 10000, 11, 40358, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Cast Death Hammer'),
(2299209, 22992, 0, 0, 100, 1, 8000, 8000, 10000, 10000, 11, 40413, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Hawk - Cast Throw');
