/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SERVER.H
 * PURPOSE     : Tough Light Racing project.
 *               Server module.
 *               Server class declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Vyacheslav Rusanov,
 *               Vasiliy Cheptsov.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __SERVER_H_
#define __SERVER_H_

#include "../net/netdef.h"

/* Project namespace */
namespace tlr
{
  /* Maximum number of characters in player name */
  const INT MaxPlayerName = 30;
  /* Maximum number of network clients */
  const INT MaxClientsCount = 30;
  /* Connection wait time before game start */
  const INT ConnectionTime = 30;

  /* Forward references */
  struct MESSAGE_READY;
  struct MESSAGE_GETCOORD;
  struct MESSAGE_GAMEOVER;
  struct MESSAGE_GAMELOSE;
  struct MESSAGE_GAMESTART;

  /* Base messages and messages IDs type */
  struct MSGBASE : public net::MSG
  {
    enum MSGID
    {
      OK,         // Agreement
      READY,      // Client ready to play
      GAMESTART,  // Game start
      GAMEOVER,   // Game over
      GAMELOSE,   // Game lose
      GETCOORD    // Get new coordinats
    } Id;
    INT PlayerId;

    /* Class constructur.
     * ARGUMENTS:
     *   - initial message Id:
     *       MSGID NewId;
     */
    MSGBASE( MSGID NewId = OK, UINT NewSize = sizeof(MSGBASE), INT NewPlayerId = 0 ) :
      Id(NewId), PlayerId(NewPlayerId)
    {
      MsgSize = NewSize;
    } /* End of 'MSGBASE' constructor */

    /* Get base massage from network message function.
     * ARGUMENTS:
     *   - Network message
     *       net::MSG *Msg;
     * RETURNS:
     *   (MSGBASE *) reinterpreted message pointer.
     */
    MSGBASE * GetBaseMsg( net::MSG *Msg )
    {
      return reinterpret_cast<MSGBASE *>(Msg);
    } /* End of 'GetRegistry' function */

    /* Obtain READY massage function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MESSAGE_READY *) reinterpreted message pointer.
     */
    MESSAGE_READY * GetReady( VOID )
    {
      return reinterpret_cast<MESSAGE_READY *>(this);
    } /* End of 'GetReady' function */

    /* Obtain GETCOORD massage function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MESSAGE_GETCOORD *) reinterpreted message pointer.
     */
    MESSAGE_GETCOORD * GetGetCoord( VOID )
    {
      return reinterpret_cast<MESSAGE_GETCOORD *>(this);
    } /* End of 'GetRegistry' function */

    /* Obtain GAMEOVER massage function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MESSAGE_GAMEOVER *) reinterpreted message pointer.
     */
    MESSAGE_GAMEOVER * GetGameOver( VOID )
    {
      return reinterpret_cast<MESSAGE_GAMEOVER *>(this);
    } /* End of 'GetGameOver' function */

    /* Obtain GAMELOSE massage function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MESSAGE_GAMELOSE *) reinterpreted message pointer.
     */
    MESSAGE_GAMELOSE * GetGameLose( VOID )
    {
      return reinterpret_cast<MESSAGE_GAMELOSE *>(this);
    } /* End of 'GetGameLose' function */

    /* Obtain GAMESTART massage function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MESSAGE_GAMESTART *) reinterpreted message pointer.
     */
    MESSAGE_GAMESTART * GetGameStart( VOID )
    {
      return reinterpret_cast<MESSAGE_GAMESTART *>(this);
    } /* End of 'GetGameStart' function */
  }; /* End of 'MSGBASE' structure */

  /* Get coordinats message representation type */
  struct MESSAGE_GETCOORD : public MSGBASE
  {
    stock<vec2> NewCoord;  // New coordinats for all clients
    stock<DBL> NewAngles;  // ABSOLUT new angles for all clients

    /* Class constructor */
    MESSAGE_GETCOORD( UINT NewSize = sizeof(MESSAGE_GETCOORD)) : MSGBASE(MSGBASE::GETCOORD)
    {
      MsgSize = NewSize;
    } /* End of 'MESSAGE_COORD' constructor */
  }; /* End of 'MESSAGE_COORD' struct */

