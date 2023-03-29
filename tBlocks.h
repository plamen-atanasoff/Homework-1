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

struct UserCoins
{
	unsigned int id;
	double coins;
};

// do I need this( can I use the upper struct instead)
struct TBlocksCoins
{
	unsigned int id;
	double coins;
};

struct TBlocksCollection
{
	TransactionBlock* tBlocks;
	UserCoins* usersCoins;
	TBlocksCoins* tBlocksCoins;
	unsigned int tBlocksCount;

	TBlocksCollection()
	{
		tBlocks = nullptr;
		usersCoins = nullptr;
		tBlocksCoins = nullptr;
		tBlocksCount = 0;
	}

	~TBlocksCollection()
	{
		delete[] tBlocks;
		delete[] usersCoins;
		delete[] tBlocksCoins;
	}

	void readFileTBlocks();
	void createTBlock();
	void writeTBlocksToBinaryFile() const;
	void makeTransaction(const User& sender, const User& receiver, double coinsToSend);
	double getUserCoins(unsigned int userId) const;
	void readUsersCoins(const User* users, unsigned int usersCount);
	void printTBlocksInfo() const;
	void printUsersCoinsInfo(unsigned int usersCount) const;
	void readTBlocksCoins(const TransactionBlock* tBlocks, unsigned int tBlocksCount);
	double getTBlockCoins(const TransactionBlock& tBlock) const;
};

unsigned computeHash(const unsigned char* memory, int length);