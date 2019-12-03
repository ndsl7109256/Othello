#include <stdio.h>
#include <stdlib.h>

void printboard(int board[][8]);

unsigned long long board[3];//0:null 1:black 2:white

int flip(int row,int col,int flip,int color,int board[][8]){
  int opp_color = color ^ 3;//if color = (1,2) opp = (2,1)
  int legal = 0;
  printf("opp:%d\n",opp_color);

  /*check empty*/
  if(board[row][col] != 0){
    printf("has stone on it\n");
    return 0;//illegal
  }


  /*Up*/
  if( board[row - 1][col] == opp_color ){
    printf("RRR\n");
    for(int i = row - 2;i>0;i--){
      if( board[i][col] == color ){
        legal = 1;
        if( !flip ){
          printf("AA\n");
          return legal;
        }
        for(int j = i + 1;j<row;++j){
          board[j][col] = color;
          printf("%d %d is %d\n",j,col,color);
        }
      }
    }  
  }

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
  board[3][3] = 1;
  board[4][4] = 1;
  board[3][4] = 2;
  board[4][3] = 2;
  printboard(board);
  int row,col; 
  while(scanf("%d %d",&row,&col) ){
    flip(row,col,1,1,board);
  }
}

