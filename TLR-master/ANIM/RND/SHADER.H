/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHADER.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Shadersupport module.
 * PROGRAMMER  : CGSG'2013.
 *               Tatyana Sankova.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __SHADER_H_
#define __SHADER_H_

#include "../../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* GLSL shader handle class */
  class shader
  {
  private:
    /* Saved shaders name */
    CHAR VName[300], FName[300];

    /* Load shader text from file function */
    static CHAR * Load( CHAR *FileName );
  public:
    /* Log file text saving flag */
    static BOOL IsLog;

    /* Program ID */
    UINT ProgId;

    /* Class constructor */
    shader( VOID ) : ProgId(0)
    {
      VName[0] = FName[0] = 0;
    } /* End of 'shader' constructor */

    /* Class destructor */
    ~shader( VOID )
    {
      if (ProgId != 0)
        Close();
    } /* End of '~shader' destructor */

    /* Shader program initialization function */
    VOID Init( CHAR *VertFileName, CHAR *FragFileName );

    /* Shader program deinitialization function */
    VOID Close( VOID );

    /* Reload shader program function */
    VOID Reload( VOID );
  }; /* End of 'shader' class */
} /* end of 'tlr' namespace */

#endif /* __SHADER_H_ */

/* END OF 'SHADER.H' FILE */
