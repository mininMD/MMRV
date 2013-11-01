/***************************************************************
 * Copyright (C) 2013
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : COMMON.INC
 * PURPOSE     : Tough Light Racing project.
 *               Common shader includes.
 * PROGRAMMER  : CGSG'2013.
 *               Vitaly A, Galinsky.
 * LAST UPDATE : 03.08.2013
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

/* Common variables */
uniform mat4 MatrWorldViewProj, MatrWorld;
uniform vec3 CamDir;

uniform vec3 Ka, Kd, Ks;
uniform float Phong, Alpha;
uniform float Time, Width, Height;

uniform sampler2D MapKa, MapKd, MapKs, MapKt, MapN;

/* END OF 'COMMON.INC' FILE */
