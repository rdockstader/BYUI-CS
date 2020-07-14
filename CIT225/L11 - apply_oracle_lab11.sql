-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lab9/apply_oracle_lab9.sql
SPOOL apply_oracle_lab11.txt
---------------------------------------------------------------
--Incorporate the query developed in Lab #10 into a MERGE statement into to the RENTAL table. 
MERGE INTO rental target
USING 
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
) source
ON 
(
	target.customer_id = source.contact_id
	AND target.check_out_date = source.check_out_date 
	AND target.return_date = source.return_date
)
-- New data only, do not update (according to forum post from week 9)
--WHEN MATCHED THEN
--UPDATE SET target.column_name = source.column_name
--,          target.column_name = source.column_name
WHEN NOT MATCHED THEN
INSERT VALUES
( 
	rental_s1.nextval,
	source.contact_id, 
	source.check_out_date, 
	source.return_date,
	1, 
	SYSDATE, 
	1, 
	SYSDATE
);

SELECT   TO_CHAR(COUNT(*),'99,999') AS "Rental after merge"
FROM     rental;


--Incorporate the query developed in Lab #10 into a MERGE statement into the RENTAL_ITEM table. 
MERGE INTO rental_item target
USING 
(
	SELECT 
		r.rental_id,
		c.contact_id,
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
		INNER JOIN common_lookup cl ON
			cl.common_lookup_table = 'RENTAL_ITEM'
			AND cl.common_lookup_column = 'RENTAL_ITEM_TYPE'
			AND cl.common_lookup_type = tu.return_item_type	
		INNER JOIN rental r ON 
			c.contact_id = r.customer_id 
			AND tu.check_out_date = r.check_out_date 
			AND tu.return_date = r.return_date
) source
ON 
(
	target.rental_id = source.rental_id
	AND target.item_id = source.item_id
)
-- New data only, do not update (according to forum post from week 9)
--WHEN MATCHED THEN
--UPDATE SET target.column_name = source.column_name
--,          target.column_name = source.column_name
WHEN NOT MATCHED THEN
INSERT VALUES
( 
	rental_item_s1.nextval,
        source.rental_id,
	source.item_id,
	1,
	sysdate,
	1,
	sysdate,
	source.common_lookup_id,	
	source.rental_item_price
);

SELECT   TO_CHAR(COUNT(*),'99,999') AS "Rental Item after merge"
FROM     rental_item;


--Incorporate the query developed in Lab #10 into a MERGE statement into the TRANSACTION table. 
MERGE INTO transaction target
USING 
(
	SELECT DISTINCT 
		t.transaction_id,
		tu.account_number,
		cl1.common_lookup_id AS transaction_type,
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
) source
ON 
(
	target.transaction_account = source.payment_account_number
	AND target.transaction_type = source.transaction_type
	AND target.payment_method_type = source.payment_method_type
	AND target.transaction_date = source.transaction_date
)
-- New data only, do not update (according to forum post from week 9)
--WHEN MATCHED THEN
--UPDATE SET target.column_name = source.column_name
--,          target.column_name = source.column_name
WHEN NOT MATCHED THEN
INSERT VALUES
(	
	transaction_s1.nextval,
	source.account_number,
	source.transaction_type,
	source.transaction_date,
	source.transaction_amount,
	source.rental_id,
	source.payment_method_type,
	source.payment_account_number,
	1,
	sysdate,
	1,
	sysdate
);

SELECT   TO_CHAR(COUNT(*),'99,999') AS "Transaction after merge"
FROM     transaction;


