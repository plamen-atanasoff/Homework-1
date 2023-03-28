#include <iostream>
#include <fstream>

#include "tBlocks.h"

const char* TBLOCKS_FILE_NAME = "blocks.dat";
const unsigned int MAX_VALID_TRANSACTIONS = 16;

unsigned computeHash(const unsigned char* memory, int length) {
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

void TBlocksCollection::readFileTBlocks()
{
	std::ifstream file(TBLOCKS_FILE_NAME, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "File cannot be opened!" << std::endl;
		createTBlock();
		return;
	}

	size_t fileSize = getSize(file);
	if (fileSize == 0)
	{
		std::cout << "File is empty!" << std::endl;
		createTBlock();
		return;
	}

	this->tBlocksCount = fileSize / sizeof(TransactionBlock);
	this->tBlocks = new TransactionBlock[tBlocksCount];
	file.read((char*)tBlocks, tBlocksCount * sizeof(TransactionBlock));

	file.close();
}

void TBlocksCollection::writeTBlocksToBinaryFile() const
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
		// make this prettier
		unsigned hash = computeHash((unsigned char*)(&tBlocks[tBlockId - 1]), sizeof(TransactionBlock));
		std::cout << hash;
		temp[tBlockId].prevBlockHash = hash;
	}

	delete[] tBlocks;
	tBlocks = temp;

	//this shouldn't be here
	//writeTBlocksToBinaryFile();
}

double TBlocksCollection::getUserCoins(unsigned int userId) const
{
	// validation ?
	double totalCoins = 0;
	for (int i = 0; i < tBlocksCount; ++i)
	{
		for (int j = 0; i < tBlocks[i].validTransactions; ++j)
		{
			//coins received
			if (userId == tBlocks[i].transactions[j].receiver)
				totalCoins += tBlocks[i].transactions[j].coins;
			//coins sent
			if (userId == tBlocks[i].transactions[j].sender)
				totalCoins -= tBlocks[i].transactions[j].coins;
		}
	}

	return totalCoins;
}

// function accepts sender and receiver as User objects !
void TBlocksCollection::makeTransaction(const User& sender, const User& receiver, double coinsToSend)
{
	if (sender.id != 0)
	{
		double senderCoins = getUserCoins(sender.id);
		// thats not the right way to compare doubles
		if (senderCoins < coinsToSend)
		{
			std::cout << "User doesn't have enough money!" << std::endl;
			return;
		}
	}

	int& validTransactionsCur = tBlocks[tBlocksCount - 1].validTransactions;
	// change to MAX_VALID_TRANSACTIONS !!!
	if (validTransactionsCur == 1)
	{
		writeTBlocksToBinaryFile();
		createTBlock();
		int& validTransactionsNew = tBlocks[tBlocksCount - 1].validTransactions;
		validTransactionsNew++;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsNew - 1].sender = sender.id;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsNew - 1].receiver = receiver.id;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsNew - 1].coins = coinsToSend;
	}
	else
	{
		validTransactionsCur++;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsCur - 1].sender = sender.id;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsCur - 1].receiver = receiver.id;
		tBlocks[tBlocksCount - 1].transactions[validTransactionsCur - 1].coins = coinsToSend;
	}
	// set time with <ctime>

	// make it better
	std::cout << "Sender sent " << coinsToSend << " coins to receiver succesfully!" << std::endl;
}

void TBlocksCollection::printTBlocksInfo() const
{
	for (int i = 0; i < tBlocksCount; ++i)
	{
		std::cout << tBlocks[i].id << "\n";
		std::cout << tBlocks[i].prevBlockId << "\n";
		std::cout << tBlocks[i].prevBlockHash << "\n";
		std::cout << tBlocks[i].validTransactions << "\n";
		std::cout << tBlocks[i].transactions[0].sender << "\n";
		std::cout << tBlocks[i].transactions[0].receiver << "\n";
		std::cout << tBlocks[i].transactions[0].coins << "\n";
		std::cout << tBlocks[i].transactions[0].time << "\n";
	}
}