#include "TXLib.h"

const int NBirds = 10;

struct SColors
    {
    COLORREF first, second, third, fourth, fifth;
    };

struct SKeys
    {
    int KeySpace, KeyRight, KeyLeft, KeyUp, KeyDown;
    };

struct SBird
    {
    int x, y, vx, vy;
    double size;

    COLORREF color;
    SColors colors;

    SKeys keys;
    };

void MoveBird ();
void Colors   (SBird* bird);
void Physics (SBird* bird, int dt);
void Control (SBird* bird);
void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF birdColor);
void DrawBirdHelper (SBird bird, int t);
void FillBirdArray      (SBird birds [], int nBirds);
void AddColorsForBirds  (SBird birds [], int nBirds);
void ProcessBirds       (SBird birds [], int nBirds, int t, int dt);
void DrawBirdsFromArray (SBird birds [], int nBirds, int t);
void AddPhysicsForBirds (SBird birds [], int nBirds, int dt);
void AddControlForBirds (SBird birds [], int nBirds);
void BirdAndMouseInteraction (SBird* bird);
void BirdsAndMouseInteraction (SBird birds [], int nBirds);
//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 650);

    txSetFillColor (RGB (26, 140, 255));
    txRectangle (0, 0, 1000, 650);

    MoveBird ();
    }
//-----------------------------------------------------------------------------

void MoveBird ()
    {
    SColors colors1 = {RGB (  2, 96,   2), RGB (100, 142,  62), RGB (  0, 187,   0), RGB ( 44, 244,  28), RGB (189, 255, 189)};
    SColors colors2 = {RGB (  4, 22, 187), RGB (100, 128, 255), RGB ( 90, 154, 241), RGB ( 17, 255, 255), RGB (  1, 186, 158)};
    SColors colors3 = {RGB (128,  0, 255), RGB (128,   0, 128), RGB (253,   2, 234), RGB (254, 141, 242), RGB (255,   0, 128)};
    SColors colors4 = {RGB (255,  0,   0), RGB (255, 140, 140), RGB (255, 128,   0), RGB (243, 191,  12), RGB (255, 255,   0)};

    SBird birds [NBirds] = {{500, 325, 3, 1, 1.7, RGB (255, 0, 0), colors1, {VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN}},
                            {100, 200, 4, 2,   2, RGB (255, 0, 0), colors2, {'1',      'C',      'Z',     'S',   'X'    }},
                            {300,   0, 1, 3, 1.3, RGB (255, 0, 0), colors3, {'2',      'N',      'V',     'H',   'B'    }},
                            {800, 500, 3, 4, 2.2, RGB (255, 0, 0), colors4, {'3',      'G',      'D',     'R',   'F'    }}};

    FillBirdArray (birds, NBirds);

    int t = 0;
    int dt = 1;

    txBegin ();

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        AddColorsForBirds (birds, NBirds);

        ProcessBirds (birds, NBirds, t, dt);

        //BirdAndMouseInteraction (&birds [0]);

        BirdsAndMouseInteraction (birds, NBirds);

        printf ("\n");

        t++;
        txSleep ();
        }

    txEnd ();
    }

void Physics (SBird* bird, int dt)
    {
    //printf ("BeginPhysics (): x = %i\n", *x);

    bird->x = bird->x + dt * bird->vx;

    bird->y = bird->y + dt * bird->vy;

    if (bird->x > 1000)
        {
        bird->vx = - bird->vx;
        bird->x = 1000;
        }

    if (bird->x < 0)
        {
        bird->vx = - bird->vx;
        bird->x = 0;
        }

    if (bird->y > 650)
        {
        bird->vy = - bird->vy;
        bird->y = 650;
        }

    if (bird->y < 0)
        {
        bird->vy = - bird->vy;
        bird->y = 0;
        }

    //printf ("EndPhysics ():   x = %i\n", bird->x);
    }

void Control (SBird* bird)
    {
    if (GetAsyncKeyState (bird->keys.KeySpace))
        {
        bird->vx = 0;
        bird->vy = 0;
        }

    if (GetAsyncKeyState (bird->keys.KeyRight))
        bird->vx = bird->vx + 1;

    if (GetAsyncKeyState (bird->keys.KeyLeft))
        bird->vx = bird->vx - 1;

    if (GetAsyncKeyState (bird->keys.KeyUp))
        bird->vy = bird->vy - 1;

    if (GetAsyncKeyState (bird->keys.KeyDown))
        bird->vy = bird->vy + 1;
    }

void Colors (SBird* bird)
    {
    //printf ("Colors ():   x = %i: ", bird.x);

    if ( -1 < bird->x && bird->x <= 200)
        {
        bird->color = bird->colors.first;
        //printf ("A");
        }

    if (200 < bird->x && bird->x <= 400)
        {
        bird->color = bird->colors.second;
        //printf ("B");
        }

    if (400 < bird->x && bird->x <= 600)
        {
        bird->color = bird->colors.third;
        //printf ("C");
        }

    if (600 < bird->x && bird->x <= 800)
        {
        bird->color = bird->colors.fourth;
        //printf ("D");
        }

    if (800 < bird->x && bird->x <= 1000)
        {
        bird->color = bird->colors.fifth;
        //printf ("E");
        }

    //printf ("\n");
    }

