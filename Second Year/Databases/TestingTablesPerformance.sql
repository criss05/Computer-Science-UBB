use Navomodelism_Course

--Take the tables used for tests
INSERT INTO Tables VALUES ('Room'), ('Jury'), ('ProjectFair')

CREATE TABLE Room(
	RID INT PRIMARY KEY,
	Rlocation VARCHAR(100),
	Rcapacity INT)

CREATE TABLE ProjectFair(
	PFName VARCHAR(100),
	PFDate DATETIME,
	RID INT FOREIGN KEY REFERENCES Room(RID),
	PRIMARY KEY (PFName, PFDate))

CREATE TABLE Jury(
	JID INT PRIMARY KEY,
	RID INT FOREIGN KEY REFERENCES Room(RID),
	NoJuries INT)
GO

--Create the views for the tables above

--View on one table
CREATE VIEW RoomsFromBucurestiAndConstanta AS
	SELECT *
	FROM Room R
	WHERE R.RLocation IN('Bucuresti', 'Constanta')
GO

--View on >2 tables
CREATE VIEW RoomsUsedForProjectFairsAndJuries AS
	SELECT R.RID, R.Rlocation
	FROM Room R
	WHERE EXISTS(SELECT PF.RID
				FROM ProjectFair PF
				WHERE PF.RID=R.RID AND PF.RID IN (SELECT RID
												FROM Jury))
GO

--View on 2 tables using GROUP BY
CREATE VIEW ProjectFairsPerRoom AS
	SELECT R.RID, Count(PF.PFName) as ProjectFairs
	FROM Room R INNER JOIN ProjectFair PF ON R.RID=PF.RID
	GROUP BY R.RID
GO

--insert the views from above
INSERT INTO Views VALUES ('RoomsFromBucurestiAndConstanta'), ('RoomsUsedForProjectFairsAndJuries'), ('ProjectFairsPerRoom')
GO

--create the procedure that runs a view given as a parameter
CREATE PROCEDURE RunView @view_name VARCHAR(100)
AS
BEGIN 
	DECLARE @DS DATETIME
	DECLARE @DE DATETIME

	SET @DS = GETDATE()
	DECLARE @String VARCHAR(100)='SELECT * FROM ' + @view_name
	EXEC (@String)
	SET @DE = GETDATE()
	PRINT 'Time:' 
	PRINT DATEDIFF(second, @DE, @DS)
END

--create the procedure that deletes all the data from a specific table given as parameter
GO
CREATE OR ALTER PROCEDURE DeleteAll
	@table_name VARCHAR(100)
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @query VARCHAR(150) = 'DELETE FROM ' + @table_name
	EXEC (@query)
END

--create the procedure that inserts in a given table a given number of rows
GO
CREATE OR ALTER PROCEDURE InsertData
    @table_name VARCHAR(100),
	@no_rows INT
AS
BEGIN
		SET NOCOUNT ON
		CREATE TABLE ColumnData(col VARCHAR(100), typ varchar(100))
		INSERT INTO ColumnData SELECT c.name AS col, t.name AS typ
									FROM sys.objects o
									INNER JOIN sys.columns c ON o.object_id = c.object_id
									INNER JOIN sys.types t ON c.user_type_id = t.user_type_id
									WHERE o.type = 'U' AND o.name = @table_name
		DECLARE @index INT = 0
		DECLARE ColumnCursor CURSOR For
		SELECT col, typ FROM ColumnData
		DECLARE @column VARCHAR(100)
		DECLARE @type VARCHAR(100)
		DECLARE @query VARCHAR(300)='INSERT INTO ' + @table_name + ' VALUES ('

		WHILE @index < @no_rows
		BEGIN
			OPEN ColumnCursor

			FETCH NEXT FROM ColumnCursor INTO @column, @type
			WHILE @@FETCH_STATUS = 0
			BEGIN
				IF @type LIKE '%int%' OR @type LIKE '%decimal%' OR @type LIKE '%float%'
					SET @query = @query + CONVERT(VARCHAR, @index) + ','
				ELSE IF @type LIKE '%char%' OR @type LIKE '%text%'
					SET @query = @query + '''Text_' + CONVERT(VARCHAR, @index) + ''''+ ','
				ELSE IF @type LIKE '%date%' OR @type LIKE '%time%'
					SET @query = @query + 'GETDATE()' + ','
				ELSE 
					SET @query = @query + 'NULL'+ ','

				FETCH NEXT FROM ColumnCursor INTO @column, @type
			END
			CLOSE ColumnCursor
			

			SET @query = LEFT(@query, LEN(@query)-1)
			SET @query = @query + ')'

			EXEC (@query)
			SET @query = 'INSERT INTO ' + @table_name + ' VALUES ('

			SET @index = @index + 1
		END
		DEALLOCATE ColumnCursor
		DROP TABLE ColumnData
