# Quest: Plan B (11658)

DELETE from spell_scripts WHERE id=45713;
INSERT into spell_scripts (id,delay,command,datalong,datalong2) VALUES
(45713,0,17,34842,1),
(45713,1,18,5,0);

DELETE from npc_spellclick_spells WHERE npc_entry IN(25343,25342);
INSERT into npc_spellclick_spells VALUES
(25343,45713,11658,1,11658,1),
(25342,45713,11658,1,11658,1),
(25343,45713,11658,1,11658,0),
(25342,45713,11658,1,11658,0);

UPDATE creature_template SET
npcflag=npcflag &~1
where entry IN(25343,25342);
