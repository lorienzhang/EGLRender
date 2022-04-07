//
// Created by zhanghao43 on 2022/4/6.
//

#ifndef EGLNATIVE_MYLOOPER_H
#define EGLNATIVE_MYLOOPER_H

#include "looper.h"
#include "../render/GLRender.h"

enum {
    MsgSurfaceCreated,
    MsgSurfaceChanged,
    MsgSurfaceDestroyed
};

class MyLooper : public looper {
public:
    MyLooper();

    virtual ~MyLooper();

    virtual void handle(loopermessage *msg);

private:
    GLRender *mRender;
};

#endif //EGLNATIVE_MYLOOPER_H
