-- Quest: The Heart of the Storm (12998)
UPDATE gameobject_template SET
ScriptName = "go_heart_of_the_storm"
WHERE entry = 192181;

-- Overseer Narvir
UPDATE creature_template SET
minlevel = 79,
maxlevel = 79,
minhealth = 11770,
maxhealth = 12175,
faction_A = 14,
faction_H = 14,
unit_flags = 512,
AIName = "",
ScriptName="npc_overseer_narvir",
equipment_id = 749,
MovementType = 0
WHERE entry = 30299;
