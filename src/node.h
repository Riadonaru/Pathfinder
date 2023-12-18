#ifndef __NODE__
#define __NODE__

#include "draw.h"


/**
 * @brief This class represents a node on screen. Each node has up to four neighbors.
 *
 */
class Node
{
public:
    static Node nodes[WIDTH][HEIGHT];

    Node()
    {
    }

    Node(int x, int y, bool highlight);

    void linkUpperNeighbor(Node *n)
    {
        if (y + 1 < HEIGHT)
        {
            this->up = n;
        }
        else
        {
            this->up = nullptr;
        }
    }

    void linkLowerNeighbor(Node *n)
    {
        if (y > 0)
        {
            this->down = n;
        }
        else
        {
            this->down = nullptr;
        }
    }

    void linkLeftNeighbor(Node *n)
    {
        if (x > 0)
        {
            this->left = n;
        }
        else
        {
            this->left = nullptr;
        }
    }

    void linkRightNeighbor(Node *n)
    {
        if (x + 1 < WIDTH)
        {
            this->right = n;
        }
        else
        {
            this->right = nullptr;
        }
    }

    Node upperNeighbor();
    Node lowerNeighbor();
    Node leftNeighbor();
    Node rightNeighbor();

    void draw();
    void draw(float r, float g, float b, bool fill);

private:
    Node *up;
    Node *down;
    Node *left;
    Node *right;

    int x;
    int y;
    float trans_x;
    float trans_y;

    bool highlight;

};

#endif