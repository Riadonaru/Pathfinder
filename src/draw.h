#ifndef __DRAW__
#define __DRAW__

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0
#define ASPECT_RATIO (SCREEN_WIDTH / SCREEN_HEIGHT)

#define WIDTH 12
#define HEIGHT 8

#define X_SPACING (2.0f / WIDTH)
#define Y_SPACING (2.0f / HEIGHT)
#define X_LINESPACE X_SPACING / 2
#define Y_LINESPACE Y_SPACING / 2
#define CIRCLE_RADIOUS (4.0f / (WIDTH * HEIGHT) > 0.02 ? 0.02 : 4.0f / (WIDTH * HEIGHT))

void thread();
int msleep(long tms);
int randInt(int min, int max);

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b);
void drawSquare(float x, float y, float size, float r, float g, float b, bool fill);
void drawCircle(float x, float y, float radius, int segments, float r, float g, float b, bool fill);

#endif