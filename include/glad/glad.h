#ifndef GLAD_GLAD_H
# define GLAD_GLAD_H

# include <KHR/khrplatform.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*GLADloadproc)(const char *name);

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
typedef khronos_intptr_t GLintptr;
typedef khronos_ssize_t GLsizeiptr;

# define GL_FALSE 0
# define GL_TRUE 1
# define GL_COLOR_BUFFER_BIT 0x00004000
# define GL_DEPTH_BUFFER_BIT 0x00000100
# define GL_VERSION 0x1F02
# define GL_VERTEX_SHADER 0x8B31
# define GL_FRAGMENT_SHADER 0x8B30
# define GL_COMPILE_STATUS 0x8B81
# define GL_LINK_STATUS 0x8B82
# define GL_INFO_LOG_LENGTH 0x8B84

extern int GLAD_GL_VERSION_3_3;

typedef const GLubyte *(*PFNGLGETSTRINGPROC)(GLenum name);
typedef void (*PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (*PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (*PFNGLCLEARPROC)(GLbitfield mask);
typedef GLuint (*PFNGLCREATESHADERPROC)(GLenum type);
typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
typedef GLuint (*PFNGLCREATEPROGRAMPROC)(void);
typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);

extern PFNGLGETSTRINGPROC glad_glGetString;
extern PFNGLVIEWPORTPROC glad_glViewport;
extern PFNGLCLEARCOLORPROC glad_glClearColor;
extern PFNGLCLEARPROC glad_glClear;
extern PFNGLCREATESHADERPROC glad_glCreateShader;
extern PFNGLSHADERSOURCEPROC glad_glShaderSource;
extern PFNGLCOMPILESHADERPROC glad_glCompileShader;
extern PFNGLGETSHADERIVPROC glad_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC glad_glDeleteShader;
extern PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
extern PFNGLATTACHSHADERPROC glad_glAttachShader;
extern PFNGLLINKPROGRAMPROC glad_glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glad_glUseProgram;
extern PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;

# define glGetString glad_glGetString
# define glViewport glad_glViewport
# define glClearColor glad_glClearColor
# define glClear glad_glClear
# define glCreateShader glad_glCreateShader
# define glShaderSource glad_glShaderSource
# define glCompileShader glad_glCompileShader
# define glGetShaderiv glad_glGetShaderiv
# define glGetShaderInfoLog glad_glGetShaderInfoLog
# define glDeleteShader glad_glDeleteShader
# define glCreateProgram glad_glCreateProgram
# define glAttachShader glad_glAttachShader
# define glLinkProgram glad_glLinkProgram
# define glGetProgramiv glad_glGetProgramiv
# define glGetProgramInfoLog glad_glGetProgramInfoLog
# define glUseProgram glad_glUseProgram
# define glDeleteProgram glad_glDeleteProgram

int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif
