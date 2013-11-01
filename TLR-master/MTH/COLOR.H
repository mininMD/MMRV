/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : COLOR.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Primitive class implementation.
 * PROGRAMMER  : CGSG'2013,
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __COLOR_H_
#define __COLOR_H_

#include <math.h>

#include "mthdef.h"

/* Math support namespace */
namespace mth
{
  /* Color (triplex) class */
  template<class Type>
    class color3
    {
    public:
      /* Vector components */
      Type R, G, B;

      /* Default constructor */
      color3( VOID )
      {
      } /* End of 'color3' constructor */

      /* Monochrome color3 class constructor.
       * ARGUMENTS:
       *   - value for all components:
       *       Type Val;
       */
      explicit color3( Type Val ) : R(Val), G(Val), B(Val)
      {
      } /* End of 'color3' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - component values:
       *       Type NewR, NewG, NewB;
       */
      explicit color3( Type NewR, Type NewG, Type NewB ) :
        R(NewR), G(NewG), B(NewB)
      {
      } /* End of 'color3' constructor */

      /* Set new components function.
       * ARGUMENTS:
       *   - component values:
       *       Type NewR, NewG, NewB;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & Set( Type NewR, Type NewG, Type NewB )
      {
        R = NewR;
        G = NewG;
        B = NewB;
        return *this;
      } /* End of 'Set' function */

      /* Get component by index function.
       * ARGUMENTS:
       *   - component index:
       *       INT I;
       * RETURNS:
       *   (Type &) reference to component.
       */
      Type & operator[]( INT I )
      {
        assert(I >= 0 && I <= 2);
        return *(&R + I);
      } /* End of 'operator[]' function */

      /* Get colors by-components product function.
       * ARGUMENTS:
       *   - color3 to be multiply:
       *       const color3 &C;
       * RETURNS:
       *   (color3) by-components product result.
       */
      color3 operator*( const color3 &C ) const
      {
        return color3(R * C.R, G * C.G, B * C.B);
      } /* End of 'operator*' function */

      /* Get colors by-components product with assignment function.
       * ARGUMENTS:
       *   - color3 to be multiply:
       *       const color3 &C;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & operator*=( const color3 &C )
      {
        R *= C.R;
        G *= C.G;
        B *= C.B;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply color3 by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color3) result color3.
       */
      color3 operator*( Type N ) const
      {
        return color3(R * N, G * N, B * N);
      } /* End of 'operator*' function */

      /* Multiply color3 by number with assignment function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & operator*=( Type N )
      {
        R *= N;
        G *= N;
        B *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide color3 by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color3) result color3.
       */
      color3 operator/( Type N ) const
      {
        return color3(R / N, G / N, B / N);
      } /* End of 'operator/' function */

      /* Divide color3 by number with assignment function.
       * ARGUMENTS:
       *   - number to be divide:
       *       Type N;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & operator/=( Type N )
      {
        R /= N;
        G /= N;
        B /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - color3 to be add:
       *       const color3 &C;
       * RETURNS:
       *   (color3) result color3.
       */
      color3 operator+( const color3 &C ) const
      {
        return color3(R + C.R, G + C.G, B + C.B);
      } /* End of 'operator+' function */

      /* Add two vectors with assignment function.
       * ARGUMENTS:
       *   - color3 to be add:
       *       const color3 &C;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & operator+=( const color3 &C )
      {
        R += C.R;
        G += C.G;
        B += C.B;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - color3 to be subtract:
       *       const color3 &C;
       * RETURNS:
       *   (color3) result color3.
       */
      color3 operator-( const color3 &C ) const
      {
        return color3(R - C.R, G - C.G, B - C.B);
      } /* End of 'operator-' function */

      /* Subtract two vectors with assignment function.
       * ARGUMENTS:
       *   - color3 to be subtract:
       *       const color3 &C;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & operator-=( const color3 &C )
      {
        R -= C.R;
        G -= C.G;
        B -= C.B;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate color3 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (color3) result color3.
       */
      color3 operator-( VOID ) const
      {
        return color3(-R, -G, -B);
      } /* End of 'operator-' function */

      /* Negate color3 with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & Negate( VOID )
      {
        R = -R;
        G = -G;
        B = -B;
        return *this;
      } /* End of 'Negate' function */

