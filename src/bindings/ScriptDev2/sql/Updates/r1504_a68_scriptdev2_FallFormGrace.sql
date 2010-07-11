DELETE FROM script_texts WHERE entry BETWEEN -1999850 AND -1999844;
INSERT INTO script_texts (`entry`,`content_default`,`emote`,`comment`) VALUES
(-1999850,'Gah! What are you doing?',1,'Onslaught Raven Priest - Bell Rang'),
(-1999849,'I know a place nearby where we can speak in private, my child. Follow me.',1,'High Abbot Landgren - begining'),
(-1999848,'Did you think that I could not see through your flimsy disquise, $N?',1,'High Abbot Landgren - at the cliff 01'),
(-1999847,'There is much that you do not understand, $c. The Master sees all.',1,'High Abbot Landgren - at the cliff 02'),
(-1999846,'He told me that you would come for me. I won\'t die by your hand, though.  have seen what have you done to my compatriots',25,'High Abbot Landgren - at the cliff 03'),
(-1999845,'No. I will leave this world in a manner of my own choosing. And I will return, the grand admiral\'s  will permitting.',1,'High Abbot Landgren - at the cliff 04'),
(-1999844,'AAAEEEllliiiiiiiiiii.................',0,'High Abbot Landgren - jumping from the cliff');

DELETE FROM script_waypoint WHERE entry = 27439;
INSERT INTO script_waypoint VALUES
(27439,0,2827.27,-447.32,119.62,0,''),
(27439,1,2828.19,-424.11,119.89,0,''),
(27439,2,2827.23,-413.33,118.19,0,''),
(27439,3,2811.16,-410.01,118.19,0,''),
(27439,4,2788.90,-435.18,118.19,0,''),
(27439,5,2781.21,-452.48,117.89,0,''),
(27439,6,2776.58,-467.34,116.10,0,''),
(27439,7,2768.54,-483.29,115.59,0,''),
(27439,8,2755.83,-505.29,106.94,0,''),
(27439,9,2743.31,-514.23,103.64,0,''),
(27439,10,2738.87,-524.66,103.35,0,''),
(27439,11,2738.87,-524.66,103.35,0,'');
