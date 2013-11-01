/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : VEC.H
 * PURPOSE     : Tough Light Racing project.
 *               Mathematic support header file.
 *               2D vector support header file.
 * PROGRAMMER  : CGSG'2013.
 *               Leonid Voroshilov
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __VEC2_H_
#define __VEC2_H_

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Forward reference */
  template<class Type>
  class vec;

  /* Plane vector class */
  template<class Type>
    class vec2
    {
    public:
      /* Vector coordinates */
      Type X, Z;

      /* Class default constructor.
       * ARGUMENTS: None.
       */
      vec2( VOID )
      {
      } /* End of 'vec2' function */

      /* Class constructor.
       * ARGUMENTS:
       *   - coordinate values:
       *       Type A, B;
       */
      vec2( Type A, Type B ) : X(A), Z(B)
      {
      } /* End of 'vec2' function */

      /* Get coordinate by index function.
       * ARGUMENTS:
       *   - coordinate index:
       *       INT I;
       * RETURNS:
       *   (Type &) reference to coordinate.
       */
      Type & operator[]( INT I )
      {
        assert(I >= 0 && I < 2);
        return *(&X + I);
      } /* End of 'operator[]' function */

      /* Get vectors dot product function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) dot product result.
       */
      Type operator&( const vec2 &V ) const
      {
        return X * V.X + Z * V.Z;
      } /* End of 'operator&' function */

      /* Get vectors cross product 'Z' coordinate function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) cross product 'Z' coordinate result.
       */
      Type operator%( const vec2 &V ) const
      {
        return X * V.Z - Z * V.X;
      } /* End of 'operator%' function */

      /* Get vectors by-components product function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) by-components product result.
       */
      vec2 operator*( const vec2 &V ) const
      {
        return vec2(X * V.X, Z * V.Z);
      } /* End of 'operator*' function */

      /* Get vectors by-components product with assignment function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & operator*=( const vec2 &V )
      {
        X *= V.X;
        Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply vector by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( Type N ) const
      {
        return vec2(X * N, Z * N);
      } /* End of 'operator*' function */

      /* Multiply vector by number with assignment function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & operator*=( Type N )
      {
        X *= N;
        Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide vector by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( Type N ) const
      {
        return vec2(X / N, Z / N);
      } /* End of 'operator/' function */

      /* Divide vector by number with assignment function.
       * ARGUMENTS:
       *   - number to be divide:
       *       Type N;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & operator/=( Type N )
      {
        X /= N;
        Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Z + V.Z);
      } /* End of 'operator+' function */

      /* Add two vectors with assignment function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & operator+=( const vec2 &V )
      {
        X += V.X;
        Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - vector to be subtract:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Z - V.Z);
      } /* End of 'operator-' function */

      /* Subtract two vectors with assignment function.
       * ARGUMENTS:
       *   - vector to be subtract:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & operator-=( const vec2 &V )
      {
        X -= V.X;
        Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( VOID ) const
      {
        return vec2(-X, -Z);
      } /* End of 'operator-' function */

      /* Negate vector with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & Negate( VOID )
      {
        X = -X;
        Z = -Z;
        return *this;
      } /* End of 'Negate' function */

      /* Normalize vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 Normalizing( VOID ) const
      {
        Type len = X * X + Z * Z;

        if (len == 0 || len == 1)
          return *this;
        len = sqrt(len);
        return vec2(X / len, Z / len);
      } /* End of 'Normalizing' function */

      /* Normalize vector with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & Normalize( VOID )
      {
        Type len = X * X + Z * Z;

        if (len == 0 || len == 1)
          return *this;
        len = sqrt(len);
        X /= len;
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
        Type len = X * X + Z * Z;

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
        return X * X + Z * Z;
      } /* End of 'Len2' function */

      /* Clamp vector function
       *   - minimal vector value:
       *       Type Min;
       *   - maximum vector value:
       *       Type Max;
       * RETURNS:
       *   (vec2) clamped vector.
       */
      vec2 Clamping( Type Min = 0, Type Max = 1 ) const
      {
        return vec2(X < Min ? Min : X > Max ? Max : X,
                   Z < Min ? Min : Z > Max ? Max : Z);
      } /* End of 'Clamping' function */

      /* Clamp vector function.
       * ARGUMENTS:
       *   - minimal vector value:
       *       Type Min;
       *   - maximum vector value:
       *       Type Max;
       * RETURNS:
       *   (vec2 &) self reference to vector.
       */
      vec2 & Clamp( Type Min = 0, Type Max = 1 )
      {
        if (X < Min)
          X = Min;
        else
          if (X > Max)
            X = Max;
        if (Z < Min)
          Z = Min;
        else
          if (Z > Max)
            Z = Max;
        return *this;
      } /* End of 'Clamp' function */

      /* Convert 2d vector to 3d.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec)  converting vector.
       */
      vec<Type> ConvVec2( Type Y = 0 )
      {
        return vec<Type>(X, Y, Z);
      } /* End of 'ConVec' function*/

    }; /* End of 'vec2' class */
} /* End of 'mth' namespace */
#endif /* __VEC2_H_ */



/* End of 'VEC2.H' */