      /* Get color3 length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) color3 length.
       */
      Type operator!( VOID ) const
      {
        Type len = R * R + G * G + B * B;

        if (len == 0 || len == 1)
          return len;
        return sqrt(len);
      } /* End of 'operator!' function */

      /* Get color3 squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) color3 length.
       */
      Type Len2( VOID ) const
      {
        return R * R + G * G + B * B;
      } /* End of 'Len2' function */

      /* Clamp color3 function
       * ARGUMENTS:
       *   - minimal color3 value:
       *       Type Min;
       *   - maximum color3 value:
       *       Type Max;
       * RETURNS:
       *   (color3) clamped color3.
       */
      color3 Clamping( Type Min = 0, Type Max = 1 ) const
      {
        return color3(R < Min ? Min : R > Max ? Max : R,
                     G < Min ? Min : G > Max ? Max : G,
                     B < Min ? Min : B > Max ? Max : B);
      } /* End of 'Clamping' function */

      /* Clamp color3 function.
       * ARGUMENTS:
       *   - minimal color3 value:
       *       Type Min;
       *   - maximum color3 value:
       *       Type Max;
       * RETURNS:
       *   (color3 &) self reference to color3.
       */
      color3 & Clamp( Type Min = 0, Type Max = 1 )
      {
        if (R < Min)
          R = Min;
        else
          if (R > Max)
            R = Max;
        if (G < Min)
          G = Min;
        else
          if (G > Max)
            G = Max;
        if (B < Min)
          B = Min;
        else
          if (B > Max)
            B = Max;
        return *this;
      } /* End of 'Clamp' function */

      /* Convert color3 to DWORD integer value function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DWORD) converted color3 value.
       */
      operator DWORD( VOID )
      {
        color3 r = Clamping() * 255.0;
        return 0xFF000000 |
               ((UINT)r.R << 16) | ((UINT)r.G << 8) | (UINT)r.B;
      } /* End of 'operator DWORD' function */
    }; /* End of 'color3' class */

  /* Color (quad) class */
  template<class Type>
    class color
    {
    public:
      /* Vector components */
      Type R, G, B, A;

      /* Default constructor */
      color( VOID )
      {
      } /* End of 'color' constructor */

      /* Monochrome color class constructor.
       * ARGUMENTS:
       *   - value for all components:
       *       Type Val;
       */
      explicit color( Type Val ) : R(Val), G(Val), B(Val), A(1)
      {
      } /* End of 'color' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - component values:
       *       Type NewR, NewG, NewB, NewA;
       */
      explicit color( Type NewR, Type NewG, Type NewB, Type NewA = 1 ) :
        R(NewR), G(NewG), B(NewB), A(NewA)
      {
      } /* End of 'color' constructor */

      /* Class constructor.
       * ARGUMENTS:
       *   - triplex color value:
       *       const color3<Type> &NewC;
       *   - alpha channel value:
       *       Type NewA;
       */
      explicit color( const color3<Type> &NewC, Type NewA = 1 ) :
        R(NewC.R), G(NewC.G), B(NewC.B), A(NewA)
      {
      } /* End of 'color' constructor */

      /* Set new components function.
       * ARGUMENTS:
       *   - component values:
       *       Type NewR, NewG, NewB, NewA;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & Set( Type NewR, Type NewG, Type NewB, Type NewA = 1 )
      {
        R = NewR;
        G = NewG;
        B = NewB;
        A = NewA;
        return *this;
      } /* End of 'Set' function */

      /* Get component by index function.
       * ARGUMENTS:
       *   - component index:
       *       INT I;
       * RETURNS:
       *   (Type &) reference to component.
       */
      Type & operator[]( INT I )
      {
        assert(I >= 0 && I <= 3);
        return *(&R + I);
      } /* End of 'operator[]' function */

      /* Get colors by-components product function.
       * ARGUMENTS:
       *   - color to be multiply:
       *       const color &C;
       * RETURNS:
       *   (color) by-components product result.
       */
      color operator*( const color &C ) const
      {
        return color(R * C.R, G * C.G, B * C.B);
      } /* End of 'operator*' function */

      /* Get colors by-components product with assignment function.
       * ARGUMENTS:
       *   - color to be multiply:
       *       const color &C;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & operator*=( const color &C )
      {
        R *= C.R;
        G *= C.G;
        B *= C.B;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply color by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color) result color.
       */
      color operator*( Type N ) const
      {
        return color(R * N, G * N, B * N);
      } /* End of 'operator*' function */

