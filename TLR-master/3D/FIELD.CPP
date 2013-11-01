/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : FIELD.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Animation system class declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Nikita Gaevoy.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../tlr.h"
#include "../tlrdef.h"
#include "field.h"

namespace tlr
{
   /* Add shape_field unit function.
   * ARGUMENTS:
   *   - animation system reference:
   *       anim &Ani;
   * RETURNS:
   *   (tlr::unit *) pointer to created unit.
   */
  tlr::unit * tlr::units::AddShapeField( anim &Ani )
  {
    unit *un = new tlr::shape_field (&Ani);
    Ani << un;
    return un;
  } // End of 'tlr::units::AddStartup' function
} // end of 'tlr' namespace

/* END OF 'FIELD.CPP' FILE */
