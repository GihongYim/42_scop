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
# define GL_TEXTURE_2D 0x0DE1
# define GL_TEXTURE0 0x84C0
# define GL_TEXTURE_WRAP_S 0x2802
# define GL_TEXTURE_WRAP_T 0x2803
# define GL_TEXTURE_MIN_FILTER 0x2801
# define GL_TEXTURE_MAG_FILTER 0x2800
# define GL_REPEAT 0x2901
# define GL_LINEAR 0x2601
# define GL_LINEAR_MIPMAP_LINEAR 0x2703
# define GL_RGB 0x1907
# define GL_UNSIGNED_BYTE 0x1401

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
typedef void (*PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (*PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
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
typedef void (*PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (*PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
typedef void (*PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (*PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
typedef void (*PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (*PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (*PFNGLGENERATEMIPMAPPROC)(GLenum target);

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
extern PFNGLUNIFORM1FPROC glad_glUniform1f;
extern PFNGLUNIFORM1IPROC glad_glUniform1i;
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
extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
extern PFNGLGENTEXTURESPROC glad_glGenTextures;
extern PFNGLBINDTEXTUREPROC glad_glBindTexture;
extern PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
extern PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
extern PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
extern PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;

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
# define glUniform1f glad_glUniform1f
# define glUniform1i glad_glUniform1i
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
# define glActiveTexture glad_glActiveTexture
# define glGenTextures glad_glGenTextures
# define glBindTexture glad_glBindTexture
# define glDeleteTextures glad_glDeleteTextures
# define glTexParameteri glad_glTexParameteri
# define glTexImage2D glad_glTexImage2D
# define glGenerateMipmap glad_glGenerateMipmap

int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif
