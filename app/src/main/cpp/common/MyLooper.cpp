#include "MyLooper.h"

#define TAG "lorien"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

MyLooper::MyLooper() {
    mRender = new GLRender();
}

void MyLooper::handle(loopermessage *msg) {
    switch (msg->what) {
        case MsgSurfaceCreated:
            LOGD("handle message MsgSurfaceCreated")
            if (mRender) {
                mRender->surfaceCreated((ANativeWindow *) msg->obj);
            }
            break;

        case MsgSurfaceChanged:
            LOGD("handle message MsgSurfaceChanged")
            if (mRender) {
                mRender->surfaceChanged(msg->arg1, msg->arg2);
            }
            break;

        case MsgSurfaceDestroyed:
            LOGD("handle message MsgSurfaceDestroyed")
            if (mRender) {
                mRender->surfaceDestroyed();
            }
            break;
    }
}

MyLooper::~MyLooper() {
    delete mRender;
}