#ifndef LINKCOMMUNICATION_H_
#define LINKCOMMUNICATION_H_

/* These are conversion functions to convert the data from one platform to another. 
 */

L1_UINT16 ntoh16(L1_UINT16 networkshort);
L1_UINT32 ntoh32(L1_UINT32 networklong);
L1_UINT16 hton16(L1_UINT16 hostshort);
L1_UINT32 hton32(L1_UINT32 hostlong);

#endif /*LINKCOMMUNICATION_H_*/
