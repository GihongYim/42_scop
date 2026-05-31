#include <glad/glad.h>

int GLAD_GL_VERSION_3_3 = 0;

PFNGLGETSTRINGPROC glad_glGetString = 0;
PFNGLVIEWPORTPROC glad_glViewport = 0;
PFNGLCLEARCOLORPROC glad_glClearColor = 0;
PFNGLCLEARPROC glad_glClear = 0;
PFNGLENABLEPROC glad_glEnable = 0;
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
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = 0;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = 0;
PFNGLUNIFORM1FPROC glad_glUniform1f = 0;
PFNGLUNIFORM1IPROC glad_glUniform1i = 0;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = 0;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = 0;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = 0;
PFNGLGENBUFFERSPROC glad_glGenBuffers = 0;
PFNGLBINDBUFFERPROC glad_glBindBuffer = 0;
PFNGLBUFFERDATAPROC glad_glBufferData = 0;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = 0;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = 0;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = 0;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = 0;
PFNGLGENTEXTURESPROC glad_glGenTextures = 0;
PFNGLBINDTEXTUREPROC glad_glBindTexture = 0;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = 0;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = 0;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = 0;
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = 0;

int gladLoadGLLoader(GLADloadproc load)
{
	if (!load)
		return 0;

	glad_glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
	glad_glViewport = (PFNGLVIEWPORTPROC)load("glViewport");
	glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
	glad_glClear = (PFNGLCLEARPROC)load("glClear");
	glad_glEnable = (PFNGLENABLEPROC)load("glEnable");
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
	glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation");
	glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
	glad_glUniform1f = (PFNGLUNIFORM1FPROC)load("glUniform1f");
	glad_glUniform1i = (PFNGLUNIFORM1IPROC)load("glUniform1i");
	glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
	glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
	glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
	glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
	glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
	glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
	glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
	glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
	glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
	glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
	glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
	glad_glGenTextures = (PFNGLGENTEXTURESPROC)load("glGenTextures");
	glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
	glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
	glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)load("glTexParameteri");
	glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
	glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");

	GLAD_GL_VERSION_3_3 = glad_glGetString != 0
		&& glad_glViewport != 0
		&& glad_glClearColor != 0
		&& glad_glClear != 0
		&& glad_glEnable != 0
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
		&& glad_glDeleteProgram != 0
		&& glad_glGetUniformLocation != 0
		&& glad_glUniformMatrix4fv != 0
		&& glad_glUniform1f != 0
		&& glad_glUniform1i != 0
		&& glad_glGenVertexArrays != 0
		&& glad_glBindVertexArray != 0
		&& glad_glDeleteVertexArrays != 0
		&& glad_glGenBuffers != 0
		&& glad_glBindBuffer != 0
		&& glad_glBufferData != 0
		&& glad_glDeleteBuffers != 0
		&& glad_glVertexAttribPointer != 0
		&& glad_glEnableVertexAttribArray != 0
		&& glad_glDrawElements != 0
		&& glad_glActiveTexture != 0
		&& glad_glGenTextures != 0
		&& glad_glBindTexture != 0
		&& glad_glDeleteTextures != 0
		&& glad_glTexParameteri != 0
		&& glad_glTexImage2D != 0
		&& glad_glGenerateMipmap != 0;
	return GLAD_GL_VERSION_3_3;
}
