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

# define GL_DEPTH_TEST 0x0B71
# define GL_FALSE 0
# define GL_TRUE 1
# define GL_COLOR_BUFFER_BIT 0x00004000
# define GL_DEPTH_BUFFER_BIT 0x00000100
# define GL_TRIANGLES 0x0004
# define GL_FLOAT 0x1406
# define GL_UNSIGNED_INT 0x1405
# define GL_ARRAY_BUFFER 0x8892
# define GL_ELEMENT_ARRAY_BUFFER 0x8893
# define GL_STATIC_DRAW 0x88E4
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
typedef void (*PFNGLENABLEPROC)(GLenum cap);
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
typedef GLint (*PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar *name);
typedef void (*PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);
typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (*PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);

extern PFNGLGETSTRINGPROC glad_glGetString;
extern PFNGLVIEWPORTPROC glad_glViewport;
extern PFNGLCLEARCOLORPROC glad_glClearColor;
extern PFNGLCLEARPROC glad_glClear;
extern PFNGLENABLEPROC glad_glEnable;
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
extern PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
extern PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
extern PFNGLGENBUFFERSPROC glad_glGenBuffers;
extern PFNGLBINDBUFFERPROC glad_glBindBuffer;
extern PFNGLBUFFERDATAPROC glad_glBufferData;
extern PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
extern PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
extern PFNGLDRAWELEMENTSPROC glad_glDrawElements;

# define glGetString glad_glGetString
# define glViewport glad_glViewport
# define glClearColor glad_glClearColor
# define glClear glad_glClear
# define glEnable glad_glEnable
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
# define glGetUniformLocation glad_glGetUniformLocation
# define glUniformMatrix4fv glad_glUniformMatrix4fv
# define glGenVertexArrays glad_glGenVertexArrays
# define glBindVertexArray glad_glBindVertexArray
# define glDeleteVertexArrays glad_glDeleteVertexArrays
# define glGenBuffers glad_glGenBuffers
# define glBindBuffer glad_glBindBuffer
# define glBufferData glad_glBufferData
# define glDeleteBuffers glad_glDeleteBuffers
# define glVertexAttribPointer glad_glVertexAttribPointer
# define glEnableVertexAttribArray glad_glEnableVertexAttribArray
# define glDrawElements glad_glDrawElements

int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif
