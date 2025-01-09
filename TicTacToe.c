#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>



char board[3][3];

void resetBoard();
void printBoard();
int checkFreeSpaces();
bool isSpaceFree(int, int);
void playerMove(int, int, char);
void computerMove(char);
bool checkWinner();
void printWinner(char);
bool gameOver = false;


int main(){

    char player1Symbol; 
    char player2Symbol;
    char compSymobl; 
    int players;
    char player1Name[25];
    char player2Name[25];

 
    printf("Number of Players: ");
    scanf("%d", &players);

    // Clear buffer 
    while ((getchar()) != '\n');

    // If there more than one player
    if(players > 1){
        printf("Player 1:  ");
        fgets(player1Name, 25, stdin);
        // Remove the newline character from fgets input for Player 1
        player1Name[strcspn(player1Name, "\n")] = '\0';
        printf("Player 2:  ");
        fgets(player2Name, 25, stdin);
        // Remove the newline character from fgets input for Player 2
        player2Name[strcspn(player2Name, "\n")] = '\0';
    }
    else{
        printf("Player name:  ");
        fgets(player1Name, 25, stdin);
        // Remove the newline character from fgets input for Player 1
        player1Name[strcspn(player1Name, "\n")] = '\0';
    }

    if(players > 1){
        printf("%s select your Symbol: (X, O): ", player1Name);
        scanf(" %c", &player1Symbol);
        if(player1Symbol == 'X'){
            player2Symbol = 'O';
        }
        else{
            player2Symbol = 'X';
        }
    }
    else{
        printf("Select your Symbol: (X, O): ");
        scanf("%c", &player1Symbol);
        if(player1Symbol == 'X'){
            compSymobl = 'O';
        }
        else{
            compSymobl = 'X';
        }
    }

    int round = 0;
    while(!gameOver){

        // Versus Computers 
        if(players < 2){
            if(checkFreeSpaces() < 1){
                // if there are no avaiable spaces that means we have a tie
                gameOver = true;
                printBoard();
                printf("Tie");
                break;
            }
            int row;
            int column;
            printf("Board: \n");
            printBoard();
            // Players turn 
            if(round % 2 ==0){
                printf("%s's turn\n", player1Name);
                printf("Row: ");
                scanf("%d", &row); 
                printf("Column: ");
                scanf("%d", &column); 
            }
            // Computer Turn
            else{
                computerMove(compSymobl);
            }
            
            // Checking if User's move is legal 
            if(round % 2 ==0){
                if(!isSpaceFree(row,column)){

                    // Keep prompting player to select unoccupied coordinate if the play keeps choosing occupied coordinate 
                    while(true){
                
                        printBoard();
                        printf("Move is either out of bounds or aready occupied\n");
                        printf("Row: ");
                        scanf("%d", &row); 
                        printf("Column: ");
                        scanf("%d", &column); 

                        // Check to see if the new coordinates entered are also avaiable if not comense with player move and break out of loop 
                        if(isSpaceFree(row,column)){
                                playerMove(row,column, player1Symbol);
                                break;
                        }
                    }   
                }
                // If move was legal then proceed with player's move 
                playerMove(row,column, player1Symbol);
            }
            
            if(checkWinner()){
                if(round % 2 ==0){
                    printBoard();
                    printf("%s wins the Game!", player1Name);
                }
                else{
                    printBoard();
                    printf("Computer wins the Game!");
                
                }
                gameOver = true;
            }
            round++;
            
        }

        // If it's muplti player
        else{
            // Check to see if there are any availbe spaces on the board
            if(checkFreeSpaces() < 1){
                // if there are no avaiable spaces that means we have a tie
                gameOver = true;
                printBoard();
                printf("Tie");
                break;
            }
            int row;
            int column;
            printf("Board: \n");
            printBoard();
            if(round % 2 ==0){
                printf("%s's turn\n", player1Name);
            }
            else{
                printf("%s's turn\n", player2Name);
            }
            printf("Row: ");
            scanf("%d", &row); 
            printf("Column: ");
            scanf("%d", &column); 
        
            // If players selecs an occupied coordinate
            if(!isSpaceFree(row,column)){

                // Keep prompting player to select unoccupied coordinate if the play keeps choosing occupied coordinate 
                while(true){
                
                    printBoard();
                    printf("Move is either out of bounds or aready occupied\n");
                    printf("Row: ");
                    scanf("%d", &row); 
                    printf("Column: ");
                    scanf("%d", &column); 

                    // Check to see if the new coordinates entered are also avaiable if not comense with player move and break out of loop 
                    if(isSpaceFree(row,column)){
                        if(round % 2 ==0){
                            playerMove(row,column, player1Symbol);
                            }
                        else{
                            playerMove(row,column,player2Symbol);
                        }
                        break;
                    }
                }
            }
            else{
                if(round % 2 ==0){
                    playerMove(row,column, player1Symbol);
                }
                else{
                    playerMove(row,column,player2Symbol);
                }    
            }
            if(checkWinner()){
                if(round % 2 ==0){
                    printBoard();
                    printf("%s wins the Game!", player1Name);
                }
                else{
                    printBoard();
                    printf("%s wins the Game!", player2Name);
                
                }
                gameOver = true;
            }
            round++;
        }
    }
    return 0;
}

