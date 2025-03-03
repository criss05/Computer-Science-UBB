USE Navomodelism_Course

--Select all records from the following tables
SELECT * FROM Barci
SELECT * FROM Materiale
SELECT * FROM Elevi
SELECT * FROM Parinti
SELECT * FROM Grupe
SELECT * FROM Profesori
SELECT * FROM Programe
SELECT * FROM Grupe_Concursuri
SELECT * FROM Concursuri

--See all competitions
SELECT DISTINCT C.Nume_Concurs
FROM Concursuri C


--See all Groups that are in competitions
SELECT DISTINCT GC.ID_Grupa
FROM Grupe_Concursuri GC


--See all teachers that are in all groups
SELECT DISTINCT Id_Profesor
FROM Grupe


--A) 2 queries with the union operation
--Show only the groups where Nivel is 1 or the Thearcher has Id 1001
SELECT G.ID_Grupa, G.Numar_Elevi, G.Id_Profesor, Id_Program
FROM Grupe G
WHERE Nivel=1 OR Id_Profesor = 1001

--Show the Concursuri records where The Name starts with Cupa and the Date is in 2025
SELECT * 
FROM Concursuri
WHERE Nume_Concurs LIKE 'Cupa%'
UNION
SELECT * 
FROM Concursuri
WHERE YEAR(Data_Stabilita)=2025


--B) 2 queries with the intersection operation; use INTERSECT and IN;
--See all parents that are women and have a girl
SELECT *
FROM Parinti
WHERE CNP_Parinte LIKE '[2,6]%'
INTERSECT
SELECT * 
FROM Parinti
WHERE CNP_Elev LIKE '6%'

--See TOP 3 latest competitions that are in Bucuresti or Constanta
SELECT TOP 3 *
FROM Concursuri C
WHERE C.Locatie IN('Bucuresti', 'Constanta')
ORDER BY C.Data_Stabilita DESC

--C) 2 queries with the difference operation; use EXCEPT and NOT IN
--See all groups where number of students are less than 15, but do not have 1001 as a teacher
SELECT *--G1.ID_Grupa
FROM Grupe G1
WHERE G1.Numar_Elevi < 15
EXCEPT
SELECT * --G2.ID_grupa
FROM Grupe G2
WHERE G2.Id_Profesor = 1001

--See all groups that does not has as program 1 or 2
SELECT *
FROM Grupe
WHERE Id_Program NOT IN(1,2)


--D) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); 
--one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

--See the parents for all the students in the course 
SELECT *
FROM Elevi E INNER JOIN Parinti P ON
P.CNP_Elev = E.CNP_Elev
ORDER BY E.Nume

--See all boats and the material they are made of, for all programs
SELECT B.Nume_Barca, P.Nume_Program, M.Nume_Material
FROM Programe P LEFT OUTER JOIN Barci B ON B.Id_Program = P.ID_Program
LEFT OUTER JOIN Materiale M ON B.Nume_Material = M.Nume_Material

--See all students, their teachers, but also the groups that has no students 
SELECT E.Nume, E.Prenume, G.ID_Grupa, P.ID_Profesor
FROM Elevi E RIGHT OUTER JOIN Grupe G ON E.Grupa=G.ID_Grupa
RIGHT OUTER JOIN Profesori P ON G.Id_Profesor=P.ID_Profesor


--See all competitions and their data (group that participates, the program in which the group is, the teacher and how many years ago was organized)
SELECT C.Nume_Concurs, G.ID_Grupa, P.Nume_Program, Pr.ID_Profesor, C.Data_Stabilita, YEAR(GETDATE()) - YEAR(C.Data_Stabilita) AS How_Long_Ago
FROM Programe P FULL OUTER JOIN Grupe G ON P.ID_Program = G.Id_Program
FULL OUTER JOIN Profesori Pr ON G.Id_Profesor=Pr.ID_Profesor
INNER JOIN Grupe_Concursuri GC ON GC.ID_Grupa = G.ID_Grupa
FULL OUTER JOIN Concursuri C ON C.Nume_Concurs = GC.Nume_Concurs AND C.Data_Stabilita=GC.Data_Stabilita



--E) 2 queries using the IN operator to introduce a subquery in the WHERE clause; 
--in at least one query, the subquery should include a subquery in its own WHERE clause;

--See all groups that participates in competitions that took place in last 3 years
SELECT *
FROM Grupe
WHERE ID_Grupa IN (SELECT GC.ID_Grupa
				FROM Grupe_Concursuri GC
				WHERE  YEAR(GETDATE())- YEAR(GC.Data_Stabilita) < 3)

--See the competitions in which are used boats
SELECT Nume_Concurs
FROM Grupe_Concursuri
WHERE ID_Grupa IN (SELECT ID_Grupa
				FROM Grupe
				WHERE Id_Program IN (SELECT Id_Program
									FROM Programe
									WHERE Nume_Program Like '%[Bb]arc_%'))

--F) 2 queries using the EXISTS operator to introduce a subquery in the WHERE clause

--See the materials that appear in the cars, but also boats
SELECT M.Nume_Material, M.Cantitate
FROM Materiale M
WHERE EXISTS(SELECT A.Nume_Material
			FROM Avioane A
			WHERE M.Nume_Material=A.Nume_Material AND A.Nume_Material IN (SELECT Nume_Material
																		FROM Barci))

