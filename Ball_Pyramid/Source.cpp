/*to make ball active - b
to make pyramid active - p
to make both active - u
to make bigger/smaller - shift and + or -
to move use arrows
to rotate use w/a/s/d
to change rotation mode - r*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

#define GL_BGR   0x80E0
#define pi (3.14)

#define BALL (0)
#define PYRAMID (1)
#define	BOTH (2)

#define X (0)
#define Y (1)

//size
float size_ball = 0.4;
float size_pyramid = 0.5;
//color
float color_ball[3];
float color_pyramid[3];
//position
float pos_ball[3];
float pos_pyramid[3];
//angle
int angle_ball[2];
int angle_pyramid[2];
int timer = 0;
int state = BALL;
int rotating_state = 0;

int xpos, ypos;

void init(void)
{
	pos_ball[0] = -1.0; //x
	pos_ball[1] = 0.0; //y
	pos_ball[2] = 0.0; //depth
	pos_pyramid[0] = 1.0;
	pos_pyramid[1] = 0.0;
	pos_pyramid[2] = 0.0;

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //отраженный свет
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 20.2, 20.0, 30.0, 0.0 };
	glClearColor(1, 1, 1, 1); //BACKGROUND color
	glShadeModel(GL_FLAT);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //material qualities
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL); //enabling light so we can see the objects
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void mouse(int x, int y)
{
	xpos = x;
	ypos = y;

	glutPostRedisplay();
}

void timer_func(int a)
{
	if (timer < 350) {
		timer++;
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer_func, a);
}

void drawAxes()//coordinates
{
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glPopMatrix();

	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
}

void drawBall(float size)
{
	glTranslatef(pos_ball[0], pos_ball[1], pos_ball[2]);
	glColor3f(color_ball[0], color_ball[1], color_ball[2]);
	glPushMatrix();
	glPopMatrix();

	glRotatef(angle_ball[0], 1.0, 0.0, 0.0);
	glRotatef(angle_ball[1], 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	//Ball Drawing
	glutSolidSphere(size_ball, 10, 10);
	glDisable(GL_TEXTURE_2D);
}

void drawPyramid(float size)
{
	glTranslatef(pos_pyramid[0], pos_pyramid[1], pos_pyramid[2]);
	glColor3f(color_pyramid[0], color_pyramid[1], color_pyramid[2]);
	glPushMatrix();
	glPopMatrix();

	glRotatef(angle_pyramid[0], 1.0, 0.0, 0.0);
	glRotatef(angle_pyramid[1], 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// Front
	glNormal3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	// Right
	glNormal3f(1.0*size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0*size);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	// Left
	glNormal3f(-1.0*size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5*size, 0.0f);
	glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glEnd();
	glBegin(GL_QUADS);
	//bottom
	glNormal3f(0.0f, -1.0*size, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5*size, -0.5*size, -0.5*size);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5*size, -0.5*size, -0.5*size);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.5*size, -0.5*size, 0.5*size);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5*size, -0.5*size, 0.5*size);
	glEnd();// Done

	glDisable(GL_TEXTURE_2D);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 4.0, //Specifies the position of the eye point.
		0.0, 0.0, 0.0, //Specifies the position of the reference point
		0.0, 1.0, 0.0); //Specifies the direction of the up vector.

	glScalef(1.0, 1.0, 1.0);

	drawAxes();

	//DRAWING Ball
	glPushMatrix();	//rotate to get the right perspective
	glRotatef(1.0, 3.0, 0.0, 0.0); //Specifies the angle of rotation, in degrees, x, y, z
	drawBall(size_ball);
	glPopMatrix();

	//DRAWING Pyramid
	glPushMatrix();
	//rotate to get the right perspective
	glRotatef(11.0, 3.0, 0.0, 0.0);
	drawPyramid(size_pyramid);
	glPopMatrix();

	glFlush();
}

void rotate_ball_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_ball[0] * pos_ball[0] + pos_ball[2] * pos_ball[2]);
		if (radius == 0)
		{
			angle_ball[1] += direction;
			return;
		}
		angle_x = acos(pos_ball[0] / radius);
		angle_x += direction*pi / 180;
		pos_ball[0] = radius*cos(angle_x);
		pos_ball[2] = radius*sin(angle_x);
		std::cout << pos_ball[2] << std::endl;
	}
	else
	{
		radius = sqrt(pos_ball[1] * pos_ball[1] + pos_ball[2] * pos_ball[2]);
		if (radius == 0)
		{
			angle_ball[0] += direction;
			return;
		}
		angle_y = acos(pos_ball[1] / radius);
		angle_y += direction*pi / 180;
		pos_ball[1] = radius*cos(angle_y);
		pos_ball[2] = radius*sin(angle_y);
	}
}

void rotate_pyramid_global_axes(int axis, int direction)
{
	float angle_x, angle_y, radius;
	if (axis == Y)
	{
		radius = sqrt(pos_pyramid[0] * pos_pyramid[0] + pos_pyramid[2] * pos_pyramid[2]);
		if (radius == 0)
		{
			angle_pyramid[1] += direction;
			return;
		}
		angle_x = acos(pos_pyramid[0] / radius);
		std::cout << angle_x << std::endl;
		angle_x += direction*pi / 180;
		std::cout << angle_x << std::endl;
		pos_pyramid[0] = radius*cos(angle_x);
		pos_pyramid[2] = radius*sin(angle_x);
	}
	else
	{
		radius = sqrt(pos_pyramid[1] * pos_pyramid[1] + pos_pyramid[2] * pos_pyramid[2]);
		if (radius == 0)
		{
			angle_pyramid[0] += direction;
			return;
		}
		angle_y = acos(pos_pyramid[1] / radius);
		angle_y += direction*pi / 180;
		pos_pyramid[1] = radius*cos(angle_y);
		pos_pyramid[2] = radius*sin(angle_y);
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'b': state = BALL; break;
	case 'p': state = PYRAMID; break;
	case 'u': state = BOTH; break;
	case 'r':
		if (rotating_state == 0) rotating_state = 1;
		else rotating_state = 0;
		break;
	case '+':
		switch (state)
		{
		case BALL:
			if (size_ball <= 1)
				size_ball += 0.1;
			break;
		case PYRAMID:
			if (size_pyramid <= 1)
				size_pyramid += 0.1;
			break;
		case BOTH:
			if (size_ball <= 1)
				size_ball += 0.1;
			if (size_pyramid <= 1)
				size_pyramid += 0.1;
			break;
		}
		break;
	case '-':
		switch (state)
		{
		case BALL:
			if (size_ball >= 0.2)
				size_ball -= 0.1;
			break;
		case PYRAMID:
			if (size_pyramid >= 0.2)
				size_pyramid -= 0.1;
			break;
		case BOTH:
			if (size_ball >= 0.2)
				size_ball -= 0.1;
			if (size_pyramid >= 0.2)
				size_pyramid -= 0.1;
			break;
		}
		break;
	case 'w':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case BALL: angle_ball[0]++; break;
			case PYRAMID: angle_pyramid[0]++; break;
			case BOTH: angle_ball[0]++; angle_pyramid[0]++; break;
			}
		}
		else
		{
			switch (state)
			{
			case BALL: rotate_ball_global_axes(X, 1); break;
			case PYRAMID: rotate_pyramid_global_axes(X, 1); break;
			case BOTH: rotate_ball_global_axes(X, 1); rotate_pyramid_global_axes(X, 1); break;
			}
		}
		break;
	case 's':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case BALL: angle_ball[0]--; break;
			case PYRAMID: angle_pyramid[0]--; break;
			case BOTH: angle_ball[0]--; angle_pyramid[0]--; break;
			}
		}
		else
		{
			switch (state)
			{
			case BALL: rotate_ball_global_axes(X, -1); break;
			case PYRAMID: rotate_pyramid_global_axes(X, -1); break;
			case BOTH: rotate_ball_global_axes(X, -1); rotate_pyramid_global_axes(X, -1); break;
			}
		}
		break;
	case 'd':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case BALL: angle_ball[1]++; break;
			case PYRAMID: angle_pyramid[1]++; break;
			case BOTH: angle_ball[1]++; angle_pyramid[1]++; break;
			}
		}
		else
		{
			switch (state)
			{
			case BALL: rotate_ball_global_axes(Y, 1); break;
			case PYRAMID: rotate_pyramid_global_axes(Y, 1); break;
			case BOTH: rotate_ball_global_axes(Y, 1); rotate_pyramid_global_axes(Y, 1); break;
			}
		}
		break;
	case 'a':
		if (rotating_state == 0)
		{
			switch (state)
			{
			case BALL: angle_ball[1]--; break;
			case PYRAMID: angle_pyramid[1]--; break;
			case BOTH: angle_ball[1]--; angle_pyramid[1]--; break;
			}
		}
		else
		{
			switch (state)
			{
			case BALL: rotate_ball_global_axes(Y, -1); break;
			case PYRAMID: rotate_pyramid_global_axes(Y, -1); break;
			case BOTH: rotate_ball_global_axes(Y, -1); rotate_pyramid_global_axes(Y, -1); break;
			}
		}
		break;
	//	switch (key){
		case 'f':
		{
					std:: ofstream myfile;
					myfile.open("lab.txt");
					myfile <<" x "<< pos_ball[0] <<" y "<< pos_ball[1];// << endl;
					myfile.close();
		}
	}

}

void skeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		switch (state)
		{
		case BALL: pos_ball[1] -= 0.1; break;
		case PYRAMID: pos_pyramid[1] -= 0.1; break;
		case BOTH: pos_ball[1] -= 0.1; pos_pyramid[1] -= 0.1; break;
		}
		break;
	case GLUT_KEY_UP:
		switch (state)
		{
		case BALL: pos_ball[1] += 0.1; break;
		case PYRAMID: pos_pyramid[1] += 0.1; break;
		case BOTH: pos_ball[1] += 0.1; pos_pyramid[1] += 0.1; break;
		}
		break;
	case GLUT_KEY_LEFT:
		switch (state)
		{
		case BALL: pos_ball[0] -= 0.1; break;
		case PYRAMID: pos_pyramid[0] -= 0.1; break;
		case BOTH: pos_ball[0] -= 0.1; pos_pyramid[0] -= 0.1; break;
		}
		break;
	case GLUT_KEY_RIGHT:
		switch (state)
		{
		case BALL: pos_ball[0] += 0.1; break;
		case PYRAMID: pos_pyramid[0] += 0.1; break;
		case BOTH: pos_ball[0] += 0.1; pos_pyramid[0] += 0.1; break;
		}
		break;
	}

}

void set_color()
{
	char answer = 0;
	std::cout << "Do you want to choose color? y/n\n";
	while (answer != 'y' && answer != 'n')
		std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Enter ball color: ";
		std::cin >> color_ball[0] >> color_ball[1] >> color_ball[2]; 
		std::cout << "Enter pyramid color: ";
		std::cin >> color_pyramid[0] >> color_pyramid[1] >> color_pyramid[2];
	}
	else
	{
		color_ball[0] = 0.294; color_ball[1] = 0.0; color_ball[2] = 0.510; //colors
		color_pyramid[0] = 0.0; color_pyramid[1] = 0.502; color_pyramid[2] = 0.502;
	}
}

int main(int argc, char** argv)
{
	set_color();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(skeyboard);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, timer_func, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();	
	
	return 0;
}