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
#include "../../modimpl/monitoring.h"

typedef struct {
  lpel_stream_t *in, *out;
  int id;
} channels_t;

#undef HAVE_PTHREAD_SETAFFINITY_NP

void *Relay(void *inarg)
{
  channels_t *ch = (channels_t *)inarg;
  int term = 0;
  int id = ch->id;
  char *item;
  lpel_stream_desc_t *in, *out;

  in = LpelStreamOpen(ch->in, 'r');
  out = LpelStreamOpen(ch->out, 'w');

  printf("Relay %d START, read from %d, write to %d\n", id, LpelStreamGetId(in), LpelStreamGetId(out));

  while (!term) {
    item = LpelStreamRead( in);
    assert( item != NULL );


    LpelStreamWrite( out, item);
    if ( 0 == strcmp( item, "T\n")) {
		term = 1;
	}

  } // end while

  LpelStreamClose( in, 1);
  LpelStreamClose( out, 0);
  free(ch);

  printf("Relay %d TERM\n", id);
  return NULL;
}


static channels_t *ChannelsCreate(lpel_stream_t *in, lpel_stream_t *out, int id)
{
  channels_t *ch = (channels_t *) malloc( sizeof(channels_t));
  ch->in = in;
  ch->out = out;
  ch->id = id;
  return ch;
}

lpel_stream_t *PipeElement(lpel_stream_t *in, int depth)
{
  lpel_stream_t *out;
  channels_t *ch;
  lpel_task_t *t;
  //int wid = depth % 2;
  //mon_task_t *mt;

  out = LpelStreamCreate(0);
  ch = ChannelsCreate( in, out, depth);
    
  t = LpelTaskCreate( 0, Relay, ch, 8192);
  //LpelTaskSetRecLimit(t, 0);
  //LpelTaskSetNegLim(1);

  //mt = LpelMonTaskCreate(LpelTaskGetId(t), NULL);
  //LpelTaskMonitor(t, mt);
  LpelTaskStart(t);

  printf("Created Relay %d n", depth );
  return (depth > 0) ? PipeElement( out, depth-1) : out;
}



static void *Outputter(void *arg)
{
  lpel_stream_desc_t *in = LpelStreamOpen((lpel_stream_t*)arg, 'r'); 
  char *item;
  int term = 0;

  printf("Outputter START\n");

  while (!term) {
    item = LpelStreamRead(in);
    assert( item != NULL );
    printf("Out: %s", item );

    if ( 0 == strcmp( item, "T\n")) {
      term = 1;
    }
    free( item);
  } // end while

  LpelStreamClose( in, 1);
  printf("Outputter TERM\n");

  LpelStop();
  return NULL;
}

static void *Inputter(void *arg)
{
  lpel_stream_desc_t *out = LpelStreamOpen((lpel_stream_t*)arg, 'w');
  char *buf;

  printf("Inputter START\n");
  do {
    buf = fgets( malloc( 120 * sizeof(char) ), 119, stdin  );
    //LpelTaskYield();
    if (0 != strcmp(buf, "T\n")) {
    	LpelStreamWrite( out, strcpy(malloc(120 * sizeof(char)), buf));
    	LpelStreamWrite( out, strcpy(malloc(120 * sizeof(char)), buf));
    	LpelStreamWrite( out, strcpy(malloc(120 * sizeof(char)), buf));
    	LpelStreamWrite( out, strcpy(malloc(120 * sizeof(char)), buf));
    	//LpelTaskYield();
    }
    LpelStreamWrite( out, strcpy(malloc(120 * sizeof(char)), buf));
  } while ( 0 != strcmp(buf, "T\n") );

  LpelStreamClose( out, 0);
  printf("Inputter TERM\n");
  return NULL;
}


static void testBasic(void)
{
    lpel_stream_t *in, *out;
    lpel_config_t cfg;
    lpel_task_t *intask, *outtask;
    //mon_task_t *mt;
    
    cfg.num_workers = 2;
    cfg.proc_workers = 1;
    cfg.proc_others = 0;
    cfg.flags = 0;
    cfg.type = HRC_LPEL;
    
    //unsigned long flags = (1 << 7) - 1;
    
    //Create monitoring
    //LpelMonInit(&cfg.mon, flags);
    
    //Initializate LPEL configuration
    printf("Initializate LPEL Configuration\n");
    LpelInit(&cfg);
    printf("LPEL STARTS\n");
    LpelStart(&cfg);
    
    //Create a stream. Allocate and initialize memory for a stream. Return pointer to the created stream
    printf("Create a stream\n");
    in = LpelStreamCreate(0);

    // Function in this document
    printf("Create Pipe\n");
    out = PipeElement(in, 2);
    
    // Create task
    outtask = LpelTaskCreate( 0, Outputter, out, 8192);
    //LpelTaskSetRecLimit(outtask, 0);
    //LpelTaskSetNegLim(1);
    //mt = LpelMonTaskCreate( LpelTaskGetId(outtask), "outtask");
    
    //LpelTaskMonitor(outtask, mt);
    
    // Run Task
    LpelTaskStart(outtask);

    //It is created fist not the last
    intask = LpelTaskCreate( 0, Inputter, in, 8192);
	LpelTaskSetRecLimit(intask, 0);
	//LpelTaskSetNegLim(1);

	//mt = LpelMonTaskCreate( LpelTaskGetId(intask), "intask");

	//LpelTaskMonitor(intask, mt);
	LpelTaskStart(intask);
    
    LpelCleanup();
    //LpelMonCleanup();
}


void MainEP(L1_TaskArguments Arguments)
{
	printf("test Starts\n");
    testBasic();
    printf("test finished\n");

    exit(1);
}

