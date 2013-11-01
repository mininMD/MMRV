/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : CHECKGP.H
 * PURPOSE     : Tough Light Racing project.
 *               Check server and client module.
 *               Insert check test.
 * PROGRAMMER  : CGSG'2013.
 *               Rusanov Vyacheslav.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __CHECKGP_H_
#define __CHECKGP_H_

#include "../tlr.h"

/* Project namespace */
namespace tlr
{
  /* Check client and server class */
  class check
  {
  public:
    /* Flag - client send or recerve message */
    BOOL ClientWrite;

    /* Main message structure */
    net::MSG *Msg;

     /* Class constructor */
    check( VOID ) : ClientWrite(TRUE)
    {
    } /* End of 'check' constructor */

    /* Send message to server function
     * ARGUMENTS: 
     *   - pointer to main message structure:
     *       net::MSG *SendMsg;
     * RETURNS: None.
     */
    VOID SendCl( net::MSG *SendMsg )
    {
      delete[] Msg;
      ClientWrite = TRUE;
      Msg = new net::MSG [SendMsg->MsgSize];
      memcpy(Msg, SendMsg, SendMsg->MsgSize);
     } /* End of 'SendCl' function */

    /* Send message to client function
     * ARGUMENTS: 
     *   - pointer to main message structure:
     *       net::MSG *SendMsg;
     * RETURNS: None.
     */
    VOID SendSer( net::MSG *SendMsg )
    {
      if (ClientWrite == FALSE)
      {
        delete[] Msg;
        Msg = new net::MSG [SendMsg->MsgSize];
        memcpy(Msg, SendMsg, SendMsg->MsgSize);
      }
    }/* End of 'SendSer' function */

    /* Recive message from server function
     * ARGUMENTS: None.
     * RETURNS:
     *   - pointer to main message structure:
     *       net::MSG *;
     */
    net::MSG * RecvCl( VOID )
    {
      while (1)
      {
        if (ClientWrite == TRUE)
         return Msg;
      }
    } /* End of 'RecvCl' function */

    /* Recive message from client function
     * ARGUMENTS: None.
     * RETURNS:
     *   - pointer to main message structure:
     *       net::MSG *;
     */
    net::MSG * RecvSrv( VOID )
    {
      while (1)
      {
        if (ClientWrite == FALSE)
         return Msg;
      }
    } /* End of 'RecvSrv' function */

  }; /* End of 'check' class */
} /* End of 'trl' namespace */

#endif /* __CHECKGP_H_ */

/* END OF 'CHECKGP.H' FILE */
