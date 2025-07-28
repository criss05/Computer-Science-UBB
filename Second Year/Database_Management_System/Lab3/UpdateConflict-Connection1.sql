ALTER DATABASE Navomodelism_Course SET ALLOW_SNAPSHOT_ISOLATION ON;

use Navomodelism_Course

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRANSACTION

	DECLARE @Cantitate INT;
	SELECT @Cantitate = Cantitate FROM Materiale WHERE Nume_Material = 'Lemn'

	WAITFOR DELAY '00:00:10'

	UPDATE Materiale
	SET Cantitate = @Cantitate + 1
	WHERE Nume_Material = 'Lemn';
	
	COMMIT;

SELECT * FROM Materiale
