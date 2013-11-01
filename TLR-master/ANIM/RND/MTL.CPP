/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTL.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Material implementation module.
 * PROGRAMMER  : CGSG'2013.
 *               Stanislav Petrov.
 * LAST UPDATE : 03.08.2013.
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <string.h>

#include "../../tlr.h"

/* Apply material function.
 * ARGUMENTS:
 *   - render system pointer:
 *       anim *Ani;
 * RETURNS: None.
 */
VOID tlr::material::Apply( render *Rnd )
{
  DeltaTime += Rnd->GlobalDeltaTime;
  if (Shader.ProgId == 0 || DeltaTime > 1)
  {
    DeltaTime = 0;
    Shader.Reload();
  }
  INT loc; // location shader parameters value

  /* Select shader program */
  glUseProgram(Shader.ProgId);
  if (Shader.ProgId != 0)
  {
    matr WVP;

    /* Setup camera and transformation handle data  */
    WVP = Rnd->MatrWorld * Rnd->MatrView * Rnd->MatrProj;
    loc = glGetUniformLocation(Shader.ProgId, "MatrWorldViewProj");
    if (loc != -1)
      glUniformMatrix4fv(loc, 1, FALSE, WVP.A[0]);
    loc = glGetUniformLocation(Shader.ProgId, "MatrWorld");
    if (loc != -1)
      glUniformMatrix4fv(loc, 1, FALSE, Rnd->MatrWorld.A[0]);
    loc = glGetUniformLocation(Shader.ProgId, "CamDir");
    if (loc != -1)
      glUniform3f(loc, -Rnd->MatrView.A[0][2], -Rnd->MatrView.A[1][2], -Rnd->MatrView.A[2][2]);

    /* Animation time */
    loc = glGetUniformLocation(Shader.ProgId, "Time");
    if (loc != -1)
      glUniform1f(loc, Rnd->Time);

    /* Frame size */
    loc = glGetUniformLocation(Shader.ProgId, "Width");
    if (loc != -1)
      glUniform1f(loc, Rnd->Width);
    loc = glGetUniformLocation(Shader.ProgId, "Height");
    if (loc != -1)
      glUniform1f(loc, Rnd->Height);
  }

  /* Textures initialization */
  for (INT i = 0; i < 5; i++)
    if (NameMap[i][0] != 0 && Map[i].ID == 0)
    {
      Map[i].LoadFile(NameMap[i]);
      glGenTextures(1, &Map[i].ID);

      /* Activate and send to OpanGL */
      glBindTexture(GL_TEXTURE_2D, Map[i].ID);
      Map[i].Load();
    }
  glBindTexture(GL_TEXTURE_2D, 0);

  if (Shader.ProgId != 0)
  {
    /* Setup current material textures */
    static CHAR *TexMapNames[] =
    {
      "MapKa", "MapKd", "MapKs", "MapKt", "MapN"
    };
    for (INT i = 0; i < 5; i++)
    {
      loc = glGetUniformLocation(Shader.ProgId, TexMapNames[i]);
      if (loc != -1)
        glUniform1i(loc, i);
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, Map[i].ID);
    }

    /* Setup illumination coefficients */
    loc = glGetUniformLocation(Shader.ProgId, "Ka");
    if (loc != -1)
      glUniform3fv(loc, 1, &Ka.R);
    loc = glGetUniformLocation(Shader.ProgId, "Kd");
    if (loc != -1)
      glUniform3fv(loc, 1, &Kd.R);
    loc = glGetUniformLocation(Shader.ProgId, "Ks");
    if (loc != -1)
      glUniform3fv(loc, 1, &Ks.R);
    loc = glGetUniformLocation(Shader.ProgId, "Phong");
    if (loc != -1)
      glUniform1f(loc, Phong);
    loc = glGetUniformLocation(Shader.ProgId, "Kt");
    if (loc != -1)
      glUniform1f(loc, Kt);
  }
} /* End of 'tlr::material::Apply' function */

/* END OF 'MTL.CPP' FILE */
