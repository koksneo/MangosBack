-- Quest :: Mildred the Cruel - 12905
-- wrong factions for alliance nad horde
UPDATE `creature_template` SET `faction_A` = '35',
`faction_H` = '35' WHERE `entry` = 29885 LIMIT 1 ;
