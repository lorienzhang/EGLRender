#ifndef _EGLNATIVE_TRIANGLE_H_
#define _EGLNATIVE_TRIANGLE_H_

#include "../gles/GLUtils.h"

class Triangle {
public:
    Triangle();

    virtual ~Triangle();

    int init();

    void onDraw(int width, int height);

    void destroy();

private:
    // GPU程序句柄
    int programHandle;
};

#endif //_EGLNATIVE_TRIANGLE_H_
