-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lab7/apply_oracle_lab7.sql

SPOOL apply_oracle_lab8.txt

--Using the query you developed in Step #4 of Lab #7, add the result set to the PRICE table. 
INSERT INTO
	price -- (item_id, price_type, active_flag, start_date, end_date, amount, created_by, creation_date, last_updated_by, last_update_date)
SELECT   
	price_s1.nextval,
	i.item_id,
	cl.common_lookup_id AS price_type,
	af.active_flag,
	--cl.common_lookup_type AS price_desc, -- REMOVE FOR INSERT
	i.release_date AS start_date,
	CASE WHEN af.active_flag = 'N' THEN TRUNC(i.release_date) + 30 ELSE null END AS end_date,
	CASE WHEN (TRUNC(SYSDATE) - 30) >= i.release_date THEN
		CASE WHEN af.active_flag = 'N' THEN
			CASE dr.rental_days
				WHEN '1' THEN 3
				WHEN '3' THEN 10
				WHEN '5' THEN 15
			END
		ELSE TO_NUMBER(dr.rental_days) END
	ELSE
		CASE dr.rental_days
			WHEN '1' THEN 3
			WHEN '3' THEN 10
			WHEN '5' THEN 15
		END
	END AS amount,
	1,
	SYSDATE,
	1,
	SYSDATE
FROM     
	item i 
	CROSS JOIN
        (
		SELECT 'Y' AS active_flag FROM dual
         	UNION ALL SELECT 'N' AS active_flag FROM dual
	) af 
	CROSS JOIN
        (
		SELECT '1' AS rental_days FROM dual
      		UNION ALL SELECT '3' AS rental_days FROM dual
         	UNION ALL SELECT '5' AS rental_days FROM dual
	) dr 
	INNER JOIN common_lookup cl ON dr.rental_days = SUBSTR(cl.common_lookup_type,1,1)
WHERE    
	cl.common_lookup_table = 'PRICE'
	AND cl.common_lookup_column = 'PRICE_TYPE'
	AND 
	(
		((TRUNC(SYSDATE) - 30) < i.release_date AND af.active_flag = 'Y')
		OR (TRUNC(SYSDATE) - 30) >= i.release_date
	);

-- *** Verify
SELECT  'OLD Y' AS "Type"
,        COUNT(CASE WHEN amount = 1 THEN 1 END) AS "1-Day"
,        COUNT(CASE WHEN amount = 3 THEN 1 END) AS "3-Day"
,        COUNT(CASE WHEN amount = 5 THEN 1 END) AS "5-Day"
,        COUNT(*) AS "TOTAL"
FROM     price p , item i
WHERE    active_flag = 'Y' AND i.item_id = p.item_id
AND     (TRUNC(SYSDATE) - TRUNC(i.release_date)) > 30
AND      end_date IS NULL
UNION ALL
SELECT  'OLD N' AS "Type"
,        COUNT(CASE WHEN amount =  3 THEN 1 END) AS "1-Day"
,        COUNT(CASE WHEN amount = 10 THEN 1 END) AS "3-Day"
,        COUNT(CASE WHEN amount = 15 THEN 1 END) AS "5-Day"
,        COUNT(*) AS "TOTAL"
FROM     price p , item i
WHERE    active_flag = 'N' AND i.item_id = p.item_id
AND     (TRUNC(SYSDATE) - TRUNC(i.release_date)) > 30
AND NOT end_date IS NULL
UNION ALL
SELECT  'NEW Y' AS "Type"
,        COUNT(CASE WHEN amount =  3 THEN 1 END) AS "1-Day"
,        COUNT(CASE WHEN amount = 10 THEN 1 END) AS "3-Day"
,        COUNT(CASE WHEN amount = 15 THEN 1 END) AS "5-Day"
,        COUNT(*) AS "TOTAL"
FROM     price p , item i
WHERE    active_flag = 'Y' AND i.item_id = p.item_id
AND     (TRUNC(SYSDATE) - TRUNC(i.release_date)) < 31
AND      end_date IS NULL
UNION ALL
SELECT  'NEW N' AS "Type"
,        COUNT(CASE WHEN amount = 1 THEN 1 END) AS "1-Day"
,        COUNT(CASE WHEN amount = 3 THEN 1 END) AS "3-Day"
,        COUNT(CASE WHEN amount = 5 THEN 1 END) AS "5-Day"
,        COUNT(*) AS "TOTAL"
FROM     price p , item i
WHERE    active_flag = 'N' AND i.item_id = p.item_id
AND     (TRUNC(SYSDATE) - TRUNC(i.release_date)) < 31
AND      NOT (end_date IS NULL);