END;
GO

INSERT INTO Tests VALUES('delete_insert'), ('insert'), ('select_view'), ('delete')

INSERT INTO TestViews VALUES (3,4),(3,5),(3,6)

INSERT INTO TestTables VALUES(1,10, 10000, 1), (1, 11, 1000,2),(1,12, 500,3)


GO

--create procedures that run tests for insert and delete into/from table
CREATE OR ALTER PROCEDURE SP_test_tables
	@testId INT,
	@testRunId INT
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @table_name VARCHAR(100)
	DECLARE @tableId INT
	DECLARE @no_rows INT
	DECLARE @position INT
	DECLARE @DS DATETIME
	DECLARE @DE DATETIME

	DECLARE tablesCursor CURSOR  SCROLL FOR
	SELECT TableID, NoOfRows, Position
	FROM TestTables
	WHERE TestID=@testId
	ORDER BY Position

	OPEN tablesCursor
	--delete from tables
	FETCH LAST FROM tablesCursor INTO @tableId, @no_rows, @position
	WHILE @@FETCH_STATUS =0
	BEGIN
		SELECT @table_name = Name
		FROM Tables
		WHERE TableID = @tableId

		EXECUTE DeleteAll @table_name
		FETCH PRIOR FROM tablesCursor INTO @tableId, @no_rows, @position
	END

	--insert into tables
	FETCH FIRST FROM tablesCursor INTO @tableId, @no_rows, @position
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SELECT @table_name = Name
		FROM Tables
		WHERE TableID = @tableId

		SET @DS = GETDATE()

		EXECUTE InsertData @table_name, @no_rows

		SET @DE = GETDATE()

		INSERT INTO TestRunTables VALUES(@testRunId, @tableId, @DS, @DE)
		PRINT 'TIME for insertion: ' + CONVERT(VARCHAR, @no_rows) + ' in ' + CONVERT(VARCHAR, DATEDIFF(MILLISECOND, @DS, @DE)) + ' milliseconds'
		FETCH NEXT FROM tablesCursor INTO @tableId, @no_rows, @position
	END
	CLOSE tablesCursor
	DEALLOCATE tablesCursor
	
END
GO

--create procedure that runs the tests for the views

CREATE OR ALTER PROCEDURE SP_test_views 
	@testId INT,
	@testRunId INT
AS
BEGIN
	SET NOCOUNT ON
	DECLARE @view_name VARCHAR(100)
	DECLARE @view_id INT
	DECLARE @DS DATETIME
	DECLARE @DE DATETIME

	DECLARE viewsCursor CURSOR FOR
	SELECT ViewID
	FROM TestViews
	WHERE TestID=@testId

	OPEN viewsCursor
	FETCH NEXT FROM viewsCursor INTO @view_id
	WHILE @@FETCH_STATUS=0
	BEGIN
		SELECT @view_name = Name
		FROM Views
		WHERE ViewID=@view_id

		SET @DS =GETDATE()

		EXECUTE RunView @view_name

		SET @DE = GETDATE()

		INSERT INTO TestRunViews VALUES(@testRunId, @view_id, @DS, @DE)
		PRINT 'Time for view:' + @view_name + ' in ' + CONVERT(VARCHAR, DATEDIFF(MILLISECOND, @DS, @DE)) + ' milliseconds'
		FETCH NEXT FROM viewsCursor INTO @view_id
	END
	CLOSE viewsCursor
	DEALLOCATE viewsCursor
END

GO
CREATE OR ALTER PROCEDURE SP_test_run
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @DS DATETIME
	DECLARE @DE DATETIME
	DECLARE @test_id INT
	DECLARE @test_name VARCHAR(100)
	DECLARE @description VARCHAR(200)
	DECLARE @test_run_id INT

	DECLARE testsCursor CURSOR FOR 
	SELECT TestID, Name
	FROM Tests
	
	OPEN testsCursor
	FETCH NEXT FROM testsCursor INTO @test_id, @test_name
	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @description = 'Running test ' + @test_name
		INSERT INTO TestRuns (Description) VALUES (@description)
		SET @test_run_id = SCOPE_IDENTITY()

		SET @DS=GETDATE()
		EXECUTE SP_test_tables @test_id, @test_run_id
		EXECUTE SP_test_views @test_id, @test_run_id
		SET @DE=GETDATE()

		UPDATE TestRuns
		SET StartAt = @DS
		WHERE TestRunId=@test_run_id

		UPDATE TestRuns
		SET EndAt = @DE
		WHERE TestRunId=@test_run_id
		FETCH NEXT FROM testsCursor INTO @test_id, @test_name
	END
	CLOSE testsCursor
	DEALLOCATE testsCursor
END

EXECUTE SP_test_run

SELECT * FROM TestRuns
SELECT* FROM TestRunTables
SELECT* FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews