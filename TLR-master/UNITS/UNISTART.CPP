/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RENDER.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Rendering engene class implementation.
 * PROGRAMMER  : CGSG'2013.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <stdio.h>

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

#include "../tlr.h"

/* Startup animation unit class */
class startup_unit : public tlr::unit
{
private:
  /* Logo images */
  tlr::image Logo, Bar;
  tlr::material *Mat;
  DBL PerCent;
public:
  /* Class constructor.
   * ARGUMENTS:
   *   - pointer to animation system:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  startup_unit( tlr::anim *Ani ) :
    PerCent(0),
    Logo("BIN/TEXTURES/TLRSTART.TGA"),
    Bar("BIN/TEXTURES/TLRPBAR.TGA")
  {
    Mat = Ani->Create("Default");
    Mat->Shader.Init("BIN/SHADERS/Def.vert", "BIN/SHADERS/Def.frag");
    Mat->Map[1].LoadFile("BIN/TEXTURES/A.TGA");
    tlr::prim::SetDefaultMaterial(Mat);
    tlr::prim::SetDefaultColor(tlr::color(1, 0, 0));
  } /* End of 'startup_unit' constructor */

  /* Class destructor */
  ~startup_unit( VOID )
  {
  } /* End of '~startup_unit' destructor */

  /* New frame response function.
   * ARGUMENTS:
   *   - pointer to animation handle object:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  VOID Response( tlr::anim *Ani )
  {
  } /* End of 'Response' function */

  /* Handle message function.
   * ARGUMENTS:
   *   - message data reference:
   *       msg &M;
   * RETURNS:
   *   (INT) due to message and unit type.
   */
  INT Handle( msg &M )
  {
    tlr::anim *Ani = (tlr::anim *)M.Data;
    if (M.Id == 1 && Ani != NULL)
      Ani->DeleteUnit(this);
    else if (M.Id == 2)
      PerCent = (INT)M.Data;
    return 0;
  } /* End of 'Handle' function */

  /* Render object function.
   * ARGUMENTS:
   *   - pointer to animation handle object:
   *       tlr::anim *Ani;
   * RETURNS: None.
   */
  VOID Render( tlr::anim *Ani )
  {
    /* Draw text and grid */
    Ani->MatrWorld = tlr::matr().Set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    Ani->MatrView = Ani->MatrProj = Ani->MatrWorld;
    Ani->MatrProj = tlr::matr().MatrProjection(-1, 1, -1, 1, 1, 1000);
    Ani->MatrView = tlr::matr().MatrViewLookAt(tlr::vec(10 * sin(Ani->Time), 15, 10 * cos(Ani->Time)), tlr::vec(0, 0, 0), tlr::vec(0, 1, 0));;
    Mat->Apply(Ani);

    glBegin(GL_LINES);
    for (INT i = -100; i <= 100; i++)
    {
      glVertex3d(-100, 0, i);
      glVertex3d(100, 0, i);
    }
    for (INT i = -100; i <= 100; i++)
    {
      glVertex3d(i, 0, -100);
      glVertex3d(i, 0, 100);
    }
    glEnd();

    tlr::prim pp;

    pp.SetDefaultColor(tlr::color(1, 1, 1));
    pp.CreatePlane(1, 1, tlr::vec(0, 0, 0), tlr::vec(8, 0, 0), tlr::vec(0, 5, 0));
    Ani->DrawPrim(pp);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    pp.SetDefaultColor(tlr::color(1, 0.30, 0.59));
    pp.CreateSphere(1, 10, 10);
    Ani->MatrWorld.SetTranslate(0, sin(Ani->Time) * 8, 0);
    Ani->DrawPrim(pp);
    Ani->MatrWorld.SetUnit();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    pp.SetDefaultColor(tlr::color(0, 1, 0));
    pp.CreateSphere(1, 10, 10, tlr::vec(-2, 0, 0));
    Ani->DrawPrim(pp);

    pp.SetDefaultColor(tlr::color(1, 0, 0));
    pp.CreateCylinder(1, 2, 10, 10, tlr::vec(3, -3, 0));
    Ani->DrawPrim(pp);

    glLoadIdentity();
    glTranslated(0, 0, 0);
    glScaled(0.130, 0.130, 0.130);
    glTranslated(-5, -1, 0);
    glRotated(30 * sin(Ani->Time * 5), 1, 1, 1);
    Ani->PrintF(5, 5, "ДОЛ \"Чайка\", 2013 год");

    glLoadIdentity();

    /* Draw plate */
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDepthMask(FALSE);
    DBL rx, ry;
    glRasterPos2d(rx = 0 - 1.0 * Logo.W / Ani->W, ry = 0 + 1.0 * Logo.H / Ani->H);
    glPixelZoom(1, -1);
    glColor3d(1, 0, 0);
    if (!Ani->Keys[VK_LSHIFT])
      Logo.Draw();
    glEnable(GL_SCISSOR_TEST);
    INT
      x = (Ani->W - Logo.W) / 2,
      y = (Ani->H - Logo.H) / 2;
    glScissor(x + 50, y, 412 * PerCent / 100.0, Logo.H);
    glRasterPos3d(rx, ry, 0.1);
    Bar.Draw();

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  } /* End of 'Render' function */
}; /* End of 'startup_unit' class */

/* Add strup unit function.
 * ARGUMENTS:
 *   - animation system reference:
 *       anim &Ani;
 * RETURNS:
 *   (tlr::unit *) pointer to created unit.
 */
tlr::unit * tlr::units::AddStartup( anim &Ani )
{
  unit *un = new startup_unit(&Ani);
  Ani << un;
  return un;
} /* End of 'tlr::units::AddStartup' function */

/* END OF 'UNISTART.CPP' FILE */
