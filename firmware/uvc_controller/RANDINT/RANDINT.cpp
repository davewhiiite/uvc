#include "randInt.h"

int randIntGen () {

   time_t t;

   // Intializes random number generator
   srand((unsigned) time(&t));

   // Returns a random integer from 0 to RAND_MAX
   return(rand());

}
