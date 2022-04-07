#include "Triangle.h"

const GLint COORDS_PER_VERTEX = 3;
const GLint vertexStride = COORDS_PER_VERTEX * 4;

Triangle::Triangle() {}

Triangle::~Triangle() {}

int Triangle::init() {
    char vertexShader[] =
            "#version 300 es\n"
            "layout(location = 0) in vec4 a_position;\n"
            "layout(location = 1) in vec4 a_color;\n"
            "out vec4 v_color;"
            "void main()\n"
            "{\n"
            "   gl_Position = a_position;\n"
            "   v_color = a_color;\n"
            "}\n";

    char fragmentShader[] =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec4 v_color;\n"
            "out vec4 fragColor;\n"
            "void main()\n"
            "{\n"
            "   fragColor = v_color;\n"
            "}\n";

    // 根据着色器，创建GL程序
    programHandle = createProgram(vertexShader, fragmentShader);
    if (programHandle <= 0) {
        LOGD("create program error, programHandle=%d\n", programHandle)
        return -1;
    }
    // 清屏
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    return 0;
}

void Triangle::onDraw(int width, int height) {
    GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    GLfloat color[] = {
            1.0f, 0.0f, 0.0f, 1.0f
    };

    GLint vertexCount = sizeof(vertices) / (sizeof(vertices[0]) * COORDS_PER_VERTEX);

    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);

    // 使用Program
    glUseProgram(programHandle);

    // 获取GL程序顶点着色器的a_position变量
    GLint positionHandle = glGetAttribLocation(programHandle, "a_position");
    // 设置顶点位置信息
    glVertexAttribPointer(positionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, vertexStride,
                          vertices);
    glEnableVertexAttribArray(positionHandle);
    // 设置片远着色器的color变量
    glVertexAttrib4fv(1, color);
    // 执行绘制
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(positionHandle);
}

void Triangle::destroy() {
    if (programHandle > 0) {
        glDeleteProgram(programHandle);
    }
    programHandle = -1;
}