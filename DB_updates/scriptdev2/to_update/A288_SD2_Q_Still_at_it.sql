DELETE from script_texts WHERE entry IN  (-1760000,-1760001,-1760002,-1760003,-1760004,-1760005,-1760006,-1760007,-1760008,-1760009,-1760010,-1760011);
INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1760000,'Beginning the destillation in 5 seconds',0,'SAY_EVENT_STARTED'),
(-1760001,'Add bannanas',0,'SAY_ADD_BANNANAS'),
(-1760002,'Put a papaya in the still',0,'SAY_ADD_PAPAYA'),
(-1760003,'Good job! Keep your eyes open now',0,'SAY_GOOD_JOB_1'),
(-1760004,'The still needs heat! Light the brazier!',0,'SAY_BRAZIER'),
(-1760005,'Well done, be ready for anything!',0,'SAY_GOOD_JOB_2'),
(-1760006,'Pressuer\'s too high! Open the pressure valve!',0,'SAY_OPEN_VALVE'),
(-1760007,'That\'ll do. Never know what it\'ll need next ...',0,'SAY_GOOD_JOB_3'),
(-1760008,'Nicely handled! Stay on your toes',0,'SAY_GOOD_JOB_4'),
(-1760009,'We\'ve done it! Come get the cask',0,'SAY_EVENT_END'),
(-1760010,'Add orange, quickly !',0,'SAY_ADD_ORANGE'),
(-1760011,'You failed! You will have to begin new destillation process if you still want cask',0,'SAY_FAIL');