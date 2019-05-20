#include <GL/glut.h>
#include <GL/gl.h>

// Rotate X
GLfloat rX = 0;
// Rotate Y
GLfloat rY = 0;

class Cube {
public:
	float x, y, z;

	Cube(){}

	Cube(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	void draw(){
		//Back
		glColor3f(0.4f, 0.3f, 0.5f);
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

	// Rotate when user changes rX and rY
	glRotatef(rX, 1.0f, 0.0f, 0.0f);
	glRotatef(rY, 0.0f, 1.0f, 0.0f);

	glColor3f(0.4f, 0.3f, 0.5f);
	cubes[0].draw();

	glFlush();
	glutSwapBuffers();
}

void keyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT) {
		rY += 5;
	} else if (key == GLUT_KEY_LEFT) {
		rY -= 5;
	} else if (key == GLUT_KEY_DOWN) {
		rX -= 5;
	} else if (key == GLUT_KEY_UP) {
		rX += 5;
	}

	// Request display update
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	// Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	cubes[0] = Cube(0.3, 0.3, 0.3);

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
	glutSpecialFunc(keyboard);

	// Pass control to GLUT for events
	glutMainLoop();

	return 0;
}