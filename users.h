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
	void makeTransaction(unsigned int sender, unsigned int receiver, double coins);
	void printUsers() const;
	void writeUsersToBinaryFile() const;
	void removeUser(unsigned int idUserToRemove);
	int getUserIndex(unsigned int idToFind) const;
	double getUserCoins(unsigned int userId) const;
};

size_t getSize(std::ifstream& file);
//unsigned int getUniqueId(unsigned int& id);
