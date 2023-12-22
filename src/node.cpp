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
