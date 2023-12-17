#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdexcept>
#include <stdio.h>
#include "headers.h"

Node Node::nodes[WIDTH][HEIGHT];
Node Node::upperNeighbor()
{
    if (up != nullptr)
    {
        return *up;
    }
    throw std::runtime_error("An attempt to access node (" + std::to_string(x) + ", " + std::to_string(y) + " )'s upper neighbor was denied because it is null");
}

Node Node::lowerNeighbor()
{
    if (down != nullptr)
    {
        return *down;
    }
    throw std::runtime_error("An attempt to access node (" + std::to_string(x) + ", " + std::to_string(y) + " )'s lower neighbor was denied because it is null");
}

Node Node::leftNeighbor()
{
    if (left != nullptr)
    {
        return *left;
    }
    throw std::runtime_error("An attempt to access node (" + std::to_string(x) + ", " + std::to_string(y) + " )'s left neighbor was denied because it is null");
}

Node Node::rightNeighbor()
{
    if (right != nullptr)
    {
        return *right;
    }
    throw std::runtime_error("An attempt to access node (" + std::to_string(x) + ", " + std::to_string(y) + " )'s right neighbor was denied because it is null");
}


void Node::draw()
{
    float trans_x = X_SPACING * (x + 1) - 1.1;
    float trans_y = Y_SPACING * (y + 1) - 1.2f;

    drawLine(trans_x, trans_y + 0.05f, trans_x, trans_y - 0.05f);
    drawLine(trans_x + 0.05f, trans_y, trans_x - 0.05f, trans_y);
}

void drawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
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

    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
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
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}