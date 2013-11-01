/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHADER.CPP
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

#include <stdio.h>
#include <string.h>

#include "../../tlr.h"

/* Log file text saving flag */
BOOL tlr::shader::IsLog;

/* Compilation logger file handle class */
class logger
{
private:
  /* File pointer */
  FILE *F;

public:
  /* Class constructor.
   * ARGUMENTS:
   *   - log file name:
   *       CHAR *FileName;
   */
  logger( CHAR *FileName = "tlr.log" ) : F(NULL)
  {
    if (!tlr::shader::IsLog)
      return;
    F = fopen(FileName, "at");
  } /* End of 'logger' constructor */

  /* Output text to log file function.
   * ARGUMENTS:
   *   - text to be store:
   *       CHAR *Text;
   * RETURNS:
   *   (logger &) self pointer.
   */
  logger & operator<<( CHAR *Text )
  {
    if (F != NULL)
      fprintf(F, "%s", Text);
    return *this;
  } /* End of 'operator<<' function */

  /* Class destructor */
  ~logger( void )
  {
    if (F != NULL)
      fclose(F);
  } /* End of 'logger' destructor */
}; /* End of 'logger' class */

/* Load shader text from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) loaded text or NULL if error is occured.
 */ 
CHAR * tlr::shader::Load( CHAR *FileName )
{
  FILE *F;
  LONG N;
  CHAR *Res;

  if ((F = fopen(FileName, "r")) == NULL)
    return NULL;

  fseek(F, 0, SEEK_END);
  N = ftell(F);

  if ((Res = new CHAR[N + 1]) == NULL)
  {
    fclose(F);
    return NULL;
  }
  memset(Res, 0, N + 1);
  rewind(F);
  fread(Res, 1, N, F);
  fclose(F);
  return Res; 
} /* End of 'shader::Load' function */

/* Shader program initialization function.
 * ARGUMENTS:
 *   - vertex shader file name:
 *       CHAR *VertFileName;
 *   - fragment shader file name:
 *       CHAR *FragFileName;
 * RETURNS: None.
 */
VOID tlr::shader::Init( CHAR *VertFileName, CHAR *FragFileName )
{
  CHAR *text;
  INT res, len;
  UINT shv, shf;
  static char Buf[10000];

  /* If shader already exists - destroy it */
  Close();
  strncpy(VName, VertFileName, sizeof(VName));
  strncpy(FName, FragFileName, sizeof(FName));

  /* Vertex shader initialization */
  if ((text = tlr::shader::Load(VertFileName)) == NULL)
  {
    logger() << "Error load vertex shader file: \"" << VertFileName << "\"\n";
    return;
  }
  if ((shv = glCreateShader(GL_VERTEX_SHADER)) == 0)
  {
    logger() << "Error create vertex shader\n";
    delete text;
    return;
  }
  /* Send text to OpenGL and compile it */
  glShaderSource(shv, 1, (const CHAR **)&text, NULL);
  delete text;
  glCompileShader(shv);
  glGetShaderiv(shv, GL_COMPILE_STATUS, &res);
  if (res != 1)
  {
    glGetShaderInfoLog(shv, sizeof(Buf), &len, Buf);
    logger() << "Error compile vertex\n" << Buf << "\n";
    glDeleteShader(shv);
    return;
  }

  /* Fragment shader initialization */
  if ((text = Load(FragFileName)) == NULL)
  {
    logger() << "Error load fragment shader file: \"" << FragFileName << "\"\n";
    glDeleteShader(shv);
    return;
  }
  if ((shf = glCreateShader(GL_FRAGMENT_SHADER)) == 0)
  {
    logger() << "Error create fragment shader\n";
    delete text;
    glDeleteShader(shv);
    return;
  }
  /* Send text to OpenGL and compile it */
  glShaderSource(shf, 1, (const CHAR **)&text, NULL);
  delete text;
  glCompileShader(shf);
  glGetShaderiv(shf, GL_COMPILE_STATUS, &res);
  if (res != 1)
  {
    glGetShaderInfoLog(shf, sizeof(Buf), &len, Buf);
    logger() << "Error compile fragment\n" << Buf << "\n";
    glDeleteShader(shv);
    glDeleteShader(shf);
    return;
  }

  /* Shader program initialization */
  if ((ProgId = glCreateProgram()) == 0)
  {
    logger() << "Error program initialization\n";
    glDeleteShader(shv);
    glDeleteShader(shf);
    return;
  }
  /* Attach and link shaders to program */
  glAttachShader(ProgId, shv);
  glAttachShader(ProgId, shf);
  glLinkProgram(ProgId);
  glGetProgramiv(ProgId, GL_LINK_STATUS, &res);
  if (res != 1)
  {
    glDetachShader(ProgId, shv);
    glDetachShader(ProgId, shf);
    glGetProgramInfoLog(ProgId, sizeof(Buf), &len, Buf);
    logger() << "Error link shader program\n" << Buf << "\n";
    glDeleteShader(shv);
    glDeleteShader(shf);
    glDeleteProgram(ProgId);
    return;
  }
} /* End of 'shader::Init' function */

/* Shader program deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::shader::Close( VOID )
{
  UINT shdrs[2];

  if (ProgId == 0)
    return;

  for (UINT i = 0; i < 2; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
  /* Set 0 - no shader load */
  ProgId = 0;
} /* End of 'tlr::shader::Close' function */

/* Reload shader program function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::shader::Reload( VOID )
{
  Init(VName, FName);
} /* End of 'tlr::shader::Reload' function */

/* END OF 'SHADER.CPP' FILE */
