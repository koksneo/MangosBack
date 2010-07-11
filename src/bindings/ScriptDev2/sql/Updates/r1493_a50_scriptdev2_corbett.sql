DELETE FROM script_texts WHERE entry BETWEEN -1999889 AND -1999869;
INSERT INTO script_texts (`entry`,`content_default`,`comment`)VALUES
(-1999889,'Corbett, dear. Harlan needs a load of knitted shirts and pants as soon as we can manage.','Rema Schneider - (0)'),
(-1999888,'Corbett, you there? Harlan needs another load of knitted goods. Can you take it to him?','Rema Schneider - (1)'),

(-1999887,'My pleasure, sugar drop. I\'ll be back soon…','Corbett Schneider - WP_0 (0)'),
(-1999886,'Business must be good down at the bazaar. I\'ll get him resupplied right away!','Corbett Schneider - WP_0 (1)'),

(-1999885,'Hm...after dropping this off, I think I\'ll head to that cheese shop for a snack.','Corbett Schneider - WP_13 (0)'),
(-1999884,'I should have a few extra coins from this sale. Maybe I\'ll buy myself some lunch...','Corbett Schneider - WP_13 (1)'),

(-1999883,'Hey Harlan. Here\'s a load of knitted cloth for you.','Corbett Schneider - WP_16 (0)'),
(-1999882,'Oomph! Here\'s a load of supplies. It must be selling fast!','Corbett Schneider - WP_16 (1)'),

(-1999881,'Ah yes, and promptly delivered. As always, it\'s a pleasure doing business with you, Corbett.','Harlan Bagley - (0)'),
(-1999880,'Ahh, much appreciated, Corbett. We\'ll get these on the racks immediately.','Harlan Bagley - (1)'),
 
(-1999879,'Glad to see you\'re doing so well, Harlan. And I hope to see you again soon…','Corbett Schneider - WP_16 (2)'),
(-1999878,'Well, I am off than. Take care, Harlan!','Corbett Schneider - WP_16 (3)'),

(-1999877,'Now for that snack…','Corbett Schneider - WP_17'),

(-1999876,'Hullo, Trias clan! A ball of your smoked mozzarella, if you please!','Corbett Schneider - WP_22 (0)'),
(-1999875,'Good day. Elling! Hullo Elaine! Let me have a wheel of blue cheese, eh?','Corbett Schneider - WP_22 (1)'),

(-1999874,'Good day, Corbett. Here\'s your cheese, fresh made this morning! And how are things at your shop?','Elaine Trias - (0)'),
(-1999873,'Hi Corbett! Here, you go! I trust business is faring well at your clothier shop...?','Elaine Trias - (1)'),

(-1999872,'Yes ma\'am, business is brisk!','Corbett Schneider - WP_22 (2)'),

(-1999871,'Thanks for the cheese!','Corbett Schneider - WP_22 (3)'),
(-1999870,'Time to get back to the shop…','Corbett Schneider - '),
(-1999869,'I\'m back!','Corbett Schneider - ');

DELETE FROM script_waypoint WHERE entry = 1433;
INSERT INTO script_waypoint (`entry`,`pointid`,`location_x`,`location_y`,`location_z`,`point_comment`) VALUES
(1433, 01, -8776.53, 714.943, 99.5343,'Corbett Schneider'),  
(1433, 02, -8764.02, 718.846, 99.5343,'Corbett Schneider'),  
(1433, 03, -8756.49, 726.230, 98.1827,'Corbett Schneider'),  
(1433, 04, -8737.77, 700.301, 98.7146,'Corbett Schneider'),  
(1433, 05, -8776.04, 669.290, 103.093,'Corbett Schneider'),  
(1433, 06, -8760.53, 646.648, 103.862,'Corbett Schneider'),  
(1433, 07, -8759.42, 624.292, 101.056,'Corbett Schneider'),  
(1433, 08, -8770.38, 609.041, 97.2165,'Corbett Schneider'),  
(1433, 09, -8797.70, 588.021, 97.3042,'Corbett Schneider'),  
(1433, 10, -8818.46, 616.102, 94.9164,'Corbett Schneider'),  
(1433, 11, -8818.67, 626.670, 93.9437,'Corbett Schneider'),  
(1433, 12, -8791.16, 634.711, 94.5033,'Corbett Schneider'),  
(1433, 13, -8779.68, 637.628, 97.2233,'Corbett Schneider'),  
(1433, 14, -8781.26, 638.974, 97.2233,'Corbett Schneider'), -- Harlan shop 
(1433, 15, -8781.68, 637.128, 97.2233,'Corbett Schneider'),  
(1433, 16, -8825.46, 624.483, 93.8268,'Corbett Schneider'),  
(1433, 17, -8849.64, 602.755, 92.1315,'Corbett Schneider'),  
(1433, 18, -8864.55, 585.043, 92.8400,'Corbett Schneider'),
(1433, 19, -8856.92, 577.403, 95.3750,'Corbett Schneider'),
(1433, 20, -8849.48, 570.495, 94.6800,'Corbett Schneider'), -- cheese shop
(1433, 21, -8856.92, 577.403, 95.3750,'Corbett Schneider'),
(1433, 22, -8864.55, 585.043, 92.8400,'Corbett Schneider'),
(1433, 23, -8837.26, 611.555, 93.3786,'Corbett Schneider'),
(1433, 24, -8843.4,  642.051, 95.8250,'Corbett Schneider'),  
(1433, 25, -8850.36, 660.501, 97.1423,'Corbett Schneider'),  
(1433, 26, -8825.86, 677.315, 97.6257,'Corbett Schneider'),  
(1433, 27, -8843.57, 720.188, 97.4082,'Corbett Schneider'),  
(1433, 28, -8801.84, 745.453, 97.5976,'Corbett Schneider'),  
(1433, 29, -8773.15, 740.631, 99.4496,'Corbett Schneider'),  
(1433, 30, -8757.46, 725.815, 98.2184,'Corbett Schneider'),  
(1433, 31, -8769.03, 714.770, 99.5337,'Corbett Schneider'),  
(1433, 32, -8778.93, 715.753, 99.5337,'Corbett Schneider'),  
(1433, 33, -8775.91, 719.409, 101.569,'Corbett Schneider'),  
(1433, 34, -8770.39, 724.865, 105.913,'Corbett Schneider'),  
(1433, 35, -8765.45, 721.190, 105.913,'Corbett Schneider'); 
