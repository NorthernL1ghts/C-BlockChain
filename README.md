# C-BlockChain

This project implements a basic blockchain written in the C programming language. The goal is to demonstrate fundamental blockchain concepts such as block creation, hashing, and linking blocks in a chain.

## Features

- Block Creation: Create blocks containing data, a hash, a previous block hash, and a timestamp.

- Hashing: SHA-256 hashing to ensure data integrity.

- Chain Validation: Basic validation to check the integrity of the blockchain.

- Simple Data Storage: Store arbitrary data in each block.

## Directory Structure

```bash
C-BlockChain/
├── src/
│ └── main.c
└── README.md
```

## Dependencies

This project uses standard C libraries and requires OpenSSL for SHA-256 hashing.

- On Debian/Ubuntu, you can install OpenSSL using:
  ```
  sudo apt-get install libssl-dev
  ```

## Tech Stack

- **Language:** C
- **Libraries:** Standard C libraries, OpenSSL (for SHA-256 hashing)
- **Compiler:** GCC

## Setup

- **Windows:** Run `Scripts/Win-GenerateProject.bat`
- **Linux:** Run `Scripts/GenerateProject.sh`

## Compilation

To compile the project, use `gcc`:

## How to Run

After compiling, run the executable:

```
./blockchain
```

## Sample Output

```bash
Block 0:
Data: Genesis Block
Hash: 5f4dcc3b5aa765d61d8327deb882cf99
Previous Hash: 0000000000000000
Timestamp: 1627565432

Block 1:
Data: Block 1 Data
Hash: 98f6bcd4621d373cade4e832627b4f6
Previous Hash: 5f4dcc3b5aa765d61d8327deb882cf99
Timestamp: 1627565492
```

# Key Functions

- CreateBlock: Creates a new block with specified data.

- CalculateHash: Computes the SHA-256 hash of the block.

- AddBlock: Adds a new block to the blockchain.

- ValidateChain: Checks the integrity of the blockchain.

## Future Enhancements

- Implement proof-of-work (PoW) for mining blocks.

- Add persistent storage for the blockchain.

- Network support to enable decentralized blockchain nodes.

## License

This project is licensed under the MIT License, which can be found here -> [LICENSE](LICENSE.md)

## Disclaimer

This is a simple educational project. It is not intended for production use or to serve as a secure blockchain implementation.
