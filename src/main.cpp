#include	<GL/glut.h>
#include	<math.h>
#include <iostream>
#include "Tools/structs.h"
#include "Tools/objectfileparser.h"
objectStruct cube;

GLfloat vertices2[]={1.0f,-1.0f,-1.0f,
                     1.0f, -1.0f,1.0f,
                     -1.0f,-1.0f,1.0f,
                     -1.0f,-1.0f,-1.0f,
                     1.0f,1.0f,-0.99f,
                     0.99f, 1.0f, 1.01f,
                     -1.00f, 1.0f, 1.0f,
                     -1.0f,1.0f,-1.0f

};

GLfloat colors2[]   = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,
                        1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,
                        1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,
                        1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,
                        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
                        0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 };

GLushort indices[] = {1,2,3,
    1,3,4,
    5,8,7,
    5,7,6,
    1,5,6,
    1,6,2,
    2,6,7,
    2,7,3,
    3,7,8,
    3,8,4,
    5,1,4,
    5,4,8};

void DisplayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0, 0, -10);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors2);
    glVertexPointer(3, GL_FLOAT, 0, cube.vertices.data());

    glPushMatrix();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, cube.faces.data());

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glFlush();
    glutSwapBuffers();

    glutPostRedisplay();
}

void ReshapeFunc(int width, int height)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60, width / (float) height, 5, 15);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    if ('q' == key || 'Q' == key || 27 == key)
        exit(0);
}


int	main(int argc, char **argv)
{
    ObjectFileParser parser;
    cube = parser.ParseObjFile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL exercise");


    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(&DisplayFunc);
    glutReshapeFunc(&ReshapeFunc);
    glutKeyboardFunc(&KeyboardFunc);

    glutMainLoop();

    return 0;
}
