#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>
#include<glu.h>// Header File For The GLu32 Library
#include<glut.h>
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "Point.h" 
#include "PrimitiveDrawer.h" 
#include "camera.h"
#include "texture.h"






HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Cntext
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = true;	// Fullscreen Flag Set To Fullscreen Mode By Default
int mouseX = 0, mouseY = 0;
bool isClicked = 0, isRClicked = 0;
int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;
bool isLightOn = true;
float lightColor[];

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
//void handleKeyPress(unsigned char key, int x, int y) {
//	if (key == 'j' || key == 'J') {
//		isLightOn = !isLightOn;
//		if (isLightOn) {
//			glEnable(GL_LIGHT0);
//		}
//		else {
//			glDisable(GL_LIGHT0);
//		}
//	}
//}

Camera MyCamera;

double movX, movY, movZ;
double lX, lY;


double z;
double gunRotate;
double gunPointing;

void toggleLight() {
	isLightOn = !isLightOn;
	if (isLightOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
}

void Key(bool* keys, float speed)
{
	/*if (keys['S']){
		MyCamera.RotateX(-1 * speed/10);
	}
	if (keys['W']){
		MyCamera.RotateX(1 * speed/10);
	}*/

	


	if (keys['D']){
		MyCamera.RotateY(-1 * speed/10);
	}
	if (keys['Z']){
		//MyCamera.RotateZ(1 * speed);
		if(gunPointing<=5)
		gunPointing+=0.2;
	}
	if (keys['X']){
		//MyCamera.RotateZ(-1 * speed);
		if(gunPointing>=-5)
		gunPointing-=0.2;
		
	}
	/*if (keys['A']){
		MyCamera.RotateY(1 * speed/10);
	}*/
	if (keys[VK_UP]){
		if(z<180){
	z-=-speed/3;
	MyCamera.MoveForward(1 * speed);}
	}
	if (keys[VK_DOWN]){
		if(z>-180){
		z-=speed/3;
		MyCamera.MoveForward(-1 * speed);}
	}
	if (keys[VK_RIGHT]){
		gunRotate-=speed/3;
		//MyCamera.MoveRight(1 * speed);
	}
	if (keys[VK_LEFT]){
		gunRotate+=speed/3;
	//	MyCamera.MoveRight(-1 * speed);
	}
	if (keys['O']){
		MyCamera.MoveUpward(1 * speed);}
	if (keys['L']){
		MyCamera.MoveUpward(-1 * speed);}
	if (keys['J'] || keys['j']) {
			isLightOn = true;
			glEnable(GL_LIGHT0);
	}
	if (keys['H'] || keys  ['h']) {
		isLightOn = false;
		//glDisable(GL_LIGHT0);
	}
}

double k = 0 , l=0 , h=0;


void mouse(int mouseX, int mouseY, bool isClicked, bool isRClicked)
{
      /* if (mouseX){
		    k = float((mouseX-520)*10)/640;
			l = float((mouseY-520)*10)/640;
			glTranslated(k,l,0);
	       
	      } */
	   if(isClicked){
	      h+=0.1f;
	   }
	    if(isRClicked){
	      h-=0.1f;
	   
	   }


}

double rocketX,rocketY,rocketZ;
bool isDone;
bool left;
int buildingImage,landImage,tankImage,rocketImage;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	//glEnable(GL_TEXTURE_2D);
	buildingImage = LoadTexture("download1.bmp", 255);
	tankImage=LoadTexture("tank1.bmp");
	landImage = LoadTexture("dart.bmp");
	rocketImage=LoadTexture("rocket1.bmp");
	//image3 = LoadTexture("building.bmp", 255);
	SKYFRONT = LoadTexture("download.bmp", 255);
	SKYBACK = LoadTexture("download.bmp", 255);
	SKYLEFT = LoadTexture("download.bmp", 255);
	SKYRIGHT = LoadTexture("download.bmp", 255);
	SKYUP = LoadTexture("download.bmp", 255);
	SKYDOWN = LoadTexture("download.bmp", 255);

	glDisable(GL_TEXTURE_2D);


	MyCamera = Camera();
	MyCamera.RotateY(180);
	//MyCamera.RotateX(-10);
	MyCamera.Position.x = 0;
	MyCamera.Position.y = 20;
	MyCamera.Position.z = -100;
	
	return TRUE;										// Initialization Went OK
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	float lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (isLightOn==false)
	{
		lightColor[0] = 0.0f;
		lightColor[1] = 0.0f;
		lightColor[2] = 1.0f;
	}
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GLUquadricObj* B = gluNewQuadric();
PrimitiveDrawer primitiveDrawer=PrimitiveDrawer();

double ticker=0;
bool allowTicker=false;

void drawGun(){
	
		glPushMatrix();
		glRotated(gunRotate,0,1,0);
//bottom 6 poly
Point i = Point(0,2,2);
Point j = Point(2,2,1);
Point k = Point(2,2,-1);
Point l = Point(0,2,-2);
Point m = Point(-2,2,-1);
Point n = Point(-2,2,1);
//glColor3f(0,0,1);
primitiveDrawer.Draw6poly(i,j,k,l,m, n,tankImage);
//up 6 poly
Point i1 = Point(0,3,2);
Point j1 = Point(2,3,1);
Point k1 = Point(2,3,-1);
Point l1 = Point(0,3,-2);
Point m1 = Point(-2,3,-1);
Point n1 = Point(-2,3,1);
//glColor3f(0,0,1);
primitiveDrawer.Draw6poly(i1,j1,k1,l1,m1, n1,tankImage);



//1
primitiveDrawer.DrawQuad4tank(i,j,j1,i1,0, 1, 1,tankImage);

//2
primitiveDrawer.DrawQuad4tank(j,k,k1,j1,1, 1, 1,tankImage);

//3
primitiveDrawer.DrawQuad4tank(k,l,l1,k1,1, 0, 1,tankImage);

//4
primitiveDrawer.DrawQuad4tank(l,m,m1,l1,0, 1, 0,tankImage);

//4
primitiveDrawer.DrawQuad4tank(m,n,n1,m1,0, 1, 0,tankImage);

//5
primitiveDrawer.DrawQuad4tank(n,i,i1,n1,1, 1, 0,tankImage);


//gun
glRotated(gunPointing,1,0,0);
glTranslated(0,2.5,1);

//glColor3f(1,0,1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tankImage);  // gunTexture is the ID of your loaded texture
	  gluQuadricTexture(B, GL_TRUE);

gluCylinder(B, 0.4,0.4,4.8, 20, 20);
glDisable(GL_TEXTURE_2D);
if(isClicked||isDone){
	
    glEnable(GL_BLEND);
  


	
	if(isRClicked){
			glPushMatrix();
		if(ticker>=100){
		//glColor4f(0,0,0,0);
			  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslated(0,0,0);
		rocketZ=0;
		isDone=false;
		ticker=0;
		allowTicker=false;
		glDisable(GL_BLEND);
		}
		if(isClicked&&isDone){
			allowTicker=true;}
	}
	
	else{
			glPushMatrix();
//glColor3f(1,0,0);
	}
		glPushMatrix();

	//glColor3f(1,0,0);
	ticker+=1;
	glTranslated(0,0,rocketZ+=0.5);/////////////////////////////////////////////////////////////////////////////////////
	    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, rocketImage);  // gunTexture is the ID of your loaded texture
	  gluQuadricTexture(B, GL_TRUE);
	  gluSphere(B,0.3,20,20);
	gluCylinder(B,0.3,0.3,2,20,20);
glDisable(GL_TEXTURE_2D);

	 
	 glPopMatrix();
}
glPopMatrix();
glPopMatrix();
}



