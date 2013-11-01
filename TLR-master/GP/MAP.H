/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MAP.H
 * PURPOSE     : Tough Light Racing project.
 *               Debug info field module.
 *               Map class declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Maria Abramova.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MAP_H_
#define __MAP_H_

#include "../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Map drawing class */
  class map2d
  {
  public:
    /* The draw player function */
    VOID DrawPlayer( PLAYER &P, anim *Ani );

    /* The draw map/support field function */
    VOID DrawField( stock<PLAYER> &P, anim *Ani );
  }; /* end of 'map2d' class */
} /* end of 'tlr' namespace */

#endif /* __MAP_H_ */

/* END OF 'MAP.H' FILE */
