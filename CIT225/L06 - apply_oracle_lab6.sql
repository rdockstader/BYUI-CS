-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lab5/apply_oracle_lab5.sql

SPOOL apply_oracle_lab6.txt

-- This is your beginning data model. ADD columns to the RENTAL table. 
ALTER TABLE rental_item
ADD 
(
	rental_item_type NUMBER,
	rental_item_price NUMBER
);

ALTER TABLE rental_item
ADD CONSTRAINT fk_rental_item_5 FOREIGN KEY(rental_item_type) REFERENCES common_lookup(common_lookup_id);


-- ** VERIFY
SET NULL ''
COLUMN table_name   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   table_name
,        column_id
,        column_name
,        CASE
           WHEN nullable = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS nullable
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    table_name = 'RENTAL_ITEM'
ORDER BY 2;



-- Create the following PRICE table as per the specification, but do so understanding the business logic to understand. 
CREATE TABLE price
( price_id              NUMBER
, item_id               NUMBER      CONSTRAINT nn_price_1 NOT NULL
, price_type		NUMBER
, active_flag		VARCHAR2(1) CONSTRAINT nn_price_2 NOT NULL CONSTRAINT yn_price CHECK (active_flag IN('Y', 'N'))
, start_date		DATE        CONSTRAINT nn_price_3 NOT NULL
, end_date		DATE
, amount		NUMBER CONSTRAINT nn_price_4 NOT NULL
, created_by            NUMBER CONSTRAINT nn_price_5 NOT NULL
, creation_date         DATE   CONSTRAINT nn_price_6 NOT NULL
, last_updated_by       NUMBER CONSTRAINT nn_price_7 NOT NULL
, last_update_date      DATE   CONSTRAINT nn_price_8 NOT NULL
, CONSTRAINT pk_price_1 PRIMARY KEY(price_id)
, CONSTRAINT fk_price_1 FOREIGN KEY(item_id) REFERENCES item(item_id)
, CONSTRAINT fk_price_2 FOREIGN KEY(price_type) REFERENCES common_lookup(common_lookup_id)
, CONSTRAINT fk_price_3 FOREIGN KEY(created_by) REFERENCES system_user(system_user_id)
, CONSTRAINT fk_price_4 FOREIGN KEY(last_updated_by) REFERENCES system_user(system_user_id));

CREATE SEQUENCE price_s1 START WITH 1001;

ALTER TABLE rental_item
ADD CONSTRAINT fk_rental_item_6 FOREIGN KEY(rental_item_price) REFERENCES price(price_id);


-- ** VERIFY
SET NULL ''
COLUMN table_name   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   table_name
,        column_id
,        column_name
,        CASE
           WHEN nullable = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS nullable
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    table_name = 'PRICE'
ORDER BY 2;

COLUMN constraint_name   FORMAT A16
COLUMN search_condition  FORMAT A30
SELECT   uc.constraint_name
,        uc.search_condition
FROM     user_constraints uc INNER JOIN user_cons_columns ucc
ON       uc.table_name = ucc.table_name
AND      uc.constraint_name = ucc.constraint_name
WHERE    uc.table_name = UPPER('price')
AND      ucc.column_name = UPPER('active_flag')
AND      uc.constraint_name = UPPER('yn_price')
AND      uc.constraint_type = 'C';

-- Insert new data into the model. 

-- lookup items
INSERT INTO
	common_lookup
