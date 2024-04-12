#ifndef __NODE__
#define __NODE__

#include "draw.h"
#include "limits"
#include <stack>

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

    void draw();
    void draw(float r, float g, float b, bool fill);

    int getX();
    int getY();

    Node *linkUp();
    Node *linkDown();
    Node *linkLeft();
    Node *linkRight();

    int highlight = 0;
    int shortest_est = std::numeric_limits<int>::max();
    int dist_from_dest = std::numeric_limits<int>::max();

    bool explored = false;
    bool visited = false;

    Node *path_prev; // For when a path is found
    std::stack<Node *> neighbors;
    
    bool links[4] = {false, false, false, false}; // Up, Down, Left, Right: False means there is a wall, true means no wall.
private:
    int x;
    int y;

    float trans_x;
    float trans_y;


};

void djikstras();
void _djikstras(Node *src, Node *dest);

Node *link(Node *myNode);

#endif