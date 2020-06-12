#include <GL/freeglut.h>
#include <math.h>

float grow_shrink = 70.0;
float resize_f = 1.0;

float rotate_x = 0, rotate_y = 0, rotate_z = 0;
float translate_x = 0, translate_y = 0, translate_z = 0;

void drawSphere(float r) {
	float center_x = 0, center_y = 0, center_z = 0;
	float increment = 0.1;

	// draw the sphere
	glBegin(GL_QUADS);
	for (float angle1 = 0; angle1 < 2 * M_PI; angle1 += increment) {
		for (float angle2 = 0; angle2 < M_PI; angle2 += increment) {
			//glColor3f(angle1 / (2 * M_PI), angle2 / (M_PI), (angle1 / (2 * M_PI) + angle2 / ( M_PI)) / 2);
			glColor3f(0.4,0.7,0.6);
			glVertex3f(center_x + r * cos(angle1) * sin(angle2),
					center_y + r * cos(angle2),
					center_z + r * sin(angle1) * sin(angle2));
			glVertex3f(center_x + r * cos(angle1) * sin(angle2 + increment),
					center_y + r * cos(angle2 + increment),
					center_z + r * sin(angle1) * sin(angle2 + increment));
			glVertex3f(
					center_x
							+ r * cos(angle1 + increment)
									* sin(angle2 + increment),
					center_y + r * cos(angle2 + increment),
					center_z
							+ r * sin(angle1 + increment)
									* sin(angle2 + increment));
			glVertex3f(center_x + r * cos(angle1 + increment) * sin(angle2),
					center_y + r * cos(angle2),
					center_z + r * sin(angle1 + increment) * sin(angle2));
		}
	}

	glEnd();
}

int myScene;

int init(void) {
	myScene = glGenLists(1);
	glNewList(myScene, GL_COMPILE);
	//drawSphere(1);
	glEndList();

	glClearColor(0.93, 0.93, 0.93, 0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	return 1;
}

void drawCube() {
	glBegin(GL_QUADS);

	// FRONT
	glColor3f(1, 0.0f, 0.0f);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);

	// BACK
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	// LEFT
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);

	// RIGHT
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);

	// TOP
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// BOTTOM
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	static float th = 0;
	th++;
	gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glRotatef(th, 1, 0, 0);

	// top
	glPushMatrix();
	glScalef(1, 0.05, 1);
	drawCube();
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(-1, -1, -1);
	glScalef(0.05, 1, 0.05);
	drawCube();
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(-1, -1, 1);
	glScalef(0.05, 1, 0.05);
	drawCube();
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(1, -1, -1);
	glScalef(0.05, 1, 0.05);
	drawCube();
	glPopMatrix();

	// leg
	glPushMatrix();
	glTranslatef(1, -1, 1);
	glScalef(0.05, 1, 0.05);
	drawCube();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0.7, 0);
	glScalef(0.03, 0.85, 0.03);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.7, 0);
	glScalef(0.2, 0.7, 0.3);
	drawSphere(1);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(grow_shrink, resize_f * w / h, resize_f, 100 * resize_f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glutTimer(int value) {
	glutPostRedisplay();
	glutTimerFunc(20, glutTimer, 1);
}

void special(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		translate_z += 0.1;
	else if (key == GLUT_KEY_DOWN)
		translate_z -= 0.1;
	else if (key == GLUT_KEY_RIGHT)
		rotate_y += 1;
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 1;
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W')
		rotate_x += 1;
	else if (key == 's' || key == 'S')
		rotate_x -= 1;
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutCreateWindow("Table and Sphere");

	glutTimerFunc(20, glutTimer, 1);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();

	return 0;
}
