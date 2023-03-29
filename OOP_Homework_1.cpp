// OOPCoin
//fourth edition
// lev * 420
//TODO test sent coins from one user to another
// CHECK THAT ALL FUNCTIONS HAVE CONST IF THEY NEED AND THAT YOU DELETE ALL HEAP MEMORY
#include <iostream>
#include <fstream>
#include <cstring>

#include "tBlocks.h"
#include "users.h"

void writeRichestUsers(unsigned int usersCount, UserCoins* usersCoins, User* users);
void writeBiggestBlocks(unsigned int tBlocksCount, TBlocksCoins* tBlocksCoins);

int main()
{
	UsersCollection uCollection;
	TBlocksCollection tCollection;
	uCollection.readMetaDataFile();

	tCollection.readFileTBlocks();
	uCollection.readFileUsers();
	tCollection.readUsersCoins(uCollection.users, uCollection.usersCount);
	tCollection.readTBlocksCoins(tCollection.tBlocks, tCollection.tBlocksCount);
	//tCollection.printUsersCoinsInfo(uCollection.usersCount);
	//uCollection.printUsers();
	//tCollection.printTBlocksInfo();
	//int sysUserInd = uCollection.getUserIndex(SYSTEM_USER_ID);
	User sysUser = uCollection.users[0];
	//uCollection.createUser("Ivan", 100);
	User Ivan = uCollection.users[1];
	//tCollection.makeTransaction(sysUser, Ivan, 4200);
	//tCollection.printTBlocksInfo();

	//uCollection.createUser("Mitko", 100);
	User Mitko = uCollection.users[2];
	//tCollection.makeTransaction(Ivan, Mitko, 10);
	//tCollection.makeTransaction(sysUser, Mitko, 420);
	//uCollection.removeUser(1);
	//uCollection.removeUser(2);

	uCollection.printUsers();
	tCollection.printTBlocksInfo();
	tCollection.printUsersCoinsInfo(uCollection.usersCount);
	tCollection.writeTBlocksToBinaryFile();
	uCollection.writeMetaDataFile();

	writeRichestUsers(uCollection.usersCount, tCollection.usersCoins, uCollection.users);
	writeBiggestBlocks(tCollection.tBlocksCount, tCollection.tBlocksCoins);
}

void sortUsers(UserCoins* usersCoins, unsigned int usersCount)
{
	for (int i = 0; i < usersCount - 1; ++i)
	{
		unsigned int richestUserInd = i;
		for (int j = i + 1; j < usersCount; ++j)
		{
			// thats not the right way to compare doubles
			if (usersCoins[j].coins > usersCoins[richestUserInd].coins)
			{
				richestUserInd = j;
			}
		}
		if (richestUserInd != i)
		{
			UserCoins temp = usersCoins[i];
			usersCoins[i] = usersCoins[richestUserInd];
			usersCoins[richestUserInd] = temp;
		}
	}
}

