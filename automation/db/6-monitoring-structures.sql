CREATE TABLE `drupal_subsites_urls` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `subsiteid` int(11) NOT NULL,
  `hostname` varchar(512),
  `uri` varchar(512),
  `http` boolean DEFAULT FALSE,
  `https` boolean DEFAULT TRUE,
  PRIMARY KEY (`id`),
  KEY (`subsiteid`),
  CONSTRAINT `drupal_urls_ibfk_1` FOREIGN KEY (`subsiteid`) REFERENCES `drupal_subsites` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Known Drupal subsites urls';

CREATE VIEW V_subsites
AS SELECT U.id AS subsite_url_id, S.id AS subsite_id, E.name AS subsite_environment, S.name AS subsite_name, M.name AS subsite_type, U.hostname AS subsite_hostname, U.uri AS subsite_uri, U.http AS subsite_http, U.https AS subsite_https, S.owner_contact AS subsite_contact_owner
FROM drupal_subsites S, drupal_master_sites M, drupal_subsites_urls U, environments E, workflow_states W
WHERE S.id=U.subsiteid AND S.master=M.id AND M.cluster_id=E.id AND W.subsite_id=U.subsiteid AND W.state='done'
ORDER BY subsite_url_id;
