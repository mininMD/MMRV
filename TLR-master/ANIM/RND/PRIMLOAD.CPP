/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PRIMLOAD.CPP
 * PURPOSE     : Tough Light Racing project.
 *               Animation module.
 *               Primitive class implementation.
 * PROGRAMMER  : CGSG'2013,
 *               Stanislav Petrov.
 * LAST UPDATE : 03.08.2013
 * NOTE        : Namespace 'tlr'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>

#include "../../tlr.h"

/* Read buffer handle class */
class buffer
{
public:
  static const INT MaxSize = 1000;
  /* Read buffer */
  CHAR Buf[MaxSize];

  /* String parsed parts */
  INT NumOfParts;
  CHAR *Parts[MaxSize / 2];

  /* Read buffer from file function.
   * ARGUMENTS:
   *   - file pointer:
   *       FILE *F;
   * RETURNS:
   *   (BOOL) FALSE if file is over, TRUE otherwise.
   */
  BOOL Read( FILE *F )
  {
    if (fgets(Buf, MaxSize - 1, F) == NULL)
      return FALSE;
    return TRUE;
  } /* End of 'Read' function */

  /* Check read buffer start substring function.
   * ARGUMENTS:
   *   - file pointer:
   *       CHAR *SubStr;
   * RETURNS:
   *   (BOOL) TRUE if substring is match, FALSE otherwise.
   */
  BOOL operator()( CHAR *SubStr )
  {
    CHAR *str1 = Buf, *str2 = SubStr;

    while (tolower(*str1) == tolower(*str2) && *str1 != 0)
      str1++, str2++;
    if (*str2 == 0)
      return TRUE;
    return FALSE;
  } /* End of 'operator()' function */

  /* Obtain read buffer part function.
   * ARGUMENTS:
   *   - part number:
   *       INT I;
   * RETURNS:
   *   (CHAR *) pointer to first symbol of specified read buffer part.
   */
  CHAR * operator[]( INT I )
  {
    assert(I >= 0 && I < NumOfParts);
    return Parts[I];
  } /* End of 'operator[]' function */

  /* Split read buffer into space separated parts function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (INT) number of splitted parts.
   */
  INT Split( VOID )
  {
    INT i = 0;

    /* Prepare parts array */
    NumOfParts = 0;
    Parts[0] = Buf;
    while (Buf[i] != 0)
    {
      /* Skip spaces */
      while (isspace(Buf[i]))
        i++;
      /* Finish if string buffer is over */
      if (Buf[i] == 0)
        return NumOfParts;

      /* Store word start */
      Parts[NumOfParts++] = Buf + i;
      /* Skip word till it end */
      while (!isspace(Buf[i]) && Buf[i] != 0)
        i++;

      /* Finish if string buffer is over */
      if (Buf[i] == 0)
        return NumOfParts;
      /* Finish current word */
      Buf[i++] = 0;
    }
    return NumOfParts;
  } /* End of 'Split' function */
}; /* End of 'buffer' class */

/* Vertex reference collector class */
class vertex_references
{
public:
  /* One reference array entry */
  struct VERTREF
  {
    /* Vertex, vertex normal, vertex texture coordinate, next vertex references */
    INT Nv, Nn, Nt, Next;

    /* Constructor */
    VERTREF( VOID ) : Next(-1)
    {
    } /* End of 'VERTREF' constructor */

    /* Constructor.
     * ARGUMENTS:
     *   - new index values:
     *       INT NewNv, NewNn, NewNt;
     */
    VERTREF( INT NewNv, INT NewNn, INT NewNt ) : Nv(NewNv), Nn(NewNn), Nt(NewNt), Next(-1)
    {
    } /* End of 'VERTREF' constructor */
  };

  /* Collection of vertex references */
  stock<VERTREF> VertexRefs;

  /* Array of every vertex start number at 'VertexRefs'  */
  stock<INT> VertexStartIndex;

  /* Class constructor.
   * ARGUMENTS:
   *   - total load vertex counter:
   *       INT NumOfVertex;
   */
  vertex_references( INT NumOfVertex = 0)
  {
    VertexStartIndex.Alloc(NumOfVertex);
    for (INT i = 0; i < VertexStartIndex.Size(); i++)
      VertexStartIndex[i] = -1;
  } /* End of 'vertex_references' constructor */

  /* Actual vertex number obtain function.
   * ARGUMENTS:
   *   - index of vertex, vertex normal, vertex texture coordinates:
   *       INT Nv, Nn, Nt;
   * RETURNS:
   *   (INT) actual vertex number at 'VertexRefs' array.
   */
  INT GetVertexNumber( INT Nv, INT Nn, INT Nt )
  {
    /* Add additional vertex start references */
    if (Nv >= VertexStartIndex.Size())
    {
      INT old;
      VertexStartIndex.Alloc((old = VertexStartIndex.Size()) - Nv + 1);
      for (INT i = old; i < VertexStartIndex.Size(); i++)
        VertexStartIndex[i] = -1;
    }

    /* Look for vertex data match */
    INT *n = &VertexStartIndex[Nv];
    while (*n != -1 &&
           !(VertexRefs[*n].Nv == Nv && VertexRefs[*n].Nn == Nn && VertexRefs[*n].Nt == Nt))
      n = &VertexRefs[*n].Next;
    if (*n != -1)
      return *n;
    /* Allocate new vertex */
    *n = VertexRefs.Size();
    VertexRefs << VERTREF(Nv, Nn, Nt);
    return VertexRefs.Size() - 1;
  } /* End of 'GetVertexNumber' function */
}; /* End of 'vertex_references' class */

