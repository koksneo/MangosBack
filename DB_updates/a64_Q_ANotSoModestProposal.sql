-- Support for quest A Not-So-Modest Proposal

UPDATE gameobject_template SET
ScriptName='go_Ethereal_Teleport_pad'
WHERE entry=184073;
UPDATE creature_template SET MovementType=0 WHERE entry=20518;
