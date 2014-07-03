#ifndef OPENGLPRIMITIVES_H
#define OPENGLPRIMITIVES_H

#include <QtOpenGL>

template <typename type>
class Vertex;
template <>
struct Vertex<GLfloat> {
    GLfloat x_;
    GLfloat y_;
    GLfloat z_;
    Vertex(GLfloat x, GLfloat y, GLfloat z) :
        x_(x), y_(y), z_(z)
    {}
};

template <typename type>
class Normal;
template<>
struct Normal<GLfloat> {
    GLfloat nx_;
    GLfloat ny_;
    GLfloat nz_;
    Normal(GLfloat nx, GLfloat ny, GLfloat nz) :
        nx_(nx), ny_(ny), nz_(nz)
    {}
};

template <typename type>
class Indices;
template<>
struct Indices<GLuint> {
    GLuint index1_;
    GLuint index2_;
    GLuint index3_;
    Indices(GLuint index1, GLuint index2, GLuint index3) :
        index1_(index1), index2_(index2), index3_(index3)
    {}
};

template <typename type>
class TexCoord;
template<>
struct TexCoord<GLfloat> {
    GLfloat s_;
    GLfloat t_;
    TexCoord(GLfloat s, GLfloat t) :
        s_(s), t_(t)
    {}
};

#endif // OPENGLPRIMITIVES_H