--Add the NOT NULL constraint to the PRICE_TYPE column of the PRICE table. 
ALTER TABLE price
MODIFY
(
	price_type NUMBER NOT NULL
);


-- **** Verify
COLUMN CONSTRAINT FORMAT A10
SELECT   TABLE_NAME
,        column_name
,        CASE
           WHEN NULLABLE = 'N' THEN 'NOT NULL'
           ELSE 'NULLABLE'
         END AS CONSTRAINT
FROM     user_tab_columns
WHERE    TABLE_NAME = 'PRICE'
AND      column_name = 'PRICE_TYPE';


--You should update the RENTAL_ITEM_PRICE column of the RENTAL_ITEM table. 
UPDATE   
	rental_item ri
SET      
	rental_item_price =
  	(
		SELECT   
			p.amount
           	FROM     
			price p 
			INNER JOIN common_lookup cl1 ON p.price_type = cl1.common_lookup_id 
			CROSS JOIN rental r
                    	CROSS JOIN common_lookup cl2 
           	WHERE    
			p.item_id = ri.item_id 
			AND ri.rental_id = r.rental_id
			AND ri.rental_item_type = cl2.common_lookup_id
			AND cl1.common_lookup_code = cl2.common_lookup_code
			AND 
			(
				(r.check_out_date BETWEEN p.start_date AND p.end_date)
				OR (r.check_out_date > p.start_date AND p.end_date IS NULL)
			)
	);

-- **** Verify
COL customer_name          FORMAT A21  HEADING "Customer Name"
COL rental_id              FORMAT 9999 HEADING "Rental|ID #"
COL rental_item_id         FORMAT 9999 HEADING "Rental|Item ID"
COL rental_item_price      FORMAT 9999 HEADING "Rental|Item|Price"
COL amount                 FORMAT 9999 HEADING "Price|Amount"
COL price_type_code        FORMAT 9999 HEADING "Price|Type|Code"
COL rental_item_type_code  FORMAT 9999 HEADING "Rental|Item|Type|Code"
SELECT   c.last_name||', '||c.first_name
||       CASE
           WHEN c.middle_name IS NOT NULL THEN ' '||c.middle_name
         END AS customer_name
,        r.rental_id
,        ri.rental_item_id
,        ri.rental_item_price
,        p.amount
,        TO_NUMBER(cl2.common_lookup_code) AS price_type_code
,        TO_NUMBER(cl2.common_lookup_code) AS rental_item_type_code
FROM     price p INNER JOIN common_lookup cl1
ON       p.price_type = cl1.common_lookup_id
AND      cl1.common_lookup_table = 'PRICE'
AND      cl1.common_lookup_column = 'PRICE_TYPE' INNER JOIN rental_item ri 
ON       p.item_id = ri.item_id INNER JOIN common_lookup cl2
ON       ri.rental_item_type = cl2.common_lookup_id
AND      cl2.common_lookup_table = 'RENTAL_ITEM'
AND      cl2.common_lookup_column = 'RENTAL_ITEM_TYPE' INNER JOIN rental r
ON       ri.rental_id = r.rental_id INNER JOIN contact c
ON       r.customer_id = c.contact_id
WHERE    cl1.common_lookup_code = cl2.common_lookup_code
AND      r.check_out_date
BETWEEN  p.start_date AND NVL(p.end_date,TRUNC(SYSDATE) + 1)
ORDER BY 2, 3;


--Add a not null constraint to the RENTAL_ITEM_PRICE column of the RENTAL_ITEM table. 
ALTER TABLE rental_item
MODIFY
(
	rental_item_price NUMBER NOT NULL
);

-- **** Verify
COLUMN CONSTRAINT FORMAT A10
SELECT   TABLE_NAME
,        column_name
,        CASE
           WHEN NULLABLE = 'N' THEN 'NOT NULL'
           ELSE 'NULLABLE'
         END AS CONSTRAINT
FROM     user_tab_columns
WHERE    TABLE_NAME = 'RENTAL_ITEM'
AND      column_name = 'RENTAL_ITEM_PRICE';


SPOOL OFF