/* File name and full path store handle class */
class file_path
{
public:
  /* File path parts */
  CHAR
    Path[_MAX_PATH],      // Full file name path
    Drive[_MAX_DRIVE],    // File path drive name
    Dir[_MAX_DIR],        // File path directory name
    FileName[_MAX_FNAME], // File path file name
    FileExt[_MAX_EXT];    // File path file extension

  /* Constructor.
   * ARGUMENTS:
   *   - file name path:
   *       CHAR *PathFileName;
   */
  file_path( CHAR *PathFileName )
  {
    strncpy(Path, PathFileName, _MAX_PATH);
    _splitpath(PathFileName, Drive, Dir, FileName, FileExt);
  } /* End of 'file_path' constructor */
}; /* End of 'file_path' class */

/* Draw object function.
 * ARGUMENTS:
 *   - render system pointer:
 *       render *Rnd;
 * RETURNS: None.
 */
VOID tlr::geom_prim::Draw( render *Rnd )
{
  for (INT i = 0; i < Prims.Size(); i++)
    Rnd->DrawPrim(Prims[i]);
} /* End of 'tlr::geom_prim::Draw' function */

/* Load materials from file function.
 * ARGUMENTS:
 *   - material file name:
 *       CHAR *FileName;
 *   - material path (or model full file name):
 *       CHAR *Path;
 * RETURNS: None.
 */
VOID tlr::material_manager::Load( CHAR *FileName, CHAR *Path )
{
  /* Build material file name */
  file_path ModelName(Path);
  CHAR FullName[_MAX_PATH];
  _makepath(FullName, ModelName.Drive, ModelName.Dir, FileName, "");

  /* Setup default material */
  material Mat("unknown");

  FILE *F;
  if ((F = fopen(FullName, "rt")) == NULL)
    return;

  buffer RBuf;
  BOOL IsFirst = TRUE;
  /* Read all material */
  while (RBuf.Read(F))
  {
    RBuf.Split();
    if (RBuf.NumOfParts > 1)
      if (RBuf("Ka"))
      {
        sscanf(RBuf[1], "%f", &Mat.Ka.R);
        sscanf(RBuf[2], "%f", &Mat.Ka.G);
        sscanf(RBuf[3], "%f", &Mat.Ka.B);
      }
      else if (RBuf("Kd"))
      {
        sscanf(RBuf[1], "%f", &Mat.Kd.R);
        sscanf(RBuf[2], "%f", &Mat.Kd.G);
        sscanf(RBuf[3], "%f", &Mat.Kd.B);
      }
      else if (RBuf("Ks"))
      {
        sscanf(RBuf[1], "%f", &Mat.Ks.R);
        sscanf(RBuf[2], "%f", &Mat.Ks.G);
        sscanf(RBuf[3], "%f", &Mat.Ks.B);
      }
      else if (RBuf("Ns"))
        sscanf(RBuf[1], "%f", &Mat.Phong);
      else if (RBuf("Tr") || RBuf("d") || RBuf("D"))
        sscanf(RBuf[1], "%f", &Mat.Kt);
      else if (RBuf("map_Ka"))
      {
        _makepath(FullName, ModelName.Drive, ModelName.Dir, RBuf[1], "");
        strncpy(Mat.NameMap[0], FullName, MaxStringLength - 1);
      }
      else if (RBuf("map_Kd"))
      {
        _makepath(FullName, ModelName.Drive, ModelName.Dir, RBuf[1], "");
        strncpy(Mat.NameMap[1], FullName, MaxStringLength - 1);
      }
      else if (RBuf("map_Ks"))
      {
        _makepath(FullName, ModelName.Drive, ModelName.Dir, RBuf[1], "");
        strncpy(Mat.NameMap[2], FullName, MaxStringLength - 1);
      }
      else if (RBuf("map_opacity") || RBuf("map_d"))
      {
        _makepath(FullName, ModelName.Drive, ModelName.Dir, RBuf[1], "");
        strncpy(Mat.NameMap[3], FullName, MaxStringLength - 1);
      }
      else if (RBuf("map_bump") || RBuf("bump"))
      {
        _makepath(FullName, ModelName.Drive, ModelName.Dir, RBuf[1], "");
        strncpy(Mat.NameMap[4], FullName, MaxStringLength - 1);
      }
      else if (RBuf("newmtl"))
      {
        if (IsFirst)
          IsFirst = FALSE;
        else 
          Materials << Mat;
        Mat = material(RBuf[1]);
      }
    }
  if (!IsFirst)
    Materials << Mat;
  fclose(F);
} /* End of 'tlr::material_manager::Load' function */

