/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MAP.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Debug info field module.
 *               Map class implementation.
 * PROGRAMMER  : CGSG'2013.
 *               Maria Abramova.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../tlr.h"

/* The draw player function.
 * ARGUMENTS:
 *   - structure with player information:
 *       PLAYER &P;
 * RETURNS:
 *   None.
 */
VOID tlr::map2d::DrawPlayer( PLAYER &P, anim *Ani )
{
    glColor3d(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (INT i = 0; i < P.Coord.Size(); i++)
      glVertex2d(P.Coord[i].X, P.Coord[i].Z);
    glEnd();
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3d(0, 1, 0);
    glVertex2d(P.Coord.Last().X, P.Coord.Last().Z);
    glEnd();
} /* End of 'tlr::map2d::DrawPlayer' function */


/* The draw map/support field function.
 * ARGUMENTS:
 *   - stock of structure with player information:
 *       stock<PLAYER> &P;
 * RETURNS:
 *   None.
 */
VOID tlr::map2d::DrawField( stock<PLAYER> &P, tlr::anim *Ani )
{
  CHAR Buf[100];
  for (INT i = 0; i < P.Size(); i++)
    if (P[i].IsActive)
    {
      DrawPlayer(P[i], Ani);
      glColor3d(0, 0, 1);
      Ani->PrintF(P[i].Coord.Last().X + 0.02, P[i].Coord.Last().Z + 0.02, P[i].PlayerName);
      sprintf(Buf, "(%.2f, %.2f)", P[i].Coord.Last().X, P[i].Coord.Last().Z);
      Ani->PrintF(P[i].Coord.Last().X + 0.02, P[i].Coord.Last().Z - 0.05, Buf);
    }

   vec CenterS = vec(0, 0, 0);
   FLT RadiusS = 1;
   INT N_Meridian = 25;
   glColor3d(1, 1, 0);
   INT M = N_Meridian;
   FLT x_t, y_t, z_t, theta, theta1, phy, RadiusM = RadiusS / 4;

      for (INT i = 0; i < N_Meridian; i++)
      {
        theta = mth::Pi * i / N_Meridian;
        theta1 = mth::Pi * (i + 1) / N_Meridian;

        glBegin(GL_QUAD_STRIP);
        for (INT j = 0; j <= M; j++)
        {
          phy = 2 * mth::Pi * j / M;

          x_t = sin(theta) * sin(phy);
          y_t = cos(theta);
          z_t = sin(theta) * cos(phy);
     
          glNormal3d(x_t, y_t, z_t);
          glVertex3d(CenterS.X + RadiusS * x_t, CenterS.Y + RadiusS * y_t, 0);

          x_t = sin(theta1) * sin(phy);
          y_t = cos(theta1);
          z_t = sin(theta1) * cos(phy);
      
          glNormal3d(x_t, y_t, z_t);
          glVertex3d(CenterS.X + RadiusS * x_t, CenterS.Y + RadiusS * y_t, 0);
        }
        glEnd();
      } 

} /* End of 'tlr::map2d::DrawField' function */

/* END OF 'MAP.CPP' FILE */
