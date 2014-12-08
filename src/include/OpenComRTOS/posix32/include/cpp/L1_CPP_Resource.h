#ifndef __L1_CPP_RESOURCE_H__
#define __L1_CPP_RESOURCE_H__

extern "C" 
{
  #include <L1_api.h>
}

class L1_CPP_Resource
{
 public:
  L1_CPP_Resource(L1_HubID res);

  /**
  * Locks a logical Resource. This service waits until it could lock the logical Resource.
  *
  * @return L1_Status
  * RC_OK	service successful (the resource was acquired and locked)
  * RC_FAIL	service failed (the resource was not acquired)
  *
  * @pre
  * - None
  *
  * @post
  * - Calling task ready
  */
  L1_Status lockResource_W();

  /**
  * Unlocks a logical Resource.
  * This service waits until is could unlock the resource!
  *
  * @return L1_Status
  * - RC_OK service successful (the resource was released)
  * - RC_FAIL service failed (the resource could not be unlocked)
  *
  * @pre
  * - None
  *
  * @post
  *  - Calling task ready
  */
  L1_Status unlockResource_W();

  /**
  * Locks a logical Resource.
  * This service does return immediately, even if it could not lock the resource.
  *
  * @return L1_Status
  * RC_OK    service successful (the resource was acquired and locked)
  * RC_FAIL  service failed (the resource was not acquired)
  *
  * @pre
  * - None
  *
  * @post
  * - Calling task ready
  */
  L1_Status lockResource_NW();

  /**
  * Unlocks a logical Resource.
  * This service returns immediately, independent whether or not it could decrement the semaphore count.
  *
  * @return L1_Status
  * - RC_OK service successful (the resource was released)
  * - RC_FAIL service failed (the resource could not be unlocked)
  *
  * @pre
  * - None
  *
  * @post
  *  - Calling task ready
  */
  L1_Status unlockResource_NW();

  /**
  * Locks a logical Resource.
  * This service waits until it either could lock the resource or the timeout expired.
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
  *
  * @return L1_Status
  * - RC_OK service successful (the resource was acquired and locked)
  * - RC_FAIL service failed (the resource was not acquired)
  * - RC_TO service timed out.
  *
  * @pre
  * - None
  *
  * @post
  * - Calling task ready
  */
  L1_Status lockResource_WT(L1_Timeout Timeout);

  /**
  * Unlocks a logical Resource.
  * This service waits until is could either unlock the resource, or the timeout expired.
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait while trying to enqueue the packet.
  *
  * @return L1_Status
  * - RC_OK service successful (the resource was released)
  * - RC_FAIL service failed (the resource could not be unlocked)
  * - RC_TO the timeout expired.
  *
  * @pre
  * - None
  *
  * @post
  *  - Calling task ready
  */
  L1_Status unlockResource_WT(L1_Timeout Timeout);

 private:
  L1_HubID HubID;
};


#endif /* !__L1_CPP_RESOURCE_H__ */