void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYFRONT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void drawTank(){
	
		glPushMatrix();
	glTranslated(0,0,z);
	//down face
	Point a= Point(2,0,-2.5);
	Point b= Point(2,0,2.5);
	Point c= Point(-2,0,2.5);
	Point d= Point(-2,0,-2.5);
	primitiveDrawer.DrawQuad4tank(a,b,c,d,1, 0, 0,tankImage);


	//up face
	Point e= Point(2,2,-4);
	Point f= Point(2,2,4);
	Point g= Point(-2,2,4);
	Point h= Point(-2,2,-4);	
	
		primitiveDrawer.DrawQuad4tank(e,f,g,h,1, 0, 0,tankImage);

	//wheels
	Point e1= Point(2,1,-2.5);
	Point f1= Point(2,1,2.5);
	Point g1= Point(-2,1,2.5);
	Point h1= Point(-2,1,-2.5);	

	//left face

	//h
	//e
	//b
	//a
	primitiveDrawer.DrawQuad4tank(a,b,f,e,0, 1, 0,tankImage);

	//left wheel
		primitiveDrawer.DrawQuad4tank(a,b,f1,e1,0, 0, 0,tankImage);

			
	//rightface
	//a
	//c
	//f
	//g
	primitiveDrawer.DrawQuad4tank(c,d,h,g,0, 0, 1,tankImage);
	//right wheel
	primitiveDrawer.DrawQuad4tank(c,d,h1,g1,0, 0, 0,tankImage);

	//backface

	primitiveDrawer.DrawQuad4tank(a,d,h,e,1, 0, 1,tankImage);


	//frontface
	//
		primitiveDrawer.DrawQuad4tank(b,c,g,f,0, 1, 1,tankImage);
		
		drawGun();

}

