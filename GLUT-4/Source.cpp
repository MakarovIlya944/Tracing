//#pragma comment( linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Tracer.h"
#include "Camera.h"

GLint Width = 960, Height = 540;
GLdouble aspect = (double)Width / (double)Height, N = 0.1, theta = 90;

vertex l(2.3, 6, 2);
vertex e(0, 0, 1), d(1000, 0, 0);

Tracer a;
Camera cam1;

bool isLight = false, isLeftDown = false, isTrace = true;

//sphere, conus, thetra, plane
//shape_type, position, radius, color
void Input(char *file_obj, char *file_cam, char *file_lig, char *file_scene)
{
	ifstream in;
	in.open(file_obj);
	GemObject o;
	Light L;
	int n;
	vertex v;
	double r;
	color c;
	Conus _c;
	in >> n;
	for (int i(0), N(n); i < N; i++)
	{
		in >> n;
		in >> v;
		in >> c;
		in >> r;
		if (n < 0)
			continue;

		o.curType = (shape_type)n;
		o.Position = v;
		o.Color = c;
		o.R = r;
		if ((shape_type)n == conus)
		{
			in >> r;
			o.H = r;
		}
		in >> r;
		o.refl = r;
		in >> r;
		o.s = r;
		a.SceneObj.push_back(o);
	}

	in.close();

	in.open(file_cam);
	in >> e;
	in >> d;
	in >> v;
	cam1.LookAt(e, d, v);
	in.close();
	 
	in.open(file_lig);

	in >> n;
	for (int i(0),_n(n); i < _n; i++)
	{
		in >> n;
		in >> v;
		in >> r;
		L.type = (light_type)n;
		L.direcion = v;
		L.intensity = r;
		a.SceneLight.push_back(L);
	}
	in.close();

	in.open(file_scene);
	in >> Width >> Height >> N >> theta >> a.maxLevel;
	in.close();
}

void Init()
{
	Input("objects.txt","camera.txt","light.txt","Scene.txt");
	a.Init(e, cam1.u, cam1.w, cam1.v, Width, Height, theta, N);

	glClearColor(1, 1, 1, 1);
	glViewport(0, 0, Width, Height);
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	if (isTrace)
	{
		glDisable(GL_LIGHTING);
		gluOrtho2D(0, Width, 0, Height);
	}
	else
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		gluPerspective(theta, aspect, N, 100);
		glEnable(GL_DEPTH_TEST);
	}
	glMatrixMode(GL_MODELVIEW);
}

void Net(int kx, int ky)
{
	double beg_x = -25, end_x = 15, beg_y = -20, end_y = 20;
	double dx = (end_x - beg_x) / kx, dy = (end_y - beg_y) / ky;
	glColor3f(0, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, new float[4]{ 0, 0, 0, 0 });
	glBegin(GL_LINES);
	for (int i = 0; i <= kx; i++)
	{
		glVertex3d(beg_x + i * dx,0, beg_y);
		glVertex3d(beg_x + i * dx,0, end_y);
	}
	for (int i = 0; i <= ky; i++)
	{
		glVertex3d(beg_x,0, beg_y + i * dy);
		glVertex3d(end_x,0, beg_y + i * dy);
	}
	glEnd();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	char title_load[26] = "Трассировка в процессе...", title_ready[23] = "Трассировка закончена!";

	if (isTrace)
	{
		glutSetWindowTitle(title_load);
		a.Trace();
		glutSetWindowTitle(title_ready);
		printf_s("e:%.1lf %.1lf %.1lf \n", e.x, e.y, e.z);
		printf_s("l:%.1lf %.1lf %.1lf \n\n", l.x, l.y, l.z);
	}
	
	
	glutSwapBuffers();
}

void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;
	glViewport(0, 0, Width, Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (isTrace)
	{
		glDisable(GL_LIGHTING);
		gluOrtho2D(0, Width, 0, Height);
	}
	else
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		gluPerspective(theta, aspect, N, 100);
		glEnable(GL_DEPTH_TEST);
	}
	glMatrixMode(GL_MODELVIEW);
	a.Init(e, cam1.u, cam1.w, cam1.v, Width, Height, theta, N);
}

void Keyboard(GLubyte key, GLint x, GLint y)
{
	switch (key)
	{
	case 'i':
		a.SceneLight.clear();
		a.SceneObj.clear();
		Init();
		glutReshapeWindow(Width, Height);
		Reshape(Width, Height);
		glutPostRedisplay();
		break;
	case 'z':
		if (isTrace)
			isTrace = false;
		else
			isTrace = true;
		Reshape(Width, Height);
		break;
	case 'w':
		l.x++;
		break;
	case 'a':
		l.y--;
		break;
	case 'd':
		l.y++;
		break;
	case 's':
		l.x--;
		break;
	case 'q':
		l.z--;
		break;
	case 'e':
		l.z++;
		break;

	case 't':
		e.x++;
		d.x++;
		break;
	case 'f':
		e.y--;
		d.y--;
		break;
	case 'h':
		e.y++;
		d.y++;
		break;
	case 'g':
		e.x--;
		d.x--;
		break;
	case 'y':
		e.z--;
		d.z--;
		break;
	case 'r':
		e.z++;
		d.z++;
		break;
	default:
		break;
	}
	//a.LightPosition = l;
	a.Init(e, cam1.u, cam1.w, cam1.v, Width, Height, theta, N);
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Лабараторная 4");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}