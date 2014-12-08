#include "PthreadAbstractionLayer.h"


#ifndef PTH_TYPES_H_
#define PTH_TYPES_H_


#define MAX_SIZE 10
#define NBR_KEYS 10

typedef struct
{
//	L1_UINT32 nbrOfThreads;
	L1_BOOL allocated;
	void (*destructor)(void*);
	void * data;
	ocr_pthread_key_t id;
}Pth_Key;

typedef struct {
	L1_TaskID taskID;
	L1_HubID exitEvent;
	void * (*start_routine) (void *);
	void * arg;
	//void * returnValue;
	Pth_Key dataKeys[NBR_KEYS];
	L1_BOOL detached;
	L1_BOOL allocated;
	ocr_pthread_t id;
}Pth_Thread;

typedef struct
{
	L1_UINT32 nbrOfThreads;
	L1_TaskID
	tasks[MAX_SIZE];
	L1_HubID events[MAX_SIZE];
	Pth_Thread pthreads[MAX_SIZE];
}Pth_ThreadPool;


typedef struct
{
	L1_HubID resource;
	L1_BOOL allocated;
	ocr_pthread_mutex_t id;
	L1_BOOL locked;
}Pth_Mutex;

typedef struct
{
	L1_UINT32 nbrOfResources;
	Pth_Mutex mutexes[MAX_SIZE];
	L1_HubID resources[MAX_SIZE];
}Pth_MutexPool;

typedef struct
{
	L1_HubID sem;
	L1_BOOL allocated;
	ocr_pthread_cond_t id;
	L1_UINT32 nbrWaitingThreads;
	ocr_pthread_mutex_t mutex;
}Pth_Cond;

typedef struct
{
	L1_UINT32 nbrOfSemaphores;
	Pth_Cond condVariables[MAX_SIZE];
	L1_HubID semaphores[MAX_SIZE];
}Pth_CondPool;

typedef struct
{
	L1_UINT32 nbrOfKeys;
	Pth_Key keys[MAX_SIZE];
}Pth_KeyPool;


#endif
