
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service 
 * node. 
 *
 * Name              : ssq1.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-01-98
 * Compile with      : gcc ssq1.c 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>                              

#define FILENAME   "ac.dat"                  /* input data file */
#define START      0.0

/* =========================== */
   double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{ 
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

/* =========================== */
   double GetDeparture(FILE *fp)                 /* read a service time */
/* =========================== */
{ 
  double s;

  fscanf(fp, "%lf\n", &s);
  return (s);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE   *fp;                                  /* input data file      */
  long   index     = 0;                        /* job index            */
  double arrival   = START;                    /* arrival time         */
  double delay;                                /* delay in queue       */
  double service;                              /* service time         */
  double wait;                                 /* delay + service      */
  double departure = START;                    /* departure time       */
  struct {                                     /* sum of ...           */
    double delay;                              /*   delay times        */
    double wait;                               /*   wait times         */
    double service;                            /*   service times      */
    double interarrival;                       /*   interarrival times */
  } sum = {0.0, 0.0, 0.0};
  double lastDeparture = 0;
  double lastArrival = 0;
  
  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }
  while (!feof(fp)) {
    index++;
    arrival      = GetArrival(fp);
    departure    = GetDeparture(fp);
    if(index>1 && lastDeparture>arrival)
    {
      service = departure - lastDeparture;
      lastDeparture = departure;
    }
    else
    {
      service = departure - arrival;
      lastDeparture = departure;
    }
    sum.service += service;
  }
  sum.interarrival = arrival - lastArrival;
  lastArrival = arrival;
  double utilization = sum.service / departure;

  printf("\nfor %ld jobs\n", index);
  printf("   average service time .... = %6.2f\n", sum.service / index);
  printf("   The utilization............ = %6.2%%f\n", utilization);
  printf("   The traffic intensity............ = %6.2%%f\n", sum.service / sum.interarrival);
  fclose(fp);
  return (0);
}
