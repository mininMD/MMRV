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

#include "../tlrdef.h"
#include "../tlr.h"

#ifndef __FIELD_H_
#define __FIELD_H_

namespace tlr
{
  /* Drawing field class */
  class shape_field : public tlr::unit
  {
    stock<tlr::PLAYER> P;
    tlr::prim PrimPlane, PrimCylinder;        // primitives
    stock<mth::vec<FLT>> Speed, CurrentCoord; // players speed and coordinates
    INT MyId;                                 // Player ID
    INT NumOfPlayers;                         // quantity of players
    tlr::material *Mat;

    /* Killing loser.
     * ARGUMENTS:
     *  - player to kill:
     *    PLAYER &P;
     *  - player speed:
     *    vec &Speed;
     *  - player coordinates:
     *    vec &CurrentGlobalCoord;
     * RETURNS:
     *   None.
     */
    VOID KillPlayer ( tlr::PLAYER &P, INT i )
    {
      CurrentCoord[i] += Speed[i];
      if (CurrentCoord[i].Y < 0)
        CurrentCoord[i].Y = 0;
      Speed[i].SubAbs (0.03);
      glBegin(GL_TRIANGLES);
      tlr::shape_player::Sphere (CurrentCoord[i], 0.1, 8);
      glEnd();
    } // End of 'KillPlayer' function

  public:
   /* Class constructor.
    * ARGUMENTS:
    *   - pointer to animation system:
    *       tlr::anim *Ani;
    * RETURNS: None.
    */
    shape_field( tlr::anim *Ani ) : MyId(0), NumOfPlayers(0)
    {
      Mat = Ani->Create("Default");
      Mat->Shader.Init("BIN/SHADERS/Def.vert", "BIN/SHADERS/Def.frag");
      Mat->Map[1].LoadFile("BIN/TEXTURES/A.TGA");
      tlr::prim::SetDefaultMaterial(Mat);
      tlr::prim::SetDefaultColor(tlr::color(1, 0, 0));
    } /* End of 'startup_unit' constructor */

    /* Set new ID and player speed.
     * ARGUMENTS:
     *  - new ID:
     *    INT MyNewId;
     *  - Speed:
     *    vec S;
     *  - num of player:
     *    INT MyNewId;
     * RETURNS:
     *   None.
     */
    VOID Set( INT MyNewId, tlr::vec2 S, INT Num )
    {
      assert(Num > 0 && Num < NumOfPlayers);
      if (Num > Speed.Size())
      {
        Speed.Reset();
        for (INT i = 0; i < NumOfPlayers; i++)
          Speed << vec(0);
      }
      Speed[Num] = S.ConvVec2(0.2);
      MyId = MyNewId;
    } // End of 'Set' function

   /* Handle message function.
    * ARGUMENTS:
    *   - message data reference:
    *       msg &M;
    * RETURNS:
    *   (INT) due to message and unit type.
    */
    INT Handle (tlr::unit::msg &M)
    {
      P << tlr::PLAYER();
      P[0].Id = 0;
      P[0].Coord << vec2 (0, 0);
      P[0].IsActive = 1;
      return 0;
    } // End of 'Handle' function

    /* Drawing field.
     * ARGUMENTS:
     *  - stock of players to draw:
     *    stock<PLAYER> &P;
     * RETURNS:
     *   None.
     */
    VOID Render ( anim *Ani )
    {
      INT i;

      Ani->MatrWorld = tlr::matr().Set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
      Ani->MatrView = Ani->MatrProj = Ani->MatrWorld;
      Ani->MatrProj = tlr::matr().MatrProjection(-1, 1, -1, 1, 1, 1000);
      Ani->MatrView = tlr::matr().MatrViewLookAt(tlr::vec(10 * sin(Ani->Time), 15, 10 * cos(Ani->Time)), tlr::vec(0, 0, 0), tlr::vec(0, 1, 0));;
      Mat->Apply(Ani);

//      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      PrimPlane.SetDefaultColor(tlr::color(1, 1, 1));
      PrimPlane.CreatePlane(1, 1, tlr::vec(-30, 0, -30), tlr::vec(0, 0, 60), tlr::vec(60, 0, 0));
      Ani->DrawPrim(PrimPlane);

      PrimCylinder.SetDefaultColor(tlr::color(0, 0, 0));
      PrimCylinder.CreateCylinder(30, 4, 300, 1, tlr::vec(0, 0, 0));
      Ani->DrawPrim(PrimCylinder);
//]      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if (Speed.Size() < P.Size())
      {
        Speed.Reset();
        for (i = 0; i < P.Size(); i++)
          Speed << vec(0);
      }
      if (CurrentCoord.Size() < P.Size())
      {
        CurrentCoord.Reset();
        for (i = 0; i < P.Size(); i++)
          if (P[i].Coord.Size() > 0)
            CurrentCoord << mth::vec<FLT> (P[i].Coord.Last().X, 0, P[i].Coord.Last().Z);
          else
            CurrentCoord << mth::vec<FLT> (0);
      }
      else
        for (INT i = 0; i < P.Size(); i++)
          if (P[i].IsActive)
          {
            if (P[i].Coord.Size() > 1)
              Speed[i] = mth::vec<FLT> (P[i].Coord.Last().X - P[i].Coord[P[i].Coord.Size() - 2].X, 0, P[i].Coord.Last().Z - P[i].Coord[P[i].Coord.Size() - 2].Z);
            else
              Speed[i] = mth::vec<FLT> (0);
          }

      for (i = 0; i < P.Size(); i++)
      {
        //if (P[i].ID == MyID)
        //  camera (CurrentCoord);
        if (P[i].IsActive)
          tlr::shape_player::Sphere (CurrentCoord[i], 0.1, 8);
        else
          KillPlayer(P[i], i);
      }
      for (i = 0; i < P.Size(); i++)
      {
        glColor3d (i / 5.0, i / 5.0, i / 5.0);
        glBegin(GL_TRIANGLE_STRIP);
        for (INT j = 0; j < P[i].Coord.Size(); j++)
        {
          glVertex3d (P[i].Coord[j].X, 0, P[i].Coord[j].Z);
          glVertex3d (P[i].Coord[j].X, 0.1, P[i].Coord[j].Z);
        }
        glEnd();
      }
    } // End of 'DrawField' function
  }; // End of 'field' class
} // end of 'tlr' namespace

#endif /* __FIELD_H_ */

/* END OF 'FIELD.H' FILE */
