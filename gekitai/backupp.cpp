#include <iostream>
#include<ctype.h>
#include<cstring>
using namespace std;
const int N=6; //board size
const int P = 8; //number of pieces per player
const int L = 3; //number of pieces required to form a line
// y = i, x = j

//added fuction to swap player
char swap(char player){
    if(player == 'X')
        return 'O';
    else
        return 'X';
}

//just use to return is its a valid position
bool is_valid_move(char board[][N], char player, int y, int x){
    return ( y>=0 && y< N && x>=0 && x< N && board[y][x] == '.');
}
//counter to check total piece on board
int pieces_on_board(char board[][N], char player){
    int x =0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if(board[i][j] == player)
                x++;
        }
    return x;
}
//check if the board hv 3 piece on a line
bool pieces_in_line(char board[][N], char player){
    int flag1 = 0;
    int newi[4] = {0,1,1,1};
    int newj[4] = {1,1,0,-1};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (board[i][j] == player)
                for (int x=0; x<4; x++) {
                    if (((i + newi[x]*2>-1) && (i + newi[x]*2 < N)) && ((j + newj[x]*2>-1) && (j + newj[x]*2 < N)))
                    if ((board[i + newi[x]][j + newj[x]] == player)&&(board[i + newi[x]*2][j + newj[x]*2] == player)) {
                        flag1 = 1;
                        break;
                    }
                }
        }
    return (flag1 == 1);
}

void move(char board[][N], char player, int y, int x) {
    board[y][x] = player;
    int newi[8] = {-1, -1, -1, 0, 1, 1, 1, 0};//direction arrays
    int newj[8] = {-1, 0, 1, 1, 1, 0, -1, -1};//direction arrays
    char player1 = 'X';
    char player2 = 'O';
    char empty = '.';
    board[y][x] = player;
    for (int k = 0; k < 8; k++) {
        if (((y + newi[k]*2>-1) && (y + newi[k]*2 < N)) && ((x + newj[k]*2>-1) && (x + newj[k]*2 < N)) && ((y + newi[k]>-1) && (y + newi[k] < N)) && ((x + newj[k]>-1) && (x + newj[k] < N))) {
            cout << "Nd do something" << k << "\n";
            if(board[y + newi[k]][x + newj[k]] == player2 ||board[y + newi[k]][x + newj[k]] == player1){
                if(board[y + newi[k]*2][x + newj[k]*2] == player2 ||board[y + newi[k]*2][x + newj[k]*2] == player1){
                    cout << "Stuck" << k << "\n";
                } else{
                    cout << "Push! " << k << "\n";
                    board[y + newi[k] * 2][x + newj[k] * 2] = board[y + newi[k]][x + newj[k]];
                    board[y + newi[k]][x + newj[k]] = '.';
                }
            }
        }else {
            if((board[y + newi[k]][x + newj[k]] == player2 ||board[y + newi[k]][x + newj[k]] == player1 )&& (((y + newi[k]>-1) && (y + newi[k] < N)) && ((x + newj[k]>-1) && (x + newj[k] < N))))
                board[y + newi[k]][x + newj[k]] = empty;
            cout << "boarder so no need" << k << "\n";
        }
    }
}

void print(char board[][N]){
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N+1; j++) {
            if (i == 0 && j == 0)
                cout << "   ";
            if ((j==0&&i>0)||(j>0&&i==0)) {
                if (i == 0 && j > 0)
                    cout << (char) (64 + j) << " ";
                else if (i > 0 && j == 0) {
                    if(N<10)
                        cout << " " << (char) (48 + i) << " ";
                    else
                        cout << (char) (48 + i) << " ";
                }
            } else {
                if (i > 0 && j > 0)
                cout << board[i - 1][j - 1] << " ";
            }
        }
        cout << '\n';
    }
}

int main() {
    char board[N][N];
    for(int i=0; i<N;i++)
        for (int j = 0; j < N; j++) {
            board[i][j] = '.';
        }

    char player = 'X';
    int flag=0;
    int counter = 1;
    //use a while loop to check input valid
    while(1){
        cout << "Round " << counter << ": \n";
        counter ++;
        print(board);
        int inputi, inputj = 0;
        while (1) {
            char inputx;
            int inputy;
            cout << "Player " << player << "'s turn: " ;
            cin >> inputx >> inputy;
            if(inputx >= 'a')
                inputj = inputx - 'a';
            else
                inputj = inputx - 'A';
            inputi = inputy-1;
            if(inputi<N &&inputj<N) {
                int checkvalid = 0;
                checkvalid = is_valid_move(board, player, inputi, inputj);
                if (checkvalid > 0)
                    break;
                else
                    cout << "Invalid move! \n";
            }else
                cout << "Invalid move! \n";
        }
        move(board, player, inputi, inputj);
        if(pieces_in_line(board, player) == true)
            break;
        if(pieces_on_board(board, player) >= N)
            break;
       player = swap(player);
    }
    cout << "Game over:\n";
    print(board);
    player = swap(player);
    if(pieces_in_line(board, player) == true)
        cout << "Draw game!";
        else {
        player = swap(player);
        cout << "Player " << player << " wins!";
    }
    return 0;
}
