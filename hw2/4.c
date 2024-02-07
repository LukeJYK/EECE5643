/* -------------------------------------------------------------------------
 * A Monte Carlo simulation of Galileo's three dice experiment.
 *
 * Name              : galileo.c
 * Author            : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-11-98
 * -------------------------------------------------------------------------
 */

#include <stdio.h>
#include "rng.h"
#include "rng.c"
#include <math.h>

#define N 10000L /* number of replications */
#define Pi 3.141592657

long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
  return (a + (long)((b - a + 1) * Random()));
}

int main(void)
{
  long i;     
  long angle; 
  long wins = 0;
  long count[19] = {0}; 
  double p;             

  PutSeed(0);

  for (i = 0; i < N; i++)
  {
    angle = Equilikely(0, 360);

    if (2*sin((Pi/180)*angle/2)>1)
    {
      wins++;
    }
  }
  /* estimate probabilities */
  p = (double)wins / N;

  printf("\nbased on %ld replications ", N);
  printf("the estimated probabilities are:%5.3lf\n\n", p);
  printf("\n");

  return (0);
}