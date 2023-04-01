// create and remove user, read and write users to file
// infinite loop when entering letter for money

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "controller.h"

const unsigned int MAX_NAME_LEN = 128;
const unsigned int MAX_COMMAND_LEN = 64;

void inputName(char* name)
{
	std::cout << "Enter name: ";
	std::cin >> name;
	std::cout << '\n';
}

void inputMoney(double& money)
{
	std::cout << "Enter sum: ";
	std::cin >> money;
	std::cout << '\n';
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Controller ctr;

	ctr.uCollection->printUsers();
	ctr.tCollection->printTBlocksInfo();

	ctr.cCollection->printUsersCoinsInfo(ctr.uCollection->usersCount);
	ctr.cCollection->printTBlocksCoinsInfo(ctr.tCollection->tBlocksCount);

	char command[MAX_COMMAND_LEN];
	do
	{
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cout << std::endl;

		if (strcmp(command, "create-user") == 0)
		{
			char name[MAX_NAME_LEN];
			double money;
			inputName(name);
			inputMoney(money);

			ctr.createUser(name, money);
		}
		else if (strcmp(command, "remove-user") == 0)
		{
			char name[MAX_NAME_LEN];
			inputName(name);

			ctr.removeUser(name);
		}
		else if (strcmp(command, "send-coins") == 0)
		{
			char senderName[MAX_NAME_LEN], receiverName[MAX_NAME_LEN];
			double coins;
			inputName(senderName);
			inputName(receiverName);
			inputMoney(coins);

			ctr.sendCoins(senderName, receiverName, coins);
		}
		else if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else
		{
			std::cout << "There is no such command!" << std::endl;
			std::cout << std::endl;
		}
	} while (strcmp(command, "exit") != 0);

	ctr.uCollection->printUsers();
	ctr.tCollection->printTBlocksInfo();

	ctr.cCollection->printUsersCoinsInfo(ctr.uCollection->usersCount);
	ctr.cCollection->printTBlocksCoinsInfo(ctr.tCollection->tBlocksCount);
}