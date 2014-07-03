#include "ledlight.h"

LedLight::LedLight(QColor tmpCurrentColor, 
    GLfloat tmpCenterXCoord, GLfloat tmpCenterYCoord, GLfloat tmpDiameter) :
    mCurrentColor(tmpCurrentColor),
    mCenterXCoord(tmpCenterXCoord),
    mCenterYCoord(tmpCenterYCoord),
    mDiameter(tmpDiameter),
    mPi(std::atan(1.0f)*4),
    mBulbNumber(0),
    mFirstInitialRender(true) {

}

LedLight::LedLight(const LedLight &other) {
    (*this) = other;
}

LedLight &LedLight::operator=(const LedLight &other) {
    mCurrentColor = other.mCurrentColor;
    mCenterXCoord = other.mCenterXCoord;
    mCenterYCoord = other.mCenterYCoord;
    mDiameter = other.mDiameter;
    mBulbNumber = 0;
    mFirstInitialRender = true;

    return (*this);
}

LedLight::~LedLight() { 
    glDeleteLists(mBulbNumber, 1);
}

static GLfloat staticDegreesToRadians(GLfloat tmpDegrees) {
    GLfloat tmpCalc = tmpDegrees * ((std::atan(1.0f)*4)/180.0f);
    return tmpCalc;
}

void LedLight::GenerateBulbs() {
    if (mBulbNumber != 0) {
        glDeleteLists(mBulbNumber, 1);
    }
    mBulbNumber = glGenLists(1);
    glNewList(mBulbNumber, GL_COMPILE);
    const GLfloat r = mDiameter/2.0f;
    const GLfloat x = mCenterXCoord;
    const GLfloat y = mCenterYCoord;
    const GLfloat phid = 5.00f;
    const GLfloat thetad = 5.00f;

    using namespace std;
    for (int32_t phi = 180; phi > 0; phi -= static_cast<int32_t>(phid)) {
        glBegin(GL_QUAD_STRIP);
        GLfloat rphi = staticDegreesToRadians(phi);
        GLfloat rphid = staticDegreesToRadians(phid);
        for (int32_t theta = 0; theta < 360;
            theta += static_cast<int32_t>(thetad)) {

            GLfloat rtheta = staticDegreesToRadians(theta);

            GLfloat x1 = x + r*sin(rphi)*sin(rtheta);
            GLfloat y1 = y + r*cos(rphi);
            GLfloat z1 = 0 + r*sin(rphi)*cos(rtheta);

            GLfloat x2 = x + r*sin(rphi + rphid)*sin(rtheta);
            GLfloat y2 = y + r*cos(rphi + rphid);
            GLfloat z2 = 0 + r*sin(rphi + rphid)*cos(rtheta);

            glNormal3f((x1 - x)/r, (y1 - y)/r, (z1 - 0)/r);
            glVertex3f(x1, y1, z1);
            glNormal3f((x2 - x)/r, (y2 - y)/r, (z2 - 0)/r);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glEndList();
}

void LedLight::RenderContents() {
    if (mFirstInitialRender) {
        GenerateBulbs();
        mFirstInitialRender = false;
    }

    glColor3f(mCurrentColor.red()/255.0,
        mCurrentColor.green()/255.0,
        mCurrentColor.blue()/255.0);

    glShadeModel(GL_SMOOTH);
    GLfloat tmpFill[] = {mCurrentColor.red()/255.0,
        mCurrentColor.green()/255.0,
        mCurrentColor.blue()/255.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tmpFill);
    glCallList(mBulbNumber);
}

