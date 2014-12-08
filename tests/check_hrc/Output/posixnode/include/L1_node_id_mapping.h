#ifndef NODE_ID_MAPPING
#define NODE_ID_MAPPING

#include <L1_types.h>
#include <L1_nodes_data.h>
#include <L1_node_config.h>


L1_TaskNameToID L1_TaskNamesToIDs[L1_NODE_NUMBER_OF_TASKS] = {
    {
        .name = "KernelTask",
        .id   = ((0 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "IdleTask",
        .id   = ((1 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "MainTask",
        .id   = ((2 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "threadpool_task_0",
        .id   = ((3 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "threadpool_task_1",
        .id   = ((4 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "threadpool_task_2",
        .id   = ((5 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
    {
        .name = "threadpool_task_3",
        .id   = ((6 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE))
    }, 
};


L1_HubNameToID L1_HubNameToIDs[L1_NODE_NUMBER_OF_HUBS] = {
    {
        .name = "threadpool_event_0",
        .id   = ((0 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = 
    }, 
    {
        .name = "threadpool_event_1",
        .id   = ((1 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = 
    }, 
    {
        .name = "threadpool_event_2",
        .id   = ((2 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = 
    }, 
    {
        .name = "threadpool_event_3",
        .id   = ((3 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = 
    }, 
    {
        .name = "threadpool_resource_0",
        .id   = ((4 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_RESOURCE
    }, 
    {
        .name = "threadpool_resource_1",
        .id   = ((5 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_RESOURCE
    }, 
    {
        .name = "threadpool_resource_2",
        .id   = ((6 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_RESOURCE
    }, 
    {
        .name = "threadpool_resource_3",
        .id   = ((7 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_RESOURCE
    }, 
    {
        .name = "threadpool_sem_0",
        .id   = ((8 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_SEMAPHORE
    }, 
    {
        .name = "threadpool_sem_1",
        .id   = ((9 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_SEMAPHORE
    }, 
    {
        .name = "threadpool_sem_2",
        .id   = ((10 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_SEMAPHORE
    }, 
    {
        .name = "threadpool_sem_3",
        .id   = ((11 << 0) | (L1_PRESENT_NODE_ID << L1_NODE_ID_SIZE)),
        .type = L1_SEMAPHORE
    }, 
};

#endif /* NODE_ID_MAPPING */