  /* Game over message representation type */
  struct MESSAGE_GAMEOVER : public MSGBASE
  {
    vec2 Speed;            // Last player speed
    stock<vec2> NewCoord;  // New coordinats for all clients
    stock<DBL> NewAngles;  // ABSOLUT angles for all clients

    /* Class constructor */
    MESSAGE_GAMEOVER( UINT NewSize = sizeof(MESSAGE_GAMEOVER) ) : MSGBASE(MSGBASE::GAMEOVER)
    {
      MsgSize = NewSize;
    } /* End of 'MESSAGE_GAMEOVER' constructor */
  }; /* End of 'MESSAGE_GAMEOVER' struct */

  /* Game lose message representation type */
  struct MESSAGE_GAMELOSE : public MSGBASE
  {
    INT LooserId;          // Looser player ID
    vec2 Speed;            // Last player speed
    stock<vec2> NewCoord;  // New coordinats for all clients
    stock<DBL> NewAngles;  // ABSOLUT angles for all clients

    /* Class constructor */
    MESSAGE_GAMELOSE( UINT NewSize = sizeof(MESSAGE_GAMELOSE) ) : MSGBASE(MSGBASE::GAMELOSE)
    {
      MsgSize = NewSize;
    } /* End of 'MESSAGE_GAMELOSE' constructor */
  }; /* End of 'MESSAGE_GAMELOSE' struct */

  /* Game start message representation type */
  struct MESSAGE_GAMESTART : public MSGBASE
  {
    stock<vec2> StartCoord;                  // Start coordinats for all clients
    stock<DBL> StartAngles;                  // ABSOLUT start angles for all clients
    stock<CHAR[MaxPlayerName]> PlayerName;   // Stock full of names pf players
    INT NumOfPlayers;                        // Number of players

    /* Class constructor */
    MESSAGE_GAMESTART( UINT NewSize = sizeof(MESSAGE_GAMESTART) ) : MSGBASE(MSGBASE::GAMESTART)
    {
      MsgSize = NewSize;
    } /* End of 'MESSAGE_GAMESTART' constructor */
  }; /* End of 'MESSAGE_GAMESTART' struct */

  /* Ready player message representation type */
  struct MESSAGE_READY : public MSGBASE
  {
    INT PlayerId;              // Player ID
    CHAR Name[MaxPlayerName];  // Player name
    FLT FielRadius;            // Field radius
    
    /* Class constructor */
    MESSAGE_READY( UINT NewSize = sizeof(MESSAGE_READY) ) : MSGBASE(MSGBASE::READY)
    {
      MsgSize = NewSize;
    } /* End of 'MESSAGE_READY' constructor */
  }; /* End of 'MESSAGE_READY' struct */

  /* Player representation type for server */
  struct PLAYER_SVR
  {
    INT Id;                               // Player Id
    CHAR Name[MaxPlayerName];             // Player name
    stock<mth::vec2<FLT>, 10000> Coords;  // All player coordinats scince start game
    FLT PosAngle;                         // Position angle
    DBL LastTime;                         // Last frame time
    FLT Speed;                            // Player speed
  }; /* End of 'PLAYER_SVR' struct */

  /* Server class */
  class server
  {
  private:
    HANDLE hThrd;                    // Thread handle
    DWORD ThrdID;                    // Thread Id

    tlr::timer Timer;                // Server timer
    DBL StartTime;                   // Start server time
    tlr::check *Check;               // Check net
    stock<tlr::PLAYER_SVR> Players;  // All players
    stock<BOOL> PlayersState;        // All players state

    /* Server thread function */
    static DWORD WINAPI ServerThrdFunc( VOID *Params );

    /* Count active players number function */
    INT CountActive( VOID );

    /* Get new player position function */
    BOOL GetNewPosition( INT Id );
  public:
    /* Create server thread function */
    VOID CreateServer( VOID *Net );
  }; /* End of 'server' class */
} /* end of 'tlr' namespace */

#endif // __SERVER_H_

/* END OF 'SERVER.H' FILE */
