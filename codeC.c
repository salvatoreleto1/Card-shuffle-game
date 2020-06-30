/* Salvatore Leto - 18633649 Practical Case Study A */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* handy typedefs */
typedef unsigned char card;
typedef unsigned char pairs;

/* arrays for the names of things */
static char *suits[] = {"Hearts","Diamonds","Clubs","Spades"};
static char *values[]= {"Ace","Two","Three","Four","Five","Six",\
                        "Seven","Eight","Nine","Ten","Jack",\
                        "Queen","King"};
static char *colour[]= {"Black","Red"};

/* function prototypes */
void printcard(card c); /* Displays the value of a card*/

void printdeck(card deck[52]); /* prints an entire deck of cards*/

void filldeck(card deck[52]); /* Populates a deck of cards */

void shuffle(card deck[52]); /* Randomizes the order of cards */

int compareface(const void* c1,const void *c2);
/* compares the face value of 2 cards, suitable to pass to qsort
   as the fourth argument */

pairs findpairs(card *hand); /* finds any pairs in a hand */

int main()
{
  card deck[52],*deckp;
  card hands[5][5],handssorted[5][5];
  pairs numpairs[5],highest;
  int hand,cd,winner;

  srand(time(NULL));       /* seed the random number generator */

  filldeck(deck); /* fills the deck */
  printdeck(deck); // prints deck in correct order */
  printf("------------------------------------ Before Shuffle\n");
  shuffle(deck); /* shuffles deck */
  printdeck(deck); /* prints shuffled deck */
  printf("------------------------------------ After Shuffle\n");

  for(cd=0;cd<5;cd++)
  {
     for(hand=0;hand<5;hand++)
     {
        hands[cd][hand] = deck[(cd*5)+hand]; /* deals the hands */
     }
  }

  for(hand=0;hand<5;hand++)
  {
     /* sort the hands here */
     qsort(hands[hand],5,sizeof(char),compareface);

     /* Find the pairs */
     numpairs[hand]=findpairs(handssorted[hand]);

     printf("Hand %i:\n",hand+1);
     /* print the 5 hands here */

     int i = 0; /* Prints out 5 hands using 'i' as loop counter */
     for(;i<5;i++)
     {
	    printf("\t");
     	printcard(hands[hand][i]);
     }
  }
  /* print the number and value of any pairs here. Did not finish. */
  /* determine the winner and print it. Did not finish. */
  return 0;
}

pairs findpairs(card *hand) /* Did not finish this. */
{
   pairs numpairs=0;

   /* find the pairs here */
   return numpairs;
}

void filldeck(card deck[52])
{
   /* populate the deck here */
   int totalcount=0; /* Track count of card in deck */
   int suitIndex; /* Suit card loop counter */
   int valueIndex; /* Value card loop counter */
   for (suitIndex=0;suitIndex<4;suitIndex++) /* Go through all 4 suits */
   {
      for (valueIndex=0;valueIndex<13;valueIndex++) /* Go through all 13 Card values */
      {
         deck[totalcount]=suitIndex<<5; /* set bits 5 and 6 from our suit index variable */

         /*
          *If suit index is 0 or 1 set card colour to 1 (Red)
          *Else set card colour to 0 (Black)
          */
         if(suitIndex == 0 || suitIndex ==1)
         {
            deck[totalcount]=deck[totalcount]|1; /* Based on our suit index, set card colour to Red */
         }
         else
         {
            deck[totalcount]=deck[totalcount]|0; /* Based on our suit index, set card colour to black */
         }
         deck[totalcount]=deck[totalcount]|valueIndex<<1; /* Set bit 1-4 the card value */
         totalcount++; /* Add to our card counter */
      }
   }
   return;
}

void printdeck(card deck[52])
{
   int i;
   for(i=0;i<52;i++)
      printcard(deck[i]); /* Prints the whole deck */
   return;
}

void printcard(card c)
{
   /* print the value of the card here */

   unsigned char cValue, cSuits, cColour; /* Store Value Suit and colour in variables to manipulate */

   cValue = (c>>1) & 0x0F; /* Gives us the value in a card */
   cSuits = (c>>5) & 0x03; /* Gives us the suit in a card */
   cColour = c & 0x01; /* Gives us the colour in a card */
   printf("%s of %s, is %s\n", values[cValue],suits[cSuits],colour[cColour]); /* Prints a card */
   return;
}

void shuffle(card deck[52])
{
   int i,rnd;
   card c;

   for(i=0;i<52;i++)
   {
      /* generate a random number between 0 & 51 */
      rnd=rand() * 52.0 / RAND_MAX;

      /* finish shuffling the deck here */
      c = deck[rnd]; /* Stores a random number in card */
      deck[rnd] = deck[i]; /* Assign to a random card in the arrray */
      deck[i] = c; /* Gives us the value in a card */
   }

   return;
}


int compareface(const void* c1, const void *c2)
{
/* This function extracts the two cards face values
   and returns 1 if cd1 > cd2, 0 if cd1 == cd2, and
   -1 otherwise. The weird argument types are for
   compatibility with qsort(), the first two lines
   decode the arguments back into "card".
   */
    card cd1,cd2;

    cd1=*((card*) c1);
    cd2=*((card*) c2);

    cd1= (cd1&0x1e)>>1;
    cd2= (cd2&0x1e)>>1;

    if(cd1>cd2)
      return 1;
    if(cd1==cd2)
      return 0;

    return -1;
}
