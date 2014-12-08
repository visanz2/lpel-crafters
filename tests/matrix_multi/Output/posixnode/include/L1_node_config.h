#define posixnode
#define L1_NODE_NUMBER_OF_TASKS 7
#define L1_NODE_NUMBER_OF_HUBS 12

#include "L1_nodes_data.h"

#include <L1_api.h>
#include <L1_hub_api.h>
#include <L1_kernel_data.h>
#include <L1_memory_api.h>
#include <L1_driver_api.h>
#include <L1_trace_api.h>

extern void L1_KernelEntryPoint(L1_TaskArguments Arguments);
extern void L1_idleTask(L1_TaskArguments Arguments);
extern void MainEP(L1_TaskArguments Arguments);
extern void pthreadEP(L1_TaskArguments Arguments);
