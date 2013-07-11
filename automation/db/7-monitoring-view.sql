CREATE VIEW V_subsites
AS SELECT U.id AS subsite_url_id, S.id AS subsite_id, E.name AS subsite_environment, S.name AS subsite_name, M.name AS subsite_type, U.hostname AS subsite_hostname, U.uri AS subsite_uri, U.http AS subsite_http, U.https AS subsite_https, U.removed AS subsite_removed
FROM drupal_subsites S, drupal_master_sites M, drupal_subsites_urls U, environments E
WHERE S.id=U.subsiteid AND S.master=M.id  AND M.cluster_id=E.id
ORDER BY subsite_url_id;