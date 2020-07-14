-- ----------------------------------------------------------------------
-- Instructions:
-- ----------------------------------------------------------------------
-- The two scripts contain spooling commands, which is why there
-- isn't a spooling command in this script. When you run this file
-- you first connect to the Oracle database with this syntax:
--
--   sqlplus student/student@xe
--
-- Then, you call this script with the following syntax:
--
--   sql> @apply_oracle_lab2.sql
--
-- ----------------------------------------------------------------------

-- Run the prior lab script.
@/home/student/Data/cit225/oracle/lib/cleanup.sql
@/home/student/Data/cit225/oracle/lib/create_oracle_store.sql

-- Add your lab here:
-- ----------------------------------------------------------------------
-- Open log file
SPOOL appply_oracle_lab2.log

-- ------------------------------------------------------------------
-- Create system_user_lab table and sequence and seed data.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE system_user_lab
( system_user_lab_id            NUMBER
, system_user_name          VARCHAR2(20) CONSTRAINT nn_system_user_lab_1 NOT NULL
, system_user_group_id      NUMBER       CONSTRAINT nn_system_user_lab_2 NOT NULL
, system_user_type          NUMBER       CONSTRAINT nn_system_user_lab_3 NOT NULL
, first_name                  	VARCHAR2(20)
, middle_name                 	VARCHAR2(20)
, last_name                   	VARCHAR2(20)
, created_by                  	NUMBER       CONSTRAINT nn_system_user_lab_4 NOT NULL
, creation_date               	DATE         CONSTRAINT nn_system_user_lab_5 NOT NULL
, last_updated_by             	NUMBER       CONSTRAINT nn_system_user_lab_6 NOT NULL
, last_update_date            	DATE         CONSTRAINT nn_system_user_lab_7 NOT NULL
, CONSTRAINT pk_system_user_lab_1 PRIMARY KEY(system_user_lab_id));

-- Create sequence.
CREATE SEQUENCE system_user_lab_s1 START WITH 1001;

-- Seed initial record in the system_user_lab table.
INSERT INTO system_user_lab
( system_user_lab_id
, system_user_name
, system_user_group_id
, system_user_type
, created_by
, creation_date
, last_updated_by
, last_update_date)
VALUES
( 1,'SYSADMIN', 1, 1, 1, SYSDATE, 1, SYSDATE);

-- ------------------------------------------------------------------
-- Alter system_user_lab table to include self-referencing foreign key constraints.
-- ------------------------------------------------------------------
ALTER TABLE system_user_lab
ADD CONSTRAINT fk_system_user_lab_1 FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id);

ALTER TABLE system_user_lab
ADD CONSTRAINT fk_system_user_lab_2 FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id);

