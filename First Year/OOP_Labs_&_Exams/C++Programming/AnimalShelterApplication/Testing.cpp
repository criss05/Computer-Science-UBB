#include "Testing.h"
#include "DynamicVector.h"
#include "Pet.h"
#include "ClientRepository.h"
#include "EmployeesRepository.h"
#include "Service.h"
#include <assert.h>


void Test::TestDynamicVector(){
	DynamicVector<int> vector1{ 2 };
	vector1.AddElement(10);
	vector1.AddElement(20);
	assert(vector1.GetSize() == 2);
	
	DynamicVector<int> vector2{ vector1 };
	assert(vector2.GetSize() == 2);

	DynamicVector<int> vector3;
	vector3.AddElement(100);
	vector3 = vector1;
	assert(vector3[0] == 10);

	assert(vector1[1] == 20);
	vector1[1] = 25;
	assert(vector1[1] == 25);
	vector1.AddElement(30);
	assert(vector1.GetSize() == 3);

	assert(vector3.GetElements()[0] == 10);

	vector3.DeleteElement(20);
	assert(vector3.GetSize() == 1);

	vector1 = vector1;
	assert(vector1[0] == 10);
}

void Test::TestPet(){
	Pet pet1{ "breed1", "name1", 1, "link1" };
	assert(pet1.GetBreed() == "breed1");
	assert(pet1.GetName() == "name1");
	assert(pet1.GetAge() == 1);
	assert(pet1.GetPhotograph() == "link1");

	pet1.SetAge(2);
	pet1.SetBreed("breed2");
	pet1.SetName("name2");
	pet1.SetPhotograph("link2");
	assert(pet1.GetAge() == 2);
	assert(pet1.GetBreed() == "breed2");
	assert(pet1.GetName() == "name2");
	assert(pet1.GetPhotograph() == "link2");
	std::string str;
	pet1.PrintPet(str);
	Pet pet2{ "breed2", "name2", 1, "link1" };
	assert(pet1 == pet2);
}

void Test::TestClientRepository(){
	ClientRepository repo;
	repo.Adoptpet(Pet{ "breed1", "name1", 1, "link1" });
	assert(repo.GetAdoptionListSize() == 1);
	assert(repo.GetAdoptionList()[0].GetBreed() == "breed1");
}

void Test::TestEmployeesRepository(){
	EmployeesRepository repo;
	repo.AddPetToRepo(Pet{ "breed1", "name1", 1, "link1" });
	assert(repo.GetPetsNumber() == 1);
	assert(repo.GetPetsFromRepo()[0].GetBreed() == "breed1");

	repo.DeletePetFromRepo(Pet{ "breed1", "name1", 1, "link1" });
	assert(repo.GetPetsNumber() == 0);

	repo.AddPetToRepo(Pet{ "breed1", "name1", 1, "link1" });
	assert(repo.GetPetFromRepo("name1", "breed1").GetAge() == 1);

	try {
		repo.AddPetToRepo(Pet{ "breed1", "name1", 1, "link1" });
	}
	catch (std::exception) {
		assert(true);
	}
	try {
		repo.DeletePetFromRepo(Pet{ "breed5", "name5", 5, "link5" });
	}
	catch (std::exception) {
		assert(true);
	}

	try {
		repo.GetPetFromRepo("breed5", "name5");
	}
	catch (std::exception) {
		assert(true);
	}
}

void Test::TestService(){
	ClientRepository client_repo;
	EmployeesRepository employees_repo;
	Service service{ client_repo, employees_repo };

	service.AddPet("breed1", "name1", 1, "link1");
	assert(service.GetPetSize() == 1);
	assert(service.GetAllPets()[0].GetBreed() == "breed1");

	service.DeletePet("breed1", "name1");
	assert(service.GetPetSize() == 0);

	service.AddPet("breed1", "name1", 1, "link1");
	service.UpdatePet("breed1", "name1", 2, "link2");
	assert(service.GetAllPets()[0].GetAge() == 2);
	assert(service.GetAllPets()[0].GetPhotograph() == "link2");

	service.AdoptPet(Pet{ "breed1", "name1", 1, "link1" });
	assert(service.GetSizeOfAdoptionList() == 1);
	assert(service.GetPetsFromAdoptionList()[0].GetBreed() == "breed1");

	int number_elements;
	Pet* pets = service.GetYoungDogsOfGivenBreed("breed1", 3, number_elements);
	assert(number_elements == 1);
	assert(pets[0].GetAge() == 2);
	delete[] pets;
}

void Test::TestAll(){
	TestDynamicVector();
	TestPet();
	TestClientRepository();
	TestEmployeesRepository();
	TestService();
}