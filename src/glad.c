#include <glad/glad.h>

int GLAD_GL_VERSION_3_3 = 0;

PFNGLGETSTRINGPROC glad_glGetString = 0;
PFNGLVIEWPORTPROC glad_glViewport = 0;
PFNGLCLEARCOLORPROC glad_glClearColor = 0;
PFNGLCLEARPROC glad_glClear = 0;
PFNGLCREATESHADERPROC glad_glCreateShader = 0;
PFNGLSHADERSOURCEPROC glad_glShaderSource = 0;
PFNGLCOMPILESHADERPROC glad_glCompileShader = 0;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = 0;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = 0;
PFNGLDELETESHADERPROC glad_glDeleteShader = 0;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = 0;
PFNGLATTACHSHADERPROC glad_glAttachShader = 0;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = 0;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = 0;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = 0;
PFNGLUSEPROGRAMPROC glad_glUseProgram = 0;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = 0;

int gladLoadGLLoader(GLADloadproc load)
{
	if (!load)
		return 0;

	glad_glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
	glad_glViewport = (PFNGLVIEWPORTPROC)load("glViewport");
	glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
	glad_glClear = (PFNGLCLEARPROC)load("glClear");
	glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
	glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
	glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
	glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
	glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
	glad_glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
	glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
	glad_glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
	glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
	glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
	glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
	glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
	glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");

	GLAD_GL_VERSION_3_3 = glad_glGetString != 0
		&& glad_glViewport != 0
		&& glad_glClearColor != 0
		&& glad_glClear != 0
		&& glad_glCreateShader != 0
		&& glad_glShaderSource != 0
		&& glad_glCompileShader != 0
		&& glad_glGetShaderiv != 0
		&& glad_glGetShaderInfoLog != 0
		&& glad_glDeleteShader != 0
		&& glad_glCreateProgram != 0
		&& glad_glAttachShader != 0
		&& glad_glLinkProgram != 0
		&& glad_glGetProgramiv != 0
		&& glad_glGetProgramInfoLog != 0
		&& glad_glUseProgram != 0
		&& glad_glDeleteProgram != 0;
	return GLAD_GL_VERSION_3_3;
}