void resetBoard(){
    for(int i =0; i < sizeof(board)/sizeof(board[0]); i++){
        for(int j =0; j < sizeof(board)/sizeof(board[0]); j++){
            board[i][j] = '\0';
        }
    }
}

void printBoard(){
    printf("\n");
     for(int i =0; i < 3; i++){
        for(int j =0; j <  3; j++){
            if(board[i][j] == NULL){
               printf("   ");
            }
            else{
                printf(" %c ", board[i][j]);
            }
            if (j < 2){
                printf("|");
            }
        }
        printf("\n");
        if(i < 2){
            printf("---|---|---\n");
        }
    }
}

int checkFreeSpaces(){
    int freeSpaces = 0;
    for(int i =0; i < 3; i++){
        for(int j =0; j < 3; j++){
            if(board[i][j] == NULL){
                freeSpaces++;
            }
        }
    }
    return freeSpaces;
}

// Check is space is free or move is inbounds 
bool isSpaceFree(int x, int y){
    // check for outofbounds 
    if(x > 3 || x < 0 || y > 3 || y < 0 ){
        return false;
    }
    // check if space is avaible 
    if(board[x][y] == NULL){
        return true;
    }
    return false;
}

void playerMove(int x , int y, char playerSymbol){
    if(playerSymbol == 'X' ){
        board[x][y] = 'X';
    }
    else{
        board[x][y] = 'O';
    }
}


void computerMove(char computerSymbol) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == NULL) {
                if(computerSymbol == 'X'){
                    board[i][j] = 'X';
                }
                else{
                    board[i][j] = 'O';
                }
                return;
            }
        }
    }
}

bool checkWinner(){
    // List of all possible combinations 

    // Horizontal Wins 
    if((board[0][1] == 88 && board[0][1] == 88 && board[0][2] == 88)){
        gameOver = true;
        return true;
    }

    if((board[0][1] == 79 && board[0][1] == 79 && board[0][2] == 79)){
        if(board[0][1] == 79){
            printf("0,0\n");
        }
        if(board[0][1] == 79){
            printf("0,1\n");
        }
        if( board[0][2] == 79){
            printf("0,2\n");
        }
        gameOver = true;
        return true;
    }
    
    if((board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')){
        gameOver = true;
        return true;
    }

    if((board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')){
        gameOver = true;
        return true;
    }

    // Vertical Wins 
    if((board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')){
        gameOver = true;
        return true;
    }

    if((board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')){
        gameOver = true;
        return true;
    }

    if((board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')){
        gameOver = true;
        return true;
    }

    // Diagonal Wins 
    if((board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')){
        gameOver = true;
        return true;
    }

    if((board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')){
        gameOver = true;
        return true;
    }
    if((board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')){
        gameOver = true;
        return true;
    }
    
    else{
        gameOver = false;
        return false;
    }
}