-- ------------------------------------------------------------------
-- Create common_lookup_lab table and sequence and seed data.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE common_lookup_lab
( common_lookup_lab_id            	NUMBER
, common_lookup_context       		VARCHAR2(30) CONSTRAINT nn_clookup_lab_1 NOT NULL
, common_lookup_type          		VARCHAR2(30) CONSTRAINT nn_clookup_lab_2 NOT NULL
, common_lookup_meaning       		VARCHAR2(30) CONSTRAINT nn_clookup_lab_3 NOT NULL
, created_by                  		NUMBER       CONSTRAINT nn_clookup_lab_4 NOT NULL
, creation_date               		DATE         CONSTRAINT nn_clookup_lab_5 NOT NULL
, last_updated_by             		NUMBER       CONSTRAINT nn_clookup_lab_6 NOT NULL
, last_update_date            		DATE         CONSTRAINT nn_clookup_lab_7 NOT NULL
, CONSTRAINT pk_c_lookup_lab_1    		PRIMARY KEY(common_lookup_lab_id)
, CONSTRAINT fk_c_lookup_lab_1    		FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_c_lookup_lab_2    		FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a non-unique index.
CREATE INDEX common_lookup_lab_n1
  ON common_lookup_lab(common_lookup_context);

-- Create a unique index.
CREATE UNIQUE INDEX common_lookup_lab_u2
  ON common_lookup_lab(common_lookup_context,common_lookup_type);

-- Create a sequence.
CREATE SEQUENCE common_lookup_lab_s1 START WITH 1001;

-- Seed the common_lookup_lab table with 18 records.
INSERT INTO common_lookup_lab VALUES
( 1,'system_user_lab','SYSTEM_ADMIN','System Administrator', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( 2,'system_user_lab','DBA','Database Administrator', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'contact_lab','EMPLOYEE','Employee', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'contact_lab','CUSTOMER','Customer', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'member_lab','INDIVIDUAL','Individual member_labship', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'member_lab','GROUP','Group member_labship', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'member_lab','DISCOVER_CARD','Discover Card', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'member_lab','MASTER_CARD','Master Card', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'member_lab','VISA_CARD','VISA Card', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'MULTIPLE','HOME','Home', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'MULTIPLE','WORK','Work', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','DVD_FULL_SCREEN','DVD: Full Screen', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','DVD_WIDE_SCREEN','DVD: Wide Screen', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','NINTENDO_GAMECUBE','Nintendo GameCube', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','PLAYSTATION2','PlayStation2', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','XBOX','XBOX', 1, SYSDATE, 1, SYSDATE);

INSERT INTO common_lookup_lab VALUES
( common_lookup_lab_s1.nextval,'item_lab','BLU-RAY','Blu-ray', 1, SYSDATE, 1, SYSDATE);

-- Add constraints to the system_user_lab table dependent on the common_lookup_lab table.
ALTER TABLE system_user_lab
ADD CONSTRAINT fk_system_user_lab_3 FOREIGN KEY(system_user_group_id)
    REFERENCES common_lookup_lab(common_lookup_lab_id);

ALTER TABLE system_user_lab
ADD CONSTRAINT fk_system_user_lab_4 FOREIGN KEY(system_user_type)
    REFERENCES common_lookup_lab(common_lookup_lab_id);

-- ------------------------------------------------------------------
-- Create member_lab table and sequence and seed data.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE member_lab
( member_lab_id                 NUMBER
, member_lab_type               NUMBER
, account_number              	VARCHAR2(10) CONSTRAINT nn_member_lab_2 NOT NULL
, credit_card_number          	VARCHAR2(20) CONSTRAINT nn_member_lab_3 NOT NULL
, credit_card_type            	NUMBER       CONSTRAINT nn_member_lab_4 NOT NULL
, created_by                  	NUMBER       CONSTRAINT nn_member_lab_5 NOT NULL
, creation_date               	DATE         CONSTRAINT nn_member_lab_6 NOT NULL
, last_updated_by             	NUMBER       CONSTRAINT nn_member_lab_7 NOT NULL
, last_update_date            	DATE         CONSTRAINT nn_member_lab_8 NOT NULL
, CONSTRAINT pk_member_lab_1    PRIMARY KEY(member_lab_id)
, CONSTRAINT fk_member_lab_1    FOREIGN KEY(member_lab_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_member_lab_2    FOREIGN KEY(credit_card_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_member_lab_3    FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_member_lab_4    FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a non-unique index.
CREATE INDEX member_lab_n1 ON member_lab(credit_card_type);

-- Create a sequence.
CREATE SEQUENCE member_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create contact_lab table and sequence and seed data.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE contact_lab
( contact_lab_id              	NUMBER
, member_lab_id               	NUMBER       CONSTRAINT nn_contact_lab_1 NOT NULL
, contact_type                	NUMBER       CONSTRAINT nn_contact_lab_2 NOT NULL
, first_name                  	VARCHAR2(20) CONSTRAINT nn_contact_lab_3 NOT NULL
, middle_name                 	VARCHAR2(20)
, last_name                   	VARCHAR2(20) CONSTRAINT nn_contact_lab_4 NOT NULL
, created_by                  	NUMBER       CONSTRAINT nn_contact_lab_5 NOT NULL
, creation_date               	DATE         CONSTRAINT nn_contact_lab_6 NOT NULL
, last_updated_by             	NUMBER       CONSTRAINT nn_contact_lab_7 NOT NULL
, last_update_date            	DATE         CONSTRAINT nn_contact_lab_8 NOT NULL
, CONSTRAINT pk_contact_lab_1   PRIMARY KEY(contact_lab_id)
, CONSTRAINT fk_contact_lab_1   FOREIGN KEY(member_lab_id) REFERENCES member_lab(member_lab_id)
, CONSTRAINT fk_contact_lab_2   FOREIGN KEY(contact_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_contact_lab_3   FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_contact_lab_4   FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create non-unique index.
CREATE INDEX contact_lab_n1 ON contact_lab(member_lab_id);
CREATE INDEX contact_lab_n2 ON contact_lab(contact_type);

-- Create sequence.
CREATE SEQUENCE contact_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create address_lab table and sequence.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE address_lab
( address_lab_id              	NUMBER
, contact_lab_id              	NUMBER       CONSTRAINT nn_address_lab_1 NOT NULL
, address_type                	NUMBER       CONSTRAINT nn_address_lab_2 NOT NULL
, city                        	VARCHAR2(30) CONSTRAINT nn_address_lab_3 NOT NULL
, state_province              	VARCHAR2(30) CONSTRAINT nn_address_lab_4 NOT NULL
, postal_code                 	VARCHAR2(20) CONSTRAINT nn_address_lab_5 NOT NULL
, created_by                  	NUMBER       CONSTRAINT nn_address_lab_6 NOT NULL
, creation_date               	DATE         CONSTRAINT nn_address_lab_7 NOT NULL
, last_updated_by             	NUMBER       CONSTRAINT nn_address_lab_8 NOT NULL
, last_update_date            	DATE         CONSTRAINT nn_address_lab_9 NOT NULL
, CONSTRAINT pk_address_lab_1   PRIMARY KEY(address_lab_id)
, CONSTRAINT fk_address_lab_1   FOREIGN KEY(contact_lab_id) REFERENCES contact_lab(contact_lab_id)
, CONSTRAINT fk_address_lab_2   FOREIGN KEY(address_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_address_lab_3   FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_address_lab_4   FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a non-unique index.
CREATE INDEX address_lab_n1 ON address_lab(contact_lab_id);
CREATE INDEX address_lab_n2 ON address_lab(address_type);

-- Create a sequence.
CREATE SEQUENCE address_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create STREET_address_lab table and sequence.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE street_address_lab
( street_address_lab_id           	NUMBER
, address_lab_id                  	NUMBER       CONSTRAINT nn_saddress_lab_1 NOT NULL
, street_address              		VARCHAR2(30) CONSTRAINT nn_saddress_lab_2 NOT NULL
, created_by                  		NUMBER       CONSTRAINT nn_saddress_lab_3 NOT NULL
, creation_date               		DATE         CONSTRAINT nn_saddress_lab_4 NOT NULL
, last_updated_by             		NUMBER       CONSTRAINT nn_saddress_lab_5 NOT NULL
, last_update_date            		DATE         CONSTRAINT nn_saddress_lab_6 NOT NULL
, CONSTRAINT pk_s_address_lab_1   	PRIMARY KEY(street_address_lab_id)
, CONSTRAINT fk_s_address_lab_1   	FOREIGN KEY(address_lab_id) REFERENCES address_lab(address_lab_id)
, CONSTRAINT fk_s_address_lab_3   	FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_s_address_lab_4   	FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create sequence.
CREATE SEQUENCE street_address_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create telephone_lab table and sequence.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE telephone_lab
( telephone_lab_id                NUMBER
, contact_lab_id                  NUMBER       CONSTRAINT nn_telephone_lab_1 NOT NULL
, address_lab_id                  NUMBER
, telephone_type              NUMBER       CONSTRAINT nn_telephone_lab_2 NOT NULL
, country_code                VARCHAR2(3)  CONSTRAINT nn_telephone_lab_3 NOT NULL
, area_code                   VARCHAR2(6)  CONSTRAINT nn_telephone_lab_4 NOT NULL
, telephone_lab_number            VARCHAR2(10) CONSTRAINT nn_telephone_lab_5 NOT NULL
, created_by                  NUMBER       CONSTRAINT nn_telephone_lab_6 NOT NULL
, creation_date               DATE         CONSTRAINT nn_telephone_lab_7 NOT NULL
, last_updated_by             NUMBER       CONSTRAINT nn_telephone_lab_8 NOT NULL
, last_update_date            DATE         CONSTRAINT nn_telephone_lab_9 NOT NULL
, CONSTRAINT pk_telephone_lab_1   PRIMARY KEY(telephone_lab_id)
, CONSTRAINT fk_telephone_lab_1   FOREIGN KEY(contact_lab_id) REFERENCES contact_lab(contact_lab_id)
, CONSTRAINT fk_telephone_lab_2   FOREIGN KEY(telephone_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_telephone_lab_3   FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_telephone_lab_4   FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create non-unique indexes.
CREATE INDEX telephone_lab_n1 ON telephone_lab(contact_lab_id,address_lab_id);
CREATE INDEX telephone_lab_n2 ON telephone_lab(address_lab_id);
CREATE INDEX telephone_lab_n3 ON telephone_lab(telephone_type);

-- Create sequence.
CREATE SEQUENCE telephone_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create rental_lab table and sequence.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE rental_lab
( rental_lab_id                   NUMBER
, customer_id                 NUMBER CONSTRAINT nn_rental_lab_1 NOT NULL
, check_out_date              DATE   CONSTRAINT nn_rental_lab_2 NOT NULL
, return_date                 DATE   CONSTRAINT nn_rental_lab_3 NOT NULL
, created_by                  NUMBER CONSTRAINT nn_rental_lab_4 NOT NULL
, creation_date               DATE   CONSTRAINT nn_rental_lab_5 NOT NULL
, last_updated_by             NUMBER CONSTRAINT nn_rental_lab_6 NOT NULL
, last_update_date            DATE   CONSTRAINT nn_rental_lab_7 NOT NULL
, CONSTRAINT pk_rental_lab_1      PRIMARY KEY(rental_lab_id)
, CONSTRAINT fk_rental_lab_1      FOREIGN KEY(customer_id) REFERENCES contact_lab(contact_lab_id)
, CONSTRAINT fk_rental_lab_2      FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_rental_lab_3      FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a sequence.
CREATE SEQUENCE rental_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create item_lab table and sequence.
-- ------------------------------------------------------------------

-- Create a table.
CREATE TABLE item_lab
( item_lab_id                     NUMBER
, item_barcode                VARCHAR2(14) CONSTRAINT nn_item_lab_1 NOT NULL
, item_type                   NUMBER       CONSTRAINT nn_item_lab_2 NOT NULL
, item_title                  VARCHAR2(60) CONSTRAINT nn_item_lab_3 NOT NULL
, item_subtitle               VARCHAR2(60)
, item_rating                 VARCHAR2(8)  CONSTRAINT nn_item_lab_4 NOT NULL
, item_release_date           DATE         CONSTRAINT nn_item_lab_5 NOT NULL
, created_by                  NUMBER       CONSTRAINT nn_item_lab_6 NOT NULL
, creation_date               DATE         CONSTRAINT nn_item_lab_7 NOT NULL
, last_updated_by             NUMBER       CONSTRAINT nn_item_lab_8 NOT NULL
, last_update_date            DATE         CONSTRAINT nn_item_lab_9 NOT NULL
, CONSTRAINT pk_item_lab_1        PRIMARY KEY(item_lab_id)
, CONSTRAINT fk_item_lab_1        FOREIGN KEY(item_type) REFERENCES common_lookup_lab(common_lookup_lab_id)
, CONSTRAINT fk_item_lab_2        FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_item_lab_3        FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a sequence.
CREATE SEQUENCE item_lab_s1 START WITH 1001;

-- ------------------------------------------------------------------
-- Create rental_lab_item_lab table and sequence.
-- ------------------------------------------------------------------

-- Create table.
CREATE TABLE rental_item_lab
( rental_item_lab_id              NUMBER
, rental_lab_id                   NUMBER CONSTRAINT nn_rental_lab_item_lab_1 NOT NULL
, item_lab_id                     NUMBER CONSTRAINT nn_rental_lab_item_lab_2 NOT NULL
, created_by                  NUMBER CONSTRAINT nn_rental_lab_item_lab_3 NOT NULL
, creation_date               DATE   CONSTRAINT nn_rental_lab_item_lab_4 NOT NULL
, last_updated_by             NUMBER CONSTRAINT nn_rental_lab_item_lab_5 NOT NULL
, last_update_date            DATE   CONSTRAINT nn_rental_lab_item_lab_6 NOT NULL
, CONSTRAINT pk_rental_lab_item_lab_1 PRIMARY KEY(rental_item_lab_id)
, CONSTRAINT fk_rental_lab_item_lab_1 FOREIGN KEY(rental_lab_id) REFERENCES rental_lab(rental_lab_id)
, CONSTRAINT fk_rental_lab_item_lab_2 FOREIGN KEY(item_lab_id) REFERENCES item_lab(item_lab_id)
, CONSTRAINT fk_rental_lab_item_lab_3 FOREIGN KEY(created_by) REFERENCES system_user_lab(system_user_lab_id)
, CONSTRAINT fk_rental_lab_item_lab_4 FOREIGN KEY(last_updated_by) REFERENCES system_user_lab(system_user_lab_id));

-- Create a sequence.
CREATE SEQUENCE rental_item_lab_s1 START WITH 1001;

-- Commit inserted records.
COMMIT;

-- Close log file.
SPOOL OFF

-- ------------------------------------------------------------------
-- Verification scripts
-- ------------------------------------------------------------------

-- Tables
COLUMN table_name_base FORMAT A30 HEADING "Base Tables"
COLUMN table_name_lab  FORMAT A30 HEADING "Lab Tables"
SELECT   a.table_name_base
,        b.table_name_lab
FROM    (SELECT   table_name AS table_name_base
         FROM     user_tables
         WHERE    table_name IN ('SYSTEM_USER'
                                ,'COMMON_LOOKUP'
                                ,'MEMBER'
                                ,'CONTACT'
                                ,'ADDRESS'
                                ,'STREET_ADDRESS'
                                ,'TELEPHONE'
                                ,'ITEM'
                                ,'RENTAL'
                                ,'RENTAL_ITEM')) a INNER JOIN
        (SELECT   table_name AS table_name_lab
         FROM     user_tables
         WHERE    table_name IN ('SYSTEM_USER_LAB'
                                ,'COMMON_LOOKUP_LAB'
                                ,'MEMBER_LAB'
                                ,'CONTACT_LAB'
                                ,'ADDRESS_LAB'
                                ,'STREET_ADDRESS_LAB'
                                ,'TELEPHONE_LAB'
                                ,'ITEM_LAB'
                                ,'RENTAL_LAB'
                                ,'RENTAL_ITEM_LAB')) b
ON       a.table_name_base = SUBSTR( b.table_name_lab, 1, REGEXP_INSTR(table_name_lab,'_LAB') - 1)
ORDER BY CASE
           WHEN table_name_base LIKE 'SYSTEM_USER%' THEN 0
           WHEN table_name_base LIKE 'COMMON_LOOKUP%' THEN 1
           WHEN table_name_base LIKE 'MEMBER%' THEN 2
           WHEN table_name_base LIKE 'CONTACT%' THEN 3
           WHEN table_name_base LIKE 'ADDRESS%' THEN 4
           WHEN table_name_base LIKE 'STREET_ADDRESS%' THEN 5
           WHEN table_name_base LIKE 'TELEPHONE%' THEN 6
           WHEN table_name_base LIKE 'ITEM%' THEN 7
           WHEN table_name_base LIKE 'RENTAL%' AND NOT table_name_base LIKE 'RENTAL_ITEM%' THEN 8
           WHEN table_name_base LIKE 'RENTAL_ITEM%' THEN 9
         END;

-- Sequences
COLUMN sequence_name_base FORMAT A30 HEADING "Base Sequences"
COLUMN sequence_name_lab  FORMAT A30 HEADING "Lab Sequences"
SELECT   a.sequence_name_base
,        b.sequence_name_lab
FROM    (SELECT   sequence_name AS sequence_name_base
         FROM     user_sequences
         WHERE    sequence_name IN ('SYSTEM_USER_S1'
                                   ,'COMMON_LOOKUP_S1'
                                   ,'MEMBER_S1'
                                   ,'CONTACT_S1'
                                   ,'ADDRESS_S1'
                                   ,'STREET_ADDRESS_S1'
                                   ,'TELEPHONE_S1'
                                   ,'ITEM_S1'
                                   ,'RENTAL_S1'
                                   ,'RENTAL_ITEM_S1')) a INNER JOIN
        (SELECT   sequence_name AS sequence_name_lab
         FROM     user_sequences
         WHERE    sequence_name IN ('SYSTEM_USER_LAB_S1'
                                   ,'COMMON_LOOKUP_LAB_S1'
                                   ,'MEMBER_LAB_S1'
                                   ,'CONTACT_LAB_S1'
                                   ,'ADDRESS_LAB_S1'
                                   ,'STREET_ADDRESS_LAB_S1'
                                   ,'TELEPHONE_LAB_S1'
                                   ,'ITEM_LAB_S1'
                                   ,'RENTAL_LAB_S1'
                                   ,'RENTAL_ITEM_LAB_S1')) b
ON       SUBSTR(a.sequence_name_base, 1, REGEXP_INSTR(a.sequence_name_base,'_S1') - 1) =
           SUBSTR( b.sequence_name_lab, 1, REGEXP_INSTR(b.sequence_name_lab,'_LAB_S1') - 1)
ORDER BY CASE
           WHEN sequence_name_base LIKE 'SYSTEM_USER%' THEN 0
           WHEN sequence_name_base LIKE 'COMMON_LOOKUP%' THEN 1
           WHEN sequence_name_base LIKE 'MEMBER%' THEN 2
           WHEN sequence_name_base LIKE 'CONTACT%' THEN 3
           WHEN sequence_name_base LIKE 'ADDRESS%' THEN 4
           WHEN sequence_name_base LIKE 'STREET_ADDRESS%' THEN 5
           WHEN sequence_name_base LIKE 'TELEPHONE%' THEN 6
           WHEN sequence_name_base LIKE 'ITEM%' THEN 7
           WHEN sequence_name_base LIKE 'RENTAL%' AND NOT sequence_name_base LIKE 'RENTAL_ITEM%' THEN 8
           WHEN sequence_name_base LIKE 'RENTAL_ITEM%' THEN 9
         END;
