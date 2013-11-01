/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RENDER.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Rendering engene class declaration.
 * PROGRAMMER  : CGSG'2013.
 * LAST UPDATE : 01.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32")

#include "../../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Render engine through OpenGL class */
  class render : public timer, public material_manager
  {
  private:
    HWND &hWnd;  // Window handle
    HDC hDC;     // Device context handle
    HGLRC hRC;   // Rendering context handle
  public:
    /* Frame size */
    INT Width, Height;

    /* Tranformation matrix */
    matr
      MatrProj,  // Projection matrix
      MatrView,  // Camera view matrix
      MatrWorld; // World transformation matrix

    /* Class constructor */
    render( HWND &hWndRender );

    /* Class destructor */
    ~render( VOID );

    /* Resize render window handle function */
    VOID Resize( INT W, INT H );

    /* Start frame rendering function */
    VOID StartFrame( VOID );

    /* Finish frame rendering function */
    VOID EndFrame( VOID );

    /* Copy current frame to window function */
    VOID CopyFrame( VOID );

    /* Draw primitive */
    VOID DrawPrim( prim &P );

    /* Output formatted text function */
    static INT PrintF( DBL X, DBL Y, CHAR *Fmt, ... );
  }; /* End of 'anim' class */
} /* end of 'tlr' namespace */

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
