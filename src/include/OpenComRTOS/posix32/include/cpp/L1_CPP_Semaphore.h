#ifndef __L1_CPP_SEMAPHORE_H__
#define __L1_CPP_SEMAPHORE_H__


extern "C" 
{
  #include <L1_api.h>
}

class L1_CPP_Semaphore
{
 public:
  L1_CPP_Semaphore(L1_HubID sem);
  
  /**
  *
  * Signals a semaphore, i.e. increases the semaphore count.
  * This call waits until it could increment the Semaphore count.
  *
  * @return L1_Status:
  * - RC_OK	service successful (the semaphore count was incremented)
  * - RC_FAIL	service failed (the semaphore count was not incremented)
  *
  * @pre
  * - None
  *
  * @post
  * - Semaphore count incremented
  * - Calling tasks ready
  */
  L1_Status  signalSemaphore_W();
  
  /**
  * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
  * This service waits until it could decrement the semaphore count.
  *
  * @return L1_Status
  * - RC_OK	The service call was successful (the semaphore count was >1 and decremented)
  * - RC_FAIL The service call failed.
  *
  * @pre
  * - None
  *
  * @post
  * - Semaphore count is 0 or decremented by one.
  * - Calling tasks ready
  *
  */
  L1_Status  testSemaphore_W();

  /**
  *
  * Signals a semaphore, i.e. increases the semaphore count.
  * This call returns immediately.
  *
  * @return L1_Status:
  * - RC_OK  service successful (the semaphore count was incremented)
  * - RC_FAIL    service failed (the semaphore count was not incremented)
  *
  * @pre
  * - None
  *
  * @post
  * - Semaphore count incremented
  * - Calling tasks ready
  */
  L1_Status  signalSemaphore_NW();

  /**
  * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
  * This service returns immediately, even if it could not decrement the semaphore counter.
  *
  * @return L1_Status
  * - RC_OK  The service call was successful (the semaphore count was >1 and decremented)
  * - RC_FAIL The service call failed.
  *
  * @pre
  * - None
  *
  * @post
  * - Semaphore count is 0 or decremented by one.
  * - Calling tasks ready
  *
  */
  L1_Status  testSemaphore_NW();
  
  /**
  *
  * Signals a semaphore, i.e. increases the semaphore count.
  * This service waits until it either could increment the semaphore count or the timout expired.
  *
  * Parameters:
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
  *
  * @return L1_Status:
  * - RC_OK service successful (the semaphore count was incremented)
  * - RC_FAIL service failed (the semaphore count was not incremented)
  * - RC_TO service timed out.
  *
  * @pre
  * - None
  *
  * @post
  * - Semaphore count incremented
  * - Calling tasks ready
  */
  L1_Status  signalSemaphore_WT(L1_Timeout Timeout);

  /**
  * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
  * This service waits until it either could decrement the semaphore or the timeout expired.
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
  *
  * @return L1_Status, the following return values are possible:
  * - RC_OK service successful (there was a set Event)
  * - RC_FAIL service failed (there was no set Event)
  * - RC_TO service timed out.
  *
  * @pre
  * - Packet is the preallocated Packet
  *
  * @post
  * - Header fields of preallocated Packet filled in
  * - Data of Put Packet will have been filled in
  *
  */
  L1_Status  testSemaphore_WT(L1_Timeout Timeout);

 private:
  L1_HubID HubID;
};

#endif /* !__L1_CPP_SEMAPHORE_H__ */