--Include the three MERGE statements into a stored PROCEDURE. 
-- Create a procedure to wrap the transaction.
CREATE OR REPLACE PROCEDURE upload_transaction IS 
BEGIN
  	-- Set save point for an all or nothing transaction.
	SAVEPOINT starting_point;
 
  	-- Merge into RENTAL table.
	MERGE INTO rental target
	USING 
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
	) source
	ON 
	(
		target.customer_id = source.contact_id
		AND target.check_out_date = source.check_out_date 
		AND target.return_date = source.return_date
	)
	-- New data only, do not update (according to forum post from week 9)
	--WHEN MATCHED THEN
	--UPDATE SET target.column_name = source.column_name
	--,          target.column_name = source.column_name
	WHEN NOT MATCHED THEN
	INSERT VALUES
	( 
		rental_s1.nextval,
		source.contact_id, 
		source.check_out_date, 
		source.return_date,
		1, 
		SYSDATE, 
		1, 
		SYSDATE
	);

	-- Merge into RENTAL_ITEM table.
	MERGE INTO rental_item target
	USING 
	(
		SELECT 
			r.rental_id,
			c.contact_id,
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
			INNER JOIN common_lookup cl ON
				cl.common_lookup_table = 'RENTAL_ITEM'
				AND cl.common_lookup_column = 'RENTAL_ITEM_TYPE'
				AND cl.common_lookup_type = tu.return_item_type	
			INNER JOIN rental r ON 
				c.contact_id = r.customer_id 
				AND tu.check_out_date = r.check_out_date 
				AND tu.return_date = r.return_date
	) source
	ON 
	(
		target.rental_id = source.rental_id
		AND target.item_id = source.item_id
	)
	-- New data only, do not update (according to forum post from week 9)
	--WHEN MATCHED THEN
	--UPDATE SET target.column_name = source.column_name
	--,          target.column_name = source.column_name
	WHEN NOT MATCHED THEN
	INSERT VALUES
	( 
		rental_item_s1.nextval,
		source.rental_id,
		source.item_id,
		1,
		sysdate,
		1,
		sysdate,
		source.common_lookup_id,	
		source.rental_item_price
	);

	-- Merge into TRANSACTION table.
	MERGE INTO transaction target
	USING 
	(
		SELECT DISTINCT 
			t.transaction_id,
			tu.account_number,
			cl1.common_lookup_id AS transaction_type,
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
	) source
	ON 
	(
		target.transaction_account = source.payment_account_number
		AND target.transaction_type = source.transaction_type
		AND target.payment_method_type = source.payment_method_type
		AND target.transaction_date = source.transaction_date
	)
	-- New data only, do not update (according to forum post from week 9)
	--WHEN MATCHED THEN
	--UPDATE SET target.column_name = source.column_name
	--,          target.column_name = source.column_name
	WHEN NOT MATCHED THEN
	INSERT VALUES
	(	
		transaction_s1.nextval,
		source.account_number,
		source.transaction_type,
		source.transaction_date,
		source.transaction_amount,
		source.rental_id,
		source.payment_method_type,
		source.payment_account_number,
		1,
		sysdate,
		1,
		sysdate
	);

	-- Save the changes.
  	COMMIT;
 
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK TO starting_point;
    RETURN;
END;
/

EXECUTE upload_transaction;

COLUMN rental_count      FORMAT 99,999 HEADING "Rental|Count"
COLUMN rental_item_count FORMAT 99,999 HEADING "Rental|Item|Count"
COLUMN transaction_count FORMAT 99,999 HEADING "Transaction|Count"
 
SELECT   il1.rental_count
,        il2.rental_item_count
,        il3.transaction_count
FROM    (SELECT COUNT(*) AS rental_count FROM rental) il1 CROSS JOIN
        (SELECT COUNT(*) AS rental_item_count FROM rental_item) il2 CROSS JOIN
        (SELECT COUNT(*) AS transaction_count FROM TRANSACTION) il3;


--Create a query that prints the following aggregated data set. 
SELECT   EXTRACT(MONTH FROM TO_DATE('02-FEB-2009'))
,        EXTRACT(YEAR FROM TO_DATE('02-FEB-2009'))
FROM     dual;

SELECT   TO_CHAR(9999,'$9,999,999.00') AS "Formatted"
FROM     dual;


SELECT
	MONTH,
	TO_CHAR(SUM(transaction_amount / 1.06),'$9,999,999.00') AS BASE_REVENUE,
	TO_CHAR(SUM(transaction_amount / 1.06 * 1.1),'$9,999,999.00') AS "10_PLUS",
	TO_CHAR(SUM(transaction_amount / 1.06 * 1.2),'$9,999,999.00') AS "20_PLUS",
	TO_CHAR(SUM(transaction_amount / 1.06 * .1),'$9,999,999.00') AS "10_PLUS_LESS_B",
	TO_CHAR(SUM(transaction_amount / 1.06 * .2),'$9,999,999.00') AS "20_PLUS_LESS_B",
	YearNum,
	MonthNum
FROM
	(
		SELECT 
			extract(year from transaction_date) AS YearNum,
			extract(month from transaction_date) AS MonthNum,
			to_char(transaction_date, 'Mon') || '-' || to_char(extract(year from transaction_date)) AS MONTH,
			transaction_amount
		FROM
			transaction
		WHERE
			extract(year from transaction_date) = 2009
	) data
GROUP BY
	MONTH,
	YearNum,
	MonthNum
ORDER BY
	YearNum,
	MonthNum;






---------------------------------------------------------------
SPOOL OFF
