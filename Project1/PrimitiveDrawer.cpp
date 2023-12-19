
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "texture.h"

#include "Point.h"
#include "PrimitiveDrawer.h"

PrimitiveDrawer::PrimitiveDrawer() {}

// Draw a point at the given position.
void PrimitiveDrawer::DrawPoint(Point point) {
    glBegin(GL_POINTS);
  //  glColor3b(1, 0,0);
    glVertex3f(point.x, point.y, point.z);
    glEnd();
}

// Draw a line between the given two positions.
void PrimitiveDrawer::DrawLine(Point start, Point end) {
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
}


// Draw a quadrilateral with the given four vertices.
void PrimitiveDrawer::DrawQuad(Point v1, Point v2, Point v3, Point v4,float r,float g,float b ) {
			 
    glBegin(GL_QUADS);
	glNormal3f(0,0,1);
 //   glColor3f(r,g,b);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);

    glEnd();	
}
void PrimitiveDrawer::DrawQuad4tank(Point v1, Point v2, Point v3, Point v4, float r, float g, float b, int buildingImage) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, buildingImage);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(v3.x, v3.y, v3.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(v4.x, v4.y, v4.z);
    glEnd();


    glDisable(GL_TEXTURE_2D);
}




void PrimitiveDrawer::DrawQuadImage(Point v1, Point v2, Point v3, Point v4, float r, float g, float b, int buildingImage) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, buildingImage);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(v3.x, v3.y, v3.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(v4.x, v4.y, v4.z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}




void PrimitiveDrawer::DrawQuadLand(Point v1, Point v2, Point v3, Point v4,float r,float g,float b,int buildingImage ) {
			glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, buildingImage);    
   glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(v1.x, v1.y, v1.z);
glTexCoord2f(0.0f, 20.0f); 

    glVertex3f(v2.x, v2.y, v2.z);
	glTexCoord2f(20.0f, 20.0f); 

    glVertex3f(v3.x, v3.y, v3.z);
	glTexCoord2f(20.0f, 0.0f); 

    glVertex3f(v4.x, v4.y, v4.z);


    glEnd();	

	 glDisable(GL_TEXTURE_2D);
	
}













void PrimitiveDrawer::Draw8poly(Point v1, Point v2, Point v3, Point v4,Point v5,Point v6,Point v7,Point v8,float r,float g,float b) {
    glBegin(GL_POLYGON);
  //  glColor3f(r,g,b);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
	glVertex3f(v5.x, v5.y, v5.z);
	glVertex3f(v6.x, v6.y, v6.z);
	glVertex3f(v7.x, v7.y, v7.z);
	glVertex3f(v8.x, v8.y, v8.z);
    glEnd();


}

void PrimitiveDrawer::Draw6poly(Point v1, Point v2, Point v3, Point v4, Point v5, Point v6, int textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_POLYGON);
    // Assuming you want to apply the texture in a planar manner, you need to specify texture coordinates for each vertex.
    // You can adjust these coordinates based on your desired texture mapping.
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(v1.x, v1.y, v1.z);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(v2.x, v2.y, v2.z);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(v3.x, v3.y, v3.z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(v4.x, v4.y, v4.z);

    glTexCoord2f(0.5f, 1.0f);  // Example of different texture coordinate
    glVertex3f(v5.x, v5.y, v5.z);

    glTexCoord2f(0.5f, 0.0f);  // Example of different texture coordinate
    glVertex3f(v6.x, v6.y, v6.z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}