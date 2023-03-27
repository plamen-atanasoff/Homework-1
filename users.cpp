// check if user id doesn't exist
// check if Id is unique

#include "users.h"

const unsigned int OOP_COINS_PER_LEV = 420;
const char* META_DATA_FILE_NAME = "metaData.dat";
const char* USERS_FILE_NAME = "users.dat";
const char* SYSTEM_USER_NAME = "Sys_User";
const unsigned int SYSTEM_USER_ID = 0;
const unsigned int USER_NAME_LEN = 128;

// file consist of unsigned idCounter
void UsersCollection::readMetaDataFile()
{
	std::ifstream file(META_DATA_FILE_NAME, std::ios::binary);
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

	file.read((char*)&idCounter, sizeof(idCounter));

	file.close();
}

void UsersCollection::writeMetaDataFile()
{
	std::ofstream file(META_DATA_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	file.write((const char*)&idCounter, sizeof(idCounter));

	file.close();
}

void UsersCollection::readFileUsers()
{
	std::ifstream file(USERS_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		createUser(SYSTEM_USER_NAME, 0);
		return;
	}
	
	size_t fileSize = getSize(file);
	if (fileSize == 0)
	{
		std::cout << "File is empty!" << std::endl;
		createUser(SYSTEM_USER_NAME, 0);
		return;
	}
	
	this->usersCount = fileSize / sizeof(User);
	this->users = new User[usersCount];
	file.read((char*)users, usersCount * sizeof(User));

	file.close();

	if (getUserIndex(0) == -1)
		createUser(SYSTEM_USER_NAME, 0);
}

int UsersCollection::getUserIndex(unsigned int idToFind) const
{
	// returns -1 if there is no such user
	for (int i = 0; i < usersCount; ++i)
	{
		if (users[i].id == idToFind)
			return i;
	}

	return -1;
}

void UsersCollection::removeUser(unsigned int idUserToRemove)
{
	if (idUserToRemove == 0)
	{
		std::cout << "You can't remove Sys_User!" << std::endl;
		return;
	}

	int userIndex = getUserIndex(idUserToRemove);
	if (userIndex == -1)
	{
		std::cout << "There is no such user!" << std::endl;
		return;
	}

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

	writeUsersToBinaryFile();

	//TODO
	//send coins to Sys_User
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

void UsersCollection::createUser(const char* userName, double investmentSum)
{
	// user part
	User* temp = new User[++usersCount];

	// for loop until the last one existing
	for (int i = 0; i < usersCount - 1; ++i)
	{
		temp[i] = users[i];
	}

	temp[usersCount - 1].id = idCounter++;
	strcpy_s(temp[usersCount - 1].name, strlen(userName) + 1, userName);

	delete[] users;
	users = temp;

	writeUsersToBinaryFile();

	// transaction part
	//makeTransaction(SYSTEM_USER_ID, userId, investmentSum * OOP_COINS_PER_LEV);
}

//double UsersCollection::getUserCoins(unsigned int userId) const
//{
//	// validation ?
//	double totalCoins = 0;
//	for (int i = 0; i < tBlocksCount; ++i)
//	{
//		for (int j = 0; i < tBlocks[i].validTransactions; ++j)
//		{
//			//coins received
//			if (userId == tBlocks[i].transactions[j].receiver)
//				totalCoins += tBlocks[i].transactions[j].coins;
//			//coins sent
//			if (userId == tBlocks[i].transactions[j].sender)
//				totalCoins -= tBlocks[i].transactions[j].coins;
//		}
//	}
//
//	return totalCoins;
//}

//void UsersCollection::makeTransaction(unsigned int senderId, unsigned int receiverId, double coinsToSend)
//{
//	if (senderId != 0)
//	{
//		int senderIndex = getUserIndex(senderId);
//		double senderCoins = getUserCoins(senderId);
//		// thats not the right way to compare doubles
//		if (senderCoins < coinsToSend)
//		{
//			std::cout << "User doesn't have enough money!" << std::endl;
//			return;
//		}
//	}
//
//	// do I need this ?
//	if (tBlocksCount == 0)
//		createTBlock();
//
//	if (tBlocks[tBlocksCount - 1].validTransactions == MAX_VALID_TRANSACTIONS)
//		createTBlock();
//
//	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].sender = senderId;
//	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].receiver = receiverId;
//	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].coins = coinsToSend;
//	// set time with <ctime>
//
//	// make it better
//	std::cout << "Sender sent " << coinsToSend << " coins to receiver succesfully!" << std::endl;
//
//	tBlocks[tBlocksCount - 1].validTransactions++;
//}

void UsersCollection::printUsers() const
{
	std::cout << "Total users: " << usersCount << std::endl;

	for (int i = 0; i < usersCount; ++i)
	{
		std::cout << users[i].id << " " << users[i].name << " ";
	}
	std::cout << std::endl;
}

size_t getSize(std::ifstream& file)
{
	unsigned int currentPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(currentPos, std::ios::beg);

	return size;
}