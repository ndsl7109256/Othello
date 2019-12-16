#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long board[3];//0 null 1 black 2 white

#define DEPTH 7
#define HEURISTIC mobility*80 - opp_mobility*90 + board_score

/*const int weight[64] = { 6,-3, 4, 3, 3, 4,-3, 6,
                        -3,-4, 2,-1,-1, 2,-4,-3,
                         4, 2, 2, 0, 0, 2, 2, 4,
                         3,-1, 0, 3, 3, 0,-1, 3,
                         3,-1, 0, 3, 3, 0,-1, 3,
                         4, 2, 2, 0, 0, 2, 2, 4,
                        -3,-4, 2,-1,-1, 2,-4,-3,
                         6,-3, 4, 3, 3, 4,-3, 6
                        };
*/

const int weight[64]={120,-20, 20,  5,  5, 20,-20,120,
              -20,-40, 15, -5, -5, 15,-40,-20,
               15, 15, 15,  3,  3, 15, 15, 15,
                5, -5,  3, 20, 20,  3, -5,  5,
                5, -5,  3, 20, 20,  3, -5,  5,
               15, 15, 15,  3,  3, 15, 15, 15,
              -20,-40, 15, -5, -5, 15,-40,-20,
              120,-20, 20,  5,  5, 20,-20,120};



int countcolor(int color,unsigned long long *board){
  int number = 0;
  unsigned long long a = 1;
  for(int i = 0;i<64;i++){
    if( board[color] & a<<i )
      ++number;
  }
  return number;
}

void printboard(unsigned long long *board){
  unsigned long long bit = 1;
  printf("   0 1 2 3 4 5 6 7 \n");
  printf("--------------------\n");
  for(int i = 0;i < 64;i++){
    if(i%8 == 0)
      printf("%d| ",i/8);
    if( board[1] & bit<<(63-i) )
      printf("1 ");
    else if( board[2] & bit<<(63-i) )
      printf("2 ");
    else if( board[0] & bit<<(63-i) )
      printf("0 ");
    else
      printf("# ");
    if(i%8 == 7)
      printf("\n");
  }

/*  printf("\n");

  for(int i = 0;i < 64;i++){
    if(i%8 == 0)
      printf("%d| ",i/8);
    if( board[0] & bit<<(63-i) )
      printf("0 ");
    else
      printf("# ");
    if(i%8 == 7)
      printf("\n");
  }

  printf("\n");
  for(int i = 0;i < 64;i++){
    if(i%8 == 0)
      printf("%d| ",i/8);
    if( board[2] & bit<<(63-i) )
      printf("2 ");
    else
      printf("# ");
    if(i%8 == 7)
      printf("\n");
  }
  
  printf("\n");
  for(int i = 0;i < 64;i++){
    if(i%8 == 0)
      printf("%d| ",i/8);
    if( board[1] & bit<<(63-i) )
      printf("1 ");
    else
      printf("# ");
    if(i%8 == 7)
      printf("\n");
  }

  */
  printf("\n");
}

unsigned long long bit(int row,int col){
  unsigned long long a = 1;
  return a << (( (7-row)<<3)+( (7-col) ));
}

