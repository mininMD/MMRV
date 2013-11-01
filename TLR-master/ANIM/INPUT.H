/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : INPUT.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Input system class declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 01.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __INPUT_H_
#define __INPUT_H_

#include "../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Joystick button selection class */
  class joy_button
  {
  private:
    INT Button; /* Button number */
  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - button number:
     *       INT Value;
     */
    joy_button( INT Value ) : Button(Value)
    {
    } /* End of 'joy_button' function */
    friend class input;
  };

  /* Input system handle class */
  class input
  {
  private:
    /* Work window reference */
    HWND &hWnd;
  public:
    /* Input devices data */
    BYTE Keys[256], KeysOld[256];    // Keyboard keys state

    INT
      MouseX, MouseY,                // Mouse cursor position
      MouseDeltaX, MouseDeltaY,      // Relative mouse cursor shift
      MousePosOldX, MousePosOldY,    // Old mouse position
      MouseWheel,                    // Relative wheel value
      MouseBut[16], MouseButOld[16]; // Mouse buttons state

    BYTE JBut[32], JButOld[32]; // Joystick button state
    DBL Jx, Jy, Jz, Jr;         // Joystive axe
    INT JPov;                   // Point-of-View [0-8] joustick state */

    /* Class constructor */
    input( HWND &hWndRef );

    /* Response input devices function */
    VOID Response( VOID );

    /* Check keyboard keys once pressed function */
    BOOL IsPressed( INT KeyValue );

    /* Check joystic buttons once pressed function */
    BOOL IsPressed( joy_button KeyValue );

  }; /* End of 'anim' class */
} /* end of 'tlr' namespace */

#endif /* __INPUT_H_ */

/* END OF 'INPUT.H' FILE */
