#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DEPTH 8
#define HEURISTIC mobility - opp_mobility + board_score

const int weight[64] = { 6,-3, 4, 3, 3, 4,-3, 6,
                        -3,-4, 2,-1,-1, 2,-4,-3,
                         4, 2, 2, 0, 0, 2, 2, 4,
                         3,-1, 0, 3, 3, 0,-1, 3,
                         3,-1, 0, 3, 3, 0,-1, 3,
                         4, 2, 2, 0, 0, 2, 2, 4,
                        -3,-4, 2,-1,-1, 2,-4,-3,
                         6,-3, 4, 3, 3, 4,-3, 6
                        };

void printboard(int board[][8]);
int flip(int row,int col,int flip,int color,int board[][8]);

int alpha_beta_cut(int alpha,int beta,int color,int board[][8],int depth){
  int opp_color = color ^ 3;
  int mobility = 0;
  int opp_mobility = 0;
  int board_score = 0;
  //int *temp_board = malloc( 64*sizeof(int) );
  int temp_board[8][8];
  memcpy(temp_board, *board,64*sizeof(int) );
  /*At the end of searching,return h(p)*/
  if(depth == DEPTH){
    /*computing board score*/
    for(int i = 0;i<64;i++){
      if( *(*board + i) == color )
        board_score += weight[i];
      else if( *(*board + i) == opp_color )
        board_score -= weight[i];
    }
    /*computing mobility*/
    for(int i = 0;i<8;i++){
      for(int j = 0;j<8;j++){
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
  for(int i = 0;i<8;i++){
    for(int j = 0;j<8;j++){
      if( board[i][j] == 0 && flip(i,j,1,color,temp_board) ){//change board
        t = -alpha_beta_cut(-beta,-m,opp_color,temp_board,depth + 1 );
        if(m >= beta)
          return m; //cut-off
        memcpy(temp_board, *board,64*sizeof(int) );//restore the board;
      }
    }
  }
}


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
      int alpha = -9999;
      int beta = 9999;
      int depth = 0;
      int move_row = -1;
      int move_col = -1;
      
      int temp_board[8][8];
      memcpy(temp_board, *board,64*sizeof(int) );


      int m = alpha;
      int t;
      for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
          if( board[i][j] == 0 && flip(i,j,1,com_color,temp_board) ){
            t = -alpha_beta_cut(-beta,-m,color,temp_board,depth + 1 );
            pass_flag = 0;
          
            if( t > m){
            //value is used
              move_row = i;
              move_col = j;
              m = t;
            }          
            memcpy(temp_board, *board,64*sizeof(int) );
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


      /*
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
      */
      
    }
  }


}