int flip(int row,int col,int flip,int color,unsigned long long *board){
  int legal = 0;
  int opp_color = color ^ 3;
  unsigned long long temp_board[3];
  int i,j;
  temp_board[color] = board[color];
  temp_board[opp_color] = board[opp_color];
  
  if( board[1] & bit(row,col) || board[2] & bit(row,col) )
    return 0; //has stone on it
  
  /*Up*/
  if( bit(row - 1,col) & board[opp_color] ){
    for(i = row - 2;i>=0;i--){
      if( board[0] & bit(i,col) )//null
        break;
      if( bit(i,col) & board[color] ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(j = i + 1;j<row;++j){
          //board[j][col] = color;
          board[color] |= bit(j,col);
          board[opp_color] &= ~bit(j,col);
          //printf("%d %d is %d\n",j,col,color);
        }
        break;
      }
    }
  }

  /*Down*/
  if( bit(row + 1,col) & board[opp_color] ){
    for(i = row + 2;i<=7;i++){
      if( board[0] & bit(i,col) )
        break;
      if( bit(i,col) & board[color] ){
        legal = 1;
        if( !flip ){
          //printf("AA\n");
          return legal;
        }
        for(j = i - 1;j>row;--j){
          //board[j][col] = color;
          board[color] |= bit(j,col);
          board[opp_color] &= ~bit(j,col);
        }
        break;
      }
    }
  }
  /*Right*/
  if( bit(row,col + 1) & board[opp_color] ){
    for(i = col + 2;i<=7;i++){
      if( board[0] & bit(row,i) )
        break;
      if( bit(row,i) & board[color] ){
        legal = 1;
        if( !flip ){
          //printf("AA\n");
          return legal;
        }
        for(j = i - 1;j>col;--j){
          //board[row][j] = color;
          board[color] |= bit(row,j);
          board[opp_color] &= ~bit(row,j);
        }
        break;
      }
    }
  }

  /*Left*/
  if( bit(row,col - 1) & board[opp_color] ){
    for(i = col - 2;i>=0;i--){
      if( board[0] & bit(row,i) )
        break;
      if( bit(row,i) & board[color] ){
        legal = 1;
        if( !flip ){
          //printf("AA\n");
          return legal;
        }
        for(j = i + 1;j<col;++j){
          //board[row][j] = color;
          board[color] |= bit(row,j);
          board[opp_color] &= ~bit(row,j);
        }
        break;
      }
    }
  }

  /*Upper Right*/
  if( bit(row-1,col+1) & board[opp_color] ){
    for(i = 2;(row - i) >= 0 && (col + i) <=7 ;++i){
      if( board[0] & bit(row-i,col+i) )
        break;
      if( bit(row - i,col + i) & board[color] ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(j = i-1;j>0;--j){
          //board[row-j][col+j] = color;
          board[color] |= bit(row-j,col+j);
          board[opp_color] &= ~bit(row-j,col+j);
        }
        break;
      }
    }
  }

  /*Upper Left*/
  if( bit(row-1,col-1) & board[opp_color] ){
    for( i = 2;(row - i) >= 0 && (col - i) >= 0 ;++i){
      if( board[0] & bit(row - i,col - i) )
        break;
      if( bit(row - i,col - i) &  board[color] ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for( j = i-1;j>0;--j){
          //board[row-j][col-j] = color;
          board[color] |= bit(row-j,col-j);
          board[opp_color] &= ~bit(row-j,col-j);
        }
        break;
      }
    }
  }


  /*Bottom Right*/
  if( bit(row+1,col+1) & board[opp_color] ){
    for(i = 2;(row + i) <= 7 && (col + i) <=7 ;++i){
      if( board[0] & bit(row + i,col + i) )
        break;
      if( bit(row + i,col + i) & board[color] ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(j = i-1;j>=0;--j){
          //board[row+j][col+j] = color;
          board[color] |= bit(row+j,col+j);
          board[opp_color] &= ~bit(row+j,col+j);
        }
        break;
      }
    }
  }

  /*Bottom Left*/
  if( bit(row+1,col-1) & board[opp_color] ){
    for(i = 2;(row + i) <= 7 && (col - i) >= 0 ;++i){
      if( board[0] & bit(row + i,col - i) )
        break;
      if( bit(row + i,col - i) & board[color] ){
        legal = 1;
        if( !flip ){
          return legal;
        }
        for(j = i-1;j>0;--j){
          //board[row+j][col-j] = color;
          board[color] |= bit(row+j,col-j);
          board[opp_color] &= ~bit(row+j,col-j);
        }
        break;
      }
    }
  }

  if( legal ){
    board[color] |= bit(row,col);
    board[0] &= ~bit(row,col);
    
  }
  return legal;

}