VALUES
(
	 common_lookup_s1.nextval
	, 'RENTAL'
	, '1-Day'
	, '1-Day Rental Period'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	common_lookup
VALUES
(
	 common_lookup_s1.nextval
	, 'RENTAL'
	, '3-Day'
	, '3-Day Rental Period'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	common_lookup
VALUES
(
	 common_lookup_s1.nextval
	, 'RENTAL'
	, '5-Day'
	, '5-Day Rental Period'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

-- items
ALTER TABLE item
RENAME COLUMN item_release_date TO release_date;

INSERT INTO item
VALUES
(
	item_s1.nextval,
	'2084-2440917-1',
	(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'ITEM' AND common_lookup_type = 'BLU-RAY'), -- (1015) bluray
	'Tron',
	NULL,
	'PG-13',
	TRUNC(SYSDATE) - 1,
	1, -- sysadmin
	SYSDATE,
	1, -- sysadmin
	SYSDATE
);

INSERT INTO item
VALUES
(
	item_s1.nextval,
	'2084-2440917-2',
	(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'ITEM' AND common_lookup_type = 'BLU-RAY'), -- (1015) bluray
	'Ender''s Game',
	NULL,
	'PG-13',
	TRUNC(SYSDATE) - 1,
	1, -- sysadmin
	SYSDATE,
	1, -- sysadmin
	SYSDATE
);

INSERT INTO item
VALUES
(
	item_s1.nextval,
	'2084-2440917-3',
	(SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'ITEM' AND common_lookup_type = 'BLU-RAY'), -- (1015) bluray
	'Elysium',
	NULL,
	'PG-13',
	TRUNC(SYSDATE) - 1,
	1, -- sysadmin
	SYSDATE,
	1, -- sysadmin
	SYSDATE
);


-- ** VERIFY
SET NULL ''
COLUMN TABLE_NAME   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   TABLE_NAME
,        column_id
,        column_name
,        CASE
           WHEN NULLABLE = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS NULLABLE
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    TABLE_NAME = 'ITEM'
ORDER BY 2;

SELECT   i.item_title
,        SYSDATE AS today
,        i.release_date
FROM     item i
WHERE   (SYSDATE - i.release_date) < 31;

-- members

-- harry
INSERT INTO
	member
VALUES
( 
	member_s1.NEXTVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'CONTACT' AND common_lookup_type = 'CUSTOMER') -- (1002) customer
	, '0000000001'
	, '1234-5678-8765-4321'
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MEMBER' AND common_lookup_type = 'VISA_CARD') -- (1007) visa
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	contact
VALUES
( 
	contact_s1.NEXTVAL
	, member_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, 'Harry'
	, 'James' 
	, 'Potter'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	address
VALUES
( 
	address_s1.NEXTVAL
	, contact_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') --(1008) home
	, 'Provo'
	, 'Utah'
	, '84097'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	street_address
VALUES
( 
	street_address_s1.NEXTVAL
	, address_s1.CURRVAL
	, '123 Hogwarts Ave'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	telephone
VALUES
( 
	telephone_s1.NEXTVAL
	, contact_s1.CURRVAL
	, address_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, '01'
	, '801'
	, '555-1234'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

-- ginny
INSERT INTO
	member
VALUES
( 
	member_s1.NEXTVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'CONTACT' AND common_lookup_type = 'CUSTOMER') -- (1002) customer
	, '0000000002'
	, '1234-5678-8765-4322'
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MEMBER' AND common_lookup_type = 'VISA_CARD') -- (1007) visa
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	contact
VALUES
( 
	contact_s1.NEXTVAL
	, member_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, 'Ginny'
	, 'Weasley' 
	, 'Potter'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	address
VALUES
( 
	address_s1.NEXTVAL
	, contact_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, 'Provo'
	, 'Utah'
	, '84097'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	street_address
VALUES
( 
	street_address_s1.NEXTVAL
	, address_s1.CURRVAL
	, '123 Hogwarts Ave'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	telephone
VALUES
( 
	telephone_s1.NEXTVAL
	, contact_s1.CURRVAL
	, address_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, '01'
	, '801'
	, '555-1235'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

-- lily
INSERT INTO
	member
VALUES
( 
	member_s1.NEXTVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'CONTACT' AND common_lookup_type = 'CUSTOMER') -- (1002) customer
	, '0000000003'
	, '1234-5678-8765-4323'
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MEMBER' AND common_lookup_type = 'VISA_CARD') -- (1007) visa
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	contact
VALUES
( 
	contact_s1.NEXTVAL
	, member_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, 'Lily'
	, 'Evans' 
	, 'Potter'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	address
VALUES
( 
	address_s1.NEXTVAL
	, contact_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, 'Provo'
	, 'Utah'
	, '84097'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	street_address
VALUES
( 
	street_address_s1.NEXTVAL
	, address_s1.CURRVAL
	, '127 Hogwarts Ave'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	telephone
VALUES
( 
	telephone_s1.NEXTVAL
	, contact_s1.CURRVAL
	, address_s1.CURRVAL
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME') -- (1008) home
	, '01'
	, '801'
	, '555-1236'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);


-- ** VERIFY
COLUMN full_name FORMAT A20
COLUMN city      FORMAT A10
COLUMN state     FORMAT A10
SELECT   c.last_name || ', ' || c.first_name AS full_name
,        a.city
,        a.state_province AS state
FROM     member m INNER JOIN contact c
ON       m.member_id = c.member_id INNER JOIN address a
ON       c.contact_id = a.contact_id INNER JOIN street_address sa
ON       a.address_id = sa.address_id INNER JOIN telephone t
ON       c.contact_id = t.contact_id
WHERE    c.last_name = 'Potter';


-- rent some movies
INSERT INTO
	rental
VALUES
( 
	rental_s1.NEXTVAL
	, (SELECT contact_id FROM contact WHERE first_name = 'Harry' AND last_name = 'Potter')
	, TRUNC(SYSDATE)
	, TRUNC(SYSDATE) + 1
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	rental_item
VALUES
( 
	rental_item_s1.NEXTVAL
	, rental_s1.CURRVAL
	, (SELECT item_id FROM item WHERE item_title = 'Elysium')
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_type = '1-Day')
	, NULL -- price
);

INSERT INTO
	rental_item
VALUES
( 
	rental_item_s1.NEXTVAL
	, rental_s1.CURRVAL
	, (SELECT item_id FROM item WHERE item_title = 'Tron')
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_type = '1-Day')
	, NULL -- price
);

INSERT INTO
	rental
VALUES
( 
	rental_s1.NEXTVAL
	, (SELECT contact_id FROM contact WHERE first_name = 'Ginny' AND last_name = 'Potter')
	, TRUNC(SYSDATE)
	, TRUNC(SYSDATE) + 3
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	rental_item
VALUES
( 
	rental_item_s1.NEXTVAL
	, rental_s1.CURRVAL
	, (SELECT item_id FROM item WHERE item_title = 'Ender''s Game')
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_type = '3-Day')
	, NULL -- price
);

INSERT INTO
	rental
VALUES
( 
	rental_s1.NEXTVAL
	, (SELECT contact_id FROM contact WHERE first_name = 'Lily' AND last_name = 'Potter')
	, TRUNC(SYSDATE)
	, TRUNC(SYSDATE) + 5
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

INSERT INTO
	rental_item
VALUES
( 
	rental_item_s1.NEXTVAL
	, rental_s1.CURRVAL
	, (SELECT item_id FROM item WHERE item_title = 'Camelot')
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
	, (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_type = '5-Day')
	, NULL -- price
);


-- ** VERIFY
COLUMN full_name   FORMAT A18
COLUMN rental_id   FORMAT 9999
COLUMN rental_days FORMAT A14
COLUMN rentals     FORMAT 9999
COLUMN items       FORMAT 9999
SELECT   c.last_name||', '||c.first_name||' '||c.middle_name AS full_name
,        r.rental_id
,       (r.return_date - r.check_out_date) || '-DAY RENTAL' AS rental_days
,        COUNT(DISTINCT r.rental_id) AS rentals
,        COUNT(ri.rental_item_id) AS items
FROM     rental r INNER JOIN rental_item ri
ON       r.rental_id = ri.rental_id INNER JOIN contact c
ON       r.customer_id = c.contact_id
WHERE   (SYSDATE - r.check_out_date) < 15
AND      c.last_name = 'Potter'
GROUP BY c.last_name||', '||c.first_name||' '||c.middle_name
,        r.rental_id
,       (r.return_date - r.check_out_date) || '-DAY RENTAL'
ORDER BY 2;


-- Modify the design of the COMMON_LOOKUP table, insert new data into the model, and update old non-compliant design data in the model. 


-- drop index
DROP INDEX COMMON_LOOKUP_N1;
DROP INDEX COMMON_LOOKUP_U2;


-- ** VERIFY
COLUMN table_name FORMAT A14
COLUMN index_name FORMAT A20
SELECT   table_name
,        index_name
FROM     user_indexes
WHERE    table_name = 'COMMON_LOOKUP';

-- add columns
ALTER TABLE common_lookup
ADD 
(
	common_lookup_table  VARCHAR2(30),
	common_lookup_column VARCHAR2(30),
	common_lookup_code   VARCHAR2(30)
);

-- ** VERIFY
SET NULL ''
COLUMN table_name   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   table_name
,        column_id
,        column_name
,        CASE
           WHEN nullable = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS nullable
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    table_name = 'COMMON_LOOKUP'
ORDER BY 2;

-- move data
UPDATE common_lookup
SET common_lookup_table = common_lookup_context
WHERE common_lookup_context IS NOT NULL;

UPDATE common_lookup
SET common_lookup_table = 'ADDRESS'
WHERE common_lookup_context = 'MULTIPLE';

UPDATE common_lookup
SET common_lookup_column = common_lookup_context || '_TYPE'
WHERE common_lookup_table = 'MEMBER' AND common_lookup_type IN ('INDIVIDUAL', 'GROUP');

UPDATE common_lookup
SET common_lookup_column = 'CREDIT_CARD_TYPE'
WHERE common_lookup_type IN ('VISA_CARD', 'MASTER_CARD', 'DISCOVER_CARD');

UPDATE common_lookup
SET common_lookup_column = 'ADDRESS_TYPE'
WHERE common_lookup_context = 'MULTIPLE';

UPDATE common_lookup
SET common_lookup_column = common_lookup_context || '_TYPE'
WHERE common_lookup_context NOT IN ('MULTIPLE', 'MEMBER');

INSERT INTO common_lookup
(
	common_lookup_id,
	common_lookup_context,
	common_lookup_meaning,
	common_lookup_table,
	common_lookup_column,
	common_lookup_type,
	created_by,
	creation_date,
	last_updated_by,
	last_update_date
)
VALUES
(
	common_lookup_s1.NEXTVAL,
	'OLD',
	'OLD',
	'TELEPHONE',
	'TELEPHONE_TYPE',
	'HOME'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

UPDATE telephone
SET telephone_type = common_lookup_s1.CURRVAL
WHERE telephone_type = (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'HOME');

INSERT INTO common_lookup
(
	common_lookup_id,
	common_lookup_context,
	common_lookup_meaning,
	common_lookup_table,
	common_lookup_column,
	common_lookup_type,
	created_by,
	creation_date,
	last_updated_by,
	last_update_date
)
VALUES
(
	common_lookup_s1.NEXTVAL,
	'OLD',
	'OLD',
	'TELEPHONE',
	'TELEPHONE_TYPE',
	'WORK'
	, 1 -- sysadmin
	, SYSDATE
	, 1 -- sysadmin
	, SYSDATE
);

UPDATE telephone
SET telephone_type = common_lookup_s1.CURRVAL
WHERE telephone_type = (SELECT common_lookup_id FROM common_lookup WHERE common_lookup_context = 'MULTIPLE' AND common_lookup_type = 'WORK');

-- ** VERIFY
SET NULL ''
COLUMN table_name   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   table_name
,        column_id
,        column_name
,        CASE
           WHEN nullable = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS nullable
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    table_name = 'COMMON_LOOKUP'
ORDER BY 2;

COLUMN common_lookup_table  FORMAT A20
COLUMN common_lookup_column FORMAT A20
COLUMN common_lookup_type   FORMAT A20
SELECT   common_lookup_table
,        common_lookup_column
,        common_lookup_type
FROM     common_lookup
ORDER BY 1, 2, 3;

COLUMN common_lookup_table  FORMAT A14 HEADING "Common|Lookup Table"
COLUMN common_lookup_column FORMAT A14 HEADING "Common|Lookup Column"
COLUMN common_lookup_type   FORMAT A8  HEADING "Common|Lookup|Type"
COLUMN count_dependent      FORMAT 999 HEADING "Count of|Foreign|Keys"
COLUMN count_lookup         FORMAT 999 HEADING "Count of|Primary|Keys"
SELECT   cl.common_lookup_table
,        cl.common_lookup_column
,        cl.common_lookup_type
,        COUNT(a.address_id) AS count_dependent
,        COUNT(DISTINCT cl.common_lookup_table) AS count_lookup
FROM     address a RIGHT JOIN common_lookup cl
ON       a.address_type = cl.common_lookup_id
WHERE    cl.common_lookup_table = 'ADDRESS'
AND      cl.common_lookup_column = 'ADDRESS_TYPE'
AND      cl.common_lookup_type IN ('HOME','WORK')
GROUP BY cl.common_lookup_table
,        cl.common_lookup_column
,        cl.common_lookup_type
UNION
SELECT   cl.common_lookup_table
,        cl.common_lookup_column
,        cl.common_lookup_type
,        COUNT(t.telephone_id) AS count_dependent
,        COUNT(DISTINCT cl.common_lookup_table) AS count_lookup
FROM     telephone t RIGHT JOIN common_lookup cl
ON       t.telephone_type = cl.common_lookup_id
WHERE    cl.common_lookup_table = 'TELEPHONE'
AND      cl.common_lookup_column = 'TELEPHONE_TYPE'
AND      cl.common_lookup_type IN ('HOME','WORK')
GROUP BY cl.common_lookup_table
,        cl.common_lookup_column
,        cl.common_lookup_type;

-- drop old column, update nulls
ALTER TABLE common_lookup DROP COLUMN common_lookup_context;

ALTER TABLE
	common_lookup
MODIFY
(
	common_lookup_table VARCHAR2(30) NOT NULL,
	common_lookup_column VARCHAR2(30) NOT NULL
);

-- ** VERIFY
SET NULL ''
COLUMN table_name   FORMAT A14
COLUMN column_id    FORMAT 9999
COLUMN column_name  FORMAT A22
COLUMN data_type    FORMAT A12
SELECT   table_name
,        column_id
,        column_name
,        CASE
           WHEN nullable = 'N' THEN 'NOT NULL'
           ELSE ''
         END AS nullable
,        CASE
           WHEN data_type IN ('CHAR','VARCHAR2','NUMBER') THEN
             data_type||'('||data_length||')'
           ELSE
             data_type
         END AS data_type
FROM     user_tab_columns
WHERE    table_name = 'COMMON_LOOKUP'
ORDER BY 2;

-- create uq
CREATE UNIQUE INDEX common_lookup_u2
  ON common_lookup(common_lookup_table, common_lookup_column ,common_lookup_type);

-- ** VERIFY
COLUMN table_name FORMAT A14
COLUMN index_name FORMAT A20
SELECT   table_name
,        index_name
FROM     user_indexes
WHERE    table_name = 'COMMON_LOOKUP';




SPOOL OFF










