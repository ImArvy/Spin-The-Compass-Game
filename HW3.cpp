/*
Ryan Vales
9/30/21
S00339723
CSCI 4550 : Computer Graphics
Homework 3
*/

#define _USE_MATH_DEFINES
#define MSEC_PER_FRAME 33.3 // 30 fps => 1000 / 30

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <ctime>

const float n = 50.0; // Global variable to define value of n

// Global variables to define center of ring shape.
float ringCenterX = 0.0;
float ringCenterY = 0.0;
float ringZ = 0.0;

// Global variables to define center of arrow shape.
float arrowCenterX = 0.0;
float arrowCenterY = 0.0;
float arrowZ = 0.0;

// Global variables to define center of triangle shape.
float triangleCenterX = 0.0;
float triangleCenterY = 125.0;
float triangleZ = 0.0;

// Global variables to define center of triangle outline.
float triangleOutlineCenterX = 0.0;
float triangleOutlineCenterY = 125.0;
float triangleOutlineZ = -0.5;

// Global variables to define center of cross shape.
float crossCenterX = 125.0;
float crossCenterY = 0.0;
float crossZ = 0.0;

// Global variables to define center of cross outline.
float crossOutlineCenterX = 125.0;
float crossOutlineCenterY = 0.0;
float crossOutlineZ = -0.5;

// Global variables to define center of diamond shape.
float diamondCenterX = 0.0;
float diamondCenterY = -125.0;
float diamondZ = 0.0;

// Global variables to define center of diamond outline.
float diamondOutlineCenterX = 0.0;
float diamondOutlineCenterY = -125.0;
float diamondOutlineZ = -0.5;

// Global variables to define center of star shape.
float starCenterX = -125.0;
float starCenterY = 0.0;
float starZ = 0.0;

// Global variables to define center of star outline.
float starOutlineCenterX = -125.0;
float starOutlineCenterY = 0.0;
float starOutlineZ = -0.5;

// Global variables to hold colors for shape outlines.
float triangleOutlineRed = 0.0;
float triangleOutlineBlue = 0.0;
float triangleOutlineGreen = 0.0;

float crossOutlineRed = 0.0;
float crossOutlineBlue = 0.0;
float crossOutlineGreen = 0.0;

float diamondOutlineRed = 0.0;
float diamondOutlineGreen = 0.0;
float diamondOutlineBlue = 0.0;

float starOutlineRed = 0.0;
float starOutlineGreen = 0.0;
float starOutlineBlue = 0.0;

// Global variables to hold colors for shapes.
float triangleRed = 0.0;
float triangleGreen = 0.0;
float triangleBlue = 1.0;

float crossRed = 1.0;
float crossGreen = 0.0;
float crossBlue = 0.0;

float diamondRed = 1.0;
float diamondGreen = 1.0;
float diamondBlue = 0.0;

float starRed = 0.0;
float starGreen = 1.0;
float starBlue = 0.0;

// Global variables to determine what shape a menu is attached to.
bool menuChangesTriangle = false;
bool menuChangesCross = false;
bool menuChangesDiamond = false;
bool menuChangesStar = false;

// Global variables to hold current position of mouse.
float mouseX = 250.0;
float mouseY = 250.0;

// Global variables to handle generating random numbers and rotation of the arrow.
bool shouldPause = true;
bool gameHasStarted = false;
int rot = 0;
int rotationCounter = 0;
int randomNumber = 0;

// Global variables to handle highlighting of the four shapes and drawing their corresponding text.
bool highlightTriangle = false;
bool highlightCross = false;
bool highlightDiamond = false;
bool highlightStar = false;

// Global variables to handle drawing text for winning and losing the game.
bool wonTheGame = false;
bool lostTheGame = false;
bool stoppedAtTriangle = false;
bool stoppedAtCross = false;
bool stoppedAtDiamond = false;
bool stoppedAtStar = false;

// Global variable to determine when the four shapes should rotate.
bool shouldRotateShapes = false;
float rotateShapes = 0.0;

// Function to draw grey ring.
void drawRing(int centerX, int centerY) {
	const float outerRadius = 175.0; // Const variable outerRadius is 175.0 as diameter of outer circle is 2 * 175, or 350.
	const float nDivByThree = (n / 3); // Const variable nDivByThree to get the difference between diamater of outer and inner circles.
	const float innerRadius = 175.0 - (nDivByThree / 2.0); // innerRadius is outerRadius - (n divided by three / 2), because inner diameter is outer diameter - n / 3.
	const int numOfVertices = 360;
	float t = 0;

	glBegin(GL_TRIANGLE_STRIP);

	glColor3f(0.50196078431, 0.50196078431, 0.50196078431); // grey, rgb(128.0, 128.0, 128.0)

	for (int i = 0; i < numOfVertices + 1; i++) {
		glVertex3f(centerX + outerRadius * cos(t), centerY + outerRadius * sin(t), ringZ); // First vertex is on outer circle, on next iteration the third vertex is on outer circle
		glVertex3f(centerX + innerRadius * cos(t), centerY + innerRadius * sin(t), ringZ); // Second vertex is on inner circle, on next iteration first vertex of secodn triangle is on inner circle
		t += 2 * M_PI / numOfVertices;
	}

	glEnd();
}

