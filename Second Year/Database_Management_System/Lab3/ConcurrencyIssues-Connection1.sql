use Navomodelism_Course

--======================================
-- Dirty reads - CONNECTION 1
--======================================
BEGIN TRANSACTION
	UPDATE Materiale SET Cantitate = Cantitate + 10 WHERE Nume_Material='Lemn';

	WAITFOR DELAY '00:00:10';
	ROLLBACK;

--======================================
-- Non-Repeatable Read - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'

	WAITFOR DELAY '00:00:10'
	SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'
	COMMIT;

-- Solution
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
BEGIN TRANSACTION
	SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'

	WAITFOR DELAY '00:00:10'
	SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'
	COMMIT;

SET TRANSACTION ISOLATION LEVEL READ COMMITTED;


--======================================
-- Phantom Read - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	SELECT * FROM Materiale WHERE Cantitate > 20;

	WAITFOR DELAY '00:00:10';
	SELECT * FROM Materiale WHERE Cantitate > 20;
	COMMIT;

-- Solution
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRANSACTION
	SELECT * FROM Materiale WHERE Cantitate > 20;

	WAITFOR DELAY '00:00:10';
	SELECT * FROM Materiale WHERE Cantitate > 20;
	COMMIT;

SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

--======================================
-- Deadlock - CONNECTION 1
--======================================

-- Issue
BEGIN TRANSACTION
	UPDATE Materiale SET Cantitate = Cantitate + 10 WHERE Nume_Material = 'Lemn'

	WAITFOR DELAY '00:00:10'
	UPDATE Programe SET Nume_Program = 'Program A' WHERE ID_Program=1;
	COMMIT;

-- Solution priority low - this will be the deadlock victim
SET DEADLOCK_PRIORITY LOW;
BEGIN TRANSACTION
	UPDATE Materiale SET Cantitate = Cantitate + 10 WHERE Nume_Material = 'Lemn'

	WAITFOR DELAY '00:00:10'
	UPDATE Programe SET Nume_Program = 'Program A' WHERE ID_Program=1;
	COMMIT;

-- Solution locking in the same order
BEGIN TRANSACTION
	UPDATE Programe SET Nume_Program = 'Program A' WHERE ID_Program=1;

	WAITFOR DELAY '00:00:10'
	UPDATE Materiale SET Cantitate = Cantitate + 10 WHERE Nume_Material = 'Lemn'
	COMMIT;


select * from Programe 
select * from Materiale