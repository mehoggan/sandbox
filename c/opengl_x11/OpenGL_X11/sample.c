#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct device {
	Display                 *display;
	Window                  root;
	GLint                   attributes[5];
	XVisualInfo             *vi;
	Colormap                cmap;
	XSetWindowAttributes    swa;
	Window                  window;
	GLXContext              glc;
	XWindowAttributes       gwa;
	XEvent                  xev;
} DEVICE;

pthread_t		_thread;

void DrawAQuad() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1., 1., -1., 1., 1., 20.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
    glBegin(GL_QUADS);
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
    glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
    glEnd(); 
} 

void* render_thread( void *_id ) {
    fprintf(stderr, "Render Thread Called");
    DEVICE device;
    device.attributes[0] = GLX_RGBA;
    device.attributes[1] = GLX_DEPTH_SIZE;
    device.attributes[2] =  24;
    device.attributes[3] = GLX_DOUBLEBUFFER;
    device.attributes[4] = None;
    device.display = XOpenDisplay(NULL);
    if(device.display == NULL) {
        fprintf(stderr,"\n\tcannot connect to X server\n\n");
        exit(0); 
    }
    device.root = DefaultRootWindow(device.display);
    device.vi = glXChooseVisual(device.display, 0, device.attributes);
    if(device.vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        exit(0); 
    } else {
        printf("\n\tvisual %p selected\n", (void *)device.vi->visualid);/* %p creates hexadecimal output like in glxinfo */
        device.cmap = XCreateColormap(device.display, device.root, device.vi->visual, AllocNone);
        device.swa.colormap = device.cmap;
        device.swa.event_mask = ExposureMask | KeyPressMask;
        device.window = XCreateWindow(device.display, device.root, 0, 0, 600, 600, 0, device.vi->depth, 
                                    InputOutput, device.vi->visual, CWColormap | CWEventMask, &(device.swa));
        XMapWindow(device.display, device.window);
        XStoreName(device.display, device.window, "VERY SIMPLE APPLICATION");
        device.glc = glXCreateContext(device.display, device.vi, NULL, GL_TRUE);
        glXMakeCurrent(device.display, device.window, device.glc);
        glEnable(GL_DEPTH_TEST); 
	
        while(1) {
            XNextEvent(device.display, &(device.xev));
            if(device.xev.type == Expose) {
                XGetWindowAttributes(device.display, device.window, &(device.gwa));
                glViewport(0, 0, device.gwa.width, device.gwa.height);
                DrawAQuad(); 
                glXSwapBuffers(device.display, device.window);
            } else if(device.xev.type == KeyPress) {
                glXMakeCurrent(device.display, None, NULL);
                glXDestroyContext(device.display, device.glc);
                XDestroyWindow(device.display, device.window);
                XCloseDisplay(device.display);
                pthread_exit(NULL);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    unsigned int junk;
    int thread_id = pthread_create(&_thread, NULL, render_thread, (void*)junk);
    while( 1 ) { ;}
    fprintf(stderr,"Good Bye");
} 

