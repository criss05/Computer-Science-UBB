#include "UI.h"
#include "RepoException.h"
#include <iostream>
using namespace std;


UI::UI(Service service) {
	this->service = service;
}

void UI::PrintMenu(){
	cout << "\n---Keep calm and adopt a pet!---\n";
	cout << "\n1. Administrator Mode.\n"
		"2. User Mode.\n"
		"3. Exit program.\n";
}

void UI::PrintAdminMenu(){
	cout << "\n---Administrator Mode---\n";
	cout << "\n1. Add a new dog.\n"
		"2. Delete a dog.\n"
		"3. Update the information of a dog.\n"
		"4. See all the dogs.\n"
		"5. Exit Administrator mode.";
}

void UI::PrintUserMenu(){
	cout << "\n---User Mode---\n";
	cout << "\n1. See the dogs one by one.\n"
		"2. See all the dogs of a given breed.\n"
		"3. See the adoption list.\n"
		"4. Open the adoption list.\n"
		"5. Exit Administrator mode.";
}

void UI::PrintAdoptMenu(){
	cout << "\n1. Adopt the dog.\n"
		"2. Next dog.\n"
		"3. See the picture.\n"
		"4.Exit.\n";
}

int UI::ValidateNumber(const std::string& string) {
	return stoi(string);
}

void UI::AddDog(){
	string age_str;
	string name, breed, photograph;

	cout << "\nPLease give the dog's breed: ";
	getline(cin, breed);

	cout << "\nPLease give the dog's name: ";
	getline(cin, name);

	cout << "\nPLease give the dog's age: ";
	getline(cin, age_str);
	int age = this->ValidateNumber(age_str);
	if (age == 0) {
		cout << "Invalid age!\n";
		return;
	}

	cout << "\nPLease give the dog's photograph: ";
	getline(cin, photograph);

	this->service.AddPet(breed, name, age, photograph);
}

void UI::DeleteDog(){
	string name, breed;

	cout << "\nPLease give the dog's breed: ";
	getline(cin, breed);

	cout << "\nPLease give the dog's name: ";
	getline(cin, name);

	this->service.DeletePet(breed, name);
}

void UI::UpdateDog(){
	string age_str;
	string name, breed, new_photograph;

	cout << "\nPLease give the dog's breed: ";
	getline(cin, breed);

	cout << "\nPLease give the dog's name: ";
	getline(cin, name);

	cout << "\nPLease give the dog's new age: ";
	getline(cin, age_str);
	int new_age = this->ValidateNumber(age_str);
	if (new_age == 0) {
		cout << "Invalid age!\n";
		return;
	}

	cout << "\nPLease give the dog's new photograph: ";
	getline(cin, new_photograph);
	this->service.UpdatePet(breed, name, new_age, new_photograph);
}

void UI::PrintAllDogs(){
	vector<Pet> pets = this->service.GetAllPets();
	for (auto pet : pets){
		cout << pet;
	}
}

void UI::PrintDogsOneByOne(){
	vector<Pet> pets = this->service.GetAllPets();
	auto it = pets.begin();
	while(!pets.empty()) {
		cout << *it;
		this->PrintAdoptMenu();
		string adopt_option_str;
		cout << "\nPlease choose an option: ";
		getline(cin, adopt_option_str);
		int adopt_option = 0;
		adopt_option = this->ValidateNumber(adopt_option_str);
		switch (adopt_option) {
		case 0: {
			cout << "Invalid input!";
			break;
		}
		case 1: {
			this->service.AdoptPet(*it);
			this->service.DeletePet((*it).GetBreed(), (*it).GetName());
			it = pets.erase(it);
			break;
		}
		case 2: {
			it++;
			break;
		}
		case 3: {
			system(string("start " + (*it).GetPhotograph()).c_str());
			break;
		}
		case 4: {
			return;
		}
		default: {
			cout << "Invalid input!";
			break;
		}
		}
		if (it == pets.end())
			it = pets.begin();
	}
}

void UI::PrintYoungDogsWithGivenBreed(){
	string age_str;
	string breed;
	cout << "\nPlease give the dog's breed: ";
	getline(cin, breed);

	cout << "\nPlease give the dog's age: ";
	getline(cin, age_str);
	int age = this->ValidateNumber(age_str);
	if (age == 0) {
		cout << "Invalid age!\n";
		return;
	}

	vector<Pet> pets = this->service.GetYoungDogsOfGivenBreed(breed, age);
	if (pets.empty()) {
		cout << "No pet found!";
		return;
	}
	auto it = pets.begin();
	while (!pets.empty()) {
		cout << *it;
		this->PrintAdoptMenu();
		string adopt_option_str;
		cout << "\nPlease choose an option: ";
		getline(cin, adopt_option_str);
		int adopt_option = 0;
		adopt_option = this->ValidateNumber(adopt_option_str);
		switch(adopt_option){
		case 0: {
			cout << "Invalid input!\n";
			break;
		}
		case 1: {
			this->service.AdoptPet(*it);
			this->service.DeletePet((*it).GetBreed(), (*it).GetName());
			it = pets.erase(it);
			break;
		}
		case 2: {
			it++;
			break;
			}
		case 3: {
			system(string("start " + (*it).GetPhotograph()).c_str());
			break;
		}
		case 4: {
			return;
		}
		default: {
			cout << "Invalid input!";
			break;
		}
		}
		if (it == pets.end())
			it = pets.begin();
	}
}

