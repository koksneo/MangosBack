-- Support for quest Return to the Earth (12417/12449)

# I get nice visual effect with spell 51367. 
# But I couldn't find out solution to make Ruby Keeper not burning after spell hit.
# Probably, the issue is somewhere in creature_template, but I don't know where ;/


-- Ruby Keeper
UPDATE creature_template SET AIName='EventAI' WHERE entry=27530;

DELETE FROM creature_ai_scripts WHERE creature_id=27530;
INSERT INTO creature_ai_scripts VALUES
(2753001,27530,11,0,100,1,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Ruby Keeper - Set Phase 1 on Spawn'),
(2753002,27530,8,1,100,1,49349,-1,0,0,33,27530,6,0,11,51367,0,3,22,2,0,0,'Ruby Keeper - Quest Credit (Phase 1) and Set Phase 2'),
(2753003,27530,1,2,100,0,4000,4000,4000,4000,41,0,0,0,23,-1,0,0,0,0,0,0,'Ruby Keeper - Despawn (Phase 2)'),
(2753004,27530,26,2,100,0,27530,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Ruby Keeper Set Phase 0 on Despawn');
