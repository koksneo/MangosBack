-- Coren Direbrew escort
DELETE FROM script_waypoint WHERE entry = 23872;
INSERT INTO script_waypoint VALUES
(23872,0,891.80,-177.97,-43.92,0,''),
(23872,1,882.33,-190.66,-43.70,0,''),
(23872,2,867.96,-204.66,-43.70,0,''),
(23872,3,849.26,-217.37,-43.68,0,''),
(23872,4,842.78,-207.95,-43.70,0,''),
(23872,5,836.68,-198.29,-49.73,0,''),
(23872,6,833.32,-182.56,-49.75,0,''),
(23872,7,845.65,-166.74,-49.75,0,''),
(23872,8,860.33,-154.14,-49.75,0,''),
(23872,9,880.10,-152.48,-49.75,0,''),
(23872,10,894.13,-135.93,-49.75,0,''),
(23872,11,907.55,-133.14,-49.75,0,''),
(23872,12,907.90,-138.81,-49.75,0,''),
(23872,13,907.90,-138.81,-49.75,0,'');

-- Mole Machine (BRD Brewerfest event)
DELETE FROM script_texts WHERE entry BETWEEN -1799998 AND -1799987;
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1799998, 'You will pay for this insults, $c', 'Coren Direbrew - QuestComplete'),
(-1799997, 'Feel the power of the Dark Iron Dwarves', 'Coren Direbrew - aggro'),
-- Idle
-- Coren
(-1799996, 'Are we going hide in our mountain and let those swift-peddlers have their little shnding without us?!', 'Coren Direbrew - idle speach1'),
(-1799995, 'DAMN RIGHT! We will show \'em whe we don\'t cross the Dark Iron Dwarves!', 'Coren Direbrew - idle speach2'),
(-1799994, 'This is an ansult! An affront! They deny our honoured dwarvien traditions!', 'Coren Direbrew - idle speach3'),
(-1799993, 'Smash their kegs! DRAIN BREWFEST DRY!', 'Coren Direbrew - idle speach3'),

-- Agonist
(-1799992, 'Damn stright!', 'Agonist - respomnse 1.1'),
(-1799991, 'Yeah!', 'Agonist - respomnse 1.2'),
(-1799990, 'Right!', 'Agonist - respomnse 1.3'),
(-1799989, 'No!', 'Agonist - respomnse 2.1'),
(-1799988, 'No way!', 'Agonist - respomnse 2.2'),
(-1799987, 'Not on your life!', 'Agonist - respomnse 2.3'),
(-1799986, 'You said it!', 'Agonist - respomnse 4');
