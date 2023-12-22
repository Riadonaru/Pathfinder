#ifndef __NODE__
#define __NODE__

#include "draw.h"
#include "limits"

/**
 * @brief This class represents a node on screen. Each node has up to four neighbors.
 *
 */
class Node
{
public:
    static Node nodes[WIDTH][HEIGHT];
    static const int dist = 1;

    Node()
    {
    }

    Node(int x, int y);

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

    Node **getNeighbors();

    void draw();
    void draw(float r, float g, float b, bool fill);

    int highlight = 0;
    int shortest_est = std::numeric_limits<int>::max();

    bool explored = false;
    
    int num_of_neighbors;

    Node *back_track; // For when we get stuck
    Node *path_prev; // For when a path is found

private:
    Node *up;
    Node *down;
    Node *left;
    Node *right;

    int x;
    int y;
    float trans_x;
    float trans_y;

};

void djikstras(Node *src, Node *dest);
void _djikstras(Node *src, Node *dest);

#endif