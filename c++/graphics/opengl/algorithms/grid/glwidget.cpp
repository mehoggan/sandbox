#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, QGLWidget *glparent) :
    QGLWidget(parent, glparent),
    texture_ids_(NULL),
    col_(30),
    row_(30),
    step_(16.0)
{
    texture_ids_ = new GLuint[row_ * col_];
}

GLWidget::~GLWidget()
{
    if (texture_ids_) {
        glDeleteTextures(row_ * col_, texture_ids_);
    }
}

void GLWidget::resizeEvent(QResizeEvent * /*event*/) {
    initGL();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width(), height());
    glOrtho(0, width(), 0, height(), -1, 1);
}

void GLWidget::initGL()
{
    makeCurrent();
    // Variables for vertices
    vertices_.clear();
    int32_t start_y = step_;
    int32_t start_x = step_;

    // Varaibles for indices
    indices_.clear();
    int32_t vertices_per_row = col_ + 1;
    int32_t vertex_num = 0;

    for (int32_t j = 0; j <= row_; ++j) {
        // Generate Vertices on row j
        for (int32_t i = 0; i <= col_; ++i) {
            vertices_.push_back(Vertex<GLfloat>((start_x + (i * step_)),
                (start_y + (j * step_)), 0.0f));
        }

        if (j == row_) {
            break;
        }

        // Generate Indices to get right vertices for traingle
        for (int32_t i = 0; i < col_; ++i) {
            indices_.push_back(Indices<GLuint>(vertex_num, (vertex_num + 1), 
                (vertex_num + vertices_per_row)));

            indices_.push_back(Indices<GLuint>((vertex_num + 1), 
                (vertex_num + vertices_per_row), 
                (vertex_num + vertices_per_row + 1)));

            vertex_num++;
        }
        vertex_num++;
    }
}


void GLWidget::textureInit()
{
    makeCurrent();
    for (int32_t i = 0; i < row_ * col_; ++i) {
        QImage tmpQImage(step_, step_, QImage::Format_ARGB32);
        tmpQImage = QGLWidget::convertToGLFormat(tmpQImage);

        QPainter tmpQPainter;
        tmpQPainter.begin(&tmpQImage);
            tmpQPainter.fillRect(QRect(0, 0, width(), height()),
                QColor(255, 0, 0));
            tmpQPainter.setRenderHint(QPainter::Antialiasing, true);
        tmpQPainter.end();

        glGenTextures(1, &texture_ids_[i]);
        glBindTexture(GL_TEXTURE_2D, texture_ids_[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmpQImage.width(),
            tmpQImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
            tmpQImage.bits());
    }
}

void GLWidget::updateGL() {
    if (first_render_) {
        textureInit();
        first_render_ = false;
    }

    glMatrixMode(GL_MODELVIEW);
    glScissor(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices_.data());
    glDrawElements(GL_TRIANGLES, indices_.size() * 3, GL_UNSIGNED_INT,
        indices_.data());
    glDisableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
