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

#ifndef MATRIX_SIZE
#define MATRIX_SIZE 3
#endif

#ifndef TIMES
#define TIMES 5
#endif

static int matrix_A[MATRIX_SIZE*MATRIX_SIZE];
static int matrix_B[MATRIX_SIZE*MATRIX_SIZE];
static int matrix_R[MATRIX_SIZE*MATRIX_SIZE];
static int ids[MATRIX_SIZE];


lpel_stream_t *streams[2*MATRIX_SIZE];
lpel_task_t *tasks[MATRIX_SIZE];


typedef struct {
	int row_A[MATRIX_SIZE];
	int pos;
	int term;
} msg_t;


static void *First(void *arg)
{
	//int id = *(int *)arg;
    int i;
	lpel_stream_desc_t *out1, *out2, *out3;
	lpel_stream_desc_t *in1, *in2, *in3;
	msg_t *msg1, *msg2, *msg3, *msg_result;

	out1 = LpelStreamOpen(streams[0], 'w');
	out2 = LpelStreamOpen(streams[1], 'w');
	out3 = LpelStreamOpen(streams[2], 'w');

	in1 = LpelStreamOpen(streams[3], 'r');
	in2 = LpelStreamOpen(streams[4], 'r');
	in3 = LpelStreamOpen(streams[5], 'r');

    
    for (i =0; i<TIMES; i++ )
    {

        msg1 = malloc( sizeof *msg1);
        msg1->row_A[0] = matrix_A[0];
        msg1->row_A[1] = matrix_A[1];
        msg1->row_A[2] = matrix_A[2];

        msg1->pos = 0;
        msg1->term = 0;
        LpelStreamWrite( out1, msg1);

        msg2 = malloc( sizeof *msg2);
        msg2->row_A[0] = matrix_A[3];
        msg2->row_A[1] = matrix_A[4];
        msg2->row_A[2] = matrix_A[5];
        msg2->pos = 1;
        msg2->term = 0;
        LpelStreamWrite( out2, msg2);

        msg3 = malloc( sizeof *msg3);
        msg3->row_A[0] = matrix_A[6];
        msg3->row_A[1] = matrix_A[7];
        msg3->row_A[2] = matrix_A[8];
        msg3->pos = 2;
        msg3->term = 0;
        LpelStreamWrite( out3, msg3);

        msg_result = LpelStreamRead(in1);

        matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
        matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
        matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];

        msg_result = LpelStreamRead(in2);
        matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
        matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
        matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];

        msg_result = LpelStreamRead(in3);
        matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
        matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
        matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];
        
        printf("Result: \n");
        printf("%d %d %d\n", matrix_R[0], matrix_R[1], matrix_R[2]);
        printf("%d %d %d\n", matrix_R[3], matrix_R[4], matrix_R[5]);
        printf("%d %d %d\n", matrix_R[6], matrix_R[7], matrix_R[8]);
        printf("\n");
    }
    
    msg1 = malloc( sizeof *msg1);
    msg1->row_A[0] = matrix_A[0];
    msg1->row_A[1] = matrix_A[1];
    msg1->row_A[2] = matrix_A[2];

    msg1->pos = 0;
    msg1->term = 1;
    LpelStreamWrite( out1, msg1);
    
    msg2 = malloc( sizeof *msg2);
    msg2->row_A[0] = matrix_A[3];
    msg2->row_A[1] = matrix_A[4];
    msg2->row_A[2] = matrix_A[5];
    msg2->pos = 1;
    msg2->term = 1;
    LpelStreamWrite( out2, msg2);
    
    msg3 = malloc( sizeof *msg3);
    msg3->row_A[0] = matrix_A[6];
    msg3->row_A[1] = matrix_A[7];
    msg3->row_A[2] = matrix_A[8];
    msg3->pos = 2;
    msg3->term = 1;
    LpelStreamWrite( out3, msg3);

    msg_result = LpelStreamRead(in1);
    matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
    matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
    matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];
    
    msg_result = LpelStreamRead(in2);
    matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
    matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
    matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];
    
    msg_result = LpelStreamRead(in3);
    matrix_R[(3*msg_result->pos)]= msg_result->row_A[0];
    matrix_R[1+(3*msg_result->pos)]= msg_result->row_A[1];
    matrix_R[2+(3*msg_result->pos)]= msg_result->row_A[2];
    
    printf("RESULT: \n");
    printf("%d %d %d\n", matrix_R[0], matrix_R[1], matrix_R[2]);
    printf("%d %d %d\n", matrix_R[3], matrix_R[4], matrix_R[5]);
    printf("%d %d %d\n", matrix_R[6], matrix_R[7], matrix_R[8]);
    printf("\n");
    
	LpelStreamClose( out1, 0);
	LpelStreamClose( out2, 0);
	LpelStreamClose( out3, 0);
	LpelStreamClose( in1, 1);
	LpelStreamClose( in2, 1);
	LpelStreamClose( in3, 1);

	LpelStop();
    
    return NULL;
}

