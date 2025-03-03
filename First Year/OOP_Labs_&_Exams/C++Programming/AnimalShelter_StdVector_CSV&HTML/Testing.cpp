#include "Testing.h"
#include "Pet.h"
#include "ClientRepository.h"
#include "EmployeesRepository.h"
#include "Service.h"
#include <assert.h>

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
	Pet pet2{ "breed2", "name2", 1, "link1" };
	assert(pet1 == pet2);
}

void Test::TestClientRepository(){
	ClientRepository repo;
	repo.AdoptPet(Pet{ "breed1", "name1", 1, "link1" });
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
	ClientRepository* client_repo = new ClientRepository();
	EmployeesRepository* employees_repo = new EmployeesRepository();
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

	vector<Pet> pets = service.GetYoungDogsOfGivenBreed("breed1", 3);
	assert(pets.size() == 1);
	assert(pets[0].GetAge() == 2);
}

void Test::TestAll(){
	TestPet();
	TestClientRepository();
	TestEmployeesRepository();
	TestService();
}