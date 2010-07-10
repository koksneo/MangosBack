-- Aura:Scarlet Raven Priest Image availeble only inside New Hearthglen (Dragonblight) and with accepted Q:A Fall from Grace  
DELETE FROM spell_area WHERE spell IN (48763,48761);  
INSERT INTO spell_area VALUES  
(48763,4180,12274,1,12274,0,690,2,0),  
(48761,4180,12274,1,12274,0,690,1,0);  
  
-- A Fall from Grace  
UPDATE quest_template SET startscript = 12274, completescript = 12274 WHERE entry = 12274;  
-- Spell: A Fall from Grace: Quest Accept (triggering transform auras)  
DELETE FROM quest_start_scripts WHERE id = 12274;  
INSERT INTO quest_start_scripts VALUES  
(12274,1,15,48774,0,0,0,0,0,0);  
  
-- A Fall from Grace: Quest Completion (triggering spell removing transforming auras)  
DELETE FROM quest_end_scripts WHERE id = 12274;  
INSERT INTO quest_end_scripts VALUES  
(12274,1,15,48765,0,0,0,0,0,0);