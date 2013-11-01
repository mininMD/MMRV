/* FILE NAME   : a.vert
 * PURPOSE     : Simple vertex shader.
 * PROGRAMMER  : TS5.
 * LAST UPDATE : 02.08.2013
 */


#version 400

layout(location = 0) in vec4 vPosition;
out vec4 UseColor;

/* Main function */
void main( void )
{
  gl_Position = vPosition;
  UseColor = vec4(1, 1, 1, 1);
} /* End of 'main' function */

/* End of 'a.vert' file */