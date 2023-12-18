#ifndef __HEADERS__
#define __HEADERS__
#define WIDTH 8
#define HEIGHT 5
#define X_SPACING (2.0f / WIDTH)
#define Y_SPACING (2.0f / HEIGHT)
#define X_LINESPACE X_SPACING / 10
#define Y_LINESPACE Y_SPACING / 10
#define TWO_X_LINESPACE 1.5 * X_LINESPACE
#define TWO_Y_LINESPACE 1.5 * Y_LINESPACE
#define CIRCLE_RADIOUS (4.0f / (WIDTH * HEIGHT) > 0.02 ? 0.02 : 4.0f / (WIDTH * HEIGHT))


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

    Node(int x, int y, bool highlight)
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
    }

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
    void draw(float r, float g, float b);

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

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b);
void drawSquare(float x, float y, float size);
void drawCircle(float x, float y, float radius, int segments, float r, float g, float b);
#endif