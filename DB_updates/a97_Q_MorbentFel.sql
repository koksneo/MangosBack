# Quest: Morbent Fel (55)

UPDATE creature_template SET AIName='EventAI', ScriptName='' WHERE entry=1200;

DELETE from creature_ai_scripts WHERE creature_id=1200;
INSERT INTO `creature_ai_scripts` VALUES 
(120001, 1200, 0, 0, 100, 1, 0, 0, 3700, 13300, 11, 3108, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel - Cast Touch of Death'),
(120002, 1200, 0, 0, 100, 1, 0, 0, 24000, 24000, 11, 3109, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel - Cast Presence of Death'),
(120003, 1200, 2, 0, 100, 0, 15, 0, 0, 0, 28, 0, 8909, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel - Remove Unholy Aura at 15% HP'),
(120004, 1200, 8, 0, 100, 0, 8913, -1, 0, 0, 36,24782, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel - Update template after spellhit');
