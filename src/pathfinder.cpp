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

        Node *next_node = nullptr;
        Node *neighbors[4] = {&Node::nodes[src->getX()][src->getY() + 1], &Node::nodes[src->getX()][src->getY() - 1], &Node::nodes[src->getX() - 1][src->getY()], &Node::nodes[src->getX() + 1][src->getY()]};

        bool allExplored = true;

        msleep(DELAY);
        for (int i = 0; i < 4; i++)
        {
            if (src->links[i])
            {
                int new_est = src->shortest_est + Node::dist;
                Node *neighbor = neighbors[i];

                if (new_est < neighbor->shortest_est)
                {
                    neighbor->shortest_est = new_est;
                    neighbor->path_prev = src;
                }
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

void aStar() {
    
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
    djikstras();
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