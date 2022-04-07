#include "GLRender.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

GLRender::GLRender() {
    mEglCore = NULL;
}

GLRender::~GLRender() {
    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}

void GLRender::surfaceCreated(ANativeWindow *window) {
    if (mEglCore == NULL) {
        mEglCore = new EglCore();
        // 创建EGL上下文
        mEglCore->createContext(NULL);
    }

    mEglCore->createWindowSurface(window);
    // 为渲染线程绑定surface和context
    mEglCore->makeCurrent();
    mTriangle = new Triangle();
    mTriangle->init();
}

void GLRender::surfaceChanged(int width, int height) {
    mTriangle->onDraw(width, height);
    mEglCore->swapBuffers();
}

void GLRender::surfaceDestroyed() {
    if (mTriangle) {
        mTriangle->destroy();
        delete mTriangle;
        mTriangle = NULL;
    }
    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}