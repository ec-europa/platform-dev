-- The multisite_supermaster database aims at storing knowns databases,
-- accounts, servers, clusters, Drupal sites (master sites and subsites) along
-- with their state.

CREATE DATABASE /*!32312 IF NOT EXISTS*/ multisite_supermaster /*!40100 DEFAULT CHARACTER SET latin1 */;
USE multisite_supermaster;

-- We may have very similar objects within different environments.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS environments (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(128) NOT NULL,
  comment text,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Known environments';
/*!40101 SET character_set_client = @saved_cs_client */;

-- We have web servers.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS web_servers (
  id int(11) NOT NULL AUTO_INCREMENT,
  hostname varchar(256) DEFAULT NULL,
  port smallint(5) unsigned DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

-- We also have database instances...
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS database_instances (
  id int(11) NOT NULL AUTO_INCREMENT,
  hostname varchar(256) NOT NULL,
  port smallint(5) unsigned DEFAULT '3306',
  type varchar(32) DEFAULT 'mysql',
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

-- ... and accounts, each account being related to a specific database instance.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS database_accounts (
  id int(11) NOT NULL AUTO_INCREMENT,
  user varchar(256) NOT NULL,
  password varchar(256) NOT NULL COMMENT 'MySQL account password -- select privilege should be granted carefully',
  database_instance int(11) NOT NULL COMMENT 'MySQL instance the account is related to',
  PRIMARY KEY (id),
  UNIQUE KEY user_at_instance_is_unique (user,database_instance),
  KEY database_instance (database_instance),
  CONSTRAINT database_accounts_ibfk_1 FOREIGN KEY (database_instance) REFERENCES database_instances (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Known MySQL accounts';
/*!40101 SET character_set_client = @saved_cs_client */;

-- We have clusters. Each cluster references one default database instance...
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS clusters (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(256) NOT NULL COMMENT 'cluster name',
  mysql_instance int(11) NOT NULL,
  sync_command varchar(512) DEFAULT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY name (name),
  KEY mysql_instance (mysql_instance),
  CONSTRAINT clusters_ibfk_1 FOREIGN KEY (mysql_instance) REFERENCES database_instances (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

-- ... and 0 to n web servers.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS clusters_servers (
  cluster_id int(11) NOT NULL,
  web_server_id int(11) NOT NULL,
  PRIMARY KEY (cluster_id,web_server_id),
  KEY web_server_id (web_server_id),
  CONSTRAINT clusters_servers_ibfk_1 FOREIGN KEY (cluster_id) REFERENCES clusters (id) ON DELETE CASCADE,
  CONSTRAINT clusters_servers_ibfk_2 FOREIGN KEY (web_server_id) REFERENCES web_servers (id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

-- On top of these services, we have Drupal master sites. Each master site lives
-- on a specific cluster, and owns a database he reaches using a database
-- account... which may be on a database instance different from the cluster's
-- default.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS drupal_master_sites (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(128) NOT NULL,
  cluster_id int(11) NOT NULL,
  sites_local_path varchar(1024) NOT NULL COMMENT 'path to the sites/ directory as mounted on the management server',
  files_local_path varchar(1024) DEFAULT NULL,
  rewritemap_local_path varchar(1024) NOT NULL COMMENT 'path to the RewriteMap files as mounted on the management server',
  default_subsite_url_pattern varchar(512) NOT NULL COMMENT 'default URL pattern leading Drupal to recognize a subsite',
  default_subsite_install_policy varchar(128) NOT NULL,
  database_name varchar(128) NOT NULL COMMENT 'Name of the master database',
  database_account int(11) NOT NULL COMMENT 'account to access the master database',
  PRIMARY KEY (id),
  UNIQUE KEY name (name),
  KEY database_account (database_account),
  KEY cluster_id (cluster_id),
  CONSTRAINT drupal_master_sites_ibfk_1 FOREIGN KEY (database_account) REFERENCES database_accounts (id),
  CONSTRAINT drupal_master_sites_ibfk_2 FOREIGN KEY (cluster_id) REFERENCES clusters (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

-- Drupal subsites have a master site as parent. They are also free to rely on
-- a database instance different from their parent's cluster's default.
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS drupal_subsites (
  id int(11) NOT NULL AUTO_INCREMENT,
  name varchar(128) NOT NULL,
  environment int(11) NOT NULL,
  url_pattern varchar(512) NOT NULL,
  database_name varchar(128) NOT NULL,
  database_account int(11) NOT NULL,
  master int(11) NOT NULL COMMENT 'Parent Drupal master site',
  install_policy varchar(128) DEFAULT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY name (name, environment),
  KEY master (master),
  KEY database_account (database_account),
  KEY environment (environment),
  CONSTRAINT drupal_subsites_ibfk_1 FOREIGN KEY (database_account) REFERENCES database_accounts (id),
  CONSTRAINT drupal_subsites_ibfk_2 FOREIGN KEY (master) REFERENCES drupal_master_sites (id),
  CONSTRAINT drupal_subsites_ibfk_3 FOREIGN KEY (environment) REFERENCES environments (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Known Drupal subsites';
/*!40101 SET character_set_client = @saved_cs_client */;

-- This table stores subsites states (are they freshly declared, fully installed
-- or in a failed state?).
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE IF NOT EXISTS workflow_states (
  subsite_id int(11) NOT NULL,
  state varchar(256) NOT NULL DEFAULT 'declared',
  last_update timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  data longtext,
  PRIMARY KEY (subsite_id),
  CONSTRAINT workflow_states_ibfk_1 FOREIGN KEY (subsite_id) REFERENCES drupal_subsites (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='State of known Drupal subsites';
/*!40101 SET character_set_client = @saved_cs_client */;
