/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SERVER.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Server module.
 *               Server class implementation.
 * PROGRAMMER  : CGSG'2013.
 *               Vasiliy Cheptsov.
 * LAST UPDATE : 03.08.2013
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

/* Get new player position function.
 * ARGUMENTS:
 *   - Player ID
 *       INT Id;
 * RETURNS:
 *   (BOOL) TRUE if can move player, FALSE if player loosed.
 */
BOOL tlr::server::GetNewPosition( INT Id )
{
  BOOL ret = TRUE;
  tlr::vec2 NewPos = (tlr::vec2(cosf(Players[Id].PosAngle), sinf(Players[Id].PosAngle)) *
                      Players[Id].Speed * (Timer.GlobalTime - Players[Id].LastTime)) +
                     Players[Id].Coords[Players[Id].Coords.Size() - 1];
  DBL
    delta_x = NewPos.X - Players[Id].Coords[Players[Id].Coords.Size() - 1].X,
    delta_z = NewPos.Z - Players[Id].Coords[Players[Id].Coords.Size() - 1].Z;

  Players[Id].LastTime = Timer.GlobalTime;

  for (INT i = 0; i < Players.Size(); i++)
    if (i != Id)
      for (INT j = 1; j < Players[i].Coords.Size(); j++)
      {
        DBL Enumer = delta_x * (Players[i].Coords[j].X - Players[i].Coords[j - 1].X);
      }

  return ret;
} /* End of 'tlr::server::GetNewPosition' function */

/* Server thread function.
 * ARGUMENTS:
 *   - start thread parameters - pointer to server class:
 *       VOID *Params;
 * RETURNS:
 *   (DWORD) exit code.
 */
DWORD WINAPI tlr::server::ServerThrdFunc( VOID *Params )
{
#if 0

  server *Svr = (server *)Params;
  Svr->StartTime = Svr->Timer.GlobalTime;
  MSGBASE *BaseMsg = NULL;

  // Player connection
  BaseMsg = BaseMsg->GetBaseMsg(Svr->Check->RecvSrv());
  if (BaseMsg->Id == MSGBASE::REGISTRY)
  {
    MESSAGE_REGISTRY *RegMsg = BaseMsg->GetRegistry();
    PLAYER_SVR Player;

    memcpy(Player.Name, RegMsg->PlayerName, MaxPlayerName);
    RegMsg->PlayerId = 0;
    Svr->Check->SendSer(RegMsg);
    Player.Coords << vec2(0, 0);
    Player.Id = 0;
    Player.PosAngle = 0;
    Svr->Players << Player;
    Svr->PlayersState << TRUE;

    /* Game play */
    while (GetNewPosition(0))
    {
    }
  }

#endif // 0
  return 0;
} /* End of 'tlr::server::ServerThrdFunc' function */

/* Create server thread function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::server::CreateServer( VOID *Net )
{
  Check = (tlr::check *)Net;
  hThrd = CreateThread(NULL, 0, tlr::server::ServerThrdFunc, (VOID *)this, 0, &ThrdID);
  //SetThreadPriority(TUP_hThrd, THREAD_PRIORITY_HIGHEST);
} /* End of 'tlr::server::CreateServer' function */

/* END OF 'SERVER.CPP' FILE */
