USE multisite_supermaster;
-- view for the dbprovider application to fetch password-less accounts
CREATE OR REPLACE ALGORITHM=UNDEFINED DEFINER=supermaster@localhost SQL SECURITY DEFINER VIEW password_less_accounts AS
SELECT a.id AS id, i.hostname AS hostname, i.port AS port, a.user AS user 
FROM database_instances i JOIN database_accounts a ON (a.database_instance = i.id)
WHERE (length(a.password) = 0);

-- function for the dbprovider application to set accounts passwords
DROP FUNCTION IF EXISTS set_account_password;
DELIMITER //
CREATE FUNCTION set_account_password (account_id int(11), account_password varchar(256))  RETURNS smallint
BEGIN
    IF (SELECT count(id) from password_less_accounts WHERE id = account_id) <> 1 THEN
        RETURN 0;
    END IF;
    UPDATE database_accounts SET password = account_password WHERE id = account_id;
    RETURN 1;
END//
DELIMITER ;