void writeRichestUsers(unsigned int usersCount, UserCoins* usersCoins, User* users)
{
	UserCoins* richestUsers = new UserCoins[usersCount];
	for (int i = 0; i < usersCount; ++i)
	{
		richestUsers[i] = usersCoins[i];
	}
	sortUsers(richestUsers, usersCount);

	// test
	/*for (int i = 0; i < usersCount; ++i)
	{
		std::cout << richestUsers[i].id << " " << richestUsers[i].coins << "\n";
	}
	std::cout << std::endl;*/

	std::ofstream file("richestUsers.txt");
	if (!file.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	for (int i = 0; i < usersCount; ++i)
	{
		file << users[richestUsers[i].id].name << " " << richestUsers[i].coins << "\n";
	}
}

void sortTBlocks(TBlocksCoins* tBlocksCoins, unsigned int tBlocksCount)
{
	for (int i = 0; i < tBlocksCount - 1; ++i)
	{
		unsigned int biggestBlockInd = i;
		for (int j = i + 1; j < tBlocksCount; ++j)
		{
			// thats not the right way to compare doubles
			if (tBlocksCoins[j].coins > tBlocksCoins[biggestBlockInd].coins)
			{
				biggestBlockInd = j;
			}
		}
		if (biggestBlockInd != i)
		{
			TBlocksCoins temp = tBlocksCoins[i];
			tBlocksCoins[i] = tBlocksCoins[biggestBlockInd];
			tBlocksCoins[biggestBlockInd] = temp;
		}
	}
}

void writeBiggestBlocks(unsigned int tBlocksCount, TBlocksCoins* tBlocksCoins)
{
	TBlocksCoins* biggestBlocks = new TBlocksCoins[tBlocksCount];
	for (int i = 0; i < tBlocksCount; ++i)
	{
		biggestBlocks[i] = tBlocksCoins[i];
	}
	sortTBlocks(biggestBlocks, tBlocksCount);

	// test
	for (int i = 0; i < tBlocksCount; ++i)
	{
		std::cout << biggestBlocks[i].id << " " << biggestBlocks[i].coins << "\n";
	}
	std::cout << std::endl;

	std::ofstream file("biggestBlocks.txt");
	if (!file.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	for (int i = 0; i < tBlocksCount; ++i)
	{
		file << biggestBlocks[i].id << " " << biggestBlocks[i].coins << "\n";
	}
}

// fourth edition
//struct User {
//	unsigned id;
//	char name[128];
//};
//	
//struct Transaction {
//	unsigned sender;
//	unsigned receiver;
//	double coins;
//	long long time;
//};
//	
//struct TransactionBlock {
//	unsigned id;
//	unsigned prevBlockId;
//	unsigned prevBlockHash;
//	int validTransactions;
//	Transaction transactions[1];
//};
//	 
//struct Identifiers
//{
//	User* users;
//	TransactionBlock* tBlocks;
//	unsigned int usersCount;
//	unsigned int tBlocksCount;
//	
//	Identifiers()
//	{
//	    users = nullptr;
//	    tBlocks = nullptr;
//	    usersCount = 0;
//	    tBlocksCount = 0;
//	}
//	
//	~Identifiers()
//	{
//	    delete[] users;
//	    delete[] tBlocks;
//	}
//	
//	void readFileUsers();
//	void readFileTBlocks();
//	void createUser(const char* userName, double investmentSum);
//	void createTBlock();
//	void makeTransaction(unsigned int sender, unsigned int receiver, double coins);
//	void printUsers() const;
//	void writeUsersToBinaryFile() const;
//	void writeTBlocksToBinaryFile() const;
//	void removeUser(unsigned int idUserToRemove);
//	int getUserIndex(unsigned int idToFind) const;
//	double getUserCoins(unsigned int userId) const;
//};
//	
//unsigned computeHash(const unsigned char* memory, int length) {
//	unsigned hash = 0xbeaf;
//	
//	for (int c = 0; c < length; c++) {
//	    hash += memory[c];
//	    hash += hash << 10;
//	    hash ^= hash >> 6;
//	}
//	
//	hash += hash << 3;
//	hash ^= hash >> 11;
//	hash += hash << 15;
//	return hash;
//}
//
//// get size is declared after Identifiers struct, is it a problem ?
//size_t getSize(std::ifstream& file);
//
//int main()
//{
//	Identifiers identifiersData;
//	identifiersData.readFileTBlocks();
//	//identifiersData.readFileUsers();
//	//
//	////test
//	//for (int i = 0; i < 1; ++i)
//	//{
//	//	identifiersData.createUser("Pesho", 10);
//	//}
//	//identifiersData.createUser("Ivan", 1);
//	////identifiersData.createUser("Blagoi", 1);
//	//identifiersData.printUsers();
//	//
//	//identifiersData.removeUser(4);
//	//identifiersData.printUsers();
//
//	TransactionBlock t;
//	unsigned hash = computeHash((unsigned char*)(&t), sizeof(t));
//	std::cout << hash;
//}
//	
//size_t getSize(std::ifstream& file)
//{
//	unsigned int currentPos = file.tellg();
//	file.seekg(0, std::ios::end);
//	size_t size = file.tellg();
//	file.seekg(currentPos, std::ios::beg);
//
//	return size;
//}
//
//void Identifiers::readFileUsers()
//{
//	std::ifstream file(USERS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//		std::cout << "File cannot be opened!" << std::endl;
//		createUser(SYSTEM_USER_NAME, 0);
//		return;
//	}
//
//	size_t fileSize = getSize(file);
//	if (fileSize == 0)
//	{
//		std::cout << "File is empty!" << std::endl;
//		createUser(SYSTEM_USER_NAME, 0);
//		return;
//	}
//
//	if (getUserIndex(0) == -1)
//		createUser(SYSTEM_USER_NAME, 0);
//
//	file.read((char*)&usersCount, sizeof(usersCount));
//	users = new User[usersCount];
//	file.read((char*)users, usersCount * sizeof(*users));
//
//	file.close();
//}
//
//void Identifiers::readFileTBlocks()
//{
//	std::ifstream file(TBLOCKS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//		std::cout << "File cannot be opened!" << std::endl;
//		createTBlock();
//		return;
//	}
//
//	size_t fileSize = getSize(file);
//	if (fileSize == 0)
//	{
//		std::cout << "File is empty!" << std::endl;
//		createTBlock();
//		return;
//	}
//
//	file.read((char*)&tBlocksCount, sizeof(tBlocksCount));
//	tBlocks = new TransactionBlock[tBlocksCount];
//	file.read((char*)tBlocks, tBlocksCount * sizeof(*tBlocks));
//
//	file.close();
//}
//
//int Identifiers::getUserIndex(unsigned int idToFind) const
//{
//	// returns -1 if there is no such user
//	for (int i = 0; i < usersCount; ++i)
//	{
//	    if (users[i].id == idToFind)
//	        return i;
//	}
//	
//	return -1;
//}
//	
//void Identifiers::removeUser(unsigned int idUserToRemove)
//{
//	if (idUserToRemove == 0)
//	{
//	    std::cout << "You can't remove Sys_User!" << std::endl;
//	    return;
//	}
//	
//	// will this work? 
//	int userIndex = getUserIndex(idUserToRemove);
//	if (userIndex == -1)
//	{
//	    std::cout << "There is no such user!" << std::endl;
//	    return;
//	}
//	
//	User* temp = new User[--usersCount];
//	for (int i = 0; i < userIndex; i++)
//	{
//	    temp[i] = users[i];
//	}
//	for (int i = userIndex; i < usersCount; i++)
//	{
//	    temp[i] = users[i + 1];
//	}
//	
//	delete[] users;
//	users = temp;
//	
//	writeUsersToBinaryFile();
//
//	//TODO
//	//send coins to Sys_User
//}
//
//void Identifiers::writeUsersToBinaryFile() const
//{
//	std::ofstream file(USERS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//	    std::cout << "File cannot be opened!" << std::endl;
//	    return;
//	}
//	
//	file.write((const char*)&usersCount, sizeof(usersCount));
//	file.write((const char*)users, usersCount * sizeof(*users));
//	
//	file.close();
//}
//
//void Identifiers::writeTBlocksToBinaryFile() const
//{
//	std::ofstream file(TBLOCKS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//		std::cout << "File cannot be opened!" << std::endl;
//		return;
//	}
//
//	file.write((const char*)&tBlocksCount, sizeof(tBlocksCount));
//	file.write((const char*)tBlocks, tBlocksCount * sizeof(*tBlocks));
//
//	file.close();
//}
//
//void Identifiers::createUser(const char* userName, double investmentSum)
//{
//	// user part
//	unsigned int userId = usersCount++;
//	User* temp = new User[usersCount];
//	
//	// for loop until the last one existing
//	for (int i = 0; i < usersCount - 1; ++i)
//	{
//	    temp[i] = users[i];
//	}
//	
//	temp[userId].id = userId;
//	strcpy_s(temp[userId].name, strlen(userName) + 1, userName);
//	
//	delete[] users;
//	users = temp;
//	
//	writeUsersToBinaryFile();
//	
//	// transaction part
//	makeTransaction(SYSTEM_USER_ID, userId, investmentSum * OOP_COINS_PER_LEV);
//}
//
//void Identifiers::createTBlock()
//{
//	unsigned int tBlockId = tBlocksCount++;
//	TransactionBlock* temp = new TransactionBlock[tBlocksCount];
//
//	// for loop until the last one existing
//	for (int i = 0; i < tBlocksCount - 1; ++i)
//	{
//		temp[i] = tBlocks[i];
//	}
//
//	temp[tBlockId].id = tBlockId;
//	temp[tBlockId].validTransactions = 0;
//
//	if (tBlockId == 0)
//		temp[tBlockId].prevBlockId = tBlockId;
//	else
//	{
//		temp[tBlockId].prevBlockId = tBlockId - 1;
//		// what should be the first argument of computeHash?
//		temp[tBlockId].prevBlockHash = computeHash((const unsigned char*)(&tBlocks[tBlockId - 1]), sizeof(tBlocks[tBlockId - 1]));
//	}
//
//	delete[] tBlocks;
//	tBlocks = temp;
//
//	writeTBlocksToBinaryFile();
//}
//
//double Identifiers::getUserCoins(unsigned int userId) const
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
//
//void Identifiers::makeTransaction(unsigned int senderId, unsigned int receiverId, double coinsToSend)
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
//	
//void Identifiers::printUsers() const
//{
//	std::cout << "Total users: " << usersCount << std::endl;
//	
//	for (int i = 0; i < usersCount; ++i)
//	{
//	    std::cout << users[i].id << " " << users[i].name << " ";
//	}
//	std::cout << std::endl;
//}

// third edition
//struct User {
//    unsigned id;
//    char name[128];
//};
//
//struct Transaction {
//    unsigned sender;
//    unsigned receiver;
//    double coins;
//    long long time;
//};
//
//struct TransactionBlock {
//    unsigned id;
//    unsigned prevBlockId;
//    unsigned prevBlockHash;
//    int validTransactions;
//    Transaction transactions[16];
//};
// 
//struct Identifiers
//{
//    User* users;
//    TransactionBlock* tBlocks;
//    unsigned int usersCount;
//    unsigned int tBlocksCount;
//
//    Identifiers()
//    {
//        users = nullptr;
//        tBlocks = nullptr;
//        usersCount = 0;
//        tBlocksCount = 0;
//    }
//
//    ~Identifiers()
//    {
//        delete[] users;
//        delete[] tBlocks;
//    }
//
//
//};
//
//unsigned computeHash(const unsigned char* memory, int length) {
//    unsigned hash = 0xbeaf;
//
//    for (int c = 0; c < length; c++) {
//        hash += memory[c];
//        hash += hash << 10;
//        hash ^= hash >> 6;
//    }
//
//    hash += hash << 3;
//    hash ^= hash >> 11;
//    hash += hash << 15;
//    return hash;
//}
//
//void readFile(Identifiers& identifier);
//void createUser(Identifiers& identifier, const char* userName, unsigned int investmentSum);
//void printUsers(const Identifiers& identifier);
//void writeUsersToBinaryFile(const Identifiers& identifier);
//void removeUser(Identifiers& identifier, unsigned int idUserToRemove);
//int getUserIndex(Identifiers& identifier, unsigned int idToFind);
//size_t getSize(std::ifstream& file);
//
//int main()
//{
//    Identifiers identifiersData;
//    readFile(identifiersData);
//
//    //test
//    /*for (int i = 0; i < 1; ++i)
//    {
//        createUser(identifiersData, "Pesho", 0);
//    }
//    createUser(identifiersData, "Ivan", 0);
//    createUser(identifiersData, "Asparuh", 0);
//    printUsers(identifiersData);*/
//
//    removeUser(identifiersData, 1);
//    printUsers(identifiersData);
//}
//
//int getUserIndex(Identifiers& identifier, unsigned int idToFind)
//{
//    // returns -1 if there is no such user
//    for (int i = 0; i < identifier.usersCount; ++i)
//    {
//        if (identifier.users[i].id == idToFind)
//            return i;
//    }
//
//    return -1;
//}
//
//void removeUser(Identifiers& identifier, unsigned int idUserToRemove)
//{
//    if (idUserToRemove == 0)
//    {
//        std::cout << "You can't remove Sys_User!" << std::endl;
//        return;
//    }
//
//    int userIndex = getUserIndex(identifier, idUserToRemove);
//    if (userIndex == -1)
//    {
//        std::cout << "There is no such user!" << std::endl;
//        return;
//    }
//
//    User* temp = new User[--identifier.usersCount];
//    for (int i = 0; i < userIndex; i++)
//    {
//        temp[i] = identifier.users[i];
//    }
//    for (int i = userIndex; i < identifier.usersCount; i++)
//    {
//        temp[i] = identifier.users[i + 1];
//    }
//
//    delete[] identifier.users;
//    identifier.users = temp;
//
//    writeUsersToBinaryFile(identifier);
//}
//
//size_t getSize(std::ifstream& file)
//{
//    unsigned int currentPos = file.tellg();
//    file.seekg(0, std::ios::end);
//    size_t size = file.tellg();
//    file.seekg(currentPos, std::ios::beg);
//
//    return size;
//}
//
//void readFile(Identifiers& identifier)
//{
//    std::ifstream file(USERS_FILE_NAME, std::ios::binary);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        createUser(identifier, SYSTEM_USER_NAME, MAX_COINS);
//        return;
//    }
//
//    size_t fileSize = getSize(file);
//    if (fileSize == 0)
//    {
//        std::cout << "File is empty!" << std::endl;
//        createUser(identifier, SYSTEM_USER_NAME, MAX_COINS);
//        return;
//    }
//
//    if (getUserIndex(identifier, 0) == -1)
//        createUser(identifier, SYSTEM_USER_NAME, MAX_COINS);
//
//    file.read((char*)&identifier.usersCount, sizeof(identifier.usersCount));
//    identifier.users = new User[identifier.usersCount];
//    file.read((char*)identifier.users, identifier.usersCount * sizeof(*identifier.users));
//
//    file.close();
//}
//
//void writeUsersToBinaryFile(const Identifiers& identifier)
//{
//    std::ofstream file(USERS_FILE_NAME, std::ios::binary);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        return;
//    }
//
//    file.write((const char*)&identifier.usersCount, sizeof(identifier.usersCount));
//    file.write((const char*)identifier.users, identifier.usersCount * sizeof(*identifier.users));
//
//    file.close();
//}
//
//void createUser(Identifiers& identifier, const char* userName, unsigned int investmentSum)
//{
//    // user part
//    unsigned int userId = identifier.usersCount++;
//    User* temp = new User[identifier.usersCount];
//
//    // for loop until the last one existing
//    for (int i = 0; i < identifier.usersCount - 1; ++i)
//    {
//        temp[i] = identifier.users[i];
//    }
//
//    temp[userId].id = userId;
//    strcpy_s(temp[userId].name, strlen(userName) + 1, userName);
//
//    delete[] identifier.users;
//    identifier.users = temp;
//
//    writeUsersToBinaryFile(identifier);
//
//    // transaction part
//
//}
//
//void printUsers(const Identifiers& identifier)
//{
//    std::cout << "Total users: " << identifier.usersCount << std::endl;
//
//    for (int i = 0; i < identifier.usersCount; ++i)
//    {
//        std::cout << identifier.users[i].id << " " << identifier.users[i].name << " ";
//    }
//    std::cout << std::endl;
//}

////second edition
//#include <iostream>
//#include <fstream>
//#include <cstring>
//
//const unsigned int OOP_COINS_PER_LEV = 420;
//const char* USERS_FILE_NAME = "users.dat";
//const unsigned int USER_NAME_LEN = 128;
//
//struct
//{
//    User* users = nullptr;
//    //int* transactionBlocksId = nullptr;
//    int usersCount = 0;
//    //int transactions = 0;
//} identifiers;
//
//struct User {
//    unsigned id;
//    char name[128];
//};
//
//struct Transaction {
//    unsigned sender;
//    unsigned receiver;
//    double coins;
//    long long time;
//};
//
//struct TransactionBlock {
//    unsigned id;
//    unsigned prevBlockId;
//    unsigned prevBlockHash;
//    int validTransactions;
//    Transaction transactions[16];
//};
//
//unsigned computeHash(const unsigned char* memory, int length) {
//    unsigned hash = 0xbeaf;
//
//    for (int c = 0; c < length; c++) {
//        hash += memory[c];
//        hash += hash << 10;
//        hash ^= hash >> 6;
//    }
//
//    hash += hash << 3;
//    hash ^= hash >> 11;
//    hash += hash << 15;
//    return hash;
//}
//
////void initSystemAdmin();
////void validateInput(char*& userName, unsigned int& investmentSum);
////// should the function return the created user?
////void createUser(const char* userName, unsigned int investmentSum);
////void removeUser(const char* userName);
////void sendCoins(const User& sender, const User& receiver, unsigned int coinsToSent);
//void testFillIdentifiers();
//void readMetaData();
//// initialize identifiers struct
//void initMetaData();
//void writeUserData(const char* fileName, const User* u);
//
//int main()
//{
//    testFillIdentifiers();
//    writeUserData(USERS_FILE_NAME);
//    initMetaData();
//    readMetaData();
//}
//
//void testFillIdentifiers()
//{
//    identifiers.usersCount = 3;
//    identifiers.users = new User[identifiers.usersCount];
//    createUser("Pesho", 0);
//    createUser("Ivan", 0);
//    createUser("Asparuh", 0);
//
//    //test
//    readMetaData();
//}
//
//void writeUserData(const char* fileName, const User* u)
//{
//    std::ofstream file(fileName, std::ios::binary | std::ios::app);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        return;
//    }
//
//    file.write((const char*)&u, sizeof(u));
//    file.seekp(0, std::ios::beg);
//    // writes the identifier of user at the beggining of the file(it's not the count of the users, it's the count - 1)
//    file.write((const char*)&u->id, sizeof(u->id));
//
//    file.close();
//}
//
//void readMetaData(const char* fileName)
//{
//    std::ifstream file(fileName, std::ios::binary);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        return;
//    }
//
//    file.read((char*)&identifiers.usersCount, sizeof(identifiers.usersCount));
//    identifiers.users = new User[identifiers.usersCount];
//    file.read((char*)identifiers.users, identifiers.usersCount * sizeof(identifiers.users[0]));
//
//    //test
//    printMetaData();
//
//    file.close();
//}
//
//void printMetaData()
//{
//    std::cout << "Total users: " << identifiers.usersCount << std::endl;
//
//    for (int i = 0; i < identifiers.usersCount; ++i)
//    {
//        std::cout << identifiers.users[i].id << identifiers.users[i].name << " ";
//    }
//    std::cout << std::endl;
//}
//
//void createUser(const char* userName, unsigned int investmentSum)
//{
//    User* u = new User;
//    u->id = identifiers.usersCount;
//    strcpy_s(u->name, strlen(userName) + 1, userName);
//}


// first edition
//#include <iostream>
//#include <fstream>
//
//const unsigned int OOP_COINS_PER_LEV = 420;
//
//struct
//{
//    int* usersId = nullptr;
//    int* transactionBlocksId = nullptr;
//    int users = 0;
//    int transactions = 0;
//} identifiers;
//
//struct User {
//    unsigned id;
//    char name[128];
//};
//
//struct Transaction {
//    unsigned sender;
//    unsigned receiver;
//    double coins;
//    long long time;
//};
//
//struct TransactionBlock {
//    unsigned id;
//    unsigned prevBlockId;
//    unsigned prevBlockHash;
//    int validTransactions;
//    Transaction transactions[16];
//};
//
//unsigned computeHash(const unsigned char* memory, int length) {
//    unsigned hash = 0xbeaf;
//
//    for (int c = 0; c < length; c++) {
//        hash += memory[c];
//        hash += hash << 10;
//        hash ^= hash >> 6;
//    }
//
//    hash += hash << 3;
//    hash ^= hash >> 11;
//    hash += hash << 15;
//    return hash;
//}
//
////void initSystemAdmin();
////void validateInput(char*& userName, unsigned int& investmentSum);
////// should the function return the created user?
////void createUser(const char* userName, unsigned int investmentSum);
////void removeUser(const char* userName);
////void sendCoins(const User& sender, const User& receiver, unsigned int coinsToSent);
//void testFillIdentifiers();
//void readMetaData();
//// initialize identifiers struct
//void initMetaData();
//void writeMetaData(const char* fileName);
//
//int main()
//{
//    testFillIdentifiers();
//    writeMetaData("myMetaData");
//    initMetaData();
//    readMetaData();
//}
//
//void testFillIdentifiers()
//{
//    identifiers.users = 3;
//    identifiers.usersId = new int[identifiers.users + 1];
//    for (int i = 0; i < identifiers.users; ++i)
//    {
//        identifiers.usersId[i] = i;
//    }
//
//    //test
//    //readMetaData();
//}
//
//void writeMetaData(const char* fileName)
//{
//    std::ofstream file(fileName, std::ios::binary);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        return;
//    }
//
//    file.write((const char*)&identifiers.users, sizeof(identifiers.users));
//    file.write((const char*)identifiers.usersId, sizeof(identifiers.users) * identifiers.users);
//
//    delete[] identifiers.usersId;
//    file.close();
//}
//
//unsigned int getSize(std::ifstream& file)
//{
//    unsigned int currentPos = file.tellg();
//    file.seekg(0, std::ios::end);
//    unsigned int size = file.tellg();
//    file.seekg(currentPos, std::ios::beg);
//
//    return size;
//}
//
//void initMetaData()
//{
//    // dont forget to change file path
//    std::ifstream file("myMetaData", std::ios::binary);
//    if (!file.is_open())
//    {
//        std::cout << "File cannot be opened!" << std::endl;
//        return;
//    }
//
//    unsigned int size = getSize(file);
//    file.read((char*)&identifiers.users, sizeof(identifiers.users));
//    identifiers.usersId = new int[identifiers.users];
//    file.read((char*)identifiers.usersId, identifiers.users * sizeof(identifiers.users));
//
//    //test
//    //readMetaData();
//
//    file.close();
//}
//
//void readMetaData()
//{
//    std::cout << "Total users: " << identifiers.users << std::endl;
//
//    for (int i = 0; i < identifiers.users; ++i)
//    {
//        std::cout << identifiers.usersId[i] << " ";
//    }
//    std::cout << std::endl;
//}
//
////void createUser(const char* userName, unsigned int investmentSum)
////{
////    
////    //User u(userName, id);
////}
