
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const double pi = std::acos(-1); //std::numbers::pi since C++20

float normalize(float val)
{
    return val / 100.0f;
}

void setPerspectiveProjection(int width, int height) {
    const float zNear = 0.1f;
    const float zFar = 100.0f;
    const float fov = 45.0f; // degrees

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    float fH = std::tan(fov / 360.0f * pi) * zNear;
    float fW = fH * aspectRatio;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void setCameraView() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Position the camera at (3, 3, 3) looking at the origin (0, 0, 0)
    // with the up vector set to (0, 1, 0)
    glTranslatef(-0.9f, -0.7f, -5.0f);
    glRotatef(30.0f, -0.4f, -0.5f, 0.0f);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set up for a compatibility profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1600, 1200, "Legacy OpenGL Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Check OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    setPerspectiveProjection(1600, 1200);
    setCameraView();
    // Render loop
    glPointSize(2.0f); // Set point size to 5 pixels
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Legacy OpenGL commands
        glColor3d(1.0, 0.7, 0.7);


        glBegin(GL_POINTS);

        for (int i = 0; i < 1000; i++) {
            //glVertex3i(i, 2 * i, 0);
            float x = normalize(i);
            float y = x;
            float z = y;
            glVertex3f(x, 0, 0);
            glVertex3f(0, y, 0);
            glVertex3f(0, 0, z);
        }
        glEnd();
        glColor3d(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 150; i++) {
            //glVertex3i(i, 2 * i, 0);
            float x = normalize(i);
            float y = x;
            float z = y;
            glVertex3f(x, 0.3, 0.7);
            glVertex3f(x, 0.8, 0.1);
            //glVertex3f(0, y, 0);
            //glVertex3f(0, 0, z);
        }
        glEnd();
        glColor3d(0.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 150; i++) {
            //glVertex3i(i, 2 * i, 0);
            float x = normalize(i);
            float y = x;
            float z = y;
            glVertex3f(x, 0.8, 0.7);
            glVertex3f(x, 0.3, 0.1);
            //glVertex3f(x, 0.4, 0.1);
            //glVertex3f(0, y, 0);
            //glVertex3f(0, 0, z);
        }
        glEnd();
        glColor3d(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 10; i < 70; i++) {
            //glVertex3i(i, 2 * i, 0);
            float x = normalize(i);
            float y = x;
            float z = y;
            glVertex3f(0.0, 0.3, z);
            glVertex3f(0.0, 0.8, z);
            glVertex3f(1.5, 0.3, z);
            glVertex3f(1.5, 0.8, z);
        }
        glEnd();
        glColor3d(0.5, 0.5, 0.5);
        glBegin(GL_POINTS);
        for (int i = 30; i < 80; i++) {
            //glVertex3i(i, 2 * i, 0);
            float x = normalize(i);
            float y = x;
            float z = y;
            glVertex3f(0.0, y, 0.7);
            glVertex3f(0.0, y, 0.1);
            glVertex3f(1.5, y, 0.7);
            glVertex3f(1.5, y, 0.1);
        }
        glEnd();
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
