/*
Load a triangle file exported from AC3D.  Takes a file
exported from AC3D as a triangle file as input.  
Outputs OpenGL code (function)to draw model in file
"drawTriModel.cpp".

public void drawTriModel(int listId)

Function drawTriModel(listId) creates a compiled display list
with the id of listId.  This file can either be 
inlined at the appropriate place in your program with 

# include "drawTriModel.cpp" 

or, it can part of your project and be referenced with the 
following function prototype and called in your draw function.

extern public void drawTriModel(int listId);

Triangle input file has 9 vertex positions and a 
hex color values.

Output file has following color for each surface,
and normals and positions values for each vertexk.

glBegin(GL_TRIANGLES);
   glColor3f(...);
   glNormal3f(...);
   glVertex3f(...);
   glVertex3f(...);
   glVertex3f(...);
   ... repeat for each triangle surface
glEnd();

There is only 1 color and normal supplied as AC3D 
modeler does not set colors at vertices, it sets them for 
surfaces.  So this is flat shading in OpenGL.

Usage:

$ triangleLoader < input.tri 

If you get a "#J" value in your normals like "-1.#J"  you have a 
"triangle" in your data file that is not a triangle.  Most likely, 
two of the edges for the triangle have the same value.  
For example the next 3 lines represent 1 line in the output from
the AC3D triangle exporter for a triangulated model.  Note that
the second and third vertices are the same point!  If you get this,
I suggest you tweak one of the equivalent points to set it off a little.

-1.34347 0.332058 -0.514927  
-1.41776 0.339353 -0.506495  
-1.41776 0.339353 -0.506495  0xFFFF00

manually edited fix:

-1.34347 0.332058 -0.514927  
-1.41776 0.339353 -0.506495  
-1.41776 0.339353 -0.516495  0xFFFF00

Mike Barnes
11/25/09

*/

# include <math.h>
# include <stdio.h>

float v[3][3];    // 3 vertices of triangle
float normal[3][3];  // normal of a vertex
const int X = 0, Y = 1, Z = 2;

// Normal n = cross(v1,v2)
void crossProduct(float v1[3], float v2[3], float n[3]) {
   n[X] = v1[Y] * v2[Z] - v1[Z] * v2[Y];
   n[Y] = v1[Z] * v2[X] - v1[X] * v2[Z];
   n[Z] = v1[X] * v2[Y] - v1[Y] * v2[X];
   }

// Compute 3 unit normals for the 3 vertices in v
// normal[0] = cross(vectorFrom v[0] to v[1], vectorFrom v[2] to v[0])
// normal[1] = cross(vectorFrom v[1] to v[2], vectorFrom v[0] to v[1])
// normal[2] = cross(vectorFrom v[2] to v[0], vectorFrom v[2] to v[0])
// This program only requires 1 normal per surface.
// I wrote all 3 before realizing that...  
void computeNormals() {
  float vec[3][3];  // 3 clockwise vectors of surface 
  float length, sOs;
  // get 3 clockwise vectors for surface
  for(int i = 0; i < 3; i++) vec[0][i] = v[1][i] - v[0][i];
  for(int i = 0; i < 3; i++) vec[1][i] = v[2][i] - v[1][i];
  for(int i = 0; i < 3; i++) vec[2][i] = v[0][i] - v[2][i]; 
  // compute normals
  crossProduct(vec[2], vec[0], normal[0]);
  crossProduct(vec[0], vec[1], normal[1]);
  crossProduct(vec[1], vec[2], normal[2]);
  // convert to unit normal
  for(int n = 0; n < 3; n++){
     sOs = 0.0;  // sOs is sum of squares
     for(int i = 0; i < 3; i++) sOs += normal[n][i]*normal[n][i];
     length = sqrt(sOs);
     for(int i = 0; i < 3; i++) normal[n][i] = normal[n][i]/length;  
     }
  }

int main () {
   
   FILE * model;

   unsigned int c;
   unsigned int red, green, blue;
   bool done = false;
   
   model = fopen("drawTriModel.cpp", "w");		// open output file for writing and write "header"
   fprintf(model, "void drawTriModel(int listId, float scale) {\n");
   fprintf(model, "\tglEnable(GL_NORMALIZE);\n");
   fprintf(model, "\tglNewList(listId, GL_COMPILE);\n");
   fprintf(model, "\tglScalef(scale, scale, scale);\n");
   fprintf(model, "\tglBegin(GL_TRIANGLES);\n");
   fprintf(model, "\tGLfloat color[4];\n");  
   //read input from stdin.
   while (!feof(stdin)) {
      for(int i = 0; i < 3; i++) 
         for(int j = 0; j < 3; j++) {
            v[i][j] = -99999;
            if ( fscanf(stdin, "%f", &v[i][j]) == EOF) {
               // at end of file
               done = true;
               break;
               }
            }
      if(!done) {  // compute values
         // read and process color values  
         fscanf(stdin, "%x", &c);
         red = c;
         green = c;
         blue = c;
         red = red >> 16;
         green = green << 16;
         green = green >> 24;   
         blue = blue << 24;
         blue = blue >> 24;
         
         
         //fprintf(	model, "   glColor3f(%4.2f, %4.2f, %4.2f);\n", 
		 //			red/255.0, green/255.0, blue/255.0);
         computeNormals();  // computes 3 normals -- only use the first one.
         fprintf(model, "\t\tglNormal3f(");
         fprintf(model, "%6.2f, %6.2f, %6.2f);\n", 
            normal[0][X], normal[0][Y], normal[0][Z]);
		 fprintf(	model, "\t\t\tcolor[0]=%4.2f;\n\t\t\tcolor[1]=%4.2f;\n\t\t\tcolor[2]=%4.2f;\n\t\t\tcolor[3]=%4.2f;\n", 
		 			red/255.0, green/255.0, blue/255.0, 1.00);
		 fprintf(	model, "\t\t\tglMaterialfv(GL_FRONT, GL_DIFFUSE, color);\n");
         for(int i = 0; i < 3; i++) { 
            fprintf(model, "\t\t\tglVertex3f(");
            fprintf(model, "%6.2f, %6.2f, %6.2f);\n", 
               v[i][X], v[i][Y], v[i][Z]); 
            }
         }
      }
   fprintf(model, "\tglEnd();\n"); 
   fprintf(model, "\tglEndList();\n"); 
   fprintf(model, "}\n"); 
   fclose(model);
   return(0);
   }
