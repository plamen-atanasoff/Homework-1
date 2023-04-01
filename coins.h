#pragma once

#include "users.h"
#include "tBlocks.h"

//change this
struct Coins
{
	unsigned int id;
	double coins;
};

struct CoinsCollection
{
	Coins* usersCoins;
	Coins* tBlocksCoins;

	CoinsCollection()
	{
		usersCoins = nullptr;
		tBlocksCoins = nullptr;
	}

	~CoinsCollection()
	{
		delete[] usersCoins;
		delete[] tBlocksCoins;
	}

	void printUsersCoinsInfo(unsigned int usersCount) const;
	void printTBlocksCoinsInfo(unsigned int tBlocksCount) const;
	void removeUser(unsigned int ind, unsigned int usersCount);

	void addUserCoins(unsigned int userId, unsigned int usersCount);
	void addTBlockCoins(unsigned int tBlockId, unsigned int tBlocksCount);

	void makeTransactionUsers(unsigned int senderInd, unsigned int receiverInd, double coins);
	void makeTransactionTBlocks(unsigned int tBlockId, double coins);
};