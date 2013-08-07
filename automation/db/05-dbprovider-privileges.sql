GRANT SELECT ON multisite_supermaster.password_less_accounts TO dbprovider@localhost;
GRANT EXECUTE ON FUNCTION multisite_supermaster.set_account_password TO dbprovider@localhost;
GRANT SELECT (id), UPDATE (password) ON multisite_supermaster.database_accounts TO dbprovider@localhost;
