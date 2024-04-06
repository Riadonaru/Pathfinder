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

    Node **getNeighbors();

    void draw();
    void draw(float r, float g, float b, bool fill);

    Node *linkUp();
    Node *linkDown();
    Node *linkLeft();
    Node *linkRight();

    int highlight = 0;
    int shortest_est = std::numeric_limits<int>::max();

    bool explored = false;
    bool visited = false;

    int num_of_neighbors;

    Node *path_prev; // For when a path is found

private:
    Node *up = nullptr;
    Node *down = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

    int x;
    int y;
    float trans_x;
    float trans_y;
};

void djikstras();
void _djikstras(Node *src, Node *dest);

Node *link(Node *myNode);

#endif