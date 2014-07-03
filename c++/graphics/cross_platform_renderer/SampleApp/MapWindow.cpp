#include "stdafx.h"
#include "MapWindow.h"
#include "FWOpenGLDevice.h"

MapWindow::MapWindow(int width, int height) : 
    FWWindow(width, height),
    resize(true),
    rotate(0),
    theta(0)
{
}

void MapWindow::InputHandler(FWEvent * /*event*/)
{
}

int MapWindow::TimerHandler(unsigned int /*timer*/)
{
    Draw();
    return 0;
}

void MapWindow::Draw()
{   
    BeginDraw();
    if (resize)
    {
        glViewport(0, 0, clientWidth, clientHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (clientHeight == 0)
            clientHeight = 1;
        gluPerspective(60, clientWidth/clientHeight, 1, 100);
        resize = false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glPushMatrix();
    glRotatef( theta, 0.0f, 0.0f, 1.0f );
    glBegin( GL_TRIANGLES );
    glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
    glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
    glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
    glEnd();
    glPopMatrix();

    theta++;
    EndDraw();
}

void MapWindow::ReDraw(int width, int height)
{
    Resize(width, height);
}

void MapWindow::Resize(int width, int height)
{
    resize = true;
    clientWidth = width;
    clientHeight = height;
}
