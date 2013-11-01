/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTL.H
 * PURPOSE     : Tough Light Racing project.
 *               Material declaration module.
 * PROGRAMMER  : CGSG'2013.
 *               Stanislav Petrov.
 * LAST UPDATE : 03.08.2013.
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MTL_H_
#define __MTL_H_

#include <string.h>

#include "shader.h"

/* Tough Animation Zone project namespace */
namespace tlr
{
  /* Marerial class */
  class material
  {
  private:
    /* Time counter for autoreload shader value */
    FLT DeltaTime;
  public:
    /* Illumination model coefficients */
    color Ka, Kd, Ks;
    FLT Phong;

    /* Opacity level (transmitted) */
    FLT Kt;

    /* Material name */
    CHAR
      Name[MaxStringLength];

    /* Textures: Ka, Kd, Ks, Kt, NormalMap */
    CHAR
      NameMap[5][MaxStringLength];

    /* Texture images */
    image Map[5];

    /* Shader */
    shader Shader;

    /* Class constructor.
     * ARGUMENTS:
     *   - material name (look for):
     *       CHAR *NewName;
     */
    material( CHAR *NewName = NULL ) :
      DeltaTime(0), Ka(0.1), Kd(0.9), Ks(0), Phong(30), Kt(0)
    {
      if (NewName != NULL)
        strncpy(Name, NewName, MaxStringLength);
      else
        Name[0] = 0;

      /* Set empty textures */
      NameMap[0][0] = 0; // Ka
      NameMap[1][0] = 0; // Kd
      NameMap[2][0] = 0; // Ks
      NameMap[3][0] = 0; // Kt
      NameMap[4][0] = 0; // N 
    } /* End of 'material' constructor */

    /* Apply material function */
    VOID Apply( render *Ani );
  }; /* End of 'material' class */

  /* Marerial manager class */
  class material_manager
  {
  public:
    /* Stock material */
    stock<material> Materials;

    /* Get material by name function.
     * ARGUMENTS:
     *   - material name (look for):
     *       CHAR *Name;
     * RETURNS:
     *   (material *) pointer to material or NULL if one not found.
     */
    material * Get( CHAR *Name )
    {
      for (INT i = 0; i < Materials.Size(); i++)
        if (strcmp(Materials[i].Name, Name) == 0)
          return &Materials[i];
      return NULL;
    } /* End of 'Get' function */

    /* Material create function.
     * ARGUMENTS:
     *   - new material name:
     *       CHAR *Name;
     *   - shader interface pointer:
     *       shader *Shad;
     *   - texture interface pointers:
     *       texture *Tex, Tex1;
     * RETURNS:
     *   (material *) pointer to created material.
     */
    material * Create( CHAR *Name )
    {
      material *mtl = Get(Name);

      if (mtl == NULL)
      {
        Materials << material(Name);
        return &Materials.Last();
      }
      return mtl;
    } /* End of 'Create' function */

    /* Class destructor */
    ~material_manager( VOID )
    {
    } /* End of '~material_manager' function */

    /* Load materials from file function */
    VOID Load( CHAR *FileName, CHAR *Path );
  }; /* End of 'material_manager' class */
} /* end of 'taz' namespace */

#endif /* __MTL_H_ */

/* END OF 'MTL.H' FILE */
