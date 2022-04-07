//
// Created by zhanghao43 on 2022/4/6.
//

#ifndef _EGLNATIVE_GLRENDER_H_
#define _EGLNATIVE_GLRENDER_H_

#include <android/native_window.h>

#include "../gles/EglCore.h"
#include "Triangle.h"

class GLRender {
public:
    GLRender();
    virtual ~GLRender();

    void surfaceCreated(ANativeWindow *window);

    void surfaceChanged(int width, int height);

    void surfaceDestroyed();

private:
    EglCore *mEglCore;
    Triangle *mTriangle;
};

#endif //_EGLNATIVE_GLRENDER_H_
