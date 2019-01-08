#include "Angel.h"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <vector>
#define DEG2RAD (3.14159265)/180
float mouseX, mouseY;
class particle
{
public:
	vec2 pos;
	vec2 speed;
	float lifetime;
	particle()
	{
		int dirx, diry;
		dirx = rand() % 3;
		diry = rand() % 3;
		if (dirx == 2)
		{
			dirx = -1;
		}
		if (diry == 2)
		{
			diry = -1;
		}
		speed = { dirx*(rand() % 5 + 5) / 5000.0f,diry*(rand() % 5 + 5) / 5000.0f };
		lifetime = (rand() % 10 + 1) / 100.0;
		pos = { mouseX,mouseY };
	}

	void Move()
	{
		pos += speed;
		lifetime -= 0.0025;
		glutPostRedisplay();
	}
};

std::vector<particle> particlelist;

void Create(vec2 pos)
{
	for (int i = 0; i < particlelist.size(); i++)
	{
		glBegin(GL_POLYGON);
		float radius = 0.01f;
		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glColor3f(1, 0, 0);
			glVertex2f(pos.x + (cos(degInRad) * radius), pos.y + (sin(degInRad) * radius));
		}
		glEnd();
	}
	glFlush();
}

void ClearScreen()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display()
{
	ClearScreen();
	particle p;
	if(rand() % 2==0)
		particlelist.push_back(p);
	else
	{
		p.~particle();
	}
	for (int i = 0; i < particlelist.size(); i++)
	{
		if (particlelist[i].lifetime <= 0)
		{
			particlelist[i].~particle();
			particlelist.erase(particlelist.begin() + i);
		}
	}
	for (int i = 0; i < particlelist.size(); i++)
	{
		Create(particlelist[i].pos);
		particlelist[i].Move();
	}
}

float width = 600, height = 600;
void Mouse(int button, int state, int x, int y)
{
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	if (state == GLUT_UP)
	{
		mouseX = (x - width / 2) / (width / 2);
		mouseY = (y - height / 2) / (height / 2);
	}
}

int main(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(400, 0);
	glutCreateWindow("Particles");
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}