/* Load primitive object from file function.
 * ARGUMENTS:
 *   - animation system pointer:
 *       anim *Ani;
 *   - model (Alias Wavefront *.OBJ) file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL tlr::geom_prim::Load( anim *Ani, CHAR *FileName )
{
  file_path ModelName(FileName);

  /* Collect model geometry information */
  FILE *F;
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  stock<vec> ReadV;
  stock<vec> ReadN;
  stock<UV> ReadUV;
  stock<INT> ReadF;
  vertex_references VRefs(10);
  struct PRIMINFO
  {
    INT First, Last; // Facet indexes (first and last)
    material *Mat;   // Material pointer
  };
  stock<PRIMINFO> PrimsInfo;


  /* Read every file line */
  buffer RBuf;
  INT pri_no = 0;
  while (RBuf.Read(F))
  {
    if (RBuf("mtllib "))
    {
      RBuf.Split();
      Ani->Load(RBuf[1], FileName);
    }
    else if (RBuf("v "))
    {
      FLT x, y, z;

      RBuf.Split();
      sscanf(RBuf[1], "%f", &x);
      sscanf(RBuf[2], "%f", &y);
      sscanf(RBuf[3], "%f", &z);
      ReadV << vec(x, y, z) * 5;
    }
    else if (RBuf("vn "))
    {
      FLT x, y, z;

      RBuf.Split();
      sscanf(RBuf[1], "%f", &x);
      sscanf(RBuf[2], "%f", &y);
      sscanf(RBuf[3], "%f", &z);
      ReadN << vec(x, y, z);
    }
    else if (RBuf("vt "))
    {
      FLT u, v;

      RBuf.Split();
      sscanf(RBuf[1], "%f", &u);
      sscanf(RBuf[2], "%f", &v);
      ReadUV << UV(u, v);
    }
    else if (RBuf("f "))
    {
      RBuf.Split();

#define SCAN3(str, ref) \
      if (sscanf(str, "%i/%i/%i", &ref[0], &ref[1], &ref[2]) == 3) \
        ref[0]--, ref[1]--, ref[2]--;                              \
      else if (sscanf(str, "%i//%i", &ref[0], &ref[2]) == 2)       \
        ref[0]--, ref[2]--, ref[1] = -1;                           \
      else if (sscanf(str, "%i/%i", &ref[0], &ref[1]) == 2)        \
        ref[0]--, ref[1]--, ref[2] = -1;                           \
      else if (sscanf(str, "%i", &ref[0]) == 1)                    \
        ref[0]--, ref[1] = ref[2] = -1

      INT n0[3], n_prev[3], n[3], r0, r_prev, r;
      /* Start polygon point */
      SCAN3(RBuf[1], n0);
      r0 = VRefs.GetVertexNumber(n0[0], n0[2], n0[1]);

      /* Second polygon point */
      SCAN3(RBuf[2], n_prev);
      r_prev = VRefs.GetVertexNumber(n_prev[0], n_prev[2], n_prev[1]);

      for (INT i = 3; i < RBuf.NumOfParts; i++)
      {
        /* Third polygon point */
        SCAN3(RBuf[i], n);
        r = VRefs.GetVertexNumber(n[0], n[2], n[1]);

        /* Add triangle */
        ReadF << r0;
        ReadF << r_prev;
        ReadF << r;

        /* Go to next triangle */
        r_prev = r;
      }
    }
    else if (RBuf("usemtl"))
    {
      RBuf.Split();

      PrimsInfo.Alloc(1);
      if (pri_no != 0)
        PrimsInfo[pri_no - 1].Last = ReadF.Size() / 3 - 1; 
      PrimsInfo[pri_no].First = ReadF.Size() / 3;

      /* Look for material */
      PrimsInfo[pri_no].Mat = Ani->Create(RBuf[1]);
      pri_no++;
    }
  }
  /* Build result primitives */
  prim p;

  p.Create(prim::TRIMESH, VRefs.VertexRefs.Size(), ReadF.Size());
  p.OpenEditV();
  matr m;
  m.SetRotateX(-90);
  for (INT i = 0; i < p.NoofV; i++)
  {
    p.V[i].P = m * ReadV[VRefs.VertexRefs[i].Nv];
    p.V[i].N = ReadN[VRefs.VertexRefs[i].Nn];
    p.V[i].T = ReadUV[VRefs.VertexRefs[i].Nt];
    p.V[i].C = color(1, 1, 1);
  }
  p.OpenEditI();
  for (INT i = 0; i < p.NoofI; i++)
  {
    p.I[i] = ReadF[i];
  }

  Prims << p;

  fclose(F);
  return FALSE;
} /* End of 'tlr::geom_prim::Load' function */

/* END OF 'PRIMLOAD.CPP' FILE */
