/* Generated by ProjectGen tool v. 1.6.0.1
   for Target WIN32 Thu Sep 18 14:36:05 2014
*/

#if (L1_GLOBALID_SIZE == 8)
#define L1_NODE_ID_SIZE 0
#elif (L1_GLOBALID_SIZE == 16)
#ifdef L1_WIDEIDS
#ifdef MP
#error "MP and use of wide ids require L1_GLOBALID_SIZE of >= 32"
#else
#define L1_NODE_ID_SIZE 0
#endif /* MP */
#else /* L1_WIDEIDS */
#define L1_NODE_ID_SIZE 8
#endif /* L1_WIDEIDS */
#elif (L1_GLOBALID_SIZE == 32)
#ifdef L1_WIDEIDS
#define L1_NODE_ID_SIZE 16
#else
#define L1_NODE_ID_SIZE 8  
#endif /* L1_WIDEIDS */
#endif /* L1_GLOBALID_SIZE == 8, 16, 32 */
#define posixnode_NODE_ID 0
#include "L1_posixnode_data.h"
#ifdef posixnode
#define L1_PRESENT_NODE_ID posixnode_NODE_ID
#endif /* posixnode*/
