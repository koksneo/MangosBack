DELETE FROM script_waypoint WHERE entry = 23784;
INSERT INTO script_waypoint VALUES
(23784,0,1379.26,-6426.18,1.08125,0,''),
(23784,1,1378.22,-6397.89,2.81855,0,''),
(23784,2,1388.79,-6385.19,4.58142,0,''),
(23784,3,1404.49,-6376.94,5.25189,0,''),
(23784,4,1428.65,-6358.85,6.43482,0,''),
(23784,5,1423.11,-6342.5,5.79411,0,''),
(23784,6,1411.06,-6333.5,5.99928,0,''),
(23784,7,1407.62,-6338.2,6.33247,7000,'burning 1st set'),
(23784,8,1424.12,-6339.58,5.61472,0,''),
(23784,9,1441.27,-6341.51,7.4658,0,''),
(23784,10,1455.76,-6345.9,8.41525,0,''),
(23784,11,1468.26,-6347.33,7.71586,7000,'burning 2nd set'),
(23784,12,1461.34,-6339.8,7.90661,0,''),
(23784,13,1470.67,-6327.01,7.19507,0,''),
(23784,14,1483.68,-6321.84,7.90882,0,''),
(23784,15,1494.07,-6312.12,7.91328,0,''),
(23784,16,1508.89,-6314.96,7.00855,0,''),
(23784,17,1509.45,-6317.81,7.23601,7000,'burning 3th set'),
(23784,18,1513.58,-6303.71,6.43527,0,''),
(23784,19,1517.54,-6291.02,6.06954,0,''),
(23784,20,1519.15,-6277.12,5.18121,0,''),
(23784,21,1522.09,-6264,4.35592,0,''),
(23784,22,1524.95,-6247.28,5.56687,0,''),
(23784,23,1528.56,-6234.32,5.98903,0,''),
(23784,24,1538.59,-6219.99,6.42572,0,''),
(23784,25,1547.34,-6210.89,7.04698,0,''),
(23784,26,1557.71,-6203.74,6.40033,0,''),
(23784,27,1573.08,-6195.38,6.89721,0,''),
(23784,28,1584.61,-6187.45,6.91971,0,''),
(23784,29,1595.9,-6179.19,7.42445,0,''),
(23784,30,1607.2,-6170.93,8.61203,0,''),
(23784,31,1618.78,-6163.06,9.377,0,''),
(23784,32,1634.28,-6154.95,8.12505,10000,'escort complete'),
(23784,33,1670.28,-6154.95,8.12505,0,'');

DELETE FROM script_texts WHERE entry BETWEEN -1999760 AND -1999753;
INSERT INTO script_texts (`entry`,`content_default`,`type`,`comment`) VALUES
(-1999760,'You couldn\'t come at better time! Let\'s get out of here.',0,'Apothecary Hanes - escort start'),
(-1999759,'Yes, let us leave... but before we leave our Alliance hosts something to remember us by!',0,'Apothecary Hanes - 1st waypoint left'),
(-1999758,'They have limited supplies in this camp. It would be a real shame if something were to happen to them.',0,'Apothecary Hanes - 2nd waypoint left'),
(-1999757,'Ah, yes... watch it burn!',0,'Apothecary Hanes - burned 1st set of supplies'),
(-1999756,'We\'re almost done.',0,'Apothecary Hanes - burned 2nd set of supplies'),
(-1999755,'Let\'s high-tail it out of here',0,'Apothecary Hanes - just before surning 3rd set of supplies'),
(-1999754,'That\'ll teach you to mess with an apothecary, you motherless Alliance dogs!','1','Apothecary Hanes - all sets burned'),
(-1999753,'We\'re in your debt, friend. Speak to Lysander at Vengeance Landing, he will arrange a suitable reward for you.','0','Apothecary Hanes - escort complete');

UPDATE creature_template SET ScriptName = 'npc_apothecary_hanes' WHERE entry = 23784;

UPDATE creature SET
spawndist = 0,
movementtype = 0
WHERE id = 23968;
