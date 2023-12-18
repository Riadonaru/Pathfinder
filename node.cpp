#include "headers.h"
#include <stdexcept>

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
    if (highlight)
    {
        draw(0.0f, 0.0f, 1.0f);
    }
    else
    {
        draw(1.0f, 1.0f, 1.0f);
    }
}

void Node::draw(float r, float g, float b)
{
    drawCircle(trans_x, trans_y, CIRCLE_RADIOUS, 10, r, g, b);
    if (up != nullptr)
    {
        drawLine(trans_x + X_LINESPACE, trans_y + TWO_Y_LINESPACE, up->trans_x + X_LINESPACE, up->trans_y - TWO_Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }

    if (down != nullptr)
    {
        drawLine(trans_x - X_LINESPACE, trans_y - TWO_Y_LINESPACE, down->trans_x - X_LINESPACE, down->trans_y + TWO_Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }

    if (left != nullptr)
    {
        drawLine(trans_x - TWO_X_LINESPACE, trans_y - Y_LINESPACE, left->trans_x + TWO_X_LINESPACE, left->trans_y - Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }

    if (right != nullptr)
    {
        drawLine(trans_x + TWO_X_LINESPACE, trans_y + Y_LINESPACE, right->trans_x - TWO_X_LINESPACE, right->trans_y + Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }
}