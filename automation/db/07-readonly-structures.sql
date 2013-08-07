-- This view can be used to restrict access to administrative data (typically:
-- existing subsites and their contacts)for some people or applications.
CREATE OR REPLACE VIEW subsites_owners AS
SELECT
  s.id AS id,
  m.name AS master,
  s.name AS name,
  s.owner_contact AS owner_contact,
  s.technical_contact AS technical_contact,
  s.notes AS notes
FROM
  drupal_subsites s
  join drupal_master_sites m ON s.master = m.id
ORDER BY m.id ASC, s.name ASC;
