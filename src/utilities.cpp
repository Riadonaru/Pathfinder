#include <math.h>
#include "node.h"
#include "draw.h"
#include <ctime>
#include <random>
#include <iostream>
#include <stdio.h>
#include <stack>

void events()
{
    while (true)
    {
        switch (click_index)
        {
        case 1:
            running = true;
            rdfSearch();
            click_index++;
            break;

        case 2:
            break;

        case 3:
            running = true;
            aStar();
            click_index++;
            break;

        case 4:
            break;

        case 5:
            running = true;
            softReset();
            djikstras();
            click_index++;
            break;

        case 6:
            break;
        }
        
        running = false;
    }
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

            Node::nodes[j][i].links[0] = false;
            Node::nodes[j][i].links[1] = false;
            Node::nodes[j][i].links[2] = false;
            Node::nodes[j][i].links[3] = false;
        }
    }
}

void softReset()
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

void showPath()
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