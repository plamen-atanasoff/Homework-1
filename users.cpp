#include "users.h"

const unsigned int OOP_COINS_PER_LEV = 420;
const char* USERS_FILE_NAME = "users.dat";
const char* SYSTEM_USER_NAME = "Sys_User";
const unsigned int SYSTEM_USER_ID = 0;
const unsigned int USER_NAME_LEN = 128;

int UsersCollection::getUserId(const char* name) const
{
	for (int i = 0; i < usersCount; ++i)
	{
		if (strcmp(name, users[i].name) == 0)
		{
			return users[i].id;
		}
	}

	return -1;
}

int UsersCollection::getUserIndex(const char* name) const
{
	// returns -1 if there is no such user
	for (int i = 0; i < usersCount; ++i)
	{
		if (strcmp(name, users[i].name) == 0)
			return i;
	}

	return -1;
}

void UsersCollection::removeUser(const char* name)
{
	int userIndex = getUserIndex(name);

	User* temp = new User[--usersCount];
	for (int i = 0; i < userIndex; i++)
	{
		temp[i] = users[i];
	}
	for (int i = userIndex; i < usersCount; i++)
	{
		temp[i] = users[i + 1];
	}

	delete[] users;
	users = temp;
}

bool UsersCollection::userNameIsUnique(const char* userName)
{
	for (int i = 0; i < usersCount; ++i)
	{
		if (strcmp(userName, users[i].name) == 0)
			return false;
	}
	return true;
}

void UsersCollection::createUser(const char* userName)
{
	User* temp = new User[++usersCount];

	for (int i = 0; i < usersCount - 1; ++i)
	{
		temp[i] = users[i];
	}

	if (strcmp(userName, "Sys_User") == 0)
		temp[usersCount - 1].id = SYSTEM_USER_ID;
	else
		temp[usersCount - 1].id = ++idCounter;

	strcpy_s(temp[usersCount - 1].name, strlen(userName) + 1, userName);

	delete[] users;
	users = temp;
}

void UsersCollection::printUsers() const
{
	std::cout << "Total users: " << usersCount << std::endl;

	for (int i = 0; i < usersCount; ++i)
	{
		std::cout << users[i].id << " " << users[i].name << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void UsersCollection::readFileUsers()
{
	std::ifstream file(USERS_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	size_t fileSize = getSize(file);
	if (fileSize == 0)
	{
		std::cout << "File is empty!" << std::endl;
		return;
	}

	this->usersCount = fileSize / sizeof(User);
	this->users = new User[usersCount];
	file.read((char*)users, usersCount * sizeof(User));

	file.close();
}

void UsersCollection::writeUsersToBinaryFile() const
{
	std::ofstream file(USERS_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	file.write((const char*)users, usersCount * sizeof(User));

	file.close();
}

void UsersCollection::writeUserToBinaryFile() const
{
	std::ofstream file(USERS_FILE_NAME, std::ios::binary | std::ios::app);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	file.write((const char*)&users[usersCount - 1], sizeof(User));

	file.close();
}