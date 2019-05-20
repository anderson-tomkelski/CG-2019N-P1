#include <GL/glut.h>
#include <GL/gl.h>

// Rotate Y
GLfloat rY = 0;
// Rotate Z
GLfloat rZ = 0;
// Rotate Z in screen
GLfloat rrZ = 0;

const float FRAMES_PER_SECOND = 30;
const float UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

class Cube {
public:
	float x, y, z, r, g, b;

	Cube(){}

	Cube(float x, float y, float z, float r, float g, float b){
		this->x = x;
		this->y = y;
		this->z = z;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	void draw(){
		//Back
		glColor3f(this->r, this->g, this->b);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y * - 1, this->z);
			glVertex3f(this->x * - 1, this->y, this->z);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y * - 1, this->z);
			glVertex3f(this->x, this->y * - 1, this->z);
			glVertex3f(this->x * - 1, this->y, this->z);
		glEnd();

		// Front
		glColor3f(this->r - 0.3, this->g + 0.2, this->b - 0.2);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y * - 1, this->z * - 1);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
			glVertex3f(this->x, this->y * - 1, this->z * - 1);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y, this->z * - 1);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
			glVertex3f(this->x, this->y * - 1, this->z * - 1);
		glEnd();

		// left
		glColor3f(this->r - 0.1, this->g + 0.2, this->b + 0.1);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y * - 1, this->z * - 1);
			glVertex3f(this->x * - 1, this->y * - 1, this->z);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y, this->z);
			glVertex3f(this->x * - 1, this->y * - 1, this->z);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
		glEnd();

		// Right
		glColor3f(this->r - 0.2, this->g - 0.1, this->b - 0.3);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y, this->z * - 1);
			glVertex3f(this->x, this->y * - 1, this->z);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y * - 1, this->z * - 1);
			glVertex3f(this->x, this->y, this->z * - 1);
			glVertex3f(this->x, this->y * - 1, this->z);
		glEnd();

		// Top
		glColor3f(this->r + 0.2, this->g - 0.3, this->b - 0.5);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x, this->y, this->z * - 1);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y, this->z);
			glVertex3f(this->x, this->y, this->z);
			glVertex3f(this->x * - 1, this->y, this->z * - 1);
		glEnd();

		// Bottom
		glColor3f(this->r, this->g - 0.3, this->b - 0.1);
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x * - 1, this->y * - 1, this->z * - 1);
			glVertex3f(this->x * - 1, this->y * - 1, this->z);
			glVertex3f(this->x, this->y * - 1, this->z);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(this->x, this->y * - 1, this->z * - 1);
			glVertex3f(this->x * - 1, this->y * - 1, this->z * - 1);
			glVertex3f(this->x, this->y * - 1, this->z);
		glEnd();
	}
};

Cube cubes[2];

void display()
{
	// Set Background Color
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	// Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glPushMatrix();
		glRotatef(rY, 0.0f, 1.0f, 0.0f);	
		cubes[0].draw();
	glPopMatrix();

	glPushMatrix();
		glRotatef(rrZ, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.5, 0.5, 0.5);
		glRotatef(rZ, 1.0f, 1.0f, 0.0f);
		cubes[1].draw();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void update(int value)
{
	rY -= 5;
	rZ -= 5;
	rrZ += 5;
	glutPostRedisplay();
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}


int main(int argc, char **argv)
{
	// Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	cubes[0] = Cube(0.1, 0.1, 0.1, 0.4, 0.3, 0.5);
	cubes[1] = Cube(0.1, 0.1, 0.1, 0.8, 0.7, 0.9);

	// Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);

	// Create window
	glutCreateWindow("OpenGL Cube");

	// Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);

	// Pass control to GLUT for events
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
	glutMainLoop();

	return 0;
}