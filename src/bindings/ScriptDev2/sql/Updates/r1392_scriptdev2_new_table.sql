CREATE TABLE IF NOT EXISTS `custom_fix` (
  `custom_id` int(16) NOT NULL auto_increment,
  `value` int(10) NOT NULL,
  `text` text NOT NULL,
  PRIMARY KEY  (`custom_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;


INSERT INTO `custom_fix` (`custom_id`, `value`, `text`) VALUES
(1, 100, 'test');
