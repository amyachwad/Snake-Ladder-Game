//Snake and Ladder

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Element
{
  int number;
  char snake;
  char ladder;
  char symbols[4];
};
typedef struct Element Element;

struct Player
{
  char symbol;
  int moves;
  int laddersTaken;
  int snakeBites;
  int position;
  char remark[20];
};
typedef struct Player Player;

struct Board
{
  Element elements[100];
  Player players[4];
  int numberOfPlayers;
};
typedef struct Board Board;

void initializePlayers(Player arr[])
{
  char temp[] = {'A', 'J', '*', 'o'};
  int i;
  for(i =0 ; i < 4; i++)
  {
    arr[i].symbol = temp[i];
    arr[i].moves = 0;
    arr[i].laddersTaken = 0;
    arr[i].snakeBites = 0;
    arr[i].position = -1;
    strcpy(arr[i].remark , "Loses");
  }

}


void initializeElements(Element arr[])
{
  int i, j;
  for(i = 0; i < 100; i++)
  {
    arr[i].number = i+1;
    arr[i].ladder = ' ';//space
    arr[i].snake = ' ';//space
    for(j =0 ; j < 4; j++)
      arr[i].symbols[j]= ' ';//space
  }
}

void printElement(Element e)
{
  printf("[%3d%c%c%c%c%c%c]",e.number, e.ladder, e.snake, e.symbols[0], e.symbols[1], e.symbols[2], e.symbols[3]);
}

void drawBoard(Element arr[])
{
  printf("\n");
  int i,j;
  int x;

  x = 99;
  for(i =0 ; i < 10 ; i++) //10 rows
  {
    printf("\n");//row change
    for(j = 0; j < 10; j++)//10 cols
    {
      printf(" ");//space
      printElement(arr[x]);
      if(i%2 == 0)
        x--;
      else
        x++;
    }//for(j

    if(i %2 == 0)
      x-=9;
    else
      x-=11;
  }
  printf("\n");

}//drawBoard

void setupSnakes(Element arr[])
{//6 snakes

  //snake head 95; snake body 86,75,66,55,46; snake tail 35
  arr[94].snake = 148; // ö
  arr[85].snake = arr[74].snake = arr[65].snake = arr[54].snake= arr[45].snake= 177; // ¦
  arr[34].snake = 245; // )

  //snake head 92; snake body 89,72,69; snake tail 52
  arr[91].snake = 148; // ö
  arr[88].snake = arr[71].snake = arr[68].snake = 177; // ¦
  arr[51].snake = 245; // )

  //snake head 81; snake body 80; snake tail 61
  arr[80].snake = 148; // ö
  arr[79].snake= 177;  // ¦
  arr[60].snake = 245; // )

  //snake head 64; snake body 57,44,37; snake tail 24
  arr[63].snake = 148; // ö
  arr[56].snake = arr[43].snake = arr[36].snake = 177; // ¦
  arr[23].snake = 245; // )

  //snake head 50; snake body 31,30; snake tail 11
  arr[49].snake = 148; // ö
  arr[30].snake = arr[29].snake = 177; // ¦
  arr[10].snake = 245; // )

  //snake head 42; snake body 39,22; snake tail 19
  arr[41].snake = 148; // ö
  arr[38].snake = arr[21].snake = 177; // ¦
  arr[18].snake = 245; // )
}

void setupLadders(Element arr[])
{//6 ladders

  //ladder top 93;  ladder body 88,73; ladder bottom 68
  arr[92].ladder = 203; // -
  arr[87].ladder  = arr[72].ladder = 206; // +
  arr[67].ladder = 202; // -

  //ladder top 82;  ladder body 79,62; ladder bottom 59
  arr[81].ladder = 203; // -
  arr[78].ladder  = arr[61].ladder = 206; // +
  arr[58].ladder = 202; // -


  //ladder top 60;  ladder body 41, 40,21; ladder bottom 20
  arr[59].ladder = 203; // -
  arr[40].ladder  = arr[39].ladder = arr[20].ladder= 206; // +
  arr[19].ladder = 202; // -

  //ladder top 54;  ladder body 47,34; ladder bottom 27
  arr[53].ladder = 203; // -
  arr[46].ladder = arr[33].ladder = 206; // +
  arr[26].ladder = 202; // -


  //ladder top 49;  ladder body 32,29; ladder bottom 12
  arr[48].ladder = 203; // -
  arr[31].ladder  = arr[28].ladder = 206; // +
  arr[11].ladder = 202; // -

  //ladder top 25;  ladder body 16; ladder bottom 5
  arr[24].ladder = 203; // -
  arr[15].ladder = 206; // +
  arr[4].ladder  = 202; // -
}

