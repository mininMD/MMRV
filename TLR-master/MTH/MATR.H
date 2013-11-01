/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATR.H
 * PURPOSE     : Tough Light Racing project.
 *               Mathemathic support header file.
 *               Matrix support declaration module.
 * PROGRAMMER  : CGSG'2013.
 *               Leonid Voroshilov
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{

  /* Space vector class */
  template<class Type>
  class matr
  {
  public:
    /* Matrix elements */
    Type A[4][4];
    mutable Type InvA[4][4]; /* Inverse of 'A' matrix */
    mutable BOOL IsInverse; /* Flag for inverse matrix precalculate */

    /* Default constructor */
    matr( VOID ) : IsInverse(FALSE)
    {
      A[0][0] = 1;
      A[0][1] = 0;
      A[0][2] = 0;
      A[0][3] = 0;

      A[1][0] = 0;
      A[1][1] = 1;
      A[1][2] = 0;
      A[1][3] = 0;

      A[2][0] = 0;
      A[2][1] = 0;
      A[2][2] = 1;
      A[2][3] = 0;

      A[3][0] = 0;
      A[3][1] = 0;
      A[3][2] = 0;
      A[3][3] = 1;
    } /* End of 'matr' constructor */

    /* Constructor */
    matr( Type A00, Type A01, Type A02, Type A03,
      Type A10, Type A11, Type A12, Type A13,
      Type A20, Type A21, Type A22, Type A23,
      Type A30, Type A31, Type A32, Type A33 ) : IsInverse(FALSE)
    {
      A[0][0] = A00;
      A[0][1] = A01;
      A[0][2] = A02;
      A[0][3] = A03;

      A[1][0] = A10;
      A[1][1] = A11;
      A[1][2] = A12;
      A[1][3] = A13;

      A[2][0] = A20;
      A[2][1] = A21;
      A[2][2] = A22;
      A[2][3] = A23;

      A[3][0] = A30;
      A[3][1] = A31;
      A[3][2] = A32;
      A[3][3] = A33;
    } /* End of 'matr' constructor */

    /* Set matrix elements function.
    * ARGUMENTS:
    *   - matrix new values:
    *       Type
    *         A00, A01, A02, A03,
    *         A10, A11, A12, A13,
    *         A20, A21, A22, A23,
    *         A30, A31, A32, A33;
    * RETURNS:
    *   (matr &) self pointer to matrix.
    */
    matr & Set( Type A00, Type A01, Type A02, Type A03,
      Type A10, Type A11, Type A12, Type A13,
      Type A20, Type A21, Type A22, Type A23,
      Type A30, Type A31, Type A32, Type A33 )
    {
      A[0][0] = A00;
      A[0][1] = A01;
      A[0][2] = A02;
      A[0][3] = A03;

      A[1][0] = A10;
      A[1][1] = A11;
      A[1][2] = A12;
      A[1][3] = A13;

      A[2][0] = A20;
      A[2][1] = A21;
      A[2][2] = A22;
      A[2][3] = A23;

      A[3][0] = A30;
      A[3][1] = A31;
      A[3][2] = A32;
      A[3][3] = A33;

      IsInverse = FALSE;

      return *this;
    } /* End of 'Set' function */

    /* Determinant of 3x3 matrix obtain function.
     * ARGUMENTS:
     *   - matrix 3x3 elements:
     *       Type
     *         A00, A01, A02,
     *         A10, A11, A12,
     *         A20, A21, A22;
     * RETURNS:
     *   (Type) matrix determinant.
     */
    Type Determ3x3( Type A00, Type A01, Type A02,
      Type A10, Type A11, Type A12,
      Type A20, Type A21, Type A22 )
    {
      return A00 * A11 * A22 +
        A01 * A12 * A20 +
        A02 * A10 * A21 -
        A00 * A12 * A21 -
        A01 * A10 * A22 -
        A02 * A11 * A20;
    } /* End of 'Determ3x3' function */

    /* Multiply two matrix function.
     * ARGUMENTS:
     *   - matrix to be multiply:
     *       matr &M;
     * RETURNS:
     *   (matr) result of multiplication.
     */
    matr operator*( const matr &M ) const
    {
      matr res;

      res.A[0][0] = A[0][0] * M.A[0][0] + A[0][1] * M.A[1][0] + A[0][2] * M.A[2][0] + A[0][3] * M.A[3][0];
      res.A[0][1] = A[0][0] * M.A[0][1] + A[0][1] * M.A[1][1] + A[0][2] * M.A[2][1] + A[0][3] * M.A[3][1];
      res.A[0][2] = A[0][0] * M.A[0][2] + A[0][1] * M.A[1][2] + A[0][2] * M.A[2][2] + A[0][3] * M.A[3][2];
      res.A[0][3] = A[0][0] * M.A[0][3] + A[0][1] * M.A[1][3] + A[0][2] * M.A[2][3] + A[0][3] * M.A[3][3];

      res.A[1][0] = A[1][0] * M.A[0][0] + A[1][1] * M.A[1][0] + A[1][2] * M.A[2][0] + A[1][3] * M.A[3][0];
      res.A[1][1] = A[1][0] * M.A[0][1] + A[1][1] * M.A[1][1] + A[1][2] * M.A[2][1] + A[1][3] * M.A[3][1];
      res.A[1][2] = A[1][0] * M.A[0][2] + A[1][1] * M.A[1][2] + A[1][2] * M.A[2][2] + A[1][3] * M.A[3][2];
      res.A[1][3] = A[1][0] * M.A[0][3] + A[1][1] * M.A[1][3] + A[1][2] * M.A[2][3] + A[1][3] * M.A[3][3];

      res.A[2][0] = A[2][0] * M.A[0][0] + A[2][1] * M.A[1][0] + A[2][2] * M.A[2][0] + A[2][3] * M.A[3][0];
      res.A[2][1] = A[2][0] * M.A[0][1] + A[2][1] * M.A[1][1] + A[2][2] * M.A[2][1] + A[2][3] * M.A[3][1];
      res.A[2][2] = A[2][0] * M.A[0][2] + A[2][1] * M.A[1][2] + A[2][2] * M.A[2][2] + A[2][3] * M.A[3][2];
      res.A[2][3] = A[2][0] * M.A[0][3] + A[2][1] * M.A[1][3] + A[2][2] * M.A[2][3] + A[2][3] * M.A[3][3];

      res.A[3][0] = A[3][0] * M.A[0][0] + A[3][1] * M.A[1][0] + A[3][2] * M.A[2][0] + A[3][3] * M.A[3][0];
      res.A[3][1] = A[3][0] * M.A[0][1] + A[3][1] * M.A[1][1] + A[3][2] * M.A[2][1] + A[3][3] * M.A[3][1];
      res.A[3][2] = A[3][0] * M.A[0][2] + A[3][1] * M.A[1][2] + A[3][2] * M.A[2][2] + A[3][3] * M.A[3][2];
      res.A[3][3] = A[3][0] * M.A[0][3] + A[3][1] * M.A[1][3] + A[3][2] * M.A[2][3] + A[3][3] * M.A[3][3];

      return res;
    } /* End of 'operator*' function */

    /* Multiply two matrix with assignment operator.
    * ARGUMENTS:
    *   - matrix to be multiply:
    *       Matr &A;
    * RETURNS:
    *   (matr &) self pointer to matrix.
    */
    matr & operator*=( const matr &A )
    {
      *this = *this * A;
      IsInverse = FALSE;
      return *this;
    } /* End of 'operator*=' function */

    /* Determinant of matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) matrix determinant.
     */
    Type Determ( VOID )
    {
      return
        A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
        A[2][1], A[2][2], A[2][3],
        A[3][1], A[3][2], A[3][3]) -
        A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
        A[2][0], A[2][2], A[2][3],
        A[3][0], A[3][2], A[3][3]) +
        A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
        A[2][0], A[2][1], A[2][3],
        A[3][0], A[3][1], A[3][3]) -
        A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
        A[2][0], A[2][1], A[2][2],
        A[3][0], A[3][1], A[3][2]);
    } /* End of 'Determ' function */

    /* Set union matrix function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SetUnit (VOID)
    {
      A[0][0] = 1;
      A[0][1] = 0;
      A[0][2] = 0;
      A[0][3] = 0;

      A[1][0] = 0;
      A[1][1] = 1;
      A[1][2] = 0;
      A[1][3] = 0;

      A[2][0] = 0;
      A[2][1] = 0;
      A[2][2] = 1;
      A[2][3] = 0;

      A[3][0] = 0;
      A[3][1] = 0;
      A[3][2] = 0;
      A[3][3] = 1;

    }/* End of 'Set1' function */

    /* Inverse matrix function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (matr) inverse matrix.
     */
    matr Inverse( VOID )
    {
      matr r;
      Type det = Determ();

      if (det == 0)
        return r;

      r.A[0][0] =
        Determ3x3(A[1][1], A[1][2], A[1][3],
        A[2][1], A[2][2], A[2][3],
        A[3][1], A[3][2], A[3][3]) / det;
      r.A[1][0] = 
        -Determ3x3(A[1][0], A[1][2], A[1][3],
        A[2][0], A[2][2], A[2][3],
        A[3][0], A[3][2], A[3][3]) / det;
      r.A[2][0] =
        Determ3x3(A[1][0], A[1][1], A[1][3],
        A[2][0], A[2][1], A[2][3],
        A[3][0], A[3][1], A[3][3]) / det;
      r.A[3][0] =
        -Determ3x3(A[1][0], A[1][1], A[1][2],
        A[2][0], A[2][1], A[2][2],
        A[3][0], A[3][1], A[3][2]) / det;

      r.A[0][1] =
        -Determ3x3(A[0][1], A[0][2], A[0][3],
        A[2][1], A[2][2], A[2][3],
        A[3][1], A[3][2], A[3][3]) / det;
      r.A[1][1] = 
        Determ3x3(A[0][0], A[0][2], A[0][3],
        A[2][0], A[2][2], A[2][3],
        A[3][0], A[3][2], A[3][3]) / det;
      r.A[2][1] =
        -Determ3x3(A[0][0], A[0][1], A[0][3],
        A[2][0], A[2][1], A[2][3],
        A[3][0], A[3][1], A[3][3]) / det;
      r.A[3][1] =
        Determ3x3(A[0][0], A[0][1], A[0][2],
        A[2][0], A[2][1], A[2][2],
        A[3][0], A[3][1], A[3][2]) / det;

      r.A[0][2] =
        Determ3x3(A[0][1], A[0][2], A[0][3],
        A[1][1], A[1][2], A[1][3],
        A[3][1], A[3][2], A[3][3]) / det;
      r.A[1][2] = 
        -Determ3x3(A[0][0], A[0][2], A[0][3],
        A[1][0], A[1][2], A[1][3],
        A[3][0], A[3][2], A[3][3]) / det;
      r.A[2][2] =
        Determ3x3(A[0][0], A[0][1], A[0][3],
        A[1][0], A[1][1], A[1][3],
        A[3][0], A[3][1], A[3][3]) / det;
      r.A[3][2] =
        -Determ3x3(A[0][0], A[0][1], A[0][2],
        A[1][0], A[1][1], A[1][2],
        A[3][0], A[3][1], A[3][2]) / det;

      r.A[0][3] =
        -Determ3x3(A[0][1], A[0][2], A[0][3],
        A[1][1], A[1][2], A[1][3],
        A[2][1], A[2][2], A[2][3]) / det;
      r.A[1][3] = 
        Determ3x3(A[0][0], A[0][2], A[0][3],
        A[1][0], A[1][2], A[1][3],
        A[2][0], A[2][2], A[2][3]) / det;
      r.A[2][3] =
        -Determ3x3(A[0][0], A[0][1], A[0][3],
        A[1][0], A[1][1], A[1][3],
        A[2][0], A[2][1], A[2][3]) / det;
      r.A[3][3] =
        Determ3x3(A[0][0], A[0][1], A[0][2],
        A[1][0], A[1][1], A[1][2],
        A[2][0], A[2][1], A[2][2]) / det;

      return r;
    } /* End of 'Inverse' function */

    /* Obtain pointer to first matrix element function.
    * ARGUMENTS: None.
    * RETURNS:
    *   (Type *) pointer to first element.
    */
    operator Type *( VOID )
    {
      return &A[0][0];
    } /* End of 'operator Type *' function */

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes):
     *       Type Dx, Dy, Dz;
     * RETURN:
     *   (matr &) self-pointer to matrix.
     */
    matr & SetTranslate( Type Dx, Type Dy, Type Dz )
    {

      A[0][0] = 1;
      A[0][1] = 0;
      A[0][2] = 0;
      A[2][2] = 0;

      A[1][0] = 0;
      A[1][1] = 1;
      A[1][2] = 0;
      A[2][2] = 0;

      A[2][0] = 0;
      A[2][1] = 0;
      A[2][2] = 1;
      A[2][3] = 0;

      A[3][0] = Dx;
      A[3][1] = Dy;
      A[3][2] = Dz;
      A[3][3] = 1;
      return *this;
    } /* End of 'SetTranslate' function */

    /* Set translation matrix function.
     * ARGUMENTS:
     *   - translation values (along axes) vector:
     *       const vec<Type> &Shift;
     * RETURN:
     *   (matr &) self-pointer to matrix.
     */
    matr & SetTranslate( const vec<Type> &Shift )
    {
      return SetTranslate(Shift.X, Shift.Y, Shift.Z);
    } /* End of 'SetTranslate' function */

    /* Rotation around 'X' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle sine and cosine function values:
    *       type AngleSine, AngleCosine;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr & RotationX( Type AngleSine, Type AngleCosine )
    {
      Type RM01, RM11, RM21, RM31, RM02, RM12, RM22, RM32;

      /* Calculate changing matrix elements */
      RM01 = A[0][1] * AngleCosine - A[0][2] * AngleSine;
      RM11 = A[1][1] * AngleCosine - A[1][2] * AngleSine;
      RM21 = A[2][1] * AngleCosine - A[2][2] * AngleSine;
      RM31 = A[3][1] * AngleCosine - A[3][2] * AngleSine;

      RM02 = A[0][1] * AngleSine + A[0][2] * AngleCosine;
      RM12 = A[1][1] * AngleSine + A[1][2] * AngleCosine;
      RM22 = A[2][1] * AngleSine + A[2][2] * AngleCosine;
      RM32 = A[3][1] * AngleSine + A[3][2] * AngleCosine;

      /* Store changed elements to matrix */
      A[0][1] = RM01;
      A[1][1] = RM11;
      A[2][1] = RM21;
      A[3][1] = RM31;

      A[0][2] = RM02;
      A[1][2] = RM12;
      A[2][2] = RM22;
      A[3][2] = RM32;

      return *this;
    } /* End of 'RotationX' function */

    /* Set rotation around 'X' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle (in degrees):
    *       TYPE AngleInDegree;
    * RETURN:
    *   (matr) self-pointer to matrix.
    */
    matr & SetRotateX( Type AngleInDegree )
    {
      FLT AngleInRadians = mth::MultiplierDegree2Radian * AngleInDegree;
      Type SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationX(SinVal, CosVal);
    } /* End of 'SetRotateX' function */


    /* Rotation around 'Y' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle sine and cosine function values:
    *       Type AngleSine, AngleCosine;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr & RotationY( Type AngleSine, Type AngleCosine ) 
    {
      Type RM00, RM10, RM20, RM30, RM02, RM12, RM22, RM32;

      /* Calculate changing matrix elements */
      RM00 = A[0][2] * AngleSine + A[0][0] * AngleCosine;
      RM10 = A[1][2] * AngleSine + A[1][0] * AngleCosine;
      RM20 = A[2][2] * AngleSine + A[2][0] * AngleCosine;
      RM30 = A[3][2] * AngleSine + A[3][0] * AngleCosine;

      RM02 = A[0][2] * AngleCosine - A[0][0] * AngleSine;
      RM12 = A[1][2] * AngleCosine - A[1][0] * AngleSine;
      RM22 = A[2][2] * AngleCosine - A[2][0] * AngleSine;
      RM32 = A[3][2] * AngleCosine - A[3][0] * AngleSine;

      /* Store changed elements to matrix */
      A[0][0] = RM00;
      A[1][0] = RM10;
      A[2][0] = RM20;
      A[3][0] = RM30;

      A[0][2] = RM02;
      A[1][2] = RM12;
      A[2][2] = RM22;
      A[3][2] = RM32;

      return *this;
    } /* End of 'RotationY' function */

    /* Set rotation around 'X' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle (in degrees):
    *       TYPE AngleInDegree;
    * RETURN:
    *   (matr) self-pointer to matrix.
    */
    matr & SetRotateY( Type AngleInDegree )
    {
      FLT AngleInRadians = mth::MultiplierDegree2Radian * AngleInDegree;
      Type SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationY(SinVal, CosVal);
    } /* End of 'SetRotateX' function */


    /* Rotation around 'Z' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle sine and cosine function values:
    *       Type AngleSine, AngleCosine;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr & RotationZ( Type AngleSine, Type AngleCosine ) 
    {
      Type RM00, RM10, RM20, RM30, RM01, RM11, RM21, RM31;

      /* Calculate changing matrix elements */
      RM00 = A[0][0] * AngleCosine - A[0][1] * AngleSine;
      RM10 = A[1][0] * AngleCosine - A[1][1] * AngleSine;
      RM20 = A[2][0] * AngleCosine - A[2][1] * AngleSine;
      RM30 = A[3][0] * AngleCosine - A[3][1] * AngleSine;

      RM01 = A[0][0] * AngleSine + A[0][1] * AngleCosine;
      RM11 = A[1][0] * AngleSine + A[1][1] * AngleCosine;
      RM21 = A[2][0] * AngleSine + A[2][1] * AngleCosine;
      RM31 = A[3][0] * AngleSine + A[3][1] * AngleCosine;

      /* Store changed elements to matrix */
      A[0][0] = RM00;
      A[1][0] = RM10;
      A[2][0] = RM20;
      A[3][0] = RM30;

      A[0][1] = RM01;
      A[1][1] = RM11;
      A[2][1] = RM21;
      A[3][1] = RM31;

      return *this;
    } /* End of 'RotationZ' function */

    /* Set rotation around 'X' axis matrix function.
    * ARGUMENTS:
    *   - rotation angle (in degrees):
    *       TYPE AngleInDegree;
    * RETURN:
    *   (matr) self-pointer to matrix.
    */
    matr & SetRotateZ( Type AngleInDegree )
    {
      FLT AngleInRadians = mth::MultiplierDegree2Radian * AngleInDegree;
      Type SinVal = sin(AngleInRadians), CosVal = cos(AngleInRadians);

      return RotationZ(SinVal, CosVal);
    } /* End of 'SetRotateX' function */

    /* Rotation around arbitrary axis matrix function.
    * ARGUMENTS:
    *   - rotation angle (in degrees):
    *       Type AngleInDegree;
    *   - rotation vector components:
    *       Type AxisX, AxisY, AxisZ;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr Rotation( Type AngleInDegree,
      Type AxisX, Type AxisY, Type AxisZ ) const
    {
      Type
        angle, s, h,
        vx, vy, vz, len,
        Rm[3][3];

      Type SinVal, CosVal;

      angle /= 2;
#ifdef __TLR_ASM__
      /* Assembler sine and cosine calculate */
      _asm {
        fld angle
          fmul mth::MultiplierDegree2Radian

          fsincos

          fstp s
          fstp h
      }
