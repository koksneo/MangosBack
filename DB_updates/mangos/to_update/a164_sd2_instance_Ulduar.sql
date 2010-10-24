-- Instance Ulduar - script_texts

-- Ignis the Furnace Master
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1610029 AND -1610020;
INSERT INTO `script_texts` VALUES
(-1610020,'Insolent whelps! Your blood will temper the weapons used to reclaim this world!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15564,1,0,0,'IGNIS_AGGRO'),
(-1610021,'Let the inferno consume you!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15567,1,0,0,'IGNIS_SCORCH_1'),
(-1610022,'BURN! Burn in the makers fire!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15568,1,0,0,'IGNIS_SCORCH_2'),
(-1610023,'I will burn away your impurities!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15566,1,0,0,'IGNIS_SLAG_POT'),
(-1610024,'Ignis the Furnace Master begins to cast Flame Jets!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_FLAME_JETS'),
(-1610025,'Arise, soldiers of the Iron Crucible! The Makers will be done! ',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15565,1,0,0,'IGNIS_SUMMON'),
(-1610026,'More scraps for the scrapheap!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15569,1,0,0,'IGNIS_SLAY_1'),
(-1610027,'Your bones will serve as kindling!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15570,1,0,0,'IGNIS_SLAY_2'),
(-1610028,'Let it be finished!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15571,1,0,0,'IGNIS_BERSERK'),
(-1610029,'I. Have. Failed.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15572,1,0,0,'IGNIS_DEATH');
