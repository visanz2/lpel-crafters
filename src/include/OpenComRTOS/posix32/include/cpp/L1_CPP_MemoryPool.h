#ifndef __L1_CPP_MEMORYPOOL_H__
#define __L1_CPP_MEMORYPOOL_H__


extern "C" 
{
  #include <L1_api.h>
}

class L1_CPP_MemoryPool
{
 public:
  L1_CPP_MemoryPool(L1_HubID mem);

  /**
  * Acquires a memory-block from a memory pool.
  * This call returns immediately independent of whether or not a MemoryBlock was available or not.
  *
  * @param Memory of type void**, if the service completed sucessfully, this will point to a
  * pointer where the allocated memory block is located.This memory can then be used by the Task.
  * Otherwise, this variable will point to a NULL pointer.
  * @param Size of type L1_UINT16, the desired size of the MemoryBlock. However, it is currently
  * not used correctly by the function.
  *
  * @return L1_Status
  * - RC_OK The service completed sucessfully, Memory points to a pointer which points to the allocated MemoryBlock.
  * - RC_FAIL The service failed, Memory will point to a NULL pointer.
  *
  * @pre
  * - NONE
  *
  * @post
  * - Calling task ready.
  */
  L1_Status allocateMemoryBlock_NW(L1_BYTE **Memory, L1_UINT16 Size);

  /**
  * Acquires a memory-block from a memory pool. This service waits till a memory block is available.
  *
  *
  * @param Memory of type void**, if the service completed sucessfully, this will point to a pointer where the allocated memory block is located.
  * This memory can then be used by the Task. Otherwise, this variable will point to a NULL pointer.
  * @param Size of type L1_UINT16, the desired size of the MemoryBlock. However, it is currently not used correctly by the function.
  *
  * @return L1_Status
  * - RC_OK The service completed sucessfully, Memory points to a pointer which points to the allocated MemoryBlock.
  * - RC_FAIL The service failed, Memory will point to a NULL pointer.
  *
  * @pre
  * - NONE
  *
  * @post
  * - Calling task ready.
  */
  L1_Status allocateMemoryBlock_W(L1_BYTE **Memory, L1_UINT16 Size);

  /**
  * Acquires a memory-block from a memory pool. Waits until either a memory-block becomes available or the timeout expired, depending on what happens earlier.
  *
  * @param Memory of type void**, if the service completed sucessfully, this will point to a pointer where the allocated memory block is located.
  * This memory can then be used by the Task. Otherwise, this variable will point to a NULL pointer.
  * @param Size of type L1_UINT16, the desired size of the MemoryBlock. However, it is currently not used correctly by the function.
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for a MemoryBlock to become available.
  *
  *
  * @return L1_Status
  * - RC_OK The service completed successfully, Memory points to a pointer which points to the allocated MemoryBlock.
  * - RC_FAIL The service failed, Memory will point to a NULL pointer.
  * - RC_TO The timeout expired without a MemoryBlock becoming available, Memory will point to a NULL pointer.
  * @pre
  * - NONE
  *
  * @post
  * - Calling task ready.
  */
  L1_Status allocateMemoryBlock_WT(L1_BYTE **Memory, L1_UINT16 Size, L1_Timeout Timeout);

  L1_Status deallocateMemoryBlock_W(void *Memory);

 private:
  L1_HubID HubID;
};


#endif /* !__L1_CPP_MEMORYPOOL_H__ */
