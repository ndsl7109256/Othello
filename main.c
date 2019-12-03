#include <stdio.h>
#include <stdlib.h>

void printboard(int board[][8]);

unsigned long long board[3];//0:null 1:black 2:white

int flip(int row,int col,int flip,int color,int board[][8]){
  int opp_color = color ^ 3;//if color = (1,2) opp = (2,1)
  int legal = 0;

  /*check empty*/
  if(board[row][col] != 0){
    printf("has stone on it\n");
    return 0;//illegal
  }


  /*Up*/
  if( board[row - 1][col] == opp_color ){
    for(int i = row - 2;i>=0;i--){
      if( board[i][col] == 0 )
        break;
      if( board[i][col] == color ){
        legal = 1;
        if( !flip ){
          printf("AA\n");
          return legal;
        }
        for(int j = i + 1;j<row;++j){
          board[j][col] = color;
          //printf("%d %d is %d\n",j,col,color);
        }
        break;
      }
    }  
  }
  
  /*Down*/
  if( board[row + 1][col] == opp_color ){
    for(int i = row + 2;i<=7;i++){
      if( board[i][col] == 0)
        break;
      if( board[i][col] == color ){
        legal = 1;
        if( !flip ){
          printf("AA\n");
          return legal;
        }
        for(int j = i - 1;j>row;--j){
          board[j][col] = color;
          //printf("%d %d is %d\n",j,col,color);
        }
        break;
      }
    }
  }
  /*Right*/
  if( board[row][col + 1] == opp_color ){
    for(int i = col + 2;i<=7;i++){
      if( board[row][i] == 0)
        break;
      if( board[row][i] == color ){
        legal = 1;
        if( !flip ){
          printf("AA\n");
          return legal;
        }
        for(int j = i - 1;j>col;--j){
          board[row][j] = color;
          //printf("%d %d is %d\n",j,col,color);
        }
        break;
      }
    }
  }

  /*Left*/
  if( board[row][col - 1] == opp_color ){
    for(int i = col - 2;i>=0;i--){
      if( board[row][i] == 0)
        break;
      if( board[row][i] == color ){
        legal = 1;
        if( !flip ){
          printf("AA\n");
          return legal;
        }
        for(int j = i + 1;j<col;++j){
          board[row][j] = color;
          //printf("%d %d is %d\n",j,col,color);
        }
        break;
      }
    }
  }
  
  /*Upper Right*/
  if( board[row-1][col+1] == opp_color ){
    for(int i = 2;(row - i) >= 0 && (col + i) <=7 ;++i){
      if( board[row - i][col + i] == 0)
        break;
      if( board[row - i][col + i] == color ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(int j = i-1;j>0;--j){
          board[row-j][col+j] = color;
        }
        break;
      }
    }
  }
  
  /*Upper Left*/
  if( board[row-1][col-1] == opp_color ){
    for(int i = 2;(row - i) >= 0 && (col - i) >= 0 ;++i){
      if( board[row - i][col - i] == 0)
        break;
      if( board[row - i][col - i] == color ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(int j = i-1;j>0;--j){
          board[row-j][col-j] = color;
        }
        break;
      }
    }
  }

  
  /*Bottom Right*/
  if( board[row+1][col+1] == opp_color ){
    for(int i = 2;(row + i) <= 7 && (col + i) <=7 ;++i){
      if( board[row + i][col + i] == 0)
        break;
      if( board[row + i][col + i] == color ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(int j = i-1;j>=0;--j){
          board[row+j][col+j] = color;
        }
        break;
      }
    }
  }

  /*Bottom Left*/
  if( board[row+1][col-1] == opp_color ){
    for(int i = 2;(row + i) <= 7 && (col - i) >= 0 ;++i){
      if( board[row + i][col - i] == 0)
        break;
      if( board[row + i][col - i] == color ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(int j = i-1;j>0;--j){
          board[row+j][col-j] = color;
        }
        break;
      }
    }
  }
  
}


void printboard(int board[][8]){
  printf("  | 0 1 2 3 4 5 6 7\n");
  printf("-------------------\n");
  for(int i = 0;i<8;i++){
    printf("%d | ",i);
    for(int j = 0;j<8;j++){
      printf("%d ",board[i][j]);
    }
    printf("\n");
  }
}

void init(){
  
  
}

int main(){
  int board[8][8];
  for(int i = 0;i<64;i++){
    *(*board+i) = 0;
  }
  board[3][3] = 2;
  board[4][4] = 2;
  board[3][4] = 1;
  board[4][3] = 1;
  printboard(board);
  int row,col;
  int turn = 1;
  printf("turn is %d\n",turn);
  while(scanf("%d %d",&row,&col) ){
    flip(row,col,1,turn,board);
    board[row][col] = turn;
    printboard(board);
    turn = turn ^ 3;
    printf("turn is %d\n",turn);
  }
}

