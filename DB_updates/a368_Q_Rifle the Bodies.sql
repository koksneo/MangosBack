-- Support for quests (11999,12000) (Rifle the Bodies A and H)
DELETE FROM npc_spellclick_spells WHERE npc_entry = 26477;
INSERT INTO npc_spellclick_spells VALUES
(26477,47096,12000,1,12000,3),
(26477,61832,12000,1,12000,1),
(26477,47096,11999,1,11999,3),
(26477,61832,11999,1,11999,1);
