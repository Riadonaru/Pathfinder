#include <math.h>
#include "node.h"
#include "draw.h"
#include <ctime>
#include <random>
#include <iostream>

void djikstras(Node *src, Node *dest)
{
    src->shortest_est = 0;
    src->path_prev = nullptr;
    _djikstras(src, dest);
}

void _djikstras(Node *src, Node *dest)
{
    if (src != dest)
    {
        int mem = src->highlight;
        src->highlight = 3;
        src->explored = true;

        Node **neighbors = src->getNeighbors();
        Node *next_node = nullptr;

        bool allExplored = true;

        for (int i = 0; i < src->num_of_neighbors; i++)
        {
            msleep(50);
            int new_est = src->shortest_est + Node::dist;

            if (new_est < neighbors[i]->shortest_est)
            {
                neighbors[i]->shortest_est = new_est;
                neighbors[i]->path_prev = src;
            }
        }

        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                if ((next_node == nullptr || Node::nodes[i][j].shortest_est < next_node->shortest_est) && !Node::nodes[i][j].explored)
                {
                    next_node = &Node::nodes[i][j];
                    allExplored = false;
                }
            }
        }
        if (allExplored)
        {
            std::cout << "No path from the source to the given destination..." << std::endl;
        }
        else
        {
            src->highlight = mem;
            _djikstras(next_node, dest);
        }
    }
    else
    {
        std::cout << "Found path!" << std::endl;
        Node *temp = src->path_prev;
        while (temp->path_prev != nullptr)
        {
            temp->highlight = 3;
            temp = temp->path_prev;
        }
    }
}

void thread()
{
    int x = randInt(0, WIDTH - 1);
    int y = randInt(0, HEIGHT - 1);

    int dx, dy;

    do
    {
        dx = randInt(0, WIDTH - 1);
        dy = randInt(0, HEIGHT - 1);
    } while (x == dx && y == dy);

    Node *src = &Node::nodes[x][y];
    Node *dest = &Node::nodes[dx][dy];
    src->highlight = 1;  // Blue color
    dest->highlight = 2; // Red color
    djikstras(src, dest);
}

int msleep(long tms)
{
    struct timespec ts;
    int ret;

    if (tms < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do
    {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}

int randInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}