// Function to draw brown arrow.
void drawArrow(float centerX, float centerY, float size) {
	glColor3f(0.54509803921, 0.27058823529, 0.07450980392); // saddlebrown, rgb(139, 69, 19)

	glBegin(GL_POLYGON);

	// glVertex3f(0.0, 75.0, 0.0); // Top middle of triangular part
	glVertex3f(centerX, centerY + (3 * size), arrowZ);

	// glVertex3f(25.0, 50.0, 0.0; // Bottom right of triangular part
	glVertex3f(centerX + size, centerY + (size * 2), arrowZ);

	// glVertex3f(12.5, 50.0, 0.0); // Top right of rectangular part
	glVertex3f(centerX + (size / 2), centerY + (size * 2), arrowZ);

	// glVertex3f(12.5, -75.0, 0.0); // Bottom right of rectangular part
	glVertex3f(centerX + (size / 2), centerY - (3 * size), arrowZ);

	// glVertex3f(-12.5, -75.0, 0.0); // Bottom left of rectangular part
	glVertex3f(centerX - (size / 2), centerY - (size * 3), arrowZ);

	// glVertex3f(-12.5, 50.0, 0.0); // Top left of rectangular part
	glVertex3f(centerX - (size / 2), centerY + (size * 2), arrowZ);

	// glVertex3f(-25.0, 50.0, 0.0); // Bottom left of triangular part
	glVertex3f(centerX - size, centerY + (size * 2), arrowZ);

	glEnd();
}

// Function to draw blue triangle.
void drawTriangle(float centerX, float centerY, float size) {
	glColor3f(triangleRed, triangleGreen, triangleBlue); // blue, rgb(0, 0, 255)

	glBegin(GL_TRIANGLES);

	// glVertex3f(-25.0, 100.0, 0); // Left vertex of triangle
	glVertex3f(centerX - size, centerY - size, triangleZ);

	// glVertex3f(0.0, 150.0, 0); // Top vertex of triangle
	glVertex3f(centerX, centerY + size, triangleZ);

	// glVertex3f(25.0, 100.0, 0); // Right vertex of triangle
	glVertex3f(centerX + size, centerY - size, triangleZ);

	glEnd();
}

// Function to draw triangle outline.
void drawTriangleOutline(float centerX, float centerY, float size) {
	glColor3f(triangleOutlineRed, triangleOutlineGreen, triangleOutlineBlue);

	glBegin(GL_TRIANGLES);

	// glVertex3f(-25.0, 100.0, 0); // Left vertex of triangle
	glVertex3f(centerX - size, centerY - size, triangleOutlineZ);

	// glVertex3f(0.0, 150.0, 0); // Top vertex of triangle
	glVertex3f(centerX, centerY + size, triangleOutlineZ);

	// glVertex3f(25.0, 100.0, 0); // Right vertex of triangle
	glVertex3f(centerX + size, centerY - size, triangleOutlineZ);

	glEnd();
}

