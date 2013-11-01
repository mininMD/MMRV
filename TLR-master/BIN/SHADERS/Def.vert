/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : Def.vert
 * PURPOSE     : Tough Light Racing project.
 *               Vertex shader.
 *               Default shader.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A, Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "common.inc"

#version 330

/* Common variables */
uniform mat4 MatrWorldViewProj, MatrWorld;
uniform vec3 CamDir;

uniform vec3 Ka, Kd, Ks;
uniform float Phong, Alpha;
uniform float Time, Width, Height;

uniform sampler2D MapKa, MapKd, MapKs, MapKt, MapN;

/* Vertex shader input parameters */
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vTexCoord;
layout(location = 2) in vec4 vNormal;
layout(location = 3) in vec4 vColor;

out vec4 DrawColor;
out vec4 DrawPos;
out vec4 DrawNormal;
out vec4 DrawTexCoord;

/* Main function */
void main( void )
{
  mat4 MIT = transpose(inverse(MatrWorld));
  vec4 N = MIT * vNormal;

  gl_Position = MatrWorldViewProj * vPosition;
  DrawPos = vPosition;
  DrawNormal = N;
  DrawColor = vColor;
  DrawTexCoord = vTexCoord;
} /* End of 'main' function */

/* END OF 'Def.vert' FILE */
