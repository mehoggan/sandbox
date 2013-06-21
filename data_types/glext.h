/*
 * Copyright 2013 Matthew Everett Hoggan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLEXT_H_INCLUDED
#define GLEXT_H_INCLUDED

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <climits>
#include <cstdio>
#include <limits>
#include <iostream>
#include <vector>

#define GLEXT_UNUSED_VAR(x) (void)(x)

#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
# define glGetProcAddress(arg) wglGetProcAddress(arg)
#elif __linux__
#include <GL/gl.h>
#include <GL/glext.h>
# include <GL/glx.h>
# define glGetProcAddress(arg) glXGetProcAddress((const GLubyte*)arg)
#endif

PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = 0;

PFNGLGENERATEMIPMAPPROC glGenerateMipmap = 0;

// GL_ARB_shader_objects
PFNGLCREATESHADERPROC glCreateShader = 0;
PFNGLDELETESHADERPROC glDeleteShader = 0;
PFNGLCREATEPROGRAMPROC glCreateProgram = 0;
PFNGLDELETEPROGRAMPROC glDeleteProgram = 0;
PFNGLGETSHADERIVPROC glGetShaderiv = 0;
PFNGLATTACHSHADERPROC glAttachShader = 0;
PFNGLDETACHSHADERPROC glDetachShader = 0;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = 0;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = 0;
PFNGLGETPROGRAMIVPROC glGetProgramiv = 0;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObject = 0;
PFNGLDETACHOBJECTARBPROC glDetachObject = 0;
PFNGLDELETEOBJECTARBPROC glDeleteObject = 0;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObject = 0;
PFNGLUSEPROGRAMPROC glUseProgram = 0;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObject = 0;
PFNGLSHADERSOURCEPROC glShaderSource = 0;
PFNGLCOMPILESHADERPROC glCompileShader = 0;
PFNGLLINKPROGRAMPROC glLinkProgram = 0;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = 0;
PFNGLUNIFORM1FPROC glUniform1f = 0;
PFNGLUNIFORM2FPROC glUniform2f = 0;
PFNGLUNIFORM3FPROC glUniform3f = 0;
PFNGLUNIFORM4FPROC glUniform4f = 0;
PFNGLUNIFORM1IPROC glUniform1i = 0;
PFNGLUNIFORM2IPROC glUniform2i = 0;
PFNGLUNIFORM3IPROC glUniform3i = 0;
PFNGLUNIFORM4IPROC glUniform4i = 0;
PFNGLUNIFORM1IVPROC glUniform1iv = 0;
PFNGLUNIFORM2IVPROC glUniform2iv = 0;
PFNGLUNIFORM3IVPROC glUniform3iv = 0;
PFNGLUNIFORM4IVPROC glUniform4iv = 0;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = 0;
PFNGLUNIFORM1FVPROC glUniform1fv = 0;
PFNGLUNIFORM2FVPROC glUniform2fv = 0;
PFNGLUNIFORM3FVPROC glUniform3fv = 0;
PFNGLUNIFORM4FVPROC glUniform4fv = 0;
PFNGLGETSHADERSOURCEPROC glGetShaderSource = 0;

// GL_ARB_vertex_shader
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = 0;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = 0;

// GL_ARB_vertex_program
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;

// GL_EXT_framebuffer_object
PFNGLBINDRENDERBUFFEREXTPROC glBindRenderbufferEXT = 0;
PFNGLDELETERENDERBUFFERSEXTPROC glDeleteRenderbuffersEXT = 0;
PFNGLGENRENDERBUFFERSEXTPROC glGenRenderbuffersEXT = 0;
PFNGLRENDERBUFFERSTORAGEEXTPROC glRenderbufferStorageEXT = 0;
PFNGLGENFRAMEBUFFERSEXTPROC glGenFramebuffersEXT = 0;
PFNGLBINDFRAMEBUFFEREXTPROC glBindFramebufferEXT = 0;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2DEXT = 0;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC
  glFramebufferRenderbufferEXT = 0;
PFNGLDELETEFRAMEBUFFERSEXTPROC
  glDeleteFramebuffersEXT = 0;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatusEXT = 0;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = 0;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = 0;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = 0;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = 0;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = 0;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = 0;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = 0;
// GL_ARB_vertex_buffer_object
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLISBUFFERPROC glIsBuffer = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLBUFFERSUBDATAPROC glBufferSubData = 0;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = 0;
PFNGLMAPBUFFERPROC glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = 0;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = 0;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = 0;

// GL_EXT_multi_draw_arrays
PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT = 0;

#ifdef WIN32
PFNGLACTIVETEXTUREPROC glActiveTexture=0;;
#endif

namespace glext
{
  enum render_target_enum
  {
    array_buffer = GL_ARRAY_BUFFER,
    element_array_buffer = GL_ELEMENT_ARRAY_BUFFER
  };

  enum render_usage_enum
  {
    stream_draw = GL_STREAM_DRAW,
    static_draw = GL_STATIC_DRAW,
    dynmaic_draw = GL_DYNAMIC_DRAW
  };

  enum render_primitive_mode_enum
  {
    points = GL_POINTS,
    line_strip = GL_LINE_STRIP,
    line_loop = GL_LINE_LOOP,
    lines = GL_LINES,
    triangle_strip = GL_TRIANGLE_STRIP,
    triangle_fan = GL_TRIANGLE_FAN,
    triangles = GL_TRIANGLES
  };

  enum index_type_enum
  {
    unsigned_byte = GL_UNSIGNED_BYTE,
    unsigned_short = GL_UNSIGNED_SHORT
  };
  
  class null_type 
  {
  };

  /*!
   * \brief load_gl_extensions this method loads all the extensions supported
   * by OpenGL ES2
   * \return bool
   */
  bool load_gl_extensions()
  {
    static bool loaded = false;
    if (loaded) {
      return true;
    }

    if (!glBlendFuncSeparate) {
      glBlendFuncSeparate = 
        (PFNGLBLENDFUNCSEPARATEPROC)(glGetProcAddress("glBlendFuncSeparate"));
      if (!glBlendFuncSeparate) {
        throw "Failed to load glBlendFuncSeparate";
      }
    }

    if (!glGenerateMipmap) {
      glGenerateMipmap = 
        (PFNGLGENERATEMIPMAPPROC)(glGetProcAddress("glGenerateMipmap"));
      if (!glBlendFuncSeparate) {
        throw "Failed to load glGenerateMipmap";
      }
    }

    if (!glCreateShader) {
      glCreateShader = 
        (PFNGLCREATESHADERPROC)(glGetProcAddress("glCreateShader"));
      if (!glCreateShader) {
        throw "Failed to load glCreateShader";
      }
    }

    if (!glDeleteShader) {
      glDeleteShader = 
        (PFNGLDELETESHADERPROC)(glGetProcAddress("glDeleteShader"));
      if (!glDeleteShader) {
        throw "Failed to load glDeleteShader";
      }
    }

    if (!glCreateProgram) {
      glCreateProgram = 
        (PFNGLCREATEPROGRAMPROC)(glGetProcAddress("glCreateProgram"));
      if (!glCreateProgram) {
        throw "Failed to load glCreateProgram";
      }
    }

    if (!glDeleteProgram) {
      glDeleteProgram = 
        (PFNGLDELETEPROGRAMPROC)(glGetProcAddress("glDeleteProgram"));
      if (!glDeleteProgram) {
        throw "Failed to load glDeleteProgram";
      }
    }

    if (!glGetShaderiv) {
      glGetShaderiv = 
        (PFNGLGETSHADERIVPROC)(glGetProcAddress("glGetShaderiv"));
      if (!glGetShaderiv) {
        throw "Failed to load glGetShaderiv";
      }
    }

    if (!glAttachShader)
    {
      glAttachShader = 
        (PFNGLATTACHSHADERPROC)(glGetProcAddress("glAttachShader"));
      if (!glAttachShader) {
        throw "Failed to load glAttachShader";
      }
    }

    if (!glDetachShader) {
      glDetachShader = 
        (PFNGLDETACHSHADERPROC)(glGetProcAddress("glDetachShader"));
      if (!glDetachShader) {
        throw "Failed to load glDetachShader";
      }
    }

    if (!glGetShaderInfoLog) {
      glGetShaderInfoLog = 
        (PFNGLGETSHADERINFOLOGPROC)(glGetProcAddress("glGetShaderInfoLog"));
      if (!glGetShaderInfoLog) {
        throw "Failed to load glGetShaderInfoLog";
      }
    }

    if (!glGetProgramInfoLog) {
      glGetProgramInfoLog = 
        (PFNGLGETPROGRAMINFOLOGPROC)(glGetProcAddress("glGetProgramInfoLog"));
      if (!glGetProgramInfoLog) {
        throw "Failed to load glGetProgramInfoLog";
      }
    }

    if (!glGetProgramiv) {
      glGetProgramiv = 
        (PFNGLGETPROGRAMIVPROC)(glGetProcAddress("glGetProgramiv"));
      if (!glGetProgramiv) {
        throw "Failed to load glGetProgramiv";
      }
    }

    if (!glUseProgram) {
      glUseProgram = 
        (PFNGLUSEPROGRAMPROC)(glGetProcAddress("glUseProgram"));
      if (!glUseProgram) {
        throw "Failed to load glUseProgram";
      }
    }

    if (!glShaderSource) {
      glShaderSource = 
        (PFNGLSHADERSOURCEPROC)(glGetProcAddress("glShaderSource"));
      if (!glShaderSource) {
        throw "Failed to load glShaderSource";
      }
    }

    if (!glCompileShader) {
      glCompileShader = 
        (PFNGLCOMPILESHADERPROC)(glGetProcAddress("glCompileShader"));
      if (!glCompileShader) {
        throw "Failed to load glCompileShader";
      }
    }

    if (!glLinkProgram) {
      glLinkProgram = 
        (PFNGLLINKPROGRAMPROC)(glGetProcAddress("glLinkProgram"));
      if (!glLinkProgram) {
        throw "Failed to load glLinkProgram";
      }
    }

    if (!glGetUniformLocation) {
      glGetUniformLocation = 
        (PFNGLGETUNIFORMLOCATIONPROC)(glGetProcAddress("glGetUniformLocation"));
      if (!glGetUniformLocation) {
        throw "Failed to load glGetUniformLocation";
      }
    }

    if (!glUniform1f) {
      glUniform1f = 
        (PFNGLUNIFORM1FPROC)(glGetProcAddress("glUniform1f"));
      if (!glUniform1f) {
        throw "Failed to load glUniform1f";
      }
    }

    if (!glUniform2f) {
      glUniform2f = 
        (PFNGLUNIFORM2FPROC)(glGetProcAddress("glUniform2f"));
      if (!glUniform2f) {
        throw "Failed to load glUniform2f";
      }
    }

    if (!glUniform3f) {
      glUniform3f = 
        (PFNGLUNIFORM3FPROC)(glGetProcAddress("glUniform3f"));
      if (!glUniform3f) {
        throw "Failed to load glUniform3f";
      }
    }

    if (!glUniform4f) {
      glUniform4f = 
        (PFNGLUNIFORM4FPROC)(glGetProcAddress("glUniform4f"));
      if (!glUniform4f) {
        throw "Failed to load glUniform4f";
      }
    }

    if (!glUniform1i) {
      glUniform1i = 
        (PFNGLUNIFORM1IPROC)(glGetProcAddress("glUniform1i"));
      if (!glUniform1i) {
        throw "Failed to load glUniform1i";
      }
    }

    if (!glUniform2i) {
      glUniform2i = 
        (PFNGLUNIFORM2IPROC)(glGetProcAddress("glUniform2i"));
      if (!glUniform2i) {
        throw "Failed to load glUniform2i";
      }
    }

    if (!glUniform3i) {
      glUniform3i = 
        (PFNGLUNIFORM3IPROC)(glGetProcAddress("glUniform3i"));
      if (!glUniform3i) {
        throw "Failed to load glUniform3i";
      }
    }

    if (!glUniform4i) {
      glUniform4i = 
        (PFNGLUNIFORM4IPROC)(glGetProcAddress("glUniform4i"));
      if (!glUniform4i) {
        throw "Failed to load glUniform4i";
      }
    }

    if (!glUniform1iv) {
      glUniform1iv = 
        (PFNGLUNIFORM1IVPROC)(glGetProcAddress("glUniform1iv"));
      if (!glUniform1iv) {
        throw "Failed to load glUniform1iv";
      }
    }

    if (!glUniform2iv) {
      glUniform2iv = 
        (PFNGLUNIFORM2IVPROC)(glGetProcAddress("glUniform2iv"));
      if (!glUniform2iv) {
        throw "Failed to load glUniform2iv";
      }
    }

    if (!glUniform3iv) {
      glUniform3iv = 
        (PFNGLUNIFORM3IVPROC)(glGetProcAddress("glUniform3iv"));
      if (!glUniform3iv) {
        throw "Failed to load glUniform3iv";
      }
    }

    if (!glUniform4iv) {
      glUniform4iv = 
        (PFNGLUNIFORM4IVPROC)(glGetProcAddress("glUniform4iv"));
      if (!glUniform4iv) {
        throw "Failed to load glUniform4iv";
      }
    }

    if (!glUniformMatrix2fv) {
      glUniformMatrix2fv = 
        (PFNGLUNIFORMMATRIX2FVPROC)(glGetProcAddress("glUniformMatrix2fv"));
      if (!glUniformMatrix2fv) {
        throw "Failed to load glUniformMatrix2fv";
      }
    }

    if (!glUniformMatrix3fv) {
      glUniformMatrix3fv = 
        (PFNGLUNIFORMMATRIX3FVPROC)(glGetProcAddress("glUniformMatrix3fv"));
      if (!glUniformMatrix3fv) {
        throw "Failed to load glUniformMatrix3fv";
      }
    }

    if (!glUniformMatrix4fv) {
      glUniformMatrix4fv = 
        (PFNGLUNIFORMMATRIX4FVPROC)(glGetProcAddress("glUniformMatrix4fv"));
      if (!glUniformMatrix4fv) {
        throw "Failed to load glUniformMatrix4fv";
      }
    }

    if (!glUniform1fv) {
      glUniform1fv = 
        (PFNGLUNIFORM1FVPROC)(glGetProcAddress("glUniform1fv"));
      if (!glUniform1fv) {
        throw "Failed to load glUniform1fv";
      }
    }

    if (!glUniform2fv) {
      glUniform2fv = 
        (PFNGLUNIFORM2FVPROC)(glGetProcAddress("glUniform2fv"));
      if (!glUniform2fv) {
        throw "Failed to load glUniform2fv";
      }
    }

    if (!glUniform3fv) {
      glUniform3fv = 
        (PFNGLUNIFORM3FVPROC)(glGetProcAddress("glUniform3fv"));
      if (!glUniform3fv) {
        throw "Failed to load glUniform3fv";
      }
    }

    if (!glUniform4fv) {
      glUniform4fv = 
        (PFNGLUNIFORM4FVPROC)(glGetProcAddress("glUniform4fv"));
      if (!glUniform4fv) {
        throw "Failed to load glUniform4fv";
      }
    }

    if (!glGetShaderSource) {
      glGetShaderSource = 
        (PFNGLGETSHADERSOURCEPROC)(glGetProcAddress("glGetShaderSource"));
      if (!glGetShaderSource) {
        throw "Failed to load glGetShaderSource";
      }
    }

    if (!glBindAttribLocation) {
      glBindAttribLocation = 
        (PFNGLBINDATTRIBLOCATIONPROC)(glGetProcAddress("glBindAttribLocation"));
      if (!glBindAttribLocation) {
        throw "Failed to load glBindAttribLocation";
      }
    }

    if (!glGetAttribLocation) {
      glGetAttribLocation = 
        (PFNGLGETATTRIBLOCATIONPROC)(glGetProcAddress("glGetAttribLocation"));
      if (!glGetAttribLocation) {
        throw "Failed to load glGetAttribLocation";
      }
    }

    if (!glEnableVertexAttribArray) {
      glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)(
        glGetProcAddress("glEnableVertexAttribArray"));
      if (!glEnableVertexAttribArray) {
        throw "Failed to load glEnableVertexAttribArray";
      }
    }

    if (!glDisableVertexAttribArray) {
      glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)(
        glGetProcAddress("glDisableVertexAttribArray"));
      if (!glDisableVertexAttribArray) {
        throw "Failed to load glDisableVertexAttribArray";
      }
    }

    if (!glVertexAttribPointer) {
      glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)(
        glGetProcAddress("glVertexAttribPointer"));
      if (!glVertexAttribPointer) {
        throw "Failed to load glVertexAttribPointer";
      }
    }

    if (!glBindRenderbufferEXT) {
      glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)(
        glGetProcAddress("glBindRenderbufferEXT"));
      if (!glBindRenderbufferEXT) {
        throw "Failed to load glBindRenderbufferEXT";
      }
    }

    if (!glDeleteRenderbuffersEXT) {
      glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)(
        glGetProcAddress("glDeleteRenderbuffersEXT"));
      if (!glDeleteRenderbuffersEXT) {
        throw "Failed to load glDeleteRenderbuffersEXT";
      }
    }

    if (!glGenRenderbuffersEXT) {
      glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)(
        glGetProcAddress("glGenRenderbuffersEXT"));
      if (!glGenRenderbuffersEXT) {
        throw "Failed to load glGenRenderbuffersEXT";
      }
    }

    if (!glRenderbufferStorageEXT) {
      glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)(
        glGetProcAddress("glRenderbufferStorageEXT"));
      if (!glRenderbufferStorageEXT) {
        throw "Failed to load glRenderbufferStorageEXT";
      }
    }

    if (!glGenFramebuffersEXT) {
      glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)(
        glGetProcAddress("glGenFramebuffersEXT"));
      if (!glGenFramebuffersEXT) {
        throw "Failed to load glGenFramebuffersEXT";
      }
    }

    if (!glBindFramebufferEXT) {
      glBindFramebufferEXT = 
        (PFNGLBINDFRAMEBUFFEREXTPROC)(glGetProcAddress("glBindFramebufferEXT"));
      if (!glBindFramebufferEXT) {
        throw "Failed to load glBindFramebufferEXT";
      }
    }

    if (!glFramebufferTexture2DEXT) {
      glFramebufferTexture2DEXT =
        (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)(
          glGetProcAddress("glFramebufferTexture2DEXT"));
      if (!glFramebufferTexture2DEXT) {
        throw "Failed to load glFramebufferTexture2DEXT";
      }
    }

    if (!glFramebufferRenderbufferEXT) {
      glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)(
        glGetProcAddress("glFramebufferRenderbufferEXT"));
      if (!glFramebufferRenderbufferEXT) {
        throw "Failed to load glFramebufferRenderbufferEXT";
      }
    }

    if (!glDeleteFramebuffersEXT) {
      glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)(
        glGetProcAddress("glDeleteFramebuffersEXT"));
      if (!glDeleteFramebuffersEXT) {
        throw "Failed to load glDeleteFramebuffersEXT";
      }
    }

    if (!glCheckFramebufferStatusEXT) {
      glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)(
        glGetProcAddress("glCheckFramebufferStatusEXT"));
      if (!glCheckFramebufferStatusEXT) {
        throw "Failed to load glCheckFramebufferStatusEXT";
      }
    }

    if (!glDeleteFramebuffers) {
      glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)(
        glGetProcAddress("glDeleteFramebuffers"));
      if (!glDeleteFramebuffers) {
        throw "Failed to load glDeleteFramebuffers";
      }
    }

    if (!glDeleteRenderbuffers) {
      glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)(
        glGetProcAddress("glDeleteRenderbuffers"));
      if (!glDeleteRenderbuffers) {
        throw "Failed to load glDeleteRenderbuffers";
      }
    }

    if (!glBindFramebuffer) {
      glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)(
        glGetProcAddress("glBindFramebuffer"));
      if (!glBindFramebuffer) {
        throw "Failed to load glBindFramebuffer";
      }
    }

    if (!glGenFramebuffers) {
      glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)(
        glGetProcAddress("glGenFramebuffers"));
      if (!glGenFramebuffers) {
        throw "Failed to load glGenFramebuffers";
      }
    }

    if (!glGenRenderbuffers) {
      glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)(
        glGetProcAddress("glGenRenderbuffers"));
      if (!glGenRenderbuffers) {
        throw "Failed to load glGenRenderbuffers";
      }
    }

    if (!glBindRenderbuffer) {
      glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)(
        glGetProcAddress("glBindRenderbuffer"));
      if (!glBindRenderbuffer) {
        throw "Failed to load glBindRenderbuffer";
      }
    }

    if (!glFramebufferTexture2D) {
      glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)(
        glGetProcAddress("glFramebufferTexture2D"));
      if (!glFramebufferTexture2D) {
        throw "Failed to load glFramebufferTexture2D";
      }
    }

    if (!glFramebufferRenderbuffer) {
      glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)(
        glGetProcAddress("glFramebufferRenderbuffer"));
      if (!glFramebufferRenderbuffer) {
        throw "Failed to load glFramebufferRenderbuffer";
      }
    }

    if (!glRenderbufferStorage) {
      glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)(
        glGetProcAddress("glRenderbufferStorage"));
      if (!glRenderbufferStorage) {
        throw "Failed to load glRenderbufferStorage";
      }
    }

    if (!glCheckFramebufferStatus) {
      glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)(
        glGetProcAddress("glCheckFramebufferStatus"));
      if (!glCheckFramebufferStatus) {
        throw "Failed to load glCheckFramebufferStatus";
      }
    }

    if (!glGenBuffers) {
      glGenBuffers = (PFNGLGENBUFFERSPROC)(glGetProcAddress("glGenBuffers"));
      if (!glGenBuffers) {
        throw "Failed to load glGenBuffers";
      }
    }

    if (!glBindBuffer) {
      glBindBuffer = (PFNGLBINDBUFFERPROC)(glGetProcAddress("glBindBuffer"));
      if (!glBindBuffer) {
        throw "Failed to load glBindBuffer";
      }
    }

    if (!glBufferData) {
      glBufferData = (PFNGLBUFFERDATAPROC)(glGetProcAddress("glBufferData"));
      if (!glBufferData) {
        throw "Failed to load glBufferData";
      }
    }

    if (!glDeleteBuffers) {
      glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)(
        glGetProcAddress("glDeleteBuffers"));
      if (!glDeleteBuffers) {
        throw "Failed to load glDeleteBuffers";
      }
    }

    if (!glBufferSubData) {
      glBufferSubData = (PFNGLBUFFERSUBDATAPROC)(
        glGetProcAddress("glBufferSubData"));
      if (!glBufferSubData) {
        throw "Failed to load glBufferSubData";
      }
    }

    if (!glIsBuffer) {
      glIsBuffer = (PFNGLISBUFFERPROC)(glGetProcAddress("glIsBuffer"));
      if (!glIsBuffer) {
        throw "Failed to load glIsBuffer";
      }
    }

    if (!glGetBufferSubData) {
      glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)(
        glGetProcAddress("glGetBufferSubData"));
      if (!glGetBufferSubData) {
        throw "Failed to load glGetBufferSubData";
      }
    }

    if (!glMapBuffer) {
      glMapBuffer = (PFNGLMAPBUFFERPROC)(glGetProcAddress("glMapBuffer"));
      if (!glMapBuffer) {
        throw "Failed to load glMapBuffer";
      }
    }

    if (!glUnmapBuffer) {
      glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)(glGetProcAddress("glUnmapBuffer"));
      if (!glUnmapBuffer) {
        throw "Failed to load glUnmapBuffer";
      }
    }

    if (!glGetBufferParameteriv) {
      glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)(
        glGetProcAddress("glGetBufferParameteriv"));
      if (!glGetBufferParameteriv) {
        throw "Failed to load glGetBufferParameteriv";
      }
    }

    if (!glGetBufferPointerv) {
      glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)(
        glGetProcAddress("glGetBufferPointerv"));
      if (!glGetBufferPointerv) {
        throw "Failed to load glGetBufferPointerv";
      }
    }

    if (!glMultiDrawArraysEXT) {
      glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC)(
        glGetProcAddress("glMultiDrawArraysEXT"));
      if (!glMultiDrawArraysEXT) {
        throw "Failed to load glMultiDrawArraysEXT";
      }
    }

#ifdef WIN32
    if (!glActiveTexture) {
      glActiveTexture = (PFNGLACTIVETEXTUREPROC)(
        glGetProcAddress("glActiveTexture"));
      if (!glActiveTexture) {
        throw "Failed to load glActiveTexture";
      }
    }
#endif

    loaded = true;
    return loaded;
  }
}

#endif