// Function to draw red cross.
void drawCross(float centerX, float centerY, float size) {
	glColor3f(crossRed, crossGreen, crossBlue); // red, rgb(255, 0, 0)

	glBegin(GL_POLYGON);

	// glVertex3f(120.0, 5.0, 0.0); // Bottom left vertex of top rectangle
	glVertex3f(centerX - (size / 5), centerY + (size / 5), crossZ);

	// glVertex3f(120.0, 25.0, 0.0); // Top left vertex of top rectangle
	glVertex3f(centerX - (size / 5), centerY + size, crossZ);

	// glVertex3f(130.0, 25.0, 0.0); // Top right vertex of top rectangle
	glVertex3f(centerX + (size / 5), centerY + size, crossZ);

	// glVertex3f(130.0, 5.0, 0.0); // Bottom right vertex of top rectangle
	glVertex3f(centerX + (size / 5), centerY + (size / 5), crossZ);

	// glVertex3f(150.0, 5.0, 0.0); // Top right vertex of right rectangle
	glVertex3f(centerX + size, centerY + (size / 5), crossZ);

	// glVertex3f(150.0, -5.0, 0.0); // Bottom right vertex of right rectangle
	glVertex3f(centerX + size, centerY - (size / 5), crossZ);

	// glVertex3f(130.0, -5.0, 0.0); // Bottom left vertex of right rectangle
	glVertex3f(centerX + (size / 5), centerY - (size / 5), crossZ);

	// glVertex3f(130.0, -25.0, 0.0); // Bottom right vertex of bottom rectangle
	glVertex3f(centerX + (size / 5), centerY - size, crossZ);

	// glVertex3f(120.0, -25.0, 0.0); // Bottom left vertex of bottom rectangle
	glVertex3f(centerX - (size / 5), centerY - size, crossZ);

	// glVertex3f(120.0, -5.0, 0.0); // Top left vertex of bottom rectangle
	glVertex3f(centerX - (size / 5), centerY - (size / 5), crossZ);

	// glVertex3f(100.0, -5.0, 0.0); // Bottom left vertex of left rectangle
	glVertex3f(centerX - size, centerY - (size / 5), crossZ);

	// glVertex3f(100.0, 5.0, 0.0); // Top left vertex of left rectangle
	glVertex3f(centerX - size, centerY + (size / 5), crossZ);

	glEnd();
}

// Function to draw cross outline.
void drawCrossOutline(float centerX, float centerY, float size) {
	glColor3f(crossOutlineRed, crossOutlineGreen, crossOutlineBlue);

	glBegin(GL_POLYGON);

	// glVertex3f(120.0, 5.0, 0.0); // Bottom left vertex of top rectangle
	glVertex3f(centerX - (size / 5), centerY + (size / 5), crossOutlineZ);

	// glVertex3f(120.0, 25.0, 0.0); // Top left vertex of top rectangle
	glVertex3f(centerX - (size / 5), centerY + size, crossOutlineZ);

	// glVertex3f(130.0, 25.0, 0.0); // Top right vertex of top rectangle
	glVertex3f(centerX + (size / 5), centerY + size, crossOutlineZ);

	// glVertex3f(130.0, 5.0, 0.0); // Bottom right vertex of top rectangle
	glVertex3f(centerX + (size / 5), centerY + (size / 5), crossOutlineZ);

	// glVertex3f(150.0, 5.0, 0.0); // Top right vertex of right rectangle
	glVertex3f(centerX + size, centerY + (size / 5), crossOutlineZ);

	// glVertex3f(150.0, -5.0, 0.0); // Bottom right vertex of right rectangle
	glVertex3f(centerX + size, centerY - (size / 5), crossOutlineZ);

	// glVertex3f(130.0, -5.0, 0.0); // Bottom left vertex of right rectangle
	glVertex3f(centerX + (size / 5), centerY - (size / 5), crossOutlineZ);

	// glVertex3f(130.0, -25.0, 0.0); // Bottom right vertex of bottom rectangle
	glVertex3f(centerX + (size / 5), centerY - size, crossOutlineZ);

	// glVertex3f(120.0, -25.0, 0.0); // Bottom left vertex of bottom rectangle
	glVertex3f(centerX - (size / 5), centerY - size, crossOutlineZ);

	// glVertex3f(120.0, -5.0, 0.0); // Top left vertex of bottom rectangle
	glVertex3f(centerX - (size / 5), centerY - (size / 5), crossOutlineZ);

	// glVertex3f(100.0, -5.0, 0.0); // Bottom left vertex of left rectangle
	glVertex3f(centerX - size, centerY - (size / 5), crossOutlineZ);

	// glVertex3f(100.0, 5.0, 0.0); // Top left vertex of left rectangle
	glVertex3f(centerX - size, centerY + (size / 5), crossOutlineZ);

	glEnd();
}

// Function to draw yellow diamond.
void drawDiamond(float centerX, float centerY, float size) {
	glColor3f(diamondRed, diamondGreen, diamondBlue); // yellow, rgb(255, 255, 0)

	glBegin(GL_POLYGON);

	// glVertex3f(0.0, -100.0, 0.0); // Top vertex of diamond
	glVertex3f(centerX, centerY + size, diamondZ);

	// glVertex3f(25.0, -125.0, 0.0); // Right vertex of diamond
	glVertex3f(centerX + size, centerY, diamondZ);

	// glVertex3f(0.0, -150.0, 0.0); // Bottom vertex of diamond
	glVertex3f(centerX, centerY - size, diamondZ);

	// glVertex3f(-25.0, -125.0, 0.0); // Left vertex of diamond
	glVertex3f(centerX - size, centerY, diamondZ);

	glEnd();
}

