use Navomodelism_Course

GO
CREATE OR ALTER PROCEDURE InsertGrupeConcursuri
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
	BEGIN TRY
		BEGIN TRANSACTION;

			--Insert into grupe
			INSERT INTO Grupe (ID_Grupa, Nivel, Numar_Elevi, Id_Profesor, Id_Program)
			VALUES (@ID_Grupa, @Nivel, @Numar_Elevi, @Id_Profesor_Grupa, @Id_Program)

			--Insert into concursuri
			INSERT INTO Concursuri(Nume_Concurs, Data_Stabilita, Id_Profesor, Locatie)
			VALUES (@Nume_Concurs, @Data_Stabilita, @Id_Profesor_Concurs, @Locatie)

			--insert into grupe_concursuri
			INSERT INTO Grupe_Concursuri (ID_Grupa, Nume_Concurs, Data_Stabilita)
			VALUES (@ID_Grupa, @Nume_Concurs, @Data_Stabilita)

		COMMIT TRANSACTION;
	END TRY
	BEGIN CATCH
		ROLLBACK TRANSACTION;

		DECLARE @Error_message VARCHAR(4000), @Error_severity INT;
		SELECT @Error_message = Error_Message(), @Error_severity = ERROR_SEVERITY();
		RAISERROR(@Error_message, @Error_severity, 1);
	END CATCH
END;

SELECT * FROM Grupe
sELECT * FROM Concursuri
SELECT * FROM Grupe_Concursuri

EXEC InsertGrupeConcursuri 13, 2, 10, 1001, 3,'CAMPIONAT Constanta1', '2025-12-03', 1002, 'Constanta'
EXEC InsertGrupeConcursuri 14, 2, 10, 1001, 3,'CAMPIONAT Constanta1', '2025-12-03', 1002, 'Constanta'
