CREATE VIEW V_subsites
AS SELECT U.id AS subsite_url_id, S.id AS subsite_id, E.name AS subsite_environment, S.name AS subsite_name, M.name AS subsite_type, U.hostname AS subsite_hostname, U.uri AS subsite_uri, U.http AS subsite_http, U.https AS subsite_https, S.owner_contact AS subsite_contact_owner
FROM drupal_subsites S, drupal_master_sites M, drupal_subsites_urls U, environments E, workflow_states W
WHERE S.id=U.subsiteid AND S.master=M.id AND M.cluster_id=E.id AND W.subsite_id=U.subsiteid AND W.state='done'
ORDER BY subsite_url_id;