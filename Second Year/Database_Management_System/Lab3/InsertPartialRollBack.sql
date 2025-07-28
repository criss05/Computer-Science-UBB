use Navomodelism_Course

GO

CREATE OR ALTER PROCEDURE InsertGrupePartialRollBack
	@ID_Grupa SMALLINT,
	@Nivel INT,
	@Numar_Elevi INT,
	@Id_Profesor_Grupa INT,
	@Id_Program SMALLINT,

	@Nume_Concurs CHAR(70),
	@Data_Stabilita DATE,
	@Id_Profesor_Concurs INT,
	@Locatie CHAR(200)
AS
BEGIN
	SET NOCOUNT ON;

	--TRY TO INSERT INTO Grupe
	BEGIN TRY
		BEGIN TRANSACTION;
			INSERT INTO Grupe(ID_Grupa, Nivel, Numar_Elevi, Id_Profesor, Id_Program)
			VALUES (@ID_Grupa, @Nivel, @Numar_Elevi, @Id_Profesor_Grupa, @Id_Program)
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT 'Error inserting into Grupe: ' + ERROR_MESSAGE();
		RETURN;
	END CATCH;

	--TRY TO INSERT INTO Concursuri
	BEGIN TRY
		BEGIN TRANSACTION;
			INSERT INTO Concursuri (Nume_Concurs, Data_Stabilita, Id_Profesor, Locatie)
			VALUES (@Nume_Concurs, @Data_Stabilita, @Id_Profesor_Concurs, @Locatie)
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT 'Error inserting into Concursuri: ' + ERROR_MESSAGE();
		RETURN;
	END CATCH;

	--TRY TO INSERT INTO Grupe_Concursuri
	BEGIN TRY
		BEGIN TRANSACTION;
			INSERT INTO Grupe_Concursuri (ID_Grupa, Nume_Concurs, Data_Stabilita)
			VALUES (@ID_Grupa, @Nume_Concurs, @Data_Stabilita)
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT 'Error inserting into Grupe-Concursuri: ' + ERROR_MESSAGE();
		RETURN;
	END CATCH;
END;


sELECT * FROM Grupe
SELECT * FROM Concursuri
SELECT * FROM Grupe_Concursuri

Exec InsertGrupePartialRollBack 14, 2, 10, 1002, 3, 'Tabara2', '2026-03-05', 1000, 'Brasov'
Exec InsertGrupePartialRollBack 15, 2, 10, 1002, 3, 'Tabara2', '2026-03-05', 1000, 'Brasov'