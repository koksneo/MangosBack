### Add Icecrown Flying Crew into world ###

# Temporary fix. I make NPCs from airships unattackable and unable to attack somebody.
# That isn't propely way, I know. But I added these npcs into neutral place - The Argent Vanguard.
# Here you've got how it looks like -> http://img188.imageshack.us/f/92194420.jpg/

DELETE FROM creature WHERE guid IN (3034501,3034401,3230201,2979901,3125901,3082501,3082401,3230101,2979501,3126101);
INSERT INTO creature VALUES
(3034501,30345,571,1,1,0,1007,6115.17,-17.2893,383.511,5.41453,300,0,0,5342,0,0,0),
(3034401,30344,571,1,1,0,1648,6112.2,-21.0034,383.511,5.5292,300,0,0,21368,0,0,0),
(3230201,32302,571,1,1,0,788,6109.62,-22.8754,383.511,5.23153,300,0,0,630000,0,0,0),
(2979901,29799,571,1,1,0,613,6107.71,-25.2567,383.511,5.21897,300,0,0,252000,0,0,0),
(3125901,31259,571,1,1,0,0,6105.16,-29.0231,383.511,5.38312,300,0,0,37800,31952,0,0),
(2979501,29795,571,1,1,0,647,6123.55,-29.6481,383.51,2.35456,300,0,0,252000,79880,0,0),
(3126101,31261,571,1,1,0,0,6115.35,-37.6508,383.511,2.56816,300,0,0,37800,31952,0,0),
(3082501,30825,571,1,1,0,1007,6117.52,-35.5651,383.511,2.23201,300,0,0,5342,0,0,0),
(3082401,30824,571,1,1,0,1884,6119.58,-33.5227,383.511,2.34753,300,0,0,21368,0,0,0),
(3230101,32301,571,1,1,0,996,6121.4,-31.6183,383.511,2.29772,300,0,0,630000,0,0,0);

UPDATE creature_template SET 
unit_flags=unit_flags|2,
AIName='EventAI'
WHERE entry IN (29795,32301,30824,30825,31261,30345,30344,32302,29799,31259);

DELETE FROM creature_ai_scripts WHERE creature_id IN (29795,32301,30824,30825,31261,30345,30344,32302,29799,31259);
INSERT INTO creature_ai_scripts VALUES
(2979501,29795,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3230101,32301,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3082401,30824,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3082501,30825,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3126101,31261,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3034501,30345,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3034401,30344,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3230201,32302,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(2979901,29799,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)'),
(3125901,31259,4,0,100,0,0,0,0,0,14,-100,0,0,21,0,0,0,24,0,0,0,'Icecrown Flying Npc - Reset threat on Aggro (ANDEERIA TEMP)');
