#pragma once

#include <iostream>
#include <fstream>

struct User {
	unsigned id;
	char name[128];
};

struct UsersCollection
{
	User* users;
	unsigned int usersCount;
	unsigned int idCounter;

	UsersCollection()
	{
		users = nullptr;
		usersCount = 0;
		idCounter = 0;
	}

	~UsersCollection()
	{
		delete[] users;
	}

	void readMetaDataFile();
	void writeMetaDataFile();
	void readFileUsers();
	void createUser(const char* userName, double investmentSum);
	void printUsers() const;
	void writeUsersToBinaryFile() const;
	void removeUser(unsigned int idUserToRemove);
	// is it okay to be here and in tBlocksCollection aswell
	int getUserIndex(unsigned int idToFind) const;
};

size_t getSize(std::ifstream& file);
//unsigned int getUniqueId(unsigned int& id);
