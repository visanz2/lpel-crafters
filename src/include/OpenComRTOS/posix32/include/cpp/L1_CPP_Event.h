#ifndef __L1_CPP_EVENT_H__
#define __L1_CPP_EVENT_H__



extern "C" 
{
  #include <L1_api.h>
}

class L1_CPP_Event
{
 public:
  L1_CPP_Event(L1_HubID event);

  /**
  * This service raises an Event from False to True. If the Event is already set, wait.
  *
  * @return L1_Status:
  * - RC_OK	service successful (the Event has been raised)
  * - RC_FAIL	service failed (the Event has not been raised)
  *
  * @pre
  * - Packet is the preallocated Packet
  * - Hub is of Event type
  *
  * @post
  * - Header fields of preallocated Packet filled in
  *
  */
  L1_Status raiseEvent_W();
  
  /**
  * This service tests an Event.
  * This call waits until the Event has been signalled.
  *
  * @return L1_Status, the following return values are possible:
  * - RC_OK	service successful (there was a set Event)
  * - RC_FAIL	service failed (there was no set Event)
  *
  * @pre
  * - Packet is the preallocated Packet
  *
  * @post
  * - Header fields of preallocated Packet filled in
  * - Data of Put Packet will have been filled in
  *
  */
  L1_Status testEvent_W();

  /**
  * This service raises an Event from False to True.
  * This service returns immediately independent of whether or not it could raise the event.
  *
  * @return L1_Status:
  * - RC_OK  service successful (the Event has been raised)
  * - RC_FAIL    service failed (the Event has not been raised)
  *
  * @pre
  * - Packet is the preallocated Packet
  * - Hub is of Event type
  *
  * @post
  * - Header fields of preallocated Packet filled in
  *
  */
  L1_Status raiseEvent_NW();
  
  /**
  * This service tests an Event.
  * Returns immediately.
  *
  * @return L1_Status, the following return values are possible:
  * - RC_OK  service successful (there was a set Event)
  * - RC_FAIL    service failed (there was no set Event)
  *
  * @pre
  * - Packet is the preallocated Packet
  *
  * @post
  * - Header fields of preallocated Packet filled in
  * - Data of Put Packet will have been filled in
  *
  */
  L1_Status testEvent_NW();

  /**
  * This service raises an Event from False to True.
  * This call waits until either the event could be raised or the timeout expired.
  *
  * Parameters:
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
  *
  * @return L1_Status:
  * - RC_OK  service successful (the Event has been raised)
  * - RC_FAIL    service failed (the Event has not been raised)
  * - RC_TO service timed out.
  *
  * @pre
  * - Packet is the preallocated Packet
  * - Hub is of Event type
  *
  * @post
  * - Header fields of preallocated Packet filled in
  *
  */
  L1_Status raiseEvent_WT(L1_Timeout Timeout);

  /**
  * This service tests an Event.
  * This call waits until either the Event has been signalled, or the timeout expired.
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
  *
  * @return L1_Status, the following return values are possible:
  * - RC_OK service successful (there was a set Event).
  * - RC_FAIL service failed (there was no set Event).
  * - RC_TO timeout expired.
  *
  * @pre
  * - Packet is the preallocated Packet
  *
  * @post
  * - Header fields of preallocated Packet filled in
  * - Data of Put Packet will have been filled in
  *
  */
  L1_Status testEvent_WT(L1_Timeout Timeout);

 private:
  L1_HubID HubID;
};

#endif /* !__L1_CPP_EVENT_H__ */
