#ifndef __DRAW__
#define __DRAW__

#define SCREEN_WIDTH 1600.0
#define SCREEN_HEIGHT 900.0
#define ASPECT_RATIO (SCREEN_WIDTH / SCREEN_HEIGHT)

#define SCALE 3

#define WIDTH (16 * SCALE)
#define HEIGHT (9 * SCALE)
#define DELAY 10

#define X_SPACING (2.0f / WIDTH)
#define Y_SPACING (2.0f / HEIGHT)
#define X_LINESPACE X_SPACING / 2
#define Y_LINESPACE Y_SPACING / 2
#define CIRCLE_RADIOUS ((1.0f / (float)(50 * SCALE)) < 0.0025 ? 0.0025 : (1.0f / (float)(50 * SCALE)))

void events();

void hardReset();
void softReset();

void showPath();

int msleep(long tms);
int randInt(int min, int max);

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b);
void drawSquare(float x, float y, float size, float r, float g, float b, bool fill);
void drawCircle(float x, float y, float radius, int segments, float r, float g, float b, bool fill);

extern int click_index;
extern bool running;

#endif