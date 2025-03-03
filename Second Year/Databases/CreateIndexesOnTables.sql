USE Navomodelism_Course

CREATE TABLE Modele(
	MID INT PRIMARY KEY,
	Cod_Serie INT UNIQUE,
	Nume VARCHAR(50),
	Cantitate INT
)

CREATE TABLE Evenimente(
	EID INT PRIMARY KEY,
	Model INT REFERENCES Modele(MID),
	JID INT REFERENCES  Jury(JID),
	Nume VARCHAR(50),
	Locatie VARCHAR(100)	
)


Execute  InsertData Modele, 1000
Execute  InsertData Evenimente, 1000

SELECT * FROM Modele
SELECT * FROM Evenimente
SELECT * FROM Jury

--A)

--Clustered index scan on PK
--0073
SELECT * 
FROM Modele 
ORDER BY MID

--Clustered index scan on PK
--0073
SELECT * 
FROM Modele 
WHERE MID % 2 = 0

--Clustered index seek on PK
--0032
SELECT * 
FROM Modele 
WHERE MID BETWEEN 7 AND 11

--Clustered index seek on PK
--0033
SELECT * 
FROM Modele 
WHERE MID > 900

--Clustered index Scan
--0073
SELECT Cod_Serie, MID, Nume
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 11

--Non-clustered index seek
--0032
SELECT MID
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 11

--Non-clustered index seek and Key lookup on UNIQUE
--0133
SELECT *
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 11
ORDER BY Cod_Serie

--Clustered index Scan
--0350
SELECT * 
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 1000
ORDER BY Cod_Serie

---Non-clustered index seek on UNIQUE
--0032
SELECT Cod_Serie 
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 11

--Non-clustered index scan
--0051
SELECT Cod_Serie
FROM Modele
ORDER BY Cod_Serie

--Non-clustered index seek
--0032
SELECT Cod_Serie, MID
FROM Modele 
WHERE Cod_Serie BETWEEN 7 AND 11

--Clustered index scan
--0342
SELECT *
FROM Modele
ORDER BY Cantitate

--Clustered index scan
--0073
SELECT * 
FROM Modele
WHERE Cantitate in (100, 200, 300)

--Clustered index / Non-clustered index seek 
--0073 / 0032
SELECT MID, Cantitate
FROM Modele
WHERE Cantitate in (100, 200, 300)

IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='N_index_Cantitate')
	DROP INDEX N_index_Cantitate ON Modele
CREATE NONCLUSTERED INDEX N_index_Cantitate ON Modele(Cantitate)



--B)

--Clustered index scan
--0058
SELECT * 
FROM Jury
WHERE NoJuries = 100

--Clustered index scan
--0058
SELECT JID, NoJuries
FROM Jury
WHERE NoJuries = 100

--Clustered index scan
--0058
SELECT NoJuries
FROM Jury
WHERE NoJuries = 100

--Clustered index scan
--0058
SELECT NoJuries, RID
FROM Jury
WHERE NoJuries = 100

IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='N__index_NoJuries')
	DROP INDEX N__index_NoJuries ON Jury

CREATE NONCLUSTERED INDEX N__index_NoJuries ON Jury(NoJuries)

--Clustered index scan
--0058
SELECT * 
FROM Jury
WHERE NoJuries = 100

--Non-clustered index seek
--0032
SELECT JID, NoJuries
FROM Jury
WHERE NoJuries = 100

--Non-clustered index seek
--0032
SELECT NoJuries
FROM Jury
WHERE NoJuries = 100

--Clustered index scan
--0058
SELECT NoJuries, RID
FROM Jury
WHERE NoJuries = 100




--C)

GO
CREATE OR ALTER VIEW ModeleleLaEvenimenteCuJuriulSiCAntitateIntre100_130
AS
	SELECT e.Model, e.EID, e.JID
	FROM Modele m INNER JOIN Evenimente e ON m.MID = e.Model
					INNER JOIN Jury j ON e.JID = j.JID
	WHERE m.Cantitate > 100 AND m.Cantitate<130
GO

SELECT * FROM ModeleleLaEvenimenteCuJuriulSiCAntitateIntre100_130

IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='N_index_Model_EID_JID')
	DROP INDEX N_index_Model_EID_JID ON Evenimente

CREATE NONCLUSTERED INDEX N_index_Model_EID_JID ON Evenimente(Model, JID)

--0551 (fara nimic)
--0502 (cu cantitate)
--0471 (cu evenimente)