#include "controller.h"

const char* META_DATA_FILE_NAME = "metaData.dat";
const char* SYSTEM_USER_NAME_ = "Sys_User";
const unsigned int SYSTEM_USER_ID_ = 0;
const unsigned int MAX_VALID_TRANSACTIONS_ = 16;
const unsigned int OOP_COINS_PER_LEV = 420;
const char* SORTED_USERS_ = "richest-users.txt";
const char* SORTED_BLOCKS_ = "biggest-blocks.txt";

void Controller::createUser(const char* userName, double investmentSum)
{
	if (!uCollection->userNameIsUnique(userName))
	{
		std::cout << "User name already exists!" << std::endl;
		return;
	}

	if (investmentSum <= 0)
	{
		std::cout << "You can not enter 0 or less!" << std::endl;
		return;
	}

	uCollection->createUser(userName);
	uCollection->writeUserToBinaryFile();
	writeMetaDataFile();

	unsigned int userId = uCollection->getUserId(userName);
	cCollection->addUserCoins(userId, uCollection->usersCount);

	makeTransaction(SYSTEM_USER_NAME_, userName, investmentSum * OOP_COINS_PER_LEV);
}

void Controller::removeUser(const char* name)
{
	int userInd = uCollection->getUserIndex(name);
	if (userInd == -1)
	{
		std::cout << "There is no such user!" << std::endl;
		return;
	}

	if (strcmp(name, SYSTEM_USER_NAME_) == 0)
	{
		std::cout << "You can't remove Sys_User!" << std::endl;
		return;
	}

	double userCoins = tCollection->getUserCoins(uCollection->getUserId(name));
	makeTransaction(name, SYSTEM_USER_NAME_, userCoins);

	uCollection->removeUser(name);
	uCollection->writeUsersToBinaryFile();

	cCollection->removeUser(userInd, uCollection->usersCount);
}

void Controller::readFileUsers()
{
	uCollection->readFileUsers();

	if (uCollection->getUserIndex(SYSTEM_USER_NAME_) == -1)
	{
		uCollection->createUser(SYSTEM_USER_NAME_);
		uCollection->writeUsersToBinaryFile();

		cCollection->addUserCoins(SYSTEM_USER_ID_, uCollection->usersCount);
	}
}

void Controller::makeTransaction(const char* senderName, const char* receiverName, double coinsToSend)
{
	int senderInd = uCollection->getUserIndex(senderName);
	int receiverInd = uCollection->getUserIndex(receiverName);

	User& sender = uCollection->users[senderInd];
	User& receiver = uCollection->users[receiverInd];

	if (tCollection->tBlocksCount == 0)
	{
		tCollection->createTBlock();
		cCollection->addTBlockCoins(tCollection->tBlocks[tCollection->tBlocksCount - 1].id, tCollection->tBlocksCount);
	}

	int validTransactions = tCollection->tBlocks[tCollection->tBlocksCount - 1].validTransactions;
	if (validTransactions == MAX_VALID_TRANSACTIONS_)
	{
		tCollection->createTBlock();
		cCollection->addTBlockCoins(tCollection->tBlocks[tCollection->tBlocksCount - 1].id, tCollection->tBlocksCount);
		
		tCollection->writeFileTBlocks();
	}

	tCollection->makeTransaction(sender.id, receiver.id, coinsToSend);

	cCollection->makeTransactionUsers(senderInd, receiverInd, coinsToSend);
	cCollection->makeTransactionTBlocks(tCollection->tBlocks[tCollection->tBlocksCount - 1].id, coinsToSend);

	std::cout << sender.name << " sent " << coinsToSend << " coins to "
		<< receiver.name << " succesfully!" << std::endl;
	std::cout << std::endl;
}

void Controller::sendCoins(const char* senderName, const char* receiverName, double coins)
{
	int senderInd = uCollection->getUserIndex(senderName);
	int receiverInd = uCollection->getUserIndex(receiverName);
	if (senderInd == -1 || receiverInd == -1)
	{
		std::cout << "There is no such user!" << std::endl;
		return;
	}

	double senderCoins = tCollection->getUserCoins(uCollection->getUserId(senderName));
	if (senderCoins < coins)
	{
		std::cout << "User doesn't have enough money to send!" << std::endl;
		return;
	}

	makeTransaction(senderName, receiverName, coins);
}

