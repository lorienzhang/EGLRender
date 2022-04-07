#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "common/MyLooper.h"

MyLooper *mLooper = NULL;
ANativeWindow *mWindow = NULL;

extern "C" JNIEXPORT void JNICALL
Java_com_baidu_eglrender_MainActivity_nativeInit(
        JNIEnv* env,
        jobject /* this */) {
    mLooper = new MyLooper();
}

extern "C" JNIEXPORT void JNICALL
Java_com_baidu_eglrender_MainActivity_onSurfaceCreated(
        JNIEnv *env, jobject instance, jobject surface) {
    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = NULL;
    }
    mWindow = ANativeWindow_fromSurface(env, surface);
    if (mLooper) {
        LOGD("post MsgSurfaceCreated")
        mLooper->post(MsgSurfaceCreated, mWindow);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_baidu_eglrender_MainActivity_onSurfaceChanged(
        JNIEnv *env, jobject instance,
        jint width, jint height) {
    if (mLooper) {
        mLooper->post(MsgSurfaceChanged, width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_baidu_eglrender_MainActivity_onSurfaceDestroyed(
        JNIEnv *env, jobject instance) {
    if (mLooper) {
        mLooper->post(MsgSurfaceDestroyed, NULL);
    }
}