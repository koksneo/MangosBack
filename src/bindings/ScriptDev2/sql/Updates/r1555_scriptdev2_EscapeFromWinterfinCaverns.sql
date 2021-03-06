DELETE FROM script_waypoint WHERE entry = 25208;
INSERT INTO script_waypoint VALUES
(25208,0,4013.51,6390.33,29.970,4000,'Lurgglbr - Escape from Winterfin Caverns - after escaped from cage'),
(25208,1,4023.06,6379.43,29.210,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,2,4033.61,6370.94,28.430,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,3,4052.03,6367.42,27.370,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,4,4061.13,6353.36,25.450,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,5,4064.28,6330.76,25.310,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,6,4057.94,6307.85,24.900,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,7,4057.40,6290.12,24.430,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,8,4065.63,6277.64,23.900,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,9,4080.71,6280.77,26.920,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,10,4098.90,6279.00,25.950,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,11,4118.00,6277.81,25.720,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,12,4129.47,6281.65,28.860,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,13,4143.86,6282.57,29.180,4000,'Lurgglbr - Escape from Winterfin Caverns - outside cave'),
(25208,14,4159.54,6280.08,30.520,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,15,4171.95,6291.50,22.250,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,16,4184.86,6293.45,16.570,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,17,4194.14,6301.28,13.310,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,18,4210.34,6285.81,09.500,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,19,4220.05,6272.75,07.770,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,20,4242.45,6272.24,01.750,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,21,4257.79,6252.91,-0.050,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,22,4256.81,6230.74,-0.090,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,23,4241.09,6217.87,-0.140,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,24,4254.66,6205.16,-0.170,0,'Lurgglbr - Escape from Winterfin Caverns'),
(25208,25,4261.82,6186.47,-0.140,4000,'Lurgglbr - Escape from Winterfin Caverns - final point');

DELETE FROM script_texts WHERE entry BETWEEN -1999801 AND -1999798;
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1999801,'Together we will fight our way out of here. Are you ready?','Lurgglbr - accept escort'),
(-1999800,'Than we leave','Lurgglbr - start escor'),
(-1999799,'This is far enough. I can make it on my own from here.','Lurgglbr - outside cave'),
(-1999798,'Thank You for helping me $c. Please tell the king I am back.','Lurgglbr - escort finished');
