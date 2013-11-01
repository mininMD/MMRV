/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PRIM.H
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

#ifndef __PRIM_H_
#define __PRIM_H_

#include "mtl.h"

/* Project namespace */
namespace tlr
{
  /* Texture coordinate representation type */
  struct UV
  {
    FLT U, V; // Texture coordinates (U - x, V - y)

    /* Constructor */
    UV( VOID )
    {
    } /* End of 'UV' function */

    /* Constructor */
    UV( FLT NewU, FLT NewV ) : U(NewU), V(NewV)
    {
    } /* End of 'UV' function */
  }; /* End of 'UV' class */

  /* Space point representation type */
  struct VERTEX
  {
    vec P;   // Point location
    UV T;    // Point texture coordinates
    vec N;   // Point normal
    color C; // Point color

    /* Constructor */
    VERTEX( VOID )
    {
    } /* End of 'VERTEX' function */

    /* Constructor.
     * ARGUMENTS:
     *   - vertex position:
     *       vec NewP;
     *   - vertex color:
     *       const color &NewColor;
     */
    VERTEX( const vec &NewP, const color &NewColor = color(1) ) :
      P(NewP), C(NewColor), N(vec(0, 1, 0)), T(UV(0, 0))
    {
    } /* End of 'VERTEX' function */

    /* Constructor.
     * ARGUMENTS:
     *   - vertex position:
     *       vec &NewP;
     *   - vertex color:
     *       const color &NewColor;
     *   - vertex normal:
     *       vec &NewN;
     *   - vertex texture coordinates:
     *       UV &NewTex;
     */
    VERTEX( const vec &NewP, const color &NewColor, const vec &NewN, const UV &NewTex ) :
      P(NewP), C(NewColor), N(NewN), T(NewTex)
    {
    } /* End of 'VERTEX' function */

    /* Constructor.
     * ARGUMENTS:
     *   - vertex position:
     *       vec &NewP;
     *   - vertex color:
     *       color &NewColor;
     *   - vertex texture coordinates:
     *       UV &NewTex;
     */
    VERTEX( const vec &NewP, const DWORD &NewColor, const UV &NewTex ) :
      P(NewP), C(NewColor), T(NewTex), N(vec(0, 1, 0))
    {
    } /* End of 'VERTEX' function */
  }; /* End of 'VERTEX' structure */

  /* Geometry primitive class */
  class prim
  {
    friend class render;
  private:

    /* Memory pool */
    BYTE *MemPool;
    UINT MemSize;

    /* Triangles indexes */
    UINT *Indexes;
    /* Vertexes array (or triangle points if indexes are not present) */
    VERTEX *Vertices;

    /* Flag for buffer content changes */
    BOOL IsIndexChange, IsVertexChange;
    INT SaveISize, SaveVSize;

    /* Primitive material */
    material *Material;

    /* Grid primitive size */
    INT GridW, GridH;

    /* Default primitive data (color and material) */
    static color DefaultColor;
    static material *DefaultMaterial;

  public:
    /* Set primitive default color function.
     * ARGUMENTS:
     *   - new default color value:
     *       const color &NewColor;
     * RETURNS: None.
     */
    static VOID SetDefaultColor( const color &NewColor )
    {
      DefaultColor = NewColor;
    } /* End of 'SetDefaultColor' function */

    /* Set primitive default material function.
     * ARGUMENTS:
     *   - new default material value:
     *       material *NewMaterial;
     * RETURNS: None.
     */
    static VOID SetDefaultMaterial( material *NewMaterial )
    {
      DefaultMaterial = NewMaterial;
    } /* End of 'SetDefaultMaterial' function */

    /* Enum type of primitive */
    enum TYPE
    {
      POINTS, LINES, STRIP, TRIMESH, GRID
    }; /* End of 'TYPE' enumeration */

    UINT VBuf, Buffs[2]; // Vertex and index buffer

  private:
    /* Primitive type */
    TYPE Type;

    /* Allocation primitive data function.
     * ARGUMENTS:
     *   - size of vertex and index arrays:
     *       INT NumOfVertexes, NumOfIndexes;
     * RETURNS: None.
     */
    VOID Alloc( INT NumOfVertexes, INT NumOfIndexes = 0 )
    {
      /* Free old memory */
      if (MemPool != NULL)
        delete [] MemPool;

      /* Set defaults */
      Type = POINTS;
      Material = NULL;
      IsIndexChange = TRUE;
      V = NULL;
      I = NULL;
      IsVertexChange = TRUE;
      SaveISize = 0;
      SaveVSize = 0;
      NoofV = NumOfVertexes;
      NoofI = NumOfIndexes;

      /* Allocate memory */
      MemSize = sizeof(VERTEX) * NumOfVertexes + sizeof(UINT) * NumOfIndexes;
      MemPool = new BYTE[MemSize];
      memset(MemPool, 0, MemSize);

      Vertices = (VERTEX *)MemPool;
      Indexes = (UINT *)(MemPool + sizeof(VERTEX) * NumOfVertexes);

      for (INT i = 0; i < NoofV; i++)
        Vertices[i].C = DefaultColor;
      Material = DefaultMaterial;
    } /* End of 'Alloc' function */

