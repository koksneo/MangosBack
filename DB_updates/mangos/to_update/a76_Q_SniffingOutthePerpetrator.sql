-- Quest Sniffing Out the Perpetrator (12855)

DELETE FROM creature WHERE id = 29695;
INSERT INTO creature VALUES (12040777,29695,571,1,1,0,857,7312.01,-1616.42,946.014,1.47662,300,5,0,12175,0,0,0);

DELETE from creature_ai_scripts WHERE creature_id=29695;
INSERT INTO creature_ai_scripts VALUES 
(2969501,29695,10,0,100,1,0,15,2000,2000,33,29677,6,0,0,0,0,0,0,0,0,0,'Complete first quest objective after los event occured(quest 12855), NPC 29695');

UPDATE creature_template SET 
AIName='EventAI'
WHERE entry=29695;

DELETE from spell_scripts WHERE id=61122;
INSERT INTO spell_scripts (id,delay,command,datalong,datalong2)VALUES
(61122,0,15,55038,0);

UPDATE creature_loot_template SET ChanceOrQuestChance=100, groupid=2 WHERE item=40971;