void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF birdColor)
    {

    txSetColor (TX_BLACK);
    txSetFillColor (birdColor);
    txEllipse (x- 9*sizeX, y- 5*sizeY, x+9*sizeX, y+5*sizeY);                                  // 782; 366
    txEllipse (x-16*sizeX, y-12*sizeY, x-5*sizeX, y-2*sizeY);
    txSetFillColor (RGB (255, 255, 255));
    txEllipse (x-14*sizeX, y-9*sizeY, x-11*sizeX, y-6*sizeY);
    txLine (x-1*sizeX, y+4*sizeY, x-(1+leg)*sizeX, y+(9-step)*sizeY);
    txLine (x+2*sizeX, y+4*sizeY, x+(2+leg)*sizeX, y+(9+step)*sizeY);
    txLine (x, y-2*sizeY, x, y+(3-wing)*sizeY);
    txLine (x-6*sizeX, y, x, y+(3-wing)*sizeY);
    txLine (x+9*sizeX, y, x+(16+tail)*sizeX, y-(7+wind)*sizeY);
    txLine (x+9*sizeX, y, x+(16+tail)*sizeX, y+(7-wind)*sizeY);
    txLine (x+9*sizeX, y, x+(19+tail)*sizeX, y-(3+wind)*sizeY);
    txLine (x+9*sizeX, y, x+(19+tail)*sizeX, y+(5-wind)*sizeY);
    txSetColor (RGB (255, 255, 0));
    txLine (x-17*sizeX, y-8*sizeY, x-18*sizeX, y-5*sizeY);
    txLine (x-19*sizeX, y-5*sizeY, x-15*sizeX, y-5*sizeY);
    }

void DrawBirdHelper (SBird bird, int t)
    {
    DrawBird (bird.x, bird.y, ((bird.vx < 0)? bird.size : -bird.size), bird.size, 0, 0, t/2%2*8, t/3%3 + 10, t/3%5 + 10, bird.color);
    }

void FillBirdArray (SBird birds [], int nBirds)
    {
    int i = 4;
    while (i < nBirds)
        {
        birds[i].x    = rand () % 500;
        birds[i].y    = rand () % 400;
        birds[i].vx   = rand () %   5 + 1;
        birds[i].vy   = rand () %   5 + 1;
        birds[i].size = rand () %   2 + 1;
        birds[i].color = RGB (rand () % 255, rand () % 255, rand () % 255);
        birds[i].colors.first  = RGB (rand () % 255, rand () % 255, rand () % 255);
        birds[i].colors.second = RGB (rand () % 255, rand () % 255, rand () % 255);
        birds[i].colors.third  = RGB (rand () % 255, rand () % 255, rand () % 255);
        birds[i].colors.fourth = RGB (rand () % 255, rand () % 255, rand () % 255);
        birds[i].colors.fifth  = RGB (rand () % 255, rand () % 255, rand () % 255);

        i++;
        }
    }

void AddColorsForBirds (SBird birds [], int nBirds)
    {
    int i = 0;
    while (i < NBirds)
        {
        Colors (&birds [i]);
        i++;
        }
    }

void ProcessBirds (SBird birds [], int nBirds, int t, int dt)
    {
    DrawBirdsFromArray (birds, nBirds, t);
    AddPhysicsForBirds (birds, nBirds, dt);
    AddControlForBirds (birds, nBirds);
    }

void DrawBirdsFromArray (SBird birds [], int nBirds, int t)
    {
    for (int i = 0; i < nBirds; i++) DrawBirdHelper (birds [i], t);
    }

void AddPhysicsForBirds(SBird birds [], int nBirds, int dt)
    {
    for (int i = 0; i < nBirds; i++) Physics (&birds [i], dt);
    }

void AddControlForBirds(SBird birds [], int nBirds)
    {
    for (int i = 0; i < nBirds; i++) Control (&birds [i]);
    }

// סל. פאיכ "interaction of bird with mouse"

void BirdAndMouseInteraction (SBird* bird)
    {
    POINT mouse = txMousePos ();

    double Fx = mouse.x - bird->x;
    double Fy = mouse.y - bird->y;

    double m = 10;

    double ax = Fx/m;
    double ay = Fy/m;

    bird->x = bird->x + ax;
    bird->y = bird->y + ay;
    }

void BirdsAndMouseInteraction (SBird birds [], int nBirds)
    {
    for (int i = 0; i < nBirds; i++) BirdAndMouseInteraction (&birds [i]);
    }

double Distance (const SBird* bird1, const SBird* bird2)
    {
    double dx = bird1->x - bird2->x;
    double dy = bird1->y - bird2->y;
    double d = sqrt (dx*dx + dy*dy);
    return d;
    }

void InteractionOfBirds (SBird birds [], int nBirds)
    {
    //double DDD = Distance (&bird [1], &bird [2]);
    for (int bird1 = 0; bird1 < nBirds; bird1++)
        for (int bird2 = 0; bird2 < nBirds; bird2++)
            Distance (bird [bird1], bird [bird2]);
    }
