#include <math.h>
#include "node.h"
#include "draw.h"
#include <ctime>
#include <random>
#include <iostream>
#include <stdio.h>
#include <stack>

void djikstras()
{

    Node *src = &Node::nodes[7 * SCALE][4 * SCALE];
    Node *dest = &Node::nodes[WIDTH - 1][HEIGHT - 1];
    src->highlight = 1;  // Blue color
    dest->highlight = 2; // Red color
    src->start_dist = 0;
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

        Node *next_node = nullptr;
        Node *neighbors[4] = {&Node::nodes[src->getX()][src->getY() + 1], &Node::nodes[src->getX()][src->getY() - 1], &Node::nodes[src->getX() - 1][src->getY()], &Node::nodes[src->getX() + 1][src->getY()]};

        bool allExplored = true;

        msleep(DELAY);
        for (int i = 0; i < 4; i++)
        {
            if (src->links[i])
            {
                int new_est = src->start_dist + Node::dist;
                Node *neighbor = neighbors[i];

                if (new_est < neighbor->start_dist)
                {
                    neighbor->start_dist = new_est;
                    neighbor->path_prev = src;
                }
            }
        }

        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                if ((next_node == nullptr || Node::nodes[i][j].start_dist < next_node->start_dist) && !Node::nodes[i][j].explored)
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

void aStar()
{
    Node *src = &Node::nodes[7 * SCALE][4 * SCALE];
    Node *dest = &Node::nodes[WIDTH - 1][HEIGHT - 1];
    src->highlight = 1;  // Blue color
    dest->highlight = 2; // Red color
    src->start_dist = 0;
    src->path_prev = nullptr;
    _aStar(src, dest);
}

void _aStar(Node *src, Node *dest)
{
    if (src != dest)
    {

        // Setup
        int mem = src->highlight;
        src->highlight = 3;
        src->explored = true;

        Node *next_node = nullptr;
        Node *neighbors[4] = {&Node::nodes[src->getX()][src->getY() + 1], &Node::nodes[src->getX()][src->getY() - 1], &Node::nodes[src->getX() - 1][src->getY()], &Node::nodes[src->getX() + 1][src->getY()]};

        bool allExplored = true;

        msleep(DELAY);

        // Updating estimates
        for (int i = 0; i < 4; i++)
        {
            if (src->links[i])
            {
                int new_est = src->start_dist + Node::dist;

                if (new_est < neighbors[i]->start_dist)
                {
                    neighbors[i]->start_dist = new_est;
                    neighbors[i]->aScore = new_est + neighbors[i]->end_dist;
                    neighbors[i]->path_prev = src;
                }
            }
        }

        // Choosing next node to explore.
        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                if ((next_node == nullptr || Node::nodes[i][j].aScore < next_node->aScore) && !Node::nodes[i][j].explored)
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
            _aStar(next_node, dest);
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

void rdfSearch()
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
        msleep(DELAY);
        myNode->highlight = false;
        myNode = link(myNode);
        if (myNode == nullptr)
        {
            history.pop();
            myNode = history.top();
            history.pop();
        }
    }
}

void events()
{
    rdfSearch();
    aStar();
    msleep(2000);
    hardReset();
    djikstras();
    msleep(1000);
    softReset();
}

Node *link(Node *myNode)
{
    Node *temp;
    Node *res = nullptr;
    std::stack<Node *> choices;
    std::stack<Node *> neighbors_copy(myNode->neighbors);

    while (!neighbors_copy.empty())
    {
        temp = neighbors_copy.top();
        if (!temp->visited)
        {
            choices.push(temp);
        }
        neighbors_copy.pop();
    }
    if (choices.empty())
    {
        return nullptr;
    }

    int rnd = randInt(0, choices.size() - 1);
    for (int i = 0; i < rnd; i++)
    {
        choices.pop();
    }
    Node *neighbor = choices.top();
    neighbor->highlight = 2;

    int x = neighbor->getX() - myNode->getX();
    int y = neighbor->getY() - myNode->getY();
    if (x == 0 && y == 1)
    {
        res = myNode->linkUp();
    }
    if (x == 0 && y == -1)
    {
        res = myNode->linkDown();
    }
    if (x == -1 && y == 0)
    {
        res = myNode->linkLeft();
    }
    if (x == 1 && y == 0)
    {
        res = myNode->linkRight();
    }
    return res;
}

void hardReset()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Node::nodes[j][i].highlight = 0;

            Node::nodes[j][i].explored = false;
            Node::nodes[j][i].visited = false;

            Node::nodes[j][i].start_dist = std::numeric_limits<int>::max();
            Node::nodes[j][i].end_dist = std::numeric_limits<float>::max();
            Node::nodes[j][i].aScore = std::numeric_limits<float>::max();
        }
    }
}

void softReset()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Node::nodes[j][i].explored = false;
            Node::nodes[j][i].visited = false;
        }
    }
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