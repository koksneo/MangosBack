-- Glyph of Blocking
DELETE FROM `spell_proc_event` WHERE entry IN (58375,58388);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMaskA0`, `SpellFamilyMaskA1`, `SpellFamilyMaskA2`, `SpellFamilyMaskB0`, `SpellFamilyMaskB1`, `SpellFamilyMaskB2`, `SpellFamilyMaskC0`, `SpellFamilyMaskC1`, `SpellFamilyMaskC2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(58375, 0, 4, 0, 0, 0, 512, 512, 512, 0, 0, 0, 16, 0, 0, 100, 0),

-- Glyph of Devastate
(58388, 0, 4, 0, 0, 0, 64, 64, 64, 0, 0, 0, 16, 0, 0, 100, 0);
