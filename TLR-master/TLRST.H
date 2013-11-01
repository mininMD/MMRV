/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TLRST.H
 * PURPOSE     : Tough Light Racing project.
 *               Single tone declaration module.
 *               Single tone template class object declaration module.
 * PROGRAMMER  : CGSG'2013.
 *               Poletaev Vsevolod.
 * LAST UPDATE : 03.08.2013
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <commondf.h>

#ifndef __TLRST_H_
#define __TLRST_H_

/* Single tone object template class */
template<class Type>
  class sngtone
  {
  private:
    static Type Instance;  // Object instance
  public:
    /* Get object instance function.
     * ARGUMENTS:
     *   None;
     * RETURNS:
     *   (Type) Object instance reference.
     */
    Type & GetInstance( VOID )
    {
      return Instance;
    } /* End of 'GetInstance' function */
  }; /* End of 'sngtone' class */

#endif  // __TLRST_H_

/* END OF 'TLRST.H' FILE */
