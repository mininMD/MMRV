/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RENDER.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Rendering engene class implementation.
 * PROGRAMMER  : CGSG'2013.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <stdio.h>
#include <stdarg.h>

#include "../../tlr.h"

/* Class constructor.
 * ARGUMENTS:
 *   - render window handle reference:
 *       HWND &hWndRender;
 */
tlr::render::render( HWND &hWndRender ) :
  hWnd(hWndRender), hDC(GetDC(hWnd)), hRC(NULL)
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Initialisation OpenGL: select appropriate pixel format */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;

  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);

  /* Set default OpenGL parameters */
  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (glewInit() != GLEW_OK)
  {
    /* Error in extensions initialization */
    ReleaseDC(hWnd, hDC);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);

    MessageBox(hWnd, "ERROR: glew initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Transformation setup */
  MatrProj.Set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  MatrView = MatrWorld = MatrProj;

  /* Set default parameters */
  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Make work font */
  SelectObject(hDC,
    CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, RUSSIAN_CHARSET,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    FF_SWISS | VARIABLE_PITCH, "Arial"));
  wglUseFontBitmaps(hDC, 0, 256, 3030);
  /*
  wglUseFontOutlines(hDC, 0, 256, 30 * 3030, 0.00051, 0.1, WGL_FONT_POLYGONS, NULL);
  */
  glListBase(3030);
} /* End of 'tlr::render::render' function */

/* Class destructor.
 * ARGUMENTS: None.
 */
tlr::render::~render( VOID )
{
  /* Destroy rendering context */
  wglMakeCurrent(NULL, NULL);
  if (hRC != NULL)
    wglDeleteContext(hRC);
  if (hDC != NULL)
    ReleaseDC(hWnd, hDC);
} /* End of 'tlr::render::~render' function */

/* Resize render window handle function.
 * ARGUMENTS:
 *   - new window work area size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID tlr::render::Resize( INT W, INT H )
{
  /* Store new size */
  Width = W;
  Height = H;

  /* Update camera projection data */
  DBL s = 1, sw = s, sh = s;
  if (W > H)
    sw = s * W / H;
  else
    sh = s * H / W;

  glViewport(0, 0, W, H);
  /// glLoadIdentity();
  /// glOrtho(-sw, sw, -sh, sh, -1, 1);
  MatrProj = MatrProj.MatrProjection(-sw, sw, -sh, sh, 1, 1000);
} /* End of 'tlr::render::Resize' function */

/* Start frame rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::render::StartFrame( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'tlr::render::StartFrame' function */

/* Finish  frame rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::render::EndFrame( VOID )
{
  glFinish();
} /* End of 'tlr::render::EndFrame' function */

/* Copy current frame to window function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::render::CopyFrame( VOID )
{
  SwapBuffers(hDC);
} /* End of 'tlr::render::CopyFrame' function */

/* Output formatted text function.
 * ARGUMENTS:
 *   - screen position:
 *       DBL X, Y;
 *   - formatted string:
 *       CHAR *Fmt;
 * RETURNS:
 *   (INT) number of output symbols.
 */
INT tlr::render::PrintF( DBL X, DBL Y, CHAR *Fmt, ... )
{
  INT ret;
  va_list ap;
  static CHAR Buf[10000];

  va_start(ap, Fmt);
  ret = vsprintf(Buf, Fmt, ap);
  glRasterPos2d(X, Y);
  glCallLists(ret, GL_UNSIGNED_BYTE, Buf);
  va_end(ap);
  return ret;
} /* End of 'tlr::render::PrintF' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - link to primitive:
 *       prim &P;
 * RETURNS: None.
 */
VOID tlr::render::DrawPrim( prim &P )
{
  INT i;

  if (P.VBuf == 0)
  {
    /* Generate new buffers */
    glGenBuffers(2, P.Buffs);
    glGenVertexArrays(1, &P.VBuf);
    P.IsVertexChange = TRUE;
    P.IsIndexChange = TRUE;
  }

  /* Update buffer vertexes and indexes */
  if (P.IsVertexChange)
  {
    glBindBuffer(GL_ARRAY_BUFFER, P.Buffs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * P.NoofV,
      P.Vertices, GL_STATIC_DRAW);
    P.IsVertexChange = FALSE;
  }
  if (P.IsIndexChange)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P.Buffs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * P.NoofI,
      P.Indexes, GL_STATIC_DRAW);
    P.IsIndexChange = FALSE;
  }

  /* Activate buffers */
  glBindVertexArray(P.VBuf);
  glBindBuffer(GL_ARRAY_BUFFER, P.Buffs[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P.Buffs[2]);

  /* Setup data order */
  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) + sizeof(UV)));
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(3, 3, GL_FLOAT, FALSE, sizeof(VERTEX), (VOID *)(sizeof(vec) * 2 + sizeof(UV)));
  glEnableVertexAttribArray(3);

  if (P.Material != NULL)
    P.Material->Apply(this);

  /* Draw primitive */
  if (P.Type == tlr::prim::GRID)
  {
    for (i = 0; i < P.GridH; i++)
    {
      glBindVertexArray(P.VBuf);
      glBindBuffer(GL_ARRAY_BUFFER, P.Buffs[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P.Buffs[1]);
      glDrawElements(GL_TRIANGLE_STRIP, (P.GridW + 1) * 2, GL_UNSIGNED_INT, (VOID *)(i * (P.GridW + 1) * 2 * sizeof(UINT)));
    }
  }
  else
  {
    glBindVertexArray(P.VBuf);
    glBindBuffer(GL_ARRAY_BUFFER, P.Buffs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P.Buffs[1]);
    glDrawElements(GL_TRIANGLES, P.NoofI, GL_UNSIGNED_INT, (VOID *)0);
  }
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Draw normal */
  /*
  glPointSize(5);
  glBegin(GL_POINTS);
  for (i = 0; i < P.NoofV; i++)
  {
    glColor3fv(&P.Vertices[i].C[0]);
    glNormal3fv(&P.Vertices[i].N[0]);
    glVertex3fv(&P.Vertices[i].P[0]);
  }
  glEnd();

  glBegin(GL_LINES);
  for (i = 0; i < P.NoofV; i++)
  {
    glColor3d(1, 1, 1);
    glNormal3d(1, 1, 1);
    glVertex3fv(&P.Vertices[i].P[0]);
    glVertex3fv(&(P.Vertices[i].P + P.Vertices[i].N * 0.30)[0]);
  }
  glEnd();
  */

  glUseProgram(0);
} /* End of 'tlr::render::DrawPrim' function */

/* END OF 'RENDER.CPP' FILE */
