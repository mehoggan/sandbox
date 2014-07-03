#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLContext>
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPainter>

#include <iostream>
#include <vector>
#include <stdint.h>

#include "openglprimitives.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

private:
    GLuint *texture_ids_;
    int32_t col_;
    int32_t row_;
    GLfloat step_;
    bool first_render_;

    std::vector<Vertex<GLfloat> > vertices_;
    std::vector<Indices<GLuint> > indices_;
    std::vector<TexCoord<GLfloat> > texture_coords_;

    void initGL();
    void textureInit();

protected:
    void resizeEvent(QResizeEvent *);

public:
    explicit GLWidget(QWidget *parent = 0, QGLWidget *glparent = 0);
    ~GLWidget();

public slots:
    void updateGL();
    
};

#endif // GLWIDGET_H
