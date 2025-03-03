#pragma once
#include <exception>
#include <string>

class FileException : public std::exception {
protected:
	std::string message;
public:
	FileException(const std::string& message) { this->message = message; }
	virtual const char* what();
};

class RepoException : public std::exception {
protected:
	std::string message;
public:
	RepoException() : exception{}, message{ "" } {}
	RepoException(const std::string& message) : message{ message } {}
	virtual ~RepoException(){}
	virtual const char* what();
};

class DuplicatePetException : public RepoException {
public:
	const char* what();
};

class InexistentPetException : public RepoException {
public:
	const char* what();
};
