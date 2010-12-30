-- Instance Violet Hold

-- Erekem texts

REPLACE INTO script_texts (entry,content_default,sound,type,comment) VALUES
(-1608010,'Not--caww--get in way of--rrak-rrak--flee! ',14219,1,'A_VH_Erekem_Aggro'),
# (-1608011,'',14222,1,'A_VH_Erekem_Slay01'),
# (-1608012,'',14223,1,'A_VH_Erekem_Slay02'),
# (-1608013,'',14224,1,'A_VH_Erekem_Slay03'),
(-1608014,'No--kaw, kaw--flee... ',14225,1,'A_VH_Erekem_Death'),
(-1608015,'Free to--mm--fly now. Ra-aak... Not find us--ekh-ekh! Escape!',14218,1,'A_VH_Erekem_Spawn'), 
(-1608016,'My---raaak--favorite! Awk awk awk! Raa-kaa! ',14220,1,'A_VH_Erekem_AddKilled'),
(-1608017,'Nasty little...A-ak, kaw! Kill! Yes, kill you! ',14221,1,'A_VH_Erekem_BothAddsDead');

-- Ichoron texts

REPLACE INTO script_texts (entry,content_default,sound,type,comment) VALUES
(-1608018,'Stand aside, mortals!',14230,1,'A_VH_Ichoron_Aggro'),
(-1608019,'I am a force of nature!',14234,1,'A_VH_Ichoron_Slay01'),
(-1608020,'I shall pass!',14235,1,'A_VH_Ichoron_Slay02'),
(-1608021,'You can not stop the tide!',14236,1,'A_VH_Ichoron_Slay03'),
(-1608022,'I... recede',14237,1,'A_VH_Ichoron_Death'),
(-1608023,'I... am fury... unrestrained!',14229,1,'A_VH_Ichoron_Spawn'),
(-1608024,'I shall consume, decimate, devastate, and destroy! Yield now to the wrath of the pounding sea!',14231,1,'A_VH_Ichoron_Enrage'),
(-1608025,'I will not be contained! Ngyah!!',14233,1,'A_VH_Ichoron_Shatter'),
(-1608026,'Water can hold any form, take any shape... overcome any obstacle.',14232,1,'A_VH_Ichoron_Bubble');

-- Xevozz texts

REPLACE INTO script_texts (entry,content_default,sound,type,comment) VALUES
(-1608027,'It seems my freedom must be bought with blood... ',14499,1,'A_VH_Xevozz_Aggro'),
(-1608028,'Nothing personal. ',14504,1,'A_VH_Xevozz_Slay01'),
(-1608029,'Business concluded.',14505,1,'A_VH_Xevozz_Slay02'),
(-1608030,'Profit!',14506,1,'A_VH_Xevozz_Slay03'),
(-1608031,'This is an... unrecoverable... loss.',14507,1,'A_VH_Xevozz_Death'),
(-1608032,'Back in business! Now to execute an exit strategy.',14498,1,'A_VH_Xevozz_Spawn'),
(-1608033,'It would seem that a renegotiation is in order.',14503,1,'A_VH_Xevozz_Charged'),
(-1608034,'The air teems with latent energy... quite the harvest!',14501,1,'A_VH_Xevozz_RepeatSummon01'),
(-1608035,'Plentiful, exploitable resources... primed for acquisition! ',14502,1,'A_VH_Xevozz_RepeatSummon02'),
(-1608036,'Intriguing... a high quantity of arcane energy is near. Time for some prospecting...',14500,1,'A_VH_Xevozz_SummonEnergy');

-- Zuramat texts

