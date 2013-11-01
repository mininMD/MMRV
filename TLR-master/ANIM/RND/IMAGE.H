/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.H
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Image handle class declaraion module.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "../../tlrdef.h"

/* Project namespace */
namespace tlr
{
  /* Texture image handle class */
  class image
  {
  private:
    /* Clone image data function */
    VOID Clone( const image &I );

  public:
    /* Image size */
    INT W, H;
    /* Image RGBA pixel data */
    DWORD *Bits;
    /* Image texture ID */
    UINT ID;

    /* Class constructor */
    image( CHAR *FileName = NULL );

    /* Class destructor */
    ~image( VOID );

    /* Copying constructor.
     * ARGUMENTS:
     *   - image to be cloned:
     *       const image &I;
     * RETURNS: None.
     */
    image( const image &I ) : ID(0), W(0), H(0), Bits(NULL)
    {
      Clone(I);
    } /* End of 'image' constructor */

    /* Assignment operator function.
     * ARGUMENTS:
     *   - image to be assignment:
     *       const image &I;
     * RETURNS:
     *   (image &) self pointer.
     */
    image & operator=( const image &I )
    {
      Clone(I);
      return *this;
    } /* End of 'operator=' function */

    /* Load image function */
    BOOL LoadFile( CHAR *FileName );

    /* Send to OpenGL as a pixel array function */
    VOID Draw( VOID );

    /* Load to OpenGL as a texture function */
    VOID Load( VOID );
  }; /* End of 'image' class */
} /* end of 'tlr' namespace */

#endif /* __IMAGE_H_ */

/* END OF 'IMAGE.H' FILE */