// Function to draw diamond outline.
void drawDiamondOutline(float centerX, float centerY, float size) {
	glColor3f(diamondOutlineRed, diamondOutlineGreen, diamondOutlineBlue);

	glBegin(GL_POLYGON);

	// glVertex3f(0.0, -100.0, 0.0); // Top vertex of diamond
	glVertex3f(centerX, centerY + size, diamondOutlineZ);

	// glVertex3f(25.0, -125.0, 0.0); // Right vertex of diamond
	glVertex3f(centerX + size, centerY, diamondOutlineZ);

	// glVertex3f(0.0, -150.0, 0.0); // Bottom vertex of diamond
	glVertex3f(centerX, centerY - size, diamondOutlineZ);

	// glVertex3f(-25.0, -125.0, 0.0); // Left vertex of diamond
	glVertex3f(centerX - size, centerY, diamondOutlineZ);

	glEnd();
}

// Function to draw green star.
void drawStar(float centerX, float centerY, float size) {
	glColor3f(starRed, starGreen, starBlue); // green, rgb(0.0, 255.0, 0.0)

	glBegin(GL_POLYGON);

	// glVertex3f(-117.5, 10.0, 0.0); // Vertex between top triangle and middle right triangle
	glVertex3f(centerX + (size / 3.33), centerY + (size / 2.5), starZ);

	// glVertex3f(-100.0, 10.0, 0.0); // Middle vertex of middle right triangle
	glVertex3f(centerX + size, centerY + (size / 2.5), starZ);

	// glVertex3f(-112.5, -5.0, 0.0); // Vertex between middle right triangle and bottom right triangle
	glVertex3f(centerX + (size / 2), centerY - (size / 5), starZ);

	// glVertex3f(-106.25.0, -25.0, 0.0); // Middle vertex of bottom right triangle
	glVertex3f(centerX + (size * 0.75), centerY - size, starZ);

	// glVertex3f(-125.0, -12.5, 0.0); // Vertex between bottom right triangle and bottom left triangle
	glVertex3f(centerX, centerY - (size / 2), starZ);

	// glVertex3f(-143.75, -25.0, 0.0); // Middle vertex of bottom left triangle
	glVertex3f(centerX - (size * 0.75), centerY - size, starZ);

	// glVertex3f(-137.5, -5.0, 0.0); // Vertex between bottom left triangle and middle left triangle
	glVertex3f(centerX - (size / 2), centerY - (size / 5), starZ);

	// glVertex3f(-150.0, 10.0, 0.0); // Middle vertex of middle left triangle
	glVertex3f(centerX - size, centerY + (size / 2.5), starZ);

	// glVertex3f(-132.5, 10.0, 0.0) // Vertex between middle left triangle and top triangle
	glVertex3f(centerX - (size / 3.33), centerY + (size / 2.5), starZ);

	// glVertex3f(-125.0, 25.0, 0.0); // Middle vertex of top triangle
	glVertex3f(centerX, centerY + size, starZ);

	glEnd();
}

// Function to draw star outline.
void drawStarOutline(float centerX, float centerY, float size) {
	glColor3f(starOutlineRed, starOutlineGreen, starOutlineBlue);

	glBegin(GL_POLYGON);

	// glVertex3f(-117.5, 10.0, 0.0); // Vertex between top triangle and middle right triangle
	glVertex3f(centerX + (size / 3.33), centerY + (size / 2.5), starOutlineZ);

	// glVertex3f(-100.0, 10.0, 0.0); // Middle vertex of middle right triangle
	glVertex3f(centerX + size, centerY + (size / 2.5), starOutlineZ);

	// glVertex3f(-112.5, -5.0, 0.0); // Vertex between middle right triangle and bottom right triangle
	glVertex3f(centerX + (size / 2), centerY - (size / 5), starOutlineZ);

	// glVertex3f(-106.25.0, -25.0, 0.0); // Middle vertex of bottom right triangle
	glVertex3f(centerX + (size * 0.75), centerY - size, starOutlineZ);

	// glVertex3f(-125.0, -10.0, 0.0); // Vertex between bottom right triangle and bottom left triangle
	glVertex3f(centerX, centerY - (size / 2), starOutlineZ);

	// glVertex3f(-143.75, -25.0, 0.0); // Middle vertex of bottom left triangle
	glVertex3f(centerX - (size * 0.75), centerY - size, starOutlineZ);

	// glVertex3f(-137.5, -5.0, 0.0); // Vertex between bottom left triangle and middle left triangle
	glVertex3f(centerX - (size / 2), centerY - (size / 5), starOutlineZ);

	// glVertex3f(-150.0, 10.0, 0.0); // Middle vertex of middle left triangle
	glVertex3f(centerX - size, centerY + (size / 2.5), starOutlineZ);

	// glVertex3f(-132.5, 10.0, 0.0) // Vertex between middle left triangle and top triangle
	glVertex3f(centerX - (size / 3.33), centerY + (size / 2.5), starOutlineZ);

	// glVertex3f(-125.0, 25.0, 0.0); // Middle vertex of top triangle
	glVertex3f(centerX, centerY + size, starOutlineZ);

	glEnd();
}