      /* Multiply color by number with assignment function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & operator*=( Type N )
      {
        R *= N;
        G *= N;
        B *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide color by number function.
       * ARGUMENTS:
       *   - number to be multiply:
       *       Type N;
       * RETURNS:
       *   (color) result color.
       */
      color operator/( Type N ) const
      {
        return color(R / N, G / N, B / N);
      } /* End of 'operator/' function */

      /* Divide color by number with assignment function.
       * ARGUMENTS:
       *   - number to be divide:
       *       Type N;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & operator/=( Type N )
      {
        R /= N;
        G /= N;
        B /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - color to be add:
       *       const color &C;
       * RETURNS:
       *   (color) result color.
       */
      color operator+( const color &C ) const
      {
        return color(R + C.R, G + C.G, B + C.B);
      } /* End of 'operator+' function */

      /* Add two vectors with assignment function.
       * ARGUMENTS:
       *   - color to be add:
       *       const color &C;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & operator+=( const color &C )
      {
        R += C.R;
        G += C.G;
        B += C.B;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - color to be subtract:
       *       const color &C;
       * RETURNS:
       *   (color) result color.
       */
      color operator-( const color &C ) const
      {
        return color(R - C.R, G - C.G, B - C.B);
      } /* End of 'operator-' function */

      /* Subtract two vectors with assignment function.
       * ARGUMENTS:
       *   - color to be subtract:
       *       const color &C;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & operator-=( const color &C )
      {
        R -= C.R;
        G -= C.G;
        B -= C.B;
        return *this;
      } /* End of 'operator-=' function */

      /* Negate color function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (color) result color.
       */
      color operator-( VOID ) const
      {
        return color(-R, -G, -B);
      } /* End of 'operator-' function */

      /* Negate color with assignment function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & Negate( VOID )
      {
        R = -R;
        G = -G;
        B = -B;
        return *this;
      } /* End of 'Negate' function */

      /* Get color length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) color length.
       */
      Type operator!( VOID ) const
      {
        Type len = R * R + G * G + B * B;

        if (len == 0 || len == 1)
          return len;
        return sqrt(len);
      } /* End of 'operator!' function */

      /* Get color squared length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) color length.
       */
      Type Len2( VOID ) const
      {
        return R * R + G * G + B * B;
      } /* End of 'Len2' function */

      /* Clamp color function
       * ARGUMENTS:
       *   - minimal color value:
       *       Type Min;
       *   - maximum color value:
       *       Type Max;
       * RETURNS:
       *   (color) clamped color.
       */
      color Clamping( Type Min = 0, Type Max = 1 ) const
      {
        return color(R < Min ? Min : R > Max ? Max : R,
                     G < Min ? Min : G > Max ? Max : G,
                     B < Min ? Min : B > Max ? Max : B,
                     A < Min ? Min : A > Max ? Max : A);
      } /* End of 'Clamping' function */

      /* Clamp color function.
       * ARGUMENTS:
       *   - minimal color value:
       *       Type Min;
       *   - maximum color value:
       *       Type Max;
       * RETURNS:
       *   (color &) self reference to color.
       */
      color & Clamp( Type Min = 0, Type Max = 1 )
      {
        if (R < Min)
          R = Min;
        else
          if (R > Max)
            R = Max;
        if (G < Min)
          G = Min;
        else
          if (G > Max)
            G = Max;
        if (B < Min)
          B = Min;
        else
          if (B > Max)
            B = Max;
        if (A < Min)
          A = Min;
        else
          if (A > Max)
            A = Max;
        return *this;
      } /* End of 'Clamp' function */

      /* Convert color to DWORD integer value function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DWORD) converted color value.
       */
      operator DWORD( VOID )
      {
        color r = Clamping() * 255.0;
        r.A *= 255.0;
        return ((UINT)r.A << 24) | ((UINT)r.R << 16) | ((UINT)r.G << 8) | (UINT)r.B;
      } /* End of 'operator DWORD' function */
    }; /* End of 'color' class */
} /* end of 'mth' namespace */

#endif /* __COLOR_H_ */

/* END OF 'COLOR.H' FILE */
