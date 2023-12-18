#include <stdexcept>
#include "node.h"
#include "draw.h"
#include "link.h"

Node Node::nodes[WIDTH][HEIGHT];

Node::Node(int x, int y, bool highlight)
{
    this->x = x;
    this->y = y;
    this->highlight = highlight;
    trans_x = X_SPACING * (x + 0.5f) - 1.0f;
    trans_y = Y_SPACING * (y + 0.5f) - 1.0f;

    linkUpperNeighbor(&nodes[x][y + 1]);
    linkLowerNeighbor(&nodes[x][y - 1]);
    linkLeftNeighbor(&nodes[x - 1][y]);
    linkRightNeighbor(&nodes[x + 1][y]);

    int choice = randInt(0, 3);
    switch (choice)
    {
    case 0:
        linkUpperNeighbor(nullptr);
        break;
    case 1:
        linkLowerNeighbor(nullptr);
        break;
    case 2:
        linkLeftNeighbor(nullptr);
        break;
    case 3:
        linkRightNeighbor(nullptr);
        break;
    }
}

void Node::draw()
{
    if (highlight)
    {
        draw(0.0f, 0.0f, 1.0f, true);
    }
    else
    {
        draw(1.0f, 1.0f, 1.0f, false);
    }
}

void Node::draw(float r, float g, float b, bool fill)
{
    drawSquare(trans_x, trans_y, CIRCLE_RADIOUS, r, g, b, fill);
    // drawCircle(trans_x, trans_y, CIRCLE_RADIOUS, 10, r, g, b, fill);
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