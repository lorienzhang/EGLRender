#include "GLUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

GLuint createProgram(const char *vertexShader, const char *fragmentShader){
    GLuint vertex;
    GLuint fragment;
    GLuint program;
    GLint linked;

    vertex = loadShader(GL_VERTEX_SHADER, vertexShader);
    if (vertex == 0) {
        LOGD("load vertex shader error")
        return 0;
    }

    fragment = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
    if (fragment == 0) {
        glDeleteShader(vertex);
        LOGD("load fragment shader error")
        return 0;
    }

    program = glCreateProgram();
    if (program == 0) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // 链接program
    glLinkProgram(program);
    // 检查链接状态
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

GLuint loadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    GLint compiled;
    // 创建shader
    shader = glCreateShader(type);
    if (shader == 0) {
        return 0;
    }
    // 加载着色器源码
    glShaderSource(shader, 1, &shaderSrc, NULL);
    // 编译
    glCompileShader(shader);
    // 检查编译状态
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

#ifdef __cplusplus
}
#endif
