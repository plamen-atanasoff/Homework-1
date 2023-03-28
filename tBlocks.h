#pragma once

#include "users.h"

struct Transaction {
	unsigned sender;
	unsigned receiver;
	double coins;
	long long time;
};

struct TransactionBlock {
	unsigned id;
	unsigned prevBlockId;
	unsigned prevBlockHash;
	int validTransactions;
	// make it 16 after testing !!!
	Transaction transactions[1];
};

struct TBlocksCollection
{
	TransactionBlock* tBlocks;
	unsigned int tBlocksCount;

	TBlocksCollection()
	{
		tBlocks = nullptr;
		tBlocksCount = 0;
	}

	~TBlocksCollection()
	{
		delete[] tBlocks;
	}

	void readFileTBlocks();
	void createTBlock();
	void writeTBlocksToBinaryFile() const;
	void makeTransaction(const User& sender, const User& receiver, double coinsToSend);
	double getUserCoins(unsigned int userId) const;
	void printTBlocksInfo() const;
};

unsigned computeHash(const unsigned char* memory, int length);