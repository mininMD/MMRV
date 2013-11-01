/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MAIN.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Main startup module.
 * PROGRAMMER  : CGSG'2013.
 *               Maria Abramova,
 *               Vasiliy Cheptsov,
 *               Nikita Gaevoy,
 *               Aleksandra Gorskaya,
 *               Stanislav Petrov,
 *               Vsevolod Poletaev,
 *               Vyacheslav Rusanov,
 *               Leonid Voroshilov,
 *               Tatyana Sankova,
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#include <stdlib.h>
#include <math.h>

#include "tlr.h"

/* Unit sample class */
class my_unit : public tlr::unit
{
private:
  /* Stored pointer to startup unit */
  tlr::unit *StartUp;
  tlr::geom_prim Obj;
public:
  /* Class constructor.
   * ARGUMENTS:
   *   - pointer to animation system:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  my_unit( tlr::anim *Ani )
  {
    StartUp = tlr::units::AddStartup(*Ani);
    Obj.Load(Ani, "BIN/MODELS/LightCycle/cycle.obj");
  } /* End of 'my_unit' constructor */

  /* Class destructor */
  ~my_unit( VOID )
  {
  } /* End of '~my_unit' destructor */

  /* New frame response function.
   * ARGUMENTS:
   *   - pointer to animation handle object:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  VOID Response( tlr::anim *Ani )
  {
    if (Ani->Keys[VK_ESCAPE])
      Ani->DoExit();
    if (Ani->IsPressed('F'))
      Ani->SetFullScreen(!Ani->GetFullScreen());
    if (Ani->IsPressed('G') && StartUp == NULL)
      StartUp = tlr::units::AddStartup(*Ani);
    if (StartUp != NULL)
    {
      if (Ani->IsPressed('1'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)10));
      if (Ani->IsPressed('2'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)20));
      if (Ani->IsPressed('3'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)30));
      if (Ani->IsPressed('4'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)40));
      if (Ani->IsPressed('5'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)50));
      if (Ani->IsPressed('6'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)60));
      if (Ani->IsPressed('7'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)70));
      if (Ani->IsPressed('8'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)80));
      if (Ani->IsPressed('9'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)100));
      if (Ani->IsPressed('0'))
        StartUp->Handle(tlr::unit::msg(2, (VOID *)(INT)0));
      if (Ani->IsPressed('S'))
      {
        StartUp->Handle(tlr::unit::msg(1, (VOID *)Ani));
        StartUp = NULL;
      }
    }
  } /* End of 'Response' function */

  /* Render object function.
   * ARGUMENTS:
   *   - pointer to animation handle object:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  VOID Render( tlr::anim *Ani )
  {
    Obj.Draw(Ani);

    glColor3d(1, 0.7, 0.7);
    Ani->PrintF(-0.9, 0.9, "Full: %d [FPS: %.5f]", 30, Ani->FPS);
  } /* End of 'Render' function */
}; /* End of 'my_unit' class */

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter:
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdStr, INT CmdShow )
{

  tlr::anim MyAnim;

  tlr::shader sh;

  tlr::shader::IsLog = TRUE;
  sh.Init("BIN/a.vert", "BIN/a.frag");


  MyAnim << new my_unit(&MyAnim);
  MyAnim.SetFullScreen(TRUE);
  
  MyAnim.Run();
  return 30;
} /* End of 'WinMain' function */

/* END OF 'MAIN.CPP' FILE */
