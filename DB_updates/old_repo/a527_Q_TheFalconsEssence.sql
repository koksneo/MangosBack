-- Support for quest The Falcon's Essence (10991)

DELETE FROM creature_ai_scripts WHERE creature_id=22994;
INSERT INTO creature_ai_scripts VALUES 
(2299401, 22994, 11, 0, 100, 0, 0, 0, 0, 0, 21, 0, 0, 0, 20, 0, 0, 0, 18, 2, 0, 0, 'Guardian of the Falcon - Set Unattackable'),
(2299402, 22994, 11, 0, 100, 0, 0, 0, 0, 0, 5, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Emote Ready Unarmed'),
(2299403, 22994, 1, 0, 100, 0, 1000, 1000, 0, 0, 1, -242, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Say 1'),
(2299404, 22994, 1, 0, 100, 0, 7500, 7500, 0, 0, 1, -243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Say 2'),
(2299405, 22994, 1, 0, 100, 0, 12000, 12000, 0, 0, 21, 1, 0, 0, 20, 1, 0, 0, 19, 2, 0, 0, 'Guardian of the Falcon - Set Attackable'),
(2299406, 22994, 1, 0, 100, 0, 0, 0, 12000, 12000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Remove Emote'),
(2299407, 22994, 0, 0, 100, 1, 2000, 2000, 10000, 10000, 11, 40367, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Cast Twisting Blast'),
(2299408, 22994, 0, 0, 100, 1, 6000, 6000, 10000, 10000, 11, 9613, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Guardian of the Falcon - Cast Shadow Bolt');
