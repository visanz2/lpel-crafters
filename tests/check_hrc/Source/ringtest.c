/*
 * matrix.c
 *
 *  Created on: Sep 16, 2014
 *      Author: vicentsanzmarco
 */

#include <L1_api.h>
#include <L1_nodes_data.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#include <hrc_lpel.h>
#include <lpel/timing.h>
#include "../../modimpl/monitoring.h"


#ifndef RING_SIZE
#define RING_SIZE 25
#endif

#ifndef ROUNDS
#define ROUNDS 100
#endif

#ifdef BENCHMARK
static struct {
  unsigned long msg_cnt;
  double msg_time;
  unsigned long task_cnt;
  double task_time;
} bench_stats;
#endif


#define STACK_SIZE  (16*1024) /* 16k */

void error(int exitcode, int val, const char *msg);


static int ids[RING_SIZE];
lpel_stream_t *streams[RING_SIZE];
lpel_task_t *tasks[RING_SIZE];

typedef struct {
  int round;
  unsigned int hopcnt;
  int term;
} msg_t;


static void PrintEOR(msg_t *msg) {
  /* print end of round message for process 0 */
  printf("Finished round %d, hops %d\n", msg->round, msg->hopcnt);
}

#undef HAVE_PTHREAD_SETAFFINITY_NP

static void *Process(void *arg)
{
  int id = *(int *)arg;
  lpel_stream_desc_t *in, *out;
  msg_t *msg;
  int term = 0;
  lpel_timing_t ts;

  //out = PthrStreamOpen(streams[id], 'w');
  out = LpelStreamOpen(streams[id], 'w');


  if (id==0)
  {
    //in = PthrStreamOpen(streams[RING_SIZE-1], 'r');
    in = LpelStreamOpen(streams[RING_SIZE-1], 'r');

	#ifndef BENCHMARK
    	printf("Sending message, ringsize %d, rounds %d\n", RING_SIZE, ROUNDS);
	#endif
    /* send the first message */
    msg = malloc( sizeof *msg);
    msg->round = 1;
    msg->term = 0;
    msg->hopcnt = 0;

    LpelTimingStart( &ts);
    //PthrStreamWrite( out, msg);
    LpelStreamWrite( out, msg);
  } else {
    //in = PthrStreamOpen(streams[id-1], 'r');
    in = LpelStreamOpen(streams[id-1], 'r');

  }


  while(!term) {
    //msg = PthrStreamRead( in);
    msg = LpelStreamRead(in);
    msg->hopcnt++;

    if (id==0) {
      PrintEOR(msg);
      /* next round */
      msg->round++;
      if (msg->round == ROUNDS) msg->term = 1;
    }
    if (msg->term)
    	term = 1;

    //PthrStreamWrite( out, msg);
    LpelStreamWrite( out, msg);
  }
  /* read the msg a last time, free it */
  if (id==0) {
    //msg = PthrStreamRead( in);
    msg = LpelStreamRead(in);
    LpelTimingEnd( &ts);
    msg->hopcnt++;
    PrintEOR(msg);
#ifndef BENCHMARK
    printf("Time to pass the message %u times: %.2f ms\n", msg->hopcnt, LpelTimingToMSec( &ts));
#else
    bench_stats.msg_cnt = msg->hopcnt;
    bench_stats.msg_time = LpelTimingToNSec(&ts);
#endif
    free(msg);
    LpelStop();
  }

  //PthrStreamClose( out, 0);
  LpelStreamClose( out, 0);
  //PthrStreamClose( in,  1);
  LpelStreamClose( in, 1);

  return NULL;
}

static void testBasic(void)
{
    lpel_config_t cfg;
    lpel_timing_t ts;
    int i;

    cfg.num_workers = 4;
    cfg.proc_workers = 1;
    cfg.proc_others = 0;
    cfg.flags = 0;
    cfg.type = HRC_LPEL;

    //Initializate LPEL configuration
    printf("Initializate LPEL Configuration\n");
    LpelInit(&cfg);
    LpelStart(&cfg);

    for (i=0; i<RING_SIZE; i++) {
       ids[i] = i;
       //Create a stream. Allocate and initialize memory for a stream. Return pointer to the created stream
       printf("Create a stream\n");
       streams[i] = LpelStreamCreate(0);
    }

    LpelTimingStart( &ts) ;

    for (i=RING_SIZE-1; i>=0; i--) {
       // Create task
       tasks[i] = LpelTaskCreate( 0, Process, &ids[i], 8192);

       // Run Task
       LpelTaskStart(tasks[i]);
       //LpelTaskSetRecLimit(tasks[i], 0);
     }

    LpelTimingEnd( &ts) ;
    #ifndef BENCHMARK
      printf("Time to create %d tasks: %.2f ms\n", RING_SIZE, LpelTimingToMSec( &ts));
    #else
      bench_stats.task_cnt = RING_SIZE;
      bench_stats.task_time = LpelTimingToNSec(&ts);
    #endif
    LpelCleanup();
}



void MainEP(L1_TaskArguments Arguments)
{
  testBasic();

#ifndef BENCHMARK
 //   DumpTraceBuffer_W(StdioHostServer);
  printf("test finished\n");

#else
  printf("%lu %.1f %lu %.1f\n",
      bench_stats.msg_cnt,
      bench_stats.msg_time,
      bench_stats.task_cnt,
      bench_stats.task_time
      );
#endif
    exit(1);
}

