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
    drawCircle(trans_x, trans_y, 0.01f, 10);

    if (up != nullptr)
    {
        drawLine(trans_x, trans_y + 0.05f, up->trans_x, up->trans_y - 0.05f);
    }

    // drawLine(trans_x, trans_y + 0.05f, trans_x, trans_y - 0.05f);
    // drawLine(trans_x + 0.05f, trans_y, trans_x - 0.05f, trans_y);
}