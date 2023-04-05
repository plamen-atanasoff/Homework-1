#pragma once

#include "helperFunc.h"

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
	Transaction transactions[16];
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

	void createTBlock();
	double getUserCoins(unsigned int userId) const;
	double getTBlockCoins(const TransactionBlock& tBlock) const;
	void printTBlocksInfo() const;
	void makeTransaction(unsigned int sender, unsigned int receiver, double coins);

	void readFileTBlocks();
	void writeFileTBlocks() const;

	void verifyTBlocks() const;
};

unsigned computeHash(const unsigned char* memory, int length);
