/* Created Fri Dec 20 11:01:43 2013 */
#include <L1_api.h>
#include <L1_node_config.h>
int main(void)
{ 
  return L1_runOpenComRTOS(L1_NODE_NUMBER_OF_TASKS,L1_NODE_NUMBER_OF_HUBS);
}

/*
 * Modify this to send the CPU into a specific sleep mode
 */
void L1_idleTask( L1_TaskArguments Arguments) 
{
    while (1) 
    {
    }
}
