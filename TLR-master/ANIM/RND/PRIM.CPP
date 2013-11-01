/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PRIM.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Primitive class implementation.
 * PROGRAMMER  : CGSG'2013,
 *               Stanislav Petrov.
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <math.h>

#include "../../tlr.h"

/* Default primitive data (color and material) */
tlr::color tlr::prim::DefaultColor = tlr::color(1, 0.3, 0.7, 1);
tlr::material *tlr::prim::DefaultMaterial = NULL;

/* Destructor */
tlr::prim::~prim( VOID )
{
  if (MemPool != NULL)
    delete[] MemPool;
  if (Buffs[0] != 0)
    glDeleteBuffers(2, Buffs);
  if (VBuf != 0)
    glDeleteVertexArrays(1, &VBuf);
} /* End of 'tlr::prim::~prim' destructor */

/* Create sphere function.
 * ARGUMENTS:
 *   - Radius of sphere:
 *       FLT Radius;
 *   - number of ceparate:
 *       INT N, M;
 *   - center position:
 *       vec Loc;
 * RETURNS:
 *   (tlr::prim &) self pointer.
 */
tlr::prim & tlr::prim::CreateSphere( FLT Radius, INT N, INT M, vec Loc )
{
  DOUBLE x, y, z, f, t;

  Create(GRID, N, M);

  for (INT i = 0, n = 0; i <= GridH; i++)
  {
    t = mth::Pi * i / GridH;
    for (INT j = 0; j <= GridW; j++)
    {
      VERTEX &v = Vertices[i * (GridW + 1) + j];

      f = 2 * mth::Pi * (j % GridW) / GridW;
      x = sin(t) * sin(f);
      y = cos(t);
      z = sin(t) * cos(f);
      v.N = vec(x, y, z);
      v.P = Loc + vec(Radius * x, Radius * y, Radius * z);
      v.T = tlr::UV(1.0 / GridW * j, 1.0 / GridW * i);
    }
  }
  return *this;
} /* End of 'tlr::prim::CreateSphere' function */

/* Create plane function.
 * ARGUMENTS:
 *   - primitive size parameters:
 *       INT N, M;
 *   - center position:
 *       vec Loc;
 *   - tangent vectors:
 *       vec Du, Dv;
 * RETURNS:
 *   (tlr::prim &) self pointer.
 */
tlr::prim & tlr::prim::CreatePlane( INT N, INT M, vec Loc, vec Du, vec Dv )
{
  Create(GRID, N, M);
  vec normal = (Du % Dv).Normalize();

  for (INT i = 0; i <= GridH; i++)
    for (INT j = 0; j <= GridW; j++)
    {
      VERTEX &v = Vertices[i * (GridW + 1) + j];

      v.P = Loc + Du * ((FLT)j / GridW) + Dv * ((FLT)i / GridH);
      v.N = normal;
      v.T = UV((FLT)j / GridW, (FLT)i / GridH);
    }
  return *this;
} /* End of 'tlr::prim::CreatePlane' function */

/* Create cylinder function.
 * ARGUMENTS:
 *   - cylinder circle Radius:
 *       FLT Radius;
 *   - cylinder height:
 *       FLT Height;
 *   - cylinder grid size:
 *       INT N, M;
 * RETURNS:
 *   (tlr::prim &) self pointer.
 */
tlr::prim & tlr::prim::CreateCylinder( FLT Radius, FLT Height, INT N, INT M, vec Loc )
{
  DOUBLE x, y, z;

  Create(GRID, N, M);

  for (INT i = 0, n = 0; i <= GridH; i++)
  {
    for (INT j = 0; j <= GridW; j++)
    {
      FLT f = 2 * mth::Pi * (j % GridW) / GridW;

      y = Height / GridH * i;
      x = sin(f);
      z = cos(f);
      Vertices[n].N = vec(x, 0, z);
      Vertices[n++].P = Loc + vec(Radius * x, y, Radius * z);
    }
  }
  return *this;
} /* End of 'tlr::prim::CreateCylinder' function */

/* Create cone function.
 * ARGUMENTS:
 *   - cylinder circle Radius:
 *       FLT Radius;
 *   - cylinder height:
 *       FLT Height;
 *   - cylinder grid size:
 *       INT N, M;
 * RETURNS:
 *   (tlr::prim &) self pointer.
 */
tlr::prim & tlr::prim::CreateCone( FLT Radius, FLT Height, INT N, INT M, vec Loc )
{
  DOUBLE x, y, z;

  Create(GRID, N, M);

  for (INT i = 0, n = 0; i <= GridH; i++)
  {
    for (INT j = 0; j <= GridW; j++)
    {
      FLT r;
      FLT f = 2 * mth::Pi * j / GridW;

      Vertices[n].N = vec(Height * sin(f), Radius, Height * cos(f));

      y = Height / GridH * i;
      r = Radius * (Height - y) / Height;
      x = r * sin(f);
      z = r * cos(f);
      Vertices[n++].P = Loc + vec(x, y, z);
    }
  }
  return *this;
} /* End of 'tlr::prim::CreateCone' function */

/* END OF 'PRIM.CPP' FILE */
