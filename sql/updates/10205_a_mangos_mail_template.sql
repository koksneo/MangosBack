CREATE TABLE IF NOT EXISTS `mail_template` (
  `id` mediumint(8) NOT NULL,
  `title` text character set utf8 NOT NULL,
  `text` text character set utf8 NOT NULL,
  `item1` mediumint(8) NOT NULL,
  `item1_count` mediumint(8) NOT NULL,
  `item2` mediumint(8) NOT NULL,
  `item2_count` mediumint(8) NOT NULL,
  `item3` mediumint(8) NOT NULL,
  `item3_count` mediumint(8) NOT NULL,
  `item4` mediumint(8) NOT NULL,
  `item4_count` mediumint(8) NOT NULL,
  `item5` mediumint(8) NOT NULL,
  `item5_count` mediumint(8) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;