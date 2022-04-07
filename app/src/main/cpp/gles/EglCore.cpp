#include "EglCore.h"
#include "GLUtils.h"

EglCore::EglCore() {
}

EglCore::~EglCore() {
    release();
}

bool EglCore::createContext(EGLContext sharedContext) {
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        return false;
    }

    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        return false;
    }

    // 不关心版本号，直接传0即可
    if (!eglInitialize(mEGLDisplay, 0, 0)) {
        return false;
    }

    const EGLint attribList[] = {EGL_BUFFER_SIZE, 32,
                                 EGL_ALPHA_SIZE, 8,
                                 EGL_BLUE_SIZE, 8,
                                 EGL_GREEN_SIZE, 8,
                                 EGL_RED_SIZE, 8,
                                 EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                                 EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                                 EGL_NONE };
    // 获取config
    EGLConfig config;
    int numConfigs;
    if (!eglChooseConfig(mEGLDisplay, attribList, &config, 1, &numConfigs)) {
        return false;
    }

    // CreateContext
    int attrib2_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    EGLContext context = eglCreateContext(mEGLDisplay, config, sharedContext, attrib2_list);
    if (eglGetError() == EGL_SUCCESS) {
        mEGLConfig = config;
        mEGLContext = context;
    }

    int values[1] = {0};
    eglQueryContext(mEGLDisplay, mEGLContext, EGL_CONTEXT_CLIENT_VERSION, values);
    LOGD("EGLContext created, client version %d", values[0])

    return true;
}

EGLSurface EglCore::createWindowSurface(ANativeWindow *window) {
    if (window == NULL) {
        return NULL;
    }

    int surfaceAttribs[] = {
            EGL_NONE
    };
    mEglSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, window, surfaceAttribs);
    if (mEglSurface == NULL) {
        return NULL;
    }
    return mEglSurface;

}

void EglCore::makeCurrent() {
    if (!eglMakeCurrent(mEGLDisplay, mEglSurface, mEglSurface, mEGLContext)) {
        LOGD("make current error")
    }
}

void EglCore::release() {
    // 销毁surface
    eglDestroySurface(mEGLDisplay, mEglSurface);
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        // 销毁上下文
        eglDestroyContext(mEGLDisplay, mEGLContext);
        eglReleaseThread();
        eglTerminate(mEGLDisplay);
    }
    mEGLDisplay = EGL_NO_DISPLAY;
    mEGLContext = EGL_NO_CONTEXT;
    mEGLConfig = NULL;
}

bool EglCore::swapBuffers() {
    return eglSwapBuffers(mEGLDisplay, mEglSurface);
}

