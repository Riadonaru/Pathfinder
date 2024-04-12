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
    
    end_dist = ((WIDTH - x) * (WIDTH - x) + (HEIGHT - y) * (HEIGHT - y));
    
    if (y + 1 < HEIGHT)
    {
        neighbors.push(&Node::nodes[x][y + 1]);
    }

    if (y > 0)
    {
        neighbors.push(&Node::nodes[x][y - 1]);
    }

    if (x > 0)
    {
        neighbors.push(&Node::nodes[x - 1][y]);
    }

    if (x + 1 < WIDTH)
    {
        neighbors.push(&Node::nodes[x + 1][y]);
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
    if (fill)
    {
        drawSquare(trans_x, trans_y, CIRCLE_RADIOUS, r, g, b, fill);
        // drawCircle(trans_x, trans_y, CIRCLE_RADIOUS, 30, r, g, b, fill);
    }
    if (y + 1 < HEIGHT && !links[0])
    {
        float avg_y = (trans_y + nodes[x][y + 1].trans_y) / 2;
        drawLine(trans_x + X_LINESPACE, avg_y, trans_x - X_LINESPACE, avg_y, 1.0f, 1.0f, 1.0f);
    }

    if (y > 0 && !links[1])
    {
        float avg_y = (trans_y + nodes[x][y - 1].trans_y) / 2;
        drawLine(trans_x + X_LINESPACE, avg_y, trans_x - X_LINESPACE, avg_y, 1.0f, 1.0f, 1.0f);
    }

    if (x > 0 && !links[2])
    {
        float avg_x = (trans_x + nodes[x - 1][y].trans_x) / 2;
        drawLine(avg_x, trans_y + Y_LINESPACE, avg_x, trans_y - Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }

    if (x + 1 < WIDTH && !links[3])
    {
        float avg_x = (trans_x + nodes[x + 1][y].trans_x) / 2;
        drawLine(avg_x, trans_y + Y_LINESPACE, avg_x, trans_y - Y_LINESPACE, 1.0f, 1.0f, 1.0f);
    }
}

int Node::getX()
{
    return x;
}

int Node::getY()
{
    return y;
}

Node *Node::linkUp()
{
    if (y + 1 < HEIGHT && nodes[x][y + 1].visited == false)
    {
        links[0] = true;
        (&nodes[x][y + 1])->links[1] = true;
        return (&nodes[x][y + 1]);
    }
    return nullptr;
}

Node *Node::linkDown()
{
    if (y > 0 && nodes[x][y - 1].visited == false)
    {
        links[1] = true;
        (&nodes[x][y - 1])->links[0] = true;
        return (&nodes[x][y - 1]);
    }
    return nullptr;
}

Node *Node::linkLeft()
{
    if (x > 0 && nodes[x - 1][y].visited == false)
    {
        links[2] = true;
        (&nodes[x - 1][y])->links[3] = true;
        return (&nodes[x - 1][y]);
    }
    return nullptr;
}

Node *Node::linkRight()
{
    if (x + 1 < WIDTH && nodes[x + 1][y].visited == false)
    {
        links[3] = true;
        (&nodes[x + 1][y])->links[2] = true;
        return (&nodes[x + 1][y]);
    }
    return nullptr;
}