#include "coins.h"

void CoinsCollection::printUsersCoinsInfo(unsigned int usersCount) const
{
	for (int i = 0; i < usersCount; ++i)
	{
		if (usersCoins[i].id == 0)
			continue;
		std::cout << usersCoins[i].id << " " << usersCoins[i].coins << "\n";
	}
	std::cout << std::endl;
}

void CoinsCollection::printTBlocksCoinsInfo(unsigned int tBlocksCount) const
{
	for (int i = 0; i < tBlocksCount; ++i)
	{
		std::cout << tBlocksCoins[i].id << " " << tBlocksCoins[i].coins << "\n";
	}
	std::cout << std::endl;
}

void CoinsCollection::removeUser(unsigned int userIndex, unsigned int usersCount)
{
	Coins* temp = new Coins[usersCount];
	for (int i = 0; i < userIndex; i++)
	{
		temp[i] = usersCoins[i];
	}
	for (int i = userIndex; i < usersCount; i++)
	{
		temp[i] = usersCoins[i + 1];
	}

	delete[] usersCoins;
	usersCoins = temp;
}

void CoinsCollection::addUserCoins(unsigned int userId, unsigned int usersCount)
{
	Coins* temp = new Coins[usersCount];
	for (int i = 0; i < usersCount - 1; ++i)
	{
		temp[i] = usersCoins[i];
	}
	temp[usersCount - 1].id = userId;
	temp[usersCount - 1].coins = 0.0;

	delete[] usersCoins;
	usersCoins = temp;
}

void CoinsCollection::addTBlockCoins(unsigned int tBlockId, unsigned int tBlocksCount)
{
	Coins* temp = new Coins[tBlocksCount];
	// validation ?
	for (int i = 0; i < tBlocksCount - 1; ++i)
	{
		temp[i].id = tBlocksCoins[i].id;
		temp[i].coins = tBlocksCoins[i].coins;
	}

	temp[tBlocksCount - 1].id = tBlockId;
	temp[tBlocksCount - 1].coins = 0.0;

	delete[] tBlocksCoins;
	this->tBlocksCoins = temp;
}

void CoinsCollection::makeTransactionUsers(unsigned int senderInd, unsigned int receiverInd, double coins)
{
	usersCoins[senderInd].coins -= coins;
	usersCoins[receiverInd].coins += coins;
}

void CoinsCollection::makeTransactionTBlocks(unsigned int tBlockId, double coins)
{
	tBlocksCoins[tBlockId].coins += coins;
}