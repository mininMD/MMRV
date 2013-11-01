/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : ANIM.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Animation system class implementation.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 01.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../tlr.h"

/* Class constructor.
 * ARGUMENTS:
 *   - render window handle:
 *       HWND &hWndRender;
 */
tlr::anim::anim( VOID ) :
  render(const_cast<HWND &>(win::hWnd)),
  input(const_cast<HWND &>(win::hWnd))
{
} /* End of 'tlr::anim::anim' constructor */

/* Class destructor.
 * ARGUMENTS:
 *   - render window handle:
 *       HWND hWndRender;
 */
tlr::anim::~anim( VOID )
{
  /* Remove all units */
  for (INT i = 0; i < Units.Size(); i++)
    delete Units[i];
} /* End of 'tlr::anim::~anim' destructor */

/* Resize window handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::anim::Resize( VOID )
{
  render::Resize(win::W, win::H);
} /* End of 'tlr::anim::Resize' function */

/* Redraw window content function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID tlr::anim::Paint( HDC hDC )
{
  CopyFrame();
  IncrFrameCount();
} /* End of 'tlr::anim::Paint' function */

/* Activate window changing handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::anim::Activate( VOID )
{
  if (IsActive)
    SetPause(FALSE);
  else
    SetPause(TRUE);
} /* End of 'tlr::anim::Activate' function */

/* Timer event handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::anim::Timer( VOID )
{
  /* Handle timer */
  timer::Response();
  static CHAR Buf[100];
  sprintf(Buf, "fps: %.5f", FPS);
  SetWindowText(win::hWnd, Buf);

  /* Handle input system */
  input::Response();

  /* Hanlde animation objects */
  for (INT i = 0; i < Units.Size(); i++)
    Units[i]->Response(this);

  StartFrame();
  for (INT i = 0; i < Units.Size(); i++)
  {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    Units[i]->Render(this);
    glPopAttrib();
  }
  EndFrame();
  CopyFrame();
  IncrFrameCount();
} /* End of 'tlr::anim::Timer' function */

/* Add unit to animation stock function.
 * ARGUMENTS:
 *   - pointer to unit to be add:
 *       unit *Uni;
 * RETURNS:
 *   (anim &) self reference.
 */
tlr::anim & tlr::anim::operator<<( tlr::unit *Uni )
{
  Units << Uni;
  return *this;
} /* End of 'tlr::anim::operator<<' function */

/* Delete unit from animation system function.
 * ARGUMENTS:
 *   - pointer to unit to be delete:
 *       unit *Uni;
 * RETURNS: None.
 */
VOID tlr::anim::DeleteUnit( unit *Uni )
{
  for (INT i = 0; i < Units.Size(); i++)
    if (Units[i] == Uni)
    {
      delete Units[i];
      Units.StableDelete(i);
    }
} /* End of 'tlr::anim::DeleteUnit' function */

/* END OF 'ANIM.CPP' FILE */
