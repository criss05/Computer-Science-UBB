USE Navomodelism_Course

--======================================
--Dirty reads - CONNECTION 2
--======================================

-- Issue
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
PRINT 'Result without preventing the dirty reads'
SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'
GO

-- Solution
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
PRINT 'Result preventing the dirty reads'
SELECT Cantitate FROM Materiale WHERE Nume_Material='Lemn'
GO

--======================================
-- Non-Repeatable Reads - CONNECTION 2
--======================================
BEGIN TRANSACTION
	UPDATE Materiale SET Cantitate = Cantitate + 5 WHERE Nume_Material='Lemn'
	COMMIT;

--======================================
-- Phantom reads - CONNECTION 2
--======================================
BEGIN TRANSACTION;
	INSERT INTO Materiale (Nume_Material, Cantitate) VALUES ('Sticla', 60);
	COMMIT;

Delete from Materiale Where Nume_Material = 'Sticla'

--======================================
-- Deadlock - CONNECTION 1
--======================================
BEGIN TRANSACTION;
	UPDATE Programe SET Nume_Program='Program B' WHERE ID_Program=1

	WAITFOR DELAY '00:00:10';
	UPDATE Materiale SET Cantitate = Cantitate + 5 WHERE Nume_Material = 'Lemn';
	COMMIT;


UPDATE Programe SET Nume_Program='Masini' WHERE ID_Program=1
UPDATE Materiale SET Cantitate = 20 WHERE Nume_Material = 'Lemn';
