#include <stdio.h>
#include <stdlib.h>

void printboard(int board[][8]);

unsigned long long board[3];//0:null 1:black 2:white

int flip(int row,int col,int flip,int color,int board[][8]){
  int opp_color = color ^ 3;//if color = (1,2) opp = (2,1)
  int legal = 0;

  /*check empty*/
  if(board[row][col] != 0){
    //printf("has stone on it\n");
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
          //printf("AA\n");
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
          //printf("AA\n");
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
          //printf("AA\n");
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
          //printf("AA\n");
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
  if( legal ){
    board[row][col] = color;
  }
  return legal;
}
int countcolor(int color,int board[][8]){
  int number = 0;
  for(int i = 0;i<64;i++){
    if( *(*board+i) == color )
      ++number;
  }
  return number;
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
  int color,opp_color;
  int turn = 1;
  int move = 4;
  int pass = 0;
  while((move++) < 64){

    printf("turn of %d\n",turn);

    if(turn == 1){
      int pass_flag = 1;
      /*check pass or not*/
      for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
          if( flip(i,j,0,turn,board ) )
            pass_flag = 0;//has legal move
        }
      }
      if(pass_flag){
        printf("PASS\n");
        ++pass;
        turn = turn ^ 3;
        --move;
        continue;
      }
      pass = 0;
      while( scanf("%d %d",&row,&col) ){
        if( row>7 || col > 7){
          printf("87= =\n");
          continue;
        }
        if( flip(row,col,1,turn,board) ){
          printboard(board);
          printf("1: %d 2: %d\n",countcolor(1,board),countcolor(2,board));
          turn = turn ^ 3;
          break;
        }else{
          printf("87 = =\n");
        }
      }
    }else if(turn == 2){
      int pass_flag = 1;
      /*check pass or not*/
      for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
          if( flip(i,j,0,turn,board) )
            pass_flag = 0;//has legal move
        }
      }
      if(pass_flag){
        printf("PASS\n");
        ++pass;
        turn = turn ^ 3;
        --move;
        continue;
      }
      pass = 0;
      while( scanf("%d %d",&row,&col) ){
        if( row>7 || col > 7){
          printf("87= =\n");
          continue;
        }
        if( flip(row,col,1,turn,board) ){
          printboard(board);
          printf("1: %d 2: %d\n",countcolor(1,board),countcolor(2,board));
          turn = turn ^ 3;
          break;
        }else{
          printf("87 = =\n");
        }
      }
    }
  }


}

