# AI Tic Tac Toe

A CLI Tic-Tac-Toe game build with a Min-Max Algorithm.


## Installation

```bash
cmake .
make
```
## Usage

Two human players:
```bash
./Tic-Tac-Toe 0
```
Human players vs AI:  (memfile.txt is the trained memory)
```bash
./Tic-Tac-Toe 1 memfile.txt
```
Training, you can train from 0 or use a pre trained memory file.
```bash
./Tic-Tac-Toe 2 max_training_matchs memfile_to_save.txt
example:	./Tic-Tac-Toe 2 20000 memory.txt
```