void drawLand(){
	//land
	Point al= Point(400,0,-450);
	Point bl= Point(400,0,450);
	Point cl= Point(-400,0,450);
	Point dl= Point(-400,0,-450);
	primitiveDrawer.DrawQuadLand(al,bl,cl,dl,1, 0.2, 0.5,landImage
		);
}

void drawBuildings(){
	

glPushMatrix();
//bulding bottom
Point bu1 = Point(15,0,0);
Point bu2 = Point(25,0,0);
Point bu3 = Point(25,0,-15);
Point bu4 = Point(15,0,-15);
//primitiveDrawer.DrawQuad(bu1,bu2,bu3,bu4,1, 1, 1);
//bulding top
Point bu12 = Point(15,20,0);
Point bu22 = Point(25,20,0);
Point bu32 = Point(25,20,-15);
Point bu42 = Point(15,20,-15);
//primitiveDrawer.DrawQuad(bu12,bu22,bu32,bu42,1, 1, 1);
  

for (int i = 0; i < 10; i++)
{
	glTranslated(0,0,20);
	primitiveDrawer.DrawQuadImage(bu1,bu2,bu3,bu4,1, 1, 1,buildingImage);
  primitiveDrawer.DrawQuadImage(bu12,bu22,bu32,bu42,1, 1, 1,buildingImage);
  

//1
  primitiveDrawer.DrawQuadImage(bu1,bu2,bu22,bu12,0, 1, 1,buildingImage);
  //2
  primitiveDrawer.DrawQuadImage(bu2,bu3,bu32,bu22,1, 0, 1,buildingImage);
  //3
  primitiveDrawer.DrawQuadImage(bu3,bu4,bu42,bu32,1, 1, 0,buildingImage);
  //4
  primitiveDrawer.DrawQuadImage(bu4,bu1,bu12,bu42,0, 0, 1,buildingImage);


}
glPopMatrix();

glPushMatrix();
for (int i = 0; i < 10; i++)
{
	glTranslated(0,0,-20);
	primitiveDrawer.DrawQuadImage(bu1,bu2,bu3,bu4,1, 1, 1,buildingImage);
  primitiveDrawer.DrawQuadImage(bu12,bu22,bu32,bu42,1, 1, 1,buildingImage);
  

//1
  primitiveDrawer.DrawQuadImage(bu1,bu2,bu22,bu12,0, 1, 1,buildingImage);
  //2
  primitiveDrawer.DrawQuadImage(bu2,bu3,bu32,bu22,1, 0, 1,buildingImage);
  //3
  primitiveDrawer.DrawQuadImage(bu3,bu4,bu42,bu32,1, 1, 0,buildingImage);
  //4
  primitiveDrawer.DrawQuadImage(bu4,bu1,bu12,bu42,0, 0, 1,buildingImage);


}


glPopMatrix();



glTranslated(-40,0,0);
glPushMatrix();


for (int i = 0; i < 10; i++)
{
	glTranslated(0,0,20);
	primitiveDrawer.DrawQuadImage(bu1,bu2,bu3,bu4,1, 1, 1,buildingImage);
  primitiveDrawer.DrawQuadImage(bu12,bu22,bu32,bu42,1, 1, 1,buildingImage);
  

//1
  primitiveDrawer.DrawQuadImage(bu1,bu2,bu22,bu12,0, 1, 1,buildingImage);
  //2
  primitiveDrawer.DrawQuadImage(bu2,bu3,bu32,bu22,1, 0, 1,buildingImage);
  //3
  primitiveDrawer.DrawQuadImage(bu3,bu4,bu42,bu32,1, 1, 0,buildingImage);
  //4
  primitiveDrawer.DrawQuadImage(bu4,bu1,bu12,bu42,0, 0, 1,buildingImage);


}
glPopMatrix();

glPushMatrix();
for (int i = 0; i < 10; i++)
{
	glTranslated(0,0,-20);
	primitiveDrawer.DrawQuadImage(bu1,bu2,bu3,bu4,1, 1, 1,buildingImage);
  primitiveDrawer.DrawQuadImage(bu12,bu22,bu32,bu42,1, 1, 1,buildingImage);
  

//1
  primitiveDrawer.DrawQuadImage(bu1,bu2,bu22,bu12,0, 1, 1,buildingImage);
  //2
  primitiveDrawer.DrawQuadImage(bu2,bu3,bu32,bu22,1, 0, 1,buildingImage);
  //3
  primitiveDrawer.DrawQuadImage(bu3,bu4,bu42,bu32,1, 1, 0,buildingImage);
  //4
  primitiveDrawer.DrawQuadImage(bu4,bu1,bu12,bu42,0, 0, 1,buildingImage);


}

glPopMatrix();
}


