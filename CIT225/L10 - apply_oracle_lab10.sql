-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lab9/apply_oracle_lab9.sql

SPOOL apply_oracle_lab10.txt
------------------------------------

--Write a query that returns the rows necessary to insert records into the RENTAL table. 
SELECT   DISTINCT c.contact_id
FROM     member m INNER JOIN transaction_upload tu
ON       m.account_number = tu.account_number INNER JOIN contact c
ON       m.member_id = c.member_id
WHERE    c.first_name = tu.first_name
AND      NVL(c.middle_name,'x') = NVL(tu.middle_name,'x')
AND      c.last_name = tu.last_name
ORDER BY c.contact_id;

SELECT   COUNT(*)
FROM     member m INNER JOIN contact c
ON       m.member_id = c.member_id;

SELECT   COUNT(*)
FROM     contact c INNER JOIN transaction_upload tu
ON       c.first_name = tu.first_name
AND      NVL(c.middle_name,'x') = NVL(tu.middle_name,'x')
AND      c.last_name = tu.last_name;

SELECT   COUNT(*)
FROM     member m INNER JOIN contact c
ON       m.member_id = c.member_id INNER JOIN transaction_upload tu
ON       c.first_name = tu.first_name
AND      NVL(c.middle_name,'x') = NVL(tu.middle_name,'x')
AND      c.last_name = tu.last_name
AND      m.account_number = tu.account_number;


SELECT   COUNT(*) AS "Rental before count"
FROM     rental;

INSERT INTO
	rental
SELECT
	rental_s1.nextval, 
	contact_id, 
	check_out_date, 
	return_date,
	1, 
	SYSDATE, 
	1, 
	SYSDATE
FROM
(
	SELECT DISTINCT 
		r.rental_id, 
		c.contact_id, 
		tu.check_out_date, 
		tu.return_date
	FROM 
		member m 
		INNER JOIN contact c ON m.member_id = c.member_id 
		INNER JOIN transaction_upload tu ON 
			tu.account_number = m.account_number
			AND tu.first_name = c.first_name
			AND NVL(tu.middle_name, 'x') = NVL(c.middle_name, 'x')
			AND tu.last_name = c.last_name 
		LEFT JOIN rental r ON 
			c.contact_id = r.customer_id 
			AND tu.check_out_date = r.check_out_date 
			AND tu.return_date = r.return_date
);

SELECT   COUNT(*) AS "Rental after count"
FROM     rental;


--Write a query that returns the rows necessary to insert records into the RENTAL_ITEM table. 
SELECT   COUNT(*) AS "Rental Item Before Count"
FROM     rental_item;

INSERT INTO
	rental_item
SELECT
	rental_item_s1.nextval,
        rental_id,
	item_id,
	1,
	sysdate,
	1,
	sysdate,
	common_lookup_id,	
	rental_item_price
FROM
(
	SELECT 
		r.rental_id,
         	tu.item_id,
         	TRUNC(r.return_date) - TRUNC(r.check_out_date) AS rental_item_price,
         	cl.common_lookup_id
	FROM 
		member m 
		INNER JOIN contact c ON m.member_id = c.member_id 
		INNER JOIN transaction_upload tu ON 
			tu.account_number = m.account_number
			AND tu.first_name = c.first_name
			AND NVL(tu.middle_name, 'x') = NVL(c.middle_name, 'x')
			AND tu.last_name = c.last_name 
		LEFT JOIN rental r ON 
			c.contact_id = r.customer_id 
			AND tu.check_out_date = r.check_out_date 
			AND tu.return_date = r.return_date
		INNER JOIN common_lookup cl ON
			cl.common_lookup_table = 'RENTAL_ITEM'
			AND cl.common_lookup_column = 'RENTAL_ITEM_TYPE'
			AND cl.common_lookup_type = tu.return_item_type
);

SELECT   COUNT(*) AS "Rental Item After Count"
FROM     rental_item;



--Write a query that returns the rows necessary to insert records into the TRANSACTION table. 
INSERT INTO
	transaction
SELECT
	transaction_s1.nextval,
	account_number,
	transaction_type_id,
	transaction_date,
	transaction_amount,
	rental_id,
	payment_method_type,
	payment_account_number,
	1,
	sysdate,
	1,
	sysdate
FROM
(
	SELECT DISTINCT 
		t.transaction_id,
		tu.account_number,
		cl1.common_lookup_id AS transaction_type_id,
		tu.transaction_date,
		SUM(tu.transaction_amount) AS transaction_amount,
		r.rental_id,
		cl2.common_lookup_id AS payment_method_type,
		tu.payment_account_number
	FROM 
		member m 
		INNER JOIN contact c ON m.member_id = c.member_id 
		INNER JOIN transaction_upload tu ON 
			tu.account_number = m.account_number
			AND tu.first_name = c.first_name
			AND NVL(tu.middle_name, 'x') = NVL(c.middle_name, 'x')
			AND tu.last_name = c.last_name 
		INNER JOIN rental r ON 
			c.contact_id = r.customer_id 
			AND tu.check_out_date = r.check_out_date 
			AND tu.return_date = r.return_date
		INNER JOIN common_lookup cl1 ON
			cl1.common_lookup_table = 'TRANSACTION'
			AND cl1.common_lookup_column = 'TRANSACTION_TYPE'
			AND cl1.common_lookup_type = tu.transaction_type
		INNER JOIN common_lookup cl2 ON
			cl2.common_lookup_table = 'TRANSACTION'
			AND cl2.common_lookup_column = 'PAYMENT_METHOD_TYPE'
			AND cl2.common_lookup_type = tu.payment_method_type
		LEFT JOIN transaction t ON
			t.transaction_account = tu.payment_account_number
			AND t.transaction_type = cl1.common_lookup_id
			AND t.payment_method_type = cl2.common_lookup_id
			AND t.transaction_date = tu.transaction_date
	GROUP BY
		t.transaction_id,
		tu.account_number,
		cl1.common_lookup_id, --AS transaction_type_id
		tu.transaction_date,
		r.rental_id,
		cl2.common_lookup_id, -- AS payment_method_type
		tu.payment_account_number
);

















------------------------------------
SPOOL OFF
