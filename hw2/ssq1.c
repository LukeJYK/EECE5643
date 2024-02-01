
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

#define FILENAME   "ssq1.dat"                  /* input data file */
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
   double GetService(FILE *fp)                 /* read a service time */
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
  double max_delay = 0;                        /* max delay time       */ 
  int time = 400;
  int service_num = 0;                         /* number of jobs at service node at time t */
  double total_job = 0;                        /* number of total jobs */
  double delay_job_num = 0;                    /* number of delayed jobs at node*/
  
  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  while (!feof(fp)) {
    index++;
    arrival      = GetArrival(fp);
    if (arrival < departure){
      delay      = departure - arrival;        /* delay in queue    */
      delay_job_num++;
      if (delay > max_delay)
      {
        max_delay = delay;
      }
    }
    else {
      delay      = 0.0;                        /* no delay          */
    }
    
    service      = GetService(fp);
    wait         = delay + service;
    departure    = arrival + wait;             /* time of departure */
    if (departure > time && arrival < time)
    {
      service_num ++;
    }
    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
    total_job ++;
  }
  sum.interarrival = arrival - START;
  double utilization = sum.service / departure;
  
  printf("\nfor %ld jobs\n", index);
  printf("   average interarrival time = %6.2f\n", sum.interarrival / index);
  printf("   average service time .... = %6.2f\n", sum.service / index);
  printf("   average delay ........... = %6.2f\n", sum.delay / index);
  printf("   average wait ............ = %6.2f\n", sum.wait / index);
  printf("   max delay ............ = %6.2f\n", max_delay);
  printf("   your input time t........ = %0.2d\n", time);
  printf("   number of jobs in the service node at time = 400............ = %d\n", service_num);
  printf("   proportion of jobs delayed.. =  %0.0f%%\n", (delay_job_num/total_job)*100);
  printf("   The proportion of utilization............ = %0.0f%%\n", utilization*100);

  fclose(fp);
  return (0);
}
