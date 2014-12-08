#include "L1_node_config.h"
#include <PthreadAbstractionLayer/Pth_Types.h>
#include <driver/posix32Timer.h>


#define NUMBER_OF_ISRS  (1)

L1_UINT32 L1_Posix32_NbrOfIsrs = NUMBER_OF_ISRS;
/*
 * The size of the array is `NUMBER_OF_ISRS + 1' because the last entry is used
 * to store the handle of the current task!
 */
//HANDLE threadSuspendEvents[NUMBER_OF_ISRS + 1];

Pth_ThreadPool Pth_ThreadPool_threadpool_threadpool_ =
{
	.nbrOfThreads = 4,
	.tasks = {threadpool_task_0, threadpool_task_1, threadpool_task_2, threadpool_task_3},
	.events = {threadpool_event_0, threadpool_event_1, threadpool_event_2, threadpool_event_3},
	.pthreads = {{0,0,0,0,{{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0}},L1_FALSE,L1_FALSE,0},
                 {0,0,0,0,{{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0}},L1_FALSE,L1_FALSE,0},
             {0,0,0,0,{{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0}},L1_FALSE,L1_FALSE,0},
                 {0,0,0,0,{{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},
                               {L1_FALSE,0,0,0},{L1_FALSE,0,0,0}},L1_FALSE,L1_FALSE,0}},
};

Pth_MutexPool Pth_MutexPool_threadpool_threadpool_ =
{
	.nbrOfResources = 4,
	.resources = {threadpool_resource_0, threadpool_resource_1, threadpool_resource_2, threadpool_resource_3},
	.mutexes = {{0,L1_FALSE,0,L1_FALSE},{0,L1_FALSE,0,L1_FALSE},{0,L1_FALSE,0,L1_FALSE},{0,L1_FALSE,0,L1_FALSE}},
};

Pth_CondPool Pth_CondPool_threadpool_threadpool_ =
{
	.nbrOfSemaphores = 4,
	.semaphores = {threadpool_sem_0, threadpool_sem_1, threadpool_sem_2, threadpool_sem_3},
	.condVariables = {{0,L1_FALSE,0,0,0},{0,L1_FALSE,0,0,0},{0,L1_FALSE,0,0,0},{0,L1_FALSE,0,0,0}},
};

Pth_KeyPool Pth_KeyPool_threadpool_threadpool_ =
{
	.nbrOfKeys = 4,
	.keys = {{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0},{L1_FALSE,0,0,0}},
};


L1_Posix32_ISR L1_Posix32_ISRs[NUMBER_OF_ISRS] =
{
	{
		.entryPoint = L1_Posix32_timerThreadProc, 
		.param = NULL 
	},
        
};

