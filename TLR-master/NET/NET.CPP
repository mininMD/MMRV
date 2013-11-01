/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : NETDEF.H
 * PURPOSE     : Tough Light Racing project.
 *               Network interaction module.
 *               Network interaction module implemention.
 * PROGRAMMER  : CGSG'2013.
 *               Poletaev Vsevolod.
 * LAST UPDATE : 01.08.2013
 * NOTE        : Namespace 'net'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "netdef.h"

#pragma comment (lib, "ws2_32.lib")

using namespace net;  // Library namespace

BOOL interfc::IsInit = FALSE;  // Win Sockets init flag
INT interfc::InstCnt = 0;      // Network interfce unstance counter

/* Default constructor.
 * ARGUMENTS:
 *   None;
 */
interfc::interfc( VOID ) : HostsNo(0), BroadCast(-1)
{
  static WSADATA wsaData;
  if (!IsInit)
  {
    INT res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != 0)
    {
      MessageBox(NULL, "WSA init failed!", "Error!", MB_OK | MB_ICONERROR);
      return;
    }
    IsInit = TRUE;
  }
  InstCnt++;  // Increase instance counter
} /* End of 'interfc::interfc' function */

/* Destuctor.
 * ARGUMENTS:
 *   None;
 */
interfc::~interfc( VOID ) : AvalHosts(AvalHostNo)
{
  if (!IsInit)
    return;

  /* Close all sockets */
  for (INT i = 0; i < HostsNo; i++)
  {
    shutdown(Hosts[i], SD_BOTH);
    closesocket(Hosts[i]);
  }

  InstCnt--;  // Decrease instance counter
  /* CleanUp library if there are not active instances */
  if (InstCnt < 1)
    WSACleanup();
} /* End of 'interfc::~interfc' function */


/* END OF 'NET.CPP' FILE */
