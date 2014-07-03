#ifndef OPENGL20_H
#define OPENGL20_H

# ifdef WIN32
#   include <Windows.h>
# elif __linux__
#endif

#include <GL/gl.h>
#include <GL/glext.h>

#ifdef WIN32
# define glGetProcAddress(arg) wglGetProcAddress(arg)
#elif __linux__
# include <GL/glx.h>
# define  glGetProcAddress(arg) glXGetProcAddress((const GLubyte*)arg)
#endif

extern PFNGLBLENDFUNCSEPARATEPROC           glBlendFuncSeparate;

// GL_ARB_shader_objects
extern PFNGLCREATESHADERPROC                glCreateShader;
extern PFNGLDELETESHADERPROC                glDeleteShader;
extern PFNGLCREATEPROGRAMPROC               glCreateProgram;
extern PFNGLDELETEPROGRAMPROC               glDeleteProgram;
extern PFNGLGETSHADERIVPROC                 glGetShaderiv;
extern PFNGLATTACHSHADERPROC                glAttachShader;
extern PFNGLDETACHSHADERPROC                glDetachShader;
extern PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
extern PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC                glGetProgramiv;
extern PFNGLUSEPROGRAMPROC                  glUseProgram;
extern PFNGLSHADERSOURCEPROC                glShaderSource;
extern PFNGLCOMPILESHADERPROC               glCompileShader;
extern PFNGLLINKPROGRAMPROC                 glLinkProgram;
extern PFNGLGETUNIFORMLOCATIONPROC          glGetUniformLocation;
extern PFNGLUNIFORM1FPROC                   glUniform1f;
extern PFNGLUNIFORM2FPROC                   glUniform2f;
extern PFNGLUNIFORM3FPROC                   glUniform3f;
extern PFNGLUNIFORM4FPROC                   glUniform4f;
extern PFNGLUNIFORM1IPROC                   glUniform1i;
extern PFNGLUNIFORM2IPROC                   glUniform2i;
extern PFNGLUNIFORM3IPROC                   glUniform3i;
extern PFNGLUNIFORM4IPROC                   glUniform4i;
extern PFNGLUNIFORM1IVPROC                  glUniform1iv;
extern PFNGLUNIFORM2IVPROC                  glUniform2iv;
extern PFNGLUNIFORM3IVPROC                  glUniform3iv;
extern PFNGLUNIFORM4IVPROC                  glUniform4iv;
extern PFNGLUNIFORMMATRIX4FVPROC            glUniformMatrix4fv;
extern PFNGLUNIFORM1FVPROC                  glUniform1fv;
extern PFNGLUNIFORM2FVPROC                  glUniform2fv;
extern PFNGLUNIFORM3FVPROC                  glUniform3fv;
extern PFNGLUNIFORM4FVPROC                  glUniform4fv;
extern PFNGLGETSHADERSOURCEPROC             glGetShaderSource;
// GL_ARB_vertex_shader
extern PFNGLGETATTRIBLOCATIONPROC           glGetAttribLocation;
// GL_ARB_vertex_program
extern PFNGLENABLEVERTEXATTRIBARRAYPROC     glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC    glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC         glVertexAttribPointer;
// GL_EXT_framebuffer_object
extern PFNGLBINDRENDERBUFFEREXTPROC         glBindRenderbufferEXT;
extern PFNGLDELETERENDERBUFFERSEXTPROC      glDeleteRenderbuffersEXT;
extern PFNGLGENRENDERBUFFERSEXTPROC         glGenRenderbuffersEXT;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC      glRenderbufferStorageEXT;
extern PFNGLGENFRAMEBUFFERSEXTPROC          glGenFramebuffersEXT;
extern PFNGLBINDFRAMEBUFFEREXTPROC          glBindFramebufferEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC     glFramebufferTexture2DEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC  glFramebufferRenderbufferEXT;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC       glDeleteFramebuffersEXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC   glCheckFramebufferStatusEXT;
extern PFNGLDELETEFRAMEBUFFERSPROC          glDeleteFramebuffers;
extern PFNGLDELETERENDERBUFFERSPROC         glDeleteRenderbuffers;
extern PFNGLBINDFRAMEBUFFERPROC             glBindFramebuffer;
extern PFNGLGENFRAMEBUFFERSPROC             glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSPROC            glGenRenderbuffers;
extern PFNGLBINDRENDERBUFFERPROC            glBindRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC        glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC     glFramebufferRenderbuffer;
extern PFNGLRENDERBUFFERSTORAGEPROC         glRenderbufferStorage;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC      glCheckFramebufferStatus;
// GL_ARB_vertex_buffer_object
extern PFNGLBINDBUFFERPROC                  glBindBuffer;
extern PFNGLDELETEBUFFERSPROC               glDeleteBuffers;
extern PFNGLGENBUFFERSPROC                  glGenBuffers;
extern PFNGLISBUFFERPROC                    glIsBuffer;
extern PFNGLBUFFERDATAPROC                  glBufferData;
extern PFNGLBUFFERSUBDATAPROC               glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC            glGetBufferSubData;
extern PFNGLMAPBUFFERPROC                   glMapBuffer;
extern PFNGLUNMAPBUFFERPROC                 glUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC        glGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC           glGetBufferPointerv;
extern PFNGLMULTIDRAWARRAYSEXTPROC          glMultiDrawArraysEXT;
#ifdef WIN32
extern PFNGLACTIVETEXTUREPROC               glActiveTexture;;
#endif

class FWGLExtensions
{
public:
    FWGLExtensions();
    static bool loadGLExtensions();
};

#endif // OPENGL20_H
