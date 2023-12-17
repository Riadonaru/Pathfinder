#ifndef __HEADERS__
#define __HEADERS__
#define WIDTH 10
#define HEIGHT 5
#define X_SPACING (2.0f / WIDTH)
#define Y_SPACING (2.0f / HEIGHT)

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

    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        linkUpperNeighbor(nodes[x][y + 1]);
        linkLowerNeighbor(nodes[x][y - 1]);
        linkLeftNeighbor(nodes[x - 1][y]);
        linkRightNeighbor(nodes[x + 1][y]);
    }

    void linkUpperNeighbor(Node n)
    {
        this->up = &n;
    }

    void linkLowerNeighbor(Node n)
    {
        this->down = &n;
    }

    void linkLeftNeighbor(Node n)
    {
        this->left = &n;
    }

    void linkRightNeighbor(Node n)
    {
        this->right = &n;
    }

    Node upperNeighbor();
    Node lowerNeighbor();
    Node leftNeighbor();
    Node rightNeighbor();


    void draw();

private:
    Node *up;
    Node *down;
    Node *left;
    Node *right;

    float x;
    float y;
};

void drawLine(float x1, float y1, float x2, float y2);

#endif