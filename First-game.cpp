#include "TXLib.h"

struct SBird
    {
    int x, y, vx, vy;
    double size;
    COLORREF color;
    };

void MoveBird ();
void Colors (int* x, COLORREF* birdColor, COLORREF first, COLORREF second, COLORREF third, COLORREF fourth, COLORREF fifth);
void Physics (int* x, int* y, int* vx, int* vy, int dt);
void Control (int* vx, int* vy, int KeySpace, int KeyRight, int KeyLeft, int KeyUp, int KeyDown);
void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF birdColor);
void DrawBirdHelper (SBird bird, int t);
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
    SBird bird1 = {500, 325, 3, 1, 1.7, RGB (0, 0, 0)};
    SBird bird2 = {100, 200, 4, 2,   2, RGB (0, 0, 0)};
    SBird bird3 = {300,   0, 1, 3, 1.3, RGB (0, 0, 0)};
    SBird bird4 = {800, 500, 3, 4, 2.2, RGB (0, 0, 0)};

    int t = 0;
    int dt = 1;

    txBegin ();

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        Colors (&bird1.x, &bird1.color, RGB (  2, 96,   2), RGB (100, 142,  62), RGB (  0, 187,   0), RGB ( 44, 244,  28), RGB (189, 255, 189));
        Colors (&bird2.x, &bird2.color, RGB (  4, 22, 187), RGB (100, 128, 255), RGB ( 90, 154, 241), RGB ( 17, 255, 255), RGB (  1, 186, 158));
        Colors (&bird3.x, &bird3.color, RGB (128,  0, 255), RGB (128,   0, 128), RGB (253,   2, 234), RGB (254, 141, 242), RGB (255,   0, 128));
        Colors (&bird4.x, &bird4.color, RGB (255,  0,   0), RGB (255, 140, 140), RGB (255, 128,   0), RGB (243, 191,  12), RGB (255, 255,   0));

        DrawBirdHelper (bird1, t);
        DrawBirdHelper (bird2, t);
        DrawBirdHelper (bird3, t);
        DrawBirdHelper (bird4, t);

        //printf ("MoveBall before physics (): x = %i\n", x);

        Physics (&bird1.x, &bird1.y, &bird1.vx, &bird1.vy, dt);
        Physics (&bird2.x, &bird2.y, &bird2.vx, &bird2.vy, dt);
        Physics (&bird3.x, &bird3.y, &bird3.vx, &bird3.vy, dt);
        Physics (&bird4.x, &bird4.y, &bird4.vx, &bird4.vy, dt);

        //printf ("MoveBall after physics ():  x = %i\n", x);

        Control (&bird1.vx, &bird1.vy, VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN);
        Control (&bird2.vx, &bird2.vy, '1',      'C',      'Z',     'S',   'X'    );
        Control (&bird3.vx, &bird3.vy, '2',      'N',      'V',     'H',   'B'    );
        Control (&bird4.vx, &bird4.vy, '3',      'G',      'D',     'R',   'F'    );

        printf ("\n");

        t++;
        txSleep (20);
        }

    txEnd ();
    }

void Physics (int* x, int* y, int* vx, int* vy, int dt)
    {
    //printf ("BeginPhysics (): x = %i\n", *x);

    *x = *x + dt * *vx;

    *y = *y + dt * *vy;

    if (*x > 1000)
        {
        *vx = - *vx;
        *x = 1000;
        }

    if (*x < 0)
        {
        *vx = - *vx;
        *x = 0;
        }

    if (*y > 650)
        {
        *vy = - *vy;
        *y = 650;
        }

    if (*y < 0)
        {
        *vy = - *vy;
        *y = 0;
        }

    //printf ("EndPhysics ():   x = %i\n", *x);
    }

void Control (int* vx, int* vy, int KeySpace, int KeyRight, int KeyLeft, int KeyUp, int KeyDown)
    {
    if (GetAsyncKeyState (KeySpace))
        {
        *vx = 0;
        *vy = 0;
        }

    if (GetAsyncKeyState (KeyRight))
        *vx = *vx + 1;

    if (GetAsyncKeyState (KeyLeft))
        *vx = *vx - 1;

    if (GetAsyncKeyState (KeyUp))
        *vy = *vy - 1;

    if (GetAsyncKeyState (KeyDown))
        *vy = *vy + 1;
    }

void Colors (int* x, COLORREF* birdColor, COLORREF first, COLORREF second, COLORREF third, COLORREF fourth, COLORREF fifth)
    {
    //printf ("Colors ():   x = %i: ", *x);

    if ( -1 < *x && *x <= 200)
        {
        *birdColor = first;
        //printf ("A");
        }

    if (200 < *x && *x <= 400)
        {
        *birdColor = second;
        //printf ("B");
        }

    if (400 < *x && *x <= 600)
        {
        *birdColor = third;
        //printf ("C");
        }

    if (600 < *x && *x <= 800)
        {
        *birdColor = fourth;
        //printf ("D");
        }

    if (800 < *x && *x <= 1000)
        {
        *birdColor = fifth;
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
