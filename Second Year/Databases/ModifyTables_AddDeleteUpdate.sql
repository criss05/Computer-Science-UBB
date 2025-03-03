USE Navomodelism_Course
GO

CREATE PROCEDURE add_nrPart_from_Concursuri
AS
BEGIN
	ALTER TABLE Concursuri
	ADD Nr_participanti SMALLINT
END
GO

CREATE PROCEDURE delete_nrPart_from_Concursuri
AS
BEGIN 
	ALTER TABLE Concursuri
	DROP COLUMN Nr_participanti
END
GO

CREATE PROCEDURE modify_nrPart_from_Concursuri_to_int
AS
BEGIN
	ALTER TABLE Concursuri
	ALTER COLUMN Nr_participanti INT
END
GO

CREATE PROCEDURE modify_nrPart_from_Concursuri_to_smallint
AS
BEGIN
	ALTER TABLE Concursuri
	ALTER COLUMN Nr_participanti SMALLINT
END
GO

CREATE PROCEDURE create_table_tren
AS
BEGIN
	CREATE TABLE Tren(
	Nume_Tren CHAR(50) NOT NULL,
	Nume_Material CHAR(50),
	Id_Program SMALLINT)
END
GO

CREATE PROCEDURE drop_table_tren
AS
BEGIN
	DROP TABLE Tren
END
GO

CREATE PROCEDURE add_defalt_constraint_to_nrPart_10
AS
BEGIN
	ALTER TABLE Concursuri
	ADD CONSTRAINT df_10 DEFAULT 10 
	FOR Nr_participanti
END
GO

CREATE PROCEDURE delete_defalt_constraint_from_nrPart
AS
BEGIN
	ALTER TABLE Concursuri
	DROP CONSTRAINT df_10
END
GO


CREATE PROCEDURE add_PK_to_NumeTren
AS
BEGIN
	ALTER TABLE Tren
	ADD CONSTRAINT pk_NumeTren PRIMARY KEY(Nume_Tren)
END
GO

CREATE PROCEDURE delete_PK_from_NumeTren
AS
BEGIN
	ALTER TABLE Tren
	DROP CONSTRAINT pk_NumeTren
END
GO

CREATE PROCEDURE add_FK_to_NumeMaterial_Tren
AS
BEGIN
		ALTER TABLE Tren
		ADD CONSTRAINT fk_NumeMaterial FOREIGN KEY(Nume_Material) REFERENCES Materiale(Nume_Material)
END
GO

CREATE PROCEDURE drop_FK_to_NumeMaterial_Tren
AS
BEGIN
		ALTER TABLE Tren
		DROP CONSTRAINT fk_NumeMaterial
END
GO

CREATE PROCEDURE add_CK_to_Program_Tren
AS
BEGIN
		ALTER TABLE Tren
		ADD CONSTRAINT ck_Program UNIQUE(Id_Program) 
END
GO

CREATE PROCEDURE drop_CK_to_Program_Tren
AS
BEGIN
		ALTER TABLE Tren
		DROP CONSTRAINT ck_Program
END
GO

CREATE TABLE DBVersion(
	versionNo INT)

INSERT INTO DBVersion VALUES (0)

CREATE TABLE ProceduresVersions(
	Id INT PRIMARY KEY,
	DoProc VARCHAR(256) NOT NULL,
	UndoProc VARCHAR(256) NOT NULL)

INSERT INTO ProceduresVersions VALUES (1, 'add_nrPart_from_Concursuri', 'delete_nrPart_from_Concursuri'), (2, 'modify_nrPart_from_Concursuri_to_int', 'modify_nrPart_from_Concursuri_to_smallint') 
INSERT INTO ProceduresVersions VALUES (3, 'create_table_tren', 'drop_table_tren'), (4, 'add_defalt_constraint_to_nrPart_10', 'delete_defalt_constraint_from_nrPart'), (5, 'add_PK_to_NumeTren', 'delete_PK_from_NumeTren')
INSERT INTO ProceduresVersions VALUES (6,'add_FK_to_NumeMaterial_Tren','drop_FK_to_NumeMaterial_Tren'), (7,'add_CK_to_Program_Tren', 'drop_CK_to_Program_Tren')
DELETE FROM ProceduresVersions
GO

CREATE PROCEDURE main 
@new_version INT
AS
BEGIN
	IF @new_version < 0 OR @new_version > 7
	BEGIN
		PRINT 'This version is not in the list. Choose one between 0 and 7'
		RETURN
	END

	DECLARE @current_version INT
	DECLARE @store_proc VARCHAR(256)
	SELECT @current_version = versionNo FROM DBVersion

	IF @current_version = @new_version 
	BEGIN
		PRINT 'The version is the current one.'
		RETURN
	END

	WHILE @current_version < @new_version
	BEGIN
		SET @current_version = @current_version+1
		SELECT @store_proc = DoProc FROM ProceduresVersions WHERE Id=@current_version
		EXEC @store_proc
	END

	WHILE @current_version > @new_version
	BEGIN
		SELECT @store_proc = UndoProc FROM ProceduresVersions WHERE Id=@current_version
		EXEC @store_proc
		SET @current_version = @current_version-1
	END

	UPDATE DBVersion SET versionNo=@new_version
END
GO

EXECUTE main 2
EXECUTE main 6
EXECUTE main 7
EXECUTE main 0
EXECUTE main -1
EXECUTE main 9
UPDATE DBVersion SET versionNo=0