REPLACE INTO script_texts (entry,content_default,sound,type,comment) VALUES
(-1608037,'Eradicate.',13996,1,'A_VH_Zuramat_Aggro'),
(-1608038,'More... energy.',13999,1,'A_VH_Zuramat_Slay01'),
(-1608039,'Relinquish.',14000,1,'A_VH_Zuramat_Slay02'),
(-1608040,'Fall... to shadow.',14001,1,'A_VH_Zuramat_Slay03'),
(-1608041,'Disperse.',14002,1,'A_VH_Zuramat_Death'),
(-1608042,'I am... renewed.',13995,1,'A_VH_Zuramat_Spawn'),
(-1608043,'Know... my... pain.',13997,1,'A_VH_Zuramat_Shield'),
(-1608044,'Gaze... into the void.',13998,1,'A_VH_Zuramat_Whisper');

-- Cyanigosa

REPLACE INTO script_texts (entry,content_default,sound,type,comment) VALUES
(-1608045,'A valiant defense, but this city must be razed. I will fulfill Malygos\'s wishes myself!',13946,1,'A_VH_Cyanigosa_Spawn'),
(-1608046,'We finish this now, champions of Kirin Tor!',13947,1,'A_VH_Cyanigosa_Aggro'),
(-1608047,'Shiver and die!',13948,1,'A_VH_Cyanigosa_BreathAttack'),
(-1608048,'The world has forgotten what true magic is! Let this be a reminder!',13949,1,'A_VH_Cyanigosa_SpecialAttack01'),
(-1608049,'Who among you can withstand my power?',13950,1,'A_VH_Cyanigosa_SpecialAttack02'),
(-1608050,'Am I interrupting?',13951,1,'A_VH_Cyanigosa_Disruption'),
(-1608051,'I will end the Kirin Tor!',13952,1,'A_VH_Cyanigosa_Slay01'),
(-1608052,'Dalaran will fall!',13953,1,'A_VH_Cyanigosa_Slay02'),
(-1608053,'So ends your defiance of the Spell-Weaver!',13954,1,'A_VH_Cyanigosa_Slay03'),
(-1608054,'Perhaps... we have... underestimated... you.',13955,1,'A_VH_Cyanigosa_Death01');


-- Lieutenant Sinclari (30658)

REPLACE INTO script_texts (entry,content_default,type,comment) VALUES
(-1608009,'You did it! You held the Blue Dragonblight back and defeated their commander. Amazing work!',1,'sinclair SAY_END');
DELETE FROM gossip_texts WHERE entry IN (-3608001,-3608000);
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3608001,'Get your people to safety, we\'ll keep the Blue Dragonflight\'s forces at bay.','sinclari GOSSIP_ITEM_START'),
(-3608000,'Activate the crystals when we get in trouble, right?','sinclari GOSSIP_ITEM_INTRO');



-- Boss emotes

REPLACE INTO script_texts (entry,content_default,type,comment) VALUES
(-1608008,'Ichoron\'s Protective Bubble shatters!',3,'EMOTE_ICHORON_PROTECTIVE_BUBBLE');


-- Azure texts

REPLACE INTO script_texts (entry,content_default,type,comment) VALUES
(-1608055,'The Kirin Tor must be stopped!',0,'AZURE_SAY_AGGRO_1'),
(-1608056,'Dalaran must fall!',0,'AZURE_SAY_AGGRO_2'),
(-1608057,'The Nexus War will not be stopped!',0,'AZURE_SAY_AGGRO_3'),
(-1608058,'For the Spellweaver!',0,'AZURE_SAY_AGGRO_4'),

(-1608059,'The destruction of Dalaran is inevitable!',1,'Portal Keeper/Guardian AGGRO_1'),
(-1608060,'The portal has stabilized! Attack!',1,'Portal Keeper/Guardian AGGRO_2'),
(-1608064,'The way into Dalaran has been opened!',1,'Portal Guardian AGGRO_3'),
(-1608061,'More portals will take this one\'s place!',1,'Portal Keeper/Guardian DEATH_1'),
(-1608062,'Why do you defend the Kirin Tor...',1,'Portal Keeper/Guardian DEATH_2'),
(-1608063,'My death will not stop the invasion!',1,'Portal Keeper/Guardian DEATH_2'),
(-1608065,'Destroy all who stand against us!',0,'Azure Captain AGGRO_1');

