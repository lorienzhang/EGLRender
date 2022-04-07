cmake_minimum_required(VERSION 3.10.2)

project("eglrender")

add_library( # Sets the name of the library.
             egl-render

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             EglJni.cpp
        common/looper.cpp
        common/MyLooper.cpp
        render/GLRender.cpp
        render/Triangle.cpp
        gles/EglCore.cpp
        gles/GLUtils.cpp)

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
find_library(EGL-lib EGL)
find_library(GLESv2-lib GLESv2)

target_link_libraries(
        # Specifies the target library.
        egl-render

        android
        ${log-lib}
        ${EGL-lib}
        ${GLESv2-lib} )