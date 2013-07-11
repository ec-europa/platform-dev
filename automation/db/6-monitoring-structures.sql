CREATE TABLE `drupal_subsites_urls` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `subsiteid` int(11) NOT NULL,
  `hostname` varchar(512),
  `uri` varchar(512),
  `http` boolean DEFAULT FALSE,
  `https` boolean DEFAULT FALSE,
  `removed` boolean DEFAULT FALSE,
  PRIMARY KEY (`id`),
  KEY (`subsiteid`),
  CONSTRAINT `drupal_urls_ibfk_1` FOREIGN KEY (`subsiteid`) REFERENCES `drupal_subsites` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Known Drupal subsites urls';