#else /* __TLR_ASM__ */
      FLT angle = AngleInDegree * mth::MultiplierDegree2Radian; 

      h = sin(AngleInRadians), s = cos(AngleInRadians);
#endif /* __TLR_ASM__ */ 

      len = AxisX * AxisX + AxisY * AxisY + AxisZ * AxisZ;
      if (COM_ABS(len) > mth::Threshold && COM_ABS(len - 1) > mth::Threshold)
      {
        len = sqrt(len);
        vx = AxisX * h / len;
        vy = AxisY * h / len;
        vz = AxisZ * h / len;
      }
      else
      {
        vx = h * AxisX;
        vy = h * AxisY;
        vz = h * AxisZ;
      }

      Rm[0][0] = 1 - 2 * (vy * vy + vz * vz);
      Rm[0][1] = 2 * vx * vy - 2 * s * vz;
      Rm[0][2] = 2 * s * vy + 2 * vx * vz;

      Rm[1][0] = 2 * vx * vy + 2 * s * vz;
      Rm[1][1] = 1 - 2 * (vx * vx + vz * vz);
      Rm[1][2] = -2 * s * vx + 2 * vy * vz;

      Rm[2][0] = -2 * s * vy + 2 * vx * vz;
      Rm[2][1] = 2 * s * vx + 2 * vy * vz;
      Rm[2][2] = 1 - 2 * (vx * vx + vy * vy);

      return
        matr(A[0][0] * Rm[0][0] + A[0][1] * Rm[1][0] + A[0][2] * Rm[2][0],
        A[0][0] * Rm[0][1] + A[0][1] * Rm[1][1] + A[0][2] * Rm[2][1],
        A[0][0] * Rm[0][2] + A[0][1] * Rm[1][2] + A[0][2] * Rm[2][2],
        A[1][0] * Rm[0][0] + A[1][1] * Rm[1][0] + A[1][2] * Rm[2][0],
        A[1][0] * Rm[0][1] + A[1][1] * Rm[1][1] + A[1][2] * Rm[2][1],
        A[1][0] * Rm[0][2] + A[1][1] * Rm[1][2] + A[1][2] * Rm[2][2],
        A[2][0] * Rm[0][0] + A[2][1] * Rm[1][0] + A[2][2] * Rm[2][0],
        A[2][0] * Rm[0][1] + A[2][1] * Rm[1][1] + A[2][2] * Rm[2][1],
        A[2][0] * Rm[0][2] + A[2][1] * Rm[1][2] + A[2][2] * Rm[2][2],
        A[3][0] * Rm[0][0] + A[3][1] * Rm[1][0] + A[3][2] * Rm[2][0],
        A[3][0] * Rm[0][1] + A[3][1] * Rm[1][1] + A[3][2] * Rm[2][1],
        A[3][0] * Rm[0][2] + A[3][1] * Rm[1][2] + A[3][2] * Rm[2][2]);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
    * ARGUMENTS:
    *   - rotation angle sine and cosine function values:
    *       Type AngleSine, AngleCosine;
    *   - rotation vector components:
    *       Type AxisX, AxisY, AxisZ;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr Rotation( Type AngleSine, Type AngleCosine,
      Type AxisX, Type AxisY, Type AxisZ ) const
    {
      return
        Rotation(mth::MultiplierRadian2Degree(atan2(AngleSine, AngleCosine)), AxisX, AxisY, AxisZ);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
    * ARGUMENTS:
    *   - rotation angle sine and cosine function values:
    *       Type AngleSine, AngleCosine;
    *   - rotation vector:
    *       const vec<type> &Vec;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr Rotation( Type AngleSine, Type AngleCosine,
      const vec<Type> &Vec ) const
    {
      return Rotation(AngleSine, AngleCosine, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Rotation around arbitrary axis matrix function.
    * ARGUMENTS:
    *   - rotation angle (in degrees):
    *       Type AngleInDegree;
    *   - rotation vector:
    *       const vec<Type> &Vec;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr Rotation( Type AngleInDegree, const vec<Type> &Vec ) const
    {
      return Rotation(AngleInDegree, Vec.X, Vec.Y, Vec.Z);
    } /* End of 'Rotation' function */

    /* Scaling along axes matrix function.
    * ARGUMENTS:
    *   - scaling axes coefficients:
    *       Type Sx, Sy, Sz;
    * RETURN:
    *   (matr) new matrix (transformed) object.
    */
    matr Scaling( Type Sx, Type Sy, Type Sz ) const
    {
      return
        matr(Sx, 0, 0, 0, 0, Sy, 0, 0, 0, 0, Sz, 0, 0, 0, 0, 1);
    } /* End of 'Scaling' function */

    /* Set View Look At matrix.
    * ARGUMENTS:
    *   - camera location vector:
    *      const vec<Type> &Loc;
    *   - direction view  vector:
    *      const vec<Type> &At;
    *   - up vector (aproximate):
    *      const vec<Type> &Up
    * RETURNS:
    *   (matr) Look-At matrix.
    */
    matr MatrViewLookAt( const vec<Type> &Loc, const vec<Type> &At, vec<Type> &Up )
    {
      vec<Type> Dir = (At - Loc).Normalize();
      vec<Type> Right = (Dir % Up).Normalize();
      Up = Right % Dir;

      matr m;
      m.A[0][0] = Right.X;
      m.A[1][0] = Right.Y;
      m.A[2][0] = Right.Z;
      m.A[3][0] = -(Right & Loc);

      m.A[0][1] = Up.X;
      m.A[1][1] = Up.Y;
      m.A[2][1] = Up.Z;
      m.A[3][1] = -(Up & Loc);

      m.A[0][2] = -Dir.X;
      m.A[1][2] = -Dir.Y;
      m.A[2][2] = -Dir.Z;
      m.A[3][2] = Dir & Loc;

      m.A[0][3] = 0;
      m.A[1][3] = 0;
      m.A[2][3] = 0;
      m.A[3][3] = 1;

      return m;
    }; /* End of 'MatrViewLookAt' function*/

    /* Set Projection matrix matrix.
    * ARGUMENTS:
    *   - borders on X:
    *      DBL l, DBL r;
    *   - borders on Y:
    *      DBL b, DBL t;
    *   - borders on Z:
    *      DBL n, DBL f;
    * RETURNS:
    *   (matr) Projection matrix.
    */
    matr MatrProjection( DBL l, DBL r, DBL b, DBL t, DBL n, DBL f )
    {
      matr M;

      M.A[0][0] = (2 * n)/(r - l);
      M.A[0][1] = 0;
      M.A[0][2] = (r + l)/(r - l);
      M.A[1][0] = 0; 
      M.A[1][1] = (2 * n)/(t - b);
      M.A[1][2] = (t + b)/(t - b);
      M.A[2][0] = 0;
      M.A[2][1] = (t + b)/(t - b);
      M.A[2][2] = -(f + n)/(f - n);

      M.A[0][3] = 0;
      M.A[1][3] = 0;
      M.A[3][2] = -2 * f * n/(f - n);

      M.A[2][3] = -1;
      M.A[3][0] = 0;
      M.A[3][1] = 0;
      M.A[3][3] = 0;

      return M;
    } /* End of 'MatrProjection' */

  }; /* End of 'matr' class */

  /* Multiply vector (matrix-row) by matrix function.
  * ARGUMENTS:
  *   - vector to be multiply:
  *       const vec<Type> &V;
  *   - matrix to be multiply:
  *       const matr<Type> &M;
  * RETURNS:
  *   (vec<Type>) result of product.
  */
  template<class Type>
  vec<Type> operator*( const vec<Type> &V, const matr<Type> &M )
  {
    Type
      x = V.X * M.A[0][0] + V.Y * M.A[0][1] + V.Z * M.A[0][2] + M.A[0][3],
      y = V.X * M.A[1][0] + V.Y * M.A[1][1] + V.Z * M.A[1][2] + M.A[1][3],
      z = V.X * M.A[2][0] + V.Y * M.A[2][1] + V.Z * M.A[2][2] + M.A[2][3],
      w = V.X * M.A[3][0] + V.Y * M.A[3][1] + V.Z * M.A[3][2] + M.A[3][3];

    if (w != 0)
      return vec(x / w, y / w, z / w);
    return vec(x, y, z);
  } /* End of 'operator*' function */

  /* Multiply matrix by vector (matrix-column) function.
  * ARGUMENTS:
  *   - matrix to be multiply:
  *       const matr<Type> &M;
  *   - vector to be multiply:
  *       const vec<Type> &V;
  * RETURNS:
  *   (vec<Type>) result of product.
  */
  template<class Type>
  vec<Type> operator*( const matr<Type> &M, const vec<Type> &V )
  {
    Type
      x = V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
      y = V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
      z = V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2],
      w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

    if (w != 0)
      return vec(x / w, y / w, z / w);
    return vec(x, y, z);
  } /* End of 'operator*' function */
}/* End of 'mth' namespace */

#endif /* __MATR_H */


