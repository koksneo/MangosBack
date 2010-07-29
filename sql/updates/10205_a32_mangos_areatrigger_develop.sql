CREATE TABLE IF NOT EXISTS `areatrigger_develop` (
  `id` mediumint(8) NOT NULL,
  `type` mediumint(8) NOT NULL,
  `action` mediumint(8) NOT NULL,
  PRIMARY KEY  (`id`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
