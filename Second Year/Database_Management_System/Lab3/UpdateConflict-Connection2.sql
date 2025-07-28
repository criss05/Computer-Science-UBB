USE Navomodelism_Course

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRANSACTION

	DECLARE @Cantitate INT
	SELECT @Cantitate = Cantitate FROM Materiale WHERE Nume_Material='Lemn'

	UPDATE Materiale
	SET Cantitate=@Cantitate + 5
	WHERE Nume_Material='Lemn'

	COMMIT;