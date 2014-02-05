/*
 *  puzzle.c
 *  
 *
 *  Created by Mark H on 2/5/14.
 *  Copyright 2014 RetiredSphinx game development. All rights reserved.
 *
 */

#define MAXLEN  10
#define GAMENO  5
#define CLEARS  "\033[2J\033[1;1H"
#include  <stdio.h>

int getline(char* input, int len)
{
  int c;
  int i = 0;
  do {
    c = getchar();
    input[i++] = c;
  } while (i < len && c != '\n');
}

void prnt_map(char table[][GAMENO])
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 5; j++)
      printf("%c",table[i][j]);
    printf("\n");
  }
}

void updtmp(char tab[][GAMENO], int y, int x)
{
  char c;
  int prev1, prev2;
  if(tab[y-1][x] == ' ')
  {
    prev1 = y-1;
    prev2 = x;
  }
  else if(tab[y+1][x] == ' ')
  {
    prev1 = y+1;
    prev2 = x;
  }
  else if(tab[y][x-1] == ' ')
  {
    prev1 = y;
    prev2 = x-1;
  }
  else
  {
    prev1 = y;
    prev2 = x+1;
  }
  c = tab[y][x];
  tab[y][x] = ' ';
  tab[prev1][prev2] = c;
}

int finished(char m[][GAMENO])
{
  if(m[1][1] == '1' &&
     m[1][2] == '2' &&
     m[1][3] == '3' && 
     m[2][1] == '4' &&
     m[2][2] == '5' &&
     m[2][3] == '6' &&
     m[3][1] == '7' &&
     m[3][2] == '8')
  {
    return 0;
  }
  return 1;
}

int main(int argc, char** argv)
{
  char inpline[MAXLEN];
  char map[][GAMENO] = {
    {'_','_','_','_','_'},
    {'|','7','3','5','|'},
    {'|','2',' ','4','|'},
    {'|','6','1','8','|'},
    {'_','_','_','_','_'},
  };
  
  int i, j, move=0;
  printf(CLEARS);
  prnt_map(map);
  while(getline(inpline, MAXLEN) != -1)
  {
    if(sscanf(inpline, "%i %i", &i, &j) != 2)
    {
      printf("Error: not a valid coordinate.\a\n");
      continue;
    }
    if(i < 1 || i > 3 || j < 1 || j > 3)
    {
      printf("Error: out of range.\a\n");
      continue;
    }
    if(map[i-1][j] != ' ' && map[i+1][j] != ' ' && map[i][j-1] != ' ' && map[i][j+1] != ' ')
    {
      printf("Error: that move not allowed.\a\n");
      continue;
    }
    updtmp(map, i, j);
    move++;
    printf(CLEARS);
    printf("Move %i:\n", move);
    prnt_map(map);
    if(finished(map) == 0)
    {
      printf("You won!\n");
      return 0;
    }
  }
  return 0;
}
