
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float dt = 0;
bool rise = true;
const double pi = std::acos(-1); //std::numbers::pi since C++20

float normalize(float val)
{
    return val / 100.0f;
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-50.0, 50.0, -50.0, 50.0, 0.0, 100.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Drawing routine.
void drawScene(void)
{
	float R = 20.0; // Radius of helix.

	float t; // Angle parameter.

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
    float x, y, z;
	for (t = -10 * pi; t <= 10 * pi; t += pi / 20.0)
    {
       x = R * std::cos(t);
       y = R * std::sin(t);
       z = t - 60.0 + dt * 10;
       glVertex3f(x, y, z); //this one would be birds eye view
	   //FUN
       //glVertex3f(R * cos(t), t, R * sin(dt * t) - 60.0);
       //glVertex3f((R) * cos(t), t, (R+dt*10) * sin(t) - 60.0);
    }
	glEnd();

	glFlush();
}


void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
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
    GLFWwindow* window = glfwCreateWindow(800, 400, "Legacy OpenGL Example", NULL, NULL);
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
    //setup();
    // Check OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    resize(800, 400);
    // Render loop
    glPointSize(2.0f); // Set point size to 5 pixels
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);
        if (dt >= 1.0 || dt <= -1.0)
            rise = !rise;
        if (rise) 
            dt += 0.01;
        else
            ;//dt -= 0.01;

        // Legacy OpenGL commands

        drawScene();

        glBegin(GL_POLYGON);
            glVertex3f(0.2, 0.2, 0.0);
            glVertex3f(1.0, 0.2, 0.0);
            glVertex3f(0.8, 0.8, 0.0);
            glVertex3f(0.0, 0.8, 0.0);
        glEnd();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
