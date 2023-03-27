//#pragma once
//
//const char* TBLOCKS_FILE_NAME = "blocks.dat";
//const unsigned int MAX_VALID_TRANSACTIONS = 16;
//
//struct Transaction {
//	unsigned sender;
//	unsigned receiver;
//	double coins;
//	long long time;
//};
//
//struct TransactionBlock {
//	unsigned id;
//	unsigned prevBlockId;
//	unsigned prevBlockHash;
//	int validTransactions;
//	Transaction transactions[1];
//};
//
//struct TBlocksCollection
//{
//	TransactionBlock* tBlocks;
//	unsigned int tBlocksCount;
//
//	TBlocksCollection()
//	{
//		tBlocks = nullptr;
//		tBlocksCount = 0;
//	}
//
//	~TBlocksCollection()
//	{
//		delete[] tBlocks;
//	}
//
//	void readFileTBlocks();
//	void createTBlock();
//	void writeTBlocksToBinaryFile() const;
//};
//
//size_t getSize(std::ifstream& file);
//unsigned computeHash(const unsigned char* memory, int length);