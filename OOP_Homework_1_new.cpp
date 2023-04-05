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
	Controller ctr;

	//ctr.uCollection->printUsers();
	//ctr.tCollection->printTBlocksInfo();

	//ctr.cCollection->printUsersCoinsInfo(ctr.uCollection->usersCount);
	//ctr.cCollection->printTBlocksCoinsInfo(ctr.tCollection->tBlocksCount);

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
		else if (strcmp(command, "verify-transactions") == 0)
		{
			ctr.tCollection->verifyTBlocks();
		}
		else if (strcmp(command, "wealthiest-users") == 0)
		{
			ctr.writeRichestUsers();
		}
		else if (strcmp(command, "biggest-blocks") == 0)
		{
			ctr.writeBiggestBlocks();
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

	//ctr.uCollection->printUsers();
	//ctr.tCollection->printTBlocksInfo();

	//ctr.cCollection->printUsersCoinsInfo(ctr.uCollection->usersCount);
	//ctr.cCollection->printTBlocksCoinsInfo(ctr.tCollection->tBlocksCount);
}
