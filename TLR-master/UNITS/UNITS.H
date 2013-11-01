/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : UNITS.H
 * PURPOSE     : Tough Light Racing project.
 *               Common definitions module.
 * PROGRAMMER  : CGSG'2013.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Create animation units functions namespace */
  namespace units
  {
    /* Add strup unit function */
    unit * AddStartup( anim &Ani );
    /* Add shape_field unit function */
    unit * AddShapeField( anim &Ani );
  } /* end of 'units' namespace */
} /* end of 'tlr' namespace */

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */
