#include <string.h>
#include <GL/glut.h>

void *font = GLUT_STROKE_ROMAN;
void *fonts[] = {GLUT_STROKE_ROMAN, GLUT_STROKE_MONO_ROMAN};
char defaultMessage[] = "Taposhi";
char *message = defaultMessage;

float angle = 0;

void selectFont(int newfont)
{
  font = fonts[newfont];
  glutPostRedisplay();
}

void selectMessage(int oneORtwo)
{
  switch (oneORtwo) {
  case 1:
    //char a[]= tolower(int ch);
    message = "taposhi";
    break;
  case 2:
    message = "TAPOSHI";
    break;
  }
}

void tick(void)
{
  angle += .2;
  glutPostRedisplay();
}

void display(void)
{
  int len, i;

  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(angle, 0.0, 0.0, 1.0);
  glTranslatef(200, 100, 0);
  glScalef(2,2,2);

  len = (int) strlen(message);
  for (i = 0; i < len; i++) {
    glutStrokeCharacter(font, message[i]);
  }
  glPopMatrix();
  glutSwapBuffers();
}

int
main(int argc, char **argv)
{
  int i, submenu;

  glutInit(&argc, argv);
  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-mono")) {
      font = GLUT_STROKE_MONO_ROMAN;
    }
  }
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("anti-aliased stroke font");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 2000, 0, 2000);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(3.0);
  glTranslatef(1000, 1000, 0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(0.0f, 1.0f, 0.0f);
  glutDisplayFunc(display);
  glutIdleFunc(tick);
  submenu = glutCreateMenu(selectMessage);
  glutAddMenuEntry("abc", 1);
  glutAddMenuEntry("ABC", 2);
  glutCreateMenu(selectFont);
  glutAddMenuEntry("Roman", 0);
  glutAddMenuEntry("Mono Roman", 1);
  glutAddSubMenu("Messages", submenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