int movePeg(Board * board, int indx,  int jump)
{
  static int finished = 1;
  int new_pos, old_pos;

  old_pos = board->players[indx].position;
  new_pos = old_pos + jump;

  board->players[indx].moves++;

  if(new_pos > 99)
  {
    printf("\n Jump of %d is required, chance void. ", 99-old_pos);
    return 0;
  }
  else if(new_pos == 99)
  {
    switch(finished)
    {
      case 1:
        printf("\n Player %c finishes first ", board->players[indx].symbol);
        strcpy(board->players[indx].remark, "First");
        finished++;
        break;
      case 2:
        printf("\n Player %c finishes second ", board->players[indx].symbol);
        strcpy(board->players[indx].remark, "Second");
        finished++;
        break;
      case 3:
        printf("\n Player %c finishes third ", board->players[indx].symbol);
        strcpy(board->players[indx].remark, "Third");
        finished++;
        break;
    }
    //clear symbol from old pos
    board->elements[old_pos].symbols[indx]= ' ';
    //set symbol at new pos
    board->elements[new_pos].symbols[indx]= board->players[indx].symbol;
    //update the position
    board->players[indx].position = new_pos;
    return 1;
  }
  else
  {
    switch(new_pos)
    {
    //snakes and ladders
      case 4:
        printf("\n Got a ladder from 5 to 25");
        board->players[indx].laddersTaken++;
        new_pos = 24;
        break;
      case 11:
        printf("\n Got a ladder from 12 to 49");
        board->players[indx].laddersTaken++;
        new_pos = 48;
        break;
      case 19:
        printf("\n Got a ladder from 20 to 60");
        board->players[indx].laddersTaken++;
        new_pos = 59;
        break;
      case 26:
        printf("\n Got a ladder from 27 to 54");
        board->players[indx].laddersTaken++;
        new_pos = 53;
        break;
      case 41:
        printf("\n Bit by a snake from 42 to 19");
        board->players[indx].snakeBites++;
        new_pos = 18;
        break;
      case 49:
        printf("\n Bit by a snake from 50 to 11");
        board->players[indx].snakeBites++;
        new_pos = 10;
        break;
      case 58:
        printf("\n Got a ladder from 59 to 82");
        board->players[indx].laddersTaken++;
        new_pos = 81;
        break;
      case 63:
        printf("\n Bit by a snake from 64 to 24");
        board->players[indx].snakeBites++;
        new_pos = 23;
        break;
      case 67:
        printf("\n Got a ladder from 68 to 93");
        board->players[indx].laddersTaken++;
        new_pos = 92;
        break;
      case 80:
        printf("\n Bit by a snake from 81 to 61");
        board->players[indx].snakeBites++;
        new_pos = 60;
        break;
      case 91:
        printf("\n Bit by a snake from 92 to 52");
        board->players[indx].snakeBites++;
        new_pos = 51;
        break;
      case 94:
        printf("\n Bit by a snake from 95 to 35");
        board->players[indx].snakeBites++;
        new_pos = 34;
        break;
    }
    //clear symbol from old pos
    if(old_pos != -1)
      board->elements[old_pos].symbols[indx]= ' ';
    //set symbol at new pos
    board->elements[new_pos].symbols[indx]= board->players[indx].symbol;

    //update the position
    board->players[indx].position = new_pos;

    return 0;
  }//else
}

int dice()
{
  char temp;
  int tot= 0;
  int val;
  do
  {
    do
    {
      temp = ' ';
      printf("\n press enter to dice ");
      fflush(stdin);
      temp= getchar();
    }while(temp != '\n');
    srand(time(0));//seed with current time to get different values from rand() every time
    val = rand(); //if not seeded with a unique value then the same set of values get generated
    val = val%6 +  1;
    tot += val;

    if(tot == 6)
      printf("\n Got 6, redicing... ");
    else if(tot == 12)
      printf("\n Got 6 again, redicing again...");
    else if(tot == 18)
    {
      printf("\n Got 3rd 6, chance void");
      return 0;
    }
    else
    {
      printf("\n Got %d ", val);
      return tot;
    }
  }while(1);//infinte loop

}

void play()
{
  Board board;
  int flag, i ,val, status;

  initializeElements(board.elements);
  initializePlayers(board.players);
  setupSnakes(board.elements);
  setupLadders(board.elements);

  do
  {
    printf("\n Enter number of players (2 to 4) : ");
    scanf("%d", &board.numberOfPlayers);
  }while(board.numberOfPlayers < 2 || board.numberOfPlayers > 4 );


  //game
  flag = board.numberOfPlayers;
  while(flag > 1)
  {
    //per player
    for(i =0; i < board.numberOfPlayers && flag > 1; i++)
    {
      if(board.players[i].position != 99)//by pass the player who have finished the game
      {
        drawBoard(board.elements);
        printf("\n player %c dices : ", board.players[i].symbol);
        val = dice();
        status= movePeg(&board,i,val);

        if(status == 1)// player finishes
          flag--;

      }//if
    }//for
  }//while

  drawBoard(board.elements);
  printf("\n\n");
  //statistics
  for(i =0; i < board.numberOfPlayers; i++)
  {
    printf("\n------------------");
    printf("\n Player : %c", board.players[i].symbol);
    printf("\n Moves : %d", board.players[i].moves);
    printf("\n Ladders Taken : %d", board.players[i].laddersTaken);
    printf("\n Snake Bites : %d", board.players[i].snakeBites);
    printf("\n Position : %s ", board.players[i].remark);
    printf("\n");
  }//for
}//game


int main()
{
  play();
  return 0;
}