    /* Clone primitive function.
     * ARGUMENTS:
     *   - primitive to be cloned:
     *       const prim &P;
     * RETURNS: None.
     */
    VOID Clone( const prim &P )
    {
      Alloc(P.NoofV, P.NoofI);

      /* Copy data */
      Type = P.Type;
      Material = P.Material;
      GridH = P.GridH;
      GridW = P.GridW;

      memcpy(MemPool, P.MemPool, MemSize);
    } /* End of 'Clone' function */

  public:
    /* Interface pointers */
    UINT *I;
    VERTEX *V;

    /* Number of indexes and vertices */
    INT NoofI, NoofV;

    /* Class constructor */
    prim( VOID ) :
      MemPool(NULL), MemSize(0),
      Type(TRIMESH),
      Material(NULL),
      IsIndexChange(FALSE), IsVertexChange(FALSE),
      SaveISize(0), SaveVSize(0),
      Indexes(NULL), Vertices(NULL), VBuf(0), V(NULL), I(NULL), NoofI(0), NoofV(0)
    {
      Buffs[0] = 0;
      Buffs[1] = 0;
    } /* End of' prim' function */

    /* Destructor */
    ~prim( VOID );

    /* Class copying constructor.
     * ARGUMENTS:
     *   - primitive to be copied:
     *       const prim &P;
     */
    prim( const prim &P) : MemPool(NULL)
    {
      Clone(P);
    } /* End of 'prim' constructor */

    /* Assignment operator function.
     * ARGUMENTS:
     *   - primitive to be assign:
     *       const prim &P;
     * RETURNS:
     *   (prim &) self pointer.
     */
    prim & operator=( const prim &P )
    {
      Clone(P);
      return *this;
    } /* End of 'operator=' function */

    /* Create primitive (memory allocation) function.
     * ARGUMENTS:
     *   - primitive type:
     *       TYPE PrimType;
     *   - primitive size parameters:
     *       INT N, M;
     * RETURNS:
     *   (prim &) self pointer.
     */
    prim & Create( TYPE PrimType, INT N, INT M = 0 )
    {
      UINT nv, ni;

      /* Determine memory size */
      switch (PrimType)
      {
      case GRID:
        GridW = N;
        GridH = M;
        nv = (GridW + 1) * (GridH + 1);
        ni = (GridW + 1) * GridH * 2;
        break;
      default:
        nv = N;
        ni = M;
        break;
      }

      /* Allocate memory */
      Alloc(nv, ni);
      Type = PrimType;

      /* Postcreation deals */
      switch (PrimType)
      {
      case GRID:
        INT k = 0;
        for (INT i = 0; i < GridH; i++)
          for (INT j = 0; j <= GridW; j++)
          {
            Indexes[k++] = (i + 1) * (GridW + 1) + j;
            Indexes[k++] = (i + 0) * (GridW + 1) + j;
          }
        break;
      }
      return *this;
    } /* End of 'Create' function */

    /* Create primitive (memory allocation) function. */
    prim & CreatePlane( INT N, INT M, vec Loc = vec(0, 0, 0),
                        vec Du = vec(1, 0, 0), vec Dv = vec(0, 0, -1) );

    /* Create sphere function */
    prim & CreateSphere( FLT Radius, INT N, INT M, vec Loc = vec(0) );

    /* Create cylinder function */
    prim & CreateCylinder( FLT Radius, FLT Height, INT N, INT M, vec Loc = vec(0) );

    /* Create cone function */
    prim & CreateCone( FLT Radius, FLT Height, INT N, INT M, vec Loc = vec(0) );

    /* Start/end data edit function */
    VOID OpenEditV( VOID )
    {
      IsVertexChange  = TRUE;
      V = Vertices;
      SaveVSize = NoofV;
    } /* End of 'OpenEditV' function */

    /* Start/end data edit function */
    VOID OpenEditI( VOID )
    {
      IsIndexChange = TRUE;
      I = Indexes;
      SaveISize = NoofI;
    } /* End of 'OpenEditV' function */

    /* End data edit function */
    VOID CloseEdit( VOID )
    {
      if (I != NULL)
        I = NULL;
      if (V != NULL)
        V = NULL;
    } /* End of 'CloseEdit' function */

    /* Set Material function.
     * ARGUMENTS:
     *   - pointer to new material interface:
     *       material *Mtl;
     * RETURNS:
     *   (prim &) self pointer.
     */
    prim & SetMtl( material *Mtl )
    {
      Material = Mtl;
      return *this;
    } /* End of 'SetMtl' function */
  }; /* End of 'prim' class */

  /* Primitive collection geometry object class */
  class geom_prim
  {
  public:
    /* Primitive collection */
    stock<prim> Prims;

    /* Draw object function */
    VOID Draw( render *Rnd );

    /* Load primitive object from file function */
    BOOL Load( anim *Ani, CHAR *FileName );
  }; /* End of 'geom_prim' class */
} /* end 'tlr' nasespace */

#endif /* __PRIM_H_ */

/* END OF 'PRIM.H' FILE */
