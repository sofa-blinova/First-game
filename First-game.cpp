#include "TXLib.h"

void MoveBird ();
void Colors (int* x, COLORREF* birdColor, COLORREF first, COLORREF second, COLORREF third, COLORREF fourth, COLORREF fifth);
void Physics (int* x, int* y, int* vx, int* vy, int dt);
void Control (int* vx, int* vy, int KeySpace, int KeyRight, int KeyLeft, int KeyUp, int KeyDown);
void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF birdColor);
void DrawBirdHelper (int x, int y, int vx, int vy, double size, COLORREF birdColor, int t);
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
    int x = 500, y = 325;
    int vx = 3, vy = 1;
    COLORREF birdColor  = RGB (0, 0, 0);

    int x2 = 100, y2 = 200;
    int vx2 = 4, vy2 = 2;
    COLORREF birdColor2 = RGB (0, 0, 0);

    int x3 = 300, y3 = 0;
    int vx3 = 1, vy3 = 3;
    COLORREF birdColor3 = RGB (0, 0, 0);

    int x4 = 800, y4 = 500;
    int vx4 = 3, vy4 = 4;
    COLORREF birdColor4 = RGB (0, 0, 0);

    int t = 0;
    int dt = 1;

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        Colors ( &x, &birdColor , RGB (2, 96, 2), RGB (100, 142, 62), RGB (0, 187, 0), RGB (44, 244, 28), RGB (189, 255, 189));
        Colors (&x2, &birdColor2, RGB (4, 22, 187), RGB (100, 128, 255), RGB (90, 154, 241), RGB (17, 255, 255), RGB (1, 186, 158));
        Colors (&x3, &birdColor3, RGB (128, 0, 255), RGB (128, 0, 128), RGB (253, 2, 234), RGB (254, 141, 242), RGB (255, 0, 128));
        Colors (&x4, &birdColor4, RGB (255, 0, 0), RGB (255, 140, 140), RGB (255, 128, 0), RGB (243, 191, 12), RGB (255, 255, 0));

        DrawBirdHelper ( x,  y,  vx,  vy, 1.7, birdColor , t);
        DrawBirdHelper (x2, y2, vx2, vy2,   2, birdColor2, t);
        DrawBirdHelper (x3, y3, vx3, vy3, 1.3, birdColor3, t);
        DrawBirdHelper (x4, y4, vx4, vy4, 2.2, birdColor4, t);

        printf ("MoveBall before physics (): x = %i\n", x);

        Physics ( &x,  &y,  &vx,  &vy, dt);
        Physics (&x2, &y2, &vx2, &vy2, dt);
        Physics (&x3, &y3, &vx3, &vy3, dt);
        Physics (&x4, &y4, &vx4, &vy4, dt);

        printf ("MoveBall after physics ():  x = %i\n", x);

        Control (&vx, &vy, VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN);
        Control (&vx2, &vy2, '1', 'C', 'Z', 'S', 'X');
        Control (&vx3, &vy3, '2', 'N', 'V', 'H', 'B');
        Control (&vx4, &vy4, '3', 'G', 'D', 'R', 'F');

        printf ("\n");

        t++;
        txSleep (10);
        }
    }

void Physics (int* x, int* y, int* vx, int* vy, int dt)
    {
    printf ("BeginPhysics (): x = %i\n", *x);

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

    printf ("EndPhysics ():   x = %i\n", *x);
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
    printf ("Colors ():   x = %i: ", *x);

    if ( -1 < *x && *x <= 200)
        {
        *birdColor = first;
        printf ("A");
        }

    if (200 < *x && *x <= 400)
        {
        *birdColor = second;
        printf ("B");
        }

    if (400 < *x && *x <= 600)
        {
        *birdColor = third;
        printf ("C");
        }

    if (600 < *x && *x <= 800)
        {
        *birdColor = fourth;
        printf ("D");
        }

    if (800 < *x && *x <= 1000)
        {
        *birdColor = fifth;
        printf ("E");
        }

    printf ("\n");
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

void DrawBirdHelper (int x, int y, int vx, int vy, double size, COLORREF birdColor, int t)
    {
    DrawBird (x, y, ((vx < 0)? size : -size), size, 0, 0, t/2%2*8, t/3%3 + 10, t/3%5 + 10, birdColor);
    }
