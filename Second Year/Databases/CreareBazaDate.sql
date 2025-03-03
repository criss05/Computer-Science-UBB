CREATE DATABASE Navomodelism_Course
GO

USE Navomodelism_Course

CREATE TABLE Materiale(
	Nume_Material CHAR(50) PRIMARY KEY,
	Cantitate INT)

CREATE TABLE Programe(
	ID_Program SMALLINT PRIMARY KEY,
	Nume_Program CHAR(70) UNIQUE)

CREATE TABLE Barci(
	Nume_Barca CHAR(50) PRIMARY KEY,
	Nume_Material CHAR(50) FOREIGN KEY REFERENCES Materiale(Nume_Material),
	Id_Program SMALLINT FOREIGN KEY REFERENCES Programe(ID_Program))
	
CREATE TABLE Masini(
	Nume_Masina CHAR(50) PRIMARY KEY,
	Nume_Material CHAR(50) FOREIGN KEY REFERENCES Materiale(Nume_Material),
	Id_Program SMALLINT FOREIGN KEY REFERENCES Programe(ID_Program))

CREATE TABLE Avioane(
	Nume_Avioane CHAR(50) PRIMARY KEY,
	Nume_Material CHAR(50) FOREIGN KEY REFERENCES Materiale(Nume_Material),
	Id_Program SMALLINT FOREIGN KEY REFERENCES Programe(ID_Program))

CREATE TABLE Profesori(
	ID_Profesor INT PRIMARY KEY CHECK(LEN(ID_Profesor)=4),
	Nume CHAR(20) NOT NULL,
	Prenume CHAR(20) NOT NULL)

CREATE TABLE Grupe(
	ID_Grupa SMALLINT PRIMARY KEY,
	Nivel INT CHECK (Nivel<=4) DEFAULT 0,
	Numar_Elevi INT CHECK (Numar_Elevi<=15),
	Id_Profesor INT FOREIGN KEY REFERENCES Profesori(ID_Profesor),
	Id_Program SMALLINT FOREIGN KEY REFERENCES Programe(ID_Program))

CREATE TABLE Concursuri(
	Nume_Concurs CHAR(70),
	Data_Stabilita DATE,
	Id_Profesor INT FOREIGN KEY REFERENCES Profesori(ID_Profesor),
	Locatie CHAR(200),
	PRIMARY KEY(Nume_Concurs, Data_Stabilita))

CREATE TABLE Grupe_Concursuri(
	ID_Grupa SMALLINT FOREIGN KEY REFERENCES Grupe(ID_Grupa),
	Nume_Concurs Char(70),
	Data_Stabilita DATE,
	 FOREIGN KEY (Nume_Concurs, Data_Stabilita) REFERENCES Concursuri(Nume_Concurs, Data_Stabilita),
	 Primary Key(ID_Grupa, Nume_Concurs, Data_Stabilita)
	 )

CREATE TABLE Elevi(
	CNP_Elev VARCHAR(13) PRIMARY KEY CHECK(LEN(CNP_Elev)=13),
	Nume CHAR(20),
	Prenume CHAR(20),
	Grupa SMALLINT FOREIGN KEY REFERENCES Grupe(ID_Grupa))

CREATE TABLE Parinti(
	CNP_Parinte  VARCHAR(13) PRIMARY KEY CHECK(LEN(CNP_Parinte)=13),
	Nume CHAR(20),
	Prenume CHAR(20),
	CNP_Elev VARCHAR(13) FOREIGN KEY REFERENCES Elevi(CNP_Elev),
	Contact VARCHAR(10) CHECK (LEN(Contact)=10))

DROP TABLE Parinti


