#ifndef _EGLNATIVE_EGLCORE_H_
#define _EGLNATIVE_EGLCORE_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

class EglCore {
public:
    EglCore();

    // 创建EGL上下文
    bool createContext(EGLContext sharedContext);

    // 创建surface
    EGLSurface createWindowSurface(ANativeWindow *window);

    // 切换到当前上下文
    void makeCurrent();

    // 交换buffer
    bool swapBuffers();

    void release();

    ~EglCore();

private:
    EGLDisplay mEGLDisplay = EGL_NO_DISPLAY;
    EGLConfig  mEGLConfig = NULL;
    EGLContext mEGLContext = EGL_NO_CONTEXT;
    EGLSurface mEglSurface;
};

#endif //_EGLNATIVE_EGLCORE_H_