L1_InputPort L1_TaskInputPorts[L1_NODE_NUMBER_OF_TASKS] =
{
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 1}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 255}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 128}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 128}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 128}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 128}
		}
	},
	{
		.WaitingList = 
		{
			.SentinelElement = {NULL, NULL, 128}
		}
	},
};
static L1_Packet PreallocatedPackets[L1_NODE_NUMBER_OF_TASKS] =
{
	{
		.ListElement = {NULL,NULL,1},
		.ServiceID = 0,
		.RequestingTaskID = ((0 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,1},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,255},
		.ServiceID = 0,
		.RequestingTaskID = ((1 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,255},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,128},
		.ServiceID = 0,
		.RequestingTaskID = ((2 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,128},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,128},
		.ServiceID = 0,
		.RequestingTaskID = ((3 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,128},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,128},
		.ServiceID = 0,
		.RequestingTaskID = ((4 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,128},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,128},
		.ServiceID = 0,
		.RequestingTaskID = ((5 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,128},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
	{
		.ListElement = {NULL,NULL,128},
		.ServiceID = 0,
		.RequestingTaskID = ((6 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
		.DestinationPortID = 0,
		.TimeoutTimer = { { NULL, NULL, 0, 0 }, NULL },
		.Timeout = 0,
		.Status = RC_OK,
		.SequenceNumber = 0,
		.DataSize = 0,
		.OwnerPool = NULL,
#ifdef PENDING_REQUESTS_QUEUE
		.PendingRequestListElement = {NULL,NULL,128},
		.PendingRequestHandler = NULL
#endif /* PENDING_REQUESTS_QUEUE */ 
	},
};
#ifdef L1_PRIO_INHERITANCE

#define NUMBER_OF_USED_RESOURCES 4
L1_UINT32 L1_NumberOfUsedResources = NUMBER_OF_USED_RESOURCES;
L1_KeyedListElement L1_KeyListElements[NUMBER_OF_USED_RESOURCES];

#endif /* L1_PRIO_INHERITANCE */
L1_TaskControlRecord L1_TaskControlBlock[L1_NODE_NUMBER_OF_TASKS] =
{
	/*---TASK ID = 0 */
	{
		.ListElement = {NULL,NULL,1},     /* ListElement */
		.TaskID      = ((0 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = L1_KernelEntryPoint,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)NULL, /* arguments */
		.TaskState   = L1_STARTED,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 1,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[0],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[0],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 1 */
	{
		.ListElement = {NULL,NULL,255},     /* ListElement */
		.TaskID      = ((1 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = L1_idleTask,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)NULL, /* arguments */
		.TaskState   = L1_STARTED,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 255,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[1],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[1],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 2 */
	{
		.ListElement = {NULL,NULL,128},     /* ListElement */
		.TaskID      = ((2 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = MainEP,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)NULL, /* arguments */
		.TaskState   = L1_STARTED,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 128,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[2],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[2],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 3 */
	{
		.ListElement = {NULL,NULL,128},     /* ListElement */
		.TaskID      = ((3 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = pthreadEP,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)0, /* arguments */
		.TaskState   = L1_INACTIVE,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 128,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[3],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[3],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 4 */
	{
		.ListElement = {NULL,NULL,128},     /* ListElement */
		.TaskID      = ((4 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = pthreadEP,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)1, /* arguments */
		.TaskState   = L1_INACTIVE,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 128,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[4],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[4],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 5 */
	{
		.ListElement = {NULL,NULL,128},     /* ListElement */
		.TaskID      = ((5 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = pthreadEP,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)2, /* arguments */
		.TaskState   = L1_INACTIVE,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 128,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[5],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[5],          /* RequestPacket */
		.Context       = NULL
	},
	/*---TASK ID = 6 */
	{
		.ListElement = {NULL,NULL,128},     /* ListElement */
		.TaskID      = ((6 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)), /* TaskID; */
		.EntryPoint  = pthreadEP,     /* entrypoint */
		.Arguments   = (L1_TaskArguments)3, /* arguments */
		.TaskState   = L1_INACTIVE,     /* status */
#ifdef L1_PRIO_INHERITANCE
		.CriticalSectionWaitingList =
		{
			.SentinelElement = {NULL,NULL,255}, /* CriticalSectionWaitingList */
		},
		.IntrinsicPriority = 128,     /* IntrinsicPriority */
#endif /* L1_PRIO_INHERITANCE */
		.isSuspended   = L1_FALSE,                        /* isSuspended */
		.TaskInputPort = &L1_TaskInputPorts[6],                 /* TaskInputPort */
		.RequestPacket = &PreallocatedPackets[6],          /* RequestPacket */
		.Context       = NULL
	},
};

L1_DataEvent_HubState threadpool_event_0_HubState =
{
	.isSet = L1_FALSE,
};

L1_DataEvent_HubState threadpool_event_1_HubState =
{
	.isSet = L1_FALSE,
};

L1_DataEvent_HubState threadpool_event_2_HubState =
{
	.isSet = L1_FALSE,
};

L1_DataEvent_HubState threadpool_event_3_HubState =
{
	.isSet = L1_FALSE,
};

L1_Resource_HubState threadpool_resource_0_HubState =
{
	.Locked = L1_FALSE,
	.OwningTaskID = 0,
#ifdef L1_PRIO_INHERITANCE
	.OwnerBoostedToPriority = 255,
	.CeilingPriority = 32,
#endif /* L1_PRIO_INHERITANCE */
};

L1_Resource_HubState threadpool_resource_1_HubState =
{
	.Locked = L1_FALSE,
	.OwningTaskID = 0,
#ifdef L1_PRIO_INHERITANCE
	.OwnerBoostedToPriority = 255,
	.CeilingPriority = 32,
#endif /* L1_PRIO_INHERITANCE */
};

L1_Resource_HubState threadpool_resource_2_HubState =
{
	.Locked = L1_FALSE,
	.OwningTaskID = 0,
#ifdef L1_PRIO_INHERITANCE
	.OwnerBoostedToPriority = 255,
	.CeilingPriority = 32,
#endif /* L1_PRIO_INHERITANCE */
};

L1_Resource_HubState threadpool_resource_3_HubState =
{
	.Locked = L1_FALSE,
	.OwningTaskID = 0,
#ifdef L1_PRIO_INHERITANCE
	.OwnerBoostedToPriority = 255,
	.CeilingPriority = 32,
#endif /* L1_PRIO_INHERITANCE */
};

L1_Semaphore_HubState threadpool_sem_0_HubState =
{
	.Count = 0,
};

L1_Semaphore_HubState threadpool_sem_1_HubState =
{
	.Count = 0,
};

L1_Semaphore_HubState threadpool_sem_2_HubState =
{
	.Count = 0,
};

L1_Semaphore_HubState threadpool_sem_3_HubState =
{
	.Count = 0,
};


L1_Hub L1_LocalHubs[L1_NODE_NUMBER_OF_HUBS] =
{
	/* dataEvent NAME = threadpool_event_0 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_DATAEVENT, /* HubType */
		.HubUpdateFunction = DataEventHub_Update, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = DataEventHub_SyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = DataEventHub_Ioctl, /* HubControlFunction */
		.HubState = (void*) &threadpool_event_0_HubState
	}, /* L1 dataEvent */
	/* dataEvent NAME = threadpool_event_1 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_DATAEVENT, /* HubType */
		.HubUpdateFunction = DataEventHub_Update, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = DataEventHub_SyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = DataEventHub_Ioctl, /* HubControlFunction */
		.HubState = (void*) &threadpool_event_1_HubState
	}, /* L1 dataEvent */
	/* dataEvent NAME = threadpool_event_2 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_DATAEVENT, /* HubType */
		.HubUpdateFunction = DataEventHub_Update, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = DataEventHub_SyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = DataEventHub_Ioctl, /* HubControlFunction */
		.HubState = (void*) &threadpool_event_2_HubState
	}, /* L1 dataEvent */
	/* dataEvent NAME = threadpool_event_3 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_DATAEVENT, /* HubType */
		.HubUpdateFunction = DataEventHub_Update, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = DataEventHub_SyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = DataEventHub_Ioctl, /* HubControlFunction */
		.HubState = (void*) &threadpool_event_3_HubState
	}, /* L1 dataEvent */
	/* resource NAME = threadpool_resource_0 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_RESOURCE, /* HubType */
		.HubUpdateFunction = ResourceUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = ResourceSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_resource_0_HubState
	}, /* L1 resource */
	/* resource NAME = threadpool_resource_1 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_RESOURCE, /* HubType */
		.HubUpdateFunction = ResourceUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = ResourceSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_resource_1_HubState
	}, /* L1 resource */
	/* resource NAME = threadpool_resource_2 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_RESOURCE, /* HubType */
		.HubUpdateFunction = ResourceUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = ResourceSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_resource_2_HubState
	}, /* L1 resource */
	/* resource NAME = threadpool_resource_3 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_RESOURCE, /* HubType */
		.HubUpdateFunction = ResourceUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = ResourceSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_resource_3_HubState
	}, /* L1 resource */
	/* semaphore NAME = threadpool_sem_0 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_SEMAPHORE, /* HubType */
		.HubUpdateFunction = SemaphoreUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = SemaphoreSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_sem_0_HubState
	}, /* L1 semaphore */
	/* semaphore NAME = threadpool_sem_1 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_SEMAPHORE, /* HubType */
		.HubUpdateFunction = SemaphoreUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = SemaphoreSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_sem_1_HubState
	}, /* L1 semaphore */
	/* semaphore NAME = threadpool_sem_2 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_SEMAPHORE, /* HubType */
		.HubUpdateFunction = SemaphoreUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = SemaphoreSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_sem_2_HubState
	}, /* L1 semaphore */
	/* semaphore NAME = threadpool_sem_3 */
	{
		.WaitingList = 
		{
			.SentinelElement = { NULL, NULL, 255 }, /* WaitingList */
		},
		.HubType = L1_SEMAPHORE, /* HubType */
		.HubUpdateFunction = SemaphoreUpdate, /* HubStateUpdateFunctions */
		.HubSyncConditionFunction = SemaphoreSyncCondition, /* HubSyncConditionFunction */
		.HubControlFunction = NULL, /* HubControlFunction */
		.HubState = (void*) &threadpool_sem_3_HubState
	}, /* L1 semaphore */
};
#ifdef L1_ALLOW_TRACE
const int L1_Trace_NumberOfTraceElements=1024;
L1_Trace_TraceBufferElement L1_Trace_TraceBuffer[1024];
#endif /* L1_ALLOW_TRACE */
