#include "tBlocks.h"

const char* TBLOCKS_FILE_NAME = "blocks.dat";
const unsigned int MAX_VALID_TRANSACTIONS = 16;

unsigned TBlocksCollection::computeHash(const unsigned char* memory, int length) {
	unsigned hash = 0xbeaf;

	for (int c = 0; c < length; c++) {
		hash += memory[c];
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}

void TBlocksCollection::createTBlock()
{
	unsigned int tBlockId = tBlocksCount++;
	TransactionBlock* temp = new TransactionBlock[tBlocksCount];

	// for loop until the last one existing
	for (int i = 0; i < tBlocksCount - 1; ++i)
	{
		temp[i] = tBlocks[i];
	}

	temp[tBlockId].id = tBlockId;
	temp[tBlockId].validTransactions = 0;

	if (tBlockId == 0)
		temp[tBlockId].prevBlockId = tBlockId;
	else
	{
		temp[tBlockId].prevBlockId = tBlockId - 1;
		unsigned hash = computeHash((unsigned char*)(&tBlocks[tBlockId - 1]), sizeof(TransactionBlock));
		temp[tBlockId].prevBlockHash = hash;
	}

	delete[] tBlocks;
	tBlocks = temp;
}

double TBlocksCollection::getUserCoins(unsigned int userId) const
{
	double totalCoins = 0.0;

	for (int i = 0; i < tBlocksCount; ++i)
	{
		for (int j = 0; j < tBlocks[i].validTransactions; ++j)
		{
			//coins received
			if (userId == tBlocks[i].transactions[j].receiver)
				totalCoins += tBlocks[i].transactions[j].coins;
			//coins sent
			else if (userId == tBlocks[i].transactions[j].sender)
				totalCoins -= tBlocks[i].transactions[j].coins;
		}
	}

	return totalCoins;
}

double TBlocksCollection::getTBlockCoins(const TransactionBlock& tBlock) const
{
	double totalCoins = 0.0;
	for (int i = 0; i < tBlock.validTransactions; ++i)
	{
		totalCoins += tBlock.transactions[i].coins;
	}

	return totalCoins;
}

void TBlocksCollection::printTBlocksInfo() const
{
	std::cout << "Total blocks: " << tBlocksCount << "\n";
	for (int i = 0; i < tBlocksCount; ++i)
	{
		std::cout << "-----------------------------------------------------" << "\n";
		std::cout << "Block id: " << tBlocks[i].id << "\n";
		std::cout << "Previous block id: " << tBlocks[i].prevBlockId << "\n";
		std::cout << "Previous block hash: " << tBlocks[i].prevBlockHash << "\n";
		std::cout << "Valid transactions: " << tBlocks[i].validTransactions << "\n";
		std::cout << "Transactions info:" << "\n" << "\n";
		for (int j = 0; j < tBlocks[i].validTransactions; ++j)
		{
			std::cout << "-Sender: " << tBlocks[i].transactions[j].sender << "\n";
			std::cout << "-Receiver: " << tBlocks[i].transactions[j].receiver << "\n";
			std::cout << "-Coins: " << tBlocks[i].transactions[j].coins << "\n";
			std::cout << "-Time: " << tBlocks[i].transactions[j].time << "\n";
			std::cout << "\n";
		}
		std::cout << "-----------------------------------------------------" << "\n";
	}
	std::cout << std::endl;
}

void TBlocksCollection::makeTransaction(unsigned int sender, unsigned int receiver, double coins)
{
	int currentTransaction = tBlocks[tBlocksCount - 1].validTransactions++;
	TransactionBlock& currentTBlock = tBlocks[tBlocksCount - 1];

	currentTBlock.transactions[currentTransaction].sender = sender;
	currentTBlock.transactions[currentTransaction].receiver = receiver;
	currentTBlock.transactions[currentTransaction].coins = coins;
	time((time_t*)&currentTBlock.transactions[currentTransaction].time);
}

void TBlocksCollection::readFileTBlocks()
{
	std::ifstream file(TBLOCKS_FILE_NAME, std::ios::binary);
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

	this->tBlocksCount = fileSize / sizeof(TransactionBlock);
	this->tBlocks = new TransactionBlock[tBlocksCount];
	file.read((char*)tBlocks, tBlocksCount * sizeof(TransactionBlock));

	file.close();
}

void TBlocksCollection::writeFileTBlocks() const
{
	std::ofstream file(TBLOCKS_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		return;
	}

	file.write((const char*)tBlocks, tBlocksCount * sizeof(TransactionBlock));

	file.close();
}