--See the parents that have children in advansed groups
SELECT TOP 3 *
FROM Parinti P
WHERE EXISTS(SELECT CNP_Elev
			FROM Elevi E
			INNER JOIN Grupe G ON G.ID_Grupa = E.Grupa
			WHERE P.CNP_Elev = E.CNP_Elev AND G.Nivel=1)
ORDER BY P.Nume


--G) 2 queries with a subquery in the FROM clause

--See all groups that have more than 10 students
SELECT A.Nume_Program, A.Numar_Elevi
FROM (SELECT P.ID_Program, P.Nume_Program, G.ID_Grupa, G.Numar_Elevi
	FROM Programe P INNER JOIN Grupe G ON P.ID_Program=G.Id_Program
	WHERE G.Numar_Elevi > 10) A

--See all teachers that goes to a competition in 2025
SELECT A.Nume, A.Prenume, A.Nume_Concurs
FROM (SELECT P.ID_Profesor, P.Nume, P.Prenume, C.Data_Stabilita, C.Nume_Concurs
	FROM Profesori P INNER JOIN Concursuri C ON P.ID_Profesor=C.Id_Profesor
	WHERE YEAR(C.Data_Stabilita) = 2025) A


--H) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

--See how many competitons has each group
SELECT G.ID_Grupa, Count(GC.Nume_Concurs) as Concursuri
FROM Grupe G INNER JOIN Grupe_Concursuri GC ON G.ID_Grupa=GC.ID_Grupa
GROUP BY G.ID_Grupa

--See all teachers that have more than 15 students in all groups and the average of students in each group
SELECT P.ID_Profesor, SUM(G.Numar_Elevi) as Numar_Elevi, SUM(G.Numar_Elevi) / COUNT(G.Id_Profesor) AS Medie_Elevi
FROM Grupe G INNER JOIN Profesori P ON P.ID_Profesor=G.Id_Profesor
GROUP BY P.Id_Profesor
HAVING SUM(G.Numar_Elevi)>=15

select* from grupe 
--See all the teachers that participate at a competition with its date bigger than the minimum date after 2023
SELECT P.ID_Profesor, C.Data_Stabilita
FROM Profesori P INNER JOIN Concursuri C ON P.ID_Profesor=C.Id_Profesor
GROUP BY P.ID_Profesor, C.Data_Stabilita
HAVING C.Data_Stabilita >(SELECT MIN(Data_Stabilita) 
								FROM Concursuri
							WHERE YEAR(Data_Stabilita)>2023)


--See all cars that are made from a material that has a quantity smaller than the maximum quantity
SELECT Ma.Nume_Masina, SUM(M.Cantitate) as Cantitate_Material
FROM Materiale M INNER JOIN Masini Ma ON M.Nume_Material=Ma.Nume_Material
GROUP BY Ma.Nume_Masina
HAVING SUM(M.Cantitate)< (SELECT MAX(Cantitate)
						FROM Materiale)


--I)  4 queries using ANY and ALL to introduce a subquery in the WHERE clause;
--rewrite 2 of them with aggregation operators, and the other 2 with [NOT] IN.

--See all groups that have a minimum level
SELECT G.ID_Grupa, G.Nivel 
FROM Grupe G
WHERE G.Nivel < ALL(SELECT G1.Nivel
					FROM Grupe G1
					WHERE G1.Nivel != G.Nivel)

SELECT G.ID_Grupa, G.Nivel 
FROM Grupe G
WHERE G.Nivel < (SELECT MIN(G1.Nivel)
					FROM Grupe G1
					WHERE G1.Nivel != G.Nivel)

--See all materials that have a maximum quantity and the price if the price of every piece is 1.5
SELECT M.Nume_Material, M.Cantitate, M.Cantitate*1.5 AS Pret
FROM Materiale M
WHERE M.Cantitate > ALL(SELECT M1.Cantitate
						FROM Materiale M1
						WHERE M1.Cantitate!=M.Cantitate)


SELECT M.Nume_Material, M.Cantitate
FROM Materiale M
WHERE M.Cantitate > (SELECT MAX(M1.Cantitate)
						FROM Materiale M1
						WHERE M1.Cantitate!=M.Cantitate)

--See all groups that are not going to any competition
SELECT G.ID_Grupa, G.Nivel
FROM Grupe G 
WHERE G.ID_Grupa <> ALL(SELECT GC.ID_Grupa
						FROM Grupe_Concursuri GC)

SELECT G.ID_Grupa, G.Nivel
FROM Grupe G 
WHERE G.ID_Grupa NOT IN(SELECT GC.ID_Grupa
						FROM Grupe_Concursuri GC)

--See all materials used for planes
SELECT A.Nume_Material, A.Nume_Avioane
FROM Avioane A
WHERE A.Nume_Material = ANY(SELECT M.Nume_Material
						FROM Materiale M)

SELECT A.Nume_Material, A.Nume_Avioane
FROM Avioane A
WHERE A.Nume_Material IN (SELECT M.Nume_Material
						FROM Materiale M)