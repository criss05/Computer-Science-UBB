#include "RepoException.h"

const char* FileException::what()
{
	return this->message.c_str();
}

const char* RepoException::what()
{
	return this->message.c_str();
}

const char* DuplicatePetException::what()
{
	return "There already exists a pet with this name and breed.\n";
}

const char* InexistentPetException::what()
{
	return "There is no pet with this name and breed.\n";
}