CREATE TABLE IF NOT EXISTS `mail_template` (
  `id` mediumint(8) NOT NULL,
  `title` text character set utf8 NOT NULL,
  `text` text character set utf8 NOT NULL,
  `item1` mediumint(8) NOT NULL default '0',
  `item1_count` mediumint(8) NOT NULL default '0',
  `item2` mediumint(8) NOT NULL default '0',
  `item2_count` mediumint(8) NOT NULL default '0',
  `item3` mediumint(8) NOT NULL default '0',
  `item3_count` mediumint(8) NOT NULL default '0',
  `item4` mediumint(8) NOT NULL default '0',
  `item4_count` mediumint(8) NOT NULL default '0',
  `item5` mediumint(8) NOT NULL default '0',
  `item5_count` mediumint(8) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;