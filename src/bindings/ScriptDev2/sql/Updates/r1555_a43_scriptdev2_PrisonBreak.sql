-- Q: Prison Break 
DELETE FROM script_texts WHERE entry IN (-1999803,-1999802);
INSERT INTO script_texts (`entry`,`content_default`,`comment`) VALUES
(-1999803,'Thank you, $R. I shall not forget your kindness!','Arcane Prisoner - Succeded'),
(-1999802,'It is.... too late for me....','Arcane Prisoner - Succeded');
