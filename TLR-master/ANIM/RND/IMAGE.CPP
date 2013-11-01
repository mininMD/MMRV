/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Image handle class implementation module.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A. Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <string.h>

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

#include "../../tlr.h"

/* Clone image data function.
 * ARGUMENTS:
 *   - image to be cloned:
 *       const image &I;
 * RETURNS: None.
 */
VOID tlr::image::Clone( const image &I )
{
  if (Bits != NULL)
    delete[] Bits;
  if (I.Bits != NULL && I.W != 0 && I.H != 0)
  {
    Bits = new DWORD[I.W * I.H];
    W = I.W;
    H = I.H;
    memcpy((VOID *)Bits, (VOID *)I.Bits, 4 * I.W * I.H);
  }
  else
    Bits = NULL, W = 0, H = 0;
  ID = 0;
} /* End of 'tlr::image::Clone' function */

/* Load image function.
 * ARGUMENTS:
 *   - image file name (TGA):
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL tlr::image::LoadFile( CHAR *FileName )
{
  tgaFILEHEADER fh;
  FILE *F;

  if (Bits != NULL)
  {
    delete[] Bits;
    W = H = 0;
  }
  if (FileName == NULL)
    return FALSE;
  if ((F = fopen(FileName, "rb")) != NULL)
  {
    /* Read file header */
    fread(&fh, sizeof(fh), 1, F);
    /* Check for supported format */
    if (fh.ColorMapType == 0 &&        // no palette
        fh.ImageType == 2 &&           // uncompressed RGB
        fh.BitsPerPixel == 32 &&       // 32 bits images
        (fh.ImageDescr & 0x20) != 0 && // upper-left start, non-interleaved
        (fh.ImageDescr & 0xF) == 8)    // 8 bit alpha channel attributes
    {
      /* Skip comment */
      fseek(F, fh.IDLength, SEEK_CUR);
      if ((Bits = new DWORD[fh.Width * fh.Height]) != NULL)
      {
        fread(Bits, 4 * fh.Width, fh.Height, F);
        W = fh.Width;
        H = fh.Height;
      }
    }
    fclose(F);
  }
  return Bits != NULL;
} /* End of 'tlr::image::LoadFile' function */

/* Class constructor.
 * ARGUMENTS:
 *   - image file name (TGA):
 *       CHAR *FileName;
 */
tlr::image::image( CHAR *FileName ) : ID(0), W(0), H(0), Bits(NULL)
{
  if (FileName != NULL)
    LoadFile(FileName);
} /* End of 'tlr::image::image' constructor */

/* Send to OpenGL as a pixel array function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::image::Draw( VOID )
{
  glDrawPixels(W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
} /* End of 'tlr::image::Draw' function */

/* Load to OpenGL as a texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID tlr::image::Load( VOID )
{
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
} /* End of 'tlr::image::Load' function */

/* Class destructor */
tlr::image::~image( VOID )
{
  if (Bits != NULL)
    delete[] Bits;
  if (ID != NULL)
    glDeleteTextures(1, &ID);
} /* End of 'tlr::image::~image' destructor */


/* END OF 'IMAGE.CPP' FILE */
