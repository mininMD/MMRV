/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : Def.frag
 * PURPOSE     : Tough Light Racing project.
 *               Fragment shader.
 *               Default shader.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A, Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#version 330

/* Common variables */
uniform mat4 MatrWorldViewProj, MatrWorld;
uniform vec3 CamDir;

uniform vec3 Ka, Kd, Ks;
uniform float Phong, Alpha;
uniform float Time, Width, Height;

uniform sampler2D MapKa, MapKd, MapKs, MapKt, MapN;

/* Output color */
out vec4 OutColor;

/* Fragment shader input parameters */
in vec4 DrawColor;
in vec4 DrawPos;
in vec4 DrawNormal;
in vec4 DrawTexCoord;


vec4 GetColor( vec3 N )
{
  vec4 TC = texture(MapKd, DrawTexCoord.st);
  ivec2 s = textureSize(MapKd, 1);
  if (s.x == 0)
    TC = vec4(1, 1, 1, 1);

  vec3 L = normalize(vec3(1, 1, 1));
  vec3 LightColor = vec3(1, 1, 1);

  N = faceforward(N, CamDir, N);

  /* Ambient */
  vec3 res_color = Ka * vec3(0.1, 0.1, 0.1);

  /* Diffuse */
  float nl = dot(L, vec3(N));
  if (nl > 0.00001)
    res_color.xyz += (Kd.xyz * TC.xyz) * nl;

  /* Specular */
  vec3 R = reflect(CamDir, N);
  float rn = dot(R, N);
  if (rn > 0.00001)
    res_color.xyz += Ks.xyz * pow(rn, Phong);

  return vec4((DrawColor.xyz * res_color) / 1, 1 - Alpha);
}

/* Main function */
void main( void )
{
  OutColor = GetColor(normalize(vec3(DrawNormal)));
} /* End of 'main' function */

/* END OF 'Def.frag' FILE */
