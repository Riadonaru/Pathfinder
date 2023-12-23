#include <stdexcept>
#include "node.h"
#include "draw.h"
#include "link.h"

Node Node::nodes[WIDTH][HEIGHT];

Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;
    trans_x = X_SPACING * (x + 0.5f) - 1.0f;
    trans_y = Y_SPACING * (y + 0.5f) - 1.0f;
}

void Node::draw()
{

    switch (highlight)
    {
    case 1:
        draw(0.0f, 0.0f, 1.0f, true);
        break;
    case 2:
        draw(1.0f, 0.0f, 0.0f, true);
        break;
    case 3:
        draw(0.0f, 1.0f, 0.0f, true);
        break;

    default:
        if (explored)
        {
            draw(1.0f, 1.0f, 1.0f, true);
        }
        else
        {
            draw(1.0f, 1.0f, 1.0f, false);
        }
        break;
    }
}

void Node::draw(float r, float g, float b, bool fill)
{
    drawSquare(trans_x, trans_y, CIRCLE_RADIOUS, r, g, b, fill);
    // drawCircle(trans_x, trans_y, CIRCLE_RADIOUS, 10, r, g, b, fill);
    if (y + 1 < HEIGHT && up == nullptr)
    {
        float avg_y = (trans_y + nodes[x][y + 1].trans_y) / 2;
        drawLine(trans_x + X_LINESPACE, avg_y, trans_x - X_LINESPACE, avg_y, 1.0f, 1.0f, 1.0f);
    }

    if (y > 0 && down == nullptr)
    {
        float avg_y = (trans_y + nodes[x][y - 1].trans_y) / 2;
        drawLine(trans_x + X_LINESPACE, avg_y, trans_x - X_LINESPACE, avg_y, 1.0f, 1.0f, 1.0f);
    }

    if (x > 0 && left == nullptr)
    {
        float avg_x = (trans_x + nodes[x - 1][y].trans_x) / 2;
        drawLine(avg_x, trans_y + Y_LINESPACE, avg_x, trans_y - Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }

    if (x + 1 < WIDTH && right == nullptr)
    {
        float avg_x = (trans_x + nodes[x + 1][y].trans_x) / 2;
        drawLine(avg_x, trans_y + Y_LINESPACE, avg_x, trans_y - Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }
}

Node **Node::getNeighbors()
{
    int size = 0;
    int index = 0;
    if (up != nullptr)
    {
        size++;
    }
    if (down != nullptr)
    {
        size++;
    }
    if (left != nullptr)
    {
        size++;
    }
    if (right != nullptr)
    {
        size++;
    }
    num_of_neighbors = size;
    Node **temp = new Node *[size];

    if (up != nullptr)
    {
        temp[index] = up;
        index++;
    }
    if (down != nullptr)
    {
        temp[index] = down;
        index++;
    }
    if (left != nullptr)
    {
        temp[index] = left;
        index++;
    }
    if (right != nullptr)
    {
        temp[index] = right;
        index++;
    }
    return temp;
}

void Node::linkUp()
{
    if (y + 1 < HEIGHT)
    {
        up = &nodes[x][y + 1];
        up->down = this;
    }
}

void Node::linkDown()
{
    if (y > 0)
    {
        down = &nodes[x][y - 1];
        down->up = this;
    }
}

void Node::linkLeft()
{
    if (x > 0)
    {
        left = &nodes[x - 1][y];
        left->right = this;
    }
}

void Node::linkRight()
{
    if (x + 1 < WIDTH)
    {
        right = &nodes[x + 1][y];
        right->left = this;
    }
}