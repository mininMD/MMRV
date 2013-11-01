/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TLRSVR.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Server module.
 *               Server class implementation.
 * PROGRAMMER  : CGSG'2013.
 *               Vasiliy Cheptsov.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../tlr.h"

/* Count active players number function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Active players number.
 */
INT tlr::server::CountActive( VOID )
{
  INT res = 0;

  for (INT i = 0; i < PlayersState.Size(); i++)
    if (PlayersState[i])
      res++;

  return res;
} /* End of 'tlr::server::CountActive' function */

/* Server function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (DWORD) exit code.
 */
DWORD WINAPI tlr::server::ServerThrdFunc( VOID *None )
{
  server *Srv = (server *)None;
  Srv->StartTime = Srv->Timer.GlobalTime;

  // Player connection
  while (Srv->Timer.GlobalTime - Srv->StartTime <= __TLR_TIME_FOR_CONNECTION)
  {
  }

  /* Game play */
  while (Srv->CountActive() > 1)
  {
    /* Recive message from client */
    MSGBASE MsgBase;

    MsgBase.ID = MSGBASE::MSGID_NONE;
    switch (MsgBase.ID)
    {
    case MSGBASE::MSGID_GETCOORD:
      break;
    }
  }
  return 0;
} /* End of 'tlr::server::ServerThrdFunc' function */

/* Create server thread function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::server::CreateServer( VOID )
{
  hThrd = CreateThread(NULL, 0, tlr::server::ServerThrdFunc, NULL, 0, &ThrdID);
  //SetThreadPriority(TUP_hThrd, THREAD_PRIORITY_HIGHEST);
} /* End of 'tlr::server::CreateServer' function */

/* END OF 'TLRSVR.CPP' FILE */