// Function to handle creation of text.
void writeBitmapString(void* font, const char* string) {
	for (const char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void drawTriangleText() {
	if (!stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-190.0, -220.0, 0.0);
		if (triangleRed == 0.0 && triangleGreen == 0.0 && triangleBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Blue triangle is selected. Press SPACE to spin!");
		}
		else if (triangleRed == 1.0 && triangleGreen == 0.0 && triangleBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Purple triangle is selected. Press SPACE to spin!");
		}
		else if (triangleRed == 1.0 && triangleGreen == 0.5 && triangleBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Orange triangle is selected. Press SPACE to spin!");
		}
		else if (triangleRed == 0.0 && triangleGreen == 1.0 && triangleBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Cyan triangle is selected. Press SPACE to spin!");
		}
		else if (triangleRed == 1.0 && triangleGreen == 0.75 && triangleBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Pink triangle is selected. Press SPACE to spin!");
		}
	}
	else if (stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "Congratulations, you win!");
	}
	else {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "That's too bad, you lose!");
	}
}

void drawCrossText() {
	if (!stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-190.0, -220.0, 0.0);
		if (crossRed == 1.0 && crossGreen == 0.0 && crossBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Red cross is selected. Press SPACE to spin!");
		}
		else if (crossRed == 1.0 && crossGreen == 0.0 && crossBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Purple cross is selected. Press SPACE to spin!");
		}
		else if (crossRed == 1.0 && crossGreen == 0.5 && crossBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Orange cross is selected. Press SPACE to spin!");
		}
		else if (crossRed == 0.0 && crossGreen == 1.0 && crossBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Cyan cross is selected. Press SPACE to spin!");
		}
		else if (crossRed == 1.0 && crossGreen == 0.75 && crossBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Pink cross is selected. Press SPACE to spin!");
		}
	} else if (!stoppedAtTriangle && stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "Congratulations, you win!");
	} else {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "That's too bad, you lose!");
	}
}

void drawDiamondText() {
	if (!stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-190.0, -220.0, 0.0);
		if (diamondRed == 1.0 && diamondGreen == 1.0 && diamondBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Yellow diamond is selected. Press SPACE to spin!");
		}
		else if (diamondRed == 1.0 && diamondGreen == 0.0 && diamondBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Purple diamond is selected. Press SPACE to spin!");
		}
		else if (diamondRed == 1.0 && diamondGreen == 0.5 && diamondBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Orange diamond is selected. Press SPACE to spin!");
		}
		else if (diamondRed == 0.0 && diamondGreen == 1.0 && diamondBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Cyan diamond is selected. Press SPACE to spin!");
		}
		else if (diamondRed == 1.0 && diamondGreen == 0.75 && diamondBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Pink diamond is selected. Press SPACE to spin!");
		}
	}
	else if (!stoppedAtTriangle && !stoppedAtCross && stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "Congratulations, you win!");
	}
	else {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "That's too bad, you lose!");
	}
}

void drawStarText() {
	if (!stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && !stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-190.0, -220.0, 0.0);
		if (starRed == 0.0 && starGreen == 1.0 && starBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Green star is selected. Press SPACE to spin!");
		}
		else if (starRed == 1.0 && starGreen == 0.0 && starBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Purple star is selected. Press SPACE to spin!");
		}
		else if (starRed == 1.0 && starGreen == 0.5 && starBlue == 0.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Orange star is selected. Press SPACE to spin!");
		}
		else if (starRed == 0.0 && starGreen == 1.0 && starBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Cyan star is selected. Press SPACE to spin!");
		}
		else if (starRed == 1.0 && starGreen == 0.75 && starBlue == 1.0) {
			writeBitmapString(GLUT_BITMAP_8_BY_13, "Pink star is selected. Press SPACE to spin!");
		}
	}
	else if (!stoppedAtTriangle && !stoppedAtCross && !stoppedAtDiamond && stoppedAtStar) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "Congratulations, you win!");
	}
	else {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-110.0, -220.0, 0.0);
		writeBitmapString(GLUT_BITMAP_8_BY_13, "That's too bad, you lose!");
	}
}

