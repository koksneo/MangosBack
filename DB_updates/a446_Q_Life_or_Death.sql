-- support for q Life or Death

DELETE FROM creature_ai_scripts WHERE id=2748201;
INSERT INTO creature_ai_scripts VALUES
(2748201,27482,8,0,100,1,48845,-1,0,0,33,27466,6,0,1,-274820,-274821,0,11,43014,0,1,'Wounded infantry -kill credit after spellhit');

UPDATE creature_template SET
ScriptName='',
AIName='EventAI'
WHERE entry=27482;

-- item required target for renewing bandage(37576)
DELETE FROM item_required_target WHERE entry=37576;
INSERT INTO item_required_target VALUES
(37576,1,27482);

DELETE FROM `creature_ai_texts` WHERE `entry` IN (-274820,-274821);
INSERT INTO `creature_ai_texts` (`entry`, `content_default`,`comment`) VALUES
(-274820, "Thank you, $R !",'wounded_westfall_infantry'),
(-274821, "Without your help, I surely would have died .....",'wounded_westfall_infantry');
