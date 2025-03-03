use Navomodelism_Course

--Insert into Materiale 3 records
INSERT INTO Materiale VALUES ('Lemn', 20), ('Plastic', 30), ('Fibra de sticla', 10)
INSERT INTO Materiale VALUES ('Hartie', 100), ('Aluminiu', 30)

--Insert into Programe 4 records
INSERT INTO Programe VALUES(1,'Constructie barci'), (2, 'Constructie avioane'), (3, 'Istoria barcilor'), (4, 'Noduri marinaresti')
INSERT INTO Programe VALUES(5, 'Istoria avioanelor'), (6, 'Constructie masini'), (7, 'Curse de masini'), (8, 'Instructaj avioane')

--Insert into Barci 1 record that violates the referential integrity and 3 records that are good
INSERT INTO Barci VALUES ('Garda de coasta', 'fier', 1)
INSERT INTO Barci VALUES ('Regina Maria', 'Lemn', 1), ('Bismark', 'Fibra de sticla', 1), ('Garda de coasta', 'PLastic', 1)

--Insert into Materiale other records
INSERT INTO Materiale VALUES ('Cauciuc', NULL), ('Tabla', NULL)
INSERT INTO Materiale VALUES ('Fier', 5), ('Metal', 3)

--Insert into Profesori 3 records
INSERT INTO Profesori VALUES (1000,'Matei', 'ALex'), (1001, 'Pop', 'Cristinel'), (1002, 'Marcu', 'Vasile')

--Insert into Grupe folosind toate valorile, dar si valoarea default
INSERT INTO Grupe VALUES (1, 1, 10, 1001, 1), (2, 1, 13, 1001, 1), (3, 2, 5, 1001, 3)
INSERT INTO Grupe(ID_Grupa, Numar_Elevi, Id_Profesor, Id_Program) VALUES (5, 3, 1002, 3),(4, 4, 1002, 3)
INSERT INTO Grupe VALUES (6, 2, 15, 1001, 2), (7, 4, 10, 1000, 4)
INSERT INTO Grupe VALUES (8, 2, 15, 1001, 2), (10, 4, 10, 1002, 4)

--Insert into Elevi 4 records
INSERT INTO	Elevi VALUES('6020304314005', 'Marcu', 'Alexandra', 1), ('5040302314006', 'Pop', 'Matei', 1), ('6020118314002', 'Labo','Margareta', 2),('6101010314009', 'Criste', 'Valentina', 4)


--Insert into Concursuri 3 records
INSERT INTO Concursuri VALUES ('Cupa Ramnicului', '2019-12-04' , 1001, 'Ramnicul Valcea')
INSERT INTO Concursuri VALUES ('Toate panzele sus', '2023-08-16', 1002, 'Constanta'), ('Cupa Crisius', '2019-09-21', 1001, 'Chisineu Cris')
INSERT INTO Concursuri VALUES ('Cupa Constantei', '2025-10-12', 1000, 'Constanta'), ('Cupa Iasului', '2025-09-08', 1000, 'Iasi'), ('Campionatul Mondial de Ma?ini', '2025-12-09', 1000, 'Bucuresti')
INSERT INTO Concursuri VALUES ('Toate panzele sus', '2020-08-16', 1002, 'Constanta'), ('Cupa Crisius', '2019-09-21', 1001, 'Chisineu Cris'), ('Cupa Ramnicului', '2019-12-04' , 1001, 'Ramnicul Valcea')

SELECT * FROM Concursuri

--Insert into Parinti some data
INSERT INTO Parinti VALUES ('1020304314005', 'Marcu', 'Andrei', '6020304314005', '0770345918'), ('2010203314003', 'Pop', 'Andrada', '5040302314006', '0789657897'), ('1090802314002', 'Pop', 'Mihai','5040302314006', '0712345678'), ('2090807312343', 'Criste', 'Bianca', '6020118314002', '0798090808') 

--Insert into Grupe Concursuri some data
INSERT INTO Grupe_Concursuri VALUES(1, 'Cupa Constantei', '2025-10-12'), (2, 'Cupa Iasului', '2025-09-08'), (1, 'Toate Panzele sus', '2023-08-16'), (3, 'Cupa Constantei', '2025-10-12'), (1, 'Cupa Iasului', '2025-09-08')
INSERT INTO Grupe_Concursuri VALUES (6, 'Toate panzele sus', '2020-08-16'), (7, 'Cupa Crisius', '2019-09-21')

SELECT * FROM Grupe
SELECT * FROM Concursuri


INSERT INTO Avioane VALUES ('Boeming', 'Lemn', 2), ('Barracuda', 'Fibra de sticla', 2), ('Iakovlev', 'Aluminiu', 5), ('Firefly', 'Hartie', 8), ('Swordfish', 'Lemn', 8)
INSERT INTO Masini VALUES ('Blue Bird', 'Tabla', 7), ('Sparrow', 'Tabla', 6), ('McQueen', 'Plastic', 6), ('Bumblebee', 'Lemn', 6), ('Buggy', 'Plastic', 7) 

SELECT * FROM Materiale
SELECT * FROM Programe


--Update ID_profesor din Grupe cu un alt Id daca profesorul este 1001 si nivelul grupei este 2
UPDATE Grupe SET Id_Profesor=1000 WHERE Id_Profesor=1001 And Nivel=2

--Update Cantitate din Materiale daca cantitatea este <=15 sau NULL
UPDATE Materiale SET Cantitate=25 WHERE Cantitate<=15
UPDATE Materiale SET Cantitate=15 WHERE Cantitate IS NULL

--Update Anul de la Data_Stabilita daca Anul Curent este 2019
UPDATE Concursuri 
SET Data_Stabilita=DATEFROMPARTS(2024, MONTH(Data_Stabilita), DAY(Data_Stabilita))
WHERE YEAR(Data_Stabilita)=2019 

--Vedem toate datele din tabelele prezentate
SELECT * FROM Programe
SELECT * FROM Profesori
SELECT * FROM Barci
SELECT * FROM Materiale
SELECT * FROM Grupe
SELECT * FROM Concursuri
SELECT * FROM Elevi
SELECT * FROM Parinti

--Delete din Elevi unde grupa este 4 sau 5
DELETE FROM Elevi WHERE Grupa IN(4,5)

--Delete idn Grupe unde nivelul este diferit de 0 sau (in al doilea) daca numarul de elevi este null
DELETE FROM Grupe WHERE NOT Nivel!=0
DELETE FROM Grupe WHERE Numar_Elevi IS NULL
