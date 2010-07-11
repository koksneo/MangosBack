-- Shadowfang Keep prisoners (powinni miec tylko falgs extra na 2 ale dla pewnosci lepiej juz bedzie zapewnic im frakcje 35)
UPDATE creature_template SET flags_extra = flags_extra|2, faction_A = 35, faction_H = 35 WHERE scriptname = 'npc_shadowfang_prisoner';
