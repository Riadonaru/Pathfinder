#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "node.h"
#include "draw.h"

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glBegin(GL_LINES);
    glColor3f(r, g, b);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}

void drawSquare(float x, float y, float size, float r, float g, float b)
{

    // Adjust both width and height for aspect ratio
    float adjustedHeight = size * ASPECT_RATIO;

    glBegin(GL_LINE_LOOP);
    glColor3f(r, g, b);
    glVertex2f(x - size / 2.0, y - adjustedHeight / 2.0); // Bottom-left vertex
    glVertex2f(x + size / 2.0, y - adjustedHeight / 2.0); // Bottom-right vertex
    glVertex2f(x + size / 2.0, y + adjustedHeight / 2.0); // Top-right vertex
    glVertex2f(x - size / 2.0, y + adjustedHeight / 2.0); // Top-left vertex
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}


void drawCircle(float x, float y, float radius, int segments, float r, float g, float b) {
    glBegin(GL_LINE_LOOP);
    glColor3f(r, g, b); // Set the color
    
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float dx = radius * cos(angle); // Adjust radius for aspect ratio
        float dy = radius * sin(angle) * ASPECT_RATIO;
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

int main()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 3 && j == 4)
            {
                Node::nodes[j][i] = Node(j, i, true);
            }
            else
            {
                Node::nodes[j][i] = Node(j, i, false);
            }
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