// Drawing routine.
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(rot, 0, 0, -1);
	drawArrow(arrowCenterX, arrowCenterY, n / 2); // Call function drawArrow() to draw brown arrow shape.
	glLoadIdentity();

	if (highlightTriangle) {
		glLoadIdentity();
		glRotatef(rotateShapes, 0, 0, 1);
		drawTriangleOutline(triangleOutlineCenterX, triangleOutlineCenterY, n - 15); // Call function drawTriangleOutline() to draw triangle outline.
		glLoadIdentity();
		drawTriangleText();
	}
	glLoadIdentity();
	glRotatef(rotateShapes, 0, 0, 1);
	drawTriangle(triangleCenterX, triangleCenterY, n / 2); // Call function drawTriangle() to draw blue triangle shape.
	glLoadIdentity();

	if (highlightCross) {
		glLoadIdentity();
		glRotatef(rotateShapes, 0, 0, 1);
		drawCrossOutline(crossOutlineCenterX, crossOutlineCenterY, n - 15); // Call function drawCrossOutline() to draw cross outline.
		glLoadIdentity();
		drawCrossText();
	}
	glLoadIdentity();
	glRotatef(rotateShapes, 0, 0, 1);
	drawCross(crossCenterX, crossCenterY, n / 2); // Call function drawCross() to draw red cross shape.
	glLoadIdentity();

	if (highlightDiamond) {
		glLoadIdentity();
		glRotatef(rotateShapes, 0, 0, 1);
		drawDiamondOutline(diamondOutlineCenterX, diamondOutlineCenterY, n - 15); // Call function drawDiamondOutline() to draw diamond outline.
		glLoadIdentity();
		drawDiamondText();
	}
	glLoadIdentity();
	glRotatef(rotateShapes, 0, 0, 1);
	drawDiamond(diamondCenterX, diamondCenterY, n / 2); // Call function drawDiamond() to draw yellow diamond shape.
	glLoadIdentity();


	if (highlightStar) {
		glLoadIdentity();
		glRotatef(rotateShapes, 0, 0, 1);
		drawStarOutline(starOutlineCenterX, starOutlineCenterY, n - 15); // Call function drawStarOutline() to draw star outline.
		glLoadIdentity();
		drawStarText();
	}
	glLoadIdentity();
	glRotatef(rotateShapes, 0, 0, 1);
	drawStar(starCenterX, starCenterY, n / 2); // Call function drawStar() to draw green star shape.
	glLoadIdentity();

	drawRing(ringCenterX, ringCenterY); // Call function drawStar() to draw grey ring shape.

	glutSwapBuffers();
}

// menuFunc will allow the user to alter the color of the shape they have selected.
void menuFunc(int id) {
	if (id == 1) { // If the purple option is selected from the menu.
		// Change color to purple depending on the selected shape.
		if (menuChangesTriangle) {
			triangleRed = 1.0;
			triangleGreen = 0.0;
			triangleBlue = 1.0;
		}
		else if (menuChangesCross) {
			crossRed = 1.0;
			crossGreen = 0.0;
			crossBlue = 1.0;
		}
		else if (menuChangesDiamond) {
			diamondRed = 1.0;
			diamondGreen = 0.0;
			diamondBlue = 1.0;
		}
		else if (menuChangesStar) {
			starRed = 1.0;
			starGreen = 0.0;
			starBlue = 1.0;
		}
	}
	else if (id == 2) { // If the orange option is selected from the menu.
	 // Change color to orange depending on the selected shape.
		if (menuChangesTriangle) {
			triangleRed = 1.0;
			triangleGreen = 0.5;
			triangleBlue = 0.0;
		}
		else if (menuChangesCross) {
			crossRed = 1.0;
			crossGreen = 0.5;
			crossBlue = 0.0;
		}
		else if (menuChangesDiamond) {
			diamondRed = 1.0;
			diamondGreen = 0.5;
			diamondBlue = 0.0;
		}
		else if (menuChangesStar) {
			starRed = 1.0;
			starGreen = 0.5;
			starBlue = 0.0;
		}
	}
	else if (id == 3) { // If the cyan option is selected from the menu.
	 // Change color to cyan depending on the selected shape.
		if (menuChangesTriangle) {
			triangleRed = 0.0;
			triangleGreen = 1.0;
			triangleBlue = 1.0;
		}
		else if (menuChangesCross) {
			crossRed = 0.0;
			crossGreen = 1.0;
			crossBlue = 1.0;
		}
		else if (menuChangesDiamond) {
			diamondRed = 0.0;
			diamondGreen = 1.0;
			diamondBlue = 1.0;
		}
		else if (menuChangesStar) {
			starRed = 0.0;
			starGreen = 1.0;
			starBlue = 1.0;
		}
	}
	else if (id == 4) { // If the pink option is selected from the menu.
	 // Change color to pink depending on the selected shape.
		if (menuChangesTriangle) {
			triangleRed = 1.0;
			triangleGreen = 0.75;
			triangleBlue = 1.0;
		}
		else if (menuChangesCross) {
			crossRed = 1.0;
			crossGreen = 0.75;
			crossBlue = 1.0;
		}
		else if (menuChangesDiamond) {
			diamondRed = 1.0;
			diamondGreen = 0.75;
			diamondBlue = 1.0;
		}
		else if (menuChangesStar) {
			starRed = 1.0;
			starGreen = 0.75;
			starBlue = 1.0;
		}
	}

	//After making changes on objects we can call print new scene
	glutPostRedisplay();
}

