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

#define N 10000000L /* number of replications */

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
  long i;      /* replication index      */
  long point1; /* number of 1 dice   */
  long point2; /* number of 2 dice   */
  long wins = 0; /* win: sum of 2 dices equals to 7*/
  double p;             /* probability estimates  */

  PutSeed(0);

  for (i = 0; i < N; i++)
  {
    point1 = Equilikely(1, 13);
    if (point1 == 1)
    {
      point1 = 1;
    }
    else if (point1 == 2 || point1 == 3)
    {
      point1 = 2;
    }
    else if (point1 == 4 || point1 == 5)
    {
      point1 = 3;
    }
    else if (point1 == 6 || point1 == 7)
    {
      point1 = 4;
    }
    else if (point1 == 8 || point1 == 9)
    {
      point1 = 5;
    }
    else if (point1 == 10 || point1 == 11 || point1 == 12 || point1 == 13)
    {
      point1 = 6;
    }
    point2 = Equilikely(1, 13);
    if (point2 == 1)
    {
      point2 = 1;
    }
    else if (point2 == 2 || point2 == 3)
    {
      point2 = 2;
    }
    else if (point2 == 4 || point2 == 5)
    {
      point2 = 3;
    }
    else if (point2 == 6 || point2 == 7)
    {
      point2 = 4;
    }
    else if (point2 == 8 || point2 == 9)
    {
      point2 = 5;
    }
    else if (point2 == 10 || point2 == 11 || point2 == 12 || point2 == 13)
    {
      point2 = 6;
    }
    if (point1 + point2 == 7)
    {
      wins++;
    }
  }
  p = (double)wins / N;
  printf("\nbased on %ld replications ", N);
  printf("the estimated probabilities are:%5.3lf\n\n", p);
  printf("\n");
  return (0);
}