# Quest: The Totem of Kar'dash (9879)

# Missing English version of text
# REPLACE INTO `script_texts`
# (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
# VALUES
# ('-1999930', 'Es ist am besten, wenn wir uns nun aufteilen, f?r den Fall, dass man uns mehr Leute nach schickt. Hoffentlich schafft es einer von uns zur?ck zu Arechron. Macht''s gut, Fremder.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '0', '0', '0', '0', NULL);

REPLACE INTO `script_waypoint`
(`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`)
VALUES
('18209', '1', '-1518.593872', '8469.956055', '-4.101756', '0', NULL),
('18209', '2', '-1511.784546', '8480.531250', '-4,033919', '0', 'first combat'),
('18209', '3', '-1513.447754', '8509.764698', '-0.109888', '0', NULL),
('18209', '4', '-1498.857788', '8508.805664', '0.844676', '0', NULL),
('18209', '5', '-1454.215088', '8495.808594', '4.912439', '0', 'second combat'),
('18209', '6', '-1437.483521', '8504.165039', '6.879123', '0', NULL),
('18209', '7', '-1387.885680', '8539.817383', '11.075749', '30000', 'quest complete');
