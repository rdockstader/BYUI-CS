-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lib/cleanup.sql
@/home/student/Data/cit225/oracle/lib/create_oracle_store.sql
@/home/student/Data/cit225/oracle/lib/seed_oracle_store.sql

SPOOL apply_oracle_lab5.txt

-- Add your lab here:
-- ----------------------------------------------------------------------

--Write INNER JOIN queries that use the USING subclause
SELECT
	member_id,
	contact_id
FROM
	member m
	JOIN contact c USING(member_id);

SELECT
	contact_id,
	address_id
FROM
	contact c 
	JOIN address a USING(contact_id);

SELECT
	address_id,
	street_address_id
FROM
	address a 
	JOIN street_address s USING(address_id);

SELECT
	contact_id,
	telephone_id
FROM
	contact a 
	JOIN telephone t USING(contact_id);


--Write INNER JOIN queries that use the ON subclause
SELECT
	contact_id,
	system_user_id
FROM
	contact c
	JOIN system_user su ON su.system_user_id = c.created_by;

SELECT
	contact_id,
	system_user_id
FROM
	contact c
	JOIN system_user su ON su.system_user_id = c.last_updated_by;


--Write INNER JOIN queries that use the ON subclause to perform a self-join
SELECT
	s1.system_user_id,
	s1.created_by,
	s2.system_user_id
FROM
	system_user s1
	JOIN system_user s2 ON s2.system_user_id = s1.created_by;

SELECT
	s1.system_user_id,
	s1.last_updated_by,
	s2.system_user_id
FROM
	system_user s1
	JOIN system_user s2 ON s2.system_user_id = s1.last_updated_by;

SELECT
	s1.system_user_name AS "System User",
	s1.system_user_id AS "System ID",
	s2.system_user_name AS "Created User",
	s1.created_by AS "Created By",
	s3.system_user_name AS "Updated user",
	s1.last_updated_by
FROM
	system_user s1
	JOIN system_user s2 ON s2.system_user_id = s1.created_by
	JOIN system_user s3 ON s3.system_user_id = s1.last_updated_by
ORDER BY
	s1.system_user_id;


--Display the RENTAL_ID column from the RENTAL table, the RENTAL_ID and ITEM_ID from the RENTAL_ITEM table, and ITEM_ID column from the ITEM table. 
SELECT
	r.rental_id,
	ri.rental_id,
	ri.item_id,
	i.item_id
FROM
	rental r
	JOIN rental_item ri ON ri.rental_id = r.rental_id
	JOIN item i ON i.item_id = ri.item_id;





SPOOL OFF
