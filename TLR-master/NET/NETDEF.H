/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : NETDEF.H
 * PURPOSE     : Tough Light Racing project.
 *               Network interaction module.
 *               Network interaction module declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Poletaev Vsevolod.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'net'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __NETDEF_H_
#define __NETDEF_H_

#include "../tlrstock.h"

namespace net
{
  /* Base network message representation type */
  struct MSG
  {
    UINT MsgSize; // Message size

    /* Default construtor */
    MSG( VOID ) : MsgSize(sizeof(MSG))
    {
    } /* End of 'MSG' constructor */
  }; /* End of 'MSG' structure */

/* Not ready now */
#if 0
  /* Network interface class */
  class interfc
  {
  private:
    static const INT MaxHostsNo = 20;        // Maximal hosts no.
    static const UINT BroadcastPort = 3031;  // Broadcast port no.
    static const UINT TCPort = 3030;         // TCP port no.

    INT HostsNo;  // Current hosts no.

    SOCKET Hosts[MaxHostsNo],     // Hosts TCP socket array
      BroadCast;                  // Broadcast socket
    static BOOL IsInit;           // Win Sockets init flag
    static INT InstCnt;           // Network interfce unstance counter
    stock<INT, 20> AvalHostsVal;  // Read-avalible hosts
  public:
    stock<INT, 20> &AvalHosts;  // Read olnly reference to read-avalible hosts stock

    /* Default constructor */
    interfc( VOID );

    /* Destructor */
    ~interfc( VOID );

    /* Send message to sprcified host function */
    MsgSend( INT HostNo, MSG * const Msg );

    /* Recive message functon */
    SelectHosts(

  }; /* End of 'interact' class */
#endif  // 0
} /* end of 'net' namespace */

#endif  // __NETDEF_H_

/* END OF 'NETDEF.H' FILE */
