/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : CLIENT.H
 * PURPOSE     : Tough Light Racing project.
 *               Client support module.
 *               Main gameplay file.
 * PROGRAMMER  : CGSG'2013.
 *               Rusanov Vyacheslav.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __CLIENT_H_
#define __CLIENT_H_

#include "../tlr.h"

/* Project namespace */
namespace tlr
{
  /* Player representation type */
  struct PLAYER
  {
    INT Id;                             // Player ID
    CHAR PlayerName[MaxPlayerName];           // Player name
    BOOL IsActive;                      // Player state (active / not active)
    stock<vec2, 10000> Coord;           // Player coordinats
    vec2 Speed;                         // Speed before die
    stock<FLT, 10000> AbsoluteAngle;    // Absolute angle
  }; /* End of 'PLAYER' struct */
  
  /* Client support class */
  class client
  {
  public:
    /* Player own ID */
    INT MyOwnID;

    /* Count of the players */
    INT CountPlayers;

    /* Field radius */
    FLT FildsRadius;

    /* Default constructor */
    client( VOID ) : MyOwnID(0), CountPlayers(1), FildsRadius(0)
    {
    }

    /* Stock full of PLAYER structur */
    stock<PLAYER, 30> Player;

    /* Recv message from server function.*/
    INT RecvMessagefromServ( net::MSG *Msg );

    /* Send registration message */
    net::MSG * SendRegMsg( CHAR *Name );
  }; /* end of 'client' class */
} /* end of 'tlr' namespace */

#endif /* __CLIENT_H_ */

/* END OF 'CLIENT.H' FILE */
