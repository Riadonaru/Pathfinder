#include <math.h>
#include "node.h"
#include "draw.h"
#include <ctime>
#include <random>
#include <iostream>
#include <stack>

void djikstras()
{

    Node *src = &Node::nodes[0][0];
    Node *dest = &Node::nodes[WIDTH - 1][HEIGHT - 1];
    src->highlight = 1;  // Blue color
    dest->highlight = 2; // Red color
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
            msleep(10);
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

void algo()
{
    Node *myNode = &Node::nodes[0][0];
    std::stack<Node *> history;
    int total_visited = 0;
    while (total_visited < WIDTH * HEIGHT)
    {
        myNode->highlight = true;
        if (!myNode->visited)
        {
            myNode->visited = true;
            total_visited++;
        }
        history.push(myNode);
        msleep(5);
        myNode->highlight = false;
        myNode = link(myNode);
        if (myNode == nullptr)
        {
            history.pop();
            myNode = history.top();
            history.pop();
        }
    }

    std::cout << "Maze generated... Prepering solver;" << std::endl;
    msleep(2000);
    djikstras();
    std::cout << "Maze Solved... Showing solution;" << std::endl;
    msleep(2000);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Node::nodes[j][i].explored = false;
            Node::nodes[j][i].visited = false;
        }
    }
}

Node *link(Node *myNode)
{
    Node *res;
    int selected[] = {-1, -1, -1, -1};
    int index = 0;
    bool present = false;
    do
    {
        int dir = randInt(0, 3);
        present = false;

        for (int i = 0; i < 4; i++)
        {
            if (selected[i] == dir)
            {
                present = true;
            }
        }

        if (!present)
        {
            selected[index] = dir;
            index++;

            switch (dir)
            {
            case 1:
                res = myNode->linkDown();
                break;
            case 2:
                res = myNode->linkRight();
                break;
            case 3:
                res = myNode->linkLeft();
                break;
            default:
                res = myNode->linkUp();
                break;
            }
        }
        else
        {
            if (index == 4)
            {
                return nullptr;
            }
        }

    } while (res == nullptr);
    return res;
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