DELETE FROM creature_template_addon WHERE entry IN (19921,19833);

DELETE FROM creature_ai_scripts WHERE creature_id IN (19833,19921);
INSERT INTO creature_ai_scripts VALUES
-- Venomous Snake
(1983301,19833,0,0,25,7,1000,3000,3000,3000, 11,34655,1,32, 0,0,0,0, 0,0,0,0,'Venomus Snake (Snake Trap - Deadly Poison)'),
-- Viper
(1992101,19921,0,0,25,7,1000,3000,3000,3000, 11,30981,1,32, 0,0,0,0, 0,0,0,0,'Viper (Snake Trap - Crippling Poison)'),
(1992102,19921,0,0,25,7,1000,3000,3000,3000, 11,25810,1,32, 0,0,0,0, 0,0,0,0,'Viper (Snake Trap - Mind Numbing Poison)');

-- make them friendly for each other that they won't attack at stats (player faction) apply
UPDATE creature_template SET
mindmg = 38,
maxdmg = 53,
attackpower = 0,
dmg_multiplier = 1,
faction_A = 35,
faction_H = 35,
-- no XP at kill | no crushing
flags_extra = flags_extra |64 |32,
AIName = 'EventAI'
WHERE entry = 19921;

UPDATE creature_template SET
mindmg = 16,
maxdmg = 24,
attackpower = 0,
dmg_multiplier = 1,
faction_A = 35,
faction_H = 35,
-- no XP at kill | no crushing
flags_extra = flags_extra |64 |32,
AIName = 'EventAI'
WHERE entry = 19833;
