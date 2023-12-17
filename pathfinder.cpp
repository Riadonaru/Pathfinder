#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "headers.h"
#include <math.h>
#include <stdio.h>

void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawSquare(float x, float y, float size)
{
    glBegin(GL_QUADS);
    glVertex2f(x - size / 2.0, y - size / 2.0); // Bottom-left vertex
    glVertex2f(x + size / 2.0, y - size / 2.0); // Bottom-right vertex
    glVertex2f(x + size / 2.0, y + size / 2.0); // Top-right vertex
    glVertex2f(x - size / 2.0, y + size / 2.0); // Top-left vertex
    glEnd();
}

void drawCircle(float center_x, float center_y, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(center_x, center_y); // Center of the circle

    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        glVertex2f(x + center_x, y + center_y);
    }

    glEnd();
}

int main()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Node::nodes[j][i] = Node(j, i);
        }
    }

    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "Pathfinding Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    float x_spacing = 2.0f / WIDTH;
    float y_spacing = 2.0f / HEIGHT;

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                Node::nodes[j][i].draw();
                Node temp = Node::nodes[j][i];
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}