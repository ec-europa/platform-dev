-- Privileges for the readonly user

-- They can read the contents of the "subsites_owners" view
GRANT SELECT ON subsites_owners TO 'readonly'@'remote-machine';

-- They can also read the ids of the drupal_subsites table (for update purposes).
GRANT SELECT(id) ON multisite_supermaster.drupal_subsites TO 'readonly'@'remote-machine';

-- They can update specific fields on both drupal_subsites and subsites_owners.
GRANT UPDATE(owner_contact, technical_contact, notes) ON multisite_supermaster.subsites_owners TO 'readonly'@'remote-machine';
GRANT UPDATE(owner_contact, technical_contact, notes) ON multisite_supermaster.drupal_subsites TO 'readonly'@'remote-machine';