void UI::PrintAdoptionList(){
	vector<Pet> pets = this->service.GetPetsFromAdoptionList();
	string str;
	for (auto pet : pets ) {
		cout << pet;
	}
}

void UI::OpenAdoptionList(){
	this->service.OpenAdoptionList();
}


void UI::GeneratePets(){
	/*this->service.AddPet("Labrador Retriever", "Lara", 1, "https://images.saymedia-content.com/.image/ar_4:3%2Cc_fill%2Ccs_srgb%2Cfl_progressive%2Cq_auto:eco%2Cw_1200/MjAxMjg4MjkxNjI5MTQ3Njc1/labrador-retriever-guide.jpg");
	this->service.AddPet("German Shepherd", "Rex", 5, "https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/German_Shepherd_-_DSC_0346_%2810096362833%29.jpg/220px-German_Shepherd_-_DSC_0346_%2810096362833%29.jpg");
	this->service.AddPet("Labrador Retriever", "Max", 3, "https://mediacdn.libertatea.ro/unsafe/632x421/smart/filters:format(webp):contrast(8):quality(75)/https://static4.libertatea.ro/wp-content/uploads/2020/09/golden-retriever-cat-de-usor-se-dreseaza-si-ce-personalitate-are-cel-mai-indragit-caine.jpg");
	this->service.AddPet("Beagle", "Bella", 2, "https://www.zooplus.ro/ghid/wp-content/uploads/2021/07/despre-beagle-1024x682.webp");
	this->service.AddPet("Labrador Retriever", "Luna", 4, "https://images.saymedia-content.com/.image/ar_4:3%2Cc_fill%2Ccs_srgb%2Cfl_progressive%2Cq_auto:eco%2Cw_1200/MjAxMjg4MjkxNjI5MTQ3Njc1/labrador-retriever-guide.jpg");
	this->service.AddPet("Bulldog", "Daisy", 6, "https://cdn.britannica.com/08/234208-050-C9A21C4C/English-bulldog-dog.jpg");
	this->service.AddPet("Doberman", "Cooper", 7, "https://images.saymedia-content.com/.image/ar_4:3%2Cc_fill%2Ccs_srgb%2Cfl_progressive%2Cq_auto:eco%2Cw_1200/MjAxMjg4MjkxNjI5MTQ3Njc1/labrador-retriever-guide.jpg");
	this->service.AddPet("Siberian Husky", "Lola", 8, "https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
	this->service.AddPet("Doberman", "Lucy", 9, "https://images.saymedia-content.com/.image/t_share/MjAwMzg3MjgzOTk0NjE3MjA4/doberman-pinscher-guide.jpg");
	this->service.AddPet("Boxer", "Charlie", 10, "https://post.bark.co/wp-content/uploads/2022/05/iStock-1257560195-1024x768.jpg");*/
	this->service.ReadFromFileService();
}

void UI::StartUI(){
	this->GeneratePets();
	while (true) {
			this->PrintMenu();
			string option_str;
			cout << "\nPlease choose an option: ";
			getline(cin, option_str);
			int option = 0;
			option = this->ValidateNumber(option_str);
			switch (option) {
			case 0: {
				cout << "Invalid option!\n";
				break;
			}
			case 1: {
				bool back_menu = false;
				while (!back_menu) {
					try {
						this->PrintAdminMenu();
						string admin_option_str;
						cout << "\nPlease choose an option: ";
						getline(cin, admin_option_str);
						int admin_option = 0;
						admin_option = this->ValidateNumber(admin_option_str);
						switch (admin_option) {
						case 0: {
							cout << "Invalid input!";
							break;
						}
						case 1: {
							this->AddDog();
							break;
						}
						case 2: {
							this->DeleteDog();
							break;
						}
						case 3: {
							this->UpdateDog();
							break;
						}
						case 4: {
							this->PrintAllDogs();
							break;
						}
						case 5: {
							cout << "Exiting Administrator Mode...\n";
							back_menu = true;
							break;
						}
						default: {
							cout << "Invalid input!\n";
							break;
						}
						}
					}
					catch (RepoException& error) {
						cout << error.what() << "\n";
					}
					catch (FileException& error) {
						cout << error.what() << "\n";
					}
					catch (PetException& error) {
						for (auto e : error.getError())
							cout << e;
					}
				}
				break;

			}
			case 2: {
				bool back_menu = false;
				while (!back_menu) {
					try {
						this->PrintUserMenu();
						string user_option_str;
						cout << "\nPlease choose an option: ";
						getline(cin, user_option_str);
						int user_option = 0;
						user_option = this->ValidateNumber(user_option_str);
						switch (user_option) {
						case 0: {
							cout << "Invalid input!";
							break;
						}
						case 1: {
							this->PrintDogsOneByOne();
							break;
						}
						case 2: {
							this->PrintYoungDogsWithGivenBreed();
							break;
						}
						case 3: {
							this->PrintAdoptionList();
							break;
						}
						case 4: {
							this->OpenAdoptionList();
							break;
						}
						case 5: {
							cout << "Exiting User Mode...\n";
							back_menu = true;
							break;
						}
						default: {
							cout << "Invalid input!\n";
							break;
						}
						}
					}
					catch (RepoException& error) {
						cout << error.what() << "\n";
					}
					catch (FileException& error) {
						cout << error.what() << "\n";
					}
					catch (PetException& error) {
						for (auto e : error.getError())
							cout << e;
					}
				}
				break;
			}
			case 3: {
				cout << "Exiting...";
				return;
			}
			default: {
				cout << "Invalid input!\n";
				break;
			}
			}
	}
}
