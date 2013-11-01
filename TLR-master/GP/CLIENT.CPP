/***************************************************************
* Copyright (C) 2013
*    Computer Graphics Support Group of 30 Phys-Math Lyceum
***************************************************************/

/* FILE NAME   : CLIENT.CPP
* PURPOSE     : Tough Light Racing project.
*               Client module.
*               Client class implementation.
* PROGRAMMER  : CGSG'2013.
*               Rusanov Vyacheslav.
* LAST UPDATE : 03.08.2013
* NOTE        : Namespace 'tlr'.
*
* No part of this file may be changed without agreement of
* Computer Graphics Support Group of 30 Phys-Math Lyceum
*/


#include "../tlr.h"

/* Send registration message */
net::MSG * tlr::client::SendRegMsg( CHAR *Name )
{
  /* Send registration message */
  MESSAGE_READY *ms_ready = NULL;
  strcpy(ms_ready->Name, Name);
  return ms_ready;
}

/* Recv message from server function.
 * ARGUMENTS:
 *   - Base message:
 *       net::MSG *Msg;
 * RETURNS:
 *       (INT) Message Id: 
 */
INT tlr::client::RecvMessagefromServ(net::MSG *Msg)
{
  MSGBASE *MyMsg = NULL;

  /* Declaration messages varibles */
  MESSAGE_READY *my_redy = NULL;
  MESSAGE_GETCOORD *my_curcoord = NULL;
  MESSAGE_GAMEOVER *my_gameover = NULL;
  MESSAGE_GAMELOSE *my_gameloose = NULL;
  MESSAGE_GAMESTART *my_gamestart = NULL;

  MyMsg = MyMsg->GetBaseMsg(Msg);

  /* Message from server */
  switch (MyMsg->Id)
  {
    /* Agrement message: NOTHING TO DO */
  case MSGBASE::OK:
    return MyMsg->Id;
    /* Ready to play: get from server count of players, my own ID, field radius */
  case MSGBASE::READY:
    my_redy = MyMsg->GetReady();
    MyOwnID = my_redy->PlayerId;
    FildsRadius = my_redy->FielRadius;
    return MyMsg->Id;
    /* Get coordinates and absolute angle, players name */
  case MSGBASE::GAMESTART:
    my_gamestart = MyMsg->GetGameStart();
    CountPlayers = my_gamestart->NumOfPlayers;
    for (INT i = 0; i < my_gamestart->NumOfPlayers; i++)
      Player[i].Coord << my_gamestart->StartCoord[i];
    for (INT i = 0; i < my_gamestart->NumOfPlayers; i++)
      Player[i].AbsoluteAngle << my_gamestart->StartAngles[i];
    for (INT i = 0; i < my_gamestart->NumOfPlayers; i++)
      strcpy(Player[i].PlayerName, my_gamestart->PlayerName[i]);
    return MyMsg->Id;
    /* Game over message: Flag IsActive = FALSE, get position and speed and absolute angles*/
  case MSGBASE::GAMEOVER:
    my_gameover = MyMsg->GetGameOver();
    Player[MyOwnID].IsActive = FALSE;
    Player[MyOwnID].Speed = my_gameover->Speed;
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].Coord << my_gameloose->NewCoord[i];
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].AbsoluteAngle << my_gameloose->NewAngles[i];
    CountPlayers = 0;
    return MyMsg->Id;
    /* Game lose message: Flag IsActive = FALSE, get position and speed and absolute angles */
  case MSGBASE::GAMELOSE:
    my_gameloose = MyMsg->GetGameLose();
    Player[my_gameloose->LooserId].IsActive = FALSE;
    Player[my_gameloose->LooserId].Speed = my_gameloose->Speed;
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].Coord << my_gameloose->NewCoord[i];
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].AbsoluteAngle << my_gameloose->NewAngles[i];
    return MyMsg->Id;
    /* Get coordinate massege: get coordinate, absolute angle */
  case MSGBASE::GETCOORD:
    my_curcoord = MyMsg->GetGetCoord();
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].Coord << my_curcoord->NewCoord[i];
    for (INT i = 0; i < Player.Size(); i++)
      Player[i].AbsoluteAngle << my_curcoord->NewAngles[i];
    return MyMsg->Id;
  }
  /* Default - fail recive */
  return -1;
} /* End of 'SendMessagetoServ' function */

/* END OF 'CLIENT.CPP' FILE */