// makeMenu will create the menu along wiht its four menu entries of purple, orange, cyan and pink
void makeMenu(void) {
	glutCreateMenu(menuFunc);
	glutAddMenuEntry("Purple", 1);
	glutAddMenuEntry("Orange", 2);
	glutAddMenuEntry("Cyan", 3);
	glutAddMenuEntry("Pink", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button.
}

// motionFunc will keep track of the mouse position and determine which shape the menu will be attached to.
void motionFunc(int x, int y) {
	mouseX = x - 250;
	mouseY = 250 - y;

	if (rotateShapes == 0 || rotateShapes == 360) {
		if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // If mouse is in the area of the triangle.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = true;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the cross.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = true;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // If mouse is in the area of the diamond.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = true;
			menuChangesStar = false;
		}
		else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the star.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = true;
		}
		else {
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	else if (rotateShapes == 90) {
		if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // If mouse is in the area of the cross.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = true;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the diamond.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = true;
			menuChangesStar = false;
		}
		else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // If mouse is in the area of the star.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = true;
		}
		else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the triangle.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = true;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else {
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	else if (rotateShapes == 180) {
		if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // If mouse is in the area of the diamond.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = true;
			menuChangesStar = false;
		}
		else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the star.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = true;
		}
		else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // If mouse is in the area of the triangle.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = true;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the cross.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = true;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else {
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	else if (rotateShapes == 270) {
		if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // If mouse is in the area of the star.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = true;
		}
		else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the triangle.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = true;
			menuChangesCross = false;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // If mouse is in the area of the cross.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = true;
			menuChangesDiamond = false;
			menuChangesStar = false;
		}
		else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // If mouse is in the area of the diamond.
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			menuChangesTriangle = false;
			menuChangesCross = false;
			menuChangesDiamond = true;
			menuChangesStar = false;
		}
		else {
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
}

// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	makeMenu();
}

// OpenGL window reshape routine.
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Function to handle mouse input and determine which shape will be highlighted.
void mouseFunction(int button, int state, int x, int y) {
	mouseX = x - 250;
	mouseY = 250 - y;

	// Check if the mosue is clicked.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Check if the shapes are at starting position.
		if (rotateShapes == 0 || rotateShapes == 360) {
			if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // Detect if mouse is in area of triangle.
				highlightTriangle = true;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of cross.
				highlightTriangle = false;
				highlightCross = true;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // Detect if mouse is in area of diamond.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = true;
				highlightStar = false;
			}
			else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of star.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = true;
			}
			else { // If mouse is not in area of any shape and mouse is clicked, deselect any highlighted objects.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			// Check if the shapes have been rotated counter clockwise by 90 degrees from starting position.
		}
		else if (rotateShapes == 90) {
			if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // Detect if mouse is in area of cross.
				highlightTriangle = false;
				highlightCross = true;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of diamond.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = true;
				highlightStar = false;
			}
			else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // Detect if mouse is in area of star.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = true;
			}
			else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of triangle.
				highlightTriangle = true;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			else { // If mouse is not in area of any shape and mouse is clicked, deselect any highlighted objects.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			// Check if the shapes have been rotated counter clockwise by 180 degrees from starting position.
		}
		else if (rotateShapes == 180) {
			if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // Detect if mouse is in area of diamond.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = true;
				highlightStar = false;
			}
			else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of star.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = true;
			}
			else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // Detect if mouse is in area of triangle.
				highlightTriangle = true;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of cross.
				highlightTriangle = false;
				highlightCross = true;
				highlightDiamond = false;
				highlightStar = false;
			}
			else { // If mouse is not in area of any shape and mouse is clicked, deselect any highlighted objects.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			// Check if the shapes have been rotated counter clockwise by 270 degrees from starting position.
		}
		else if (rotateShapes == 270) {
			if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= 100.0 && mouseY <= 150.0) { // Detect if mouse is in area of star.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = true;
			}
			else if (mouseX >= 100.0 && mouseX <= 150.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of triangle.
				highlightTriangle = true;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= -25.0 && mouseX <= 25.0 && mouseY >= -150.0 && mouseY <= -100.0) { // Detect if mouse is in area of cross.
				highlightTriangle = false;
				highlightCross = true;
				highlightDiamond = false;
				highlightStar = false;
			}
			else if (mouseX >= -150.0 && mouseX <= -100.0 && mouseY >= -25.0 && mouseY <= 25.0) { // Detect if mouse is in area of diamond.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = true;
				highlightStar = false;
			}
			else { // If mouse is not in area of any shape and mouse is clicked, deselect any highlighted objects.
				highlightTriangle = false;
				highlightCross = false;
				highlightDiamond = false;
				highlightStar = false;
			}
		}
	}
	glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 114:
		shouldRotateShapes = true;
		break;
	case 82:
		shouldRotateShapes = true;
		break;
	case ' ':
		randomNumber = (rand() % 15) + 3;
		if (shouldPause) {
			shouldPause = false; // Set boolean shouldPause to false to allow arrow to rotate.
			gameHasStarted = true; // Set boolean gameHasStarted to true to avoid default win at 0 degrees of rot.
			stoppedAtTriangle = false;
			stoppedAtCross = false;
			stoppedAtDiamond = false;
			stoppedAtStar = false;
		}
		break;
	default:
		break;
	}
}

