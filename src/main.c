#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

// Define difficulty level for mining
#define DIFFICULTY 4

// Block structure
typedef struct Block {
    int Index; // Index of the block in the blockchain
    char PreviousHash[65]; // Hash of the previous block
    time_t Timestamp; // Timestamp of the block creation
    char Data[256]; // Data stored in the block
    int m_Nonce; // Nonce used for mining (private member)
    char m_Hash[65]; // Hash of the current block (private member)
    struct Block* Next; // Pointer to the next block in the chain
} Block;

// Blockchain structure
typedef struct Blockchain {
    Block* Head; // Pointer to the head (first block) of the blockchain
    int Difficulty; // Difficulty level for mining
} Blockchain;

// Function to calculate the hash of a block
void CalculateHash(Block* block) {
    char input[1024];
    snprintf(input, sizeof(input), "%d%s%ld%s%d", block->Index, block->PreviousHash, block->Timestamp, block->Data, block->m_Nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(block->m_Hash + (i * 2), "%02x", hash[i]);
    }
    block->m_Hash[64] = '\0';
}

// Function to mine a block
void MineBlock(Block* block, int difficulty) {
    char target[65];
    memset(target, '0', difficulty);
    target[difficulty] = '\0';

    while (strncmp(block->m_Hash, target, difficulty) != 0) {
        block->m_Nonce++;
        CalculateHash(block);
    }
}

// Function to create a new blockchain with a genesis block
Blockchain* CreateBlockchain(int difficulty) {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->Head = (Block*)malloc(sizeof(Block));
    blockchain->Head->Index = 0;
    strcpy(blockchain->Head->PreviousHash, "0");
    blockchain->Head->Timestamp = time(NULL);
    strcpy(blockchain->Head->Data, "Genesis Block");
    blockchain->Head->m_Nonce = 0;
    CalculateHash(blockchain->Head);
    blockchain->Head->Next = NULL;
    blockchain->Difficulty = difficulty;
    return blockchain;
}

// Function to create a new block
Block* CreateBlock(int index, const char* previousHash, const char* data) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->Index = index;
    strcpy(block->PreviousHash, previousHash);
    block->Timestamp = time(NULL);
    strcpy(block->Data, data);
    block->m_Nonce = 0;
    CalculateHash(block);
    block->Next = NULL;
    return block;
}

// Function to add a block to the blockchain
void AddBlock(Blockchain* blockchain, Block* newBlock) {
    Block* latestBlock = blockchain->Head;
    while (latestBlock->Next != NULL) {
        latestBlock = latestBlock->Next;
    }
    newBlock->Index = latestBlock->Index + 1;
    strcpy(newBlock->PreviousHash, latestBlock->m_Hash);
    MineBlock(newBlock, blockchain->Difficulty);
    latestBlock->Next = newBlock;
}

// Function to validate the blockchain
int IsBlockchainValid(Blockchain* blockchain) {
    Block* currentBlock = blockchain->Head;
    Block* previousBlock = NULL;

    while (currentBlock != NULL) {
        Block hashBlock = *currentBlock;
        CalculateHash(&hashBlock);
        if (strcmp(currentBlock->m_Hash, hashBlock.m_Hash) != 0) {
            return 0;
        }
        if (previousBlock != NULL && strcmp(currentBlock->PreviousHash, previousBlock->m_Hash) != 0) {
            return 0;
        }
        previousBlock = currentBlock;
        currentBlock = currentBlock->Next;
    }
    return 1;
}

// Function to print the blockchain
void PrintBlockchain(Blockchain* blockchain) {
    Block* currentBlock = blockchain->Head;
    while (currentBlock != NULL) {
        printf("Index: %d\n", currentBlock->Index);
        printf("Previous Hash: %s\n", currentBlock->PreviousHash);
        printf("Timestamp: %ld\n", currentBlock->Timestamp);
        printf("Data: %s\n", currentBlock->Data);
        printf("Hash: %s\n", currentBlock->m_Hash);
        printf("Nonce: %d\n", currentBlock->m_Nonce);
        printf("------------------------------\n");
        currentBlock = currentBlock->Next;
    }
}

// Main function
int main() {
    srand(time(NULL));

    // Create a new blockchain with a difficulty level of 4
    Blockchain* blockchain = CreateBlockchain(DIFFICULTY);

    // Add blocks to the blockchain
    AddBlock(blockchain, CreateBlock(1, "", "Block 1 Data"));
    AddBlock(blockchain, CreateBlock(2, "", "Block 2 Data"));

    // Print the blockchain
    PrintBlockchain(blockchain);

    // Validate the blockchain
    if (IsBlockchainValid(blockchain)) {
        printf("Blockchain is valid.\n");
    } else {
        printf("Blockchain is invalid.\n");
    }

    return 0;
}
