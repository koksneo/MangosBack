-- Support for quests (Planning for the Future)
DELETE from npc_spellclick_spells Where npc_entry = 26200;
INSERT into npc_spellclick_spells VALUES
(26200,46773,11960,1,11960,3),
(26200,46167,11960,1,11960,1);
