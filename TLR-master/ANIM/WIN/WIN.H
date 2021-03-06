/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : WIN.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Window handle class declaration.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 01.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __WIN_H_
#define __WIN_H_

#include "../../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Window handle class */
  class win
  {
  private:
    static const int InitializationTimer = 3030;
    HWND hWndValue;      // Window handle
    INT WinW, WinH;      // Window size
    BOOL IsInit;         // Initialization flag
    BOOL ActiveFlag;     // Window active flag
    BOOL IsFullScreen;   // Full screen output flag
    RECT SaveRC;         // Stored window original size and position

  protected:
    HINSTANCE hInstance; // Instance of application

  public:
    const INT &W, &H;     // User accessable window size
    const HWND &hWnd;     // User accessable window handle
    const BOOL &IsActive; // User accessable activation flag

    /* Class constructor */
    win( VOID );

    /* Main message loop function */
    VOID Run( VOID );

    /* Exit from main loop function */
    VOID DoExit( VOID );

    /* Goto fullscreen mode function */
    BOOL SetFullScreen( BOOL IsFullScreen );

    /* Get full screen state function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) TRUE if window in fullscreen mode, FALSE otherwise.
     */
    BOOL GetFullScreen( VOID )
    {
      return IsFullScreen;
    } /* End of 'GetFullScreen' function */

    /***
     * Handle window messages functions
     ***/

    /* Window message handle function */
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    /* WM_CREATE handle message function */
    BOOL OnCreate( CREATESTRUCT *CreateStruct );
    /* WM_DESTROY handle message function */
    VOID OnDestroy( VOID );
    /* WM_SIZE  handle message function */
    VOID OnSize( UINT State, INT Width, INT Height );
    /* WM_ACTIVATE window message handle function */
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    /* WM_PAINT  handle message function */
    VOID OnPaint( VOID  );
    /* WM_ERASEBKGND handle message function */
    BOOL OnEraseBkgnd( HDC hDC );
    /* WM_TIMER handle message function */
    VOID OnTimer( INT Id );

    /***
     * Derived class handle functions
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Redraw window content function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Erase background function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Change activity event handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Timer event handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */
  }; /* End of 'win' class */
} /* end of 'tlr' namespace */

#endif /* __WIN_H_ */

/* END OF 'WIN.H' FILE */
