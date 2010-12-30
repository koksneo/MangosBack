-- Leave only one spawn coppy of Injured Oracle

DELETE FROM script_texts WHERE entry IN (-1999795,-1999794,-1999793,-1999792);
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1999795,'We wait until you ready','Injured oracle - quest accepted'),
(-1999794,'Home time','Injured oracle - escort start'),
(-1999793,'Thanks!','Injured oracle - escort completed'),
-- couldn't read last two words of this quote from YT video :D
(-1999792,'Oh no! Some puppy man lolowed!','Injured oracle - after escort completed');

DELETE FROM script_waypoint WHERE entry = 28217;
INSERT INTO script_waypoint VALUES
(28217,0,5398.97,4509.59,-131.02,0,'Injured Oracle'),
(28217,1,5396.6,4520.8,-132.538,0,'Injured Oracle'),
(28217,2,5403.09,4529.73,-138.526,0,'Injured Oracle'),
(28217,3,5407.94,4526.85,-143.511,0,'Injured Oracle'),
(28217,4,5417.01,4521.1,-144.062,0,'Injured Oracle'),
(28217,5,5426.05,4524.29,-148.2,0,'Injured Oracle'),
(28217,6,5440.56,4538.17,-149.565,0,'Injured Oracle'),
(28217,7,5448.16,4548.17,-149.628,0,'Injured Oracle'),
(28217,8,5454.08,4557.31,-148.648,0,'Injured Oracle'),
(28217,9,5457.64,4571.63,-147.796,0,'Injured Oracle'),
(28217,10,5458.63,4581.94,-147.28,0,'Injured Oracle'),
(28217,11,5463.83,4591.32,-147.28,0,'Injured Oracle'),
(28217,12,5471.43,4603.84,-145.204,0,'Injured Oracle'),
(28217,13,5479.23,4613.66,-141.319,0,'Injured Oracle'),
(28217,14,5487.9,4622.07,-137.417,0,'Injured Oracle'),
(28217,15,5495.01,4630.13,-135.591,0,'Injured Oracle'),
(28217,16,5506.42,4641.75,-134.855,0,'Injured Oracle'),
(28217,17,5525.26,4648.73,-135.732,0,'Injured Oracle'),
(28217,18,5538.77,4649.64,-136.051,0,'Injured Oracle'),
(28217,19,5554.95,4651.68,-134.196,0,'Injured Oracle'),
(28217,20,5571.63,4653.39,-135.157,0,'Injured Oracle'),
(28217,21,5588.42,4647.65,-136.494,0,'Injured Oracle'),
(28217,22,5599.17,4639.45,-136.494,0,'Injured Oracle'),
(28217,23,5609.14,4629.58,-136.945,0,'Injured Oracle'),
(28217,24,5620.89,4618.27,-137.895,0,'Injured Oracle'),
(28217,25,5631.98,4604.56,-137.037,30000,'Injured Oracle');
