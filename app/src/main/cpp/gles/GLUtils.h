//
// Created by zhanghao43 on 2022/4/6.
//

#ifndef EGLNATIVE_GLUTILS_H
#define EGLNATIVE_GLUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#include <android/log.h>

#define TAG "lorien"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

GLuint createProgram(const char *vertexShader, const char *fragmentShader);

GLuint loadShader(GLenum type, const char *shaderSrc);

#ifdef __cplusplus
}
#endif

#endif //EGLNATIVE_GLUTILS_H
