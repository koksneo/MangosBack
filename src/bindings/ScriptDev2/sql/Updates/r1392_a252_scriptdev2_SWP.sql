/* SD2 */
DELETE FROM `script_texts` WHERE entry IN (-1942002,-1942001,-1942000,-1941002,-1941001,-1941000,-1940010,-1940004,-1940003,-1940002,-1940001);
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `comment`) VALUES 
(-1942002, 'You can not keep the orientation forever, little one', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Sacro castet Verwirrender Schlag'),
(-1942001, 'The darkness shall bring you suffer !!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Sacro castet Schattennova'),
(-1942000, 'Are you all that weak?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Sacro tötet einen Spieler'),
(-1941002, 'Shadowmetal, rip them to pieces!!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Aly castet Schattenklingen'),
(-1941001, 'Burn in the fire of the Blaze !!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Aly castet Lohe'),
(-1941000, 'Another useless creature in my collection', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Aly killt einen Spieler'),
(-1940010, 'No...Sister...YOU have done that!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'Übergebliebener Twin macht sich für die Enrage-Attacke bereit'),
(-1940004, 'NO !! SISTER!! WHAT HAVE YOU DONE !! YOU WILL PAY WITH HELL AGONIES FOR THIS !!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Überlebender Twin geht enrage'),
(-1940003, 'Forgive me Sister - I did not withstand ...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Ein Twin stirbt'),
(-1940002, 'No, we have failed - Foregive us ...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: beide Twins sind tot'),
(-1940001, 'What do you want from us - YOU DISTURB!!!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 1, 0, 'SP-Twins: Kampf beginnt');
