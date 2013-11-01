/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PLAYER.H
 * PURPOSE     : Tough Light Racing project.
 *               Player build realisation.
 *               Class player build.
 * PROGRAMMER  : CGSG'2013.
 *               Alexandra Gorskaya.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../tlrdef.h"

#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <math.h>

#define PLAYERS_RADIUS 0.3
#define SPHERES_MERIDIANS 25

/* Tough network flyer project namespace */
namespace tlr
{
  /* Class of build player object */
  class shape_player
  {
  private:

  public:
    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    shape_player( VOID )
    {
    } /* End of 'shape_player' constructor */

    /* Sphere draw function 
     * ARGUMENTS: 
     *   - sphere SphereCenter coordinates:
     *       const vec &SphereCenter;
     *   - sphere radius:
     *       double Radius;
     *   - qantity of meridian
     *       INT N_Meridian
     * RETURNS: None.
     */
   static VOID Sphere( vec CenterS, FLT RadiusS, INT N_Meridian )
    {
      INT M = N_Meridian;
      FLT
        x_t, y_t, z_t,
        theta, theta1, phy, RadiusM = RadiusS/4;

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
//          glTexCoord2d((FLT)j / M, (FLT)i / N);
          glColor3d(0.2, 0.2, 0.5);
          glNormal3d(x_t, y_t, z_t);
          glVertex3d(CenterS.X + RadiusS * x_t, CenterS.Y + RadiusS * y_t, CenterS.Z + RadiusS * z_t);

          x_t = sin(theta1) * sin(phy);
          y_t = cos(theta1);
          z_t = sin(theta1) * cos(phy);
//          glTexCoord2d((FLT)j / M, (FLT)i / N);
          glColor3d(0, 0, 0.9);
          glNormal3d(x_t, y_t, z_t);
          glVertex3d(CenterS.X + RadiusS * x_t, CenterS.Y + RadiusS * y_t, CenterS.Z + RadiusS * z_t);
        }
        glEnd();
      } 
    } /* End of 'TLR_Sphere' function */
  }; /* End of 'shape_player' class */
} /* End of 'tlr' namespace */

#endif /* _PLAYER_H_ */

/* END OF 'PLAYER.H' FILE */
