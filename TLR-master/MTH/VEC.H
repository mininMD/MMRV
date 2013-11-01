/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : VEC.H
 * PURPOSE     : Tough Light Racing project.
 *               Mathematic support header file.
 *               3D vector support header file.
 * PROGRAMMER  : CGSG'2013.
 *               Leonid Voroshilov
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __VEC_H_
#define __VEC_H_

#include "mthdef.h"
#include <math.h>
namespace mth
{
  /* Forward reference */
  template<class Type>
    class matr;
  /* Space vector class */
  template<class Type>
    class vec
    {
    public:
      /* Vector coordinates */
      Type X, Y, Z;

      /* Default constructor */
      vec( VOID )
      {
      } /* End of 'vec' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - value for all coordinates:
       *       Type Val;
       */
      explicit vec( Type Val ) : X(Val), Y(Val), Z(Val)
      {
      } /* End of 'vec' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - coordinate values:
       *       Type NewX, NewY, NewZ;
       */
      explicit vec( Type NewX, Type NewY, Type NewZ ) :
        X(NewX), Y(NewY), Z(NewZ)
      {
      } /* End of 'vec' constructor */

      /* Set new coordinates function.
       * ARGUMENTS:
       *   - coordinate values:
       *       Type NewX, NewY, NewZ;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & Set( Type NewX, Type NewY, Type NewZ )
      {
        X = NewX;
        Y = NewY;
        Z = NewZ;
        return *this;
      } /* End of 'Set' function */

      /* Get coordinate by index function.
       * ARGUMENTS:
       *   - coordinate index:
       *       INT I;
       * RETURNS:
       *   (Type &) reference to coordinate.
       */
      Type & operator[]( INT I )
      {
        assert(I >= 0 && I <= 2);
        return *(&X + I);
      } /* End of 'operator[]' function */

      /* Get vectors dot product function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec &V;
       * RETURNS:
       *   (Type) dot product result.
       */
      Type operator&( const vec &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Get vectors cross product function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec &V;
       * RETURNS:
       *   (vec) cross product result.
       */
      vec operator%( const vec &V ) const
      {
        return vec(Y * V.Z - Z * V.Y,
                   Z * V.X - X * V.Z,
                   X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* Get vectors by-components product function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec &V;
       * RETURNS:
       *   (vec) by-components product result.
       */
      vec operator*( const vec &V ) const
      {
        return vec(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* Get vectors by-components product with assignment function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec &V;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & operator*=( const vec &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply vector by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec) result vector.
       */
      vec operator*( Type N ) const
      {
        return vec(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */

      /* Multiply vector by number with assignment function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & operator*=( Type N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide vector by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec) result vector.
       */
      vec operator/( Type N ) const
      {
        return vec(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Divide vector by number with assignment function.
       * ARGUMENTS:
       *   - number to be divide:
       *       Type N;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & operator/=( Type N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec &V;
       * RETURNS:
       *   (vec) result vector.
       */
      vec operator+( const vec &V ) const
      {
        return vec(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Add two vectors with assignment function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec &V;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & operator+=( const vec &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - vector to be subtract:
       *       const vec &V;
       * RETURNS:
       *   (vec) result vector.
       */
      vec operator-( const vec &V ) const
      {
        return vec(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Subtract two vectors with assignment function.
       * ARGUMENTS:
       *   - vector to be subtract:
       *       const vec &V;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & operator-=( const vec &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) result vector.
       */
      vec operator-( VOID ) const
      {
        return vec(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Negate vector with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & Negate( VOID )
      {
        X = -X;
        Y = -Y;
        Z = -Z;
        return *this;
      } /* End of 'Negate' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec) result vector.
       */
      vec Normalizing( VOID ) const
      {
        Type len = X * X + Y * Y + Z * Z;

        if (len == 0 || len == 1)
          return *this;
        len = sqrt(len);
        return vec(X / len, Y / len, Z / len);
      } /* End of 'Normalizing' function */

      /* Normalize vector with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & Normalize( VOID )
      {
        Type len = X * X + Y * Y + Z * Z;

        if (len == 0 || len == 1)
          return *this;
        len = sqrt(len);
        X /= len;
        Y /= len;
        Z /= len;
        return *this;
      } /* End of 'Normalize' function */

      /* Get vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
      Type operator!( VOID ) const
      {
        Type len = X * X + Y * Y + Z * Z;

        if (len == 0 || len == 1)
          return len;
        return sqrt(len);
      } /* End of 'operator!' function */

      /* Get vector squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length.
       */
      Type Len2( VOID ) const
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Len2' function */

      /* Clamp vector function
       * ARGUMENTS:
       *   - minimal vector value:
       *       Type Min;
       *   - maximum vector value:
       *       Type Max;
       * RETURNS:
       *   (vec) clamped vector.
       */
      vec Clamping( Type Min = 0, Type Max = 1 ) const
      {
        return vec(X < Min ? Min : X > Max ? Max : X,
                   Y < Min ? Min : Y > Max ? Max : Y,
                   Z < Min ? Min : Z > Max ? Max : Z);
      } /* End of 'Clamping' function */

      /* Clamp vector function.
       * ARGUMENTS:
       *   - minimal vector value:
       *       Type Min;
       *   - maximum vector value:
       *       Type Max;
       * RETURNS:
       *   (vec &) self reference to vector.
       */
      vec & Clamp( Type Min = 0, Type Max = 1 )
      {
        if (X < Min)
          X = Min;
        else
          if (X > Max)
            X = Max;
        if (Y < Min)
          Y = Min;
        else
          if (Y > Max)
            Y = Max;
        if (Z < Min)
          Z = Min;
        else
          if (Z > Max)
            Z = Max;
        return *this;
      } /* End of 'Clamp' function */

      /* Convert 3d vector to 2d.
       * ARGUMENTS:
       *   - vector to converted:
       *       vec2 In;
       * RETURNS:
       *   (vec)  converting vector.
       */
      vec2<Type> ConvVec( VOID )
      {
        return vec2<Type>(X, Z);
      } /* End of 'ConVec' function*/

      /* Convert 3d vector to 2d.
       * ARGUMENTS:
       *   - vector to converted:
       *     vec2 In;
       * RETURNS:
       *   (vec)  converting vector.
       */
      vec & SubAbs( Type a )
      {
        Type tmp;
        if (X < 0)
          tmp = -1;
        else
          tmp = 1;
        X = abs(X) - a;
        if (X < 0)
          X = 0;
        else
          X *= tmp;

        if (Y < 0)
          tmp = -1;
        else
          tmp = 1;
        Y = abs(Y) - a;
        if (Y < 0)
          Y = 0;
        else
          Y *= tmp;

        if (Z < 0)
          tmp = -1;
        else
          tmp = 1;
        Z = abs(Z) - a;
        if (Z < 0)
          Z = 0;
        else
          Z *= tmp;

        return *this;
      } /* End of 'ConVec' function*/



    }; /* End of 'vec2' class */
} /* End of 'mth' namespace */



#endif /* __VEC_H_ */
/* End of 'VEC.H' file */