void Light() {
	/*glPushMatrix();*/
	//
	
	init();
	/*glPopMatrix();*/
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{   
		//glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	glClear( GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//Draw_Skybox(0, 0, 0, 1, 1, 1);
		mouse(mouseX, mouseY, isClicked, isRClicked);
		MyCamera.Render();
	Key(keys, .1);
		Draw_Skybox(0, 0, 0, 4000, 4000,4000);
		Camera();

	
	glTranslated(0, -3, -30);
	glScaled(3,3,3);

	

	glPushMatrix();

drawLand();

	
drawTank();
glPopMatrix();
	glPushMatrix();
drawBuildings();
Light();
glPopMatrix();


	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}


BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{

case WM_MOUSEMOVE:
	{
		mouseX = (int)LOWORD(lParam);
		mouseY = (int)HIWORD(lParam);
		isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
		isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
		break;
	}

	case WM_LBUTTONUP:
		{
			isClicked = false;
		break;
		}
	case WM_RBUTTONUP:
		isRClicked = false;   break;
	case WM_LBUTTONDOWN:
		{
			isDone= true;
			isClicked = true;
		break;
		}
	case WM_RBUTTONDOWN:
		isRClicked = true;	break;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}




int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = false;							// Windowed Mode
	}
	//wc.lpfnWndProc = (WNDPROC)WndProc;	

	// Create Our OpenGL Window
	if (!CreateGLWindow("Example", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}







	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}




//