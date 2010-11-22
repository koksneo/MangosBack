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

-- Razorscale
DELETE FROM `script_texts` WHERE (`entry` BETWEEN -1603026 AND -1603020) AND (`entry` IN (-1603353, -1603354));
INSERT INTO `script_texts` VALUES
(-1603020,'Welcome, champions! All of our attempts at grounding her have failed. We could use a hand in bring her down with these harpoon guns.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15647,'0',0,0,'razorscale intro - commander'),
(-1603021,'Give us a moment to prepare to build the turrets.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',NULL,NULL,'razor aggro 1 - eng'),
(-1603022,'Be on the lookout! Mole machines will be surfacing soon with those nasty Iron dwarves aboard!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor aggro 2 - commander'),
(-1603023,'Ready to move out, keep those dwarves off of our backs!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor aggro 3 - eng'),
(-1603024,'Move! Quickly! She won’t remain grounded for long.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor ground - commander'),
(-1603025,'Razorscale takes a deep breath...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'3',0,0,'razor deep breath'),
(-1603026,'Fires out! Let\'s rebuild those turrets!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,'1',0,0,'razor extinguish fires'),
(-1603353,'Harpoon Turret is ready for use!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_harpoon'),
(-1603354,'Razorscale grounded permanently!' ,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'EMOTE_ground');

-- XT-002 Deconstructor
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1610040 AND -1610030;
INSERT INTO `script_texts` VALUES
(-1610030,"New toys? For me? I promise I won't break them this time!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15724,1,0,0,'XT002 SAY_AGGRO'),
(-1610031,"So tired. I will rest for just a moment!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15725,1,0,0,'XT002 SAY_HEART_OPENED'),
(-1610032,"I'm ready to play!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15726,1,0,0,'XT002 SAY_HEART_CLOSED'),
(-1610033,"NO! NO! NO! NO! NO!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15727,1,0,0,'XT002 SAY_TYMPANIC_TANTRUM'),
(-1610034,"I... I think I broke it.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15728,1,0,0,'XT002 SAY_SLAY_1'),
(-1610035,"I guess it doesn't bend that way.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15729,1,0,0,'XT002 SAY_SLAY_2'),
(-1610036,"I'm tired of these toys. I don't want to play anymore!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15730,1,0,0,'XT002 SAY_BERSERK'),
(-1610037,"You are bad... Toys... Very... Baaaaad!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15731,1,0,0,'XT002 SAY_DEATH'),
(-1610038,"Time for a new game! My old toys will fight my new toys!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,15732,1,0,0,'XT002 SAY_SUMMON'),
(-1610039,"XT-002 Deconstructor's heart is exposed and leaking energy.",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'XT002 EMOTE_HEART'),
(-1610040,"XT-002 Deconstructor consumes a scrap bot to repair himself!",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'XT002 EMOTE_REPAIR');
