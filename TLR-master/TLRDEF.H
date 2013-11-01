/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TLRDEF.H
 * PURPOSE     : Tough Light Racing project.
 *               Common definitions module.
 * PROGRAMMER  : CGSG'2013.
 *               Maria Abramova,
 *               Vasiliy Cheptsov,
 *               Nikita Gaevoy,
 *               Aleksandra Gorskaya,
 *               Stanislav Petrov,
 *               Vsevolod Poletaev,
 *               Vyacheslav Rusanov,
 *               Leonid Voroshilov,
 *               Tatyana Sankova,
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TLRDEF_H_
#define __TLRDEF_H_

#include <assert.h>

#include <commondf.h>

#pragma warning(disable : 4996)

/* Math support */
#include "mth/mth.h"

#include "tlrstock.h"

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
    _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy
{
public:
  /* Class constructor */
  __Dummy( VOID )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

/* Common purpose base types */
typedef __int64 INT64;
typedef unsigned __int64 UINT64;

/* Project namespace */
namespace tlr
{
  /* Math type definitions */
  typedef mth::vec<FLT> vec;
  typedef mth::vec2<FLT> vec2;
  typedef mth::matr<FLT> matr;
  typedef mth::color<FLT> color;

  /* Maximum string length value */
  const INT MaxStringLength = 100;

  /* Forward references */
  class win;
  class timer;
  class render;
  class prim;
  class unit;
  class anim;
  class shader;
  class material;
  class material_manager;
  class shape_player;
  class check;
  struct PLAYER;
} /* end of 'tlr' namespace */

#endif /* __TLRDEF_H_ */

/* END OF 'TLRDEF.H' FILE */
