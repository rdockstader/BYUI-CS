-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lab2/apply_oracle_lab2.sql
@/home/student/Data/cit225/oracle/lib/seed_oracle_store.sql

SPOOL apply_oracle_lab4.txt

-- Insert two rows into the SYSTEM_USER_LAB table. 
INSERT INTO system_user_lab
VALUES
(
	system_user_lab_s1.NEXTVAL
	,'REACHERJ'
	,(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'SYSTEM_USER' AND common_lookup_type = 'DBA')
	,(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME')
	,'Jack'
	,NULL
	,'Reacher'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

INSERT INTO system_user_lab
VALUES
(
	system_user_lab_s1.NEXTVAL
	,'OWENSR'
	,(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'SYSTEM_USER' AND common_lookup_type = 'DBA')
	,(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME')
	,'Ray'
	,NULL
	,'Owens'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

-- Insert two rows into the COMMON_LOOKUP_LAB table. 
INSERT INTO common_lookup_lab
VALUES
(
	common_lookup_lab_s1.NEXTVAL
	,'MEMBER_LAB'
	,'AMERICAN_EXPRESS_CARD'
	,'American Express Card'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

INSERT INTO common_lookup_lab
VALUES
(
	common_lookup_lab_s1.NEXTVAL
	,'MEMBER_LAB'
	,'DINERS_CLUB_CARD'
	,'Diners Club Card'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

-- Insert two rows into the MEMBER_LAB table. 
INSERT INTO member_lab
VALUES
(
	member_lab_s1.NEXTVAL
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'INDIVIDUAL')
	,'X15-500-01'
	,'9876-5432-1234-5678'
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'AMERICAN_EXPRESS_CARD')
	,1
	,SYSDATE
	,1
	,SYSDATE
);

INSERT INTO member_lab
VALUES
(
	member_lab_s1.NEXTVAL
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'INDIVIDUAL')
	,'X15-500-02'
	,'9876-5432-1234-5679'
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'DINERS_CLUB_CARD')
	,1
	,SYSDATE
	,1
	,SYSDATE
);

-- Insert two rows into the CONTACT_LAB table. 
INSERT INTO contact_lab
(
	contact_lab_id
	,member_lab_id
	,contact_type
	,last_name
	,first_name	
	,created_by
	,creation_date
	,last_updated_by
	,last_update_date
)
VALUES
(
	contact_lab_s1.NEXTVAL
	,(SELECT member_lab_id FROM member_lab WHERE account_number = 'X15-500-01')
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'CUSTOMER')
	,'Jones'
	,'John'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

INSERT INTO contact_lab
(
	contact_lab_id
	,member_lab_id
	,contact_type
	,last_name
	,first_name	
	,created_by
	,creation_date
	,last_updated_by
	,last_update_date
)
VALUES
(
	contact_lab_s1.NEXTVAL
	,(SELECT member_lab_id FROM member_lab WHERE account_number = 'X15-500-01')
	,(SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'CUSTOMER')
	,'Jones'
	,'Jane'
	,1
	,SYSDATE
	,1
	,SYSDATE
);

-- Insert two rows into the ADDRESS_LAB table. 
INSERT INTO address_lab
VALUES
(
	address_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'John' AND last_name = 'Jones')
	, (SELECT common_lookup_lab_ID FROM common_lookup_lab WHERE common_lookup_type = 'HOME')
	, 'Draper'
	, 'Utah'
	, '84020'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO address_lab
VALUES
(
	address_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'Jane' AND last_name = 'Jones')
	, (SELECT common_lookup_lab_ID FROM common_lookup_lab WHERE common_lookup_type = 'HOME')
	, 'Draper'
	, 'Utah'
	, '84020'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

-- Insert two rows into the STREET_ADDRESS_LAB table. 
INSERT INTO street_address_lab
VALUES
(
	street_address_lab_s1.NEXTVAL
	, (SELECT address_lab_id FROM address_lab WHERE contact_lab_id = (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'John' AND last_name = 'Jones'))
	, '372 East 12300 South'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO street_address_lab
VALUES
(
	street_address_lab_s1.NEXTVAL
	, (SELECT address_lab_id FROM address_lab WHERE contact_lab_id = (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'Jane' AND last_name = 'Jones'))
	, '1872 West 5400 South'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

-- Insert two rows into the TELEPHONE_LAB table. 
INSERT INTO telephone_lab
VALUES
(
	telephone_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'John' AND last_name = 'Jones')
	, (SELECT address_lab_id FROM address_lab WHERE contact_lab_id = (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'John' AND last_name = 'Jones'))
	, (SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'HOME')
	, '001'
	, '801'
	, '435-7654'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO telephone_lab
VALUES
(
	telephone_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'Jane' AND last_name = 'Jones')
	, (SELECT address_lab_id FROM address_lab WHERE contact_lab_id = (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'Jane' AND last_name = 'Jones'))
	, (SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'HOME')
	, '001'
	, '801'
	, '435-7655'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

-- Insert two rows into the ITEM_LAB table. 
INSERT INTO item_lab
VALUES
(
	item_lab_s1.NEXTVAL
	, 'B00N1JQ2UO'
	, (SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'DVD_WIDE_SCREEN')
	, 'Guardians of the Galaxy'
	, NULL
	, 'PG-13'
	, '09-DEC-2014'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO item_lab
VALUES
(
	item_lab_s1.NEXTVAL
	, 'B00OY7YPGK'
	, (SELECT common_lookup_lab_id FROM common_lookup_lab WHERE common_lookup_type = 'BLU-RAY')
	, 'The Maze Runner'
	, NULL
	, 'PG-13'
	, '16-DEC-2014'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

-- Insert first row into the RENTAL_LAB table. 
-- Insert first row into the RENTAL_ITEM_LAB table. 
INSERT INTO rental_lab
VALUES
(
	rental_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'John' AND last_name = 'Jones')
	, '02-JAN-2015'
	, '06-JAN-2015'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO rental_item_lab
VALUES
(
	rental_item_lab_s1.NEXTVAL
	, rental_lab_s1.CURRVAL
	, (SELECT item_lab_id FROM item_lab WHERE item_title = 'Guardians of the Galaxy')
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

-- Insert second row into the RENTAL_LAB table. 
-- Insert second row into the RENTAL_ITEM_LAB table.
INSERT INTO rental_lab
VALUES
(
	rental_lab_s1.NEXTVAL
	, (SELECT contact_lab_id FROM contact_lab WHERE first_name = 'Jane' AND last_name = 'Jones')
	, '03-JAN-2015'
	, '05-JAN-2015'
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);

INSERT INTO rental_item_lab
VALUES
(
	rental_item_lab_s1.NEXTVAL
	, rental_lab_s1.CURRVAL
	, (SELECT item_lab_id FROM item_lab WHERE item_title = 'The Maze Runner')
	, 1
	, SYSDATE
	, 1
	, SYSDATE
);






-- Verification queries
SELECT * FROM system_user_lab;

SELECT   *
FROM     common_lookup_lab
WHERE    common_lookup_context = 'MEMBER_LAB'
AND      common_lookup_type IN ('AMERICAN_EXPRESS_CARD','DINERS_CLUB_CARD');

CLEAR COLUMNS
SELECT   m.member_lab_id
,        m.member_type
,        m.account_number
,        m.credit_card_number
,        cl.common_lookup_meaning AS credit_card_type
FROM     member_lab m INNER JOIN common_lookup_lab cl
ON       m.credit_card_type = cl.common_lookup_lab_id
WHERE    common_lookup_context = 'MEMBER_LAB'
AND      common_lookup_type IN ('AMERICAN_EXPRESS_CARD','DINERS_CLUB_CARD');

CLEAR COLUMNS
SELECT   c.contact_lab_id
,        m.credit_card_type
,        c.member_lab_id
,        c.contact_type
,        c.last_name
,        c.first_name
FROM     
	member_lab m 
	INNER JOIN contact_lab c ON m.member_lab_id = c.member_lab_id 
	INNER JOIN common_lookup_lab cl1 ON m.credit_card_type = cl1.common_lookup_lab_id 
	INNER JOIN common_lookup_lab cl2 ON c.contact_type = cl2.common_lookup_lab_id
WHERE    
	cl1.common_lookup_context = 'MEMBER_LAB'
	AND cl1.common_lookup_type IN ('AMERICAN_EXPRESS_CARD','DINERS_CLUB_CARD')
	AND cl2.common_lookup_context = 'CONTACT_LAB'
	AND cl2.common_lookup_type = 'CUSTOMER';

CLEAR COLUMNS
SELECT   c.contact_lab_id
,        a.address_type
,        c.first_name
,        c.last_name
,        a.city
,        a.state_province
,        a.postal_code
FROM     contact_lab c INNER JOIN common_lookup_lab cl1
ON       c.contact_type = cl1.common_lookup_lab_id INNER JOIN address_lab a
ON       c.contact_lab_id = a.contact_lab_id INNER JOIN common_lookup_lab cl2
ON       a.address_type = cl2.common_lookup_lab_id
WHERE    cl1.common_lookup_context = 'CONTACT_LAB'
AND      cl1.common_lookup_type = 'CUSTOMER'
AND      cl2.common_lookup_context = 'MULTIPLE'
AND      cl2.common_lookup_type = 'HOME';

CLEAR COLUMNS
SELECT   c.contact_lab_id
,        a.address_lab_id
,        a.address_type
,        c.first_name
,        c.last_name
,        sa.street_address
,        a.city
,        a.state_province
,        a.postal_code
FROM     contact_lab c INNER JOIN common_lookup_lab cl1
ON       c.contact_type = cl1.common_lookup_lab_id INNER JOIN address_lab a
ON       c.contact_lab_id = a.contact_lab_id INNER JOIN street_address_lab sa
ON       a.address_lab_id = sa.address_lab_id INNER JOIN common_lookup_lab cl2
ON       a.address_type = cl2.common_lookup_lab_id
WHERE    cl1.common_lookup_context = 'CONTACT_LAB'
AND      cl1.common_lookup_type = 'CUSTOMER'
AND      cl2.common_lookup_context = 'MULTIPLE'
AND      cl2.common_lookup_type = 'HOME';

CLEAR COLUMNS
SELECT   c.contact_lab_id
,        t.telephone_lab_id
,        t.telephone_type
,        c.first_name
,        c.last_name
,        t.country_code
,        t.area_code
,        t.telephone_number
FROM     contact_lab c INNER JOIN telephone_lab t
ON       c.contact_lab_id = t.contact_lab_id
WHERE    c.first_name IN ('John','Jane')
AND      c.last_name = 'Jones';

CLEAR COLUMNS
SELECT   r.rental_lab_id
,        r.customer_id
,        r.check_out_date
,        r.return_date
FROM     rental_lab r 
WHERE    r.check_out_date IN ('02-JAN-2015','03-JAN-2015');

CLEAR COLUMNS
SELECT   i.item_lab_id
,        i.item_title
,        i.item_rating
,        i.item_release_date
FROM     item_lab i 
WHERE    i.item_release_date IN ('09-DEC-2014','16-DEC-2014');

CLEAR COLUMNS
SELECT   ri.rental_item_lab_id
,        ri.rental_lab_id
,        ri.item_lab_id
FROM     rental_item_lab ri INNER JOIN rental_lab r
ON       r.rental_lab_id = ri.rental_lab_id INNER JOIN item_lab i
ON       i.item_lab_id = ri.item_lab_id
WHERE    r.rental_lab_id IN (SELECT   r.rental_lab_id
                             FROM     rental_lab r 
                             WHERE    r.check_out_date IN ('02-JAN-2015','03-JAN-2015'))
AND      i.item_lab_id IN (SELECT   i.item_lab_id
                           FROM     item_lab i
                           WHERE    item_title IN ('Guardians of the Galaxy','The Maze Runner')
                           AND      item_release_date IN ('09-DEC-2014','16-DEC-2014'));

SPOOL OFF
