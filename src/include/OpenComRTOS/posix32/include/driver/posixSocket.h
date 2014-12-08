#ifndef POSIX32SOCKETCOM_H_
#define POSIX32SOCKETCOM_H_

#include <L1_types.h>
#include <driver/L1_xfer_packet_api.h>

#ifdef MP

typedef struct sPosixSocketDriver {
	char *host;
} PosixSocketDriver;


typedef struct sPosixSocketLinkPort{
        PosixSocketDriver   * driver;
        L1_UINT16           portNumber;
        char                * host;
        int                 txSocket;
        int                 rxSocket;
        int                 socket;
        L1_XferPacket       rxPacket;
}PosixSocketLinkPort;



#define POSIX32_SOCKET_COM_MAX_CONN      10    /* Max pending connections                   */

L1_Status posixSocketDriver_init(PosixSocketDriver * self);

L1_BOOL posixSocketLinkPort_initServer(PosixSocketDriver * driver, PosixSocketLinkPort * self);

L1_BOOL posixSocketLinkPort_initClient(PosixSocketDriver * driver, PosixSocketLinkPort * self);

void* posixSocket_LinkPort_RxIsr(void* param);

void posixSocketDriver_EntryPoint(L1_TaskArguments Arguments);

#endif /*MP*/

#endif /*POSIX32SOCKETCOM_H_*/