// Timer function updates at a rate of 30 fps and chnages the value of rotation for both the arrow and the shapes.
void timerFunc(int value) {
	// These code blocks control the clockwise rotation of the arrow.
	if (rotationCounter == randomNumber) {
		shouldPause = true;
	}

	if (!shouldPause) {
		rot += 5;
	}
	else if (shouldPause) {
		rotationCounter = 0;
	}

	// If shapes are at starting position.
	if (rotateShapes == 0 || rotateShapes == 360) {
		if (rot == 90) {
			if (shouldPause) {
				stoppedAtCross = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 180) {
			if (shouldPause) {
				stoppedAtDiamond = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 270) {
			if (shouldPause) {
				stoppedAtStar = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 360) {
			rotationCounter += 1;
			rot = 0;
		}
		else if (rot == 0 && gameHasStarted && shouldPause) {
			stoppedAtTriangle = true;
		}
		// If shapes have rotated 90 degrees counter clockwise from starting position.
	}
	else if (rotateShapes == 90) {
		if (rot == 90) {
			if (shouldPause) {
				stoppedAtDiamond = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 180) {
			if (shouldPause) {
				stoppedAtStar = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 270) {
			if (shouldPause) {
				stoppedAtTriangle = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 360) {
			rotationCounter += 1;
			rot = 0;
		}
		else if (rot == 0 && gameHasStarted && shouldPause) {
			stoppedAtCross = true;
		}
		// If shapes have rotated 180 degrees counter clockwise from starting position.
	}
	else if (rotateShapes == 180) {
		if (rot == 90) {
			if (shouldPause) {
				stoppedAtStar = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 180) {
			if (shouldPause) {
				stoppedAtTriangle = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 270) {
			if (shouldPause) {
				stoppedAtCross = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 360) {
			rotationCounter += 1;
			rot = 0;
		}
		else if (rot == 0 && gameHasStarted && shouldPause) {
			stoppedAtDiamond = true;
		}
		// If shapes have rotated 270 degrees counter clockwise from starting position.
	}
	else if (rotateShapes == 270) {
		if (rot == 90) {
			if (shouldPause) {
				stoppedAtTriangle = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 180) {
			if (shouldPause) {
				stoppedAtCross = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 270) {
			if (shouldPause) {
				stoppedAtDiamond = true;
			}
			rotationCounter += 1;
		}
		else if (rot == 360) {
			rotationCounter += 1;
			rot = 0;
		}
		else if (rot == 0 && gameHasStarted && shouldPause) {
			stoppedAtStar = true;
		}
	}

	// This code block controls the counter-clockwise rotation of the shapes.
	if (shouldRotateShapes) {
		rotateShapes += (5.0 / 2.0);
		if (rotateShapes == 90) {
			shouldRotateShapes = false;
		}
		else if (rotateShapes == 180) {
			shouldRotateShapes = false;
		}
		else if (rotateShapes == 270) {
			shouldRotateShapes = false;
		}
		else if (rotateShapes == 360) {
			shouldRotateShapes = false;
			rotateShapes = 0;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}

// Main function of program.
int main(int argc, char** argv) {
	srand(time(NULL));

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3); // OpenGL version 4.3
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // Allows use of older versions.

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(500, 500); // Window 500px x 500px
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HW3.cpp");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMouseFunc(mouseFunction);
	glutKeyboardFunc(keyInput);

	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);
	glutPassiveMotionFunc(motionFunc);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}