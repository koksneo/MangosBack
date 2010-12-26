-- Mole Machine (BRD Brewerfest event)
DELETE FROM script_texts WHERE entry IN (-1799999);
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1799999, 'Welcome onboard all passengers of Mole Undergroundlines. Please take a seat, fasten your seat belt, switch console device and enjoy journey. Thank you', 'Mole Machine');
