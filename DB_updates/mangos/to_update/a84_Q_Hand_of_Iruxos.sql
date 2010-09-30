-- Support for quest Hand of Iruxos (5381)

DELETE FROM creature WHERE id=11876;
UPDATE gameobject_template SET ScriptName='go_hand_of_iruxos_crystal' WHERE entry=176581;
UPDATE creature_template SET AIName='EventAI' WHERE entry=11876;

DELETE FROM creature_ai_scripts WHERE creature_id=11876;
INSERT INTO creature_ai_scripts VALUES
(1187601,11876,11,0,100,0,0,0,0,0,11,7741,0,3,0,0,0,0,0,0,0,0,'Demon Spirit - Summon Demon (Visual)');