void Controller::readMetaDataFile()
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

	file.read((char*)&uCollection->idCounter, sizeof(uCollection->idCounter));

	file.close();
}

void Controller::writeMetaDataFile() const
{
	std::ofstream file(META_DATA_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	file.write((const char*)&uCollection->idCounter, sizeof(uCollection->idCounter));

	file.close();
}

void Controller::readUsersCoins(User* users, unsigned int usersCount)
{
	Coins* temp = new Coins[usersCount];
	for (int i = 0; i < usersCount; ++i)
	{
		unsigned curUserId = users[i].id;
		temp[i].id = curUserId;

		if (curUserId == 0)
		{
			temp[i].coins = 0;
			continue;
		}
		temp[i].coins = tCollection->getUserCoins(curUserId);
	}

	delete[] cCollection->usersCoins;
	this->cCollection->usersCoins = temp;
}

void Controller::readTBlocksCoins(TransactionBlock* tBlocks, unsigned int tBlocksCount)
{
	if (tBlocksCount == 0)
		return;
	Coins* temp = new Coins[tBlocksCount];
	for (int i = 0; i < tBlocksCount; ++i)
	{
		temp[i].id = tBlocks[i].id;
		temp[i].coins = tCollection->getTBlockCoins(tBlocks[i]);
	}

	delete[] cCollection->tBlocksCoins;
	this->cCollection->tBlocksCoins = temp;
}

void Controller::writeRichestUsers()
{
	// there will always be at least one user(Sys_User)
	if (uCollection->usersCount == 1)
	{
		std::cout << "There are no users!" << std::endl;
		return;
	}

	unsigned int usersCount = uCollection->usersCount;
	Coins* richestUsers = new Coins[usersCount];
	for (int i = 0; i < usersCount; ++i)
	{
		richestUsers[i] = cCollection->usersCoins[i];
	}
	cCollection->sort(richestUsers, usersCount);

	// test
	//for (int i = 0; i < usersCount - 1; ++i)
	//{
	//	std::cout << richestUsers[i].id << " " << richestUsers[i].coins << "\n";
	//}
	//std::cout << std::endl;

	char fileName[50];
	convertTimeToChar(fileName);
	strcat_s(fileName, SORTED_USERS_);
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	for (int i = 0; i < usersCount - 1; ++i)
	{
		char userName[128];
		uCollection->getUserName(userName, richestUsers[i].id);
		file << userName << " " << richestUsers[i].coins << "\n";
	}
}

void Controller::writeBiggestBlocks()
{
	if (tCollection->tBlocksCount == 0)
	{
		std::cout << "There are no blocks!" << std::endl;
		return;
	}

	unsigned int blocksCount = tCollection->tBlocksCount;

	Coins* biggestBlocks = new Coins[blocksCount];
	for (int i = 0; i < blocksCount; ++i)
	{
		biggestBlocks[i] = cCollection->tBlocksCoins[i];
	}
	cCollection->sort(biggestBlocks, blocksCount);

	// test
	//for (int i = 0; i < blocksCount; ++i)
	//{
	//	std::cout << biggestBlocks[i].id << " " << biggestBlocks[i].coins << "\n";
	//}
	//std::cout << std::endl;

	char fileName[50];
	convertTimeToChar(fileName);
	strcat_s(fileName, SORTED_BLOCKS_);
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "File could not be opened!" << std::endl;
		return;
	}

	for (int i = 0; i < blocksCount; ++i)
	{
		file << biggestBlocks[i].id << " " << biggestBlocks[i].coins << "\n";
	}
}

void Controller::convertTimeToChar(char fileName[])
{
	long long num;
	time(&num);
	int i = 0;
	while (num > 0) {
		fileName[i++] = static_cast<char>('0' + (num % 10));
		num /= 10;
	}
	fileName[i] = '\0';
	reverseCharArray(fileName, strlen(fileName));
}

void Controller::reverseCharArray(char arr[], int size) {
	for (int i = 0; i < size / 2; i++) {
		char temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
}
