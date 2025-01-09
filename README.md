# TicTacToe
TicTacToe Game

Key Functionalities:

Game Initialization:
The main() function initializes the game, collects player names, and assigns symbols (X or O) based on user input.
Players can choose between multiplayer mode or playing against the computer.

Game Board:
A 3x3 grid is represented by the global board array.

Functions:
resetBoard() initializes the board to an empty state.

printBoard() displays the current board state with gridlines.

checkFreeSpaces() counts the remaining empty cells on the board.

Player and Computer Moves:
playerMove(int x, int y, char playerSymbol): Updates the board with the player's move at the specified coordinates.

computerMove(char computerSymbol): Makes a computer move by placing its symbol in the first available cell.
Input Validation:

isSpaceFree(int x, int y): Checks if a given cell is within bounds and unoccupied.
Win/Tie Conditions:

checkWinner(): Checks for all possible winning conditions (horizontal, vertical, diagonal).
If the board is full without a winner, the game ends in a tie.
Gameplay Loop:

Alternates turns between players (or player and computer).
Prompts for valid moves and ensures illegal moves (out of bounds or on occupied cells) are corrected.
Endgame:

Displays the winner or declares a tie when the game concludes.
Observations:
Single-Player Mode: The computer plays a simple strategy by filling the first empty cell it finds.
Input Handling: The program ensures valid input for coordinates and prevents overwriting cells.
