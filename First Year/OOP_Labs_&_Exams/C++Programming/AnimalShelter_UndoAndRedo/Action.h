#pragma once
#include "EmployeesRepository.h"

class Action {
public:
	virtual void ExecuteUndo() = 0;
	virtual void ExecuteRedo() = 0;
};

class ActionAdd : public Action {
private:
	EmployeesRepositoryBase* repo;
	Pet added_pet;

public:
	ActionAdd(EmployeesRepositoryBase* repo, const Pet& pet) : repo(repo), added_pet(pet) {}

	void ExecuteUndo() override {
		repo->DeletePetFromRepo(added_pet);
	}
	void ExecuteRedo() override {
		repo->AddPetToRepo(added_pet);
	}
};

class ActionDelete : public Action {
private:
	EmployeesRepositoryBase* repo;
	Pet deleted_pet;

public:
	ActionDelete(EmployeesRepositoryBase* repo, const Pet& pet): repo(repo), deleted_pet(pet){}

	void ExecuteUndo() override {
		repo->AddPetToRepo(deleted_pet);
	}
	void ExecuteRedo() override {
		repo->DeletePetFromRepo(deleted_pet);
	}
};

class ActionUpdate : public Action {
private:
	EmployeesRepositoryBase* repo;
	Pet new_pet;
	Pet old_pet;

public:
	ActionUpdate(EmployeesRepositoryBase* repo, const Pet& new_pet, const Pet& old_pet) : repo(repo), new_pet(new_pet), old_pet(old_pet){}

	void ExecuteUndo() override {
		repo->DeletePetFromRepo(new_pet);
		repo->AddPetToRepo(old_pet);
	}

	void ExecuteRedo() override {
		repo->DeletePetFromRepo(old_pet);
		repo->AddPetToRepo(new_pet);
	}
};