int alpha_beta_cut(int alpha,int beta,int color,unsigned long long *board,int depth){
  int opp_color = color ^ 3;
  int mobility = 0;
  int opp_mobility = 0;
  int board_score = 0;
  int i,j;
  unsigned long long temp_board[3];
  memcpy(temp_board, board,3*sizeof( temp_board[0] ) );
  unsigned long long a = 1;
  /*At the end of searching,return h(p)*/
  if(depth == DEPTH){
    /*computing board score*/
    for(i = 0;i<64;i++){
      if(  a<<i & board[color] )
        board_score += weight[i];
      else if( a<<i & board[opp_color] )
        board_score -= weight[i];
    }
    /*computing mobility*/
    for(i = 0;i<8;i++){
      for(j = 0;j<8;j++){
        if( flip(i,j,0,color,temp_board) )
          ++mobility;
        if( flip(i,j,0,opp_color,temp_board) )
          ++opp_mobility;
      }
    }
    return HEURISTIC;/* ʕ •ᴥ•ʔ ʕ •ᴥ•ʔ  HEURISTIC  ʕ •ᴥ•ʔ ʕ •ᴥ•ʔ*/
  }
  int m = alpha;// hard initial value
  int t;
  for(i = 0;i<8;i++){
    for(j = 0;j<8;j++){
      if( ( bit(i,j) & board[0] )&& flip(i,j,1,color,temp_board) ){//change board
        t = -alpha_beta_cut(-beta,-m,opp_color,temp_board,depth + 1 );
        if(m >= beta)
          return m; //cut-off
        memcpy(temp_board, board,3*sizeof( temp_board[0] ) );//restore the board;
      }
    }
  }
}


int main(){
  int turn = 1;
  printf("player first 1,computer first 2\n");
  int first = 0;
  int color,com_color;
  if(first ){//computer first control black;
    com_color = 1;
    color = 2;
    turn = 2;
  }else{
    color = 1;
    com_color = 2;
    turn = 1;
  }
  

  board[2]=0x0000001008000000;
  board[1]=0x0000000810000000;
  board[0] = (~board[2]) & (~board[1]);

  printboard(board);
  int row,col;
  int move = 4;
  int pass = 0;

  


  while((move++) < 64){

    /*no move and end game*/
    if(pass == 2){
        printf("No move 88\n");
        break;
    }

    printf("\n///////\nturn of %d\n",turn);

    if(turn == 1){
      int pass_flag = 1;
      /*check pass or not*/
      for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
          if( flip(i,j,0,color,board ) )
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
        if( flip(row,col,1,color,board) ){
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
      int alpha = -99999;
      int beta = 99999;
      int depth = 0;
      int move_row = -1;
      int move_col = -1;

      unsigned long long temp_board[3];
      memcpy(temp_board,board,3*sizeof( temp_board[0] ) );


      int m = alpha;
      int t;
      for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
          if( ( bit(i,j) & board[0] ) && flip(i,j,1,com_color,temp_board) ){
            t = -alpha_beta_cut(-beta,-m,color,temp_board,depth + 1 );
            pass_flag = 0;

            if( t > m){
            //value is used
              move_row = i;
              move_col = j;
              m = t;
            }
            memcpy(temp_board, board,3*sizeof(temp_board[0]) );
          }
        }
      }


      if(pass_flag){
        printf("PASS %d %d\n",move_row,move_col);
        ++pass;
        turn = turn ^ 3;
        --move;
        continue;
      }
      pass = 0;
      if( flip(move_row,move_col,1,com_color,board) ){
          printboard(board);
          printf("move at %d %d\n",move_row,move_col);
          printf("1: %d 2: %d\n",countcolor(1,board),countcolor(2,board));
          turn = turn ^ 3;
      }else{
          printf("87 = = %d %d\n",move_row,move_col);
      }

    }
  }
}
