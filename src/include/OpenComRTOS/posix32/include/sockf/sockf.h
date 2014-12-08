/*
 ** FILE        : sockf.h
 ** IMPORTS     :
 ** EXPORTS     : Defines, see below
 ** DESCRIPTION : Socket handling function definitions
 **
 */
#ifndef _SOCKF_H
#define _SOCKF_H



#include <stdio.h>

#ifdef WIN32
#define bzero(x,y) memset(x,0,y)
#define bcopy(x,y,z) memcpy(y,x,z)
#endif

/*
 ** General defines
 */
#define MAX_COUNT     10    /* Number of 'bind' attempts                 */
#define MAX_LENGTH 16384    /* Max length of a message sent via a socket */
#define MAX_CONN      10    /* Max pending connections                   */

/*
 ** Error codes
 */
#define SOCKF_OK          0  /* Successfull operation                    */
#define SOCKF_ERR_SOCKET  1  /* Failed to initiate socket                */
#define SOCKF_ERR_BIND    2  /* Reached max. number of bind retries      */
#define SOCKF_ERR_CONNECT 3  /* Error in connecting socket               */
#define SOCKF_ERR_READ    4  /* Error in reading from descriptor         */
#define SOCKF_ERR_WRITE   5  /* Error in writing to descriptor           */
#define SOCKF_ERR_NOBLOCK 6  /* Failed to unblock descriptor             */
#define SOCKF_ERR_INIT    7  /* Error in initiation sequence with client */
#define SOCKF_ERR_HOST    8  /* Failed to get host address               */

/*
 ** Socket initiation functions
 */
int sockf_init_server(const char *host, unsigned short *portnumber);
int sockf_init_client(const char *host, unsigned short portnumber);
int sockf_accept(int sockfd);
int sockf_select(int nSockets, int *sockets);
void sockf_close(int sockfd);
void sockf_terminate(void);

/*
 ** Read functions
 */
int sockf_readn(register int fd, register char *ptr,
                register int nbytes);
int sockf_readline(register int fd, register char *ptr, register int maxlen);
int sockf_readinput(register int fd, register char *ptr,
                    register int maxlen);
#ifdef _Windows
long sockf_read (register int fd, char **ptr);
#endif

/*
 ** Write functions
 */
int sockf_writen(register int fd, register char *ptr,
                 register int nbytes);
int sockf_writeline(register int fd, register char *ptr);
int sockf_writestring(register int fd, register char *ptr);
int sockf_writeoutput(register int fd, register char *ptr, int length);

/*
 ** Socket blocking functions
 */
int sockf_blocking(int fd);
int sockf_nonblocking(int fd);

#endif /* #ifndef _SOCKF_H */
