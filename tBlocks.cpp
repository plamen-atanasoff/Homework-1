//#include <iostream>
//#include <fstream>
//
//#include "tBlocks.h"
//
//#include "constVariables.h"
//
//unsigned computeHash(const unsigned char* memory, int length) {
//	unsigned hash = 0xbeaf;
//
//	for (int c = 0; c < length; c++) {
//		hash += memory[c];
//		hash += hash << 10;
//		hash ^= hash >> 6;
//	}
//
//	hash += hash << 3;
//	hash ^= hash >> 11;
//	hash += hash << 15;
//	return hash;
//}
//
//void TBlocksCollection::readFileTBlocks()
//{
//	std::ifstream file(TBLOCKS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//		std::cout << "File cannot be opened!" << std::endl;
//		createTBlock();
//		return;
//	}
//
//	size_t fileSize = getSize(file);
//	if (fileSize == 0)
//	{
//		std::cout << "File is empty!" << std::endl;
//		createTBlock();
//		return;
//	}
//
//	file.read((char*)&tBlocksCount, sizeof(tBlocksCount));
//	tBlocks = new TransactionBlock[tBlocksCount];
//	file.read((char*)tBlocks, tBlocksCount * sizeof(*tBlocks));
//
//	file.close();
//}
//
//void TBlocksCollection::writeTBlocksToBinaryFile() const
//{
//	std::ofstream file(TBLOCKS_FILE_NAME, std::ios::binary);
//	if (!file.is_open())
//	{
//		std::cout << "File cannot be opened!" << std::endl;
//		return;
//	}
//
//	file.write((const char*)&tBlocksCount, sizeof(tBlocksCount));
//	file.write((const char*)tBlocks, tBlocksCount * sizeof(*tBlocks));
//
//	file.close();
//}
//
//void TBlocksCollection::createTBlock()
//{
//	unsigned int tBlockId = tBlocksCount++;
//	TransactionBlock* temp = new TransactionBlock[tBlocksCount];
//
//	// for loop until the last one existing
//	for (int i = 0; i < tBlocksCount - 1; ++i)
//	{
//		temp[i] = tBlocks[i];
//	}
//
//	temp[tBlockId].id = tBlockId;
//	temp[tBlockId].validTransactions = 0;
//
//	if (tBlockId == 0)
//		temp[tBlockId].prevBlockId = tBlockId;
//	else
//	{
//		temp[tBlockId].prevBlockId = tBlockId - 1;
//		// what should be the first argument of computeHash?
//		temp[tBlockId].prevBlockHash = computeHash((const unsigned char*)(&tBlocks[tBlockId - 1]), sizeof(tBlocks[tBlockId - 1]));
//	}
//
//	delete[] tBlocks;
//	tBlocks = temp;
//
//	writeTBlocksToBinaryFile();
//}
//
////double Identifiers::getUserCoins(unsigned int userId) const
////{
////	// validation ?
////	double totalCoins = 0;
////	for (int i = 0; i < tBlocksCount; ++i)
////	{
////		for (int j = 0; i < tBlocks[i].validTransactions; ++j)
////		{
////			//coins received
////			if (userId == tBlocks[i].transactions[j].receiver)
////				totalCoins += tBlocks[i].transactions[j].coins;
////			//coins sent
////			if (userId == tBlocks[i].transactions[j].sender)
////				totalCoins -= tBlocks[i].transactions[j].coins;
////		}
////	}
////
////	return totalCoins;
////}
//
////void Identifiers::makeTransaction(unsigned int senderId, unsigned int receiverId, double coinsToSend)
////{
////	if (senderId != 0)
////	{
////		int senderIndex = getUserIndex(senderId);
////		double senderCoins = getUserCoins(senderId);
////		// thats not the right way to compare doubles
////		if (senderCoins < coinsToSend)
////		{
////			std::cout << "User doesn't have enough money!" << std::endl;
////			return;
////		}
////	}
////
////	// do I need this ?
////	if (tBlocksCount == 0)
////		createTBlock();
////
////	if (tBlocks[tBlocksCount - 1].validTransactions == MAX_VALID_TRANSACTIONS)
////		createTBlock();
////
////	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].sender = senderId;
////	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].receiver = receiverId;
////	tBlocks[tBlocksCount - 1].transactions[tBlocks[tBlocksCount - 1].validTransactions].coins = coinsToSend;
////	// set time with <ctime>
////
////	// make it better
////	std::cout << "Sender sent " << coinsToSend << " coins to receiver succesfully!" << std::endl;
////
////	tBlocks[tBlocksCount - 1].validTransactions++;
////}
//
//size_t getSize(std::ifstream& file)
//{
//	unsigned int currentPos = file.tellg();
//	file.seekg(0, std::ios::end);
//	size_t size = file.tellg();
//	file.seekg(currentPos, std::ios::beg);
//
//	return size;
//}