static void *Process(void *arg)
{
	int id = *(int *)arg;
	int i,j, term;
	lpel_stream_desc_t *in, *out;
	msg_t *msg, *msg_result;
	int result[MATRIX_SIZE];

	term = 0;
	out = LpelStreamOpen(streams[(id+3)], 'w');

	in = LpelStreamOpen(streams[id], 'r');

	while(!term)
	{
		for (i=0; i<MATRIX_SIZE; i++)
			result[i] = 0;
        
		msg = LpelStreamRead(in);
		for (i=0; i<3; i++)
		{
		  for(j=0; j<3; j++)
		  {
			  result[j] = result[j] + msg->row_A[i] * matrix_B[(j+(3*i))];
		  }
		}

		msg_result = malloc( sizeof *msg_result);
		msg_result->row_A[0] = result[0];
		msg_result->row_A[1] = result[1];
		msg_result->row_A[2] = result[2];
		msg_result->pos = msg->pos;
		msg_result->term = msg->term;

		LpelStreamWrite( out, msg_result);

		if (msg->term)
			term = 1;
	}

	LpelStreamClose( out, 0);
	LpelStreamClose( in, 1);

	return NULL;
}


static void testBasic(void)
{
    lpel_config_t cfg;
    lpel_task_t *first;
    int i;

    cfg.num_workers = 2;
    cfg.proc_workers = 1;
    cfg.proc_others = 0;
    cfg.flags = 0;
    cfg.type = HRC_LPEL;

    //Initializate LPEL configuration
    printf("Initializate LPEL Configuration\n");
    LpelInit(&cfg);
    LpelStart(&cfg);

    for (i=0; i<(2*MATRIX_SIZE); i++) {
       //Create a stream. Allocate and initialize memory for a stream. Return pointer to the created stream
       printf("Create a stream\n");
       streams[i] = LpelStreamCreate(0);
    }

    first = LpelTaskCreate( 0, First, 0, 8192);
	// Run Task
	LpelTaskStart(first);


    for (i=0; i<MATRIX_SIZE; i++) {
    	ids[i] = i;
    	// Create task
    	tasks[i] = LpelTaskCreate( 0, Process, &ids[i], 8192);

    	// Run Task
    	LpelTaskStart(tasks[i]);
    	//LpelTaskSetRecLimit(tasks[i], 0);
     }

    LpelCleanup();
}


void createMatrix()
{
	int i;
	for(i = 1; i<=(MATRIX_SIZE*MATRIX_SIZE); i++)
	{
		matrix_A[i-1] = i;
		matrix_B[i-1] = i;
	}
    
    printf(" A = \n");
    
    printf("%d %d %d\n", matrix_A[0], matrix_A[1], matrix_A[2]);
    printf("%d %d %d\n", matrix_A[3], matrix_A[4], matrix_A[5]);
    printf("%d %d %d\n", matrix_A[6], matrix_A[7], matrix_A[8]);

    printf(" B = \n");
    printf("%d %d %d\n", matrix_B[0], matrix_B[1], matrix_B[2]);
    printf("%d %d %d\n", matrix_B[3], matrix_B[4], matrix_B[5]);
    printf("%d %d %d\n", matrix_B[6], matrix_B[7], matrix_B[8]);
    printf("\n");
}

void MainEP(L1_TaskArguments Arguments)
{
	createMatrix();
	testBasic();
	printf("test finished\n");
	exit(1);
}
