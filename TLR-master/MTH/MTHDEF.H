/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTH.H
 * PURPOSE     : Tough Light Racing project.
 *               Mathemathic support header file.
 *               Global defenition.
 * PROGRAMMER  : CGSG'2013.
 *               Leonid Voroshilov
 * LAST UPDATE : 02.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MTHDEF_H_
#define __MTHDEF_H_

/* Common case float point types */
typedef float FLT;
typedef double DBL;
typedef long double LDBL;

/* Math support namespace */
namespace mth
{
  /* Pi constant */
  const FLT Pi = 3.14159265358979323846;
  template<class Type>
    class matr;
  const FLT MultiplierDegree2Radian = 0.01745329251994329576L;
  const FLT MultiplierRadian2Degree = 57.29577951308232087684;
  const DOUBLE Threshold = 1e-6;
} /* End of 'mth' namespace */

#endif /* __MTHDEF_H_ */

/* END OF 'MTH.H' FILE */
