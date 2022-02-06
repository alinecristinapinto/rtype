#define NUM_STARS 50

typedef struct Star
{
    float x, y, radius, moveSpeed;
} Star;

void initStars(Star stars[], int screen_w, int screen_h, float moveSpeed);

void updateStars(Star stars[], int screen_w);

void drawStars(Star stars[]);